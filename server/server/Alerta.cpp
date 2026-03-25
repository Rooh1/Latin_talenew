#include "stdafx.h"
#include "Alerta.h"

// Variáveis externas da sua source para acessar a tabela de itens
extern ItemData* pAllocItemTable;
extern UINT iTableItemCompressPosition;

Alerta cAlertaHandler;

Alerta* Alerta::getInstance()
{
	return &cAlertaHandler;
}

void Alerta::Init()
{
	vEnabled.clear();
	vAlertaInfo.clear();

	// Usa a conexão padrão do servidor (GameDB ou UserDB, dependendo de onde criou a tabela)
	SQLConnection* pcDB = SQLCONNECTION(DATABASEID_GameDB);

	if (pcDB->Open())
	{
		// Certifique-se que a tabela DropLogAlert existe no banco
		if (pcDB->Prepare("SELECT ItemCode FROM DropLogAlert"))
		{
			if (pcDB->Execute())
			{
				while (pcDB->Fetch())
				{
					char szItemCode[32] = { 0 };
					pcDB->GetData(1, PARAMTYPE_String, szItemCode, 32);

					// Procura o ID do item na tabela do servidor pelo código (ex: "WA101")
					if (pAllocItemTable)
					{
						for (UINT i = 0; i < iTableItemCompressPosition; i++)
						{
							if (STRINGCOMPAREI(pAllocItemTable[i].szInventoryName, szItemCode))
							{
								// Ativa o alerta para este ID
								vEnabled[pAllocItemTable[i].sBaseItemID.ToInt()] = true;
								break;
							}
						}
					}
				}
			}
		}
		pcDB->Close();
	}
}

void Alerta::AddItemLog(UserData* pcUserData, UnitData* pcUnitData, Item* psItem)
{
	// Verifica se o item existe e se está na lista de alertas
	if (!psItem || vEnabled.find(psItem->sItemID.ToInt()) == vEnabled.end())
		return;

	char szItemName[64] = { 0 };
	char szMonsterName[64] = { 0 };
	char szPlayerName[32] = { 0 };

	// Copia Nomes
	if (psItem->szItemName[0])
		strncpy_s(szItemName, psItem->szItemName, 63);

	if (pcUnitData && pcUnitData->sCharacterData.szName[0])
		strncpy_s(szMonsterName, pcUnitData->sCharacterData.szName, 63);
	else
		strncpy_s(szMonsterName, "Unknown", 63);

	if (pcUserData && pcUserData->sCharacterData.szName[0])
		strncpy_s(szPlayerName, pcUserData->sCharacterData.szName, 31);
	else
		strncpy_s(szPlayerName, "Player", 31);

	// 1. Mensagem no Chat (Opcional, se quiser manter)
	char szMessage[256];
	wsprintf(szMessage, "> %s dropou %s do monstro %s!", szPlayerName, szItemName, szMonsterName);
	CHATSERVER->SendChatAll(CHATCOLOR_Global, szMessage);

	// 2. Pacote Visual
	PacketRareDropAlert sPacket;
	sPacket.iLength = sizeof(PacketRareDropAlert);
	sPacket.iHeader = PKTHDR_RareDropAlert;

	CopyMemory(sPacket.szItemName, szItemName, 64);
	CopyMemory(sPacket.szMonsterName, szMonsterName, 64);
	CopyMemory(sPacket.szPlayerName, szPlayerName, 32); // <--- Envia o Nick

	for (int i = 0; i < PLAYERS_MAX; i++) {
		UserData* ud = &USERSDATA[i];
		if (ud->pcSocketData && ud->iID) {
			SENDPACKET(USERDATATOUSER(ud), &sPacket);
		}
	}
}