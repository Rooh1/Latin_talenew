#include "stdafx.h"
#include "CGameWorld.h"



CGameWorld::CGameWorld()
{
	pcWorld = NULL;
}



BOOL CGameWorld::Init()
{
	ULONG ulFPT			= inet_addr( IP_FORTRESS_WORLD );
	ULONG ulFPTBeta		= inet_addr( IP_FORTRESS_BETA );
	ULONG ulFPTLocal	= inet_addr( "25.38.161.237" ); //25.38.161.237
	const char * pszClanWebHost = "25.38.161.237";
 
	vWorlds.push_back( new CWorld( WORLDID_None, "None", 0x00000000, 0, "", "", "", 0x00000000, 0x00000000 ) );
	vWorlds.push_back( new CWorld( WORLDID_Fortress, "Latin Tale", ulFPT, 10009, "Latin Tale", "FW", pszClanWebHost, ulFPT, ulFPT ) );
	vWorlds.push_back( new CWorld( WORLDID_Test, "Test", ulFPTBeta, 10009, "Latin Tale", "Latin Tale", pszClanWebHost, ulFPTBeta, ulFPTBeta ) );
	vWorlds.push_back( new CWorld( WORLDID_TestLocal, "TestLocal", ulFPTLocal, 10009, "Latin Tale", "Latin Tale", pszClanWebHost, ulFPTLocal, ulFPTLocal ) );

	SetWorld( WORLDID_Fortress );

	return TRUE;
}

void CGameWorld::Shutdown()
{
	for ( vector<CWorld*>::iterator it = vWorlds.begin(); it != vWorlds.end(); it++ )
	{
		CWorld * p = *it;

		DELET( p );
	}
	vWorlds.clear();

	pcWorld = NULL;
}

void CGameWorld::Apply()
{
	SOCKETGAME->SetIPPort( pcWorld->GetIP().c_str(), pcWorld->GetPort() );
}

void CGameWorld::SetWorld( EWorldID iWorldID )
{
	for ( vector<CWorld*>::iterator it = vWorlds.begin(); it != vWorlds.end(); it++ )
	{
		CWorld * p = *it;

		if ( p->GetWorldID() == iWorldID )
		{
			pcWorld = p;
			return;
		}
	}

	pcWorld = NULL;
}

void CGameWorld::SetWorld( string strWorld )
{
	for ( vector<CWorld*>::iterator it = vWorlds.begin(); it != vWorlds.end(); it++ )
	{
		CWorld * p = *it;

		if ( p->GetName().compare( strWorld ) == 0 )
		{
			pcWorld = p;
			return;
		}
	}

	SetWorld( WORLDID_None );
}
