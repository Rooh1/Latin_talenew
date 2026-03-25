#include "stdafx.h"
#include "CEventHandler.h"

CEventHandler::CEventHandler()
{
}

CEventHandler::~CEventHandler()
{
}

void CEventHandler::Init()
{
}

void CEventHandler::HandlePacket( PacketEventServer * psPacket )
{
    CopyMemory( &sEventData, &psPacket->sEventData, sizeof( PacketEventServer::EventData ) );

    if ( (bPlaceTimer == false) && HaveActiveEvent() )
    {
        AddTimer();

        bPlaceTimer = true;
    }
    else if ( (HaveActiveEvent() == false) && (bPlaceTimer) )
    {
        TIMERSKILLHANDLER->KillTimer( SKILLID_EventTimer );

        bPlaceTimer = false;
    }
}


void CEventHandler::AddTimer()
{
    if ( !iTimerID )
        iTimerID = TIMERSKILLHANDLER->LoadSkillTimerTexture( "game\\images\\skills\\timers\\EventTimer.tga" );

    Skill * psSkill = TIMERSKILLHANDLER->FindSkillTimer( SKILLID_EventTimer );

    if ( psSkill )
        ZeroMemory( psSkill, sizeof( Skill ) );

    if ( !TIMERSKILLHANDLER->FindSkillTimer( SKILLID_EventTimer ) )
    {
        Skill sSkill;
        ZeroMemory( &sSkill, sizeof( sSkill ) );
        STRINGCOPY( sSkill.sSkillInfo.szName, "Eventos activos actualmente" );
        STRINGCOPY( sSkill.sSkillInfo.szDescription, "Aqu\355 puedes ver los eventos activos o cu\341ndo comenzar\341n" );

        sSkill.iID = SKILLID_EventTimer;
        sSkill.iUseTime = 70 * 70;
        sSkill.iLevel = 1;
        sSkill.MatIcon = iTimerID;
        TIMERSKILLHANDLER->AddSkillTimer( &sSkill );
    }
}

bool CEventHandler::HaveActiveEvent()
{
    return (sEventData.bEXP || sEventData.bExtraDrop || sEventData.bPvP || sEventData.bWantedMoriph ||
            sEventData.bWantedWolf || sEventData.bHalloween || sEventData.bXmas || (sEventData.iEventCount > 0));
}
