#include "stdafx.h"
#include "PremiumModel.h"
#include "CPremiumHandler.h"



CPremiumModel::CPremiumModel()
{
}


CPremiumModel::~CPremiumModel()
{
}

DWORD CPremiumModel::GetPremiumTime( EItemID eID )
{
	DWORD dwTotalTime = 0;

	switch ( eID )
	{	
		case ITEMID_ExpUp1H:
		case ITEMID_ThirdEye1H:
			dwTotalTime = (60 * 60);
			break;

		case ITEMID_ExpUp24H:
		case ITEMID_ThirdEye24H:
			dwTotalTime = (60 * 60 * 24);
			break;

		case ITEMID_ExpUp48H:
		case ITEMID_ThirdEye48H:
			dwTotalTime = (60 * 60 * 48);
			break;
		case ITEMID_PhoenixFire:
		case ITEMID_PhoenixIce:
		case ITEMID_PhoenixHealing:
		case ITEMID_PhoenixLightning:
		case ITEMID_BCBuff:
			dwTotalTime = (60 * 60 * 72);
			break;

		case ITEMID_ExpUp72H:
		case ITEMID_ThirdEye72H:
		case ITEMID_GravityStone72H:
			dwTotalTime = (60 * 60 * 72);
			break;

		case ITEMID_MPDown12H:
		case ITEMID_SPDown12H:
		case ITEMID_MPUp12H:
		case ITEMID_HPUp12H:
		case ITEMID_CartolaHat:
		case ITEMID_WitchHat:
		case ITEMID_SheepHat:
		case ITEMID_HairHelmetNew:
		case ITEMID_GiraffeHat:
		case ITEMID_SoccerHat:
		case ITEMID_XMasRedHat:
		case ITEMID_XMasGreenHat:
			dwTotalTime = (60 * 60 * 12);
			break;

		case ITEMID_BigHeadHappyness:
		case ITEMID_BigHeadLove:
		case ITEMID_BigHeadSadness:
		case ITEMID_BigHeadShyness:
		case ITEMID_BigHeadAngry:
		case ITEMID_BigHeadSensual:
		case ITEMID_BigHeadSurprised:
			dwTotalTime = (60 * 60 * 3);
			break;

		default:
			break;
	}
	return dwTotalTime;
}

EItemTimerType CPremiumModel::GetPremiumType( EItemID eID )
{
	EItemTimerType eType = (EItemTimerType)0;
	switch ( eID )
	{
		case ITEMID_ExpUp1H:
		case ITEMID_ExpUp24H:
		case ITEMID_ExpUp48H:
		case ITEMID_ExpUp72H:
			eType = ITEMTIMERTYPE_ExpUp;
			break;
		case ITEMID_ThirdEye1H:
		case ITEMID_ThirdEye24H:
		case ITEMID_ThirdEye48H:
		case ITEMID_ThirdEye72H:
			eType = ITEMTIMERTYPE_ThirdEye;
			break;
		case ITEMID_MPDown12H:
			eType = ITEMTIMERTYPE_MPDown;
			break;
		case ITEMID_SPDown12H:
			eType = ITEMTIMERTYPE_SPDown;
			break;
		case ITEMID_MPUp12H:
			eType = ITEMTIMERTYPE_MPUp;
			break;
		case ITEMID_HPUp12H:
			eType = ITEMTIMERTYPE_HPUp;
			break;
		case ITEMID_TopazStone:
		case ITEMID_TurquoiseStone:
			eType = ITEMTIMERTYPE_MatureStone;
			break;
		case ITEMID_EmeraldStone:
		case ITEMID_RubyStone:
			eType = ITEMTIMERTYPE_SkillStone;
			break;
		case ITEMID_CartolaHat:
			eType = ITEMTIMERTYPE_CartolaHat;
			break;
		case ITEMID_WitchHat:
			eType = ITEMTIMERTYPE_WitchHat;
			break;
		case ITEMID_SheepHat:
			eType = ITEMTIMERTYPE_SheepHat;
			break;
		case ITEMID_HairHelmetNew:
			eType = ITEMTIMERTYPE_HairHelmetNew;
			break;			
		case ITEMID_GiraffeHat:
			eType = ITEMTIMERTYPE_GiraffeHat;
			break;
		case ITEMID_SoccerHat:
			eType = ITEMTIMERTYPE_SoccerHat;
			break;
		case ITEMID_XMasGreenHat:
			eType = ITEMTIMERTYPE_XMasGreenHat;
			break;
		case ITEMID_XMasRedHat:
			eType = ITEMTIMERTYPE_XMasRedHat;
			break;
		case ITEMID_PhoenixFire:
			eType = ITEMTIMERTYPE_PhoenixFire;
			break;
		case ITEMID_PhoenixIce:
			eType = ITEMTIMERTYPE_PhoenixIce;
			break;
		case ITEMID_PhoenixLightning:
			eType = ITEMTIMERTYPE_PhoenixLightning;
			break;
		case ITEMID_PhoenixHealing:
			eType = ITEMTIMERTYPE_PhoenixHeal;
			break;
		case ITEMID_GravityStone72H:
			eType = ITEMTIMERTYPE_WeightStone;
			break;
		case ITEMID_BigHeadHappyness:
			eType = ITEMTIMERTYPE_BigHeadHappiness;
			break;
		case ITEMID_BigHeadLove:
			eType = ITEMTIMERTYPE_BigHeadLove;
			break;
		case ITEMID_BigHeadSadness:
			eType = ITEMTIMERTYPE_BigHeadSadness;
			break;
		case ITEMID_BigHeadShyness:
			eType = ITEMTIMERTYPE_BigHeadShyness;
			break;
		case ITEMID_BigHeadAngry:
			eType = ITEMTIMERTYPE_BigHeadAngry;
			break;
		case ITEMID_BigHeadSurprised:
			eType = ITEMTIMERTYPE_BigHeadSurprised;
			break;
		case ITEMID_BigHeadSensual:
			eType = ITEMTIMERTYPE_BigHeadSensual;
			break;
		case ITEMID_BCBuff:
			eType = ITEMTIMERTYPE_BCBuff;
			break;
		default:
			break;
	}
	return eType;
}

BOOL CPremiumModel::IsHeadPremium( EItemID eID )
{
	BOOL bRet = FALSE;
	switch ( eID )
	{
		case ITEMID_CartolaHat:
		case ITEMID_WitchHat:
		case ITEMID_GiraffeHat:
		case ITEMID_HairHelmetNew:
		case ITEMID_SheepHat:
		case ITEMID_SoccerHat:
		case ITEMID_XMasGreenHat:
		case ITEMID_XMasRedHat:
		case ITEMID_HairPotionA:
		case ITEMID_HairPotionB:
		case ITEMID_HairPotionC:
		case ITEMID_HairPotionD:
		case ITEMID_HairPotionE:
		case ITEMID_HairPotionF:
		case ITEMID_HairPotionG:
		case ITEMID_HairPotionH:
		case ITEMID_HairPotionI:
		case ITEMID_HairPotionJ:
		case ITEMID_HairPotionK:
		case ITEMID_HairPotionL:
		case ITEMID_HairPotionM:
		case ITEMID_HairPotionN:
		case ITEMID_HairPotionO:
		case ITEMID_HairPotionP:
		case ITEMID_HairPotionQ:
		case ITEMID_HairPotionR:
		case ITEMID_HairPotionS:
		case ITEMID_BigHeadHappyness:
		case ITEMID_BigHeadLove:
		case ITEMID_BigHeadSadness:
		case ITEMID_BigHeadShyness:
		case ITEMID_BigHeadAngry:
		case ITEMID_BigHeadSensual:
		case ITEMID_BigHeadSurprised:
			bRet = TRUE;
			break;

		default:
			break;
	}
	return bRet;
}

PremiumInfoData * CPremiumModel::GetPremiumInfo( EItemTimerType eID )
{
	for ( int i = 0; i < PREMIUM_ITEM_TOTAL; i++ )
	{
		if ( psaPremiumInfoData[i] && psaPremiumInfoData[i]->eType == eID )
			return psaPremiumInfoData[i];
	}
	return NULL;
}

ItemPremium * CPremiumModel::GetPremium( EItemID eID )
{
	for ( int i = 0; i < PREMIUM_ITEM_TOTAL; i++ )
	{
		if ( PREMIUMHANDLER->GetData()->saItemList[ i ].dwCode == eID )
			return &PREMIUMHANDLER->GetData()->saItemList[ i ];
	}
	return NULL;
}

PremiumResource * CPremiumModel::GetResource( EItemTimerType eType )
{
	for ( int i = 0; i < PREMIUM_ITEM_TOTAL; i++ )
	{
		if ( psaPremiumResource[ i ].eType && psaPremiumResource[ i ].eType == eType )
			return &psaPremiumResource[ i ];
	}
	return NULL;
}

PremiumResource * CPremiumModel::GetResource( EItemID eID )
{
	for ( int i = 0; i < PREMIUM_ITEM_TOTAL; i++ )
	{
		if ( psaPremiumResource[ i ].dwCode && psaPremiumResource[ i ].dwCode == eID )
			return &psaPremiumResource[ i ];
	}
	return NULL;
}

void CPremiumModel::SetTimeFunction( DWORD pdwTime, int iTime )
{
	if ( *(DWORD*)pdwTime <= 0 )
		*(DWORD*)pdwTime = iTime;
}

void CPremiumModel::SetPremiumFunction( EItemID eID, EItemTimerType eType, int iTimeLeft )
{
	switch ( eType )
	{
		case ITEMTIMERTYPE_MPDown:
			SetTimeFunction( pdwMPDownTime, iTimeLeft / 1000 );
			WRITEDWORD( pdwMPDownPercent, dwMPDownPercent );
			break;
		case ITEMTIMERTYPE_SPDown:
			SetTimeFunction( pdwSPDownTime, iTimeLeft / 1000 );
			WRITEDWORD( pdwSPDownPercent, dwSPDownPercent );
			break;

		case ITEMTIMERTYPE_WeightStone:
			SetTimeFunction( pdwGravityStnTime, iTimeLeft / 1000 );
			WRITEDWORD( pdwGravityStnAdd, dwGravityStnAdd );
			break;

		default:
			break;
	}
}

void CPremiumModel::SetPhoenix( DWORD dwCode )
{
	EItemID eID = (EItemID)dwCode;

	tfnPhoenix pFunction = (tfnPhoenix)pfnSetPhoenix;

	switch ( eID )
	{
		case ITEMID_PhoenixFire:
			(*(DWORD*)pActivePhoenix) = PHOENIXTYPEID_Fire;
			pFunction( pcPhoenix );
			*(BOOL*)(bShowPhoenixPet) = TRUE;
			break;
		case ITEMID_PhoenixIce:
			(*(DWORD*)pActivePhoenix) = PHOENIXTYPEID_Ice;
			pFunction( pcPhoenix );
			*(BOOL*)(bShowPhoenixPet) = TRUE;
			break;
		case ITEMID_PhoenixLightning:
			(*(DWORD*)pActivePhoenix) = PHOENIXTYPEID_Lightning;
			pFunction( pcPhoenix );
			*(BOOL*)(bShowPhoenixPet) = TRUE;
			break;
		case ITEMID_PhoenixHealing:
			(*(DWORD*)pActivePhoenix) = PHOENIXTYPEID_Healing;
			pFunction( pcPhoenix );
			*(BOOL*)(bShowPhoenixPet) = TRUE;
			break;
		default:
			break;
	}
}

void CPremiumModel::SetPremiumServer( PacketActivePremium * psPacket )
{
	// Set Premium
	for ( int i = 0; i < PREMIUM_ITEM_TOTAL; i++ )
	{
		if ( !PREMIUMHANDLER->GetData()->saItemList[i].dwCode )
		{
			DWORD dwTime = GetPremiumTime( (EItemID)psPacket->sPremium.dwCode ) * 1000;
			PREMIUMHANDLER->GetData()->saItemList[i].dwCode = psPacket->sPremium.dwCode;
			PREMIUMHANDLER->GetData()->saItemList[i].dwTimeLeft = psPacket->sPremium.dwTimeLeft * 1000;
			PREMIUMHANDLER->GetData()->saItemList[i].dwTimeTotal = psPacket->sPremium.dwTimeLeft * 1000;
			PREMIUMHANDLER->GetData()->saItemList[i].eType = GetPremiumType( (EItemID)psPacket->sPremium.dwCode );

			// Phoenix Pet
			SetPhoenix( psPacket->sPremium.dwCode );

			break;
		}
	}
}

BOOL CPremiumModel::IsUsingHeadPremium()
{
	// Found Item?
	for ( int i = 0; i < PREMIUM_ITEM_TOTAL; i++ )
	{
		if ( IsHeadPremium( (EItemID)PREMIUMHANDLER->GetData()->saItemList[ i ].dwCode ) && PREMIUMHANDLER->GetData()->saItemList[ i ].dwTimeLeft )
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPremiumModel::SetPremiumSlot( EItemID eID )
{

	if ( XMASHANDLER->IsPremiumXMas( eID ) )
	{
		(*(DWORD*)0x362BEA4) = TRUE;
		return TRUE;
	}

	//Easter Egg
	if ( eID == ITEMID_RedEasterEgg || eID == ITEMID_GreenEasterEgg || eID == ITEMID_PinkEasterEgg )
		return TRUE;

	// Got type?
	EItemTimerType eType = GetPremiumType( eID );
	
	PremiumInfoData * psInfo = GetPremiumInfo( eType );

	BOOL bIsHeadPremium = IsHeadPremium( eID );

	if ( !eType )
	{
		if ( eID == ITEMID_PhoenixEgg )
		{
			if ( *(BOOL*)(bShowPhoenixPet) )
			{
				(*(DWORD*)0x362BEA4) = FALSE;
				TITLEBOX( "\241Ya est\341s usando un \355tem de este tipo!" );
				return TRUE;
			}
			(*(DWORD*)0x362BEA4) = TRUE;
			return TRUE;
		}

		if ( HALLOWEENHANDLER->IsLantern( (EItemID)eID ) )
		{
			ItemData * psItemData = ITEMHANDLER->FindItemTableByCode( ITEMID_VampireSuit );
			if ( psItemData )
			{
				// Check iWeight
				if ( !CHARACTERGAME->CheckInventoryWeight( psItemData ) )
				{
					TITLEBOX( "L\355mite de peso excedido" );
					return TRUE;
				}

				// Check Space
				if ( !CHARACTERGAME->CheckInventorySpace( psItemData ) )
				{
					TITLEBOX( "No hay suficiente espacio en el inventario" );
					return TRUE;
				}
			}
			(*(DWORD*)0x362BEA4) = TRUE;
			return TRUE;
		}
		if ( !bIsHeadPremium )
			return FALSE;

		eType = ITEMTIMERTYPE_BigHead;
	}
	// Found Item?
	for ( int i = 0; i < PREMIUM_ITEM_TOTAL; i++ )
	{
		// Repeat Use?
		if ( psInfo && psInfo->bRepeatUse )
			break;

		// Mismatch item type?
		if ( PREMIUMHANDLER->GetData()->saItemList[ i ].eType == eType )
		{
			TITLEBOX( "\241Ya est\341s usando un \355tem de este tipo!" );
			return TRUE;
		}
	}

	if ( bIsHeadPremium && IsUsingHeadPremium() )
	{
		TITLEBOX( "\241Ya est\341s usando un \355tem de este tipo!" );
		return TRUE;
	}

	// Set Premium
	for ( int i = 0; i < PREMIUM_ITEM_TOTAL; i++ )
	{
		// Is repeat use or free slot?
		if ( (psInfo && psInfo->bRepeatUse && PREMIUMHANDLER->GetData()->saItemList[ i ].eType == psInfo->eType ) || (!PREMIUMHANDLER->GetData()->saItemList[ i ].dwCode) )
		{	
			// Not have Required Level? Send message and break
			if ( psInfo && (int)psInfo->iLevel > UNITDATA->sCharacterData.iLevel )
			{
				TITLEBOX( "\241Se requiere nivel %d para usar este \355tem!", psInfo->iLevel );
				return TRUE;
			}

			// Only Server?
			if ( psInfo && psInfo->bUseServer )
			{
				// Set Phoenix is in server, no need set
				(*(DWORD*)0x362BEA4) = TRUE;
				return TRUE;
			}

			// Big Head?
			if ( bIsHeadPremium )
			{
				if ( eID == ITEMID_CartolaHat || eID == ITEMID_WitchHat )
				{
					BOOL bRet = TRUE;
					int iJC = UNITDATA->sCharacterData.iClass;

					if ( eID == ITEMID_CartolaHat )
					{ 
						if ( iJC == CHARACTERCLASS_Assassin || iJC == CHARACTERCLASS_Archer || iJC == CHARACTERCLASS_Atalanta || iJC == CHARACTERCLASS_Priestess )
							bRet = FALSE;
					}
					if ( eID == ITEMID_WitchHat )
					{ 
						if ( iJC == CHARACTERCLASS_Fighter || iJC == CHARACTERCLASS_Mechanician || iJC == CHARACTERCLASS_Pikeman || iJC == CHARACTERCLASS_Knight ||
							 iJC == CHARACTERCLASS_Magician || iJC == CHARACTERCLASS_Shaman )
							bRet = FALSE;
					}
					if ( !bRet )
					{
						(*(DWORD*)0x362BEA4) = FALSE;
						TITLEBOX( "\241No puedes usar este \355tem!" );
						return TRUE;
					}
				}
				ITEMHANDLER->OnSetHairModel( eID );
			}
			// Mature Stone?
			if ( eType == ITEMTIMERTYPE_MatureStone )
			{
				if ( !ITEMHANDLER->OnMatureStone( eID ) )
				{
					(*(DWORD*)0x362BEA4) = FALSE;
					TITLEBOX( "\241No tienes \355tems para madurar!" );
					return TRUE;
				}
				(*(DWORD*)0x362BEA4) = TRUE;
				return TRUE;
			}
			// Skill Stone?
			if ( eType == ITEMTIMERTYPE_SkillStone )
			{
				if ( !ITEMHANDLER->OnSkillStone( eID ) )
				{
					(*(DWORD*)0x362BEA4) = FALSE;
					return TRUE;
				}
				(*(DWORD*)0x362BEA4) = TRUE;
				return TRUE;
			}

			DWORD dwTime = GetPremiumTime( eID ) * 1000;
			if ( dwTime != 0 )
			{
				// Set Item
				PREMIUMHANDLER->GetData()->saItemList[i].eType = eType;
				PREMIUMHANDLER->GetData()->saItemList[i].dwCode = eID;
				PREMIUMHANDLER->GetData()->saItemList[i].dwTimeLeft = dwTime;
				PREMIUMHANDLER->GetData()->saItemList[i].dwTimeTotal = dwTime;
			}
			(*(DWORD*)0x362BEA4) = TRUE;
			return TRUE;
		}
	}

	return FALSE;
}

void CPremiumModel::LoadPremiumImages()
{

}

char szDescriptionPremiumGlobal[512];

void CPremiumModel::RenderBox( ItemPremium * psItem, int iX, int iY )
{
	if ( Game::IsPoint2D( iX, iY, iPremiumWidth, iPremiumHeight ) )
	{
		PremiumInfoData * psInfo = GetPremiumInfo( psItem->eType );

		if ( psInfo )
		{
			// Render Box
			UI::ImageRender::Render( pHandlerPremiumBox, iX + iXRight + 2, iY - (iPremiumBoxHeight >> 1) + (iPremiumHeight >> 1), iPremiumBoxWidth, iPremiumBoxHeight, D3DCOLOR_ARGB( 255, 255, 255, 255 ) );

			// Set Text
			FONTHANDLER->Draw( 0, iX + iXRight + 2 + 12, iY - (iPremiumBoxHeight >> 1) + (iPremiumHeight >> 1) + 5, psInfo->szTitle,DT_WORDBREAK, D3DCOLOR_ARGB( 255, 222, 231, 255 ) );
			
			lstrcpyA( szDescriptionPremiumGlobal, psInfo->szDescription );

			for ( int i = 0; i < 512; i++ )
			{
				if ( szDescriptionPremiumGlobal[i] == '\0' )
					break;
				if ( szDescriptionPremiumGlobal[i] == '\r' )
				{
					szDescriptionPremiumGlobal[i] = '\n';
				}
			}

			FONTHANDLER->Draw( 0, iX + iXRight + 2 + 12, iY - (iPremiumBoxHeight >> 1) + (iPremiumHeight >> 1) + 4 + 16, szDescriptionPremiumGlobal, DT_WORDBREAK, D3DCOLOR_ARGB( 255, 255, 255, 255 ) );

			char szBuf[128] = { 0 };
			int iHour	 = (psItem->dwTimeLeft / 1000) / 3600;
			int iMinutes = ((psItem->dwTimeLeft / 1000) / 60) % 60;
			int iSeconds = (psItem->dwTimeLeft / 1000) % 60;
			STRINGFORMAT( szBuf, "Tiempo restante: %02d:%02d:%02d", iHour, iMinutes, iSeconds );
			FONTHANDLER->Draw( 0, iX + iXRight + 2 + 12, iY - (iPremiumBoxHeight >> 1) + (iPremiumHeight >> 1) + 2 + (16 * 3), szBuf, DT_WORDBREAK, D3DCOLOR_ARGB( 255, 0, 196, 0 ) );
		}
	}
}

PremiumInfoData * CPremiumModel::CreatePremiumDataInfo( PremiumInfoData * psPremiumData, EItemTimerType eType, int iLevel, const char szTitle[32], const char szDescription[64], BOOL bRepeatUse, BOOL bUseServer, const char * pszImage, const char * pszImageDisabled )
{

	psPremiumData->eType			= eType;
	psPremiumData->iLevel			= iLevel;
	psPremiumData->bUseServer		= bUseServer;
	psPremiumData->bRepeatUse		= bRepeatUse;
	psPremiumData->pImage			= UI::ImageLoader::LoadImage( pszImage );
	psPremiumData->pDisabledImage   = UI::ImageLoader::LoadImage( pszImageDisabled );
	psPremiumData->iAlpha			= 0;

	STRINGCOPY( psPremiumData->szTitle, szTitle );
	STRINGCOPY( psPremiumData->szDescription, szDescription );

	return psPremiumData;
}

char * CPremiumModel::OnDescription( DWORD dwCode )
{

	return NULL;
}

BOOL CPremiumModel::SetPremium( EItemID eID )
{
	if ( SetPremiumSlot( eID ) )
		return TRUE;

	return ITEMHANDLER->OnSetHairModel( (DWORD)eID );
}

void CPremiumModel::Update( float fTime )
{

	for ( int i = 0; i < PREMIUM_ITEM_TOTAL; i++ )
	{
		// Item set and have time?
		if ( PREMIUMHANDLER->GetData()->saItemList[i].dwCode && PREMIUMHANDLER->GetData()->saItemList[i].dwTimeLeft )
		{
			EItemTimerType eType = PREMIUMHANDLER->GetData()->saItemList[i].eType;
			PremiumInfoData * psPremiumInfo = GetPremiumInfo( eType );

			if ( psPremiumInfo && psPremiumInfo->iAlpha < 255 )
			{
				psPremiumInfo->iAlpha += 1;
				if ( psPremiumInfo->iAlpha > 255 )
					psPremiumInfo->iAlpha = 255;
			}

			if ( !CHARACTERGAME->IsStageVillage() )
			{
				if ( eType == ITEMTIMERTYPE_ExpUp || eType == ITEMTIMERTYPE_ThirdEye )
				{
					if ( CHARACTERGAME->GetStageID() == 33 )
						continue;
				}
				PREMIUMHANDLER->GetData()->saItemList[i].dwTimeLeft -= 100;
			}
			
			if ( PREMIUMHANDLER->GetData()->saItemList[i].dwTimeLeft <= 999 )
				{
					if ( IsHeadPremium( (EItemID)PREMIUMHANDLER->GetData()->saItemList[i].dwCode ) )
					{
						CHARACTERGAME->ResetHead();
					}

					DWORD dwCode = PREMIUMHANDLER->GetData()->saItemList[i].dwCode;

					if ( dwCode == ITEMID_PhoenixFire || dwCode == ITEMID_PhoenixIce || dwCode == ITEMID_PhoenixHealing || dwCode == ITEMID_PhoenixLightning )
						*(BOOL*)(bShowPhoenixPet) = FALSE;

					ZeroMemory( &PREMIUMHANDLER->GetData()->saItemList[i], sizeof( ItemPremium ) );
					if ( psPremiumInfo )
						psPremiumInfo->iAlpha = 0;
				}

			SetPremiumFunction( (EItemID)PREMIUMHANDLER->GetData()->saItemList[i].dwCode, PREMIUMHANDLER->GetData()->saItemList[i].eType, PREMIUMHANDLER->GetData()->saItemList[i].dwTimeLeft );
			if ( *(BOOL*)(bShowPhoenixPet) == FALSE )
				SetPhoenix( PREMIUMHANDLER->GetData()->saItemList[i].dwCode );
		}
	}
}

BOOL CPremiumModel::OnMouseClick( CMouse * pcMouse )
{
	return FALSE;
}

void CPremiumModel::OnDraw()
{
	int iCount	= 0;
	int iX		= iXBegin;
	int	iY		= iYBegin;
	for ( int i = 0; i < PREMIUM_ITEM_TOTAL; i++ )
	{
		// Item set and have time?
		if ( PREMIUMHANDLER->GetData()->saItemList[ i ].dwCode && PREMIUMHANDLER->GetData()->saItemList[ i ].dwTimeLeft )
		{
			PremiumInfoData * psPremiumInfo = GetPremiumInfo( PREMIUMHANDLER->GetData()->saItemList[i].eType );

			// Black Image iHeight
			DWORD dwMaxTime = GetPremiumTime( (EItemID)PREMIUMHANDLER->GetData()->saItemList[i].dwCode );
			DWORD dwHeight  = (((PREMIUMHANDLER->GetData()->saItemList[i].dwTimeLeft / 1000) * iPremiumHeight) / dwMaxTime);
			
			UI::ImageRender::Render( psPremiumInfo->pImage, iX, iY, iPremiumWidth, iPremiumHeight, 0, 0, D3DCOLOR_ARGB( psPremiumInfo->iAlpha, 255, 255, 255 ) );

			// ViewPort Image
			{
				if ( psPremiumInfo->iAlpha )
				{
					if ( PREMIUMHANDLER->GetData()->saItemList[i].dwTimeLeft != dwMaxTime )
						UI::ImageRender::Render( psPremiumInfo->pDisabledImage, iX, iY, iPremiumWidth, iPremiumHeight - dwHeight, 0, 0, D3DCOLOR_ARGB( psPremiumInfo->iAlpha, 255, 255, 255 ) );
				}
			}
			iY += iYDown;
				
			iCount++;
			// Is Next wall?
			if ( iCount == iCountWall )
			{
				// Reset position to next wall
				iX += iXRight;
				iY = iYBegin;
				iCount = 0;
			}
		}
	}

	// Box
	iCount = 0;
	iX = iXBegin;
	iY = iYBegin;
	for ( int i = 0; i < PREMIUM_ITEM_TOTAL; i++ )
	{
		// Item set and have time?
		if ( PREMIUMHANDLER->GetData()->saItemList[ i ].dwCode && PREMIUMHANDLER->GetData()->saItemList[ i ].dwTimeLeft )
		{
			// Box Description
			RenderBox( &PREMIUMHANDLER->GetData()->saItemList[ i ], iX, iY );
			iY += iYDown;
				
			iCount++;
			// Is Next wall?
			if ( iCount == iCountWall )
			{
				// Reset position to next wall
				iX += iXRight;
				iY = iYBegin;
				iCount = 0;
			}
		}
	}
}

void CPremiumModel::Init()
{
	pHandlerPremiumBox = UI::ImageLoader::LoadImage( "game\\images\\items\\premium\\box.png" );

	// Clear premiums
	for ( int i = 0; i < PREMIUM_ITEM_TOTAL; i++ )
		ZeroMemory( &PREMIUMHANDLER->GetData()->saItemList[ i ], sizeof( ItemPremium ) );

	// Clear Premium info
	for ( int i = 0; i < 50; i++ )
		psaPremiumInfoData[i] = NULL;


	int iCount						= 0;
	PremiumInfoData * psPremiumInfo = NULL;

	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_ExpUp, 0, "Poci\363n EXP", "30% de experiencia adicional", FALSE, FALSE, "game\\images\\items\\premium\\EXP.png", "game\\images\\items\\premium\\EXP_.png" );

	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_ThirdEye, 0, "Tercer Ojo", "Un bot\355n adicional", FALSE, FALSE, "game\\images\\items\\premium\\ThirdEye.png", "game\\images\\items\\premium\\ThirdEye_.png" );

	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_MPDown, 0, "Consumo de Man\341", "Reduce un 25% el consumo de man\341", FALSE, FALSE, "game\\images\\items\\premium\\MPDown.png", "game\\images\\items\\premium\\MPDown_.png" );

	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_MPUp, 0, "Aura de Man\341", "+10 de regeneraci\363n de man\341", FALSE, FALSE, "game\\images\\items\\premium\\MPUp.png", "game\\images\\items\\premium\\MPUp_.png" );

	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_HPUp, 0, "Dientes de Vampiro", "+10 de regeneraci\363n de HP", FALSE, FALSE, "game\\images\\items\\premium\\HPUp.png", "game\\images\\items\\premium\\HPUp_.png" );

	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_SPDown, 0, "Consumo de Estamina", "Reduce un 25% el consumo de estamina", FALSE, FALSE, "game\\images\\items\\premium\\SPDown.png", "game\\images\\items\\premium\\SPDown_.png" );
	
	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_CartolaHat, 0, "Sombrero de Mago", "+10 de regeneraci\363n de HP y +10 HP", FALSE, FALSE, "game\\images\\items\\premium\\MagicianHat.png", "game\\images\\items\\premium\\MagicianHat_.png" );
	
	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_WitchHat, 0, "Sombrero de Bruja", "+10 de regeneraci\363n de HP y +10 HP", FALSE, FALSE, "game\\images\\items\\premium\\WitchHat.png", "game\\images\\items\\premium\\WitchHat_.png" );
	
	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_PhoenixFire, 0, "F\351nix de Fuego", "Te ayuda con el da\361o", FALSE, FALSE, "game\\images\\items\\premium\\PhoenixFire.png", "game\\images\\items\\premium\\PhoenixFire_.png" );

	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_PhoenixIce, 0, "F\351nix de Hielo", "Te ayuda con el da\361o", FALSE, FALSE, "game\\images\\items\\premium\\PhoenixIce.png", "game\\images\\items\\premium\\PhoenixIce_.png" );
	
	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_PhoenixLightning, 0, "F\351nix de Rayo", "Te ayuda con el da\361o", FALSE, FALSE, "game\\images\\items\\premium\\PhoenixLightning.png", "game\\images\\items\\premium\\PhoenixLightning_.png" );
	
	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_PhoenixHeal, 0, "F\351nix de Curaci\363n", "Te cura", FALSE, FALSE, "game\\images\\items\\premium\\PhoenixHeal.png", "game\\images\\items\\premium\\PhoenixHeal_.png" );
	
	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_WeightStone, 0, "Piedra de Gravedad", "Otorga +1000 de peso", FALSE, FALSE, "game\\images\\items\\premium\\Gravity.png", "game\\images\\items\\premium\\Gravity_.png" );

	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_WeightStone, 0, "Piedra de Gravedad", "Otorga +1000 de peso", FALSE, FALSE, "game\\images\\items\\premium\\Gravity.png", "game\\images\\items\\premium\\Gravity_.png" );

	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_WeightStone, 0, "Piedra de Gravedad", "Otorga +1000 de peso", FALSE, FALSE, "game\\images\\items\\premium\\Gravity.png", "game\\images\\items\\premium\\Gravity_.png" );

	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_SheepHat, 0, "Sombrero de Oveja", "Tierno *-* +100 Defensa", FALSE, FALSE, "game\\images\\items\\premium\\SheepHat.png", "game\\images\\items\\premium\\SheepHat_.png" );

	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_HairHelmetNew, 0, "Casco de Realeza", "+100 Defensa\n+100 HP/MP/STM", FALSE, FALSE, "game\\images\\items\\premium\\Demon.png", "game\\images\\items\\premium\\Demon_.png" );

	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_GiraffeHat, 0, "Sombrero de Jirafa", "+50 \315ndice de Ataque", FALSE, FALSE, "game\\images\\items\\premium\\GiraffeHat.png", "game\\images\\items\\premium\\GiraffeHat_.png" );
	
	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_SoccerHat, 0, "Sombrero de F\372tbol", "+2 Velocidad de Movimiento", FALSE, FALSE, "game\\images\\items\\premium\\SoccerHat.png", "game\\images\\items\\premium\\SoccerHat_.png" );

	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_XMasGreenHat, 0, "Sombrero Navide\361o Verde", "+2 Velocidad de Movimiento", FALSE, FALSE, "game\\images\\items\\premium\\XmasHat.png", "game\\images\\items\\premium\\XmasHat_.png" );
	
	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_XMasRedHat, 0, "Sombrero Navide\361o Rojo", "+50 MP/STM", FALSE, FALSE, "game\\images\\items\\premium\\XmasHat.png", "game\\images\\items\\premium\\XmasHat_.png" );

	psPremiumInfo = new PremiumInfoData;
	if( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_BigHeadHappiness, 0, "Cabeza Grande de Felicidad", "+50 HP/MP/STM", FALSE, FALSE, "game\\images\\items\\premium\\BigHead.png", "game\\images\\items\\premium\\BigHead_.png" );
	
	psPremiumInfo = new PremiumInfoData;
	if( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_BigHeadLove, 0, "Cabeza Grande de Amor", "+10 de regeneraci\363n de HP y +10 HP", FALSE, FALSE, "game\\images\\items\\premium\\BigHead.png", "game\\images\\items\\premium\\BigHead_.png" );

	psPremiumInfo = new PremiumInfoData;
	if( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_BigHeadSadness, 0, "Cabeza Grande de Tristeza", "+2 Velocidad de Movimiento", FALSE, FALSE, "game\\images\\items\\premium\\BigHead.png", "game\\images\\items\\premium\\BigHead_.png" );

	psPremiumInfo = new PremiumInfoData;
	if( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_BigHeadShyness, 0, "Cabeza Grande de Timidez", "+2 \315ndice de Bloqueo", FALSE, FALSE, "game\\images\\items\\premium\\BigHead.png", "game\\images\\items\\premium\\BigHead_.png" );

	psPremiumInfo = new PremiumInfoData;
	if( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_BigHeadAngry, 0, "Cabeza Grande de Ira", "+50 \315ndice de Ataque", FALSE, FALSE, "game\\images\\items\\premium\\BigHead.png", "game\\images\\items\\premium\\BigHead_.png" );

	psPremiumInfo = new PremiumInfoData;
	if( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_BigHeadSurprised, 0, "Cabeza Grande de Sorpresa", "+100 Defensa", FALSE, FALSE, "game\\images\\items\\premium\\BigHead.png", "game\\images\\items\\premium\\BigHead_.png" );

	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_BigHeadSensual, 0, "Cabeza Grande Sensual", "+2 Cr\355tico", FALSE, FALSE, "game\\images\\items\\premium\\BigHead.png", "game\\images\\items\\premium\\BigHead_.png" );
	
	psPremiumInfo = new PremiumInfoData;
	if ( psPremiumInfo )
		psaPremiumInfoData[iCount++] = CreatePremiumDataInfo( psPremiumInfo, ITEMTIMERTYPE_BCBuff, 0, "Honor PvP", "+100 HP", FALSE, FALSE, "game\\images\\items\\premium\\TopPvp.png", "game\\images\\items\\premium\\TopPvp_.png" );
}
