#include "stdafx.h"
#include "party.h"

const char * GetPartyMode( EPartyMode eMode )
{
	const char * pszRet = "Desconocido";

	if( eMode == PARTYMODE_EXP )
		pszRet = "Modo EXP";
	else if( eMode == PARTYMODE_Normal )
		pszRet = "Modo normal";
	else if( eMode == PARTYMODE_Hunt )
		pszRet = "Modo caza";

	return pszRet;
}
