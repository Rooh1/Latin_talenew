#include "stdafx.h"
#include "CMiniMapHandler.h"

CMiniMapHandler::CMiniMapHandler()
{
	bMapSelected	= FALSE;
	bMapTitleSelected = FALSE;
	sPointMouse = Point2D();

	bSelectedMapLarge = FALSE;	//For Map Title after Teleport
}

CMiniMapHandler::~CMiniMapHandler()
{
}

void CMiniMapHandler::Init()
{
	//New Map Title
	for ( size_t i = 0; i < MaxField; i++ )
		pcImageMap[i] = UI::ImageLoader::LoadImage( "game\\images\\UI\\hud\\title\\%d.png", i );

	pcBattleRoyaleBackground = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\broyale.tga");
	pcMaskBattleRoyaleBackground = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\mask_broyale.png");
	pcMaskBattleRoyaleMeteorite = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\meteorite_broyale.png");
	//pcPKChar = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\pk_char.png");

	pcMaskBackground = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\mask_minimap.tga");
	pcMaskBackgroundActive = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\mask_activeminimap.tga");
	pcBorderImageLarge = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\border_large.png");
	pcBorderImage = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\border.png");

	pcMapArrowImage = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\map_arrow.png");
	pcMapHellspawnMainImage = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\hs_main.png");
	pcMapHellspawnSecondaryImage = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\hs_sec.png");
	pcMapBossImage = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\boss_inactive.png");
	pcUserPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\arrow.png");
	pcNPCPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\npc.png");
	pcBlacksmithPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Anvil.png");
	pcMagicsmithPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Magicsmith.png");
	pcWarehousePoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Warehouse.png");
	pcUpgradePoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Aging-Mixing.png");
	pcSkillMasterPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Skill-Master.png");
	pcSupplyPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Supply.png");
	pcQuestStartPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-Start.png");
	pcQuestFinishPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-Finish.png");
	pcQuestStartDailyPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-Start-Daily.png");
	pcQuestFinishDailyPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-Finish-Daily.png");
	pcQuestStartRepeatablePoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-Start-Repeatable.png");
	pcQuestFinishRepeatablePoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-Finish-Repeatable.png");
	pcQuestProgressPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-Progress.png");
	pcTeleportPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Warp.png");
	pcBossIcon = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\boss.png");
	pcSpawnIcon = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\spawn.png");

	pcPremiumShopPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\premium-shop.png");
	pcItemDistributorPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\item-distributor.png");
	pcQuestStartSoloPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-Start-Solo-Daily.png.png");

	//NFTale Quests
	pcMapQuest80NPCPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-80-NPC.png");
	pcMapQuest85NPCPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-85-NPC.png");
	pcMapQuest90NPCPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-90-NPC.png");
	pcMapQuest95NPCPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-95-NPC.png");
	pcMapQuest100NPCPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-100-NPC.png");
	pcMapQuest105NPCPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-105-NPC.png");
	pcMapQuest110NPCPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-110-NPC.png");
	pcMapQuest115NPCPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-115-NPC.png");
	pcMapQuest120NPCPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Quest-120-NPC.png");

	//HG
	pcMapLordBabelNPCPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\HG-LB-NPC.png");
	pcMapKingFuryNPCPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\HG-KF-NPC.png");
	pcMapGrandArenaNPCPoint = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\HG-ARENA-NPC.png");

	pcGoldWolverineIcon = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Wolverine-Golden.png");
	pcSilverWolverineIcon = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Wolverine-Silver.png");
	pcBronzeWolverineIcon = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\Wolverine-Bronze.png");

	pcImageSantaSkeletonIcon = UI::ImageLoader::LoadImage( "game\\images\\UI\\hud\\minimap\\santa_skeleton.bmp" );
	pcImageSantaGoblinIcon = UI::ImageLoader::LoadImage( "game\\images\\UI\\hud\\minimap\\santa_goblin.bmp" );
	pcImageGinkoBearIcon = UI::ImageLoader::LoadImage( "game\\images\\UI\\hud\\minimap\\ginko_bear.bmp" );
	pcImageLovelyBearIcon = UI::ImageLoader::LoadImage( "game\\images\\UI\\hud\\minimap\\lovely_bear.bmp" );

	pcImageHalloweenBearIcon = UI::ImageLoader::LoadImage( "game\\images\\UI\\hud\\minimap\\hw_bear.bmp" );

	pEffectMask = GetGraphicsDevice()->GetEffectFactory()->MakeEffect("game\\scripts\\shaders\\UI\\Minimap.fx");
	pRenderTargetMask = GetGraphicsDevice()->MakeRenderTarget(1000, MINIMAP_SMALL_SIZE, MINIMAP_SMALL_SIZE);
	pcImageRaidIcon = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\party\\raidmember.png");

	pTooltipUnit = std::make_shared<UI::Tooltip>(Rectangle2D());
	pTooltipUnit->Init();
	pTooltipUnit->SetFont("Arial", 16, -1);
	pTooltipUnit->SetPosition(TOOLTIPPOSITION_Top);
	pTooltipUnit->SetFollowMouse(FALSE);
	pTooltipUnit->SetHover(TRUE);
	pTooltipUnit->Open();

	pcImagePlayerIcon = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\player.png");
	pcImageUnknownIcon = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\unknown.png");
	pcImageEnemyIcon = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\enemy.png");
	pcImageFriendlyIcon = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\friendly.png");
	pcImageNextBoss = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\minimap\\nextboss.png");

	//iMiniMapIndicatorFont = FONTHANDLER->CreateFont("Arvo", 12, 0, FALSE, TRUE, -1);

	pFontMap = GetGraphicsDevice()->GetFontFactory()->MakeFont(nullptr, "Arial", 14, 0, FALSE, FALSE);

	for (size_t i = 0; i < MAX_PARTY_MEMBERS; i++)
		pcaImagesPartyMemberIcon[i] = UI::ImageLoader::LoadImage("game\\images\\UI\\hud\\party\\member%d.png", i + 1);

	ResetMiniMapScreenPositions();

}

void CMiniMapHandler::ResetMiniMapScreenPositions()
{
	iMiniMapSmallScreenPositionX = (RESOLUTION_WIDTH - MINIMAP_SMALL_SIZE) - 16;
	iMiniMapSmallScreenPositionY = (RESOLUTION_HEIGHT - MINIMAP_SMALL_SIZE) - 50;

	iMiniMapLargeScreenPositionX = (RESOLUTION_WIDTH - MINIMAP_LARGE_SIZE) - 16;
	iMiniMapLargeScreenPositionY = (RESOLUTION_HEIGHT - MINIMAP_LARGE_SIZE) - 50;

	if (bLargeMiniMap)
	{
		iMiniMapScreenPositionX = iMiniMapLargeScreenPositionX;
		iMiniMapScreenPositionY = iMiniMapLargeScreenPositionY;
	}
	else
	{
		iMiniMapScreenPositionX = iMiniMapSmallScreenPositionX;
		iMiniMapScreenPositionY = iMiniMapSmallScreenPositionY;
	}

	SetMiniMapBox(Rectangle2D(iMiniMapScreenPositionX, iMiniMapScreenPositionY, iMiniMapSize, iMiniMapSize));

}

void CMiniMapHandler::Render()
{
	if (Game::GetGameMode() == GAMEMODE_InGame && ISSHOW_MINIMAP && (MAP_ID != MAPID_ChessRoom && MAP_ID != MAPID_QuestArena && MAP_ID != MAPID_GhostCastle && MAP_ID != MAPID_ForestDungeon && MAP_ID != MAPID_DragonsDungeon))
	{
		bIsHoverUnit = FALSE;

		//Render Minimaps
		RenderMap( UNIT->GetPosition() );

		//Render Border (always do - to force border to be shown regardless of settings. It is off by default)

		int iBorderWidth = 144;
		int iBorderHeight = 158;

		if ( bLargeMiniMap )
		{
			//256 is the added width / height to the original mini map border
			// to get the larger version
			iBorderWidth += 256;
			iBorderHeight += 256;
		}

		//Start Map Title Show
		if ( UNITDATA->iLoadedMapIndex >= 0 )
			UI::ImageRender::Render( GetMiniMapData( UNITDATA->iLoadedMapIndex )->psTextureTitle->pcD3DTexture, GetMiniMapPostion().iX - 1, GetMiniMapPostion().iY - GetMiniMapData( UNITDATA->iLoadedMapIndex )->psTextureTitle->iHeight, GetMiniMapData( UNITDATA->iLoadedMapIndex )->psTextureTitle->iWidth, GetMiniMapData( UNITDATA->iLoadedMapIndex )->psTextureTitle->iHeight, 0, 0, -1, FALSE );
		else
			UI::ImageRender::Render( GetMiniMapData( 0 )->psTextureTitle->pcD3DTexture, GetMiniMapPostion().iX - 1, GetMiniMapPostion().iY - GetMiniMapData( 0 )->psTextureTitle->iHeight, GetMiniMapData( 0 )->psTextureTitle->iWidth, GetMiniMapData( 0 )->psTextureTitle->iHeight, 0, 0, -1, FALSE );
			
		if ( bShowImgMap )
		{
			UI::ImageRender::Render(pcImageMap[CHARACTERGAME->GetStageID()], (RESOLUTION_WIDTH >> 1) - (pcImageMap[CHARACTERGAME->GetStageID()]->GetWidth() >> 1), 100, pcImageMap[CHARACTERGAME->GetStageID()]->GetWidth(), pcImageMap[CHARACTERGAME->GetStageID()]->GetHeight(), -1);
		}
		//End Title Map Show

		//if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera != TRUE )
			UI::ImageRender::Render( bLargeMiniMap ? pcBorderImageLarge : pcBorderImage, GetMiniMapPostion().iX - 9, GetMiniMapPostion().iY - 24, iBorderWidth, iBorderHeight, -1 );

		auto miniMapData = UNITDATA->iLoadedMapIndex >= 0 ? GetMiniMapData(UNITDATA->iLoadedMapIndex) : GetMiniMapData(0);
		auto textureTitle = miniMapData->psTextureTitle;

		int miniMapiX = GetMiniMapPostion().iX;
		int miniMapiY = GetMiniMapPostion().iY - textureTitle->iHeight;

		//if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera != TRUE )
			UI::ImageRender::Render(textureTitle->pcD3DTexture, miniMapiX - 1, miniMapiY, textureTitle->iWidth, textureTitle->iHeight, 0, 0, -1, FALSE);

		if ( bShowBossTime && SETTINGSHANDLER->GetModel()->GetSettings().bShowNextBossTimer )
		{
			int iHour	= (dwNextBossTime / 3600) % 60;
			int iMinute = (dwNextBossTime / 60) % 60;
			int iSecond = dwNextBossTime % 60;

			UI::ImageRender::Render( pcImageNextBoss, miniMapiX - 5, miniMapiY - 24, 130, 23, -1 );
			//FONTHANDLER->Draw( iFontID, miniMapiX + 20, miniMapiY - 20, FormatString( "Siguiente jefe: %02d:%02d:%02d", iHour, iMinute, iSecond ), DT_NOCLIP, D3DCOLOR_XRGB( 255, 180, 180 ) );
			//pFontMap->Draw(FormatString("Siguiente jefe: %02d:%02d:%02d", iHour, iMinute, iSecond), GetMiniMapPostion().iX + 20, GetMiniMapPostion().iY - 40, DT_NOCLIP, DX::Color(D3DCOLOR_XRGB(255, 180, 180)));
	pFontMap->Draw(FormatString("Siguiente jefe: %02d:%02d:%02d", iHour, iMinute, iSecond), GetMiniMapPostion().iX + 20, GetMiniMapPostion().iY - 37, DT_NOCLIP, DX::Color(D3DCOLOR_XRGB(255, 180, 180)));
		}

		if( bIsHoverUnit )
		{
			pTooltipUnit->SetText( strHoverUnit );
			pTooltipUnit->SetTextColor( cHoverColor );
			pTooltipUnit->Render( sHoverUnitBox.iX + 5, sHoverUnitBox.iY, 0,0, 0, 0 );
		}
	}
}

//void CMiniMapHandler::Update(float fTime)
//{
//	dwTickTime++;
//
//	//Title Map Rodrigo
//	DWORD dwTime = TICKCOUNT;
//
//	if (bShowImgMap)
//	{
//		if (((dwTime % 45) == 0))
//		{
//			bShowImgMap = FALSE;
//		}
//	}
//
//
//	//Decrease Boss Time
//	if (dwNextBossTime > 0)
//	{
//		dwNextBossTime -= (double)fTime;
//		//Boss Time End? Hide.
//		if (dwNextBossTime <= 0)
//		{
//			dwNextBossTime = 0.0;
//
//			bShowBossTime = FALSE;
//
//			//Get new Boss Time
//			ProcessPacket(&PacketBossTimeUpdate(MAP_ID));
//		}
//	}
//
//	BATTLEROYALEHANDLER->GetWindowMinimapHUD()->SetPosition(GetMiniMapPostion().iX, GetMiniMapPostion().iY - BATTLEROYALEHANDLER->GetWindowMinimapHUD()->GetHeight() - 42);
//}

void CMiniMapHandler::Update()
{
	dwTickTime++;

	//Title Map Show
	DWORD dwTime = TICKCOUNT;

	if (bShowImgMap)
	{
		if (((dwTime % 45) == 0))
		{
			bShowImgMap = FALSE;
		}
	}

	//1 Second?
	if ((dwTickTime % 10) == 0)
	{
		//Decrease Boss Time
		if (dwNextBossTime > 0)
		{
			dwNextBossTime--;
			//Boss Time End? Hide.
			if (dwNextBossTime == 0)
			{
				bShowBossTime = FALSE;

				//Get new Boss Time
				ProcessPacket(&PacketBossTimeUpdate(MAP_ID));
			}
		}
	}
	//BATTLEROYALEHANDLER->GetWindowMinimapHUD()->SetPosition(GetMiniMapPostion().iX, GetMiniMapPostion().iY - BATTLEROYALEHANDLER->GetWindowMinimapHUD()->GetHeight() - 42);
	if (bLargeMiniMap)
	{
		BATTLEROYALEHANDLER->GetWindowMinimapHUD()->SetPosition(iMiniMapLargeScreenPositionX, iMiniMapLargeScreenPositionY - BATTLEROYALEHANDLER->GetWindowMinimapHUD()->GetHeight() - 42);
	}
	else
	{
		BATTLEROYALEHANDLER->GetWindowMinimapHUD()->SetPosition(iMiniMapSmallScreenPositionX, iMiniMapSmallScreenPositionY - BATTLEROYALEHANDLER->GetWindowMinimapHUD()->GetHeight() - 42);
	}
}

BOOL CMiniMapHandler::OnMouseClick( CMouse * pcMouse )
{
	//If mini map isn't shown
	// don't process the mouse click otherwise
	// player cannot move
	if (!ISSHOW_MINIMAP)
		FALSE;

	BOOL bRet = FALSE;

	// User clicked outside of mini map region
	if (pcMouse->GetEvent() == EMouseEvent::ClickDownL && !bActive)
		ResetMapTextureDeltas();

	if( bMapSelected || bMapTitleSelected )
	{
		if (pcMouse->GetEvent() == EMouseEvent::ClickUpL)
		{
			bMapSelected = FALSE;
			bMapTitleSelected = FALSE;
			iMiniMapDeltaXPrev = iMiniMapDeltaX;
			iMiniMapDeltaYPrev = iMiniMapDeltaY;
		}
	}
	else if (!bMapTitleSelected && !SETTINGSHANDLER->GetModel()->GetSettings().bLockUI &&
		pcMouse->GetEvent() == EMouseEvent::ClickDownL &&
		pcMouse->GetPosition()->Inside(Rectangle2D(GetMiniMapPostion().iX, GetMiniMapPostion().iY - 16, iMiniMapSize, 16)))
	{
		bMapTitleSelected = TRUE;
		bRet = TRUE;

		sPointMouse.iX = abs(pcMouse->GetPosition()->iX - GetMiniMapPostion().iX);
		sPointMouse.iY = abs(pcMouse->GetPosition()->iY - GetMiniMapPostion().iY) - 16;
	}
	else if( !bMapSelected && bLargeMiniMap &&
		pcMouse->GetEvent() == EMouseEvent::ClickDownL &&
		pcMouse->GetPosition()->Inside( Rectangle2D( GetMiniMapPostion().iX, GetMiniMapPostion().iY, iMiniMapSize, iMiniMapSize ) ) )
	{
		bMapSelected = TRUE;


		//if ( SETTINGSHANDLER->GetModel ()->GetSettings ().bARPGCamera )
		//{
		//	float fRotation = 0.25f*PI;

		//	iMouseDownInitialX = static_cast<int>( pcMouse->GetPosition()->iX * cos( fRotation ) - pcMouse->GetPosition()->iY * sin( fRotation ) );
		//	iMouseDownInitialY = static_cast<int>( pcMouse->GetPosition()->iY * cos( fRotation ) + pcMouse->GetPosition()->iX * sin( fRotation ) );
		//}
		//else
		{
			iMouseDownInitialX = pcMouse->GetPosition()->iX ;
			iMouseDownInitialY = pcMouse->GetPosition()->iY ;
		}

		bRet = TRUE;
	}

	return bRet;
}

void CMiniMapHandler::OnMouseMove( CMouse * pcMouse )
{
	Rectangle2D MapRect = Rectangle2D ( GetMiniMapPostion ().iX, GetMiniMapPostion ().iY - 16, iMiniMapSize, iMiniMapSize + 16 );

	if (pcMouse->GetPosition()->Inside(MapRect))
		bActive = TRUE;
	else
		bActive = FALSE;

	if( bMapSelected && bLargeMiniMap)
	{
		//if ( SETTINGSHANDLER->GetModel ()->GetSettings ().bARPGCamera )
		//{
		//	float fRotation = 0.25f*PI;

		//	iMiniMapDeltaX = static_cast<int>( iMiniMapDeltaXPrev + pcMouse->GetPosition()->iX * cos( fRotation ) - pcMouse->GetPosition()->iY * sin( fRotation ) - iMouseDownInitialX );
		//	iMiniMapDeltaY = static_cast<int>( iMiniMapDeltaYPrev + pcMouse->GetPosition()->iY * cos( fRotation ) + pcMouse->GetPosition()->iX * sin( fRotation ) - iMouseDownInitialY );
		//}
		//else
		{
			iMiniMapDeltaX = iMiniMapDeltaXPrev + (pcMouse->GetPosition()->iX - iMouseDownInitialX);
			iMiniMapDeltaY = iMiniMapDeltaYPrev + (pcMouse->GetPosition()->iY - iMouseDownInitialY);
		}
	}
	else if (bMapTitleSelected)
	{
		int iX = pcMouse->GetPosition()->iX - sPointMouse.iX;
		int iY = pcMouse->GetPosition()->iY - sPointMouse.iY;

		if (iX < 0)
			iX = 0;

		if (iY < 0)
			iY = 0;

		if (iY > RESOLUTION_HEIGHT - iMiniMapSize)
			iY = RESOLUTION_HEIGHT - iMiniMapSize;

		if (iX > RESOLUTION_WIDTH - iMiniMapSize)
			iX = RESOLUTION_WIDTH - iMiniMapSize;

		if (bLargeMiniMap)
		{

			iMiniMapScreenPositionX = iMiniMapLargeScreenPositionX = iX;
			iMiniMapScreenPositionY = iMiniMapLargeScreenPositionY = iY;
		}
		else
		{
			iMiniMapScreenPositionX = iMiniMapSmallScreenPositionX = iX;
			iMiniMapScreenPositionY = iMiniMapSmallScreenPositionY = iY;
		}

		SetMiniMapBox(Rectangle2D(iMiniMapScreenPositionX, iMiniMapScreenPositionY, iMiniMapSize, iMiniMapSize));
		//BATTLEROYALEHANDLER->GetWindowMinimapHUD()->SetPosition(GetMiniMapPostion().iX, GetMiniMapPostion().iY - BATTLEROYALEHANDLER->GetWindowMinimapHUD()->GetHeight() - 42);
		BATTLEROYALEHANDLER->GetWindowMinimapHUD()->SetPosition(GetMiniMapPostion().iX, GetMiniMapPostion().iY - BATTLEROYALEHANDLER->GetWindowMinimapHUD()->GetHeight() - 42);
	}
}

void CMiniMapHandler::ResetMapTextureDeltas()
{
	iMiniMapDeltaY = 0;
	iMiniMapDeltaX = 0;
	iMiniMapDeltaXPrev = 0;
	iMiniMapDeltaYPrev = 0;
}


float CMiniMapHandler::GetMapScale(EMapID mapId)
{
	float fMapSizeScale = 15.0f - ((MINIMAP_TEXTURE_SCALE * 10.0f) / 100.0f);

	if (bLargeMiniMap)
		fMapSizeScale = 15.0f;

	switch (mapId)
	{
		case MAPID_DarkSanctuary:
		case MAPID_BeehiveCave:
		case MAPID_MushroomCave:
		case MAPID_AncientDungeonF1:
		case MAPID_AncientDungeonF2:
		case MAPID_AncientDungeonF3:
			return (float)(fMapSizeScale / 1.5);

		case MAPID_PhillaiTown:
		case MAPID_CursedTempleF1:
		case MAPID_CursedTempleF2:
		case MAPID_CursedTempleF3:
		case MAPID_AncientWeapon:
			return (float)(fMapSizeScale / 1.3);

		case MAPID_QuestArena:
			return (float)( fMapSizeScale / 3.0 );
	}

	return fMapSizeScale;
}

void CMiniMapHandler::ClearSpawnFlagMarkers ()
{
	vSpawnFlags.clear();
}

//For test map only (map id = 32)
void CMiniMapHandler::AddSpawnFlagMarker (int iX, int iY, int iZ)
{
	vSpawnFlags.push_back ( Point3D ( iX, iY, iZ ) );
}

void CMiniMapHandler::RenderMap( Point3D sUserPosition )
{
	//New Render Target to render the minimap
	if (GetGraphicsDevice()->SetRenderTarget(pRenderTargetMask))
	{
		//Clear Render Target
	//	GetGraphicsDevice()->Clear(TRUE, FALSE, FALSE);
		GetGraphicsDevice()->Clear( TRUE, TRUE, TRUE );

		int firstMapId = -1;
		int secondMapId = -1;

		if ( IsCurrentUserMap( GetMiniMapData( 0 )->pcBaseMap->iMapID ) )
		{
			firstMapId = GetMiniMapData( 0 )->pcBaseMap->iMapID;
		}
		else if (IsCurrentUserSecondMap( GetMiniMapData( 0 )->pcBaseMap->iMapID ) )
		{
			secondMapId = GetMiniMapData( 0 )->pcBaseMap->iMapID;
		}

		if ( GetMiniMapData( 1 ) && GetMiniMapData( 1 )->pcBaseMap )
		{
			if ( IsCurrentUserMap( GetMiniMapData( 1 )->pcBaseMap->iMapID ) )
			{
				firstMapId = GetMiniMapData( 1 )->pcBaseMap->iMapID;
			}
			else if ( IsCurrentUserSecondMap( GetMiniMapData( 1 )->pcBaseMap->iMapID ) )
			{
				secondMapId = GetMiniMapData( 1 )->pcBaseMap->iMapID;
			}
		}

		if ( firstMapId == -1 )
			return;

		float fMapSizeScale = GetMapScale((EMapID)firstMapId);

		if (bLargeMiniMap)
		{
			SetMinimapSize(iMiniMapSize * 5.0f); //Render mask to the Render Target
		}
		else
		{
			SetMinimapSize(static_cast<float>(iMiniMapSize)); //Render mask to the Render Target
		}

		int iMinimapSize = 256 * 256 * (int)fMapSizeScale;
		int iMinimapSizeDraw = iMinimapSize;
		int iShiftX = 0;
		int iShiftY = 0;

		if (bLargeMiniMap)
		{
			iMinimapSizeDraw *= 5;
			iShiftX = -(256 * 3);
			iShiftY = -(256 * 3);
		}

		//DrawMinimap -> iMinimapSize defines the map size to be drawn
		DrawMinimap(GetMiniMapData(1), iMiniMapDeltaX + iShiftX, iMiniMapDeltaY + iShiftY, iMinimapSizeDraw);
		DrawMinimap(GetMiniMapData(0), iMiniMapDeltaX + iShiftX, iMiniMapDeltaY + iShiftY, iMinimapSizeDraw);



		int iMapID = CHARACTERGAME->GetStageID();
		BOOL bShowNPCs = SETTINGSHANDLER->GetModel()->GetSettings().bShowNPCs;

		if ( DEBUG_GM )
		{
			for ( Point3D point : vSpawnFlags )
			{
				RenderSpawnFlagMarker( point, sUserPosition, iMinimapSize );
			}
		}


		bFirstMapBossActive = FALSE;
		bSecondMapBossActive = FALSE;

		for ( int i = 0; i < MAX_UNITS; i++ )
		{
			UnitData * pc = UNITGAME->pcaUnitData + i;

			if ( pc == NULL )
				continue;

			if (pc->bActive &&
				pc->sCharacterData.iType == CHARACTERTYPE_Monster &&
				((pc->sCharacterData.bExclusiveBoss || pc->sCharacterData.sGlow == 1 ) ))
			{

				if ( pc->sCharacterData.sUnused23841212352 == firstMapId )
				{
					bFirstMapBossActive = TRUE;
					continue;
				}
				else if ( pc->sCharacterData.sUnused23841212352 == secondMapId )
				{
					bSecondMapBossActive = TRUE;
					continue;
				}

				if ( bFirstMapBossActive && bSecondMapBossActive )
					break;
			}
		}


		//Units
		for ( int i = 0; i < MAX_UNITS; i++ )
		{
			UnitData * pc = UNITGAME->pcaUnitData + i;

			if ( &pc == nullptr )
				continue;

			if ( RenderQuestMonsters( pc, sUserPosition, iMinimapSize ) )
				continue;

			if ( RenderBoss( pc, sUserPosition, iMinimapSize ) )
				continue;


			if ( SETTINGSHANDLER->GetModel()->GetSettings().bShowNPCs )
				if ( RenderNPC( pc, sUserPosition, iMinimapSize ) )
					continue;

			if ( RenderMonster( pc, sUserPosition, iMinimapSize ) )
				continue;

			if ( pc->iLoadedMapIndex >= 0 && pc->bActive && ( FIELDGAME[pc->iLoadedMapIndex]->iMapID == iMapID ) )
			{
				if ( RenderPlayer( pc, sUserPosition, UNITDATA->sCharacterData.iClanID, iMinimapSize, CHARACTERGAME->GetStageID() ) )
					continue;

				RenderUnknown( pc, sUserPosition, iMinimapSize );
			}
		}

		RenderParty( sUserPosition, UNITDATA->iID, iMinimapSize );

		//Render user Point
	//	if (/*UNIT->bInvisibleInMiniMap == FALSE ||*/
	//		MAP_ID == MAPID_BlessCastle ||
	//		MAP_ID == MAPID_Bellatra)
	//	{
			RenderUser( sUserPosition, UNITDATA->sAngle, iMinimapSize );
	//	}

		SetMinimapSize( static_cast<float>( iMiniMapSize ) );

		//Back Old Render Target
		GetGraphicsDevice()->UnsetRenderTarget();

		//Set Sprite Effect...
		UI::ImageRender::SetEffect( pEffectMask );
		pEffectMask->SetTechnique( "MaskScale" );
		if ( pEffectMask->Begin() >= 0 )
		{
			//Set Texture Mask Sampler
			D3DXHANDLE hTexture = pEffectMask->Get()->GetParameterByName( 0, "MaskTexture" );
			//pEffectMask->Get()->SetTexture( hTexture, pcMaskBackgroundActive->GetTexture() );
			pEffectMask->Get()->SetTexture(hTexture, (bActive || SETTINGSHANDLER->GetModel()->GetSettings().bMinimapAlwaysActive) ? pcMaskBackgroundActive->GetTexture() : pcMaskBackground->GetTexture());
			//Rotate Minimap in ARPG Mode
			float fRotation = 0.0f;
		//	if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera )
		//		fRotation = ( ( ((PTANGLE_360*3)/8) * 360 ) / PTANGLE_360 ) + 180;

			UI::ImageRender::Render( pRenderTargetMask->GetTexture(), GetMiniMapPostion ().iX, GetMiniMapPostion ().iY, pRenderTargetMask->GetWidth (), pRenderTargetMask->GetWidth (), 0, 0, D3DCOLOR_XRGB ( 255, 255, 255 ), 1.0f, 1.0f, fRotation );

			pEffectMask->End();

		}



		UI::ImageRender::SetEffect( NULL );

		////原始代码
		//if (BATTLEROYALEHANDLER->InBattle())
		//{
		//	float fRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iRadius) / (float)((MINIMAP_TEXTURE_SCALE * MINIMAP_TEXTURE_SCALE) >> 3);
		//	float fNextRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iNextRadius) / (float)((MINIMAP_TEXTURE_SCALE * MINIMAP_TEXTURE_SCALE) >> 3);

		//	//Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sPosition, 1, 1, iMinimapSize);  //原始代码 
		//	//Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sPosition, 1, 1, iMinimapSizeDraw);
		//	//Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition,BATTLEROYALEHANDLER->GetState().sPosition.iX,  BATTLEROYALEHANDLER->GetState().sPosition.iZ,  1,1,iMinimapSize);
		//	Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition,BATTLEROYALEHANDLER->GetState().sPosition.iX,BATTLEROYALEHANDLER->GetState().sPosition.iZ, 1, 1, iMinimapSizeDraw);


		//	BOOL bInsideRadius = BATTLEROYALEHANDLER->IsInsideRadius(sUserPosition);

		//	UI::ImageRender::Render(pcMaskBattleRoyaleBackground->GetTexture(), sPosition.iX - (int)(34.0f * fRadiusScale), sPosition.iY - (int)(34.0f * fRadiusScale),
		//		pcMaskBattleRoyaleBackground->GetWidth(), pcMaskBattleRoyaleBackground->GetHeight(), 0, 0,
		//		bInsideRadius ? D3DCOLOR_XRGB(0, 160, 255) : D3DCOLOR_XRGB(70, 70, 255), fRadiusScale, fRadiusScale, 0.0f);

		//	UI::ImageRender::Render(pcMaskBattleRoyaleBackground->GetTexture(), sPosition.iX - (int)(34.0f * fNextRadiusScale), sPosition.iY - (int)(34.0f * fNextRadiusScale),
		//		pcMaskBattleRoyaleBackground->GetWidth(), pcMaskBattleRoyaleBackground->GetHeight(), 0, 0, D3DCOLOR_XRGB(255, 255, 255), fNextRadiusScale, fNextRadiusScale, 0.0f);

		//	//Have Meteorite?
		//	if (BATTLEROYALEHANDLER->GetState().iMeteoriteTime > 0)
		//	{
		//		float fMeteoriteScale = (float)(RADIUS_BATTLEROYALE_METEORITE) / (float)((MINIMAP_TEXTURE_SCALE * MINIMAP_TEXTURE_SCALE) >> 3);

		//		//Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sMeteoritePosition, 1, 1, iMinimapSize);//原始代码 
		//		//Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sPosition, 1, 1, iMinimapSizeDraw);
		//		Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sPosition.iX, BATTLEROYALEHANDLER->GetState().sPosition.iZ, 1, 1, iMinimapSizeDraw);

		//		UI::ImageRender::Render(pcMaskBattleRoyaleMeteorite->GetTexture(), sPosition.iX - (int)(33.5f * fMeteoriteScale), sPosition.iY - (int)(33.5f * fMeteoriteScale),
		//			pcMaskBattleRoyaleMeteorite->GetWidth(), pcMaskBattleRoyaleMeteorite->GetHeight(), 0, 0, D3DCOLOR_ARGB(76, 255, 0, 0), fMeteoriteScale, fMeteoriteScale, 0.0f);
		//	}
		//}
		//SetMinimapSize(static_cast<float>(iMiniMapSize));


		//修改版本V5 这里可以正常显示了，就是毒圈会显示在小地图外面，大地图毒圈位置可根据MINIMAP_TEXTURE_LARGE_SCALE的值来修正
		if (BATTLEROYALEHANDLER->InBattle())
		{
			// Calculate radius scales with fMapSizeScale taken into account
			//float fRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iRadius) / (float)((MINIMAP_TEXTURE_SCALE * MINIMAP_TEXTURE_SCALE) >> 3) ;
			//float fNextRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iNextRadius) / (float)((MINIMAP_TEXTURE_SCALE * MINIMAP_TEXTURE_SCALE) >> 3);

			float fRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iRadius) / (float)((bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) * (bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) >> 3);
			float fNextRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iNextRadius) / (float)((bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) * (bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) >> 3);

			// Use iMinimapSizeDraw to calculate the correct position
			Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sPosition, 1, 1, iMinimapSize);//  iMinimapSizeDraw

			BOOL bInsideRadius = BATTLEROYALEHANDLER->IsInsideRadius(sUserPosition);

			// 获取小地图的实际位置
			int iMiniMapPosX = (bLargeMiniMap) ? iMiniMapLargeScreenPositionX : iMiniMapSmallScreenPositionX;
			int iMiniMapPosY = (bLargeMiniMap) ? iMiniMapLargeScreenPositionY : iMiniMapSmallScreenPositionY;

			//// 如果是大地图，考虑偏移
			//if (bLargeMiniMap)
			//{
			//	// 在大地图情况下，sPosition 需要加上偏移量 iShiftX 和 iShiftY
			//	sPosition.iX += iShiftX;
			//	sPosition.iY += iShiftY;
			//}

			// Render the current radius
			UI::ImageRender::Render(pcMaskBattleRoyaleBackground->GetTexture(), 
				sPosition.iX - (int)(34.0f * fRadiusScale) + iMiniMapPosX,
				sPosition.iY - (int)(34.0f * fRadiusScale) + iMiniMapPosY,
				pcMaskBattleRoyaleBackground->GetWidth(),
				pcMaskBattleRoyaleBackground->GetHeight(),
				0, 0,
				bInsideRadius ? D3DCOLOR_XRGB(0, 160, 255) : D3DCOLOR_XRGB(70, 70, 255), fRadiusScale, fRadiusScale, 0.0f);

			// Render the next radius
			UI::ImageRender::Render(pcMaskBattleRoyaleBackground->GetTexture(), 
				sPosition.iX - (int)(34.0f * fNextRadiusScale) + iMiniMapPosX,
				sPosition.iY - (int)(34.0f * fNextRadiusScale) + iMiniMapPosY,
				pcMaskBattleRoyaleBackground->GetWidth(),
				pcMaskBattleRoyaleBackground->GetHeight(), 
				0, 0, D3DCOLOR_XRGB(255, 255, 255), fNextRadiusScale, fNextRadiusScale, 0.0f);

			// Check for Meteorite presence and render it
			if (BATTLEROYALEHANDLER->GetState().iMeteoriteTime > 0)
			{
				//float fMeteoriteScale = (float)(RADIUS_BATTLEROYALE_METEORITE) / (float)((MINIMAP_TEXTURE_SCALE * MINIMAP_TEXTURE_SCALE) >> 3);
				float fMeteoriteScale = (float)(RADIUS_BATTLEROYALE_METEORITE) / (float)((bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) * (bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) >> 3);

				// Render Meteorite
				Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sPosition, 1, 1, iMinimapSize);//iMinimapSizeDraw

				UI::ImageRender::Render(pcMaskBattleRoyaleMeteorite->GetTexture(),
					sPosition.iX - (int)(33.5f * fMeteoriteScale) + iMiniMapPosX,
					sPosition.iY - (int)(33.5f * fMeteoriteScale) + iMiniMapPosY,
					pcMaskBattleRoyaleMeteorite->GetWidth(), 
					pcMaskBattleRoyaleMeteorite->GetHeight(),
					0, 0, D3DCOLOR_ARGB(76, 255, 0, 0), fMeteoriteScale, fMeteoriteScale, 0.0f);
			}
		}
		SetMinimapSize(static_cast<float>(iMiniMapSize));


		//修改版本V6
		//if (BATTLEROYALEHANDLER->InBattle())
		//{
		//	// Calculate radius scales with fMapSizeScale taken into account
		//	//float fRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iRadius) / (float)((MINIMAP_TEXTURE_SCALE * MINIMAP_TEXTURE_SCALE) >> 3);
		//	//float fNextRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iNextRadius) / (float)((MINIMAP_TEXTURE_SCALE * MINIMAP_TEXTURE_SCALE) >> 3);

		//	float fRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iRadius) / (float)((bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) * (bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) >> 3);
		//	float fNextRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iNextRadius) / (float)((bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) * (bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) >> 3);

		//	// Use iMinimapSizeDraw to calculate the correct position
		//	Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sPosition, 1, 1, iMinimapSizeDraw);

		//	BOOL bInsideRadius = BATTLEROYALEHANDLER->IsInsideRadius(sUserPosition);

		//	// 获取小地图的实际位置
		//	int iMiniMapPosX = (bLargeMiniMap) ? iMiniMapLargeScreenPositionX : iMiniMapSmallScreenPositionX;
		//	int iMiniMapPosY = (bLargeMiniMap) ? iMiniMapLargeScreenPositionY : iMiniMapSmallScreenPositionY;

		//	// 修正毒圈的显示位置，确保不会超出小地图或大地图的范围
		//	int iMinimapSizeLimit = (bLargeMiniMap) ? 384 : 128;

		//	// 修正毒圈位置，使其不超过地图边界
		//	sPosition.iX = std::min(std::max(sPosition.iX, 0), iMinimapSizeLimit);
		//	sPosition.iY = std::min(std::max(sPosition.iY, 0), iMinimapSizeLimit);

		//	// Render the current radius
		//	UI::ImageRender::Render(pcMaskBattleRoyaleBackground->GetTexture(),
		//		sPosition.iX - (int)(34.0f * fRadiusScale) + iMiniMapPosX,
		//		sPosition.iY - (int)(34.0f * fRadiusScale) + iMiniMapPosY,
		//		pcMaskBattleRoyaleBackground->GetWidth(),
		//		pcMaskBattleRoyaleBackground->GetHeight(),
		//		0, 0,
		//		bInsideRadius ? D3DCOLOR_XRGB(0, 160, 255) : D3DCOLOR_XRGB(70, 70, 255), fRadiusScale, fRadiusScale, 0.0f);

		//	// Render the next radius
		//	UI::ImageRender::Render(pcMaskBattleRoyaleBackground->GetTexture(),
		//		sPosition.iX - (int)(34.0f * fNextRadiusScale) + iMiniMapPosX,
		//		sPosition.iY - (int)(34.0f * fNextRadiusScale) + iMiniMapPosY,
		//		pcMaskBattleRoyaleBackground->GetWidth(),
		//		pcMaskBattleRoyaleBackground->GetHeight(),
		//		0, 0, D3DCOLOR_XRGB(255, 255, 255), fNextRadiusScale, fNextRadiusScale, 0.0f);

		//	// Check for Meteorite presence and render it
		//	if (BATTLEROYALEHANDLER->GetState().iMeteoriteTime > 0)
		//	{
		//		//float fMeteoriteScale = (float)(RADIUS_BATTLEROYALE_METEORITE) / (float)((MINIMAP_TEXTURE_SCALE * MINIMAP_TEXTURE_SCALE) >> 3);
		//		float fMeteoriteScale = (float)(RADIUS_BATTLEROYALE_METEORITE) / (float)((bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) * (bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) >> 3);

		//		// Render Meteorite
		//		Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sPosition, 1, 1, iMinimapSizeDraw);

		//		UI::ImageRender::Render(pcMaskBattleRoyaleMeteorite->GetTexture(),
		//			sPosition.iX - (int)(33.5f * fMeteoriteScale) + iMiniMapPosX,
		//			sPosition.iY - (int)(33.5f * fMeteoriteScale) + iMiniMapPosY,
		//			pcMaskBattleRoyaleMeteorite->GetWidth(),
		//			pcMaskBattleRoyaleMeteorite->GetHeight(),
		//			0, 0, D3DCOLOR_ARGB(76, 255, 0, 0), fMeteoriteScale, fMeteoriteScale, 0.0f);
		//	}
		//}
		//SetMinimapSize(static_cast<float>(iMiniMapSize));

		//修改版本V8
		//if (BATTLEROYALEHANDLER->InBattle())
		//{
		//	// Calculate radius scales with fMapSizeScale taken into account
		//	float fRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iRadius) /
		//		(float)((bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) *
		//			(bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_LARGE_SCALE) >> 3);
		//	float fNextRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iNextRadius) /
		//		(float)((bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) *
		//			(bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_LARGE_SCALE) >> 3);

		//	// Use iMinimapSizeDraw to calculate the correct position
		//	Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sPosition, 1, 1, iMinimapSizeDraw);

		//	BOOL bInsideRadius = BATTLEROYALEHANDLER->IsInsideRadius(sUserPosition);

		//	// 获取小地图的实际位置
		//	int iMiniMapPosX = (bLargeMiniMap) ? iMiniMapLargeScreenPositionX : iMiniMapSmallScreenPositionX;
		//	int iMiniMapPosY = (bLargeMiniMap) ? iMiniMapLargeScreenPositionY : iMiniMapSmallScreenPositionY;

		//	// 获取小地图或大地图的尺寸限制
		//	int iMinimapSizeLimit = (bLargeMiniMap) ? 384 : 128;

		//	// 修正当前毒圈的位置，确保它不超出边界
		//	int iCurrentRadiusPosX = sPosition.iX - (int)(34.0f * fRadiusScale) + iMiniMapPosX;
		//	int iCurrentRadiusPosY = sPosition.iY - (int)(34.0f * fRadiusScale) + iMiniMapPosY;

		//	// 限制毒圈位置不超出地图边界
		//	iCurrentRadiusPosX = std::max(0, std::min(iCurrentRadiusPosX, iMinimapSizeLimit - (int)(34.0f * fRadiusScale) * 2));
		//	iCurrentRadiusPosY = std::max(0, std::min(iCurrentRadiusPosY, iMinimapSizeLimit - (int)(34.0f * fRadiusScale) * 2));

		//	// 渲染当前毒圈
		//	UI::ImageRender::Render(pcMaskBattleRoyaleBackground->GetTexture(),
		//		iCurrentRadiusPosX,
		//		iCurrentRadiusPosY,
		//		pcMaskBattleRoyaleBackground->GetWidth(),
		//		pcMaskBattleRoyaleBackground->GetHeight(),
		//		0, 0,
		//		bInsideRadius ? D3DCOLOR_XRGB(0, 160, 255) : D3DCOLOR_XRGB(70, 70, 255),
		//		fRadiusScale, fRadiusScale, 0.0f);

		//	// 修正下一个毒圈的位置，确保它不超出边界
		//	int iNextRadiusPosX = sPosition.iX - (int)(34.0f * fNextRadiusScale) + iMiniMapPosX;
		//	int iNextRadiusPosY = sPosition.iY - (int)(34.0f * fNextRadiusScale) + iMiniMapPosY;

		//	// 限制下一个毒圈位置不超出地图边界
		//	iNextRadiusPosX = std::max(0, std::min(iNextRadiusPosX, iMinimapSizeLimit - (int)(34.0f * fNextRadiusScale) * 2));
		//	iNextRadiusPosY = std::max(0, std::min(iNextRadiusPosY, iMinimapSizeLimit - (int)(34.0f * fNextRadiusScale) * 2));

		//	// 渲染下一个毒圈
		//	UI::ImageRender::Render(pcMaskBattleRoyaleBackground->GetTexture(),
		//		iNextRadiusPosX,
		//		iNextRadiusPosY,
		//		pcMaskBattleRoyaleBackground->GetWidth(),
		//		pcMaskBattleRoyaleBackground->GetHeight(),
		//		0, 0,
		//		D3DCOLOR_XRGB(255, 255, 255),
		//		fNextRadiusScale, fNextRadiusScale, 0.0f);

		//	// 检查是否有陨石并渲染它
		//	// Check for Meteorite presence and render it
		//	if (BATTLEROYALEHANDLER->GetState().iMeteoriteTime > 0)
		//	{
		//		// 计算陨石的缩放比例
		//		float fMeteoriteScale = (float)(RADIUS_BATTLEROYALE_METEORITE) /
		//			(float)((bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) *
		//				(bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_LARGE_SCALE) >> 3);

		//		// 计算陨石的渲染位置
		//		int iMeteoritePosX = sPosition.iX - (int)(33.5f * fMeteoriteScale) + iMiniMapPosX;
		//		int iMeteoritePosY = sPosition.iY - (int)(33.5f * fMeteoriteScale) + iMiniMapPosY;

		//		// 获取小地图或大地图的尺寸限制
		//		int iMinimapSizeLimit = (bLargeMiniMap) ? 384 : 128;

		//		// 限制陨石的渲染位置不超出边界
		//		iMeteoritePosX = std::max(0, std::min(iMeteoritePosX, iMinimapSizeLimit - (int)(33.5f * fMeteoriteScale) * 2));
		//		iMeteoritePosY = std::max(0, std::min(iMeteoritePosY, iMinimapSizeLimit - (int)(33.5f * fMeteoriteScale) * 2));

		//		// 渲染陨石
		//		UI::ImageRender::Render(pcMaskBattleRoyaleMeteorite->GetTexture(),
		//			iMeteoritePosX,
		//			iMeteoritePosY,
		//			pcMaskBattleRoyaleMeteorite->GetWidth(),
		//			pcMaskBattleRoyaleMeteorite->GetHeight(),
		//			0, 0,
		//			D3DCOLOR_ARGB(76, 255, 0, 0),
		//			fMeteoriteScale,
		//			fMeteoriteScale,
		//			0.0f);
		//	}

		//}

		//SetMinimapSize(static_cast<float>(iMiniMapSize));



		//修改版本V7
		//if (BATTLEROYALEHANDLER->InBattle())
		//{
		//	// 计算当前毒圈的缩放比例
		//	float fRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iRadius) /
		//		(float)((bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) *
		//			(bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) >> 3);
		//	// 计算下一个毒圈的缩放比例
		//	float fNextRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iNextRadius) /
		//		(float)((bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) *
		//			(bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) >> 3);

		//	// 使用 iMinimapSizeDraw 来计算正确的毒圈位置
		//	Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sPosition, 1, 1, iMinimapSizeDraw);

		//	// 检查玩家是否在毒圈内
		//	BOOL bInsideRadius = BATTLEROYALEHANDLER->IsInsideRadius(sUserPosition);

		//	// 获取小地图的实际位置
		//	int iMiniMapPosX = (bLargeMiniMap) ? iMiniMapLargeScreenPositionX : iMiniMapSmallScreenPositionX;
		//	int iMiniMapPosY = (bLargeMiniMap) ? iMiniMapLargeScreenPositionY : iMiniMapSmallScreenPositionY;

		//	// 设置小地图或大地图的边界限制
		//	int iMinimapSizeLimit = (bLargeMiniMap) ? 384 : 128;

		//	// 计算当前毒圈的半径
		//	int iRadiusWidth = (int)(34.0f * fRadiusScale);
		//	int iRadiusHeight = (int)(34.0f * fRadiusScale);

		//	// 修正当前毒圈的位置，使其不超过地图边界
		//	sPosition.iX = std::min(std::max(sPosition.iX, 0), iMinimapSizeLimit);
		//	sPosition.iY = std::min(std::max(sPosition.iY, 0), iMinimapSizeLimit);

		//	// 计算当前毒圈的实际渲染位置
		//	int iRenderPosX = sPosition.iX - iRadiusWidth + iMiniMapPosX;
		//	int iRenderPosY = sPosition.iY - iRadiusHeight + iMiniMapPosY;

		//	// 修正当前毒圈渲染的位置，确保不超出小地图或大地图的边界
		//	iRenderPosX = std::max(0, std::min(iRenderPosX, iMinimapSizeLimit - iRadiusWidth * 2));
		//	iRenderPosY = std::max(0, std::min(iRenderPosY, iMinimapSizeLimit - iRadiusHeight * 2));

		//	// 修正渲染宽度和高度，确保当前毒圈不会超出小地图或大地图
		//	int iRenderWidth = std::min(iRadiusWidth * 2, iMinimapSizeLimit - iRenderPosX);
		//	int iRenderHeight = std::min(iRadiusHeight * 2, iMinimapSizeLimit - iRenderPosY);

		//	// 渲染当前毒圈
		//	UI::ImageRender::Render(pcMaskBattleRoyaleBackground->GetTexture(),
		//		iRenderPosX,
		//		iRenderPosY,
		//		iRenderWidth,
		//		iRenderHeight,
		//		0, 0,
		//		bInsideRadius ? D3DCOLOR_XRGB(0, 160, 255) : D3DCOLOR_XRGB(70, 70, 255),
		//		(float)iRenderWidth / (float)pcMaskBattleRoyaleBackground->GetWidth(),
		//		(float)iRenderHeight / (float)pcMaskBattleRoyaleBackground->GetHeight(),
		//		0.0f);

		//	// 渲染下一个毒圈
		//	int iNextRadiusWidth = (int)(34.0f * fNextRadiusScale);
		//	int iNextRadiusHeight = (int)(34.0f * fNextRadiusScale);

		//	// 修正下一个毒圈的位置
		//	int iNextRenderPosX = sPosition.iX - iNextRadiusWidth + iMiniMapPosX;
		//	int iNextRenderPosY = sPosition.iY - iNextRadiusHeight + iMiniMapPosY;

		//	// 修正下一个毒圈渲染的位置，确保不超出小地图或大地图的边界
		//	iNextRenderPosX = std::max(0, std::min(iNextRenderPosX, iMinimapSizeLimit - iNextRadiusWidth * 2));
		//	iNextRenderPosY = std::max(0, std::min(iNextRenderPosY, iMinimapSizeLimit - iNextRadiusHeight * 2));

		//	// 修正渲染宽度和高度，确保下一个毒圈不会超出小地图或大地图
		//	int iNextRenderWidth = std::min(iNextRadiusWidth * 2, iMinimapSizeLimit - iNextRenderPosX);
		//	int iNextRenderHeight = std::min(iNextRadiusHeight * 2, iMinimapSizeLimit - iNextRenderPosY);

		//	// 渲染下一个毒圈
		//	UI::ImageRender::Render(pcMaskBattleRoyaleBackground->GetTexture(),
		//		iNextRenderPosX,
		//		iNextRenderPosY,
		//		iNextRenderWidth,
		//		iNextRenderHeight,
		//		0, 0,
		//		D3DCOLOR_XRGB(255, 255, 255),
		//		(float)iNextRenderWidth / (float)pcMaskBattleRoyaleBackground->GetWidth(),
		//		(float)iNextRenderHeight / (float)pcMaskBattleRoyaleBackground->GetHeight(),
		//		0.0f);

		//	// 检查是否有陨石并渲染它
		//	if (BATTLEROYALEHANDLER->GetState().iMeteoriteTime > 0)
		//	{
		//		// 计算陨石的缩放比例
		//		float fMeteoriteScale = (float)(RADIUS_BATTLEROYALE_METEORITE) /
		//			(float)((bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) *
		//				(bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_LARGE_SCALE) >> 3);

		//		// 计算陨石的宽度和高度
		//		int iMeteoriteWidth = (int)(pcMaskBattleRoyaleMeteorite->GetWidth() * fMeteoriteScale);
		//		int iMeteoriteHeight = (int)(pcMaskBattleRoyaleMeteorite->GetHeight() * fMeteoriteScale);

		//		// 计算陨石的渲染位置
		//		int iMeteoritePosX = sPosition.iX - iMeteoriteWidth + iMiniMapPosX;
		//		int iMeteoritePosY = sPosition.iY - iMeteoriteHeight + iMiniMapPosY;

		//		// 修正陨石渲染的位置，确保不超出小地图或大地图的边界
		//		iMeteoritePosX = std::max(0, std::min(iMeteoritePosX, iMinimapSizeLimit - iMeteoriteWidth));
		//		iMeteoritePosY = std::max(0, std::min(iMeteoritePosY, iMinimapSizeLimit - iMeteoriteHeight));

		//		// 渲染陨石
		//		UI::ImageRender::Render(pcMaskBattleRoyaleMeteorite->GetTexture(),
		//			iMeteoritePosX,
		//			iMeteoritePosY,
		//			iMeteoriteWidth,
		//			iMeteoriteHeight,
		//			0, 0,
		//			D3DCOLOR_ARGB(76, 255, 0, 0),
		//			fMeteoriteScale,
		//			fMeteoriteScale,
		//			0.0f);
		//	}
		//}

		//SetMinimapSize(static_cast<float>(iMiniMapSize));






		//修改版本V3
		//if (BATTLEROYALEHANDLER->InBattle())
		//{
		//	// 计算毒圈的缩放比例
		//	float fRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iRadius) / (float)((bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) * (bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) >> 3);
		//	float fNextRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iNextRadius) / (float)((bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) * (bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) >> 3);

		//	// 计算渲染大小
		//	int iMinimapSizeDraw = iMinimapSize;
		//	if (bLargeMiniMap)
		//	{
		//		iMinimapSizeDraw *= 5;  // 大地图放大5倍
		//	}

		//	// 计算渲染位置
		//	Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sPosition, 1, 1, iMinimapSizeDraw);
		//	BOOL bInsideRadius = BATTLEROYALEHANDLER->IsInsideRadius(sUserPosition);

		//	// 渲染当前毒圈
		//	UI::ImageRender::Render(
		//		pcMaskBattleRoyaleBackground->GetTexture(),
		//		sPosition.iX - (int)(34.0f * fRadiusScale), // 通过 `fRadiusScale` 调整缩放
		//		sPosition.iY - (int)(34.0f * fRadiusScale), // 通过 `fRadiusScale` 调整缩放
		//		pcMaskBattleRoyaleBackground->GetWidth(), pcMaskBattleRoyaleBackground->GetHeight(),
		//		0, 0,
		//		bInsideRadius ? D3DCOLOR_XRGB(0, 160, 255) : D3DCOLOR_XRGB(70, 70, 255),
		//		fRadiusScale, fRadiusScale, 0.0f
		//	);

		//	// 渲染下一轮毒圈
		//	UI::ImageRender::Render(
		//		pcMaskBattleRoyaleBackground->GetTexture(),
		//		sPosition.iX - (int)(34.0f * fNextRadiusScale), // 通过 `fNextRadiusScale` 调整缩放
		//		sPosition.iY - (int)(34.0f * fNextRadiusScale), // 通过 `fNextRadiusScale` 调整缩放
		//		pcMaskBattleRoyaleBackground->GetWidth(), pcMaskBattleRoyaleBackground->GetHeight(),
		//		0, 0,
		//		D3DCOLOR_XRGB(255, 255, 255),
		//		fNextRadiusScale, fNextRadiusScale, 0.0f
		//	);

		//	// 判断是否有陨石
		//	if (BATTLEROYALEHANDLER->GetState().iMeteoriteTime > 0)
		//	{
		//		// 计算陨石的缩放比例
		//		float fMeteoriteScale = (float)(RADIUS_BATTLEROYALE_METEORITE) / (float)((bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) * (bLargeMiniMap ? MINIMAP_TEXTURE_LARGE_SCALE : MINIMAP_TEXTURE_SCALE) >> 3);

		//		// 计算陨石的位置
		//		Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sMeteoritePosition, 1, 1, iMinimapSizeDraw);

		//		// 渲染陨石
		//		UI::ImageRender::Render(
		//			pcMaskBattleRoyaleMeteorite->GetTexture(),
		//			sPosition.iX - (int)(33.5f * fMeteoriteScale),
		//			sPosition.iY - (int)(33.5f * fMeteoriteScale),
		//			pcMaskBattleRoyaleMeteorite->GetWidth(), pcMaskBattleRoyaleMeteorite->GetHeight(),
		//			0, 0,
		//			D3DCOLOR_ARGB(76, 255, 0, 0), // 颜色
		//			fMeteoriteScale, fMeteoriteScale, // 缩放
		//			0.0f
		//		);
		//	}
		//}

		//SetMinimapSize(static_cast<float>(iMiniMapSize)); // 调整地图的大小


		//修改版本V2
		//if (BATTLEROYALEHANDLER->InBattle())
		//{
		//	// 使用当前地图大小来计算缩放比例
		//	float fRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iRadius) / (float)(iMinimapSize); // 基于当前地图大小计算缩放
		//	float fNextRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iNextRadius) / (float)(iMinimapSize); // 同样调整下一个圆的缩放

		//	// 计算战斗 Royale 圆圈的显示位置
		//	Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sPosition, 1, 1, iMinimapSize);

		//	// 判断玩家是否在当前的安全圈内
		//	BOOL bInsideRadius = BATTLEROYALEHANDLER->IsInsideRadius(sUserPosition);

		//	// 渲染当前安全圈
		//	UI::ImageRender::Render(pcMaskBattleRoyaleBackground->GetTexture(), sPosition.iX - (int)(34.0f * fRadiusScale), sPosition.iY - (int)(34.0f * fRadiusScale),
		//		pcMaskBattleRoyaleBackground->GetWidth(), pcMaskBattleRoyaleBackground->GetHeight(), 0, 0,
		//		bInsideRadius ? D3DCOLOR_XRGB(0, 160, 255) : D3DCOLOR_XRGB(70, 70, 255), fRadiusScale, fRadiusScale, 0.0f);

		//	// 渲染下一个安全圈
		//	UI::ImageRender::Render(pcMaskBattleRoyaleBackground->GetTexture(), sPosition.iX - (int)(34.0f * fNextRadiusScale), sPosition.iY - (int)(34.0f * fNextRadiusScale),
		//		pcMaskBattleRoyaleBackground->GetWidth(), pcMaskBattleRoyaleBackground->GetHeight(), 0, 0, D3DCOLOR_XRGB(255, 255, 255), fNextRadiusScale, fNextRadiusScale, 0.0f);

		//	// 渲染陨石圈
		//	if (BATTLEROYALEHANDLER->GetState().iMeteoriteTime > 0)
		//	{
		//		float fMeteoriteScale = (float)(RADIUS_BATTLEROYALE_METEORITE) / (float)(iMinimapSize); // 也根据当前地图大小来计算陨石的缩放

		//		// 计算陨石的显示位置
		//		Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sMeteoritePosition, 1, 1, iMinimapSize);

		//		// 渲染陨石
		//		UI::ImageRender::Render(pcMaskBattleRoyaleMeteorite->GetTexture(), sPosition.iX - (int)(33.5f * fMeteoriteScale), sPosition.iY - (int)(33.5f * fMeteoriteScale),
		//			pcMaskBattleRoyaleMeteorite->GetWidth(), pcMaskBattleRoyaleMeteorite->GetHeight(), 0, 0, D3DCOLOR_ARGB(76, 255, 0, 0), fMeteoriteScale, fMeteoriteScale, 0.0f);
		//	}
		//}


		//修改版本V1
		//if (BATTLEROYALEHANDLER->InBattle())
		//{
		//	float fRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iRadius) / (float)((MINIMAP_TEXTURE_SCALE * MINIMAP_TEXTURE_SCALE) >> 3);
		//	float fNextRadiusScale = (float)(BATTLEROYALEHANDLER->GetState().iNextRadius) / (float)((MINIMAP_TEXTURE_SCALE * MINIMAP_TEXTURE_SCALE) >> 3);

		//	//新增 放大地图
		//	// 根据 iMinimapSize 的变化调整缩放比例
		//	fRadiusScale *= (float)iMinimapSize / 128.0f;
		//	fNextRadiusScale *= (float)iMinimapSize / 128.0f;
		//	//新增 放大地图

		//	Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sPosition, 1, 1, iMinimapSize);

		//	BOOL bInsideRadius = BATTLEROYALEHANDLER->IsInsideRadius(sUserPosition);

		//	UI::ImageRender::Render(pcMaskBattleRoyaleBackground->GetTexture(), sPosition.iX - (int)(34.0f * fRadiusScale), sPosition.iY - (int)(34.0f * fRadiusScale),
		//		pcMaskBattleRoyaleBackground->GetWidth(), pcMaskBattleRoyaleBackground->GetHeight(), 0, 0,
		//		bInsideRadius ? D3DCOLOR_XRGB(0, 160, 255) : D3DCOLOR_XRGB(70, 70, 255), fRadiusScale, fRadiusScale, 0.0f);

		//	UI::ImageRender::Render(pcMaskBattleRoyaleBackground->GetTexture(), sPosition.iX - (int)(34.0f * fNextRadiusScale), sPosition.iY - (int)(34.0f * fNextRadiusScale),
		//		pcMaskBattleRoyaleBackground->GetWidth(), pcMaskBattleRoyaleBackground->GetHeight(), 0, 0, D3DCOLOR_XRGB(255, 255, 255), fNextRadiusScale, fNextRadiusScale, 0.0f);

		//	//Have Meteorite?
		//	if (BATTLEROYALEHANDLER->GetState().iMeteoriteTime > 0)
		//	{
		//		float fMeteoriteScale = (float)(RADIUS_BATTLEROYALE_METEORITE) / (float)((MINIMAP_TEXTURE_SCALE * MINIMAP_TEXTURE_SCALE) >> 3);

		//		//新增 放大地图
		//		// 根据 iMinimapSize 调整缩放
		//		fMeteoriteScale *= (float)iMinimapSize / 128.0f;
		//		//新增 放大地图

		//		Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, BATTLEROYALEHANDLER->GetState().sMeteoritePosition, 1, 1, iMinimapSize);

		//		UI::ImageRender::Render(pcMaskBattleRoyaleMeteorite->GetTexture(), sPosition.iX - (int)(33.5f * fMeteoriteScale), sPosition.iY - (int)(33.5f * fMeteoriteScale),
		//			pcMaskBattleRoyaleMeteorite->GetWidth(), pcMaskBattleRoyaleMeteorite->GetHeight(), 0, 0, D3DCOLOR_ARGB(76, 255, 0, 0), fMeteoriteScale, fMeteoriteScale, 0.0f);
		//	}
		//}

		//SetMinimapSize(128);

		if ( bUIDebug )
		{
			GRAPHICENGINE->DrawRectangle2D( Rectangle2D( GetMiniMapPostion().iX, GetMiniMapPostion().iY, iMiniMapSize, 1 ), -1 );
			GRAPHICENGINE->DrawRectangle2D( Rectangle2D( GetMiniMapPostion().iX, GetMiniMapPostion().iY + iMiniMapSize - 1, iMiniMapSize, 1 ), -1 );
			GRAPHICENGINE->DrawRectangle2D( Rectangle2D( GetMiniMapPostion().iX, GetMiniMapPostion().iY, 1, iMiniMapSize ), -1 );
			GRAPHICENGINE->DrawRectangle2D( Rectangle2D( GetMiniMapPostion().iX + iMiniMapSize - 1, GetMiniMapPostion().iY, 1, iMiniMapSize ), -1 );
		}
	}
}

void CMiniMapHandler::RenderUser(Point3D sUserPosition, Point3D sUserAngle, int iSize)
{
	Point2D sPosition = GetMinimapPositionFromCenter ( sUserPosition, sUserPosition, pcUserPoint->GetWidth () >> 1, pcUserPoint->GetHeight () >> 1, iSize );
//	Rectangle2D sBox = Rectangle2D( sPosition.iX + GetMiniMapPostion().iX, sPosition.iY + GetMiniMapPostion().iY, pcUserPoint->GetWidth(), pcUserPoint->GetHeight() );

	float fRotation = 0.0f;

	int iXLocation = sPosition.iX + GetMiniMapPostion ().iX + iMiniMapDeltaX;
	int iYLocation = sPosition.iY + GetMiniMapPostion ().iY + iMiniMapDeltaY;

	int iMapCenterX =  GetMiniMapPostion ().iX + iMiniMapSize / 2 ;
	int iMapCenterY =  GetMiniMapPostion ().iY + iMiniMapSize / 2 ;

	int iDistFromCenterX = iXLocation - iMapCenterX;
	int iDistFromCenterY = iYLocation - iMapCenterY;

	int iInputRotX = static_cast<int>( iDistFromCenterX * cos( fRotation ) - iDistFromCenterY * sin( fRotation ) );
	int iInputRotY = static_cast<int>( iDistFromCenterY * cos( fRotation ) + iDistFromCenterX * sin( fRotation ) );

	int FinalX = iMapCenterX + iInputRotX + pcUserPoint->GetWidth()/2 - 5;
	int FinalY = iMapCenterY + iInputRotY;

	Rectangle2D sBox = Rectangle2D( FinalX, FinalY, pcUserPoint->GetWidth() + 10, pcUserPoint->GetHeight() );

	//Angle of User Point
	int iAngle = ( ( sUserAngle.iY * 360 ) / PTANGLE_360 ) + 180;

	UI::ImageRender::Render ( pcUserPoint, sPosition.iX + iMiniMapDeltaX, sPosition.iY + iMiniMapDeltaY, pcUserPoint->GetWidth (), pcUserPoint->GetHeight (), 0, 0, -1, 0.7f, (float)iAngle );

	if ( MOUSEHANDLER->GetPosition()->Inside( sBox ) && MOUSEHANDLER->GetPosition()->Inside( GetMiniMapBox() ) )
	{
		bIsHoverUnit = TRUE;
		sHoverUnitBox = sBox;
		strHoverUnit = "T\372";
		cHoverColor = UI::Color( 255, 255, 255, 255 );
	}
}


BOOL CMiniMapHandler::RenderNPC( UnitData * pcUnitData, Point3D sUserPosition, int iSize )
{
	if ( pcUnitData->sCharacterData.iType == CHARACTERTYPE_NPC && pcUnitData->bActive )
	{
		UI::Image * img = pcNPCPoint;

		// Pet System
		if ( pcUnitData->sCharacterData.iOwnerID )
		{
			img = pcImageFriendlyIcon;
		}
		//Miscellaneous or Supply Store
		else if ( ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Miscellaneous Store, Rey" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Miscellaneous Store, Leia" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Dungeon Keeper" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Cursed Temple Guard" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Miscellaneous Store, Cindy" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Miscellaneous Store, Valeriya" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Marina" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Miscellaneous Store, Lynn" ) )	|| 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Miscellaneous Store, Lette" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Supply Store, Ny" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Battle Potion Store" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Rossa" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Shellbi" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Rozalie" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Kara" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Kiri" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Miscellaneous Store, Savy" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Miscellaneous Store, Eura" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Supply Store, Resia" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Miscellaneous Store, Robin" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Pitchman Dela" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Miscellaneous Store, Evy" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Miscellaneous Store, Ivonne" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Miscellaneous Store, Byant" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Miscellaneous Store, Phillya" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Miscellaneous Store, Namy" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Ruinen Kiosk" ) ) ||
			( strstr( pcUnitData->sCharacterData.szName, "Tienda Miscelanea," ) == pcUnitData->sCharacterData.szName ) ||
			( strstr( pcUnitData->sCharacterData.szName, "Tienda miscelanea," ) == pcUnitData->sCharacterData.szName ) ||
			( strstr( pcUnitData->sCharacterData.szName, "Tienda de Suministros," ) == pcUnitData->sCharacterData.szName ) )
		{
			img = pcSupplyPoint;
		}
		//Blacksmith
		else if ( ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Blacksmith Frain" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Blacksmith Andrew" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Blacksmith Umph" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Blacksmith Drol" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Blacksmith Bartz" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Blacksmith Defrain" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Blacksmith Goden" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Blacksmith Gus" ) )	|| 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Blacksmith Ruga" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Blacksmith Solo" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Blacksmith Plagueis" ) ) ||
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Herrero Frain" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Herrero Andrew" ) ) ||
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Herrero Umph" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Herrero Drol" ) ) ||
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Herrero Bartz" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Herrero Defrain" ) ) ||
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Herrero Goden" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Herrero Gus" ) ) ||
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Herrero Ruga" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Herrero Solo" ) ) ||
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Herrero Plagueis" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Herrero Dios" ) ) ||
			( strstr( pcUnitData->sCharacterData.szName, "Herrero " ) == pcUnitData->sCharacterData.szName ) )
		{
			img = pcBlacksmithPoint;
		}
		//Magicsmith
		else if ( ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Magic Store, 3rd Branch" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Witchcraft Store" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Magic Store, 2nd Branch" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Tienda M\341gica, Sucursal 3" ) ) ||
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Tienda de Hechicer\355a" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Tienda M\341gica, Sucursal 2" ) ) ||
			( strstr( pcUnitData->sCharacterData.szName, "Tienda de Magia," ) == pcUnitData->sCharacterData.szName ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Tienda de Brujeria" ) ) )
		{
			img = pcMagicsmithPoint;
		}
		//Warehousekeeper
		else if ( ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Warehouse Keeper, Doj" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Warehouse Keeper, Eura" ) ) || 
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Warehouse Keeper, Omidor" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Warehouse Keeper, Arent" ) ) || 
				( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Warehouse Keeper" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Warehouse Keeper, Lavendar" ) ) ||
				( strstr( pcUnitData->sCharacterData.szName, "Encargado del almacen" ) == pcUnitData->sCharacterData.szName ) || ( strstr( pcUnitData->sCharacterData.szName, "Encargada del almacen" ) == pcUnitData->sCharacterData.szName ) )
		{
			img = pcWarehousePoint;
		}
		//Aging & Mixing
		else if ( ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Arcane Moriph" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Mixing Craftsman, Morald" ) ) )
		{
			img = pcUpgradePoint;
		}
		//Skill Masters
		else if ( ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Witchcraft Academe, Raymon" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Skill Master, Verkan" ) ) ||
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Academia de Hechicer\355a, Raymon" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Maestro de habilidades, Verkan" ) ) ||
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Academia de Brujeria, Raymon" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Maestro de Habilidades, Verkan" ) ) )
		{
			img = pcSkillMasterPoint;
		}
		//Teleporters
			else if ( ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Mayor Maz" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Alcalde Maz" ) ) ||
				( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Skill Master, Verkan" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Maestro de habilidades, Verkan" ) ) ||
				( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Clever Daemon" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Daemon Astuto" ) ) ||
				( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Mystery Portal" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Portal Misterioso" ) ) ||
				( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Wiseman Val" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Sabio Val" ) ) ||
				( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Atlantis Ambassador, Rennan" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Embajador de Atlantis, Rennan" ) ) ||
				( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Embajador Atlantis, Rennan" ) ) )
		{
			img = pcTeleportPoint;
		}
		//Premium Shops
		else if ( ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Item Shop" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Timer Shop" ) ) ||
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Tienda de \315tems" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Tienda de Temporizadores" ) ) ||
			( strstr( pcUnitData->sCharacterData.szName, "Tienda de Articulos Especiales" ) == pcUnitData->sCharacterData.szName ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Tienda del tiempo" ) ) ||
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Tienda GM" ) ) )
		{
			img = pcPremiumShopPoint;
		}
		//Item Distributor
		else if ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Item Distributor" ) || STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Distribuidor de \315tems" ) ||
			STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Distribuidor de Items" ) )
		{
			img = pcItemDistributorPoint;
		}
		//LB/KF
		else if ( ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Albus P. W. B. Dumbledore" ) ) || ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "The Messenger, Saphir" ) ) ||
			( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "El Mensajero, Saphir" ) ) )
		{
			img = pcMapGrandArenaNPCPoint;
		}
		//QuestWindowList
		else if ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Railyway Guard" ) || STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Railway Guard" ) ||
			STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Guardia del Ferrocarril" ) )
		{
			//80
			if ( MAP_ID == MAPID_ForbiddenLand )
			{
				img = pcMapQuest80NPCPoint;
			}
			//85
			else if ( MAP_ID == MAPID_RailwayOfChaos )
			{
				img = pcMapQuest85NPCPoint;
			}
			else
			{
				img = pcNPCPoint;
			}
		}
		else if ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Eura Guard, Andrei" ) || STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Guardia de Eura, Andrei" ) ||
			STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Guardia Eura, Andrei" ) )
		{
			//90
			if ( MAP_ID == MAPID_Eura )
			{
				img = pcMapQuest90NPCPoint;
			}
			else
			{
				img = pcNPCPoint;
			}
		}
		else if ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Eura Force Master" ) || STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Maestro de Fuerza de Eura" ) ||
			STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Maestro de la Fuerza Eura" ) )
		{
			//95
			if ( MAP_ID == MAPID_Eura )
			{
				img = pcMapQuest95NPCPoint;
			}
		}
		//100
		else if ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Lost Island Guard" ) || STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Guardia de Isla Perdida" ) )
		{
			img = pcMapQuest100NPCPoint;
		}
		//105
		else if ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Lost Temple Guard" ) || STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Guardia del Templo Perdido" ) )
		{
			img = pcMapQuest105NPCPoint;
		}
		//110
		else if ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Cursed Milter" ) || STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Milter Maldito" ) )
		{
			img = pcMapQuest110NPCPoint;
		}
		//Boss Quests
		else if ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Boss Quests Advisor" ) || STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Asesor de misiones de jefes" ) ||
			STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Cazador de Jefes, William" ) )
		{
			img = pcQuestFinishPoint;
		}
		//Daily Town Quests
		else if ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Good Boy, Longbo" ) || STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Buen Chico, Longbo" ) )
		{
			if ( UNITDATA->sCharacterData.iLevel >= 80 )
			{
				if ( ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Fighter ) || ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Mechanician ) || ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Archer ) || 
						( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Pikeman ) || ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Assassin ) )
				{
					img = pcQuestFinishDailyPoint;
				}
				else
				{
					img = pcNPCPoint;
				}
			}
			else
			{
				img = pcNPCPoint;
			}
		}
		else if ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Molly, The Granny" ) || STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Molly, la Abuela" ) )
		{
			if ( UNITDATA->sCharacterData.iLevel >= 80 )
			{
				if ( ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Atalanta ) || ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Knight ) || ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Magician ) || 
						( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Priestess ) || ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Shaman ) )
				{
					img = pcQuestFinishDailyPoint;
				}
				else
				{
					img = pcNPCPoint;
				}
			}
			else
			{
				img = pcNPCPoint;
			}
		}
		//Repeatable Town Quests
			else if ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Inventor of Warpgate" ) ||
					  STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Inventor de Warpgate" ) ||
					  STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Inventor del Warpgate" ) )
		{
			int iQuestID = 3201;

			if ( ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Fighter ) || ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Mechanician ) || ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Archer ) || 
					( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Pikeman ) || ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Assassin ) )
			{
				if ( CQUESTGAME->GetQuestInstance()->GetQuest( iQuestID ) )
				{
					if ( CQUESTGAME->GetQuestInstance()->IsActiveQuest( iQuestID ) )
					{
						if ( CQUESTGAME->GetQuestInstance()->IsFinishedQuestKills( iQuestID ) )
						{
							img = pcQuestFinishRepeatablePoint;
						}
						else
						{
							img = pcQuestProgressPoint;
						}
					}
					else
					{
						img = pcQuestStartRepeatablePoint;
					}
				}
				else
				{
					img = pcNPCPoint;
				}
			}
			else
			{
				img = pcNPCPoint;
			}
		}
		else if ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Clever Newter" ) ||
				  STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Newter Astuto" ) ) 
		{
			int iQuestID = 3211;

			if ( ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Atalanta ) || ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Knight ) || ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Magician ) || 
					( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Priestess ) || ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Shaman ) )
			{
				if ( CQUESTGAME->GetQuestInstance()->GetQuest( iQuestID ) )
				{
					if ( CQUESTGAME->GetQuestInstance()->IsActiveQuest( iQuestID ) )
					{
						if ( CQUESTGAME->GetQuestInstance()->IsFinishedQuestKills( iQuestID ) )
						{
							img = pcQuestFinishRepeatablePoint;
						}
						else
						{
							img = pcQuestProgressPoint;
						}
					}
				}
				else
				{
					img = pcQuestStartRepeatablePoint;
				}
			}
			else
			{
				img = pcTeleportPoint;
			}
		}
		//Battle Town Repeatable
		else if ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Elder Wein" ) ||
				  STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Anciano Wein" ) ) 
		{
			int iQuestID = 0;

			if ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Fighter )
				iQuestID = 6001;
			else if ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Mechanician )
				iQuestID = 6002;
			else if ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Archer )
				iQuestID = 6003;
			else if ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Pikeman )
				iQuestID = 6004;
			else if ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Atalanta )
				iQuestID = 6005;
			else if ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Knight )
				iQuestID = 6006;
			else if ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Magician )
				iQuestID = 6007;
			else if ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Priestess )
				iQuestID = 6008;
			else if ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Assassin )
				iQuestID = 6009;
			else if ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Shaman )
				iQuestID = 6010;

			if ( CQUESTGAME->GetQuestInstance()->GetQuest( iQuestID ) )
			{
				if ( CQUESTGAME->GetQuestInstance()->IsActiveQuest( iQuestID ) )
				{
					if ( CQUESTGAME->GetQuestInstance()->IsFinishedQuestKills( iQuestID ) )
					{
						img = pcQuestFinishRepeatablePoint;
					}
					else
					{
						img = pcQuestProgressPoint;
					}
				}
			}
			else
			{
				img = pcQuestStartRepeatablePoint;
			}
		}
		//Beginner Quests
		else if ( STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Instructor Annie" ) ||
				  STRINGCOMPARE( pcUnitData->sCharacterData.szName, "Instructora Annie" ) )
		{
			if ( UNITDATA->sCharacterData.iLevel < 80 )
			{
				int iQuestID = 0;

				if ( ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Fighter ) || ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Mechanician ) || ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Archer ) || 
					( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Pikeman ) || ( UNITDATA->sCharacterData.iClass == CHARACTERCLASS_Assassin ) )
				{
					iQuestID = 3001;
				}
				else
				{
					iQuestID = 3011;
				}

				if ( ( CQUESTGAME->GetQuestInstance()->IsActiveQuest( iQuestID ) == FALSE ) && ( CQUESTGAME->GetQuestInstance()->IsDoneQuest( iQuestID ) == FALSE ) )
				{
					img = pcQuestStartPoint;
				}
				else if ( ( CQUESTGAME->GetQuestInstance()->IsActiveQuest( iQuestID ) == TRUE ) && ( CQUESTGAME->GetQuestInstance()->IsDoneQuest( iQuestID ) == FALSE ) )
				{
					img = pcQuestProgressPoint;
				}
				else
				{
					img = pcNPCPoint;
				}
			}
			else
			{
				img = pcNPCPoint;
			}
		}
		else
		{
			img = pcNPCPoint;
		}

		if ( img )
		{
			Point2D sPosition = GetMinimapPositionFromCenter( sUserPosition, pcUnitData->sPosition, img->GetWidth() >> 1, img->GetHeight() >> 1, iSize );

			float fRotation = 0.0f;

			int iXLocation = sPosition.iX + GetMiniMapPostion ().iX + iMiniMapDeltaX;
			int iYLocation = sPosition.iY + GetMiniMapPostion ().iY + iMiniMapDeltaY;

			int iMapCenterX =  GetMiniMapPostion ().iX + iMiniMapSize / 2 ;
			int iMapCenterY =  GetMiniMapPostion ().iY + iMiniMapSize / 2 ;

			int iDistFromCenterX = iXLocation - iMapCenterX;
			int iDistFromCenterY = iYLocation - iMapCenterY;

			int iInputRotX = static_cast<int>( iDistFromCenterX * cos( fRotation ) - iDistFromCenterY * sin( fRotation ) );
			int iInputRotY = static_cast<int>( iDistFromCenterY * cos( fRotation ) + iDistFromCenterX * sin( fRotation ) );

			int FinalX = iMapCenterX + iInputRotX + img->GetWidth()/2 - 5;
			int FinalY = iMapCenterY + iInputRotY;

			Rectangle2D sBox = Rectangle2D(FinalX, FinalY, img->GetWidth() + 10, img->GetHeight());

			float fRotationDX = 0.0f;

			UI::ImageRender::Render( img, sPosition.iX + iMiniMapDeltaX, sPosition.iY + iMiniMapDeltaY, img->GetWidth(), img->GetHeight(), 0, 0, -1, 1.0f ,fRotationDX );


			if ( MOUSEHANDLER->GetPosition()->Inside(sBox) && MOUSEHANDLER->GetPosition()->Inside( GetMiniMapBox() ) )
			{
				if ( pcUnitData->sCharacterData.iOwnerID )
				{
					if ( UNITDATA->iID == pcUnitData->sCharacterData.iOwnerID )
					{
						bIsHoverUnit = TRUE;
						sHoverUnitBox = sBox;
			strHoverUnit = "Tu mascota";
						cHoverColor = UI::Color( 255, 255, 255, 255 );
					}
					else
					{
						bIsHoverUnit = TRUE;
						sHoverUnitBox = sBox;
						strHoverUnit = pcUnitData->sCharacterData.szName;
						cHoverColor = UI::Color( 255, 175, 230, 175 );
					}
				}
				else
				{
					bIsHoverUnit = TRUE;
					sHoverUnitBox = sBox;
					strHoverUnit = pcUnitData->sCharacterData.szName;
					cHoverColor = UI::Color(255, 255, 255, 255);
				}
			}

			return TRUE;
		}
	}

	return FALSE;
}


BOOL CMiniMapHandler::RenderMonster( UnitData * pcUnitData, Point3D sUserPosition, int iSize )
{
	if ( pcUnitData->bActive == FALSE )
		return FALSE;

	if ( pcUnitData->sCharacterData.iType == CHARACTERTYPE_Monster && ( !pcUnitData->sCharacterData.bExclusiveBoss || pcUnitData->sCharacterData.sGlow == 0 ) )
	{
		//Friendly
		if ( pcUnitData->sCharacterData.iMonsterType == MONSTERTYPE_Friendly )
		{
			Point2D sPosition = GetMinimapPositionFromCenter( sUserPosition, pcUnitData->sPosition, pcImageFriendlyIcon->GetWidth() >> 1, pcImageFriendlyIcon->GetHeight() >> 1, iSize );

			float fRotation = 0.0f;

			int iXLocation = sPosition.iX + GetMiniMapPostion ().iX + iMiniMapDeltaX;
			int iYLocation = sPosition.iY + GetMiniMapPostion ().iY + iMiniMapDeltaY;

			int iMapCenterX =  GetMiniMapPostion ().iX + iMiniMapSize / 2 ;
			int iMapCenterY =  GetMiniMapPostion ().iY + iMiniMapSize / 2 ;

			int iDistFromCenterX = iXLocation - iMapCenterX;
			int iDistFromCenterY = iYLocation - iMapCenterY;

			int iInputRotX = static_cast<int>( iDistFromCenterX * cos( fRotation ) - iDistFromCenterY * sin( fRotation ) );
			int iInputRotY = static_cast<int>( iDistFromCenterY * cos( fRotation ) + iDistFromCenterX * sin( fRotation ) );

			int FinalX = iMapCenterX + iInputRotX + pcImageFriendlyIcon->GetWidth()/2 - 5;
			int FinalY = iMapCenterY + iInputRotY;

			Rectangle2D sBox = Rectangle2D( FinalX, FinalY, pcImageFriendlyIcon->GetWidth() + 10, pcImageFriendlyIcon->GetHeight() );

			float fRotationDX = 0.0f;

			UI::ImageRender::Render( pcImageFriendlyIcon, sPosition.iX + iMiniMapDeltaX, sPosition.iY + iMiniMapDeltaY, pcImageFriendlyIcon->GetWidth(), pcImageFriendlyIcon->GetHeight(), 0, 0, -1, 1.0f ,fRotationDX );


			if ( MOUSEHANDLER->GetPosition()->Inside( sBox ) && MOUSEHANDLER->GetPosition()->Inside( GetMiniMapBox() ) )
			{
				if ( STRINGCOMPARE( UNITDATA->sCharacterData.szName, pcUnitData->sCharacterData.Pet.szOwnerName ) )
				{
					bIsHoverUnit = TRUE;
					sHoverUnitBox = sBox;
				strHoverUnit = "Tu monstruo invocado";
					cHoverColor = UI::Color( 255, 255, 255, 255 );
				}
				else
				{
					bIsHoverUnit = TRUE;
					sHoverUnitBox = sBox;
					strHoverUnit = FormatString( "Monstruo invocado de %s", pcUnitData->sCharacterData.Pet.szOwnerName );
					cHoverColor = UI::Color( 255, 175, 230, 175 );
				}
			}
		}
		else if ( MAP_ID == MAPID_BattleTown )
		{
			UI::Image * img = NULL;

			if ( pcUnitData->bNoDeath )
			{
				img = pcImageEnemyIcon;
			}
			else
				img = pcSpawnIcon;

			if ( img )
			{
				Point2D sPosition = GetMinimapPositionFromCenter( sUserPosition, pcUnitData->sPosition, img->GetWidth() >> 1, img->GetHeight() >> 1, iSize );

				float fRotation = 0.0f;

				int iXLocation = sPosition.iX + GetMiniMapPostion ().iX + iMiniMapDeltaX;
				int iYLocation = sPosition.iY + GetMiniMapPostion ().iY + iMiniMapDeltaY;

				int iMapCenterX =  GetMiniMapPostion ().iX + iMiniMapSize / 2 ;
				int iMapCenterY =  GetMiniMapPostion ().iY + iMiniMapSize / 2 ;

				int iDistFromCenterX = iXLocation - iMapCenterX;
				int iDistFromCenterY = iYLocation - iMapCenterY;

				int iInputRotX = static_cast<int>( iDistFromCenterX * cos( fRotation ) - iDistFromCenterY * sin( fRotation ) );
				int iInputRotY = static_cast<int>( iDistFromCenterY * cos( fRotation ) + iDistFromCenterX * sin( fRotation ) );

				int FinalX = iMapCenterX + iInputRotX + img->GetWidth()/2 - 5;
				int FinalY = iMapCenterY + iInputRotY;

				Rectangle2D sBox = Rectangle2D( FinalX, FinalY, img->GetWidth() + 10, img->GetHeight() );

				float fRotationDX = 0.0f;

				UI::ImageRender::Render( img, sPosition.iX + iMiniMapDeltaX, sPosition.iY + iMiniMapDeltaY, img->GetWidth(), img->GetHeight(), 0, 0, -1, 1.0f ,fRotationDX );

				if ( MOUSEHANDLER->GetPosition()->Inside( sBox ) && MOUSEHANDLER->GetPosition()->Inside( GetMiniMapBox() ) )
				{
					if ( pcUnitData->bNoDeath )
					{
						bIsHoverUnit = TRUE;
						sHoverUnitBox = sBox;
				strHoverUnit = "Objetivo PvP";
						cHoverColor = UI::Color( 255, 255, 0, 0 );
					}
					else
					{
						bIsHoverUnit = TRUE;
						sHoverUnitBox = sBox;
						strHoverUnit = pcUnitData->sCharacterData.szName;
						cHoverColor = UI::Color( 255, 255, 255, 255 );
					}
				}
			}
		}
		else
		{

			//if ( MAP_ID == MAPID_BlessCastle )
			if (MAP_ID == MAPID_BlessCastle || MAP_ID == MAPID_OldRuinen2 || MAP_ID == MAPID_RoyalDesert || MAP_ID == MAPID_OasisRoyale )
				return FALSE;

			//Monsters
			Point2D sPosition = GetMinimapPositionFromCenter( sUserPosition, pcUnitData->sPosition, pcSpawnIcon->GetWidth() >> 1, pcSpawnIcon->GetHeight() >> 1, iSize );

			float fRotation = 0.0f;

			int iXLocation = sPosition.iX + GetMiniMapPostion ().iX + iMiniMapDeltaX;
			int iYLocation = sPosition.iY + GetMiniMapPostion ().iY + iMiniMapDeltaY;

			int iMapCenterX =  GetMiniMapPostion ().iX + iMiniMapSize / 2 ;
			int iMapCenterY =  GetMiniMapPostion ().iY + iMiniMapSize / 2 ;

			int iDistFromCenterX = iXLocation - iMapCenterX;
			int iDistFromCenterY = iYLocation - iMapCenterY;

			int iInputRotX = static_cast<int>( iDistFromCenterX * cos( fRotation ) - iDistFromCenterY * sin( fRotation ) );
			int iInputRotY = static_cast<int>( iDistFromCenterY * cos( fRotation ) + iDistFromCenterX * sin( fRotation ) );

			int FinalX = iMapCenterX + iInputRotX + pcSpawnIcon->GetWidth()/2 - 5;
			int FinalY = iMapCenterY + iInputRotY;

			Rectangle2D sBox = Rectangle2D( FinalX, FinalY, pcSpawnIcon->GetWidth() + 10, pcSpawnIcon->GetHeight() );

			float fRotationDX = 0.0f;

			UI::ImageRender::Render( pcSpawnIcon, sPosition.iX + iMiniMapDeltaX, sPosition.iY + iMiniMapDeltaY, pcSpawnIcon->GetWidth(), pcSpawnIcon->GetHeight(), 0, 0, -1, 1.0f ,fRotationDX );

			if ( MOUSEHANDLER->GetPosition()->Inside( sBox ) && MOUSEHANDLER->GetPosition()->Inside( GetMiniMapBox() ) )
			{
				bIsHoverUnit = TRUE;
				sHoverUnitBox = sBox;
				strHoverUnit = pcUnitData->sCharacterData.szName;
				cHoverColor = UI::Color( 255, 255, 255, 255 );
			}
		}
		
		return TRUE;
	}

	return FALSE;
}


BOOL CMiniMapHandler::RenderQuestMonsters( UnitData* pcUnitData, Point3D sUserPosition, int iSize )
{
//	if ( pcUnitData->bActive &&
//		pcUnitData->sCharacterData.iType == CHARACTERTYPE_Monster &&
//		( pcUnitData->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_WOLVERLIN ) )
	if ( pcUnitData->bActive &&
		pcUnitData->sCharacterData.iType == CHARACTERTYPE_Monster &&
		( pcUnitData->sCharacterData.iMonsterType != MONSTERTYPE_Friendly ) )
	{
		UI::Image* img = nullptr;

		if ( pcUnitData->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_WOLVERLIN )
		{
			if ( STRINGCOMPARE( pcUnitData->GetName(), "Golden Wolverine" ) )
			{
				img = pcGoldWolverineIcon;
			}
			else if ( STRINGCOMPARE( pcUnitData->GetName(), "Silver Wolverine" ) )
			{
				img = pcSilverWolverineIcon;
			}
			else if ( STRINGCOMPARE( pcUnitData->GetName(), "Bronze Wolverine" ) )
			{
				img = pcBronzeWolverineIcon;
			}
		}
		//Christmas Event
		else if ( pcUnitData->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_SKELETON )
		{
			if ( STRINGCOMPARE( pcUnitData->GetName(), "Santa Skeleton" ) )
			{
				img = pcImageSantaSkeletonIcon;
			}
		}
		else if ( pcUnitData->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_HOBGOBLIN )
		{
			if ( STRINGCOMPARE( pcUnitData->GetName(), "Santa Goblin" ) )
			{
				img = pcImageSantaGoblinIcon;
			}
		}
		//Valentines Bear
		else if ( STRINGCOMPARE( pcUnitData->GetName(), "Ginko Bear" ) )
		{
			img = pcImageGinkoBearIcon;
		}
		else if ( STRINGCOMPARE( pcUnitData->GetName(), "Lovely Bear" ) )
		{
			img = pcImageLovelyBearIcon;
		}

		if ( img )
		{
			Point2D sPosition = GetMinimapPositionFromCenter( sUserPosition, pcUnitData->sPosition, img->GetWidth() >> 1, img->GetHeight() >> 1, iSize );

			float fRotation = 0.0f;
		//	if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera )
		//		fRotation = -0.25f*PI;

			int iXLocation = sPosition.iX + GetMiniMapPostion ().iX + iMiniMapDeltaX;
			int iYLocation = sPosition.iY + GetMiniMapPostion ().iY + iMiniMapDeltaY;

			int iMapCenterX =  GetMiniMapPostion ().iX + iMiniMapSize / 2 ;
			int iMapCenterY =  GetMiniMapPostion ().iY + iMiniMapSize / 2 ;

			int iDistFromCenterX = iXLocation - iMapCenterX;
			int iDistFromCenterY = iYLocation - iMapCenterY;

			int iInputRotX = static_cast<int>( iDistFromCenterX * cos( fRotation ) - iDistFromCenterY * sin( fRotation ) );
			int iInputRotY = static_cast<int>( iDistFromCenterY * cos( fRotation ) + iDistFromCenterX * sin( fRotation ) );

			int FinalX = iMapCenterX + iInputRotX + img->GetWidth()/2 - 5;
			int FinalY = iMapCenterY + iInputRotY;

			Rectangle2D sBox = Rectangle2D( FinalX, FinalY, img->GetWidth() + 10, img->GetHeight() );

			float fRotationDX = 0.0f;
		//	if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera )
		//		fRotationDX = ( ( ((PTANGLE_360*3)/8) * -360 ) / PTANGLE_360 ) + 180;

			UI::ImageRender::Render( img, sPosition.iX + iMiniMapDeltaX, sPosition.iY + iMiniMapDeltaY, img->GetWidth(), img->GetHeight(), 0, 0, -1, 1.0f ,fRotationDX );


			if ( MOUSEHANDLER->GetPosition()->Inside(sBox) &&
				MOUSEHANDLER->GetPosition()->Inside(GetMiniMapBox() ) )
			{
				bIsHoverUnit = TRUE;
				sHoverUnitBox = sBox;
				strHoverUnit = pcUnitData->sCharacterData.szName;
				cHoverColor = UI::Color( 255, 255, 255, 255 );
			}

			return TRUE;
		}
	}

	return FALSE;
}

BOOL CMiniMapHandler::RenderBoss(UnitData* pcUnitData, Point3D sUserPosition, int iSize)
{
	if ( pcUnitData->bActive == FALSE )
		return FALSE;

	if ( MAP_ID == MAPID_BlessCastle )
		return FALSE;

	if ( pcUnitData->sCharacterData.iType == CHARACTERTYPE_Monster && ( ( pcUnitData->sCharacterData.bExclusiveBoss || pcUnitData->sCharacterData.sGlow == 1 ) ) )
	{
		//If this unit has a owner, then it's a summon
		//not an actual boss. Note
		//monster id is not 0 for pets
		if ( strlen( pcUnitData->sCharacterData.Pet.szOwnerName ) > 0 )
			return FALSE;

		Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, pcUnitData->sPosition, pcBossIcon->GetWidth() >> 1, pcBossIcon->GetHeight() >> 1, iSize);

		float fRotation = 0.0f;
	//	if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera )
	//		fRotation = -0.25f*PI;

		int iXLocation = sPosition.iX + GetMiniMapPostion ().iX + iMiniMapDeltaX;
		int iYLocation = sPosition.iY + GetMiniMapPostion ().iY + iMiniMapDeltaY;

		int iMapCenterX =  GetMiniMapPostion ().iX + iMiniMapSize / 2 ;
		int iMapCenterY =  GetMiniMapPostion ().iY + iMiniMapSize / 2 ;

		int iDistFromCenterX = iXLocation - iMapCenterX;
		int iDistFromCenterY = iYLocation - iMapCenterY;

		int iInputRotX = static_cast<int>(iDistFromCenterX  * cos ( fRotation ) - iDistFromCenterY * sin ( fRotation ));
		int iInputRotY = static_cast<int>(iDistFromCenterY * cos ( fRotation ) + iDistFromCenterX * sin ( fRotation ));

		int FinalX = iMapCenterX + iInputRotX + pcBossIcon->GetWidth()/2 - 5;
		int FinalY = iMapCenterY + iInputRotY;

		Rectangle2D sBox = Rectangle2D(FinalX, FinalY, pcBossIcon->GetWidth() + 10, pcBossIcon->GetHeight());

		float fRotationDX = 0.0f;
	//	if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera )
	//		fRotationDX = ( ( ((PTANGLE_360*3)/8) * -360 ) / PTANGLE_360 ) + 180;

		UI::ImageRender::Render(pcBossIcon, sPosition.iX + iMiniMapDeltaX, sPosition.iY + iMiniMapDeltaY, pcBossIcon->GetWidth(), pcBossIcon->GetHeight(), 0, 0, -1, 1.0f ,fRotationDX);

		if (MOUSEHANDLER->GetPosition()->Inside(sBox) &&
			MOUSEHANDLER->GetPosition()->Inside(GetMiniMapBox()))
		{
			bIsHoverUnit = TRUE;
			sHoverUnitBox = sBox;
			strHoverUnit = pcUnitData->sCharacterData.szName;
			cHoverColor = UI::Color( 255, 255, 0, 0 );
		}

		return TRUE;
	}

	return FALSE;
}

BOOL CMiniMapHandler::RenderPlayer( UnitData * pcUnitData, Point3D sUserPosition, int iUserClanID, int iSize, int mapID )
{
	if (BATTLEROYALEHANDLER->InWaiting() || BATTLEROYALEHANDLER->InBattle())
		return TRUE;

	if( pcUnitData->iCharacterType == CHARACTERTYPE_Player || pcUnitData->sCharacterData.iType == CHARACTERTYPE_Player )
	{
		Unit * pcUnit = UNITDATATOUNIT( pcUnitData );

		//Allied Clan
		if( pcUnitData->sCharacterData.iClanID > 0 && pcUnitData->sCharacterData.iClanID == iUserClanID && SETTINGSHANDLER->GetModel()->GetSettings().bShowClanMembers )
		{
			if ( MAP_ID == MAPID_BattleTown )
				return TRUE;

			Point2D sPosition = GetMinimapPositionFromCenter( sUserPosition, pcUnitData->sPosition, pcImageFriendlyIcon->GetWidth() >> 1, pcImageFriendlyIcon->GetHeight() >> 1, iSize );

			float fRotation = 0.0f;
		//	if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera )
		//		fRotation = -0.25f*PI;

			float iXLocation = static_cast<float>( sPosition.iX + GetMiniMapPostion().iX + iMiniMapDeltaX );
			float iYLocation = static_cast<float>( sPosition.iY + GetMiniMapPostion().iY + iMiniMapDeltaY );

			float iMapCenterX = GetMiniMapPostion ().iX + iMiniMapSize / 2.0f;
			float iMapCenterY = GetMiniMapPostion ().iY + iMiniMapSize / 2.0f;

			float iDistFromCenterX = iXLocation - iMapCenterX;
			float iDistFromCenterY = iYLocation - iMapCenterY;

			float iInputRotX = iDistFromCenterX  * cos ( fRotation ) - iDistFromCenterY * sin ( fRotation );
			float iInputRotY = iDistFromCenterY * cos ( fRotation ) + iDistFromCenterX * sin ( fRotation );

			int FinalX = static_cast<int>( iMapCenterX + iInputRotX + pcImageFriendlyIcon->GetWidth() / 2 - 5 );
			int FinalY = static_cast<int>( iMapCenterY + iInputRotY );

			Rectangle2D sBox = Rectangle2D(FinalX, FinalY, pcImageFriendlyIcon->GetWidth() + 10, pcImageFriendlyIcon->GetHeight());

			float fRotationDX = 0.0f;
		//	if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera )
		//		fRotationDX = ( ( ((PTANGLE_360*3)/8) * -360 ) / PTANGLE_360 ) + 180;

			UI::ImageRender::Render(pcImageFriendlyIcon, sPosition.iX + iMiniMapDeltaX, sPosition.iY + iMiniMapDeltaY, pcImageFriendlyIcon->GetWidth(), pcImageFriendlyIcon->GetHeight(), 0, 0, -1, 1.0f ,fRotationDX);

			if (MOUSEHANDLER->GetPosition()->Inside(sBox) &&
				MOUSEHANDLER->GetPosition()->Inside(GetMiniMapBox()))
			{
				if (&pcUnitData->sCharacterData)
				{
					std::string strLevel = std::to_string(pcUnitData->sCharacterData.iLevel);
					bool bTwoDigitLevel = strLevel.size() > 1 ? true : false;

					char fullStr[32] = { 0 };
					STRINGFORMAT(fullStr, "%s (%s%c)", pcUnitData->GetName(), bTwoDigitLevel ? strLevel.substr(0, strLevel.size() - 1).c_str() : strLevel.c_str(), bTwoDigitLevel ? 'x' : NULL);

					strHoverUnit = fullStr;
				}
				else
				{
					strHoverUnit = pcUnitData->GetName();
				}

				bIsHoverUnit = TRUE;
				sHoverUnitBox = sBox;
				cHoverColor = UI::Color( 255, 175, 230, 175 );
			}
		}
		else if(pcUnit->bPvPMode && MAP_ID == MAPID_BlessCastle && SETTINGSHANDLER->GetModel()->GetSettings().bShowEnemies )	//OG
	//	else if ( ( MAP_ID == MAPID_BlessCastle && SETTINGSHANDLER->GetModel()->GetSettings().bShowEnemies ) || ( MAP_ID == MAPID_BattleTown && SETTINGSHANDLER->GetModel()->GetSettings().bShowEnemies ) )
		{
			//Enemy Clan

			Point2D sPosition = GetMinimapPositionFromCenter( sUserPosition, pcUnitData->sPosition, pcImageEnemyIcon->GetWidth() >> 1, pcImageEnemyIcon->GetHeight() >> 1, iSize );

			Rectangle2D sBox = Rectangle2D(sPosition.iX + GetMiniMapPostion().iX + iMiniMapDeltaX, sPosition.iY + GetMiniMapPostion().iY + iMiniMapDeltaY, pcImageEnemyIcon->GetWidth(), pcImageEnemyIcon->GetHeight());

			UI::ImageRender::Render( pcImageEnemyIcon, sPosition.iX + iMiniMapDeltaX, sPosition.iY + iMiniMapDeltaY, pcImageEnemyIcon->GetWidth(), pcImageEnemyIcon->GetHeight(), 0, 0, -1 );

			if (MOUSEHANDLER->GetPosition()->Inside(sBox) &&
				MOUSEHANDLER->GetPosition()->Inside(GetMiniMapBox()))
			{
				bIsHoverUnit = TRUE;
				sHoverUnitBox = sBox;
				//strHoverUnit = pcUnitData->sCharacterData.szName;
				strHoverUnit = "Enemigo";
				cHoverColor = UI::Color( 255, 255, 0, 0 );
			}
		}
	//	else if (mapID != MAPID_RicartenTown &&
	//			 mapID != MAPID_PhillaiTown &&
	//			 mapID != MAPID_BlessCastle)
		else
		{
			//Other players
			if ( PARTYHANDLER->GetPartyData().iMembersCount > 0 )
			{
				for ( int i = 0; i < PARTYHANDLER->GetPartyData().iMembersCount; i++ )
				{
					PartyMember sMember = PARTYHANDLER->GetPartyData().saMembers[i];

					//Don't render icon if player is in party. A party icon will be rendered instead
					if ( strcmp(sMember.szCharacterName, pcUnitData->GetName() ) == 0 )
						return TRUE; //need to be true here. see logic above
				}
			}


			Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, pcUnitData->sPosition, pcImagePlayerIcon->GetWidth() >> 1, pcImagePlayerIcon->GetHeight() >> 1, iSize);
			Rectangle2D sBox = Rectangle2D(sPosition.iX + GetMiniMapPostion().iX + iMiniMapDeltaX, sPosition.iY + GetMiniMapPostion().iY + iMiniMapDeltaY, pcImagePlayerIcon->GetWidth(), pcImagePlayerIcon->GetHeight());
			UI::ImageRender::Render(pcImagePlayerIcon, sPosition.iX + iMiniMapDeltaX, sPosition.iY + iMiniMapDeltaY, pcImagePlayerIcon->GetWidth(), pcImagePlayerIcon->GetHeight(), 0, 0, -1);

			if (MOUSEHANDLER->GetPosition()->Inside(sBox) &&
				MOUSEHANDLER->GetPosition()->Inside(GetMiniMapBox()))
			{
				if (&pcUnitData->sCharacterData)
				{
					std::string strLevel = std::to_string(pcUnitData->sCharacterData.iLevel);
					bool bTwoDigitLevel = strLevel.size() > 1 ? true : false;

					char fullStr[32] = { 0 };
					STRINGFORMAT(fullStr, "%s (%s%c)", pcUnitData->GetName(), bTwoDigitLevel ? strLevel.substr(0, strLevel.size() - 1).c_str() : strLevel.c_str(), bTwoDigitLevel ? 'x' : NULL);

					strHoverUnit = fullStr;
				}
				else
				{
					strHoverUnit = pcUnitData->GetName();
				}

				bIsHoverUnit = TRUE;
				sHoverUnitBox = sBox;
 				cHoverColor = UI::Color( 255, 175, 230, 175 );
			}
		}

		return TRUE;
	}

	return FALSE;
}

/// <summary>
/// For unknown char type.
/// </summary>
BOOL CMiniMapHandler::RenderUnknown( UnitData * pcUnitData, Point3D sUserPosition, int iSize )
{
	if ( pcUnitData->bActive &&
		pcUnitData->sCharacterData.iType == CHARACTERTYPE_Monster &&
		( pcUnitData->sCharacterData.iMonsterEffectID == MONSTEREFFECTID_WOLVERLIN ) )
	{
		return FALSE;
	}

	if (pcUnitData->bActive &&
		pcUnitData->sCharacterData.iType == CHARACTERTYPE_Monster &&
		( ( pcUnitData->sCharacterData.bExclusiveBoss || pcUnitData->sCharacterData.sGlow == 1 ) ))
	{
		return FALSE;
	}

	if ( pcUnitData->bActive && (pcUnitData->iCharacterType == CHARACTERTYPE_Player || pcUnitData->sCharacterData.iType == CHARACTERTYPE_Player) )
		return FALSE;

	if ( pcUnitData->bActive && pcUnitData->sCharacterData.iType == CHARACTERTYPE_NPC )
		return FALSE;

	if ( pcUnitData->bActive && GM_MODE ) //for GM only for now (need to test)
	{
		Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, pcUnitData->sPosition, pcImageUnknownIcon->GetWidth() >> 1, pcImageUnknownIcon->GetHeight() >> 1, iSize);


		float fRotation = 0.0f;
	//	if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera )
	//		fRotation = -0.25f*PI;

		int iXLocation = sPosition.iX + GetMiniMapPostion ().iX + iMiniMapDeltaX;
		int iYLocation = sPosition.iY + GetMiniMapPostion ().iY + iMiniMapDeltaY;

		int iMapCenterX =  GetMiniMapPostion ().iX + iMiniMapSize / 2 ;
		int iMapCenterY =  GetMiniMapPostion ().iY + iMiniMapSize / 2 ;

		int iDistFromCenterX = iXLocation - iMapCenterX;
		int iDistFromCenterY = iYLocation - iMapCenterY;

		int iInputRotX = static_cast<int>( iDistFromCenterX * cos( fRotation ) - iDistFromCenterY * sin( fRotation ) );
		int iInputRotY = static_cast<int>( iDistFromCenterY * cos( fRotation ) + iDistFromCenterX * sin( fRotation ) );

		int FinalX = iMapCenterX + iInputRotX + pcImageUnknownIcon->GetWidth()/2 - 5;
		int FinalY = iMapCenterY + iInputRotY ;

		Rectangle2D sBox = Rectangle2D(FinalX, FinalY, pcImageUnknownIcon->GetWidth() + 10, pcImageUnknownIcon->GetHeight());

		float fRotationDX = 0.0f;
	//	if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera )
	//		fRotationDX = ( ( ((PTANGLE_360*3)/8) * -360 ) / PTANGLE_360 ) + 180;

		UI::ImageRender::Render(pcImageUnknownIcon, sPosition.iX + iMiniMapDeltaX, sPosition.iY + iMiniMapDeltaY, pcImageUnknownIcon->GetWidth(), pcImageUnknownIcon->GetHeight(), 0, 0, -1, 1.0f ,fRotationDX);



		if (MOUSEHANDLER->GetPosition()->Inside(sBox) &&
			MOUSEHANDLER->GetPosition()->Inside(GetMiniMapBox()))
		{
			if (&pcUnitData->sCharacterData)
			{
				std::string strLevel = std::to_string(pcUnitData->sCharacterData.iLevel);
				bool bTwoDigitLevel = strLevel.size() > 1 ? true : false;

				char fullStr[32] = { 0 };
				STRINGFORMAT(fullStr, "%s (%s%c)", pcUnitData->GetName(), bTwoDigitLevel ? strLevel.substr(0, strLevel.size() - 1).c_str() : strLevel.c_str(), bTwoDigitLevel ? 'x' : NULL);

				strHoverUnit = fullStr;
			}
			else
			{
				strHoverUnit = pcUnitData->GetName();
			}

			bIsHoverUnit = TRUE;
			sHoverUnitBox = sBox;
			cHoverColor = UI::Color(255, 175, 230, 175);
		}
	}

	return TRUE;
}

void CMiniMapHandler::RenderSpawnFlagMarker ( Point3D sSpawnFlagPosition, Point3D sUserPosition, int iSize )
{
	if ( pcSpawnIcon )
	{
		Point2D sPosition = GetMinimapPositionFromCenter ( sUserPosition, sSpawnFlagPosition, pcSpawnIcon->GetWidth () >> 1, pcSpawnIcon->GetHeight () >> 1, iSize );

		float fRotation = 0.0f;
	//	if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera )
	//		fRotation = -0.25f*PI;

		int iXLocation = sPosition.iX + GetMiniMapPostion ().iX + iMiniMapDeltaX;
		int iYLocation = sPosition.iY + GetMiniMapPostion ().iY + iMiniMapDeltaY;

		int iMapCenterX =  GetMiniMapPostion ().iX + iMiniMapSize / 2 ;
		int iMapCenterY =  GetMiniMapPostion ().iY + iMiniMapSize / 2 ;

		int iDistFromCenterX = iXLocation - iMapCenterX;
		int iDistFromCenterY = iYLocation - iMapCenterY;

		int iInputRotX = static_cast<int>( iDistFromCenterX * cos( fRotation ) - iDistFromCenterY * sin( fRotation ) );
		int iInputRotY = static_cast<int>( iDistFromCenterY * cos( fRotation ) + iDistFromCenterX * sin( fRotation ) );

		int FinalX = iMapCenterX + iInputRotX + pcSpawnIcon->GetWidth()/2 - 5;
		int FinalY = iMapCenterY + iInputRotY;

		Rectangle2D sBox = Rectangle2D(FinalX, FinalY, pcSpawnIcon->GetWidth() + 10 , pcSpawnIcon->GetHeight());

		float fRotationDX = 0.0f;
	//	if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera )
	//		fRotationDX = ( ( ((PTANGLE_360*3)/8) * -360 ) / PTANGLE_360 ) + 180;

		UI::ImageRender::Render(pcSpawnIcon, sPosition.iX + iMiniMapDeltaX, sPosition.iY + iMiniMapDeltaY, pcSpawnIcon->GetWidth(), pcSpawnIcon->GetHeight(), 0, 0, -1, 1.0f ,fRotationDX);

	}
}


BOOL CMiniMapHandler::RenderParty( Point3D sUserPosition, int iUserID, int iSize )
{
	BOOL found = FALSE;

	if( PARTYHANDLER->GetPartyData().iMembersCount > 0 && SETTINGSHANDLER->GetModel()->GetSettings().bShowPartyMembers )
	{
		for( int i = 0; i < PARTYHANDLER->GetPartyData().iMembersCount; i++ )
		{
			PartyMember sMember = PARTYHANDLER->GetPartyData().saMembers[i];
			UI::Image * pImage = pcaImagesPartyMemberIcon[i];

			if( sMember.sData.sLevel > 0 && (sMember.sData.iID != iUserID) && pImage )
			{
				Point2D sPosition = GetMinimapPositionFromCenter( sUserPosition, sMember.sData.sPosition, pImage->GetWidth() >> 1, pImage->GetHeight() >> 1, iSize );

				float fRotation = 0.0f;
			//	if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera )
			//		fRotation = -0.25f*PI;

				int iXLocation = sPosition.iX + GetMiniMapPostion ().iX + iMiniMapDeltaX;
				int iYLocation = sPosition.iY + GetMiniMapPostion ().iY + iMiniMapDeltaY;

				int iMapCenterX =  GetMiniMapPostion ().iX + iMiniMapSize / 2 ;
				int iMapCenterY =  GetMiniMapPostion ().iY + iMiniMapSize / 2 ;

				int iDistFromCenterX = iXLocation - iMapCenterX;
				int iDistFromCenterY = iYLocation - iMapCenterY;

				int iInputRotX = static_cast<int>( iDistFromCenterX * cos( fRotation ) - iDistFromCenterY * sin( fRotation ) );
				int iInputRotY = static_cast<int>( iDistFromCenterY * cos( fRotation ) + iDistFromCenterX * sin( fRotation ) );

				int FinalX = iMapCenterX + iInputRotX + pImage->GetWidth()/2 - 5;
				int FinalY = iMapCenterY + iInputRotY;

				Rectangle2D sBox = Rectangle2D(FinalX, FinalY, pImage->GetWidth()+ 20, pImage->GetHeight());

				float fRotationDX = 0.0f;
			//	if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera )
			//		fRotationDX = ( ( ((PTANGLE_360*3)/8) * -360 ) / PTANGLE_360 ) + 180;

				if ( MAP_ID != MAPID_BattleTown )
				{
					UI::ImageRender::Render(pImage, sPosition.iX + iMiniMapDeltaX, sPosition.iY + iMiniMapDeltaY, pImage->GetWidth(), pImage->GetHeight(), 0, 0, -1, 1.0f ,fRotationDX);


					if( MOUSEHANDLER->GetPosition()->Inside( sBox ) &&
						MOUSEHANDLER->GetPosition()->Inside(GetMiniMapBox()))
					{
						bIsHoverUnit = TRUE;
						sHoverUnitBox = sBox;
						strHoverUnit = sMember.szCharacterName;
						cHoverColor = UI::Color( 255, 175, 230, 175 );
					}
				}
			}
		}
	}

	if( PARTYHANDLER->GetPartyData().iRaidCount > 0 && SETTINGSHANDLER->GetModel()->GetSettings().bShowRaidMembers )
	{
		for( int i = 0; i < PARTYHANDLER->GetPartyData().iRaidCount; i++ )
		{
			for( size_t j = 0; j < MAX_PARTY_MEMBERS; j++ )
			{
				PartyRaidMember sMember = PARTYHANDLER->GetPartyData().saRaid[i].saMembers[j];

				if( sMember.sData.iID && sMember.szCharacterName[0] != 0 )
				{
					Point2D sPosition = GetMinimapPositionFromCenter( sUserPosition, sMember.sData.sPosition, pcImageRaidIcon->GetWidth() >> 1, pcImageRaidIcon->GetHeight() >> 1, iSize );

					float fRotation = 0.0f;
				//	if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera )
				//		fRotation = -0.25f*PI;

					int iXLocation = sPosition.iX + GetMiniMapPostion ().iX + iMiniMapDeltaX;
					int iYLocation = sPosition.iY + GetMiniMapPostion ().iY + iMiniMapDeltaY;

					int iMapCenterX =  GetMiniMapPostion ().iX + iMiniMapSize / 2 ;
					int iMapCenterY =  GetMiniMapPostion ().iY + iMiniMapSize / 2 ;

					int iDistFromCenterX = iXLocation - iMapCenterX;
					int iDistFromCenterY = iYLocation - iMapCenterY;

					int iInputRotX = static_cast<int>( iDistFromCenterX * cos( fRotation ) - iDistFromCenterY * sin( fRotation ) );
					int iInputRotY = static_cast<int>( iDistFromCenterY * cos( fRotation ) + iDistFromCenterX * sin( fRotation ) );

					int FinalX = iMapCenterX + iInputRotX + pcImageRaidIcon->GetWidth()/2 - 5;
					int FinalY = iMapCenterY + iInputRotY;

					Rectangle2D sBox = Rectangle2D(FinalX, FinalY, pcImageRaidIcon->GetWidth() + 10, pcImageRaidIcon->GetHeight());

					float fRotationDX = 0.0f;
				//	if (SETTINGSHANDLER->GetModel()->GetSettings().bARPGCamera )
				//		fRotationDX = ( ( ((PTANGLE_360*3)/8) * -360 ) / PTANGLE_360 ) + 180;

					if ( MAP_ID != MAPID_BattleTown )
					{
						UI::ImageRender::Render(pcImageRaidIcon, sPosition.iX + iMiniMapDeltaX, sPosition.iY + iMiniMapDeltaY, pcImageRaidIcon->GetWidth(), pcImageRaidIcon->GetHeight(), 0, 0, -1, 1.0f ,fRotationDX);

						if( MOUSEHANDLER->GetPosition()->Inside(sBox) &&
							MOUSEHANDLER->GetPosition()->Inside(GetMiniMapBox()))
						{
							bIsHoverUnit = TRUE;
							sHoverUnitBox = sBox;
							strHoverUnit = sMember.szCharacterName;
							cHoverColor = UI::Color( 255, 40, 240, 230 );
						}
					}
				}
			}
		}
	}

	return TRUE;
}

BOOL CMiniMapHandler::RenderMapTime()
{
	return TRUE;
}

BOOL CMiniMapHandler::IsCurrentUserMap( int iMapID )
{
	if ( UNITDATA->iLoadedMapIndex >= 0 )
	{
		if ( FIELDGAME[UNITDATA->iLoadedMapIndex]->iMapID == iMapID )
			return TRUE;
	}

	return FALSE;
}

BOOL CMiniMapHandler::IsCurrentUserSecondMap( int iMapID )
{
	int iSecondMapIndex = (UNITDATA->iLoadedMapIndex == 0) ? 1 : 0;
	if ( FIELDGAME[iSecondMapIndex] )
	{
		return FIELDGAME[iSecondMapIndex]->iMapID == iMapID;
	}

	return FALSE;
}

BOOL CMiniMapHandler::IsCurrentUserMap( MiniMapData * psMap )
{
	if ( UNITDATA->iLoadedMapIndex >= 0 )
	{
		if ( FIELDGAME[UNITDATA->iLoadedMapIndex] == psMap->pcBaseMap )
			return TRUE;
	}

	return FALSE;
}

void CMiniMapHandler::BeginViewport()
{
	RECT r = { GetMiniMapPostion().iX, GetMiniMapPostion().iY, GetMiniMapPostion().iX + iMiniMapSize, GetMiniMapPostion().iY + iMiniMapSize };
	GetGraphicsDevice()->PushScissorRect( r );
}

void CMiniMapHandler::EndViewport()
{
	GetGraphicsDevice()->PopScissorRect();
}

NAKED void CMiniMapHandler::DrawMinimap( MiniMapData * psMap, int iX, int iY, int iSize )
{
	JMP( 0x00460D50 );
}

void CMiniMapHandler::SetMinimapSize( float fSize )
{
	(*(float*)0x04B0DF44) = fSize / 2.0f;
	(*(float*)0x04B0DF48) = fSize - 2.0f;
}

Point2D CMiniMapHandler::GetMinimapPositionFromCenter( Point3D sCenterPosition, Point3D sObjectPositiion, int iWidthPoint, int iHeightPoint, int iSize )
{
	return GetMinimapPositionFromCenter( sCenterPosition, sObjectPositiion.iX, sObjectPositiion.iZ, iWidthPoint, iHeightPoint, iSize );
}

Point2D CMiniMapHandler::GetMinimapPositionFromCenter( Point3D sCenterPosition, int iDetailedX, int iDetailedZ, int iWidthPoint, int iHeightPoint, int iSize )
{
	//Compute position from center to object
	int iX = iDetailedX - sCenterPosition.iX;
	int iZ = iDetailedZ - sCenterPosition.iZ;

	//Divide points to inside of minimap
	iX /= (iSize / (iMiniMapSize / 2));
	iZ /= (iSize / (iMiniMapSize / 2));

	//Negative Z, since it will up...
	iZ = -iZ;


	return Point2D( iX + (iMiniMapSize >> 1) - iWidthPoint, iZ + (iMiniMapSize >> 1) - iHeightPoint );
}

void CMiniMapHandler::OnResolutionChanged()
{
	ResetMiniMapScreenPositions();
}

void CMiniMapHandler::OnMiniMapSizeChanged()
{
	pRenderTargetMask = GetGraphicsDevice()->MakeRenderTarget(1000, iMiniMapSize, iMiniMapSize);

	if (bLargeMiniMap)
	{
		iMiniMapScreenPositionX = iMiniMapLargeScreenPositionX;
		iMiniMapScreenPositionY = iMiniMapLargeScreenPositionY;
	}
	else
	{
		iMiniMapScreenPositionX = iMiniMapSmallScreenPositionX;
		iMiniMapScreenPositionY = iMiniMapSmallScreenPositionY;
	}

	SetMiniMapBox(Rectangle2D(iMiniMapScreenPositionX, iMiniMapScreenPositionY, iMiniMapSize, iMiniMapSize));
	ResetMapTextureDeltas();
}




//void CMiniMapHandler::HandlePacket(PacketBossTimeUpdate* psPacket)
//{
//	strNextBossName = psPacket->szBossName;
//	dwNextBossTime = (double)psPacket->dwTime * 1000.0;
//
//	//新增 放大地图
//	//Title Map Rodrigo
//	bShowImgMap = TRUE;
//
//	if (dwNextBossTime > 0.0)
//		bShowBossTime = TRUE;
//	else
//		bShowBossTime = FALSE;
//}

void CMiniMapHandler::HandlePacket(PacketBossTimeUpdate* psPacket)
{
	strNextBossName = psPacket->szBossName;
	dwNextBossTime = psPacket->dwTime;

	//New Title Map Show
	bShowImgMap = TRUE;

	if (dwNextBossTime)
		bShowBossTime = TRUE;
	else
		bShowBossTime = FALSE;
}

void CMiniMapHandler::ProcessPacket( PacketBossTimeUpdate * psPacket )
{
	psPacket->iLength = sizeof( PacketBossTimeUpdate );
	psPacket->iHeader = PKTHDR_BossTimeUpdate;
	SENDPACKETG( psPacket );
}

void CMiniMapHandler::OnChangeMap( int iMapID )
{
	//std::cout << "OnChangeMap" << std::endl;
	//vSpawnFlags.clear ();

	if ( CHARACTERGAME->GetLastStageID () == MAPID_Invalid )
	{
		ProcessPacket ( &PacketBossTimeUpdate ( iMapID ) );
	}
}
