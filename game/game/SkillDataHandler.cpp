#include "stdafx.h"
#include "SkillDataHandler.h"


int CSkillDataHandler::OnFighterSkill( Skill * psSkill, int iLevel )
{
	int iLineCount = 0;

	int iSkillLevel = iLevel - 1;

	switch ( psSkill->iID )
	{
		case SKILLID_SeismicImpact:
			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Aumento de da\361o:      \r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d%%\r", iaSesmicImpactDamage[iSkillLevel] );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "\301rea:                 \r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d\r", iaSesmicImpactArea[iSkillLevel] );
			iLineCount++;
			break;

		case SKILLID_SurvivalInstinct:
			SKILLMANAGERHANDLER->AddSkillInfo( 1, "HP adicional:         \r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d\r", iaSurvivalInstinctAddHP[iSkillLevel] );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Reg. HP en cadena:    \r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d%%\r", iaSurvivalInstinctBoostHPRegen[iSkillLevel] );
			iLineCount++;
			break;

		case SKILLID_RuthlessofZecram:
			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Reducci\363n de HP:      \r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%.1f%%\r", FST5A3_1[iSkillLevel] );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Golpes para aumento:  \r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d\r", FST5A3_2[iSkillLevel] );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Aum. final de da\361o:   \r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d%%\r", FST5A3_3[iSkillLevel] );
			iLineCount++;
			break;

		case SKILLID_WhirlwindFS01:
			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Aumento de da\361o:      \r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d%%\r", FST5A4_1[iSkillLevel] );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Duraci\363n:             \r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d\r", FST5A4_2[iSkillLevel] );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Consumo de MP:        \r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d\r", FST5A4_3[iSkillLevel] );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Consumo de STM:       \r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d\r", FST5A4_4[iSkillLevel] );
			iLineCount++;
			break;

		default:
			break;
	}

	return iLineCount;
}

int CSkillDataHandler::OnAtalantaSkill( Skill * psSkill, int iLevel )
{
	int iLineCount = 0;

	int iSkillLevel = iLevel - 1;

	switch ( psSkill->iID )
	{
		case SKILLID_SummonTiger:
			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Configuraci\363n de mascota:\r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%s\r", SKILLMANAGERHANDLER->IsAgressive( SKILLID_SummonTiger ) ? "Autom\341tico" : "Manual" );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Poder de ataque:\r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d-%d\r", iaSummonTigerAttackPower[iSkillLevel], iaSummonTigerAttackPower[iSkillLevel] );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "\315ndice de ataque:\r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d\r", iaSummonTigerAttackRating[iSkillLevel] );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "HP:\r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d\r", iaSummonTigerHP[iSkillLevel] );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Duraci\363n:\r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "300\r" );
			iLineCount++;
			break;

		default:
			break;
	}

	return iLineCount;
}

int CSkillDataHandler::OnKnightSkill( Skill * psSkill, int iLevel )
{
	int iLineCount = 0;

	int iSkillLevel = iLevel - 1;

	switch ( psSkill->iID )
	{
		case SKILLID_HolyConviction:
			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Configuraci\363n de mascota:\r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%s\r", SKILLMANAGERHANDLER->IsAgressive( SKILLID_SummonTiger ) ? "Autom\341tico" : "Manual" );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Poder de ataque:\r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d-%d\r", iaSummonTigerAttackPower[iSkillLevel], iaSummonTigerAttackPower[iSkillLevel] );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "\315ndice de ataque:\r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d\r", iaSummonTigerAttackRating[iSkillLevel] );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "HP:\r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d\r", iaSummonTigerHP[iSkillLevel] );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Duraci\363n:\r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "300\r" );
			iLineCount++;
			break;

		default:
			break;
	}

	return iLineCount;
}

int CSkillDataHandler::OnPriestessSkill( Skill * psSkill, int iLevel )
{
	int iLineCount = 0;

	int iSkillLevel = iLevel - 1;

	switch ( psSkill->iID )
	{
		case SKILLID_IceElemental:
			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Configuraci\363n de mascota:\r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%s\r", SKILLMANAGERHANDLER->IsAgressive( SKILLID_IceElemental ) ? "Autom\341tico" : "Manual" );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Poder de ataque:\r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d-%d\r", iaIceElementalAttackPower[iSkillLevel], iaIceElementalAttackPower[iSkillLevel] );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "\315ndice de ataque:\r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d\r", iaIceElementalAttackRating[iSkillLevel] );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "HP:\r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "%d\r", iaIceElementalHP[iSkillLevel] );
			iLineCount++;

			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Duraci\363n:\r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "300\r" );
			iLineCount++;
			break;

		default:
			break;
	}

	return iLineCount;
}

CSkillDataHandler::CSkillDataHandler()
{
}

CSkillDataHandler::~CSkillDataHandler()
{
}

BOOL CSkillDataHandler::IsSkillLocked( int iID )
{
#if defined(_DEBUG)
	return FALSE;
#endif

	if ( WORLD->GetWorldID() == WORLDID_Test )
	{
		switch ( iID )
		{
			case SKILLID_LastBreath:
				return FALSE;
				break;
		}
	}

	switch( iID )
	{
		case SKILLID_ParasitShot:
		case SKILLID_HardeningShield:
		//case SKILLID_SeismicImpact:
		case SKILLID_RuthlessofZecram:
		case SKILLID_WhirlwindFS01:
		//case SKILLID_KissViper:
		case SKILLID_ViolentStub:
		case SKILLID_ShadowStorm:
		case SKILLID_FierceWind:
		case SKILLID_EntalingRoots:
		case SKILLID_Bombardment:
		case SKILLID_DeathMaster:
		case SKILLID_Twister:
		case SKILLID_PlagueJavelin:
		case SKILLID_GoldenApple:
		case SKILLID_ComboJavelin:
		case SKILLID_GloriousShield:
		case SKILLID_DivineCross:
		//case SKILLID_StoneSkin:
		case SKILLID_RedRay:
		case SKILLID_Cataclysm:
		case SKILLID_HeavenlyLight:
		case SKILLID_Consecration:
		case SKILLID_PhantomNail:
		case SKILLID_OccultLife:
		case SKILLID_WhirlWind:
			return TRUE;
			break;
	}

	return FALSE;
}

int CSkillDataHandler::OnInformationHandler( Skill * psSkill, int iLevel )
{
	int iLineCount = 0;

	int iLoop = iLevel < 10 ? 2 : 1;
	
	SKILLMANAGERHANDLER->AddSkillInfo( 1, "\r" );
	SKILLMANAGERHANDLER->AddSkillInfo( 2, "\r" );

	for ( int i = 0; i < iLoop; i++ )
	{
		if ( i == 1 )
		{
			SKILLMANAGERHANDLER->AddSkillInfo( 1, "Siguiente nivel\r" );
			SKILLMANAGERHANDLER->AddSkillInfo( 2, "\r" );
		}

		switch ( psSkill->iID & 0xFF000000 )
		{

			case 0x02000000:
				iLineCount += OnFighterSkill( psSkill, iLevel + i );
				break;

			case 0x07000000:
				iLineCount += OnPriestessSkill( psSkill, iLevel + i );
				break;

			default:
				break;
		}
	}

	return iLineCount;
}
