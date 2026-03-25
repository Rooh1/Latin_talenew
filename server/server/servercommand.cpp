#include "stdafx.h"
#include "servercommand.h"

#define COMMAND StrCmpPT

typedef UINT( __cdecl *t_GetItemBySpeckPerf )( UserData * pcUserData, UserData * pcUserDataRecv, char * ItemCodeOrName );
t_GetItemBySpeckPerf GetItemBySpeckPerf = ( t_GetItemBySpeckPerf )0x08B70388;

typedef BOOL( __cdecl *tfnGetParamOld )(char * pszBuffRecv, char * pszBuffer);
tfnGetParamOld fnGetParamOld = (tfnGetParamOld)0x00552320;

typedef UserData*(__cdecl *tfnGetUsedataLoginName)(char * pszName);
tfnGetUsedataLoginName fnGetUsedataLoginName = (tfnGetUsedataLoginName)0x00552400;

extern BOOL bTestDebugDamageUnit;
extern BOOL bFreeExpEvent;
extern int iExpFreeExp;

extern int iUpdateMaxPacket;
extern int iUpdateMaxUnitMask;
extern int iUpdateFrameCounter;

int StrCmpPT( const char *Comando1, const char *Comando2 )
{
	int Resultado = 0;
	__asm{
		pushad
			push ecx
			push Comando2
			mov eax, Comando1
			mov ecx, 0x005522D0
			call ecx
			add esp, 4
			mov Resultado, eax
			pop ecx
			popad
	}
	return Resultado;
}

EItemRarity ParseCommandItemRarity( const char * pszValue )
{
	if ( pszValue == NULL || pszValue[0] == 0 )
		return ITEMRARITY_None;

	if ( STRINGCOMPAREI( pszValue, "none" ) || STRINGCOMPAREI( pszValue, "0" ) )
		return ITEMRARITY_None;
	if ( STRINGCOMPAREI( pszValue, "common" ) || STRINGCOMPAREI( pszValue, "1" ) )
		return ITEMRARITY_Common;
	if ( STRINGCOMPAREI( pszValue, "uncommon" ) || STRINGCOMPAREI( pszValue, "2" ) )
		return ITEMRARITY_Uncommon;
	if ( STRINGCOMPAREI( pszValue, "rare" ) || STRINGCOMPAREI( pszValue, "3" ) )
		return ITEMRARITY_Rare;
	if ( STRINGCOMPAREI( pszValue, "epic" ) || STRINGCOMPAREI( pszValue, "4" ) )
		return ITEMRARITY_Epic;
	if ( STRINGCOMPAREI( pszValue, "legendary" ) || STRINGCOMPAREI( pszValue, "5" ) )
		return ITEMRARITY_Legendary;

	return (EItemRarity)-1;
}

const char * GetCommandItemRarityName( EItemRarity eRarity )
{
	switch ( eRarity )
	{
		case ITEMRARITY_None:		return "None";
		case ITEMRARITY_Common:		return "Common";
		case ITEMRARITY_Uncommon:	return "Uncommon";
		case ITEMRARITY_Rare:		return "Rare";
		case ITEMRARITY_Epic:		return "Epic";
		case ITEMRARITY_Legendary:	return "Legendary";
		default:					return "Unknown";
	}
}

void WriteSQLSkillInfo( const char * pszColumnName, const char * pszSkillTier, int iClass )
{
	int iCount = 0;

	struct SQLSkillDataInfo
	{
		char szColumnName[64];
		char szValues[10][32];
	};

	SQLSkillDataInfo * ps = new SQLSkillDataInfo[10];

	SQLConnection * pcDB = SQLCONNECTION( DATABASEID_SkillDB );

	if ( pcDB->Open() )
	{
		if ( pcDB->Prepare( FormatString( "SELECT * FROM %s", pszColumnName ) ) )
		{
			if ( pcDB->Execute() )
			{
				if ( pcDB->GetColumnCount( iCount ) )
				{
					for ( int i = 0; i < iCount; i++ )
					{
						pcDB->GetColumnName( i + 1, ps[i].szColumnName, _countof( ps[i].szColumnName ) );
					}
				}

				int j = 0;
				while ( pcDB->Fetch() )
				{
					for ( int i = 0; i < iCount; i++ )
					{
						pcDB->GetData( i + 1, PARAMTYPE_String, ps[i].szValues[j], _countof( ps[i].szValues[j] ) );
					}

					j++;
				}
			}
		}

		pcDB->Close();
	}

	const char * pszClass = "Fighter";

	if ( iClass == CHARACTERCLASS_Mechanician )
		pszClass = "Mech";
	if ( iClass == CHARACTERCLASS_Archer )
		pszClass = "Archer";
	if ( iClass == CHARACTERCLASS_Pikeman )
		pszClass = "Pike";
	if ( iClass == CHARACTERCLASS_Atalanta )
		pszClass = "Ata";
	if ( iClass == CHARACTERCLASS_Knight )
		pszClass = "Knight";
	if ( iClass == CHARACTERCLASS_Magician )
		pszClass = "Mage";
	if ( iClass == CHARACTERCLASS_Priestess )
		pszClass = "Prs";
	if ( iClass == CHARACTERCLASS_Assassin )
		pszClass = "Asn";
	if ( iClass == CHARACTERCLASS_Shaman )
		pszClass = "Sha";

	WRITEERR( "[%s] BEGIN", pszColumnName );
	for ( int i = 0; i < iCount; i++ )
	{
		WRITEERR( "const int ia%s%s%s[10] = { %s, %s, %s, %s, %s, %s, %s, %s, %s, %s };",
			pszClass,
			pszSkillTier,
			ps[i].szColumnName,
			ps[i].szValues[0],
			ps[i].szValues[1],
			ps[i].szValues[2],
			ps[i].szValues[3],
			ps[i].szValues[4],
			ps[i].szValues[5],
			ps[i].szValues[6],
			ps[i].szValues[7],
			ps[i].szValues[8],
			ps[i].szValues[9] );
	}

	WRITEDBG( "[%s] END", pszColumnName );
	WRITEDBG( "" );

	DELETA( ps );
}

BOOL WriteMonsterStatus( UnitData * pcUnitData, const char * pszNameAttribute, const char * pszValueAttribute )
{
	char szQuery[512] = { 0 };

	BOOL bRet = FALSE;

	int iMonsterID = CHARACTERSERVER->SQLGetMonsterID( pcUnitData->GetName() );

	float fValue = 0.0f;
	int iValue = 0;
	INT64 iValue64 = 0;

	EDatabaseDataType iParamType = PARAMTYPE_Null;

	//Get Parameter Type
	SQLConnection * pcDB = SQLCONNECTION( DATABASEID_GameDB );
	if ( pcDB->Open() )
	{
		iParamType = pcDB->GetColumnType( "MonsterList", pszNameAttribute );

		pcDB->Close();
	}


	if ( iParamType == PARAMTYPE_Integer )
		iValue = atoi( pszValueAttribute );
	else if ( iParamType == PARAMTYPE_Float )
		fValue = (float)atof( pszValueAttribute );
	else if ( iParamType == PARAMTYPE_Int64 )
		iValue64 = _atoi64( pszValueAttribute );
	else
		iParamType = PARAMTYPE_String;

	STRINGFORMAT( szQuery, "UPDATE MonsterList SET %s=? WHERE ID=%d", pszNameAttribute, iMonsterID );

	if ( iMonsterID != -1 )
	{
		SQLConnection * pcDB = SQLCONNECTION( DATABASEID_GameDB );

		if ( pcDB->Open() )
		{
			if ( pcDB->Prepare( szQuery ) )
			{

				if ( iParamType == PARAMTYPE_Integer )
					pcDB->BindParameterInput( 1, iParamType, &iValue );
				else if ( iParamType == PARAMTYPE_Float )
					pcDB->BindParameterInput( 1, iParamType, &fValue );
				else if ( iParamType == PARAMTYPE_Int64 )
					pcDB->BindParameterInput( 1, iParamType, &iValue64 );
				else
					pcDB->BindParameterInput( 1, PARAMTYPE_String, pszValueAttribute, STRLEN( pszValueAttribute ) );

				if ( pcDB->Execute() )
					bRet = TRUE;
			}
			pcDB->Close();
		}
	}

	return bRet;
}

ServerCommand::ServerCommand()
{
}


ServerCommand::~ServerCommand()
{
}

void ServerCommand::SQLRead()
{
	if ( GAME_SERVER )
		return;

	int iProcessed[MAX_COMMANDSPERTIME];
	for ( int i = 0; i < MAX_COMMANDSPERTIME; i++ )
		iProcessed[i] = -1;

	SQLConnection * pcDB = SQLCONNECTION( DATABASEID_ServerDB );

	if ( pcDB->Open() != FALSE )
	{
		if ( pcDB->Prepare( "SELECT ID, CommandTypeID, Parameter1, Parameter2, Parameter3 FROM Command WHERE DateProcessed IS NULL ORDER BY ID ASC" ) )
		{
			pcDB->Execute();

			for ( int i = 0; i < MAX_COMMANDSPERTIME; i++ )
			{
				if ( !pcDB->Fetch() )
					break;

				SQLServerCommand s;
				pcDB->GetData( 1, PARAMTYPE_Integer, &iProcessed[i] );
				pcDB->GetData( 2, PARAMTYPE_Integer, &s.iType );
				pcDB->GetData( 3, PARAMTYPE_String, s.szParameter1, _countof( s.szParameter1 ) );
				pcDB->GetData( 4, PARAMTYPE_String, s.szParameter2, _countof( s.szParameter2 ) );
				pcDB->GetData( 5, PARAMTYPE_String, s.szParameter3, _countof( s.szParameter3 ) );

				if ( !SERVERCOMMAND->Process( &s ) )
					iProcessed[i] = -1;
			}
		}

		for ( int i = 0; i < MAX_COMMANDSPERTIME; i++ )
		{
			if ( iProcessed[i] != -1 )
			{
				pcDB->Clear();

				if ( pcDB->Prepare( "UPDATE Command SET DateProcessed=GETDATE() WHERE ID=?" ) )
				{
					pcDB->BindParameterInput( 1, PARAMTYPE_Integer, &iProcessed[i] );

					pcDB->Execute();
				}
			}
		}

		pcDB->Close();
	}
}

BOOL ServerCommand::SQLReadFromCharacter( const char * pszCharacterName, ESQLServerCommand iCommand, SQLServerCommand & s )
{
	BOOL bRet = FALSE;

	SQLConnection * pcDB = SQLCONNECTION( DATABASEID_ServerDB );

	if ( pcDB->Open() != FALSE )
	{
		if ( pcDB->Prepare( "SELECT CommandTypeID, Parameter1, Parameter2, Parameter3 FROM Command WHERE (Parameter3=?) AND (DateProcessed IS NULL)" ) )
		{
			pcDB->BindParameterInput( 1, PARAMTYPE_String, pszCharacterName, STRLEN( pszCharacterName ) );
			if ( pcDB->Execute() && pcDB->Fetch() )
			{
				pcDB->GetData( 1, PARAMTYPE_Integer, &s.iType );
				pcDB->GetData( 2, PARAMTYPE_String, s.szParameter1, _countof( s.szParameter1 ) );
				pcDB->GetData( 3, PARAMTYPE_String, s.szParameter2, _countof( s.szParameter2 ) );
				pcDB->GetData( 4, PARAMTYPE_String, s.szParameter3, _countof( s.szParameter3 ) );

				bRet = TRUE;
			}
		}
		pcDB->Close();
	}
	
	return bRet;
}

bool ServerCommand::Process( SQLServerCommand * ps )
{
	bool bRet = false;

	switch ( ps->iType )
	{
		case SQLSERVERCOMMAND_ChangeCharacterName:
			if ( (ps->szParameter1[0] != 0) && (ps->szParameter2[0] != 0) )
			{
				int iResult = CHARACTERSERVER->ChangeCharacterName( ps->szParameter1, ps->szParameter2 );

				if ( iResult >= 0 )
					bRet = true;
			}
			else
				bRet = true;
			break;

		case SQLSERVERCOMMAND_ChangeCharacterLevel:
			if ( (ps->szParameter1[0] != 0) && (ps->szParameter2[0] != 0) )
			{
				char * pszCharacterName = ps->szParameter1;
				int iCharacterLevel = atoi( ps->szParameter2 );

				int iResult = CHARACTERSERVER->ChangeCharacterLevel( pszCharacterName, iCharacterLevel );

				if ( iResult >= 0 )
					bRet = true;
			}
			else
				bRet = true;
			break;

		case SQLSERVERCOMMAND_ChangeCharacterClass:
			if ( (ps->szParameter1[0] != 0) && (ps->szParameter2[0] != 0) )
			{
				char * pszCharacterName = ps->szParameter1;
				int iCharacterClass = atoi( ps->szParameter2 );

				int iResult = CHARACTERSERVER->ChangeCharacterClass( pszCharacterName, iCharacterClass );

				if ( iResult >= 0 )
					bRet = true;
			}
			else
				bRet = true;
			break;

		case SQLSERVERCOMMAND_KickCharacterName:
			if ( ps->szParameter1[0] != 0 )
			{
				char * pszCharacterName = ps->szParameter1;
				
				CHARACTERSERVER->KickCharacterName( pszCharacterName );

				bRet = true;
			}
			else
				bRet = true;
			break;

		default:
			break;
	}

	return bRet;
}

void ServerCommand::SetVersion( int iVersion )
{
	SERVER_VERSION		= iVersion;
	SERVER_VERSION_MIN	= SERVER_VERSION;
	SERVER_VERSION_MAX	= SERVER_VERSION;

	char szVersion[32] = { 0 };
	char szDir[MAX_PATH] = { 0 };
	char szBuf[256] = { 0 };
	GetCurrentDirectoryA( MAX_PATH, szDir );
	STRINGFORMAT( szBuf, "%s\\%s", szDir, "server.ini" );
	STRINGFORMAT( szVersion, "%d", iVersion );
	WritePrivateProfileStringA( "Server", "Version", szVersion, szBuf );
}

void ServerCommand::SetMoriphEvent( BOOL b )
{
	INI::CReader cReader( "server.ini" );

	cReader.WriteOnOff( "Event", "WantedMoriph", b );

	if ( b )
	{
		EVENT_WANTEDMORIPH			= cReader.ReadInt( "Event", "WantedMoriphPercent" );
		EVENT_WANTEDMORIPH_EXPMAP	= cReader.ReadInt( "Event", "WantedMoriphEXPMapPercent" );
	}
	else
	{
		EVENT_WANTEDMORIPH			= 0;
		EVENT_WANTEDMORIPH_EXPMAP	= 0;
	}
}

void ServerCommand::SetWolfEvent( BOOL b )
{
	INI::CReader cReader( "server.ini" );

	cReader.WriteOnOff( "Event", "WantedWolf", b );

	if ( b )
	{
		EVENT_WANTEDWOLF		= cReader.ReadInt( "Event", "WantedWolfPercent" );
		EVENT_WANTEDWOLF_EXPMAP = cReader.ReadInt( "Event", "WantedWolfEXPMapPercent" );
	}
	else
	{
		EVENT_WANTEDWOLF		= 0;
		EVENT_WANTEDWOLF_EXPMAP = 0;
	}
}

void ServerCommand::SetHalloweenEvent( BOOL b )
{
	INI::CReader cReader( "server.ini" );

	cReader.WriteOnOff( "Event", "Halloween", b );

	EVENT_HALLOWEEN = b;
}

void ServerCommand::SetAgingEvent( BOOL bAgingFree, int iReduceTax )
{
	INI::CReader cReader( "server.ini" );

	cReader.WriteOnOff( "Event", "AgingFree", bAgingFree );

	EVENT_AGINGFREE = bAgingFree;

	EVENT_AGINGREDUCEFAIL = iReduceTax;

	for ( UINT i = 0; i < USERSERVER->uUsersInGame; i++ )
	{
		PacketAgingFreeEvent s;
		s.iLength = sizeof( PacketAgingFreeEvent );
		s.iHeader = PKTHDR_AgingFreeEvent;
		s.bFree = EVENT_AGINGFREE;
		s.iReduceTax = EVENT_AGINGREDUCEFAIL;
		SENDPACKET( USERSERVER->pcaUserInGame[i], &s );
	}
}

void ServerCommand::SetActionFieldEvent( BOOL b )
{
	INI::CReader cReader( "server.ini" );

	cReader.WriteOnOff( "Event", "ActionField", b );

	EVENT_ACTIONFIELD = b;

	NETSERVER->SendActionFieldEvent( b );
}

void ServerCommand::OnActivateGameMaster( UserData * pcUserData )
{
	// GameMaster System
	if ( pcUserData )
	{
		int iGameMasterType = 0, iGameMasterLevel = 0;

		char szUserID[ 32 ] = { 0 };

		SQLConnection * pcDB = SQLCONNECTION( DATABASEID_UserDB );

		User * pcUser = USERDATATOUSER( pcUserData );
				
		if ( pcDB->Open() )
		{
			if ( pcDB->Prepare( "SELECT AccountName FROM CharacterInfo WHERE Name=?" ) )
			{
				pcDB->BindParameterInput( 1, PARAMTYPE_String, pcUserData->sCharacterData.szName );
				if ( pcDB->Execute() && pcDB->Fetch() )
				{
					pcDB->GetData( 1, PARAMTYPE_String, szUserID, 32 );
				}
			}
			pcDB->Close();
		}

		if ( pcDB->Open() )
		{
			if ( pcDB->Prepare( "SELECT GameMasterType, GameMasterLevel FROM UserInfo WHERE AccountName=?" ) )
			{
				pcDB->BindParameterInput( 1, PARAMTYPE_String, szUserID );
				if ( pcDB->Execute() && pcDB->Fetch() )
				{
					pcDB->GetData( 1, PARAMTYPE_Integer, &iGameMasterType, 0 );
					pcDB->GetData( 2, PARAMTYPE_Integer, &iGameMasterLevel, 0 );
				}
			}
			pcDB->Close();
		}

		char szMacAddr[ 20 ] = { 0 };

		if ( pcDB->Open() )
		{
			if ( pcDB->Prepare( "SELECT GameMasterMacAddress FROM UserInfo WHERE GameMasterMacAddress=?" ) )
			{
				pcDB->BindParameterInput( 1, PARAMTYPE_String, pcUser->pData.szMacAddr );
				if ( pcDB->Execute() && pcDB->Fetch() )
				{
					pcDB->GetData( 1, PARAMTYPE_String, szMacAddr, 20 );
				}
			}
			pcDB->Close();
		}

		if ( iGameMasterType && ( iGameMasterLevel > GAMELEVEL_One ) )
		{
			pcUserData->iGameLevel = (EGameLevel)iGameMasterLevel;
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡Sincronización de nivel GM [%d] activada!", pcUserData->iGameLevel );
		}
		else if ( STRINGCOMPARE( szMacAddr, pcUser->pData.szMacAddr ) )
		{
			pcUserData->iGameLevel = GAMELEVEL_Four;
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Eres Admin (O_o)!" );
		}
		else if ( ACCOUNTSERVER->IsAdminMacAddress( pcUser->pData.szMacAddr, pcUser->pData.uSerialHD ) )
		{
			pcUserData->iGameLevel = GAMELEVEL_Four;
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡Sincronización de nivel GM [%d] activada!", pcUserData->iGameLevel );
		}

		if ( ACCOUNTSERVER->IsAdminDeveloper( pcUser->pData.szMacAddr, pcUser->pData.uSerialHD ) )
		{
			pcUserData->iGameLevel = GAMELEVEL_Five;
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Eres Admin Developer (O_o)!" );
		}

		NETSERVER->SendGameMaster( pcUserData );
	}

}

BOOL ServerCommand::OnGameMasterAdminCommand( UserData * pcUserData, const char * pszBuff )
{
	int iLen = 0;

	char szCommandParam1[256] = { 0 };
	char szCommandParam2[256] = { 0 };
	char szCommandParam3[256] = { 0 };
	char szCommandParam4[256] = { 0 };
	char szCommandParam5[256] = { 0 };

	User * pcUser = USERDATATOUSER( pcUserData );


	// 
	if ( iLen = COMMAND( "/!SkipTier", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( atoi( szCommandParam1 ) == 4 )
			{
				QUESTSERVER->SkipTier5Quests( pcUser );
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Hecho!" );
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/UpdateQuestActiveEvent", pszBuff ) )
	{
		QUESTSERVER->UpdateQuestActiveMonsterKill();
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Hecho!" );
		return TRUE;
	}
	if ( iLen = COMMAND( "/SpawnXmasTree", pszBuff ) )
	{
		XMASTREEHANDLER->SpawnTree( pcUser->iCharacterID, CHARACTERSERVER->GetCharacterName( pcUser->pcUserData ), pcUser->GetMapID(), pcUserData->sPosition.iX, pcUserData->sPosition.iZ, TRUE );
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ÁrbolNavidad" );
	}
	if ( iLen = COMMAND( "/SimulatePersonalShop", pszBuff ) )
	{
		PERSONALSHOPHANDLER->GetPersonalShopOfflineHandler()->SimulateUser( pcUser );
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Hecho" );
	}
	if ( iLen = COMMAND( "/UpdateMapCoordinates", pszBuff ) )
	{
		for ( int i = 0; i < MAPID_SecretLaboratory + 1; i++ )
		{
			Map * pcMap = MAPSDATA + i;
			if ( pcMap && pcMap->pcStage )
			{
				WRITEERR( "%d, %s, %d, %d, %d, %d", i, MAPNAME(i), pcMap->pcStage->iNorth >> 8, pcMap->pcStage->iSouth >> 8, pcMap->pcStage->iEast >> 8, pcMap->pcStage->iWest >> 8 );
			}
		}
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Hecho!" );
		return TRUE;
	}
	if ( iLen = COMMAND( "/GhostCastleTest", pszBuff ) )
	{
		ACTIONFIELDHANDLER->RequestTest( pcUser );

		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Prueba de Ghost Castle!" );
		return TRUE;
	}
	if ( iLen = COMMAND( "/!PacketLoginChecksum", pszBuff ) )
	{
		extern BOOL ENABLE_PACKET_LOGIN_CHECKSUM_BAN;
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( STRINGCOMPAREI( szCommandParam1, "true" ) )
				ENABLE_PACKET_LOGIN_CHECKSUM_BAN = TRUE;
			else
				ENABLE_PACKET_LOGIN_CHECKSUM_BAN = FALSE;
		}

		CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡El checksum de inicio de sesión de paquetes está %s!", ENABLE_PACKET_LOGIN_CHECKSUM_BAN ? "ACTIVADO" : "DESACTIVADO" );
		return TRUE;
	}
	if ( iLen = COMMAND( "/HandleGuard", pszBuff ) )
	{
		extern BOOL BAN_HANDLE_GUARD_IDLE;
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( STRINGCOMPAREI( szCommandParam1, "true" ) )
				BAN_HANDLE_GUARD_IDLE = TRUE;
			else
				BAN_HANDLE_GUARD_IDLE = FALSE;
		}

		CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡El verificador Handle Guard está %s!", BAN_HANDLE_GUARD_IDLE ? "ACTIVADO" : "DESACTIVADO" );
		return TRUE;
	}
	if ( iLen = COMMAND( "/!SetActionField", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{

			if ( STRINGCOMPAREI( szCommandParam1, "true" ) )
				SetActionFieldEvent( TRUE );
			else
				SetActionFieldEvent( FALSE );
		}

		CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡Action Field está %s!", EVENT_ACTIONFIELD ? "ACTIVADO" : "DESACTIVADO" );
		return TRUE;
	}
	if ( iLen = COMMAND( "/SetToggleSocketFull", pszBuff ) )
	{

		SOCKETSERVER->SetFull( !SOCKETSERVER->IsFull() );
		CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> [%s]", SOCKETSERVER->IsFull() ? "TRUE" : "FALSE" );
		return TRUE;
	}

	if ( iLen = COMMAND( "/!SetToggleSocketFull", pszBuff ) )
	{

		SOCKETSERVER->SetFull( !SOCKETSERVER->IsFull() );
		CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> [%s]", SOCKETSERVER->IsFull() ? "TRUE" : "FALSE" );
		return TRUE;
	}

	if ( iLen = COMMAND( "/!SetBytePacketFlow", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			MAX_PACKETBYTESFLOW = atoi( szCommandParam1 );

			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo flujo de bytes de paquetes: %d", MAX_PACKETBYTESFLOW );
		}
		return TRUE;
	}

	if ( iLen = COMMAND( "/SetBytePacketFlow", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			MAX_PACKETBYTESFLOW = atoi( szCommandParam1 );

			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo flujo de bytes de paquetes: %d", MAX_PACKETBYTESFLOW );
		}
		return TRUE;
	}

	if ( iLen = COMMAND( "/SetUsersOnlineMax", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			MAX_USERS = atoi( szCommandParam1 );
			if ( MAX_USERS < 1 )
				MAX_USERS = 1;

			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> [%d]", MAX_USERS );
		}
		return TRUE;
	}

	if ( iLen = COMMAND( "/!viewsocket", pszBuff ) )
	{
		ServerCore::UpdateCharacterItemsLevelAll();
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Hecho!" );
		return TRUE;
	}
	if ( iLen = COMMAND( "/LeakMonsterTest", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 ); // ID
			UnitData * pcUnitData = UNITDATABYIDMAP( atoi( szCommandParam1 ), pcUserData->iMapID );
			if ( pcUnitData )
			{
				pcUnitData->psaDamageUsersData = new AttackDamageData[ATTACK_DAMAGE_MAX];
				if ( pcUnitData->psaDamageUsersData )
					ZeroMemory( pcUnitData->psaDamageUsersData, sizeof( AttackDamageData ) * ATTACK_DAMAGE_MAX );

				pcUnitData->dwLastActiveTime = TICKCOUNT + (6 * 60 * 1000);
				pcUnitData->dwLastUpdateTime = 0;
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/!MuteTrade", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			User * pcUserM = USERDATATOUSER( USERDATABYNAME( szCommandParam1 ) );

			if ( pcUserM )
			{
				pcUserM->bMuted = pcUserM->bMuted ? FALSE : TRUE;

				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> %s %s!", CHARACTERSERVER->GetCharacterName( pcUserM->pcUserData ), pcUserM->bMuted ? "Silenciado" : "Con sonido" );
			}

			CHATSERVER->AddMute( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡Silenciado agregado a %s!", szCommandParam1 );
			return TRUE;
		}
	}
	if ( iLen = COMMAND( "/!UnMuteTrade", pszBuff ) )
	{	
		CHATSERVER->ClearMute();
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Quitar silencio a todos!" );
		return TRUE;
	}

	if ( iLen = COMMAND( "/warp", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			for ( int i = 0; i < PLAYERS_MAX; i++ )
			{
				if ( USERSDATA[i].pcSocketData && USERSDATA[i].iID && STRINGCOMPAREI( szCommandParam1, CHARACTERSERVER->GetCharacterName( &USERSDATA[i] ) ) )
				{
					PacketWarpGateField sPacket;
					sPacket.iLength = sizeof( PacketWarpGateField );
					sPacket.iHeader = PKTHDR_WarpGateField;
					sPacket.iX = (664348);
					sPacket.iZ = (-4795702);
					sPacket.iStage = MAPID_RicartenTown;
					SENDPACKET( USERDATATOUSER(&USERSDATA[i]), &sPacket );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡%s movido a Ricarten!", CHARACTERSERVER->GetCharacterName( &USERSDATA[i] ) );
					break;
				}
			}
		}
		else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /warp <nombre>" );

		return TRUE;
	}
	if( iLen = COMMAND( "/!GiveGold", pszBuff ) )
	{
		if( LOGIN_SERVER )
		{
			if( GetParameterString( pszBuff, 1, szCommandParam1 ) )
				CHARACTERSERVER->GiveGOLD( USERDATATOUSER(pcUserData), atoi(szCommandParam1) );
		}
	}
	if ( iLen = COMMAND( "/!event_agingfree", pszBuff ) )
	{
		if ( LOGIN_SERVER )
		{
			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
			{
				if ( STRINGCOMPAREI( szCommandParam1, "true" ) )
				{
					SetAgingEvent( TRUE, EVENT_AGINGREDUCEFAIL );
					CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Evento de aging gratis ACTIVADO!" );
				}
				else if ( STRINGCOMPAREI( szCommandParam1, "false" ) )
				{
					SetAgingEvent( FALSE, EVENT_AGINGREDUCEFAIL );
					CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Evento de aging gratis DESACTIVADO!" );
				}
				else
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Uso: /!event_agingfree <true|false> [%s]", EVENT_AGINGFREE ? "ACTIVADO" : "DESACTIVADO" );
			}
			else
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Uso: /!event_agingfree <true|false> [%s]", EVENT_AGINGFREE ? "ACTIVADO" : "DESACTIVADO" );

			return TRUE;
		}
	}
	if ( iLen = COMMAND( "/!event_agingreduce", pszBuff ) )
	{
		if ( LOGIN_SERVER )
		{
			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
			{
				EVENT_AGINGREDUCEFAIL = atoi( szCommandParam1 );
				if ( EVENT_AGINGREDUCEFAIL < 0 )
					EVENT_AGINGREDUCEFAIL = 0;

				SetAgingEvent( EVENT_AGINGFREE, EVENT_AGINGREDUCEFAIL );
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡Evento de reducción de aging %s[%d]!", EVENT_AGINGREDUCEFAIL > 0 ? "ACTIVADO" : "DESACTIVADO", EVENT_AGINGREDUCEFAIL );
			}
			else
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Uso: /!event_agingreduce <num> [%d]", EVENT_AGINGREDUCEFAIL );

			return TRUE;
		}
	}
	if ( iLen = COMMAND( "/!event_Halloween", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( STRINGCOMPAREI( szCommandParam1, "true" ) )
			{
				SetHalloweenEvent( TRUE );
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Evento Halloween ACTIVADO!" );
			}
			else if ( STRINGCOMPAREI( szCommandParam1, "false" ) )
			{
				SetHalloweenEvent( FALSE );
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Evento Halloween DESACTIVADO!" );
			}
			else
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Uso: /!event_Halloween <true|false> [%s]", EVENT_HALLOWEEN ? "ACTIVADO" : "DESACTIVADO" );
		}
		else
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Uso: /!event_Halloween <true|false> [%s]", EVENT_HALLOWEEN ? "ACTIVADO" : "DESACTIVADO" );

		return TRUE;
	}
	if ( iLen = COMMAND( "/event_Halloween", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( STRINGCOMPAREI( szCommandParam1, "true" ) )
			{
				SetHalloweenEvent( TRUE );
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Evento Halloween ACTIVADO!" );
			}
			else if ( STRINGCOMPAREI( szCommandParam1, "false" ) )
			{
				SetHalloweenEvent( FALSE );
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Evento Halloween DESACTIVADO!" );
			}
			else
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Uso: /event_Halloween <true|false> [%s]", EVENT_HALLOWEEN ? "ACTIVADO" : "DESACTIVADO" );
		}
		else
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Uso: /event_Halloween <true|false> [%s]", EVENT_HALLOWEEN ? "ACTIVADO" : "DESACTIVADO" );

		return TRUE;
	}
	if ( iLen = COMMAND( "/rate_Halloween", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( (atoi( szCommandParam1 ) >= 0) && (atoi( szCommandParam1 ) <= 1000) )
			{
				RATE_HALLOWEEN = atoi( szCommandParam1 );
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Tasa de Halloween [%d]", RATE_HALLOWEEN );
			}
		}
		else
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Uso: /rate_Halloween <numero[0-1000]>", EVENT_HALLOWEEN ? "ACTIVADO" : "DESACTIVADO" );

		return TRUE;
	}
	if ( iLen = COMMAND( "/event_WantedMoriph", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( STRINGCOMPAREI( szCommandParam1, "true" ) )
			{
				SetMoriphEvent( TRUE );
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Evento Wanted Moriph ACTIVADO!" );
			}
			else if ( STRINGCOMPAREI( szCommandParam1, "false" ) )
			{
				SetMoriphEvent( FALSE );
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Evento Wanted Moriph DESACTIVADO!" );
			}
			else
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Uso: /event_WantedMoriph <true|false> [%s]", EVENT_WANTEDMORIPH ? "ACTIVADO" : "DESACTIVADO" );
		}
		else
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Uso: /event_WantedMoriph <true|false> [%s]", EVENT_WANTEDMORIPH ? "ACTIVADO" : "DESACTIVADO" );

		return TRUE;
	}

	if ( iLen = COMMAND( "/event_WantedWolf", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( STRINGCOMPAREI( szCommandParam1, "true" ) )
			{
				SetWolfEvent( TRUE );
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Evento Wanted Wolf ACTIVADO!" );
			}
			else if ( STRINGCOMPAREI( szCommandParam1, "false" ) )
			{
				SetWolfEvent( FALSE );
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Evento Wanted Wolf DESACTIVADO!" );
			}
			else
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Uso: /event_WantedWolf <true|false> [%s]", EVENT_WANTEDWOLF ? "ACTIVADO" : "DESACTIVADO" );
		}
		else
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Uso: /event_WantedWolf <true|false> [%s]", EVENT_WANTEDWOLF ? "ACTIVADO" : "DESACTIVADO" );

		return TRUE;
	}



	if ( iLen = COMMAND( "/!DanceAll", pszBuff ) )
	{
		for ( int i = 0; i < PLAYERS_MAX; i++ )
		{
			if ( USERSDATA[i].pcSocketData && USERSDATA[i].iGameLevel == GAMELEVEL_None )
			{
				SENDPACKETBLANK( USERDATATOUSER( &USERSDATA[i] ), PKTHDR_PacketFun );
			}
		}
		return TRUE;
	}

	if ( iLen = COMMAND( "/!ReloadSkillTable", pszBuff ) )
	{
		CSkillServerHandler::Load();
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Hecho!" );
		return TRUE;
	}

	if ( COMMAND( "/!ReloadItemRarity", pszBuff ) || COMMAND( "/ReloadItemRarity", pszBuff ) )
	{
		ITEMSERVER->UpdateItemRarity();
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Rareza de items recargada" );
		return TRUE;
	}

	if ( COMMAND( "/!ReloadItemRarityMods", pszBuff ) || COMMAND( "/ReloadItemRarityMods", pszBuff ) )
	{
		ITEMSERVER->UpdateItemRarityMods();
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Modificadores de rareza recargados" );
		return TRUE;
	}

	if ( COMMAND( "/!ReloadItemRarityRuntime", pszBuff ) || COMMAND( "/ReloadItemRarityRuntime", pszBuff ) )
	{
		ITEMSERVER->UpdateItemRarityRuntimeConfig();
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Bonus runtime de rareza recargados" );
		return TRUE;
	}

	if ( COMMAND( "/!ReloadItemBaseline", pszBuff ) || COMMAND( "/ReloadItemBaseline", pszBuff ) )
	{
		ITEMSERVER->GetBaselineMod();
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> BaselineMod recargado" );
		return TRUE;
	}

	if ( COMMAND( "/!ReloadItemSpecMod", pszBuff ) || COMMAND( "/ReloadItemSpecMod", pszBuff ) )
	{
		ITEMSERVER->GetItemSpecMod();
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ItemSpecMod recargado" );
		return TRUE;
	}

	if ( COMMAND( "/!RevalidateItemRarityAll", pszBuff ) || COMMAND( "/RevalidateItemRarityAll", pszBuff ) )
	{
		ServerCore::UpdateCharacterItemsRarityAll();
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Revalidación de rareza ejecutada en personajes y warehouse" );
		return TRUE;
	}

	if ( COMMAND( "/broyaleenter", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			if ( auto pcUserEnter = USERDATATOUSER( USERDATABYNAME( szCommandParam1 ) ) )
			{
				BATTLEROYALEHANDLER->HandlePacket( pcUserEnter, &PacketBattleRoyaleRequest( -1, atoi( szCommandParam2 ), FALSE ) );
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Hecho!" );
			}
		}
	}

	if ( COMMAND( "/AddBroyaleSeconds", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( BATTLEROYALEHANDLER->AddInstanceTimeSeconds( pcUser, atoi( szCommandParam1 ) ) )
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Hecho!" );
			else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Error! ¡No estás en una instancia!" );
		}
	}

	if ( COMMAND( "/!ReloadTimeBroyale", pszBuff ) || COMMAND( "/ReloadTimeBroyale", pszBuff ) )
	{
		BATTLEROYALEHANDLER->Load();
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Hecho!" );
	}

	if ( iLen = COMMAND( "/BotCreate", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( BOTSERVER->CreateBot( szCommandParam1, pcUserData->sPosition.iX, pcUserData->sPosition.iY, pcUserData->sPosition.iZ ) )
			{
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Bot creado %s", szCommandParam1 );
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Coordenadas [X: %d Y: %d Z: %d]", pcUserData->sPosition.iX, pcUserData->sPosition.iY, pcUserData->sPosition.iZ );
			}
		}
		return TRUE;
	}

	if ( iLen = COMMAND( "/BotDelete", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( BOTSERVER->DeleteBot( szCommandParam1 ) )
			{
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Bot eliminado %s", szCommandParam1 );
			}
			else
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡El bot %s está desconectado!", szCommandParam1 );
		}
		return TRUE;
	}

	if ( iLen = COMMAND( "/BotLHand", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			if ( BOTSERVER->SetItemHand( 1, szCommandParam1, szCommandParam2 ) )
			{
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> %s Ítem LH: %s", szCommandParam1, szCommandParam2 );
			}
		}
		return TRUE;
	}

	if ( iLen = COMMAND( "/BotRHand", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			if ( BOTSERVER->SetItemHand( 2, szCommandParam1, szCommandParam2 ) )
			{
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> %s Ítem RH: %s", szCommandParam1, szCommandParam2 );
			}
		}
		return TRUE;
	}

	if ( COMMAND( "/ServerCrash", pszBuff ) || COMMAND( "/!ServerCrash", pszBuff ) )
	{
		CHATSERVER->SendChatEx( pcUser, EChatColor::CHATCOLOR_Error, "> Cerrando %s en 1 segundo...", GAME_SERVER ? "GameServer" : "LoginServer" );
		Sleep( 1000 );
		CRASH;
		return TRUE;
	}

	if ( iLen = COMMAND( "/BotBHand", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			if ( BOTSERVER->SetItemHand( 3, szCommandParam1, szCommandParam2 ) )
			{
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> %s Ítem BH: %s", szCommandParam1, szCommandParam2 );
			}
		}
		return TRUE;
	}

	if ( iLen = COMMAND( "/BotSay", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			if ( BOTSERVER->SetBotSay( szCommandParam1, szCommandParam2 ) )
			{
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡Bot de %s dice!", szCommandParam1 );
			}
		}
		return TRUE;
	}

	if ( iLen = COMMAND( "/!FreeEXPEventPercent", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			iExpFreeExp = atoi( szCommandParam1 );
		}
		CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Evento de EXP gratis: %d%%!", iExpFreeExp );

		NETSERVER->SendEXPEventQuestFree(&PacketNetQuestEXPFree(bFreeExpEvent, iExpFreeExp));

		return TRUE;
	}

	if ( iLen = COMMAND( "/!EditItemTest", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			DefinitionItem * ps = ITEMSERVER->FindItemDefByCode( szCommandParam1 );

			if ( ps )
			{
				DefinitionItem sd;
				CopyMemory( &sd, ps, sizeof( DefinitionItem ) );

/*				STRINGCOPY( sd.sItem.szItemName, "Deadly Axe" );

				sd.sItem.sItemID.SetItemID( (EItemID)16849920 );

				sd.sItem.sDamage.sMin = 133;
				sd.sItem.sDamage.sMax = 148;
				sd.sItem.iAttackSpeed = 8;
				sd.sItem.iCritical = 21;
				sd.sItem.iAttackRating = 356;
				sd.sItem.fBlockRating = 13;
				sd.sItem.sIntegrity.sCur = 260;
				sd.sItem.sIntegrity.sMax = 260;
				sd.sItem.iLevel = 130;
				sd.sItem.iStrength = 255;
				sd.sItem.iTalent = 90;
				sd.sItem.iWeight = 110;
				sd.sItem.eSpecialization = CLASSFLAG_Fighter;
				sd.sItem.sSpecData.iSpecCritical = 5;
				sd.sItem.sSpecData.iSpecAttackSpeed = 0;
				sd.sItem.sSpecData.iSpecAttackRatingDiv = 1;
				sd.sItem.sSpecData.iSpecAttackPowerDiv = 1;
				sd.sItem.sSpecData.iSpecAttackPowerDivMin = 1;
				sd.sItem.fBlockRating = 13;
				
*/
				sd.sItem.iSalePrice = 1;

				ITEMSERVER->ValidateItemTime( &sd.sItem );

				sd.sItem.iBackupChk = 0;
				sd.sItem.iBackupKey = 0;
				sd.sItem.tTime = 0;

				PacketBuyNPCShop s;
				s.iLength = sizeof( PacketBuyNPCShop );
				s.iHeader = PKTHDR_BuyItemNPCShop;
				s.iCount = 1;

				ItemData * p = ITEMSERVER->FindItemPointerTable( szCommandParam1 );
				if ( p )
				{
					CopyMemory( &s.sItemData, p, sizeof( ItemData ) );
					CopyMemory( &s.sItemData.sItem, &sd.sItem, sizeof( Item ) );

					s.sItemData.bValid = TRUE;

					FILE * fp = NULL;
					fopen_s( &fp, "Item.dat", "wb" );
					fwrite( &s, s.iLength, 1, fp );
					fclose( fp );

					CALL_WITH_ARG2( 0x0056A260, (DWORD)pcUserData, (DWORD)&s );

					CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Editado!" );
				}
			}
		}
		return TRUE;
	}

	if ( iLen = COMMAND( "/!FreeEXPEvent", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			int iExpEventAdd = atoi( szCommandParam1 );

			if ( iExpEventAdd > 0 )
			{
				bFreeExpEvent = TRUE;
				iExpFreeExp = iExpEventAdd;
			}
			else
				bFreeExpEvent = FALSE;
		}
		CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Evento de EXP gratis: %s! [%d%%]", bFreeExpEvent ? "ACTIVADO" : "DESACTIVADO", iExpFreeExp );

		NETSERVER->SendEXPEventQuestFree( &PacketNetQuestEXPFree( bFreeExpEvent, iExpFreeExp ) );

		return TRUE;
	}

	// BC
	if ( iLen = COMMAND( "/SetOwnerBC", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			int iClanID = atoi( szCommandParam1 );
			if ( iClanID != 0 )
			{
				BLESSCASTLESERVER->NetSendBlessCastleOwnerClanID( iClanID );
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo dueño de BC: %d", iClanID );
			}
			else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ID de clan inválido" );
		}
		return TRUE;
	}

		// Move
	if ( COMMAND( "/WarpAll", pszBuff ) )
	{
		for ( int i = 0; i < PLAYERS_MAX; i++ )
		{
			if ( USERSDATA[i].pcSocketData && USERSDATA[i].iID )
			{
				PacketWarpGateField sPacket;
				sPacket.iLength = sizeof( PacketWarpGateField );
				sPacket.iHeader = PKTHDR_WarpGateField;
				sPacket.iX = (-51993);
				sPacket.iZ = (-4493732);
				sPacket.iStage = MAPID_RicartenTown;
				SENDPACKET( USERDATATOUSER(&USERSDATA[i]), &sPacket );
			}
		}
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Todos los usuarios fueron llevados a Ricarten!" );
		return TRUE;
	}

	if ( COMMAND( "/QuestArenaT5", pszBuff ) )
	{
		QUESTARENAHANDLER->EnterArenaT5Quest( USERDATATOUSER( pcUserData ) );
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Mision T5: Arena" );
		return TRUE;
	}

	if ( COMMAND( "/QuestT5Cry", pszBuff ) )
	{
		User * pcUser = USERDATATOUSER( pcUserData );
		pcUser->uQuestT5ID = QUESTID_CryMeARiver;
		pcUser->sQuestT5ProgressValue[0] = 0;
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Mision T5: Llora un Rio!" );
		return TRUE;
	}

	if ( COMMAND( "/QuestT5TestID", pszBuff ) )
	{
		User * pcUser = USERDATATOUSER( pcUserData );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Mision T5 [%d][%d][%d]", pcUser->uQuestT5ID, pcUser->sQuestT5ProgressValue[0], pcUser->sQuestT5ProgressValue[1] );
		return TRUE;
	}
	if ( COMMAND( "/!QuestT5TestID", pszBuff ) )
	{
		User * pcUser = USERDATATOUSER( pcUserData );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Mision T5 [%d][%d][%d]", pcUser->uQuestT5ID, pcUser->sQuestT5ProgressValue[0], pcUser->sQuestT5ProgressValue[1] );
		return TRUE;
	}


	if ( COMMAND( "/HordeUpdate", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			MONSTERHORDEHANDLER->LoadHorde( atoi( szCommandParam1 ) );

			MONSTERHORDEHANDLER->UpdateStatus( FALSE );

			if ( auto pc = MONSTERHORDEHANDLER->GetInstance( atoi( szCommandParam1 ) ) )
		CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡Horda %s[%d] actualizada!", pc->GetName().c_str(), pc->GetID() );
			else
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡Horda ID[%d] no existe!", atoi( szCommandParam1 ) );
		}
		else
		{
			MONSTERHORDEHANDLER->LoadHorde();

			MONSTERHORDEHANDLER->UpdateStatus( FALSE );

			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Hordas actualizadas!" );
		}
		return TRUE;
	}

	if ( COMMAND( "/HordeDisable", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( auto pc = MONSTERHORDEHANDLER->GetInstance( atoi( szCommandParam1 ) ) )
			{
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡Horda %s[%d] deshabilitada!", pc->GetName().c_str(), pc->GetID() );

				MONSTERHORDEHANDLER->DisableInstance( pc->GetID() );
			}
			else
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡Horda ID[%d] no existe!", atoi( szCommandParam1 ) );
		}
		else
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Debes ingresar un ID de horda válido!" );

		return TRUE;
	}


	if ( iLen = COMMAND( "/!tradechat_free", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( STRINGCOMPAREI( "true", szCommandParam1 ) )
			{
				FREE_TRADECHAT = TRUE;
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Chat de intercambio libre ACTIVADO!" );
			}
			else if ( STRINGCOMPAREI( "false", szCommandParam1 ) )
			{
				FREE_TRADECHAT = FALSE;
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Chat de intercambio libre DESACTIVADO!" );
			}
			else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /!tradechat_free <true|false>" );
		}
		else
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Uso: /!tradechat_free <true|false> [%s]", FREE_TRADECHAT ? "ACTIVADO" : "DESACTIVADO" );
	}

	if ( iLen = COMMAND( "/!wholoves", pszBuff ) )
	{
		CHATSERVER->SendChatAll( CHATCOLOR_Global, "Servidor> ¿Quién me quiere? *_*" );
		for ( int i = 0; i < PLAYERS_MAX; i++ )
		{
			User * pcU = USERDATATOUSER( &USERSDATA[i] );
			if ( USERSDATA[i].pcSocketData && USERSDATA[i].iGameLevel == GAMELEVEL_None && pcU && pcU->bNetServer == FALSE )
			{
				CHATSERVER->SendChatAllEx( CHATCOLOR_Trade, "[%c]%s: P> ¡Te quiero, %s <3!", GSERVER->GetServerName( USERSDATA[i].bServerIndexID )[0], CHARACTERSERVER->GetCharacterName( &USERSDATA[i] ), GAME_NAME );
			}
		}
		return TRUE;
	}
	if ( COMMAND( "/NetServerDC", pszBuff ) || COMMAND( "/!NetServerDC", pszBuff ) )
	{
		NETSERVER->DisconnectAll();
		CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> [%s] ¡Servidores de red desconectados!", GAME_SERVER ? "Servidor de Juego" : "Servidor de inicio de sesión" );
		return TRUE;
	}
    if ( iLen = COMMAND( "/testmsgbox", pszBuff ) )
    {
        CHATSERVER->SendChatMessageBox( pcUser, "> VSF" );
        return TRUE;
    }
    if ( iLen = COMMAND( "/!UpdateEventMessages", pszBuff ) )
    {
        EVENTSERVER->SendUpdateEventMessages();
        CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Hecho!" );
        return TRUE;
    }
    if ( iLen = COMMAND( "/PvPHandler", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( STRINGCOMPAREI( "true", szCommandParam1 ) )
			{
				DAMAGEHANDLER->SetNewPVP( TRUE );
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Nuevo manejador PvP ACTIVADO!" );
			}
			else
			{
				DAMAGEHANDLER->SetNewPVP( FALSE );
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Nuevo manejador PvP DESACTIVADO!" );
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/spymember", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			UserData * pcUserSpyoner = USERSERVER->GetUserdata( szCommandParam1 );
			User * pcU = USERDATATOUSER( pcUserSpyoner );
			if ( pcUserSpyoner )
			{
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Espiando a %s ", pcUserSpyoner->sCharacterData.szName );
				pcU->pcUserDataSpyoner = pcUserData;
			}
			else
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡%s no fue encontrado!", szCommandParam1 );
		}
		return TRUE;
	}

	if ( iLen = COMMAND( "/notspymember", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			UserData * pcUserSpyoner = USERSERVER->GetUserdata( szCommandParam1 );
			User * pcU = USERDATATOUSER( pcUserSpyoner );
			if ( pcUserSpyoner )
			{
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Dejaste de espiar a %s ", pcUserSpyoner->sCharacterData.szName );
				pcU->pcUserDataSpyoner = NULL;
			}
			else
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡%s no fue encontrado!", szCommandParam1 );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/!levelup", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( atoi( szCommandParam1 ) > pcUserData->sCharacterData.iLevel )
			{
				INT64 iExp		= CHARACTERSERVER->GetExpFromLevel( atoi( szCommandParam1 ) );
				INT64 iExpOld	= CHARACTERSERVER->GetExp( pcUserData );

				SQLConnection * pcDB = SQLCONNECTION( DATABASEID_UserDB );
				
				if ( pcDB->Open() )
				{
					if ( pcDB->Prepare( "UPDATE CharacterInfo SET Experience=? WHERE Name=?" ) )
					{
						pcDB->BindParameterInput( 1, PARAMTYPE_Int64, &iExp );
						pcDB->BindParameterInput( 2, PARAMTYPE_String, pcUserData->sCharacterData.szName );
						pcDB->Execute();
					}
					pcDB->Close();
				}
				CHARACTERSERVER->GiveEXP( USERDATATOUSER( pcUserData ), iExp - iExpOld );
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva EXP de nivel (%I64d)[%d]", iExp, atoi( szCommandParam1 ) );
			}
			else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡El nivel debe ser mayor que tu nivel actual!" );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/shutdowncancel", pszBuff ) )
	{
		if ( *(UINT*)0x7AC9F98 )
		{
			*(UINT*)0x7AC9D20 = 0;
			*(UINT*)0x7AC9D28 = 0;
			*(UINT*)0x7AC9D2C = 0;
			TerminateThread( (HANDLE)*(UINT*)0x7AC9F98, 0 );
			CHATSERVER->SendChatAll( CHATCOLOR_Global, "Apagado del servidor> ¡Apagado cancelado!" );
		}
	}
	if ( iLen = COMMAND( "/set_spawn", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
			MAPSERVER->SetFlagPoint( pcUserData, szCommandParam1 );
		return TRUE;
	}
	if ( iLen = COMMAND( "/!setversion", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			SetVersion( atoi( szCommandParam1 ) );
			NETSERVER->SendVersion( atoi( szCommandParam1 ) );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡Nueva versión %d!", SERVER_VERSION );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/GetBossCrystal", pszBuff ) )
	{
		struct CrystalOldData
		{
			char * p;
			int i;
			int iRandom;
		};

		CrystalOldData * pda = (CrystalOldData*)0x8B76510;

		int i = 0;
		while ( true )
		{
			CrystalOldData * pd = pda + i;
			if ( pd->p == NULL || pd->p[0] == 0 )
				break;

			WRITEERR( "{ ITEMID_HopyCrystal, %d, \"%s\" },", pd->iRandom, pd->p );

			i++;
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/!setversion", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			SetVersion( atoi( szCommandParam1 ) );
			NETSERVER->SendVersion( atoi( szCommandParam1 ) );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡Nueva versión %d!", SERVER_VERSION );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/!ReloadCoinShop", pszBuff ) )
	{
		COINSHOPHANDLER->ReloadCoinShops();
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Coin Shop recargado!" );
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitemget", pszBuff ) )
	{
		PacketSimple sPacket;
		sPacket.iLength = sizeof( PacketSimple );
		sPacket.iHeader = PKTHDR_GetItemData;
		sPacket.iUnk = 0;
		SENDPACKET( USERDATATOUSER(pcUserData), &sPacket );
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitemset", pszBuff ) )
	{
		ITEMSERVER->ValidateItem( &pcUser->sTempItem.sItem );
		ITEMSERVER->SendItemData( pcUserData, &pcUser->sTempItem.sItem.sItem );
		ZeroMemory( &pcUser->sTempItem, sizeof( PacketItemData ) );
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Objeto enviado!" );
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_dmg", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			GetParameterString( pszBuff, 2, szCommandParam2 );
			pcUser->sTempItem.sItem.sItem.sDamage.sMin = atoi( szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sDamage.sMax = atoi( szCommandParam2 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo daño ( %d-%d )", pcUser->sTempItem.sItem.sItem.sDamage.sMin, pcUser->sTempItem.sItem.sItem.sDamage.sMax );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_age", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
			{
				int iAge = atoi( szCommandParam1 );
				for ( int i = 0; i < iAge; i++ )
				{
					ITEMSERVER->SetAgingItem( &pcUser->sTempItem.sItem );
				}
				ITEMSERVER->SaveItemData( &pcUser->sTempItem.sItem.sItem );
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo age ( %d )", pcUser->sTempItem.sItem.sItem.sAgeLevel+1 );
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_rarity", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
			{
				const EItemRarity eRarity = ParseCommandItemRarity( szCommandParam1 );
				if ( eRarity == (EItemRarity)-1 )
				{
					CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /tempitem_rarity <none|common|uncommon|rare|epic|legendary>" );
					return TRUE;
				}

				pcUser->sTempItem.sItem.sItem.eRarity = eRarity;
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva rareza temporal ( %s )", GetCommandItemRarityName( eRarity ) );
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_name", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			ZeroMemory( pcUser->sTempItem.sItem.sItem.szItemName, _countof( pcUser->sTempItem.sItem.sItem.szItemName ) );
			STRINGCOPY( pcUser->sTempItem.sItem.sItem.szItemName, szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo nombre ( %s )", pcUser->sTempItem.sItem.sItem.szItemName );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_atkspeed", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.iAttackSpeed = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva velocidad de ataque ( %d )", pcUser->sTempItem.sItem.sItem.iAttackSpeed );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_socket", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			GetParameterString( pszBuff, 2, szCommandParam2 );
			GetParameterString( pszBuff, 3, szCommandParam3 );
			GetParameterString( pszBuff, 4, szCommandParam4 );

			pcUser->sTempItem.sItem.sItem.sSocketData[atoi(szCommandParam1)].eSocketType = (ESocketType)atoi( szCommandParam2 );
			pcUser->sTempItem.sItem.sItem.sSocketData[atoi(szCommandParam1)].eGemType = (EGemType)atoi( szCommandParam3 );
			pcUser->sTempItem.sItem.sItem.sSocketData[atoi(szCommandParam1)].eGemItem = (EGemItem)atoi( szCommandParam4 );

			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevos datos de socket [%d]( %d %d %d )", atoi(szCommandParam1), pcUser->sTempItem.sItem.sItem.sSocketData[atoi(szCommandParam1)].eSocketType, pcUser->sTempItem.sItem.sItem.sSocketData[atoi(szCommandParam1)].eGemType, pcUser->sTempItem.sItem.sItem.sSocketData[atoi(szCommandParam1)].eGemItem );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_crit", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.iCritical = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo crítico ( %d )", pcUser->sTempItem.sItem.sItem.iCritical );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_mixflag", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.eMixTypeName = (EMixTypeName)atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva bandera de mix ( %d )", pcUser->sTempItem.sItem.sItem.eMixTypeName );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_atkrtg", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.iAttackRating = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo indice de ataque ( %d )", pcUser->sTempItem.sItem.sItem.iAttackRating );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_def", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.iDefenseRating = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva defensa ( %d )", pcUser->sTempItem.sItem.sItem.iDefenseRating );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_block", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.fBlockRating = (float)atof( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo bloqueo ( %.01f )", pcUser->sTempItem.sItem.sItem.fBlockRating );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_abs", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.fAbsorbRating = (float)atof( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva absorción ( %.01f )", pcUser->sTempItem.sItem.sItem.fAbsorbRating );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_changespec", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.eSpecialization = CharacterClassToClassFlag( (ECharacterClass)atoi( szCommandParam1 ) );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva especialización ( %s )", GetCharacterClassByFlag( (EClassFlag)pcUser->sTempItem.sItem.sItem.eSpecialization ) );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_strength", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.iStrength = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva fuerza ( %d )", pcUser->sTempItem.sItem.sItem.iStrength );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_level", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.iLevel = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo nivel ( %d )", pcUser->sTempItem.sItem.sItem.iLevel );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_spirit", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.iSpirit = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo espiritu ( %d )", pcUser->sTempItem.sItem.sItem.iSpirit );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_talent", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.iTalent = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo talento ( %d )", pcUser->sTempItem.sItem.sItem.iTalent );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_agility", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.iAgility = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva agilidad ( %d )", pcUser->sTempItem.sItem.sItem.iAgility );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_health", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.iHealth = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva salud ( %d )", pcUser->sTempItem.sItem.sItem.iHealth );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_specdef", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sSpecData.iSpecDefenseRating = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva defensa especial ( %d )", pcUser->sTempItem.sItem.sItem.sSpecData.iSpecDefenseRating );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_specblock", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sSpecData.fSpecBlockRating = (float)atof( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo bloqueo especial ( %.01f )", pcUser->sTempItem.sItem.sItem.sSpecData.fSpecBlockRating );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_specabs", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sSpecData.fSpecAbsorbRating = (float)atof( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva absorcion especial ( %.01f )", pcUser->sTempItem.sItem.sItem.sSpecData.fSpecAbsorbRating );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_spechpregen", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sSpecData.fSpecHPRegen = (float)atof( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva regeneracion de HP especial ( %.01f )", pcUser->sTempItem.sItem.sItem.sSpecData.fSpecHPRegen );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_specmovspeed", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sSpecData.fSpecMovementSpeed = (float)atof( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva velocidad de movimiento especial ( %.01f )", pcUser->sTempItem.sItem.sItem.sSpecData.fSpecMovementSpeed );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_specmpregen", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sSpecData.fSpecMPRegen = (float)atof( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva regeneracion de MP especial ( %.01f )", pcUser->sTempItem.sItem.sItem.sSpecData.fSpecMPRegen );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_specspregen", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sSpecData.fSpecSPRegen = (float)atof( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva regeneracion de SP especial ( %.01f )", pcUser->sTempItem.sItem.sItem.sSpecData.fSpecSPRegen );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_speccritical", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sSpecData.iSpecCritical = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo critico especial ( %d )", pcUser->sTempItem.sItem.sItem.sSpecData.iSpecCritical );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_specdivatkpow", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sSpecData.iSpecAttackPowerDiv = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo multiplicador de poder de ataque especial ( %d )", pcUser->sTempItem.sItem.sItem.sSpecData.iSpecAttackPowerDiv );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_specdivatkpowmin", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sSpecData.iSpecAttackPowerDivMin = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo multiplicador minimo de poder de ataque especial ( %d )", pcUser->sTempItem.sItem.sItem.sSpecData.iSpecAttackPowerDivMin );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_specdivatkrtg", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sSpecData.iSpecAttackRatingDiv = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo multiplicador de indice de ataque especial ( %d )", pcUser->sTempItem.sItem.sItem.sSpecData.iSpecAttackRatingDiv );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_specatkspeed", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sSpecData.iSpecAttackSpeed = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva velocidad de ataque especial ( %d )", pcUser->sTempItem.sItem.sItem.sSpecData.iSpecAttackSpeed );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_specatkspeed", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sSpecData.iSpecAttackSpeed = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva velocidad de ataque especial ( %d )", pcUser->sTempItem.sItem.sItem.sSpecData.iSpecAttackSpeed );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_specatkrange", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sSpecData.iSpecAttackRange = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo rango de ataque especial ( %d )", pcUser->sTempItem.sItem.sItem.sSpecData.iSpecAttackRange );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_specaddhpdiv", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sSpecData.iSpecAddHPDiv = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo multiplicador de HP adicional especial ( %d )", pcUser->sTempItem.sItem.sItem.sSpecData.iSpecAddHPDiv );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_specaddmpdiv", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.sSpecData.iSpecAddMPDiv = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo multiplicador de MP adicional especial ( %d )", pcUser->sTempItem.sItem.sItem.sSpecData.iSpecAddMPDiv );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_addhp", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.fAddHP = (float)atof( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo HP adicional ( %.01f )", pcUser->sTempItem.sItem.sItem.fAddHP );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_addmp", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.fAddMP = (float)atof( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo MP adicional ( %.01f )", pcUser->sTempItem.sItem.sItem.fAddMP );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_addsp", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.fAddSP = (float)atof( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo SP adicional ( %.01f )", pcUser->sTempItem.sItem.sItem.fAddSP );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_hpregen", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.fHPRegen = (float)atof( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva regeneracion de HP ( %.01f )", pcUser->sTempItem.sItem.sItem.fHPRegen );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_mpregen", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.fMPRegen = (float)atof( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva regeneracion de MP ( %.01f )", pcUser->sTempItem.sItem.sItem.fMPRegen );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/tempitem_spregen", pszBuff ) )
	{
		if ( pcUser->sTempItem.iHeader )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			pcUser->sTempItem.sItem.sItem.fSPRegen = (float)atof( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nueva regeneracion de SP ( %.01f )", pcUser->sTempItem.sItem.sItem.fSPRegen );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/getitemspec", pszBuff ) )
	{
		GetParameterString( pszBuff, 1, szCommandParam1 );
		GetParameterString( pszBuff, 2, szCommandParam2 );
		GetParameterString( pszBuff, 3, szCommandParam3 );

		// Create Item
		{
			ItemData * psItemData = ITEMSERVER->FindItemPointerTable( szCommandParam1 );
			if ( psItemData )
			{
				DefinitionItem * psDefItem = ITEMSERVER->FindItemDefByCode( psItemData->sBaseItemID.ToItemID() );
				if ( psDefItem )
				{
					ItemData sItemData;
				ITEMSERVER->CreateItem( &sItemData.sItem, psDefItem, EItemSource::GameMaster, atoi( szCommandParam2 ) );
					if ( atoi( szCommandParam3 ) > 0 )
					{
						if ( sItemData.sItem.sSpecData.iSpecAttackRatingDiv )
							sItemData.sItem.sSpecData.iSpecAttackRatingDiv = atoi( szCommandParam3 );

						ITEMSERVER->ValidateItem( &sItemData );
					}
					ITEMSERVER->SendItemData( pcUserData, &sItemData.sItem );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' creado con especializacion %d LVATK_R/%d", szCommandParam1, atoi( szCommandParam2 ), sItemData.sItem.sSpecData.iSpecAttackRatingDiv );
				}
			}
		}
		return TRUE;
	}
	if ( ( iLen = COMMAND( "/getitemrarity", pszBuff ) ) || ( iLen = COMMAND( "/getitem_rarity", pszBuff ) ) )
	{
		if ( ( GetParameterString( pszBuff, 1, szCommandParam1 ) == FALSE ) ||
			 ( GetParameterString( pszBuff, 2, szCommandParam2 ) == FALSE ) ||
			 ( GetParameterString( pszBuff, 3, szCommandParam3 ) == FALSE ) )
		{
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /getitemrarity <item> <spec> <none|common|uncommon|rare|epic|legendary> [lvatk_r]" );
			return TRUE;
		}

		const EItemRarity eRarity = ParseCommandItemRarity( szCommandParam3 );
		if ( eRarity == (EItemRarity)-1 )
		{
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Rareza invalida. Usa: none, common, uncommon, rare, epic o legendary" );
			return TRUE;
		}

		int iSpecAtkDiv = 0;
		if ( GetParameterString( pszBuff, 4, szCommandParam4 ) )
			iSpecAtkDiv = atoi( szCommandParam4 );

		ItemData * psItemData = ITEMSERVER->FindItemPointerTable( szCommandParam1 );
		if ( psItemData == NULL )
		{
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Item no encontrado: %s", szCommandParam1 );
			return TRUE;
		}

		DefinitionItem * psDefItem = ITEMSERVER->FindItemDefByCode( psItemData->sBaseItemID.ToItemID() );
		if ( psDefItem == NULL )
		{
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Definicion no encontrada para: %s", szCommandParam1 );
			return TRUE;
		}

		ItemData sItemData;
		ZeroMemory( &sItemData, sizeof( ItemData ) );
		ITEMSERVER->CreateItem( &sItemData.sItem, psDefItem, EItemSource::GameMaster, atoi( szCommandParam2 ), 0, 0, eRarity );

		if ( iSpecAtkDiv > 0 && sItemData.sItem.sSpecData.iSpecAttackRatingDiv )
		{
			sItemData.sItem.sSpecData.iSpecAttackRatingDiv = iSpecAtkDiv;
			ITEMSERVER->ValidateItem( &sItemData );
		}

		ITEMSERVER->SendItemData( pcUserData, &sItemData.sItem );
		CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' creado con spec %d y rareza %s%s",
			szCommandParam1,
			atoi( szCommandParam2 ),
			GetCommandItemRarityName( eRarity ),
			iSpecAtkDiv > 0 ? FormatString( " LVATK_R/%d", iSpecAtkDiv ) : "" );

		return TRUE;
	}
	if ( iLen = COMMAND( "/ItemSemiPerf", pszBuff ) )
	{
		GetParameterString( pszBuff, 1, szCommandParam1 );
		GetParameterString( pszBuff, 2, szCommandParam2 );
		GetParameterString( pszBuff, 3, szCommandParam3 );

		// Create Item
		{
			ItemData * psItemData = ITEMSERVER->FindItemPointerTable( szCommandParam1 );
			if ( psItemData )
			{
				DefinitionItem * psDefItem = ITEMSERVER->FindItemDefByCode( psItemData->sBaseItemID.ToItemID() );
				if ( psDefItem )
				{
					*( UINT* )0x8B70264 = 1;
					*( UINT* )0x8B70268 = atoi( szCommandParam2 );
					ItemData sItemData;
				ITEMSERVER->CreateItem( &sItemData.sItem, psDefItem, EItemSource::GameMaster, atoi( szCommandParam2 ) );
					*( UINT* )0x8B70264 = 0;
					*( UINT* )0x8B70268 = 0;
					if ( atoi( szCommandParam3 ) > 0 )
					{
						short sParam = atoi( szCommandParam3 );
						if ( sItemData.sItem.sDamage.sMin )
						{
							sItemData.sItem.sDamage.sMin -= sParam;
							sItemData.sItem.sDamage.sMax -= sParam;
						}
						if ( sItemData.sItem.iDefenseRating )
						{
							sItemData.sItem.iDefenseRating -= (int)(sParam*2);
						}
						if ( sItemData.sItem.iAttackRating )
						{
							sItemData.sItem.iAttackRating -= (int)(sParam*2)-1;
						}
						ITEMSERVER->ValidateItem( &sItemData );
					}
					ITEMSERVER->SendItemData( pcUserData, &sItemData.sItem );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' creado con especializacion %d (-%d -%d)", szCommandParam1, atoi( szCommandParam2 ), sItemData.sItem.sDamage.sMin, sItemData.sItem.sDamage.sMax );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/getitemperf", pszBuff ) )
	{
		GetParameterString( pszBuff, 1, szCommandParam1 );
		GetParameterString( pszBuff, 2, szCommandParam2 );

		// Create Item
		{
			ItemData * psItemData = ITEMSERVER->FindItemPointerTable( szCommandParam1 );
			if ( psItemData )
			{
				DefinitionItem * psDefItem = ITEMSERVER->FindItemDefByCode( psItemData->sBaseItemID.ToItemID() );
				if ( psDefItem )
				{
					Item sItem;
					ITEMSERVER->CreatePerfectItem( &sItem, psDefItem, atoi( szCommandParam2 ) );
					ITEMSERVER->SendItemData( pcUserData, &sItem );
				}
			}
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' creado perfecto con especializacion %d", szCommandParam1, atoi( szCommandParam2 ) );
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/RecoveryItem", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			ITEMSERVER->AddItemRecovery( pcUser, szCommandParam1 );
		}
		return TRUE;
	}
	if ( COMMAND( "/extradrop", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			int iDrop = atoi( szCommandParam1 );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Botín extra: %d -> %d", *(int*)0x0084602C, iDrop );
			*(int*)0x0084602C = iDrop;
		}
		else
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Botín extra: %d", *(int*)0x0084602C );
	}
	if ( COMMAND( "/event_reducemondmg", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( STRINGCOMPAREI( "true", szCommandParam1 ) )
			{
				EVENT_REDUCE_DAMAGEMON		= TRUE;
				EVENT_REDUCE_DAMAGEMON_LIVE = TRUE;
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Evento de reducción de daño de monstruos ACTIVADO!" );
			}
			else if ( STRINGCOMPAREI( "false", szCommandParam1 ) )
			{
				EVENT_REDUCE_DAMAGEMON		= FALSE;
				EVENT_REDUCE_DAMAGEMON_LIVE = FALSE;
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Evento de reducción de daño de monstruos DESACTIVADO!" );
			}
			else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /event_reducemondmg <true|false>" );
		}
		else
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Uso: /event_reducemondmg <true|false> [%s]", EVENT_REDUCE_DAMAGEMON ? "ACTIVADO" : "DESACTIVADO" );
	}
	if ( COMMAND( "/SuperPowerEvent", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			int iSuperPower = atoi( szCommandParam1 );
			if ( iSuperPower >= 0 )
				EVENT_SUPERPOWER = iSuperPower;

			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Evento super power: %d%%!", iSuperPower );
		}
	}
	if ( COMMAND( "/serverfps", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			int iFps = atoi( szCommandParam1 );
			if ( iFps > 1000 )
				iFps = 1000;
			else if ( iFps < 15 )
				iFps = 15;

			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> FPS servidor: %d -> %d", *(int *)0x006E46F4, iFps );
			*(int *)(0x006E46F4) = iFps;
			*(DWORD *)(0x07AC9F74) = 0;
		}
		else
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> FPS servidor: %d", *(int *)(0x006E46F4) );
	}

	if ( COMMAND( "/GetRoomCount", pszBuff ) || COMMAND( "/!GetRoomCount", pszBuff ) )
	{
		UINT iRoomCount = 0;
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
			iRoomCount = ROOMINSTANCEHANDLER->GetRooms( (EMapID)atoi( szCommandParam1 ) ).size();
		else
			iRoomCount = ROOMINSTANCEHANDLER->GetRooms().size();

		CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Cantidad de salas: %d", iRoomCount );
	}

	if ( COMMAND( "/SetRoomTest", pszBuff ) )
	{
		CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Prueba de sala completada [%d]", ROOMINSTANCEHANDLER->Add( MAPID_Invalid )->GetID() );
	}

	if ( COMMAND( "/DelRoomTest", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			ROOMINSTANCEHANDLER->Delete( atoi( szCommandParam1 ) );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Prueba de sala eliminada [%d]", atoi( szCommandParam1 ) );
		}
	}

	if ( COMMAND( "/SQLSkill", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ), GetParameterString( pszBuff, 3, szCommandParam3 ) )
		{
			WriteSQLSkillInfo( szCommandParam1, szCommandParam2, atoi( szCommandParam3 ) );
		}
	}
	if ( COMMAND( "/SQLCALCMON", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) && GetParameterString( pszBuff, 3, szCommandParam3 )
			&& GetParameterString( pszBuff, 4, szCommandParam4 ) )
		{
			int iCount = 0;

			int iTotal = ((atoi( szCommandParam1 ) * 24) * atoi( szCommandParam4 )) * atoi( szCommandParam2 );

			for ( int i = 0; i < iTotal; i++ )
			{
				int iPercentMax = 105019060;

				int iChanceDrop = iPercentMax - atoi( szCommandParam3 );

				int v = CALL( 0x00402050 ) % iPercentMax;

				if ( v < iChanceDrop )
					iCount++;
			}

			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> [%d]", iTotal - iCount );
		}
	}

	if ( COMMAND( "/!expevent", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			int iExp = atoi( szCommandParam1 );
			if ( iExp > 1000 )
				iExp = 1000;
			else if ( iExp < 0 )
				iExp = 0;

			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Evento EXP: %d%% -> %d%%", *(int*)0x0084601C, iExp );
			*(int*)(0x0084601C)		= iExp;

			NETSERVER->SendEXPEventLogin( iExp );
		}
		else
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Evento EXP: %d%%", *(int*)(0x0084601C) );
	}
	if ( COMMAND( "/PVPMap", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			int iMap = atoi( szCommandParam1 );

			if ( iMap != -1 )
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Mapa PVP: %d", iMap );
			else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡El mapa PVP está deshabilitado!" );
			*(int*)(0x0084831C) = iMap;
		}
		else
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Evento EXP: %d%%", *(int*)(0x0084601C) );
	}
	if ( COMMAND( "/EventBC", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			int i = atoi( szCommandParam1 );

			if ( i != -1 )
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Modo Guerra de Asedio: %d", i );

			BLESSCASTLESERVER->SetSiegeWarMode( (ESiegeWarMode)i );
		}
		else
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Evento EXP: %d%%", *(int*)(0x0084601C) );
	}
	if ( MAPSDATA[MAPID_BlessCastle].iState )
	{
		if ( COMMAND( "/StartSiegeWar", pszBuff ) )
		{
			BLESSCASTLESERVER->Start();
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Iniciado!" );
		}
		if ( COMMAND( "/EndSiegeWar", pszBuff ) )
		{
			BLESSCASTLESERVER->ResetUserScore();
			BLESSCASTLESERVER->End( FALSE );
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Terminado!" );
		}
		if ( COMMAND( "/EndWinSiegeWar", pszBuff ) )
		{
			BLESSCASTLESERVER->psBlessCastleStatusData->dwBattleOverTime = TICKCOUNT;
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Terminado!" );
		}
		if ( COMMAND( "/EasySiegeWar", pszBuff ) )
		{
			BLESSCASTLESERVER->EasySiegeWar();
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Guerra de asedio fácil activada!" );
		}
		if ( COMMAND( "/TestSiegeWarCMD1", pszBuff ) )
		{
			BLESSCASTLESERVER->SpeedUpDeathTimer();
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> PROBADO!" );
		}
		if ( COMMAND( "/TestSiegeWarCMD2", pszBuff ) )
		{
			BLESSCASTLESERVER->RemoveTimeAlive();
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> PROBADO 2!" );
		}
		if ( COMMAND( "/KillUnitsSiegeWar", pszBuff ) )
		{
			BLESSCASTLESERVER->EasySiegeWar();
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Guerra de asedio fácil activada!" );
		}
	}

	if ( COMMAND( "/!ClearTickRO", pszBuff ) )
	{
		EVENTSERVER->ClearTickOnlineReward();
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Recompensa en línea: ¡limpiada!" );
	}

	if ( COMMAND( "/!SetTickDR", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			int iHour = atoi( szCommandParam1 );

			EVENTSERVER->SetDailyReward( iHour );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Recompensa diaria: ¡nueva hora [%d]!", iHour );
		}
		else
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /!SetTickDR <hora>" );
	}

	if ( COMMAND( "/!ClearTickXmas", pszBuff ) )
	{
		EVENTSERVER->ClearTickOnlineRewardXmas();
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Recompensa en línea de Navidad: ¡limpiada!" );
	}

	if ( COMMAND( "/ActivePartyInfo", pszBuff ) )
	{
		int iMapID = -1;
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
			iMapID = atoi( szCommandParam1 );

		PARTYHANDLER->SendActivePartyInfo( pcUser, iMapID );
	}

	if ( COMMAND( "/debugmon", pszBuff ) )
	{
		bTestDebugDamageUnit = bTestDebugDamageUnit ? FALSE : TRUE;
		CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Prueba de depuración de daño a monstruo[%s]", bTestDebugDamageUnit ? "ACTIVADO" : "DESACTIVADO" );
	}

	if ( COMMAND( "/DDoSDC", pszBuff ) )
	{
		GetParameterString( pszBuff, 1, szCommandParam1 );
		for ( int i = 0; i < 11; i++ )
			SOCKETSERVER->AddDisconnectedUser( StringIPToNumberIPV4( szCommandParam1 ) );

		CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡Prueba DDoS!" );
	}

	if ( COMMAND( "/setbosstime", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			BOSS_TIME = atoi( szCommandParam1 );
			*(UINT*)0x07AC9F60 = 0;
			*(DWORD*)(0x7AC9F64) = 0;

			MAPSERVER->UpdateUsersBossTime();

			MAPSERVER->SQLUpdateBossTime( BOSS_TIME, SERVER_CODE, (int)(*(WORD *)0x07AC9F54), TRUE );
			MAPSERVER->SQLUpdateBossTimeBotDB( BOSS_TIME, SERVER_CODE, (int)(*(WORD *)0x07AC9F54) );

			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Nuevo horario de boss [xx:%02d]", BOSS_TIME );
		}
	}

	if ( iLen = COMMAND( "/sod_enable", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( STRINGCOMPAREI( "true", szCommandParam1 ) )
			{
				EVENT_BELLATRA = 2;
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Evento Bellatra habilitado!" );
			}
			else if ( STRINGCOMPAREI( "false", szCommandParam1 ) )
			{
				EVENT_BELLATRA = 0;
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Evento Bellatra deshabilitado!" );
			}
			else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /sod_enable <true|false>" );
		}
		else
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /sod_enable <true|false>" );
	}

	if ( iLen = COMMAND( "/event_crystal", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( STRINGCOMPAREI( "true", szCommandParam1 ) )
			{
				(*(int*)0x00845FF8) = 2;
				(*(int*)0x07AC9D50) = 1;
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Evento Crystal habilitado!" );
			}
			else if ( STRINGCOMPAREI( "false", szCommandParam1 ) )
			{
				(*(int*)0x00845FF8) = 0;
				(*(int*)0x07AC9D50) = 0;
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Evento Crystal deshabilitado!" );
			}
			else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /event_crystal <true|false>" );
		}
		else
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /event_crystal <true|false>" );
	}

	if ( iLen = COMMAND( "/set_ViewSightSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo = UNITSERVER->GetUnitInfoByName( pcUnitData->GetName() );

				if ( psCharacterData && psUnitInfo )
				{
					psUnitInfo->iSight = atoi( szCommandParam2 );
					psCharacterData->iSight = psUnitInfo->iSight * psUnitInfo->iSight;
					WriteMonsterStatus( pcUnitData, "ViewSight", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/set_HPSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo			= psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psCharacterData->sHP.sMax = atoi( szCommandParam2 );
					psCharacterData->sHP.sCur = psCharacterData->sHP.sMax;
					WriteMonsterStatus( pcUnitData, "HP", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}

	if ( iLen = COMMAND( "/set_EXPSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo			= psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					LARGE_INTEGER li;
					li.QuadPart = _atoi64( szCommandParam2 );

					if ( RATE_EXP > 0 )
						li.QuadPart = li.QuadPart * RATE_EXP;

					if ( EVENT_PVPMODE )
						li.QuadPart += (li.QuadPart * RATE_EXPPVPMODE) / 100;

					psCharacterData->iCurrentExpLow = li.LowPart;
					psCharacterData->iCurrentExpHigh = li.HighPart;
					WriteMonsterStatus( pcUnitData, "EXP", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}

	if ( iLen = COMMAND( "/set_SpecialSkillTypeSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo   = psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psUnitInfo->iSkillType = atoi( szCommandParam2 );
					WriteMonsterStatus( pcUnitData, "SpecialSkillType", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/set_SpecialSkillHitSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo   = psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psUnitInfo->iSkillPierceRange = atoi( szCommandParam2 );
					WriteMonsterStatus( pcUnitData, "SpecialSkillHit", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/set_SpecialHitRateSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo   = psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psUnitInfo->iSkillChance = atoi( szCommandParam2 );
					WriteMonsterStatus( pcUnitData, "SpecialHitRate", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/set_SpecialHitScopeSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo   = psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psUnitInfo->iSkillArea = atoi( szCommandParam2 );
					WriteMonsterStatus( pcUnitData, "SpecialHitScope", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/set_SpecialHitPowerMinSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo   = psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psUnitInfo->sSkillPower.sMin = atoi( szCommandParam2 );
					WriteMonsterStatus( pcUnitData, "SpecialHitPowerMin", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/set_SpecialHitPowerMaxSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo   = psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psUnitInfo->sSkillPower.sMax = atoi( szCommandParam2 );
					WriteMonsterStatus( pcUnitData, "SpecialHitPowerMin", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/set_ATKPowMinSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo   = psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psCharacterData->iMinDamage = atoi( szCommandParam2 );
					WriteMonsterStatus( pcUnitData, "ATKPowMin", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/set_ATKPowMaxSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo   = psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psCharacterData->iMaxDamage = atoi( szCommandParam2 );
					WriteMonsterStatus( pcUnitData, "ATKPowMax", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/set_AbsorbSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo   = psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psCharacterData->iAbsorbRating = atoi( szCommandParam2 );
					WriteMonsterStatus( pcUnitData, "Absorb", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/set_StunchanceSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo   = psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psUnitInfo->iFlinch = atoi( szCommandParam2 );
					WriteMonsterStatus( pcUnitData, "Stunchance", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/set_BlockSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo   = psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psCharacterData->iBlockRating = atoi( szCommandParam2 );
					WriteMonsterStatus( pcUnitData, "Block", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/set_DefenseSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo   = psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psCharacterData->iDefenseRating = atoi( szCommandParam2 );
					WriteMonsterStatus( pcUnitData, "Defense", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/set_AttackSpeedSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo   = psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psCharacterData->iAttackSpeed = atoi( szCommandParam2 );
					WriteMonsterStatus( pcUnitData, "AttackSpeed", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/set_AttackRatingSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo   = psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psCharacterData->iAttackRating = atoi( szCommandParam2 );
					WriteMonsterStatus( pcUnitData, "AttackRating", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/set_AttackRangeSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo   = psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psCharacterData->iAttackRange = atoi( szCommandParam2 ) << 8;
					WriteMonsterStatus( pcUnitData, "AttackRange", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/set_PerfectAttackRateSQL", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			if ( pcUnitData )
			{
				CharacterData * psCharacterData = UNITSERVER->GetCharacterDataByName( pcUnitData->GetName() );
				UnitInfo * psUnitInfo			= psCharacterData != NULL ? psCharacterData->psUnitInfo : NULL;

				if ( psCharacterData && psUnitInfo )
				{
					psUnitInfo->iLureDistance = atoi( szCommandParam2 );
					WriteMonsterStatus( pcUnitData, "PerfectAttackRate", szCommandParam2 );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' ¡Hecho!", pcUnitData->GetName() );
				}
			}
		}
		return TRUE;
	}
	if ( iLen = COMMAND( "/KillUnitsMap", pszBuff ) )
	{
		if ( pcUserData )
		{
			// Is User Alive?
			if ( pcUserData )
			{
				Map * pcMap = MAPSDATA + pcUserData->iMapID;

				if ( pcMap )
				{
					int iCount = 0;

					for ( int i = 0; i < MAX_ALIVEMONSTERS; i++ )
					{
						UnitData * pcUnitData = pcMap->pcaUnitData[i];

						// Is Unit Alive?
						if ( pcUnitData && pcUnitData->sCharacterData.sHP.sCur > 0 )
						{
							// Kill Unit
							pcUnitData->sCharacterData.sHP.sCur = pcUnitData->sCharacterData.sHP.sMax = 0;

							if ( pcUnitData->Animate( ANIMATIONTYPE_Die ) )
								iCount++;
						}
					}

					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Unidades eliminadas[%d] MapID[%d]", iCount, pcUserData->iMapID );
				}
			}
		}
	}

	if ( iLen = COMMAND( "/ResetAliveUnitsMap", pszBuff ) )
	{
		Map * pcMap = MAPSDATA + pcUserData->iMapID;
		if ( pcMap )
		{
			pcMap->iNumAliveUnitData = 0;
		}
	}


	return TRUE;
}

BOOL ServerCommand::OnGameMasterEventCommand( UserData * pcUserData, const char * pszBuff )
{
	User * pcUser = USERDATATOUSER( pcUserData );

	int iLen = 0;

	char szCommandParam1[256] = { 0 };
	char szCommandParam2[256] = { 0 };
	char szCommandParam3[256] = { 0 };
	char szCommandParam4[256] = { 0 };
	char szCommandParam5[256] = { 0 };

	if ( pszBuff[0] == '/' && pszBuff[1] == '!' )
	{
		if ( pszBuff[2] == '>' )
		{
			if ( pszBuff[3] == '>' )
			{
				CHATSERVER->SendChatAllEx( CHATCOLOR_Global, "%s", (char*)&pszBuff[4] );
			}
			else
			{
				char * p = CHARACTERSERVER->GetCharacterName( pcUserData );
				
				if ( p[0] != 0 )
					CHATSERVER->SendChatAllEx( CHATCOLOR_Global, "GM> %s", (char*)&pszBuff[3] );
			}
		}
		else if ( pszBuff[2] == '+' )
		{
			char * p = CHARACTERSERVER->GetCharacterName( pcUserData );

			if ( p[0] != 0 )
				CHATSERVER->SendChatAllEx( CHATCOLOR_Global, "%s> %s", p, (char*)&pszBuff[3] );
		}
	}

	if ( COMMAND( "/!StartMaintenance", pszBuff ) || COMMAND( "/StartMaintenance", pszBuff ) )
	{
		GetParameterString( pszBuff, 1, szCommandParam1 );

		int iSeconds = 300;
		if ( szCommandParam1[0] != 0 )
			iSeconds = atoi( szCommandParam1 );

		if ( iSeconds > 0 )
		{
			CHATSERVER->SendChatAll( CHATCOLOR_Global, "Notice> ¡Anuncio del servidor!" );
			CHATSERVER->SendChatAll( CHATCOLOR_Global, "Notice> ¡El mantenimiento comienza ahora!" );
			CHATSERVER->SendChatAll( CHATCOLOR_Global, "Notice> ¡Revisa nuestro Discord para más información!" );
			CHATSERVER->SendChatAll( CHATCOLOR_Global, "Notice> ¡Por favor desconéctate del servidor!" );
			CHATSERVER->SendChatAllEx( CHATCOLOR_Global, "Notice> ¡Disfruta %s!", GAME_NAME );

			GSERVER->StartMaintenanceCountdown( iSeconds );
		}
	}

	if ( COMMAND( "/!SetMaintenanceFlag", pszBuff ) || COMMAND( "/SetMaintenanceFlag", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( STRINGCOMPAREI( szCommandParam1, "true" ) )
				SERVER->SetMaintenance( TRUE );
			else
				SERVER->SetMaintenance( FALSE );
		}

		CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡El estado de mantenimiento está %s!", SERVER->GetMaintenance() ? "ACTIVADO" : "DESACTIVADO" );
	}

	if ( COMMAND( "/!StopMaintenance", pszBuff ) || COMMAND( "/StopMaintenance", pszBuff ) )
	{
		GSERVER->StopMaintenanceCountdown();

		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡La cuenta regresiva de mantenimiento se detuvo!" );
	}

	if ( iLen = COMMAND( "/!HWCombination", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			MANUFACTUREHANDLER->SetHalloweenCombination( atoi( szCommandParam1 ) );
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ID de combinacion ( %d )", MANUFACTUREHANDLER->GetHalloweenCombination() );
		}
		else
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ID de combinacion ( %d )", MANUFACTUREHANDLER->GetHalloweenCombination() );
	}
	if ( iLen = COMMAND( "/HWItemSoul", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			HALLOWEENHANDLER->ClearTickItem();
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡Hecho!" );
		}
	}

	if ( iLen = COMMAND( "/!kickall", pszBuff ) )
	{
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Expulsando...!" );
		for ( int i = 0; i < PLAYERS_MAX; i++ )
		{
			User * pcU = USERDATATOUSER( &USERSDATA[i] );
			if ( USERSDATA[i].pcSocketData && USERSDATA[i].iGameLevel == GAMELEVEL_None && pcU && !pcU->bNetServer )
			{
				SENDPACKETBLANK( USERDATATOUSER( &USERSDATA[i] ), PKTHDR_Disconnect, TRUE );
				WNDPROC_SOCKETCLOSE( SOCKETSERVER->GetHWND(), USERSDATA[i].pcSocketData );
			}
		}
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Todos expulsados!" );
	}

	if ( iLen = COMMAND( "/SetPos", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			CHARACTERSERVER->SetPositionWarp( pcUserData, atoi( szCommandParam1 ), atoi( szCommandParam2 ), pcUserData->iMapID );
			CHATSERVER->SendChatEx( pcUser, EChatColor::CHATCOLOR_Error, "> Posición X: %d   Z: %d", atoi( szCommandParam1 ), atoi( szCommandParam2 ) );
		}
	}

	if ( iLen = COMMAND( "/SetPacketUnit", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			CHATSERVER->SendChatEx( pcUser, EChatColor::CHATCOLOR_Error, "> Máx. de paquetes: %d -> %d", iUpdateMaxPacket, atoi( szCommandParam1 ) );
			iUpdateMaxPacket = atoi( szCommandParam1 );
		}
	}

	if ( iLen = COMMAND( "/SetMaskUnit", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			CHATSERVER->SendChatEx( pcUser, EChatColor::CHATCOLOR_Error, "> Máx. de máscara: %d -> %d", iUpdateMaxUnitMask, atoi( szCommandParam1 ) );
			iUpdateMaxUnitMask = atoi( szCommandParam1 );
		}
	}

	if ( iLen = COMMAND( "/SetFrameCounterUnit", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			CHATSERVER->SendChatEx( pcUser, EChatColor::CHATCOLOR_Error, "> Máx. de frame counter: %d -> %d", iUpdateFrameCounter, atoi( szCommandParam1 ) );
			iUpdateFrameCounter = atoi( szCommandParam1 );
		}
	}

	if ( iLen = COMMAND( "/gf_enable", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( STRINGCOMPAREI( "true", szCommandParam1 ) )
			{
				FURYARENAHANDLER->SetEnable( TRUE );
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡La Gran Furia está habilitada!" );
			}
			else if ( STRINGCOMPAREI( "false", szCommandParam1 ) )
			{
				FURYARENAHANDLER->SetEnable( FALSE );
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡La Gran Furia está deshabilitada!" );
			}
			else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /gf_enable <true|false>" );
		}
		else
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /gf_enable <true|false>" );
	}

	if ( iLen = COMMAND( "/gf_start", pszBuff ) )
	{
		if ( !FURYARENAHANDLER->IsStarted() )
		{
			FURYARENAHANDLER->StartEvent();
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡La Gran Furia inició!" );
		}
		else
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡La Gran Furia ya está iniciada!" );
	}

	if ( iLen = COMMAND( "/gf_end", pszBuff ) )
	{
		if ( FURYARENAHANDLER->IsStarted() )
		{
			FURYARENAHANDLER->EndEvent();
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡La Gran Furia terminó!" );
		}
		else
			CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡La Gran Furia ya terminó!" );
	}

	if ( iLen = COMMAND( "/gf_call", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			User * pcUser = USERDATATOUSER( USERSERVER->GetUserdata( szCommandParam1 ) );
			// Is User Alive?
			if ( pcUser )
			{
				// Enter to arena
				FURYARENAHANDLER->EnterFromArena( pcUser );
			}
		}
		else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /gf_call <nombre>" );
	}

	if ( iLen = COMMAND( "/gf_time", pszBuff ) )
	{
		FURYARENAHANDLER->UpdateTime();
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "TGF> ¡Tiempo actualizado!" );
	}

	if ( iLen = COMMAND( "/gf_gettick", pszBuff ) )
	{
		CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "TGF> Tick: %d", FURYARENAHANDLER->GetTick() );
	}

	if ( iLen = COMMAND( "/gf_getstone", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
		{
			DefinitionItem * psDef = ITEMSERVER->FindItemDefByCode( ITEMID_KingStone );
			if ( psDef )
			{
				Item sItem;
		ITEMSERVER->CreateItem( &sItem, psDef, EItemSource::GameMaster );
				sItem.eMixTypeName		= (EMixTypeName)atoi( szCommandParam1 );
				sItem.sQuestMonsters.sCur = atoi( szCommandParam2 );
				ITEMSERVER->ValidateItemTime( &sItem );
				ITEMSERVER->SendItemData( pcUserData, &sItem );
			}
		}
	}

	if ( iLen = COMMAND( "/gf_getstone", pszBuff ) )
	{


	}

	if ( iLen = COMMAND( "/gf_timeminion", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( FURYARENAHANDLER->SetTimeMinion( atoi( szCommandParam1 ) ) )
			{
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Tiempo de esbirro de La Gran Furia: %d", atoi( szCommandParam1 ) );
			}
		}
		else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /gf_timeminion <minutos>" );
	}

	if ( iLen = COMMAND( "/gf_boss", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( FURYARENAHANDLER->SetBoss( szCommandParam1 ) )
			{
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Jefe de La Gran Furia: %s", szCommandParam1 );
			}
		}
		else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /gf_boss <nombre>" );
	}

	if ( iLen = COMMAND( "/gf_minion", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( FURYARENAHANDLER->SetMinion(szCommandParam1) )
			{
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Esbirro de La Gran Furia: %s", szCommandParam1 );
			}
		}
		else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /gf_minion <nombre>" );
	}

	if ( iLen = COMMAND( "/gf_monevent", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( FURYARENAHANDLER->SetMonsterEvent(szCommandParam1) )
			{
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Evento de monstruos de La Gran Furia: %s", szCommandParam1 );
			}
		}
		else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /gf_monevent <nombre>" );
	}

	if ( iLen = COMMAND( "/gf_kick", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			User * pcUser = USERDATATOUSER( USERSERVER->GetUserdata( szCommandParam1 ) );
			// Is User Alive?
			if ( pcUser )
			{
				// Enter to arena
				FURYARENAHANDLER->LeaveFromArena( pcUser );
			}
		}
		else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /gf_kick <nombre>" );
	}

	if ( iLen = COMMAND( "/Meteor", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			PacketFireMeteorite sPacket;
			sPacket.iLength = sizeof( PacketFireMeteorite );
			sPacket.iHeader = PKTHDR_FireMeteorite;
			sPacket.bSmallMeteor = FALSE;
			sPacket.iDelay = RandomI( 50, 251 );
			sPacket.sBegin.iX = pcUserData->sPosition.iX - 8092;
			sPacket.sBegin.iY = pcUserData->sPosition.iY + 150000;
			sPacket.sBegin.iZ = pcUserData->sPosition.iZ - 8092;
			sPacket.sEnd.iX = pcUserData->sPosition.iX + 8092;
			sPacket.sEnd.iY = pcUserData->sPosition.iY;
			sPacket.sEnd.iZ = pcUserData->sPosition.iZ + 8092;
			sPacket.iCount = RandomI( 1, 3 );
			SENDPACKETRANGE( &sPacket, (Point3D*)&pcUserData->sPosition, DISTANCE_UNIT_FAR );

			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
			{
				// Structure Packet to Quick Damage
				PacketDamageQuick sPDM;
				sPDM.iLength		= sizeof( PacketDamageQuick );
				sPDM.iHeader		= PKTHDR_DamageQuick;
				sPDM.bPercentile	= FALSE;
				sPDM.bBaseCurrentHP = FALSE;
				sPDM.iDamage		= atoi( szCommandParam1 );
				SENDPACKETRANGE( &sPDM, (Point3D*)&pcUserData->sPosition, (atoi( szCommandParam2 ) * 27) );
			}
		}
	}

	if (iLen = COMMAND("/remove_npc", pszBuff))
	{
		if (GetParameterString(pszBuff, 1, szCommandParam1)) //npc id (via mouse id)
		{
			int currentStageId = pcUserData->iMapID;
			int npcID = atoi(szCommandParam1);
			int iX, iZ;
			BOOL bFound = FALSE;

			Map* psMap = MAPSDATA + currentStageId;

			if (psMap == NULL)
				return TRUE;

			for (int i = 0; i < MAX_NPCINMAP; i++)
			{
				PacketUnitInfo* psNPC = psMap->saNPC + i;

				if (psNPC->iHeader == 0)
					continue;

				if (psNPC->iID == npcID)
				{
					iX = psNPC->sPosition.iX >> 8;
					iZ = psNPC->sPosition.iZ >> 8;

					ZeroMemory(psNPC, sizeof(PacketUnitInfo));

					bFound = TRUE;
					break;
				}
			}

			if (bFound == FALSE)
			{
				CHATSERVER->SendChatEx(pcUser, CHATCOLOR_Error, "> Error al eliminar NPC ID: %d. ¿No es un NPC?", npcID);
				return TRUE;
			}
			else
			{
				MAPSERVER->RemoveNPC(psMap, npcID);

				SQLConnection* pcDB = SQLCONNECTION(DATABASEID_GameDB);

				if (pcDB->Open())
				{
					if (pcDB->Prepare("DELETE FROM MapNPC WHERE Stage=? AND X=? AND Z=?"))
					{
						pcDB->BindParameterInput(1, PARAMTYPE_Integer, &currentStageId);
						pcDB->BindParameterInput(2, PARAMTYPE_Integer, &iX);
						pcDB->BindParameterInput(3, PARAMTYPE_Integer, &iZ);

						if (!pcDB->Execute())
						{
							//WARN("Remove NPC failed. Stage: %d, X: %d, Z: %d", currentStageId, iX, iZ);
						}
					}

					pcDB->Close();
				}

					//CHATSERVER->SendChatAllGM("GM> NPC eliminado del mapa ID(%d) EN X(%d) Z(%d)", currentStageId, iX, iZ);
			}
		}
		else
		{
			CHATSERVER->SendChat(pcUser, CHATCOLOR_Error, "> Se esperaba un id como primer parámetro");
		}

		return TRUE;
	}


	//Add NPC
	if (iLen = COMMAND("/add_npc", pszBuff))
	{
		if (GetParameterString(pszBuff, 1, szCommandParam1) &&
			GetParameterString(pszBuff, 2, szCommandParam2) &&
			GetParameterString(pszBuff, 3, szCommandParam3) &&
			GetParameterString(pszBuff, 4, szCommandParam4) &&
			GetParameterString(pszBuff, 5, szCommandParam5))
		{
			int currentStageId = pcUserData->iMapID;
			int dbNpcId = atoi(szCommandParam1);
			int iX = atoi(szCommandParam2);
			int iY = atoi(szCommandParam3);
			int iZ = atoi(szCommandParam4);
			int iAngle = atoi(szCommandParam5);
			int enabled = 1;
			int onlyGM = 0;

			SQLConnection* pcDB = SQLCONNECTION(DATABASEID_GameDB);

			int npcCount = 0;
			if (pcDB->Open())
			{
				if (pcDB->Prepare("SELECT COUNT(ID) FROM NPCList WHERE ID=?"))
				{
					pcDB->BindParameterInput(1, PARAMTYPE_Integer, &dbNpcId);
					if (pcDB->Execute() && pcDB->Fetch())
					{
						pcDB->GetData(1, PARAMTYPE_Integer, &npcCount);
					}
				}

				if (npcCount == 1)
				{
					pcDB->Clear();

					if (pcDB->Prepare("INSERT INTO MapNPC VALUES (?,?,?,?,?,?,?,?)"))
					{
						pcDB->BindParameterInput(1, PARAMTYPE_Integer, &pcUserData->iMapID); //Stage
						pcDB->BindParameterInput(2, PARAMTYPE_Integer, &iX);
						pcDB->BindParameterInput(3, PARAMTYPE_Integer, &iY);
						pcDB->BindParameterInput(4, PARAMTYPE_Integer, &iZ);
						pcDB->BindParameterInput(5, PARAMTYPE_Integer, &iAngle);
						pcDB->BindParameterInput(6, PARAMTYPE_Integer, &dbNpcId); //IDNPC
						pcDB->BindParameterInput(7, PARAMTYPE_Integer, &enabled); //Enabled
						pcDB->BindParameterInput(8, PARAMTYPE_Integer, &onlyGM);  //OnlyGM
						pcDB->Execute();
					}

					pcDB->Close();

					bool found = false;

					for (UINT i = 0; i < MAX_NPCINMAP; i++)
					{
						PacketUnitInfo* psNPC = MAPSDATA->saNPC + i;

						//found next empty one
						if ((psNPC->iHeader == 0))
						{
							psNPC[i].sCharacterData.iClanID = onlyGM;

							std::string s = std::to_string(dbNpcId);
							strcpy_s(psNPC[i].sCharacterData.szName, 32, s.c_str());

							// Packet structure
							psNPC[i].iLength = sizeof(PacketUnitInfo);
							psNPC[i].iHeader = PKTHDR_NpcData;
							psNPC[i].sCharacterData.saUnused = 200; // ???
							psNPC[i].sCharacterData.sHP.sCur = 100; // HP default
							psNPC[i].sCharacterData.sHP.sMax = 100; // HP default
							psNPC[i].iID = 8100; // Default ID
							psNPC[i].sPosition.iX = iX * 256; // X << 8
							psNPC[i].sPosition.iY = iY * 256; // Y << 8
							psNPC[i].sPosition.iZ = iZ * 256; // Z << 8
							psNPC[i].sAngle.iX = 0;
							psNPC[i].sAngle.iY = iAngle;
							psNPC[i].sAngle.iZ = 0;

							MAPSERVER->SpawnNPC(MAPSDATA + currentStageId, &psNPC[i]);

								//CHATSERVER->SendChatAllGM("GM> NPC ID(%d) agregado al mapa ID(%d) EN X(%d) Z(%d)", dbNpcId, pcUserData->iMapID, iX, iZ);

							found = true;
							break;
						}
					}

					if (!found)
					{
						CHATSERVER->SendChatEx(pcUser, CHATCOLOR_Error, "> NPC ID(%d) no fue agregado al mapa ID(%d). Se alcanzo el maximo!", dbNpcId, pcUserData->iMapID);
					}
				}
				else
				{
					pcDB->Close();
					CHATSERVER->SendChatEx(pcUser, CHATCOLOR_Error, "> ¡NPC ID(%d) no existe!", dbNpcId);
				}
			}
		}
	}

	//Update Position
	if ( iLen = COMMAND( "/set_pos", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) &&
				GetParameterString( pszBuff, 2, szCommandParam2 ) &&
				GetParameterString( pszBuff, 3, szCommandParam3 ) &&
				GetParameterString( pszBuff, 4, szCommandParam4 ) )
			{
				int iID = atoi( szCommandParam1 );
				int iX = atoi( szCommandParam2 );
				int iY = atoi( szCommandParam3 );
				int iZ = atoi( szCommandParam4 );

				UnitData * pcUnitData = UNITSERVER->GetUnit( iID );

				if ( pcUnitData && MAPSERVER->UpdateUnitPosition( pcUnitData, pcUserData->iMapID, iX, iY, iZ ) )
				{
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> %s ID(%d) X(%d) Y(%d) Z(%d)", pcUnitData->sCharacterData.szName, iID, iX, iY, iZ );
				}
			}
		}
		return TRUE;
	}

	//Update Angle
	if ( iLen = COMMAND( "/set_ang", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) &&
				GetParameterString( pszBuff, 2, szCommandParam2 ) )
			{
				int iID = atoi( szCommandParam1 );
				int iAngle = atoi( szCommandParam2 );

				UnitData * pcUnitData = UNITSERVER->GetUnit( iID );

				if ( pcUnitData && MAPSERVER->UpdateUnitAngle( pcUnitData, pcUserData->iMapID, iAngle ) )
				{
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> %s ID(%d) Angle(%d)", pcUnitData->sCharacterData.szName, iID, iAngle );
				}
			}
		}
		return TRUE;
	}

	// Kill Enemy
	if ( iLen = COMMAND( "/killmon", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );

			// Is Unit Alive?
			if ( pcUnitData )
			{
				// Kill Unit
				pcUnitData->sCharacterData.sHP.sCur = pcUnitData->sCharacterData.sHP.sMax = 0;

				if ( UNITSERVER->SetMotionFromCode( pcUnitData, UnitServer::MOTIONID_Death ) )
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' eliminado!", pcUnitData->sCharacterData.szName );
			}
		}
		return TRUE;
	}
	// Set HP Enemy
	if ( iLen = COMMAND( "/set_hp", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 ); // ID
			GetParameterString( pszBuff, 2, szCommandParam2 ); // HP

			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			short sEnemyHP = ( short )atoi( szCommandParam2 );

			// Is more than 30000 or minor than 0?
			if ( sEnemyHP < 0 )
			{
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡No puede ser mayor a 30k HP ni menor a 0!" );
				return TRUE;
			}

			// Is Unit Alive?
			if ( pcUnitData )
			{
				// Change HP Unit
				short sOldEnemyHP = pcUnitData->sCharacterData.sHP.sCur;
				pcUnitData->sCharacterData.sHP.sCur = sEnemyHP;

				if ( pcUnitData->sCharacterData.sHP.sCur > pcUnitData->sCharacterData.sHP.sMax )
					pcUnitData->sCharacterData.sHP.sMax = pcUnitData->sCharacterData.sHP.sCur;

				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' HP ( %d -> %d )!", pcUnitData->sCharacterData.szName, sOldEnemyHP, sEnemyHP );
			}
		}
		return TRUE;
	}

	// Set HP Enemy
	if ( iLen = COMMAND( "/set_abs", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			GetParameterString( pszBuff, 2, szCommandParam2 );

			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			short sEnemyAbs = ( short )atoi( szCommandParam2 );

			// Is more than 30000 or minor than 0?
			if ( sEnemyAbs < 0 )
			{
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡No puede ser mayor a 30k Abs ni menor a 0!" );
				return TRUE;
			}

			// Is Unit Alive?
			if ( pcUnitData )
			{
				// Change HP Unit
				short sOldEnemyAbs = pcUnitData->sCharacterData.iAbsorbRating;
				pcUnitData->sCharacterData.iAbsorbRating = sEnemyAbs;

				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' Absorcion ( %d -> %d )!", pcUnitData->sCharacterData.szName, sOldEnemyAbs, sEnemyAbs );
			}
		}
		return TRUE;
	}

	// Set Damage Enemy
	if ( iLen = COMMAND( "/set_dmg", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{

			GetParameterString( pszBuff, 1, szCommandParam1 );
			GetParameterString( pszBuff, 2, szCommandParam2 );
			GetParameterString( pszBuff, 3, szCommandParam3 );

			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			short sDamageMin = (short)atoi( szCommandParam2 );
			short sDamageMax = (short)atoi( szCommandParam3 );

			// Is more than 30000 or minor than 0?
			if ( sDamageMin < 0 || sDamageMax < 0 )
			{
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡No puede ser mayor a 30k HP ni menor a 0!" );
				return TRUE;
			}

			// Is Unit Alive?
			if ( pcUnitData )
			{
				// Change HP Unit
				short sOldDamageMin = pcUnitData->sCharacterData.iMinDamage;
				short sOldDamageMax = pcUnitData->sCharacterData.iMaxDamage;
				pcUnitData->sCharacterData.iMinDamage = sDamageMin;
				pcUnitData->sCharacterData.iMaxDamage = sDamageMax;

				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' Daño ( %d-%d -> %d-%d )!", pcUnitData->sCharacterData.szName, sOldDamageMin, sOldDamageMax, sDamageMin, sDamageMax );
			}
		}
		return TRUE;
	}

	// Kill Character
	if ( COMMAND( "/killch", pszBuff ) || COMMAND( "/!killch", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
			{
				UserData * pcUserKilled = USERSERVER->GetUserdata( szCommandParam1 );
				if ( pcUserKilled )
				{
					PacketSimple sPacket;
					sPacket.iLength = sizeof( PacketSimple );
					sPacket.iHeader = PKTHDR_TheDeath;
					sPacket.iUnk	= 0;
					SENDPACKET( USERDATATOUSER( pcUserKilled ), &sPacket );

					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡%s eliminado!", GAME_SERVER ? pcUserKilled->sCharacterData.szName : pcUserKilled->szCharacterName );
				}
				else
				{
					if ( GAME_SERVER )
						CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Prueba usar /!killch" );
					else
						CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Prueba usar /killch" );
				}
			}
			else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /(!)killch <chname>" );
		}
		return TRUE;
	}

	//Chica del Evento
	if ( COMMAND( "/event_girl", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			if ( STRINGCOMPAREI( "true", szCommandParam1 ) )
			{
				CHATSERVER->SendChat( pcUser, EChatColor::CHATCOLOR_Error, "> Chica del Evento gratis: ACTIVADO!" );
				FREE_EVENTGIRL = TRUE;
			}
			else if ( STRINGCOMPAREI( "false", szCommandParam1 ) )
			{
				CHATSERVER->SendChat( pcUser, EChatColor::CHATCOLOR_Error, "> Chica del Evento gratis: DESACTIVADO!" );
				FREE_EVENTGIRL = FALSE;
			}
			else
				CHATSERVER->SendChatEx( pcUser, EChatColor::CHATCOLOR_Error, "> Uso: /event_girl <true|false> [%s]", FREE_EVENTGIRL == TRUE ? "ACTIVADO" : "DESACTIVADO" );
		}
		else
			CHATSERVER->SendChatEx( pcUser, EChatColor::CHATCOLOR_Error, "> Uso: /event_girl <true|false> [%s]", FREE_EVENTGIRL == TRUE ? "ACTIVADO" : "DESACTIVADO" );

		return TRUE;
	}

	// Ban Character
	if ( COMMAND( "/banacc", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
			{
				UserData * pcUserBanned = USERSERVER->GetUserdata( szCommandParam1 );
				if ( pcUserBanned )
				{
					PacketLogCheatEx sPacket;
					sPacket.iCheatID = CHEATLOGID_GMReason;
					STRINGCOPY( sPacket.szParam, szCommandParam2 );
					LOGSERVER->OnLogCheat( pcUserBanned, &sPacket );
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡%s fue baneado!", pcUserBanned->sCharacterData.szName );
				}
				else
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡%s no fue encontrado!", szCommandParam1 );

				return TRUE;
			}
		}
	}

	// UnBan Character
	if ( COMMAND( "/unbanacc", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
			{
				CHEATSERVER->UnbanAccount( szCommandParam1 );
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡%s desbaneado!", szCommandParam1 );

				return TRUE;
			}
		}
	}

	// UnBan Character
	if ( COMMAND( "/mapusers", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
			{
				int iCount	= 0;
				int iMap	= atoi( szCommandParam1 );
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> [Usuarios del mapa %d]", iMap );
				// Search player
				for ( int i = 0; i < PLAYERS_MAX; i++ )
				{
					// Found?
					if ( USERSDATA[i].pcSocketData && USERSDATA[i].iMapID == iMap )
					{
						CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> %s", USERSDATA[i].sCharacterData.szName );
						iCount++;
					}
				}
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Total de jugadores en el mapa: %d", iCount );
				return TRUE;
			}
		}
	}

	if ( COMMAND( "/!UnbrokeAge", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			User * pcUser = USERDATATOUSER( pcUserData );
			pcUser->bUnbrokeAge = pcUser->bUnbrokeAge ? FALSE : TRUE;
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Anti-rotura de age: %s", pcUser->bUnbrokeAge ? "ACTIVADO" : "DESACTIVADO" );
		}
	}

	if ( COMMAND( "/!UnbrokePlusAge", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			User * pcUser = USERDATATOUSER( pcUserData );
			pcUser->bUnbrokeAge = pcUser->bUnbrokeAge ? FALSE : 2;
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Anti-rotura de age: %s", pcUser->bUnbrokeAge ? "ACTIVADO" : "DESACTIVADO" );
		}
	}

	if ( COMMAND( "/!Unbroke15Age", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			User * pcUser = USERDATATOUSER( pcUserData );
			pcUser->bUnbrokeAge = pcUser->bUnbrokeAge ? FALSE : 15;
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Anti-rotura de age 15: %s", pcUser->bUnbrokeAge ? "ACTIVADO" : "DESACTIVADO" );
		}
	}

	if (COMMAND("/!Unbroke18Age", pszBuff))
	{
		// Is User Alive?
		if (pcUserData)
		{
			User* pcUser = USERDATATOUSER(pcUserData);
			pcUser->bUnbrokeAge = pcUser->bUnbrokeAge ? FALSE : 18;
			CHATSERVER->SendChatEx(pcUser, CHATCOLOR_Error, "> Anti-rotura de age 18: %s", pcUser->bUnbrokeAge ? "ACTIVADO" : "DESACTIVADO");
		}
	}

	// Kill Character
	if ( COMMAND( "/kickch", pszBuff ) || COMMAND( "/!kickch", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
			{
				UserData * pcUserKilled = USERSERVER->GetUserdata( szCommandParam1 );
				if ( pcUserKilled )
				{
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> ¡%s expulsado!", GAME_SERVER ? pcUserKilled->sCharacterData.szName : pcUserKilled->szCharacterName );
					ACCOUNTSERVER->OnDisconnectUser( pcUserKilled );
					SENDPACKETBLANK( USERDATATOUSER( pcUserKilled ), PKTHDR_Disconnect, TRUE );
					pcUserKilled->dwDisconnectTime = TICKCOUNT + 1500;
					NETSERVER->DisconnectUser( pcUserKilled );
				}
				else
				{
					if ( GAME_SERVER )
						CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Prueba usar /!kickch" );
					else
						CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Prueba usar /kickch" );
				}
			}
			else
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /(!)kickch <chname>" );
		}
		return TRUE;
	}

	// Move
	if ( COMMAND( "/move", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) && GetParameterString( pszBuff, 2, szCommandParam2 ) )
			{
				UserData * pcUserWarp = USERSERVER->GetUserdata( szCommandParam2 );
				if ( pcUserWarp )
				{
					if ( STRINGCOMPARE( szCommandParam1, "here" ) )
					{
						PacketWarpGateField sPacket;
						sPacket.iLength	= sizeof( PacketWarpGateField );
						sPacket.iHeader = PKTHDR_WarpGateField;
						sPacket.iX		= pcUserData->sPosition.iX;
						sPacket.iZ		= pcUserData->sPosition.iZ;
						sPacket.iStage	= pcUserData->iMapID;
						SENDPACKET( USERDATATOUSER( pcUserWarp ), &sPacket );
					}
					else if ( STRINGCOMPARE( szCommandParam1, "to" ) )
					{
						PacketWarpGateField sPacket;
						sPacket.iLength	= sizeof( PacketWarpGateField );
						sPacket.iHeader = PKTHDR_WarpGateField;
						sPacket.iX		= pcUserWarp->sPosition.iX;
						sPacket.iZ		= pcUserWarp->sPosition.iZ;
						sPacket.iStage	= pcUserWarp->iMapID;
						SENDPACKET( USERDATATOUSER(pcUserData), &sPacket );
					}
				}
			}
			else
					CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> Uso: /move <here|to> <nombre>" );
		}
		return TRUE;
	}

	if ( iLen = COMMAND( "/!ResetPVPRank", pszBuff ) )
	{
		PVPSERVER->ResetTick();
		CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡Ranking PvP reiniciado!" );
	}

	if ( COMMAND( "/mon", pszBuff ) || COMMAND( "/monster", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			int iMonsterCount = 1;
			if ( GetParameterString( pszBuff, 2, szCommandParam2 ) )
				iMonsterCount += atoi( szCommandParam2 );

			if ( iMonsterCount > 100 )
				iMonsterCount = 100;

			for ( int i = 0; i < iMonsterCount; i++ )
			{
				Point3D sPosition = pcUserData->sPosition;
				sPosition.iX += rand() % (128 << 8);
				sPosition.iZ += rand() % (128 << 8);

				sPosition.iX -= 64 << 8;
				sPosition.iZ -= 64 << 8;

				if ( auto pcUnitData = MAPSERVER->SpawnMonster( szCommandParam1, pcUser->GetMapID(), sPosition ) )
				{
					if ( pcUser->GetGameLevel() < GAMELEVEL_Four )
						pcUnitData->sUnitInfo.iDropCount = 0;

					FixUnitDataName( pcUnitData );
				}
			}
		}
	}

	if ( COMMAND( "/pet", pszBuff ) || COMMAND( "/mymonster", pszBuff ) )
	{
		if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
		{
			int iMonsterCount = 1;
			if ( GetParameterString( pszBuff, 2, szCommandParam2 ) )
				iMonsterCount += atoi( szCommandParam2 );

			if ( iMonsterCount > 100 )
				iMonsterCount = 100;

			for ( int i = 0; i < iMonsterCount; i++ )
			{
				Point3D sPosition = pcUserData->sPosition;
				sPosition.iX += rand() % (128 << 8);
				sPosition.iZ += rand() % (128 << 8);

				sPosition.iX -= 64 << 8;
				sPosition.iZ -= 64 << 8;

				if ( auto pcUnitData = MAPSERVER->SpawnMonster( szCommandParam1, pcUser->GetMapID(), sPosition, pcUser ) )
				{
					if ( pcUser->GetGameLevel() < GAMELEVEL_Four )
						pcUnitData->sUnitInfo.iDropCount = 0;

					FixUnitDataName( pcUnitData );
				}
			}
		}
	}

	// Set Defense Enemy
	if ( iLen = COMMAND( "/set_def", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			GetParameterString( pszBuff, 2, szCommandParam2 );

			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			int iDefense = atoi( szCommandParam2 );

			// Is minor than 0?
			if ( iDefense < 0 )
			{
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡No puede ser menor que 0!" );
				return TRUE;
			}

			// Is Unit Alive?
			if ( pcUnitData )
			{
				// Change HP Unit
				int iOldDefense = pcUnitData->sCharacterData.iDefenseRating;
				pcUnitData->sCharacterData.iDefenseRating = iDefense;

				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' Defensa ( %d -> %d )!", pcUnitData->sCharacterData.szName, iOldDefense, iDefense );
			}
		}
		return TRUE;
	}

	// Set Level Enemy
	if ( iLen = COMMAND( "/set_lvl", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			GetParameterString( pszBuff, 2, szCommandParam2 );

			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			int iLevel = atoi( szCommandParam2 );

			// Is minor than 0?
			if ( iLevel < 0 )
			{
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡No puede ser menor que 0!" );
				return TRUE;
			}

			// Is Unit Alive?
			if ( pcUnitData )
			{
				// Change HP Unit
				int iOldLevel = pcUnitData->sCharacterData.iLevel;
				pcUnitData->sCharacterData.iLevel = iLevel;

				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' Nivel ( %d -> %d )!", pcUnitData->sCharacterData.szName, iOldLevel, iLevel );
			}
		}
		return TRUE;
	}

	// Set Defense Enemy
	if ( iLen = COMMAND( "/set_exp", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			GetParameterString( pszBuff, 1, szCommandParam1 );
			GetParameterString( pszBuff, 2, szCommandParam2 );

			UnitData * pcUnitData = UNITSERVER->GetUnit( atoi( szCommandParam1 ) );
			INT64 iExperience = _atoi64( szCommandParam2 );

			// Is minor than 0?
			if ( iExperience < 0 )
			{
				CHATSERVER->SendChat( pcUser, CHATCOLOR_Error, "> ¡No puede ser menor que 0!" );
				return TRUE;
			}

			// Is Unit Alive?
			if ( pcUnitData )
			{
				// Change HP Unit
				INT64 iOldExperience = (INT64)pcUnitData->sUnitInfo.iExp;
				pcUnitData->sUnitInfo.iExp = (int)iExperience;
				typedef void( __cdecl *t_SetExpUnitFunc )( CharacterData * pMonster, INT64 iExp );
				t_SetExpUnitFunc SetExpUnitFunc = ( t_SetExpUnitFunc )0x08B815CC;
				SetExpUnitFunc( &pcUnitData->sCharacterData, iExperience );
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> '%s' Experiencia ( %lld -> %lld )!", pcUnitData->sCharacterData.szName, iOldExperience, iExperience );
			}
		}
		return TRUE;
	}

	// Create a pet with warehouse function
	if ( iLen = COMMAND( "/petwh", pszBuff ) )
	{
		GetParameterString( pszBuff, 1, szCommandParam1 );

		// No have name?
		if ( szCommandParam1[0] == 0 )
			return TRUE;

		FOLLOWUNITHANDLER->SpawnUnit( pcUser, szCommandParam1 );
	}

	// Move
	if ( COMMAND( "/!getfield", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Mapa [%d]", pcUserData->iMapID );
			return TRUE;
		}
	}

	if ( COMMAND( "/debug", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			User * pcUser = USERDATATOUSER( pcUserData );
			if ( pcUser )
			{
				pcUser->bDebugChat = pcUser->bDebugChat ? FALSE : TRUE;
				CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Depuración [%s]", pcUser->bDebugChat ? "ACTIVADO" : "DESACTIVADO" );
				return TRUE;
			}
		}
	}

	if ( COMMAND( "/getclan", pszBuff ) )
	{
		// Is User Alive?
		if ( pcUserData )
		{
			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
			{
				UserData * pcUserClan = USERSERVER->GetUserdata( szCommandParam1 );
				if ( pcUserClan )
				{
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> Clan [%d]", pcUserClan->iClanID );
				}
			}
		}
		return TRUE;
	}

	return FALSE;
}

BOOL ServerCommand::OnPlayerCommand( UserData * pcUserData, const char * pszBuff )
{
	int iLen = 0, iLen2 = 0;

	char szCommandParam1[256] = { 0 };
	char szCommandParam2[256] = { 0 };
	char szCommandParam3[256] = { 0 };
	char szCommandParam4[256] = { 0 };
	char szCommandParam5[256] = { 0 };

	User * pcUser = USERDATATOUSER( pcUserData );

	if( GAME_SERVER )
	{
		//Emote Commands
		if( pszBuff[0] == 'e' && isdigit(pszBuff[1]) && lstrlenA(pszBuff) < 4 )
		{
			CHATSERVER->SendUserBoxChatRange( pcUser->pcUserData->sPosition.iX, pcUser->pcUserData->sPosition.iZ, 0x4B000, pcUser->GetID(), pszBuff );
			return TRUE;
		}

		//Party Chat
		if( pszBuff[0] == '@' )
		{
			if( pcUser )
			{
				if( (pcUser->bParty && pcUser->psParty) && pcUser->psParty->pcLeader )
				{
					std::string str( pszBuff );
					str.erase( 0, 1 );

					PARTYHANDLER->SendChatParty( pcUser, FormatString("%s: %s", pcUser->pcUserData->sCharacterData.szName, str.c_str()), CHATCOLOR_Party );

                    CHATSERVER->SQLLogChat( pcUser->iAccountID, pcUser->iCharacterID, 0, 0,
                        CHATCOLOR_Party, str, pcUser->pcUserData->pcSocketData->szIP, "45.40.99.104" );
				}
			}
			return TRUE;
		}
		else if( pszBuff[0] == '#' )
		{
			if( pcUser )
			{
				if( (pcUser->bParty && pcUser->psParty) && pcUser->psParty->pcLeader && pcUser->psParty->iRaidCount > 0 )
				{
					std::string str( pszBuff );
					str.erase( 0, 1 );

					PARTYHANDLER->SendChatRaid( pcUser, FormatString( "%s: %s", pcUser->pcUserData->sCharacterData.szName, str.c_str() ), CHATCOLOR_Raid );

                    CHATSERVER->SQLLogChat( pcUser->iAccountID, pcUser->iCharacterID, 0, 0,
                        CHATCOLOR_Party, str, pcUser->pcUserData->pcSocketData->szIP, "45.40.99.104" );
				}
			}
			return TRUE;
		}

		if ( COMMAND( "/request_party", pszBuff ) || COMMAND( "/party", pszBuff ) || COMMAND( "//party", pszBuff ) || COMMAND( "//PARTY", pszBuff ) )
		{
			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
			{
				UserData * pcUserDataParty = USERSERVER->GetUserdata( szCommandParam1 );

				if ( pcUserDataParty )
					PARTYHANDLER->HandlePacket( USERDATATOUSER( pcUserData ), &PacketRequestParty( pcUserDataParty->iID ) );
			}
		}
		else if ( COMMAND( "/request_raid", pszBuff ) || COMMAND( "/raid", pszBuff ) || COMMAND( "//raid", pszBuff ) || COMMAND( "//RAID", pszBuff ) )
		{
			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
			{
				UserData * pcUserDataRaid = USERSERVER->GetUserdata( szCommandParam1 );

				if ( pcUserDataRaid )
					PARTYHANDLER->HandlePacket( USERDATATOUSER( pcUserData ), &PacketRequestRaid( pcUserDataRaid->iID ) );
			}
		}
		else if( COMMAND( "/leave_party", pszBuff ) )
		{
			User * u = USERDATATOUSER( pcUserData );

			if( u )
				if( u->bParty && u->psParty )
					PARTYHANDLER->LeaveParty( u );
		}
		else if( COMMAND( "/lot", pszBuff ) || COMMAND( "/lottery", pszBuff ) )
		{
			User * u = USERDATATOUSER( pcUserData );

			if( u )
			{
				if( u->bParty && u->psParty )
				{
					UINT uRandom = RandomU( 0, 1000 );
					PARTYHANDLER->SendChatParty( u, FormatString( "> %s jugó a la lotería y obtuvo %d puntos.", u->pcUserData->sCharacterData.szName, uRandom ), CHATCOLOR_Notice, true );
				}
			}
		}
		else if ( COMMAND( "/kick_party", pszBuff ) )
		{
			if ( GetParameterString( pszBuff, 1, szCommandParam1 ) )
			{
				UserData * pcUserDataParty = USERSERVER->GetUserdata( szCommandParam1 );

				if ( pcUserDataParty )
				{
					User * u = USERDATATOUSER( pcUserData );
					User * uParty = USERDATATOUSER( pcUserDataParty );

					if ( u && uParty )
					{
						if ( u->bParty && u->psParty && uParty->bParty && uParty->psParty )
							if ( u->psParty == uParty->psParty )
								if ( u->psParty->pcLeader == u )
									PARTYHANDLER->LeaveParty( USERDATATOUSER( pcUserDataParty ), true );
					}
				}
			}
		}
		else if ( COMMAND( "/coins", pszBuff ) )
		{
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Global, "> Tienes %d monedas.", COINSHOPHANDLER->GetCoinAmount( COINSHOPHANDLER->GetCoinShop(), pcUser->pcUserData->szAccountName ) );
		}
		else if ( COMMAND( "/timepoints", pszBuff ) )
		{
			CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Global, "> Tienes %d puntos de tiempo.", COINSHOPHANDLER->GetTimePointAmount( pcUser->pcUserData->szAccountName ) );
		}
	}

	if ( iLen = COMMAND( "/CLAN>", pszBuff ) )
	{
		if ( pcUserData->iClanID != 0 )
		{
			BOOL bFound = FALSE;

			for ( int i = iLen; i < 100; i++ )
			{
				if ( pszBuff[i] == 0 )
					break;

				if ( pszBuff[i] != ' ' )
				{
					iLen = i;
					bFound = TRUE;
					break;
				}


			}
			if ( bFound )
			{
				EChatColor eColor = CHATCOLOR_Clan;

				if ( CHARACTERSERVER->IsCharacterLeader( USERDATATOUSER( pcUserData ) ) )
					eColor = CHATCOLOR_ClanLeader;

				CHATSERVER->SendChatAllUsersInClan( pcUserData, eColor,  "[%c]%s: %s", CHARACTERSERVER->GetServerName( USERDATATOUSER( pcUserData ) )[0], CHARACTERSERVER->GetCharacterName( pcUserData ), pszBuff+iLen );
				CHATSERVER->SendChatEx( pcUser, eColor, "[%c]%s: %s", CHARACTERSERVER->GetServerName( USERDATATOUSER( pcUserData ) )[0], CHARACTERSERVER->GetCharacterName( pcUserData ), pszBuff+iLen );

                CHATSERVER->SQLLogChat( pcUser->iAccountID, pcUser->iCharacterID, 0, 0,
                    eColor, pszBuff + iLen, pcUser->pcUserData->pcSocketData->szIP, "45.40.99.104" );
			}
			
		}
		return TRUE;
	}

	if( LOGIN_SERVER )
	{
		if( COMMAND("/TRADE>", pszBuff) )
			CHATSERVER->SendChatTrade( pcUserData, pszBuff );
		else if( pszBuff[0] == '/' && ( pszBuff[1] == ';' || pszBuff[1] == ':' ) )
		{
			if( fnGetParamOld( szCommandParam1, (char*)&pszBuff[2] ) )
			{
				UserData * ud = fnGetUsedataLoginName( szCommandParam1 );
				if( ud )
					CHATSERVER->SendWhisper( pcUser, USERDATATOUSER( ud ), &pszBuff[lstrlenA( szCommandParam1 ) + 2] );
				else
					CHATSERVER->SendChatEx( pcUser, CHATCOLOR_Error, "> %s está desconectado o no fue encontrado!", szCommandParam1 );
			}
		}
	}

	return FALSE;
}

BOOL ServerCommand::OnGameMasterCommand( UserData * pcUserData, const char * pszBuff )
{
	int iLen = 0;

	// Game master activate
	if ( iLen = COMMAND( "/activategm", pszBuff ) )
	{
		OnActivateGameMaster( pcUserData );
		return TRUE;
	}
	// Game master deactivate
	if ( iLen = COMMAND( "/deactivategm", pszBuff ) )
	{
		if ( pcUserData )
		{
			// Send server information to user debug
			PacketSimple sPacket;
			sPacket.iLength	= sizeof( PacketSimple );
			sPacket.iHeader = PKTHDR_DisableGM;
			SENDPACKET( USERDATATOUSER(pcUserData), &sPacket );
			
		}
		return TRUE;
	}

	// Game Master Commands
	if ( pcUserData )
	{
		if ( pcUserData->iGameLevel > GAMELEVEL_One )	// Level 2
			OnGameMasterEventCommand( pcUserData, pszBuff );
		if ( pcUserData->iGameLevel > GAMELEVEL_Three )		// Level 4 (Admin)
			OnGameMasterAdminCommand( pcUserData, pszBuff );
	}

	return FALSE;
}

BOOL ServerCommand::OnReceiveChat( UserData * pcUserData, PacketChat * psPacket )
{
	BOOL bRet = FALSE;

	if( OnPlayerCommand( pcUserData, psPacket->szChat ) )
		bRet = TRUE;
	
	if( OnGameMasterCommand( pcUserData, psPacket->szChat ) )
		bRet = TRUE;

	return bRet;
}

void ServerCommand::CheckUserOnline( UserData * pcUserData, struct PacketUserOnline * psPacket )
{
	UserData * pcUserOn = fnGetUsedataLoginName( psPacket->szName );
	if ( pcUserOn )
		psPacket->bOnline = TRUE;
	else
		psPacket->bOnline = FALSE;

	SENDPACKET( USERDATATOUSER( pcUserData ), psPacket, TRUE );

	CHATSERVER->SendDebugChat( pcUserData, CHATCOLOR_Error, "> VerificarUsuarioEnLinea( %s ) [%s]", psPacket->szName, psPacket->bOnline ? "TRUE" : "FALSE" );
}

void ServerCommand::AddCommand( int iCommandID, const char * pszParameter1, const char * pszParameter2, const char * pszParameter3 )
{
	SQLConnection * pcDB = SQLCONNECTION( DATABASEID_ServerDB );

	if ( pcDB->Open() )
	{
		if ( pcDB->Prepare( "INSERT INTO Command([CommandTypeID],[Parameter1],[Parameter2],[Parameter3],[DateProcessed]) VALUES(?,?,?,?,NULL)" ) )
		{
			pcDB->BindParameterInput( 1, PARAMTYPE_Integer, &iCommandID );
			pcDB->BindParameterInput( 2, PARAMTYPE_String, pszParameter1, STRLEN( pszParameter1 ) );
			pcDB->BindParameterInput( 3, PARAMTYPE_String, pszParameter2, STRLEN( pszParameter2 ) );
			pcDB->BindParameterInput( 4, PARAMTYPE_String, pszParameter3, STRLEN( pszParameter3 ) );

			pcDB->Execute();
		}

		pcDB->Close();
	}
}


