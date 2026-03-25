#include "stdafx.h"
#include "gameeffectfollow.h"


NAKED void CGameEffectFollow::Constructor()
{
	JMP( pfnConstructor );
}

CGameEffectFollow::CGameEffectFollow()
{
	Constructor();
}


CGameEffectFollow::~CGameEffectFollow()
{
}

NAKED void CGameEffectFollow::Start( UnitData * pcUnitData, char * pszMeshName, char * pszParticleName, bool bAttack, int iTime )
{
	JMP( pfnStart );
}

void CGameEffectFollow::SetPositionLength( int i )
{
	iLength = i;
}

void CGameEffectFollow::SetScale( float f )
{
	fScale = f;
}

BOOL CGameEffectFollow::SetEffectUnitSpawn( UnitData * pcUnitData )
{
	BOOL bRet = FALSE;

	switch ( pcUnitData->sCharacterData.iMonsterEffectID )
	{
		case MONSTEREFFECTID_Arhdyra:
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip01 Spine", "ArhdyraBody", MONSTERFOLLOWEFFECT_ArhdyraBody );
			break;

		case MONSTEREFFECTID_Igniculus:
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip001 Spine", "IgniculusBody", MONSTERFOLLOWEFFECT_IgniculusBody );
			break;

		case MONSTEREFFECTID_Faugn:
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip01 Faugn01", "FaugnBody", MONSTERFOLLOWEFFECT_FaugnBody );
			break;

		case MONSTEREFFECTID_IceElemental:
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip01 Tail", "IceElementalBody", MONSTERFOLLOWEFFECT_IceElementalBody );
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip01 L Hand", "IceElementalHand", MONSTERFOLLOWEFFECT_IceElementalLeftHand );
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip01 R Hand", "IceElementalHand", MONSTERFOLLOWEFFECT_IceElementalRightHand );
			break;

		case MONSTEREFFECTID_DarkGuardian:
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip01 center", "DarkGuardian1", MONSTERFOLLOWEFFECT_DarkGuardianCenter );
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip01 center01", "DarkGuardian1", MONSTERFOLLOWEFFECT_DarkGuardianCenter01 );
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip01 center02", "DarkGuardian1", MONSTERFOLLOWEFFECT_DarkGuardianCenter02 );
			break;

		case MONSTEREFFECTID_Insec:
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip001 Spine", "InsecBody", MONSTERFOLLOWEFFECT_InsecBody );
			break;

		case MONSTEREFFECTID_FlameMaiden:
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip001 Spine", "FlamemaidenBody", MONSTERFOLLOWEFFECT_FlameMaidenBody );
			break;

		case MONSTEREFFECTID_Greedy:
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip01 L Finger1", "GreedyBody", MONSTERFOLLOWEFFECT_GreedyBody );
			break;

// NEW ADD

/*		case MONSTEREFFECTID_Aragonian:
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip01 L Finger1", "AragonianBody", MONSTERFOLLOWEFFECT_AragonianBody );
			break;*/
			
		case MONSTEREFFECTID_CrystalWrath:
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip01 L Finger1", "CrystalWrathBody", MONSTERFOLLOWEFFECT_CrystalWrathBody );
			break;		  
		case MONSTEREFFECTID_Deius:
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip01 Spine", "DeiusBody", MONSTERFOLLOWEFFECT_DeiusBody );
			break;

		case MONSTEREFFECTID_Grangium:
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip01 Spine", "GrangiumBody", MONSTERFOLLOWEFFECT_GrangiumBody );
			break;			

		case MONSTEREFFECTID_Sylers:
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip01 Spine", "SylersBody", MONSTERFOLLOWEFFECT_SylersBody );
			break;
			
		case MONSTEREFFECTID_Bydream:
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip01 L Finger1", "BydreamBody", MONSTERFOLLOWEFFECT_BydreamBody );
			break;

		case MONSTEREFFECTID_Samsara:
			SETPARTICLEMESHFOLLOW( pcUnitData, "Bip01 L Finger1", "SamsaraBody", MONSTERFOLLOWEFFECT_SamsaraBody );
			break;
		default:
			break;
	}



	return bRet;
}

void CGameEffectFollow::LoadParticles()
{
	//Abyss
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\ArhdyraBody.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\ArhdyraHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\ArhdyraSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\DeyHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\DeySkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\DeyStart.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\FaugnBody.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\FaugnHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\FaugnSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\GurkobHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\GurkobSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\GurkobStart.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\KoonHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\KoonSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\SathlaHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\SathlaSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\SathlaStart.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\YagdithaBody.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\YagdithaHit1.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\YagdithaHit2.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\YagdithaSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\abyssmap\\YagdithaStart.part" );
	// CRYSTALNEST
	PARTICLE->Load( "game\\scripts\\particles\\AmesystHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\AmesystSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\AmonkHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\AmonkSkill.part" );
//	PARTICLE->Load( "game\\scripts\\particles\\AragonianBody.part" );	
	PARTICLE->Load( "game\\scripts\\particles\\AragonianFlameWave.part" );
	PARTICLE->Load( "game\\scripts\\particles\\AragonianFlameWaveBig.part" );
	PARTICLE->Load( "game\\scripts\\particles\\AragonianHit1.part" );
	PARTICLE->Load( "game\\scripts\\particles\\AragonianHit2.part" );
	PARTICLE->Load( "game\\scripts\\particles\\AragonianSkill1.part" );
	PARTICLE->Load( "game\\scripts\\particles\\AragonianSkill2.part" );
	PARTICLE->Load( "game\\scripts\\particles\\AragonianStart.part" );
	PARTICLE->Load( "game\\scripts\\particles\\CrystalWrathBody.part" );
	PARTICLE->Load( "game\\scripts\\particles\\CrystalWrathHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\CrystalWrathSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\CrystalWrathStart.part" );
	PARTICLE->Load( "game\\scripts\\particles\\KolpionHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\KolpionSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\QuartzBatHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\QuartzBatSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\QuartzBatStart.part" );
	PARTICLE->Load( "game\\scripts\\particles\\QuartzSaurusHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\QuartzSaurusSkill.part" );	
	PARTICLE->Load( "game\\scripts\\particles\\UndeadSlaveHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\UndeadSlaveSkill.part" );
// LandOfNurwin	
	PARTICLE->Load( "game\\scripts\\particles\\DeiusBody.part" );
	PARTICLE->Load( "game\\scripts\\particles\\DeiusHit1.part" );
	PARTICLE->Load( "game\\scripts\\particles\\DeiusHit2.part" );
	PARTICLE->Load( "game\\scripts\\particles\\DeiusSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\GrangiumBody.part" );
	PARTICLE->Load( "game\\scripts\\particles\\GrangiumHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\GrangiumSkill.part" );	
	PARTICLE->Load( "game\\scripts\\particles\\OblankoHit1.part" );
	PARTICLE->Load( "game\\scripts\\particles\\OblankoHit2.part" );
	PARTICLE->Load( "game\\scripts\\particles\\OblankoSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\RaedaHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\RaedaSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\RoblankoHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\RoblankoSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\SylersBody.part" );
	PARTICLE->Load( "game\\scripts\\particles\\SylersHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\SylersSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\TeesHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\TeesSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\ToosHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\ToosSkill.part" );
// OBLIVION
	PARTICLE->Load( "game\\scripts\\particles\\BydreamBody.part" );
	PARTICLE->Load( "game\\scripts\\particles\\BydreamDead.part" );
	PARTICLE->Load( "game\\scripts\\particles\\BydreamHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\BydreamSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\DominaHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\DominaSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\GemHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\GemSkill1.part" );
	PARTICLE->Load( "game\\scripts\\particles\\GemSkill2.part" );
	PARTICLE->Load( "game\\scripts\\particles\\GemSkill3.part" );
	PARTICLE->Load( "game\\scripts\\particles\\MarterumHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\MarterumSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\MellHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\MellSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\MorosHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\MorosSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\MorosStart.part" );
	PARTICLE->Load( "game\\scripts\\particles\\MorosStart2.part" );
	PARTICLE->Load( "game\\scripts\\particles\\PermaHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\PermaSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\SamsaraBody.part" );
	PARTICLE->Load( "game\\scripts\\particles\\SamsaraHit1.part" );	
	PARTICLE->Load( "game\\scripts\\particles\\SamsaraHit2.part" );
	PARTICLE->Load( "game\\scripts\\particles\\SamsaraSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\VirdomHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\VirdomSkill.part" );	
	PARTICLE->Load( "game\\scripts\\particles\\IceElementalBody.part" );
	PARTICLE->Load( "game\\scripts\\particles\\IceElementalHand.part" );
	PARTICLE->Load( "game\\scripts\\particles\\DarkGuardian1.part" );
	PARTICLE->Load( "game\\scripts\\particles\\DarkGuardian2.part" );
	PARTICLE->Load( "game\\scripts\\particles\\IgniculusBody.part" );
	PARTICLE->Load( "game\\scripts\\particles\\IgniculusSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\IgniculusHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\LavaArmorStart.part" );
	PARTICLE->Load( "game\\scripts\\particles\\LavaArmorSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\LavaArmorHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\LavaGolemHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\LavaGolemSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\LavaGiantStart.part" );
	PARTICLE->Load( "game\\scripts\\particles\\LavaGiantSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\LavaGiantHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\LavaArcherStart.part" );
	PARTICLE->Load( "game\\scripts\\particles\\LavaArcherSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\LavaArcherHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\InsecBody.part" );
	PARTICLE->Load( "game\\scripts\\particles\\InsecSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\InsecHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\FlamoSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\FlamoHit1.part" );
	PARTICLE->Load( "game\\scripts\\particles\\FlamemaidenStart.part" );
	PARTICLE->Load( "game\\scripts\\particles\\FlamemaidenSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\FlamemaidenHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\FlamemaidenBody.part" );

	PARTICLE->Load( "game\\scripts\\particles\\AceroStart.part" );
	PARTICLE->Load( "game\\scripts\\particles\\AceroSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\AceroHit.part" );

	PARTICLE->Load( "game\\scripts\\particles\\ChalybsStart.part" );
	PARTICLE->Load( "game\\scripts\\particles\\ChalybsSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\ChalybsHit.part" );

	PARTICLE->Load( "game\\scripts\\particles\\GreedyStart.part" );
	PARTICLE->Load( "game\\scripts\\particles\\GreedySkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\GreedyHit1.part" );
	PARTICLE->Load( "game\\scripts\\particles\\GreedyHit2.part" );
	PARTICLE->Load( "game\\scripts\\particles\\GreedyBody.part" );

	PARTICLE->Load( "game\\scripts\\particles\\IEliteStart.part" );
	PARTICLE->Load( "game\\scripts\\particles\\IEliteSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\IEliteHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\IEliteBody.part" );

	PARTICLE->Load( "game\\scripts\\particles\\ISoldierSkill.part" );
	PARTICLE->Load( "game\\scripts\\particles\\NihilHit.part" );
	PARTICLE->Load( "game\\scripts\\particles\\NihilSkill.part" );
}

BOOL CGameEffectFollow::StartMacro( UnitData * pcUnitData, char * pszMeshName, char * pszParticleName, int iID )
{
	if ( EffectBaseFollow::IsActiveEffect( pcUnitData, iID ) == FALSE )
	{
		int iIndex = EffectBaseFollow::GetFreeIndex();

		CGameEffectFollow * pc = new CGameEffectFollow();
		pc->Start( pcUnitData, pszMeshName, pszParticleName );

		EffectBaseFollow::GetData()[iIndex] = pc;
		EffectBaseFollow::GetData()[iIndex]->dwID = iID;

		return TRUE;
	}

	return FALSE;
}

NAKED int EffectBaseFollow::GetFreeIndex()
{
	JMP( pfnGetFreeIndex );
}

NAKED BOOL EffectBaseFollow::IsActiveEffect( UnitData * pcUnitData, DWORD dwID )
{
	JMP( pfnIsActiveEffect );
}

BOOL EffectBaseFollow::DeleteEffect( UnitData * pcUnitData )
{
	BOOL bRet = FALSE;

	for ( int i = 0; i < 5000; i++ )
	{
		EffectBaseFollow * pc = EffectBaseFollow::GetData()[i];

		if ( pc )
		{
			if ( pc->iTime < pc->iTimeMax )
			{
				if ( (pc->pcUnitData == pcUnitData) || (pc->pcUnitDataDest == pcUnitData) )
				{
					pc->iTime = pc->iTimeMax;

					bRet = TRUE;
				}
			}
		}
	}

	return bRet;
}

void EffectBaseFollow::MainEffect()
{
	for ( int i = 0; i < 5000; i++ )
	{
		EffectBaseFollow * pc = EffectBaseFollow::GetData()[i];

		if ( pc )
		{
			pc->iTime++;

			if ( (pc->iTime >= pc->iTimeMax) && (pc->iTimeMax > 0) )
			{
				DELET( pc );
				EffectBaseFollow::GetData()[i] = NULL;
				continue;
			}

			pc->Main();

			if ( pc->iTime > 0 )
			{
				if ( pc->pcUnitData && (pc->pcUnitData->bActive && pc->pcUnitData->bVisible) && UNITDATA )
				{
					Point3D sDistance;
					sDistance.iX = UNITDATA->sPosition.iX - pc->pcUnitData->sPosition.iX;
					sDistance.iY = UNITDATA->sPosition.iY - pc->pcUnitData->sPosition.iY;
					sDistance.iZ = UNITDATA->sPosition.iZ - pc->pcUnitData->sPosition.iZ;

					sDistance >>= 8;

					int iDistance	 = sDistance.iX * sDistance.iX;
					iDistance		+= sDistance.iY * sDistance.iY;
					iDistance		+= sDistance.iZ * sDistance.iZ;

					if ( iDistance < DISTANCE_UNIT_NEAR )
						CALL_WITH_ARG1( 0x005356D0, (DWORD)pc );
				}
			}

			if ( pc->iTime >= pc->iTimeMax )
			{
				DELET( pc );
				EffectBaseFollow::GetData()[i] = NULL;
				continue;
			}
		}
	}
}

NAKED void EffectBaseFollowShot::Constructor()
{
	JMP( 0x00559080 );
}

void EffectBaseFollowShot::Deconstructor()
{
}

NAKED void EffectBaseFollowShot::Start( Point3D * psCurrentPosition, Point3D * psTargetPosition, int iEffectType )
{
	JMP( 0x0055D9E0 );
}

NAKED void EffectBaseFollowTrace::AddData( Point3D * psPosition )
{
	JMP( 0x00535620 );
}
