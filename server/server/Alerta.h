#pragma once
#include "stdafx.h"
#include <vector>
#include <map>

struct AlertaInfo
{
	DWORD Head, ChkSum;
	char ItemName[32];
	char MonsterName[32];
	int iMap;
};

class Alerta
{
public:
	static Alerta* getInstance();

	void Init();

	// Adaptado para usar UnitData (Monstro) e Item (Item do drop)
	void AddItemLog(UserData* pcUserData, UnitData* pcUnitData, Item* psItem);

private:
	std::vector<AlertaInfo> vAlertaInfo;
	std::map<int, bool> vEnabled; // Mapa de IDs habilitados
};

#define ALERTAHANDLER Alerta::getInstance()