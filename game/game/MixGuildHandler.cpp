#include "stdafx.h"
#include "MixGuildHandler.h"


CMixGuildHandler::CMixGuildHandler()
{
}


CMixGuildHandler::~CMixGuildHandler()
{
	DELET(pcMixGuildWindow);
}

void CMixGuildHandler::Init()
{
	pcMixGuildWindow = new CMixGuildWindow();
	pcMixGuildWindow->Init();

}

void CMixGuildHandler::Update()
{

}

void CMixGuildHandler::Render()
{
	GetWindow()->Render();
}

