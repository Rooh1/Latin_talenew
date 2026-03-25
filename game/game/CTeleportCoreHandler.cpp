#include "stdafx.h"
#include "CTeleportCoreHandler.h"

// <-- DADOS: Array de guias com 9 entradas -->
const char* INFO_MAPA[5] = {
	"EVENTS",
	"DROP GOLD",
	"EXP 150-155",
	"DROP SHELTOMS",
	"DROP 130\nDROP 134\nBoss Volcanos ",
	/*"9x to 10x",
	"9x to 10x",
	"10x to 11x",
	"10x to 11x",
	"10x to 11x",
	"11x to 12x",
	"11x to 12x",
	"11x to 12x",
	"12x to 13x",
	"12x to 13x",
	"12x to 13x",
	"13x to 14x",
	"13x to 14x",
	"13x to 14x\nNPC ITEMS LEVEL 105",
	"14x to 15x",
	"Boss Valento ",
	"Boss Kelvezu ",
	"Boss Mokova ",
	"DROP ITEMS 110 ",
	"DROP ITEMS 120 ",
	"DROP ITEMS 130 ",*/
};
// <-- FIM DADOS -->


// NOTE: The order must match the enabled maps in saTeleportMapInfo.
const char* CUSTOM_MINIMAP_PATHS[] = {
	// iIndex = 0 (MAPID_Atlantis)
	//"game\\images\\teleport\\Mapas\\atlantis_custom.png",

	// iIndex = 1 (MAPID_BattleTown)
	//"game\\images\\teleport\\Mapas\\battletown_custom.png",

	// iIndex = 2 (MAPID_GardenOfFreedom)
	"game\\images\\teleport\\Mapas\\jardim-liberdade.png",

	// iIndex = 3 (MAPID_RuinenVillage)
	"game\\images\\teleport\\Mapas\\vila-ruinem.png",

	// iIndex = 4 (MAPID_BeehiveCave)
	//"game\\images\\teleport\\Mapas\\bcave.png",

	// iIndex = 5 (MAPID_MushroomCave)
	//"game\\images\\teleport\\Mapas\\mcave.png",

	// iIndex = 6 (MAPID_DarkSanctuary)
	//"game\\images\\teleport\\Mapas\\ds.png",

	// iIndex = 7 (MAPID_AncientPrisonF1)
	//"game\\images\\teleport\\Mapas\\dun1.png",

	// iIndex = 8 (MAPID_AncientPrisonF2)
	//"game\\images\\teleport\\Mapas\\dun2.png",

	// iIndex = 9 (MAPID_AncientPrisonF3)
	//"game\\images\\teleport\\Mapas\\dun3.png",

	// iIndex = 10 (MAPID_AncientDungeonF1)
	//"game\\images\\teleport\\Mapas\\dun1.png",

	// iIndex = 11 (MAPID_AncientDungeonF2)
	//"game\\images\\teleport\\Mapas\\dun2.png",

	// iIndex = 12 (MAPID_AncientDungeonF3)
	//"game\\images\\teleport\\Mapas\\dun3.png",

	// iIndex = 13 (MAPID_MysteryForest3)
	//"game\\images\\teleport\\Mapas\\mysteryforest3_custom.png",

	// iIndex = 14 (MAPID_MysteryForest2)
	//"game\\images\\teleport\\Mapas\\mysteryforest2_custom.png",

	// iIndex = 15 (MAPID_MysteryForest1)
	//"game\\images\\teleport\\Mapas\\mysteryforest1_custom.png",

	// iIndex = 16 (MAPID_MysteryDesert3)
	//"game\\images\\teleport\\Mapas\\mysterydesert3_custom.png",

	// iIndex = 17 (MAPID_MysteryDesert2)
	//"game\\images\\teleport\\Mapas\\mysterydesert2_custom.png",

	// iIndex = 18 (MAPID_MysteryDesert1)
	//"game\\images\\teleport\\Mapas\\mysterydesert1_custom.png",

	// iIndex = 19 (MAPID_GreedyLake)
	"game\\images\\teleport\\Mapas\\gl.png",

	// iIndex = 20 (MAPID_GallubiaValley)
	//"game\\images\\teleport\\Mapas\\ice1.png",

	// iIndex = 21 (MAPID_KelvezuLair)
	//"game\\images\\teleport\\Mapas\\kcave.png",

	// iIndex = 22 (MAPID_LostTemple)
	//"game\\images\\teleport\\Mapas\\lost2.png",

	// iIndex = 23 (MAPID_DeathIsland)
	"game\\images\\teleport\\Mapas\\deathisland_custom.png",

	// iIndex = 24 (MAPID_CrystalNest)
	//"game\\images\\teleport\\Mapas\\crystalnest_custom.png",

	// iIndex = 25 (MAPID_CursedDesert)
	"game\\images\\teleport\\Mapas\\curseddesert_custom.png",

	//"game\\images\\teleport\\Mapas\\curseddesert_custom.png",
};


CTeleportCoreHandler::CTeleportCoreHandler()
{

}


CTeleportCoreHandler::~CTeleportCoreHandler()
{
	pWindow.reset();
}

void CTeleportCoreHandler::Init()
{
	BuildWindow();
}

BOOL CTeleportCoreHandler::OnMouseClick(CMouse* pcMouse)
{
	return pWindow->OnMouseClick(pcMouse, 0, 0, DX::Graphic::GetWidthBackBuffer(), DX::Graphic::GetHeightBackBuffer(), 0, 0);
}

void CTeleportCoreHandler::OnMouseMove(CMouse* pcMouse)
{
	pWindow->OnMouseMove(pcMouse, 0, 0, DX::Graphic::GetWidthBackBuffer(), DX::Graphic::GetHeightBackBuffer(), 0, 0);
}

BOOL CTeleportCoreHandler::OnMouseScroll(CMouse* pcMouse)
{
	return pWindow->OnMouseScroll(pcMouse, 0, 0, DX::Graphic::GetWidthBackBuffer(), DX::Graphic::GetHeightBackBuffer(), 0, 0);
}

void CTeleportCoreHandler::OnResolutionChanged()
{
	int iWindowWidth = pWindow->GetWidth();
	int iWindowHeight = pWindow->GetHeight();

	int iWindowX = (RESOLUTION_WIDTH >> 1) - (iWindowWidth >> 1);
	int iWindowY = (RESOLUTION_HEIGHT >> 1) - (iWindowHeight >> 1);

	pWindow->SetPosition(iWindowX, iWindowY);
}

void CTeleportCoreHandler::Render()
{
	pWindow->Render(0, 0, DX::Graphic::GetWidthBackBuffer(), DX::Graphic::GetHeightBackBuffer(), 0, 0);
}

void CTeleportCoreHandler::Update(float fTime)
{
	pWindow->Update(fTime);
}

void CTeleportCoreHandler::Open(ItemData* pcItemData)
{
	if (pWindow->IsOpen() == FALSE)
	{
		this->iItemID = pcItemData->sItem.sItemID.ToItemID();
		this->iChk1 = pcItemData->sItem.iChk1;
		this->iChk2 = pcItemData->sItem.iChk2;

		for (int i = 0; i < _countof(saTeleportMapInfo); i++)
		{
			if (saTeleportMapInfo[i].bEnabled && (MAPLEVEL(saTeleportMapInfo[i].iMapID) < 200))
			{
				auto pWindowMap = pWindow->GetElement<UI::List>(LISTID_Map)->GetWindow(WINDOWID_Map + i);

				if (UNITDATA->sCharacterData.iLevel >= MAPLEVEL(saTeleportMapInfo[i].iMapID))
				{
					pWindowMap->GetElement<UI::Text>(TEXTID_MapNameList + i)->SetColor(D3DCOLOR_XRGB(255, 255, 255));
				}
				else
				{
					pWindowMap->GetElement<UI::Text>(TEXTID_MapNameList + i)->SetColor(D3DCOLOR_XRGB(235, 0, 0));
				}
			}
		}

		pWindow->Show();
		MOUSEHANDLER->BlockMouse();
	}
}

void CTeleportCoreHandler::Close()
{
	pWindow->GetElement<UI::Text>(TEXTID_MapName)->SetText("");
	pWindow->GetElement<UI::Text>(TEXTID_MapType)->SetText("");
	pWindow->Hide();
	MOUSEHANDLER->UnblockMouse();

	pWindow->GetElement<UI::Button>(BUTTONID_Teleport)->Hide();

	pWindow->GetElement<UI::ImageBox>(IMAGEID_Minimap)->Hide();

	pWindow->GetElement<UI::ImageBox>(IMAGEID_MapTown)->Hide();
	pWindow->GetElement<UI::ImageBox>(IMAGEID_MapEXP)->Hide();
	pWindow->GetElement<UI::ImageBox>(IMAGEID_MapHunt)->Hide();
	pWindow->GetElement<UI::ImageBox>(IMAGEID_MapPVP)->Hide();
	pWindow->GetElement<UI::ImageBox>(IMAGEID_MapSolo)->Hide();

	pWindow->GetElement<UI::Text>(TEXTID_MapLevelText)->Hide();
	pWindow->GetElement<UI::Text>(TEXTID_MapLevel)->Hide();

	iMapID = -1;
}

BOOL CTeleportCoreHandler::IsOpen()
{
	return pWindow->IsOpen();
}

void CTeleportCoreHandler::BuildWindow()
{
	pWindow = std::make_shared<UI::Window>(Rectangle2D(0, 0, 364, 374));

	int iWindowWidth = pWindow->GetWidth();
	int iWindowHeight = pWindow->GetHeight();

	int iWindowX = (RESOLUTION_WIDTH >> 1) - (iWindowWidth >> 1);
	int iWindowY = (RESOLUTION_HEIGHT >> 1) - (iWindowHeight >> 1);

	pWindow->SetPosition(iWindowX, iWindowY);
	pWindow->SetImage(UI::ImageLoader::LoadImage("game\\images\\UI\\window\\window.png"));

	UI::ImageBox_ptr pHeaderBG = std::make_shared<UI::ImageBox>(Rectangle2D((iWindowWidth >> 1) - (181 >> 1), -13, 181, 32));
	pHeaderBG->SetImage(UI::ImageLoader::LoadImage("game\\images\\UI\\window\\text\\header.png"));
	pWindow->AddElement(pHeaderBG);

	UI::ImageBox_ptr pHeaderTitle = std::make_shared<UI::ImageBox>(Rectangle2D((iWindowWidth >> 1) - (61 >> 1), -4, 61, 15));
	pHeaderTitle->SetImage(UI::ImageLoader::LoadImage("game\\images\\UI\\window\\text\\header_teleport.png"));
	pWindow->AddElement(pHeaderTitle);

	UI::ImageBox_ptr pVerticalSeparator = std::make_shared<UI::ImageBox>(Rectangle2D((iWindowWidth >> 1), 26, 1, 312));
	pVerticalSeparator->SetImage(UI::ImageLoader::LoadImage("game\\images\\UI\\window\\separator_teleport_v.png"));
	pWindow->AddElement(pVerticalSeparator);

	// Minimap Image
	UI::ImageBox_ptr pMinimapImage = std::make_shared<UI::ImageBox>(Rectangle2D(186, 44, 162, 162));
	pMinimapImage->SetID(IMAGEID_Minimap);
	pMinimapImage->SetScale(0.85f);
	pMinimapImage->Hide();
	pWindow->AddElement(pMinimapImage);

	UI::Text_ptr pTextMapName = std::make_shared<UI::Text>(Rectangle2D(186, 188, 158, 30));
	pTextMapName->SetID(TEXTID_MapName);
	pTextMapName->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
	pTextMapName->SetHorizontalAlign(EAlign::ALIGN_Center);
	pTextMapName->SetVerticalAlign(EAlign::ALIGN_Middle);
	pTextMapName->SetMultiLine(TRUE);
	pTextMapName->SetWordWrap(TRUE);
	pTextMapName->SetText("");
	pWindow->AddElement(pTextMapName);

	UI::ImageBox_ptr pTownTypeImage = std::make_shared<UI::ImageBox>(Rectangle2D(194, 222, 40, 13));
	pTownTypeImage->SetID(GetMapTypeImageID(TELEPORTINFOTYPE_Town));
	pTownTypeImage->SetImage(UI::ImageLoader::LoadImage(GetMapTypeImageFile(TELEPORTINFOTYPE_Town)));
	pTownTypeImage->Hide();
	pWindow->AddElement(pTownTypeImage);

	UI::ImageBox_ptr pEXPTypeImage = std::make_shared<UI::ImageBox>(Rectangle2D(194, 222, 40, 13));
	pEXPTypeImage->SetID(GetMapTypeImageID(TELEPORTINFOTYPE_EXP));
	pEXPTypeImage->SetImage(UI::ImageLoader::LoadImage(GetMapTypeImageFile(TELEPORTINFOTYPE_EXP)));
	pEXPTypeImage->Hide();
	pWindow->AddElement(pEXPTypeImage);

	UI::ImageBox_ptr pHuntTypeImage = std::make_shared<UI::ImageBox>(Rectangle2D(194, 222, 40, 13));
	pHuntTypeImage->SetID(GetMapTypeImageID(TELEPORTINFOTYPE_Hunt));
	pHuntTypeImage->SetImage(UI::ImageLoader::LoadImage(GetMapTypeImageFile(TELEPORTINFOTYPE_Hunt)));
	pHuntTypeImage->Hide();
	pWindow->AddElement(pHuntTypeImage);

	UI::ImageBox_ptr pPVPTypeImage = std::make_shared<UI::ImageBox>(Rectangle2D(194, 222, 40, 13));
	pPVPTypeImage->SetID(GetMapTypeImageID(TELEPORTINFOTYPE_PVP));
	pPVPTypeImage->SetImage(UI::ImageLoader::LoadImage(GetMapTypeImageFile(TELEPORTINFOTYPE_PVP)));
	pPVPTypeImage->Hide();
	pWindow->AddElement(pPVPTypeImage);

	UI::ImageBox_ptr pSoloTypeImage = std::make_shared<UI::ImageBox>(Rectangle2D(194, 222, 40, 13));
	pSoloTypeImage->SetID(GetMapTypeImageID(TELEPORTINFOTYPE_Solo));
	pSoloTypeImage->SetImage(UI::ImageLoader::LoadImage(GetMapTypeImageFile(TELEPORTINFOTYPE_Solo)));
	pSoloTypeImage->Hide();
	pWindow->AddElement(pSoloTypeImage);

	UI::ImageBox_ptr pManaTypeImage = std::make_shared<UI::ImageBox>(Rectangle2D(194, 222, 40, 13));
	pManaTypeImage->SetID(GetMapTypeImageID(TELEPORTINFOTYPE_Mana));
	pManaTypeImage->SetImage(UI::ImageLoader::LoadImage(GetMapTypeImageFile(TELEPORTINFOTYPE_Mana)));
	pManaTypeImage->Hide();
	pWindow->AddElement(pManaTypeImage);

	UI::Text_ptr pTextMapType = std::make_shared<UI::Text>(Rectangle2D(194, 242, 156, 42));
	pTextMapType->SetID(TEXTID_MapType);
	pTextMapType->SetFont("Arial", 14, 0, FALSE, FALSE, -1);
	pTextMapType->SetHorizontalAlign(EAlign::ALIGN_Left);
	pTextMapType->SetMultiLine(TRUE);
	pTextMapType->SetWordWrap(TRUE);
	pTextMapType->SetText("");
	pWindow->AddElement(pTextMapType);

	UI::Text_ptr pTextMapLevelText = std::make_shared<UI::Text>(Rectangle2D(194, 288, 80, 18));
	pTextMapLevelText->SetID(TEXTID_MapLevelText);
	pTextMapLevelText->SetFont("Arial", 14, 0, FALSE, TRUE, -1);
	pTextMapLevelText->SetText("");
	pWindow->AddElement(pTextMapLevelText);

	UI::Text_ptr pTextMapLevel = std::make_shared<UI::Text>(Rectangle2D(274, 288, 70, 18));
	pTextMapLevel->SetID(TEXTID_MapLevel);
	pTextMapLevel->SetFont("Arial", 14, 0, FALSE, FALSE, -1);
	pTextMapLevel->SetText("");
	pWindow->AddElement(pTextMapLevel);

	UI::Button_ptr pButtonTeleport = std::make_shared<UI::Button>(Rectangle2D((iWindowWidth >> 1) + 6, 308, 153, 29));
	pButtonTeleport->SetID(BUTTONID_Teleport);
	pButtonTeleport->SetActiveImage(UI::ImageLoader::LoadActiveImage(
		"game\\images\\events\\teleport\\btnteleport.png",
		"game\\images\\events\\teleport\\btnteleport_.png"));
	pButtonTeleport->SetEvent(UI::Event::Build(std::bind(&CTeleportCoreHandler::OnClickTeleport, this, std::placeholders::_1)));
	pButtonTeleport->Hide();
	pWindow->AddElement(pButtonTeleport);

	UI::List_ptr pListMap = std::make_shared<UI::List>(Rectangle2D(16, 27, 166, 310));
	pListMap->SetID(LISTID_Map);
	pListMap->MakeScrollBar(Rectangle2D(158, 4, 6, 300), "game\\images\\UI\\scroll\\barbg_v.png", "game\\images\\UI\\scroll\\icon_2.png");
	pListMap->SetPaddingSeparator(1);

	int iMapCount = 0;
	for (int i = 0; i < _countof(saTeleportMapInfo); i++)
	{
		if (saTeleportMapInfo[i].bEnabled && (MAPLEVEL(saTeleportMapInfo[i].iMapID) < 200))
		{
			UI::Window_ptr pWindowMapName = std::make_shared<UI::Window>(Rectangle2D(0, 0, 166, 32));
			pWindowMapName->SetID(WINDOWID_Map + i);

			UI::ImageBox_ptr pMapTypeImage = std::make_shared<UI::ImageBox>(Rectangle2D(2, (28 >> 1) - (13 >> 1), 40, 13));
			pMapTypeImage->SetImage(UI::ImageLoader::LoadImage(GetMapTypeImageFile(saTeleportMapInfo[i].iMapTypeFirst)));
			pWindowMapName->AddElement(pMapTypeImage);

			UI::Text_ptr pTextMapName = std::make_shared<UI::Text>(Rectangle2D(42, 0, 114, 28));
			pTextMapName->SetID(TEXTID_MapNameList + i);
			pTextMapName->SetFont("Arial", 14, 0, FALSE, FALSE, -1);
			pTextMapName->SetHorizontalAlign(EAlign::ALIGN_Center);
			pTextMapName->SetVerticalAlign(EAlign::ALIGN_Middle);
			pTextMapName->SetMultiLine(TRUE);
			pTextMapName->SetWordWrap(TRUE);
			pTextMapName->SetTextEx("%s", pszaMapsName[saTeleportMapInfo[i].iMapID]);
			pTextMapName->SetColorHover(D3DCOLOR_XRGB(255, 165, 0));
			pTextMapName->SetEvent(UI::Event::Build(std::bind(&CTeleportCoreHandler::OnClickMap, this, saTeleportMapInfo[i].iMapID, iMapCount, std::placeholders::_1)));
			pWindowMapName->AddElement(pTextMapName);

			UI::ImageBox_ptr pHorizontalSeparator = std::make_shared<UI::ImageBox>(Rectangle2D(0, 31, 165, 1));
			pHorizontalSeparator->SetImage(UI::ImageLoader::LoadImage("game\\images\\UI\\window\\separator_teleport_h.png"));
			pWindowMapName->AddElement(pHorizontalSeparator);

			pListMap->AddWindow(pWindowMapName);

			iMapCount++;
		}
	}

	pWindow->AddElement(pListMap);

	UI::Button_ptr pButtonClose = std::make_shared<UI::Button>(Rectangle2D((iWindowWidth >> 1) - (93 >> 1), 342, 93, 23));
	pButtonClose->SetImage(UI::ImageLoader::LoadImage("game\\images\\UI\\window\\btnclose.png"));
	pButtonClose->SetActiveImage(UI::ImageLoader::LoadActiveImage(
		"game\\images\\UI\\window\\btnclose.png",
		"game\\images\\UI\\window\\btnclose_.png"));
	pButtonClose->SetEvent(UI::Event::Build(std::bind(&CTeleportCoreHandler::OnButtonCloseClick, this, std::placeholders::_1)));
	pWindow->AddElement(pButtonClose);


	pWindow->Hide();
}

void CTeleportCoreHandler::OnClickMap(int iMapID, int iIndex, UIEventArgs eArgs)
{
	if (MESSAGEBOX->IsOpen())
		return;

	ETeleportMapInfoType iMapType = TELEPORTINFOTYPE_Town;
	for (int i = 0; i < _countof(saTeleportMapInfo); i++)
	{
		if (saTeleportMapInfo[i].iMapID == iMapID)
		{
			iMapType = saTeleportMapInfo[i].iMapTypeFirst;
			break;
		}
	}

	const char * pszMinimapFile = nullptr;

	if (iIndex >= 0 && iIndex < _countof(CUSTOM_MINIMAP_PATHS))
	{
		const char * pszCustomMinimapFile = CUSTOM_MINIMAP_PATHS[iIndex];

		if (pszCustomMinimapFile && pszCustomMinimapFile[0] && FILEEXIST(pszCustomMinimapFile))
			pszMinimapFile = pszCustomMinimapFile;
	}

	if (pszMinimapFile == nullptr)
		pszMinimapFile = MAPGAME->GetBaseMapGame()[iMapID].szMiniMapFilePath;

	pWindow->GetElement<UI::ImageBox>(IMAGEID_Minimap)->SetImage(UI::ImageLoader::LoadImage(pszMinimapFile));

	pWindow->GetElement<UI::ImageBox>(IMAGEID_Minimap)->Show();
	this->iMapID = iMapID;

	pWindow->GetElement<UI::Text>(TEXTID_MapName)->SetTextEx("%s", pszaMapsName[iMapID]);

	// 1. Esconde todos os ícones (Obrigatório antes de tentar mostrar)
	pWindow->GetElement<UI::ImageBox>(IMAGEID_MapTown)->Hide();
	pWindow->GetElement<UI::ImageBox>(IMAGEID_MapEXP)->Hide();
	pWindow->GetElement<UI::ImageBox>(IMAGEID_MapHunt)->Hide();
	pWindow->GetElement<UI::ImageBox>(IMAGEID_MapPVP)->Hide();
	pWindow->GetElement<UI::ImageBox>(IMAGEID_MapSolo)->Hide();
	pWindow->GetElement<UI::ImageBox>(IMAGEID_MapMana)->Hide();
	pWindow->GetElement<UI::ImageBox>(GetMapTypeImageID(iMapType))->SetPosition(194, 222);
	pWindow->GetElement<UI::ImageBox>(GetMapTypeImageID(iMapType))->Show();

	int iInfoMapaIndex = -1;

	if (iIndex >= 0 && iIndex < _countof(INFO_MAPA))
	{
		iInfoMapaIndex = iIndex;
	}

	if (iInfoMapaIndex != -1)
	{
		pWindow->GetElement<UI::Text>(TEXTID_MapType)->SetText(INFO_MAPA[iInfoMapaIndex]);
		pWindow->GetElement<UI::Text>(TEXTID_MapType)->Show();
	}
	else
	{
		pWindow->GetElement<UI::Text>(TEXTID_MapType)->SetText("Guia no disponible para este mapa.");
		pWindow->GetElement<UI::Text>(TEXTID_MapType)->Show();
	}

	pWindow->GetElement<UI::Button>(BUTTONID_Teleport)->Show();

	pWindow->GetElement<UI::Text>(TEXTID_MapLevelText)->SetText("Nivel:");
	pWindow->GetElement<UI::Text>(TEXTID_MapLevel)->SetTextEx("%d", MAPLEVEL(iMapID));

	pWindow->GetElement<UI::Text>(TEXTID_MapLevelText)->Show();
	pWindow->GetElement<UI::Text>(TEXTID_MapLevel)->Show();
}

void CTeleportCoreHandler::OnClickTeleport(UIEventArgs eArgs)
{
	if (UNITDATA->sCharacterData.iLevel >= MAPLEVEL(iMapID))
	{
		MESSAGEBOX->SetBoxType(CMessageBox::BOXTYPEID_YesNo);
		MESSAGEBOX->SetTitle(pszaMapsName[iMapID]);
			MESSAGEBOX->SetDescription("Quieres teletransportarte?");
		MESSAGEBOX->SetEvent(std::bind(&CTeleportCoreHandler::OnAcceptTeleport, this, iMapID, std::placeholders::_1));
		MESSAGEBOX->Show();
	}
	else
			TITLEBOX("Debes ser nivel %d o superior para teletransportarte!", MAPLEVEL(iMapID));
}

void CTeleportCoreHandler::OnAcceptTeleport(int iMapID, UIEventArgs eArgs)
{
	if (MESSAGEBOX->GetType())
	{
		ItemData* pcItemData = ITEMHANDLER->GetItemInventory(iItemID, iChk1, iChk2);
		if (pcItemData)
		{
			ITEMHANDLER->DropSpecialItem(pcItemData);

			TELEPORTPLAYER(iMapID);

			RESTARTCOUNTER = 70 * 10;
		}

		Close();
	}
}

void CTeleportCoreHandler::OnButtonCloseClick(UIEventArgs eArgs)
{
	Close();
}

int CTeleportCoreHandler::GetMapTypeImageID(ETeleportMapInfoType iType)
{
	if (iType == TELEPORTINFOTYPE_EXP)
		return IMAGEID_MapEXP;
	else if (iType == TELEPORTINFOTYPE_Hunt)
		return IMAGEID_MapHunt;
	else if (iType == TELEPORTINFOTYPE_PVP)
		return IMAGEID_MapPVP;
	else if (iType == TELEPORTINFOTYPE_Solo)
		return IMAGEID_MapSolo;
	else if (iType == TELEPORTINFOTYPE_Mana)
		return IMAGEID_MapMana;

	return IMAGEID_MapTown;
}

const char* CTeleportCoreHandler::GetMapTypeImageFile(ETeleportMapInfoType iType)
{
	if (iType == TELEPORTINFOTYPE_EXP)
		return "game\\images\\events\\teleport\\map_exptype.png";
	else if (iType == TELEPORTINFOTYPE_Hunt)
		return "game\\images\\events\\teleport\\map_hunttype.png";
	else if (iType == TELEPORTINFOTYPE_PVP)
		return "game\\images\\events\\teleport\\map_pvptype.png";
	else if (iType == TELEPORTINFOTYPE_Solo)
		return "game\\images\\events\\teleport\\map_solotype.png";
	else if (iType == TELEPORTINFOTYPE_Mana)
		return "game\\images\\events\\teleport\\map_manatype.png";

	return "game\\images\\events\\teleport\\map_towntype.png";
}
