#include "stdafx.h"
#include "BellatraGame.h"


BellatraGame::BellatraGame()
{

}


BellatraGame::~BellatraGame()
{
}

void BellatraGame::SetCrown()
{
	if ( Game::GetGameMode() != GAMEMODE_InGame )
		return;

	if ( (*(DWORD*)(0x03B18BC8)) == 1 )
	{
		Skill * psSkill = TIMERSKILLHANDLER->FindSkillTimer( TIMERSKILLID_BellatraGold );
		if ( !psSkill && dwTextureCrownTimerGold )
		{
			Skill sSkill; 
			ZeroMemory( &sSkill, sizeof( sSkill ) );
			STRINGCOPY( sSkill.szName, "Corona Bellatra Oro" );
			STRINGCOPY( sSkill.sSkillInfo.szName, "Corona Bellatra Oro" );
			STRINGCOPY( sSkill.sSkillInfo.szDescription, "Agrega +1 vel. de ataque" );
			sSkill.iID = TIMERSKILLID_BellatraGold;
			sSkill.iUseTime = 70 * 70;
			sSkill.iLevel = 1;
			sSkill.MatIcon = dwTextureCrownTimerGold;
			TIMERSKILLHANDLER->KillTimer( TIMERSKILLID_BellatraSilver );
			TIMERSKILLHANDLER->KillTimer( TIMERSKILLID_BellatraBronze );
			TIMERSKILLHANDLER->AddSkillTimer( &sSkill );
			PLAYMINISOUND( 25 );
			bKilledTimers = FALSE;
		}
	}
	else if ( (*(DWORD*)(0x03B18BC8)) == 2 )
	{
		Skill * psSkill = TIMERSKILLHANDLER->FindSkillTimer( TIMERSKILLID_BellatraSilver );
		if ( !psSkill && dwTextureCrownTimerSilver )
		{
			Skill sSkill; 
			ZeroMemory( &sSkill, sizeof( sSkill ) );
			STRINGCOPY( sSkill.szName, "Corona Bellatra Plata" );
			STRINGCOPY( sSkill.sSkillInfo.szName, "Corona Bellatra Plata" );
			STRINGCOPY( sSkill.sSkillInfo.szDescription, "Agrega +10% defensa" );
			sSkill.iID = TIMERSKILLID_BellatraSilver;
			sSkill.iUseTime = 70 * 70;
			sSkill.iLevel = 1;
			sSkill.MatIcon = dwTextureCrownTimerSilver;
			TIMERSKILLHANDLER->KillTimer( TIMERSKILLID_BellatraGold );
			TIMERSKILLHANDLER->KillTimer( TIMERSKILLID_BellatraBronze );
			TIMERSKILLHANDLER->AddSkillTimer( &sSkill );
			PLAYMINISOUND( 25 );
			bKilledTimers = FALSE;
		}
	}
	else if ( (*(DWORD*)(0x03B18BC8)) == 3 )
	{
		Skill * psSkill = TIMERSKILLHANDLER->FindSkillTimer( TIMERSKILLID_BellatraBronze );
		if ( !psSkill && dwTextureCrownTimerBronze )
		{
			Skill sSkill; 
			ZeroMemory( &sSkill, sizeof( sSkill ) );
			STRINGCOPY( sSkill.szName, "Corona Bellatra Bronce" );
			STRINGCOPY( sSkill.sSkillInfo.szName, "Corona Bellatra Bronce" );
			STRINGCOPY( sSkill.sSkillInfo.szDescription, "Agrega +5% tasa de ataque" );
			sSkill.iID = TIMERSKILLID_BellatraBronze;
			sSkill.iUseTime = 70 * 70;
			sSkill.iLevel = 1;
			sSkill.MatIcon = dwTextureCrownTimerBronze;
			TIMERSKILLHANDLER->KillTimer( TIMERSKILLID_BellatraGold );
			TIMERSKILLHANDLER->KillTimer( TIMERSKILLID_BellatraSilver );
			TIMERSKILLHANDLER->AddSkillTimer( &sSkill );
			PLAYMINISOUND( 25 );
			bKilledTimers = FALSE;
		}
	}
	else
	{
		if ( !bKilledTimers )
		{
			TIMERSKILLHANDLER->KillTimer( TIMERSKILLID_BellatraGold );
			TIMERSKILLHANDLER->KillTimer( TIMERSKILLID_BellatraSilver );
			TIMERSKILLHANDLER->KillTimer( TIMERSKILLID_BellatraBronze );
			bKilledTimers = TRUE;
		}
	}
	if ( !dwTextureCrownTimerGold )
			dwTextureCrownTimerGold = TIMERSKILLHANDLER->LoadSkillTimerTexture( "game\\images\\skills\\timers\\bellatracrown_1.tga" );
	if ( !dwTextureCrownTimerSilver )
			dwTextureCrownTimerSilver = TIMERSKILLHANDLER->LoadSkillTimerTexture( "game\\images\\skills\\timers\\bellatracrown_2.tga" );
	if ( !dwTextureCrownTimerBronze )
			dwTextureCrownTimerBronze = TIMERSKILLHANDLER->LoadSkillTimerTexture( "game\\images\\skills\\timers\\bellatracrown_3.tga" );
}
