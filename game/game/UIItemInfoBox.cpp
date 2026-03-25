#include "stdafx.h"
#include "UIItemInfoBox.h"


const char * pszaQuestMonsterName[] = { "Bargon", "Guerrero Esqueleto", "Cortacabezas", "Escarabajo Blindado", "Explorador Esqueleto", "Tit\341n", "Monstruos de Tierra Olvidada", "Monstruos del Oasis", "Monstruos de Mazmorra 1F" };

namespace UI
{
namespace
{
EItemRarity ClampTooltipRarity( EItemRarity eRarity )
{
	if ( eRarity < ITEMRARITY_None )
		return ITEMRARITY_None;

	if ( eRarity > ITEMRARITY_Legendary )
		return ITEMRARITY_Legendary;

	return eRarity;
}

Image * LoadTooltipBorderImage( const char * pszFolder, const char * pszFileName )
{
	return ImageLoader::LoadImage( FormatString( "game\\images\\UI\\box\\border\\%s\\%s", pszFolder, pszFileName ) );
}

bool IsRaritySkinnedEquipment( EItemType eItemType )
{
	switch ( eItemType )
	{
		case ITEMTYPE_Axe:
		case ITEMTYPE_Claw:
		case ITEMTYPE_Hammer:
		case ITEMTYPE_Wand:
		case ITEMTYPE_Scythe:
		case ITEMTYPE_Bow:
		case ITEMTYPE_Sword:
		case ITEMTYPE_Javelin:
		case ITEMTYPE_Phantom:
		case ITEMTYPE_Dagger:
		case ITEMTYPE_Armor:
		case ITEMTYPE_Boots:
		case ITEMTYPE_Gauntlets:
		case ITEMTYPE_Shield:
		case ITEMTYPE_Robe:
		case ITEMTYPE_Sheltom:
		case ITEMTYPE_Amulet:
		case ITEMTYPE_Bracelets:
		case ITEMTYPE_Orb:
		case ITEMTYPE_Ring:
		case ITEMTYPE_Ring2:
			return true;
		default:
			return false;
	}
}

std::vector<std::string> BuildTooltipTitleLines( const std::string & strItemName )
{
	std::vector<std::string> vTitleLines;

	if ( strItemName.empty() )
		return vTitleLines;

	if ( strItemName.find( '\n' ) != std::string::npos )
	{
		vTitleLines = split( strItemName, '\n' );
		if ( vTitleLines.empty() )
			vTitleLines.push_back( strItemName );
		return vTitleLines;
	}

	if ( strItemName.length() <= 15 )
	{
		vTitleLines.push_back( strItemName );
		return vTitleLines;
	}

	std::vector<int> vSpaces;
	for ( size_t i = 0; i < strItemName.length(); i++ )
	{
		if ( strItemName[i] == ' ' )
			vSpaces.push_back( static_cast<int>( i ) );
	}

	if ( vSpaces.empty() )
	{
		vTitleLines.push_back( strItemName );
		return vTitleLines;
	}

	int iMidSpace = vSpaces.front();
	int iMidDistance = INT_MAX;
	const int iMiddle = static_cast<int>( strItemName.length() / 2 );
	for ( int iSpace : vSpaces )
	{
		const int iDistance = abs( iSpace - iMiddle );
		if ( iDistance < iMidDistance )
		{
			iMidDistance = iDistance;
			iMidSpace = iSpace;
		}
	}

	vTitleLines.push_back( trim( strItemName.substr( 0, iMidSpace ) ) );
	vTitleLines.push_back( trim( strItemName.substr( iMidSpace + 1 ) ) );
	return vTitleLines;
}

bool CanRenderTooltipItemPreview( ItemData & cItemData )
{
	const EItemBase eItemBase = cItemData.sItem.sItemID.ToItemBase();
	const EItemType eItemType = cItemData.sItem.sItemID.ToItemType();

	return ( eItemBase == ITEMBASE_Weapon ) || IsRaritySkinnedEquipment( eItemType );
}

int GetDisplayedRarityBuyPrice( const Item * psItem )
{
	if ( psItem == NULL )
		return 0;

	switch ( *(const DWORD *)&psItem->sItemID )
	{
		case ITEMID_MokovaBoots:
		case ITEMID_DraxosBoots:
		case ITEMID_ValentoRing:
		case ITEMID_KelvezuAmulet:
		case ITEMID_DevilShyRing:
		case ITEMID_GreedyGauntlets:
		case ITEMID_TullaAmulet:
		case ITEMID_AbyssRing:
			return psItem->iSalePrice;
		default:
			break;
	}

	if ( psItem->eRarity > ITEMRARITY_None )
		return static_cast<int>( round( ( static_cast<float>( psItem->iSalePrice ) / 2.0f ) * static_cast<int>( psItem->eRarity ) ) );

	return psItem->iSalePrice;
}

int GetDisplayedRarityWeaponDamageMin( const Item * psItem )
{
	if ( psItem == NULL )
		return 0;

	return psItem->sDamage.sMin + GetItemRarityRuntimeWeaponStats( psItem ).iDamageMin + GetItemRarityRuntimeMiscStats( psItem ).iDamageMin;
}

int GetDisplayedRarityWeaponDamageMax( const Item * psItem )
{
	if ( psItem == NULL )
		return 0;

	return psItem->sDamage.sMax + GetItemRarityRuntimeWeaponStats( psItem ).iDamageMax + GetItemRarityRuntimeMiscStats( psItem ).iDamageMax;
}

int GetDisplayedRarityWeaponAttackRating( const Item * psItem )
{
	if ( psItem == NULL )
		return 0;

	return psItem->iAttackRating + GetItemRarityRuntimeWeaponStats( psItem ).iAttackRating + GetItemRarityRuntimeMiscStats( psItem ).iAttackRating;
}

int GetDisplayedRarityWeaponCritical( const Item * psItem )
{
	if ( psItem == NULL )
		return 0;

	return psItem->iCritical + GetItemRarityRuntimeWeaponStats( psItem ).iCritical;
}

int GetDisplayedRarityDefense( const Item * psItem )
{
	if ( psItem == NULL )
		return 0;

	return psItem->iDefenseRating + GetItemRarityRuntimeDefenseStats( psItem ).iDefenseRating;
}

float GetDisplayedRarityAbsorb( const Item * psItem )
{
	if ( psItem == NULL )
		return 0.0f;

	return psItem->fAbsorbRating + GetItemRarityRuntimeDefenseStats( psItem ).fAbsorbRating;
}

float GetDisplayedRarityBlock( const Item * psItem )
{
	if ( psItem == NULL )
		return 0.0f;

	return psItem->fBlockRating + GetItemRarityRuntimeDefenseStats( psItem ).fBlockRating;
}

float GetDisplayedRarityAddHP( const Item * psItem )
{
	if ( psItem == NULL )
		return 0.0f;

	return psItem->fAddHP + GetItemRarityRuntimeMiscStats( psItem ).fAddHP;
}

float GetDisplayedRarityAddMP( const Item * psItem )
{
	if ( psItem == NULL )
		return 0.0f;

	return psItem->fAddMP + GetItemRarityRuntimeMiscStats( psItem ).fAddMP;
}

float GetDisplayedRarityAddSP( const Item * psItem )
{
	if ( psItem == NULL )
		return 0.0f;

	return psItem->fAddSP + GetItemRarityRuntimeMiscStats( psItem ).fAddSP;
}

int GetDisplayedRarityPotionStorage( const Item * psItem )
{
	if ( psItem == NULL )
		return 0;

	return psItem->iPotionStorage + GetItemRarityRuntimeMiscStats( psItem ).iPotionStorage;
}

DWORD GetItemRarityColor( EItemRarity eRarity )
{
	switch ( eRarity )
	{
		case ITEMRARITY_Common:		return D3DCOLOR_ARGB( 255, 228, 228, 228 );
		case ITEMRARITY_Uncommon:	return D3DCOLOR_ARGB( 255, 148, 255, 162 );
		case ITEMRARITY_Rare:		return D3DCOLOR_ARGB( 255, 116, 208, 255 );
		case ITEMRARITY_Epic:		return D3DCOLOR_ARGB( 255, 226, 150, 255 );
		case ITEMRARITY_Legendary:	return D3DCOLOR_ARGB( 255, 255, 204, 108 );
		default:					return D3DCOLOR_ARGB( 255, 215, 215, 215 );
	}
}

void ApplyTooltipRarityTextStyle( const Text_ptr & pText, EItemRarity eRarity )
{
	if ( pText == nullptr )
		return;

	pText->SetFont( "Arial", 15, 6, FALSE, TRUE, -1 );
	pText->SetColor( GetItemRarityColor( eRarity ) );
	pText->SetDropdownShadow( TRUE );
	pText->SetDropdownColor( D3DCOLOR_ARGB( 255, 12, 10, 8 ) );
	pText->SetDropdownShadowDistance( 1 );
	pText->SetOutlineColor( D3DCOLOR_ARGB( 255, 18, 14, 10 ) );
}
}

ItemInfoBox::ItemInfoBox()
{
	iSocketGem[0] = iSocketGem[1] = -1;

	pWindowHair = std::make_shared<UI::Window>( Rectangle2D( 0, 62, 102, 102 ) );
	pWindowBody = std::make_shared<UI::Window>( Rectangle2D( 0, 72, 150, 190 ) );
}

ItemInfoBox::~ItemInfoBox()
{
	pWindowHair = nullptr;
	pWindowBody = nullptr;
}

void ItemInfoBox::AddString( int iSide, const std::string & strString, DWORD dwColor, BOOL bBold )
{
	std::vector<std::string> vString;

	//Find breakline in String 
	BOOL bMultiLine = FALSE;
	if( strString.find( '\n' ) != std::string::npos )
	{
		vString = split( strString, '\n' );
		bMultiLine = TRUE;
	}

	switch( iSide )
	{
	case 0: //Left Side
		//Is Multiline?
		if( bMultiLine )
		{
			//String from vector
			int i = 0;
			for( const auto & strSplitted : vString )
			{
				vLeftText.push_back( std::make_shared<Text>( strSplitted, Rectangle2D( 0, 0, 180, 20 ), bBold, dwColor ) );
				i++;

				if( i != vString.size() )
				{
					vRightText.push_back( std::make_shared<Text>( "", Rectangle2D( 0, 0, 180, 20 ), bBold, dwColor ) );
				}
			}
		}
		else
		{
			vLeftText.push_back( std::make_shared<Text>( strString, Rectangle2D( 0, 0, 180, 20 ), bBold, dwColor ) );
		}

		break;

	case 1: //Right Side
		vRightText.push_back( std::make_shared<Text>( strString, Rectangle2D( 0, 0, 180, 20 ), bBold, dwColor ) );
		break;
	}
}

void ItemInfoBox::AddCompareString( const std::string & strString, DWORD dwColor )
{
	vRowCompare.push_back( vLeftText.size() );
	vCompareText.push_back( std::make_shared<Text>( strString, Rectangle2D( 0, 0, 180, 20 ), FALSE, dwColor ) );
}

void ItemInfoBox::SetLineColor( DWORD dwColor, int iSide, int iLineCount )
{
	int iSetColor = 0;
	if( iLineCount < 0 )
		iSetColor = vLeftText.size() - 1;
	else
		iSetColor = iLineCount;

	switch( iSide )
	{
	case -1:
		vLeftText[ iSetColor ]->SetColor( dwColor );
		vRightText[ iSetColor ]->SetColor( dwColor );
		break;
	case 0:
		vLeftText[ iSetColor ]->SetColor( dwColor );
		break;
	case 1:
		vRightText[ iSetColor ]->SetColor( dwColor );
		break;
	}
}

void ItemInfoBox::AppendLineText( std::string str, int iSide, int iLineCount )
{
	int iSetText = 0;
	if( iLineCount < 0 )
		iSetText = vLeftText.size() - 1;
	else
		iSetText = iLineCount;

	switch( iSide )
	{
		case -1:
			vLeftText[ iSetText ]->AppendText(str);
			vRightText[ iSetText ]->AppendText( str );
			break;
		case 0:
			vLeftText[ iSetText ]->AppendText( str );
			break;
		case 1:
			vRightText[ iSetText ]->AppendText( str );
			break;
	}
}

const ItemInfoBox::RarityBorderSet & ItemInfoBox::GetRarityBorderSet( EItemRarity eRarity ) const
{
	return saRarityBorderSet[ClampTooltipRarity( eRarity )];
}

void ItemInfoBox::LoadRarityBorderSet( EItemRarity eRarity, const char * pszFolder )
{
	RarityBorderSet & sSkin = saRarityBorderSet[ClampTooltipRarity( eRarity )];

	sSkin.pLeftTop = LoadTooltipBorderImage( pszFolder, "topleft.png" );
	sSkin.pRightTop = LoadTooltipBorderImage( pszFolder, "topright.png" );
	sSkin.pTop = LoadTooltipBorderImage( pszFolder, "top.png" );
	sSkin.pLeftBottom = LoadTooltipBorderImage( pszFolder, "bottomleft.png" );
	sSkin.pRightBottom = LoadTooltipBorderImage( pszFolder, "bottomright.png" );
	sSkin.pBottom = LoadTooltipBorderImage( pszFolder, "bottom.png" );
	sSkin.pLeft = LoadTooltipBorderImage( pszFolder, "left.png" );
	sSkin.pRight = LoadTooltipBorderImage( pszFolder, "right.png" );
	sSkin.pDivider = LoadTooltipBorderImage( pszFolder, "divider.png" );
	sSkin.pInfo = LoadTooltipBorderImage( pszFolder, "info.png" );
	sSkin.pInfoLeft = LoadTooltipBorderImage( pszFolder, "infoleft.png" );
	sSkin.pInfoRight = LoadTooltipBorderImage( pszFolder, "inforight.png" );
	sSkin.pNameFrameLeft = LoadTooltipBorderImage( pszFolder, "nameframeleft.png" );
	sSkin.pNameFrameCenter = LoadTooltipBorderImage( pszFolder, "nameframecenter.png" );
	sSkin.pNameFrameRight = LoadTooltipBorderImage( pszFolder, "nameframeright.png" );
	sSkin.pNameFrameBackground = LoadTooltipBorderImage( pszFolder, "nameframebackgroud.png" );
	sSkin.pCorner = LoadTooltipBorderImage( pszFolder, "corner.png" );
	sSkin.pBottomCorner = LoadTooltipBorderImage( pszFolder, "bottomcorner.png" );
}

void ItemInfoBox::RenderRarityBorder( const RarityBorderSet & sSkin, int iX, int iY, int iWidth, int iHeight ) const
{
	Image * pLeftTop = sSkin.pLeftTop ? sSkin.pLeftTop : pImageBorderLeftTop;
	Image * pRightTop = sSkin.pRightTop ? sSkin.pRightTop : pImageBorderRightTop;
	Image * pTop = sSkin.pTop ? sSkin.pTop : pImageBorderTop;
	Image * pLeftBottom = sSkin.pLeftBottom ? sSkin.pLeftBottom : pImageBorderLeftBottom;
	Image * pRightBottom = sSkin.pRightBottom ? sSkin.pRightBottom : pImageBorderRightBottom;
	Image * pBottom = sSkin.pBottom ? sSkin.pBottom : pImageBorderBottom;
	Image * pLeft = sSkin.pLeft ? sSkin.pLeft : pImageBorderLeft;
	Image * pRight = sSkin.pRight ? sSkin.pRight : pImageBorderRight;

	if ( pLeftTop == nullptr || pRightTop == nullptr || pTop == nullptr || pLeftBottom == nullptr || pRightBottom == nullptr || pBottom == nullptr || pLeft == nullptr || pRight == nullptr )
		return;

	UI::ImageRender::Render( pLeftTop, iX, iY - 10, pLeftTop->GetWidth(), pLeftTop->GetHeight(), -1 );
	UI::ImageRender::Render( pTop, iX + pLeftTop->GetWidth(), iY - 10, iWidth - pLeftTop->GetWidth() - pRightTop->GetWidth(), pTop->GetHeight(), -1 );
	UI::ImageRender::Render( pRightTop, iX + iWidth - pRightTop->GetWidth(), iY - 10, pRightTop->GetWidth(), pRightTop->GetHeight(), -1 );
	UI::ImageRender::Render( pLeft, iX, iY - 10 + pLeftTop->GetHeight(), pLeft->GetWidth(), iHeight - pLeftTop->GetHeight() - pLeftBottom->GetHeight(), -1 );
	UI::ImageRender::Render( pRight, iX + iWidth - pRight->GetWidth(), iY - 10 + pRightTop->GetHeight(), pRight->GetWidth(), iHeight - pRightTop->GetHeight() - pRightBottom->GetHeight(), -1 );
	UI::ImageRender::Render( pLeftBottom, iX, iY - 10 + iHeight - pLeftBottom->GetHeight(), pLeftBottom->GetWidth(), pLeftBottom->GetHeight(), -1 );
	UI::ImageRender::Render( pRightBottom, iX + iWidth - pRightBottom->GetWidth(), iY - 10 + iHeight - pRightBottom->GetHeight(), pRightBottom->GetWidth(), pRightBottom->GetHeight(), -1 );
	UI::ImageRender::Render( pBottom, iX + pLeftBottom->GetWidth(), iY - 10 + iHeight - pBottom->GetHeight(), iWidth - pLeftBottom->GetWidth() - pRightBottom->GetWidth(), pBottom->GetHeight(), -1 );

	if ( sSkin.pCorner )
		UI::ImageRender::Render( sSkin.pCorner, iX - 11, iY - 22, sSkin.pCorner->GetWidth(), sSkin.pCorner->GetHeight(), 0, 0, -1, 1, 0 );
}

void ItemInfoBox::RenderRarityNameFrame( const RarityBorderSet & sSkin, int iX, int iY, int iWidth ) const
{
	if ( sSkin.pNameFrameLeft == nullptr || sSkin.pNameFrameCenter == nullptr || sSkin.pNameFrameRight == nullptr )
		return;

	int iFrameWidth = iWidth - 10;
	const int iMinimumWidth = sSkin.pNameFrameLeft->GetWidth() + sSkin.pNameFrameRight->GetWidth();
	if ( iFrameWidth < iMinimumWidth )
		iFrameWidth = iMinimumWidth;

	const int iLeft = iX + ( iWidth - iFrameWidth ) / 2;
	const int iTop = iY - 5;

	UI::ImageRender::Render( sSkin.pNameFrameLeft, iLeft, iTop, sSkin.pNameFrameLeft->GetWidth(), sSkin.pNameFrameLeft->GetHeight(), 0, 0, -1 );
	UI::ImageRender::Render( sSkin.pNameFrameCenter, iLeft + sSkin.pNameFrameLeft->GetWidth(), iTop, iFrameWidth - sSkin.pNameFrameLeft->GetWidth() - sSkin.pNameFrameRight->GetWidth(), sSkin.pNameFrameCenter->GetHeight(), 0, 0, -1 );
	UI::ImageRender::Render( sSkin.pNameFrameRight, iLeft + iFrameWidth - sSkin.pNameFrameRight->GetWidth(), iTop, sSkin.pNameFrameRight->GetWidth(), sSkin.pNameFrameRight->GetHeight(), 0, 0, -1 );

	if ( sSkin.pNameFrameBackground )
		UI::ImageRender::Render( sSkin.pNameFrameBackground, iX + ( iWidth - sSkin.pNameFrameBackground->GetWidth() ) / 2, iY - 5, sSkin.pNameFrameBackground->GetWidth(), sSkin.pNameFrameBackground->GetHeight(), 0, 0, -1 );
}

void ItemInfoBox::RenderRarityInfoPanel( const RarityBorderSet & sSkin, int iX, int iY, int iWidth, int iHeight ) const
{
	if ( sSkin.pInfoLeft == nullptr || sSkin.pInfo == nullptr || sSkin.pInfoRight == nullptr || pImageGradient == nullptr || pImagePKey == nullptr )
		return;

	Text_ptr pHelpText = std::make_shared<Text>( "Hold       to see perfect stats", Rectangle2D( 0, 0, 180, 20 ), FALSE, D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
	pHelpText->SetFont( "Arial", 14, 6, FALSE, FALSE, -1 );
	pHelpText->SetMultiLine( TRUE );
	pHelpText->SetNoClip( TRUE );
	pHelpText->SetColor( D3DCOLOR_ARGB( 220, 255, 255, 255 ) );
	pHelpText->SetHorizontalAlign( ALIGN_Center );
	pHelpText->SetBox( Rectangle2D( ( iWidth - pHelpText->GetWidth() ) / 2, iHeight - 12, 180, 20 ) );

	const int iPanelWidth = ( iWidth > 200 ) ? ( iWidth - 30 ) : ( iWidth - 15 );
	const int iPanelLeft = iX + ( iWidth - iPanelWidth ) / 2;
	const int iPanelTop = iY + iHeight - 15;

	const int iPanelBackgroundWidth = iPanelWidth - 14;
	const int iPanelBackgroundLeft = iX + ( iWidth - iPanelBackgroundWidth ) / 2;
	UI::Color cPanelColor = cBackgroundColor2;
	GRAPHICENGINE->DrawRectangle2D( Rectangle2D( iPanelBackgroundLeft, iPanelTop, iPanelBackgroundWidth, 17 ), cPanelColor.Get(), cPanelColor.Get() );

	UI::ImageRender::Render( sSkin.pInfoLeft, iPanelLeft, iPanelTop, sSkin.pInfoLeft->GetWidth(), sSkin.pInfoLeft->GetHeight(), 0, 0, -1 );
	UI::ImageRender::Render( sSkin.pInfo, iPanelLeft + sSkin.pInfoLeft->GetWidth(), iPanelTop, iPanelWidth - sSkin.pInfoLeft->GetWidth() - sSkin.pInfoRight->GetWidth(), sSkin.pInfo->GetHeight(), 0, 0, -1 );
	UI::ImageRender::Render( sSkin.pInfoRight, iPanelLeft + iPanelWidth - sSkin.pInfoRight->GetWidth(), iPanelTop, sSkin.pInfoRight->GetWidth(), sSkin.pInfoRight->GetHeight(), 0, 0, -1 );

	UI::ImageRender::Render( pImageGradient, iPanelLeft + 2, iPanelTop, iPanelWidth - 4, pImageGradient->GetHeight(), 0, 0, -1 );
	UI::ImageRender::Render( pImagePKey, iX + ( iWidth / 2 ) - 43, iPanelTop + 4, pImagePKey->GetWidth(), pImagePKey->GetHeight(), 0, 0, -1 );
	pHelpText->Render( iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0 );
}

void ItemInfoBox::RenderRarityDivider( const RarityBorderSet & sSkin, int iX, int iY, int iWidth, int iLineIndex ) const
{
	if ( sSkin.pDivider == nullptr || iLineIndex <= 0 )
		return;

	UI::ImageRender::Render( sSkin.pDivider, iX + ( iWidth - sSkin.pDivider->GetWidth() ) / 2, iY + 5 + ( iLineIndex * 14 ) + ( sSkin.pDivider->GetHeight() >> 1 ), sSkin.pDivider->GetWidth(), sSkin.pDivider->GetHeight(), 0, 0, -1 );
}

void ItemInfoBox::Init()
{
	//Load Images
	pImageMaskLeftTop				= ImageLoader::LoadImage( "game\\images\\UI\\box\\mask\\topleft.png" );
	pImageMaskRightTop				= ImageLoader::LoadImage( "game\\images\\UI\\box\\mask\\topright.png" );
	pImageMaskLeftBottom			= ImageLoader::LoadImage( "game\\images\\UI\\box\\mask\\bottomleft.png" );
	pImageMaskRightBottom			= ImageLoader::LoadImage( "game\\images\\UI\\box\\mask\\bottomright.png" );

	//Load Border Images
	pImageBorderLeftTop				= ImageLoader::LoadImage( "game\\images\\UI\\box\\border\\topleft.png" );
	pImageBorderRightTop			= ImageLoader::LoadImage( "game\\images\\UI\\box\\border\\topright.png" );
	pImageBorderTop					= ImageLoader::LoadImage( "game\\images\\UI\\box\\border\\top.png" );
	pImageBorderRightBottom			= ImageLoader::LoadImage( "game\\images\\UI\\box\\border\\bottomright.png" );
	pImageBorderLeftBottom			= ImageLoader::LoadImage( "game\\images\\UI\\box\\border\\bottomleft.png" );
	pImageBorderBottom				= ImageLoader::LoadImage( "game\\images\\UI\\box\\border\\bottom.png" );
	pImageBorderLeft				= ImageLoader::LoadImage( "game\\images\\UI\\box\\border\\left.png" );
	pImageBorderRight				= ImageLoader::LoadImage( "game\\images\\UI\\box\\border\\right.png" );
	pImageGradient					= ImageLoader::LoadImage( "game\\images\\UI\\box\\border\\gradient.png" );
	pImagePKey						= ImageLoader::LoadImage( "game\\images\\UI\\box\\border\\p_key.png" );

	LoadRarityBorderSet( ITEMRARITY_None, "none" );
	LoadRarityBorderSet( ITEMRARITY_Common, "common" );
	LoadRarityBorderSet( ITEMRARITY_Uncommon, "uncommon" );
	LoadRarityBorderSet( ITEMRARITY_Rare, "rare" );
	LoadRarityBorderSet( ITEMRARITY_Epic, "epic" );
	LoadRarityBorderSet( ITEMRARITY_Legendary, "legendary" );

	//Load Icons
	pImageIconArmor					= ImageLoader::LoadImage( "Image\\SinImage\\Items\\Weapon_Knight.bmp" );
	pImageIconRobe					= ImageLoader::LoadImage( "Image\\SinImage\\Items\\Weapon_Wizard.bmp" );
	pImageIconWeaponOneHand			= ImageLoader::LoadImage( "Image\\SinImage\\Items\\Weapon_Onehand.bmp" );
	pImageIconWeaponTwoHand			= ImageLoader::LoadImage( "Image\\SinImage\\Items\\Weapon_Twohand.bmp" );

	//Load Aging Bar
	pImageAgingBar					= ImageLoader::LoadImage("image\\Sinimage\\shopall\\Aging\\Bar.bmp");
	pImageAgingBarGage				= ImageLoader::LoadImage("image\\Sinimage\\shopall\\Aging\\Bar_.bmp");
	pImageAgingBarNum				= ImageLoader::LoadImage("image\\Sinimage\\shopall\\Aging\\Aging.bmp");

	pTextAging = std::make_shared<Text>( Rectangle2D( 0, 0, 0, 0 ) );
	pTextAging->SetFont( "Arial", 14, 0, FALSE, FALSE, D3DCOLOR_ARGB(255,20,20,20) );

	cBackgroundColor2 = UI::Color( 235, 45, 39, 27 );
	cBackgroundColor2 = UI::Color( 245, 9, 23, 22 );

	paSocketText[0][0] = std::make_shared<Text>( Rectangle2D( 0, 0, 0, 0 ) );
	paSocketText[0][0]->SetFont( "Arial", 16, 0, FALSE, TRUE, -1 );

	paSocketText[0][1] = std::make_shared<Text>( Rectangle2D( 0, 0, 0, 0 ) );
	paSocketText[0][1]->SetFont( "Arial", 16, 0, FALSE, FALSE, -1 );

	paSocketText[1][0] = std::make_shared<Text>( Rectangle2D( 0, 0, 0, 0 ) );
	paSocketText[1][0]->SetFont( "Arial", 16, 0, FALSE, TRUE, -1 );

	paSocketText[1][1] = std::make_shared<Text>( Rectangle2D( 0, 0, 0, 0 ) );
	paSocketText[1][1]->SetFont( "Arial", 16, 0, FALSE, FALSE, -1 );


	pRenderTargetMask	= GetGraphicsDevice()->MakeRenderTarget( 5001, 600, 600 );
	pEffectMask			= GetGraphicsDevice()->GetEffectFactory()->MakeEffect( "game\\scripts\\shaders\\UI\\InfoBox.fx" );

	//Socket Images
	pImageSocketBackground			= ImageLoader::LoadImage("image\\Sinimage\\Inven\\InfoBox\\socketbg.png");

	for( int i = 0; i < 6; i++ )
		paSocket[i] = ImageLoader::LoadImage( "image\\Sinimage\\Inven\\InfoBox\\socket%d.png", i + 1 );

	for( int i = 0; i < 15; i++ )
		paSocketGems[i] = ImageLoader::LoadImage( "image\\Sinimage\\Items\\Event\\itPR5%02d.bmp", i + 1 );

	UI::ImageBox_ptr pImagePreview = std::make_shared<UI::ImageBox>( Rectangle2D( 0, 0, 102, 102 ) );
	pImagePreview->SetImage( UI::ImageLoader::LoadImage( "game\\images\\coinshop\\previewhair.png" ) );
	pWindowHair->AddElement( pImagePreview );

	UI::UnitMesh_ptr pUnitMeshPreview = std::make_shared<UI::UnitMesh>( Rectangle2D( 1, 1, 100, 99 ) );
	pUnitMeshPreview->SetID( UNITMESHID_HeadPreview );
	pUnitMeshPreview->SetRenderBody( FALSE );
	pWindowHair->AddElement( pUnitMeshPreview );

	pWindowHair->Hide();

	UI::ImageBox_ptr pImagePreviewBody = std::make_shared<UI::ImageBox>( Rectangle2D( 0, 0, 150, 190 ) );
	pImagePreviewBody->SetImage( UI::ImageLoader::LoadImage( "game\\images\\coinshop\\previewcostume.png" ) );
	pWindowBody->AddElement( pImagePreviewBody );

	UI::UnitMesh_ptr pUnitMeshPreviewBody = std::make_shared<UI::UnitMesh>( Rectangle2D( 1, 1, 148, 188 ) );
	pUnitMeshPreviewBody->SetID( UNITMESHID_BodyPreview );
	pWindowBody->AddElement( pUnitMeshPreviewBody );

	pWindowBody->Hide();
}

void ItemInfoBox::ClearCompareItem()
{
	ZeroMemory( &cItemCompare, sizeof( ItemData ) );
	bCompareItem = FALSE;
}

void ItemInfoBox::SetCompareItem( const ItemData * pcCompareItemData, BOOL bEquippedItem )
{
	CopyMemory( &cItemCompare, pcCompareItemData, sizeof( ItemData ) );
	bCompareItem = TRUE;
	bIsEquippedItem = bEquippedItem;
}

bool ItemInfoBox::IsCostumeItem( ItemData * pcItemData )
{
	return HUDHANDLER->GetInventoryWindow()->GetWindowCostume()->IsSpecialCostume( pcItemData->sItem.sItemID.ToItemID() ) || pcItemData->sItem.bCostumeItem;
}

BOOL ItemInfoBox::IsBeginnerSet( ItemData * pcItemData )
{
	BOOL bRet = FALSE;
	switch ( pcItemData->sItem.sItemID.ToItemID() )
	{
		case ITEMID_BeginnerAxe:
		case ITEMID_BeginnerClaw:
		case ITEMID_BeginnerHammer:
		case ITEMID_BeginnerSword:
		case ITEMID_BeginnerJavelin:
		case ITEMID_BeginnerBow:
		case ITEMID_BeginnerScythe:
		case ITEMID_BeginnerPhantom:
		case ITEMID_BeginnerDagger:
		case ITEMID_BeginnerStaff:
		case ITEMID_BeginnerBoots:
		case ITEMID_BeginnerGauntlet:
		case ITEMID_BeginnerBracelet:
		case ITEMID_GrumpyArmor:
		case ITEMID_GrumpyRobe:
			bRet = TRUE;
			break;

		default:
			break;
	}

	return bRet;
}

BOOL ItemInfoBox::IsSameItem( ItemData * pcItemData )
{
	if ( (cItemWrapper.sItem.sItemID.ToItemID() == pcItemData->sItem.sItemID.ToItemID()) && (cItemWrapper.sItem.iChk1 == pcItemData->sItem.iChk1) && (cItemWrapper.sItem.iChk2 == pcItemData->sItem.iChk2) && (cItemWrapper.sPosition.Equals( &pcItemData->sPosition )) )
		return TRUE;

	return FALSE;
}

const char * ItemInfoBox::GetItemRarityName( EItemRarity eRarity ) const
{
	switch ( eRarity )
	{
		case ITEMRARITY_Common:		return "Comun";
		case ITEMRARITY_Uncommon:	return "Inusual";
		case ITEMRARITY_Rare:		return "Raro";
		case ITEMRARITY_Epic:		return "Epico";
		case ITEMRARITY_Legendary:	return "Legendario";
		default:					return "";
	}
}

BOOL ItemInfoBox::FormatItemInfo( ItemData * pcItemData )
{
	if ( IsBeginnerSet( pcItemData ) )
	{
		AddString( 0, "\315tem Impulso 70", D3DCOLOR_ARGB( 255, 132, 50, 254 ) );
		AddString( 1, "" );
	}

	if ( pcItemData->sItem.eRarity != ITEMRARITY_None )
	{
		AddString( 0, GetItemRarityName( pcItemData->sItem.eRarity ), GetItemRarityColor( pcItemData->sItem.eRarity ), TRUE );
		if ( !vLeftText.empty() )
			ApplyTooltipRarityTextStyle( vLeftText.back(), pcItemData->sItem.eRarity );
		AddString( 1, "" );
	}

	if ( auto pszHeadModel = ITEMHANDLER->GetHeadModel( pcItemData->sItem.sItemID.ToInt() ) )
	{
		static EItemID eLastItemHeadID = ITEMID_None;

		if ( (eLastItemHeadID != pcItemData->sItem.sItemID.ToItemID()) || (pWindowHair->IsOpen() == FALSE) )
		{
			auto pUnitMeshPreview = pWindowHair->GetElement<UI::UnitMesh>( UNITMESHID_HeadPreview );
			pUnitMeshPreview->FreeUnit();
			pUnitMeshPreview->SetRenderBody( FALSE );
			pUnitMeshPreview->PrepareUnitData( UNITDATA );
			pUnitMeshPreview->SetHeadModel( ITEMHANDLER->GetHeadModel( pcItemData->sItem.sItemID.ToInt() ) );
			pUnitMeshPreview->SetCameraPosition( Point3D( pUnitMeshPreview->GetCameraPosition().iX, pUnitMeshPreview->GetCameraPosition().iY + (1 << 8), pUnitMeshPreview->GetCameraPosition().iZ ) );
			pWindowHair->Show();

			eLastItemHeadID = pcItemData->sItem.sItemID.ToItemID();
		}
	}
	else
		pWindowHair->Hide();

	if ( auto pszArmorPattern = ITEMHANDLER->GetArmorPatternName( UNITDATA, pcItemData->sItem.sItemID.ToInt() ) )
	{
		static EItemID eLastItemBodyID = ITEMID_None;

		int iGender = ITEMHANDLER->GetItemGender( pcItemData->sItem.sItemID.ToInt() );
		if ( (iGender == UNITDATA->GetCharacterGender()) || (iGender == 0) )
		{
			if ( (eLastItemBodyID != pcItemData->sItem.sItemID.ToItemID()) || (pWindowBody->IsOpen() == FALSE) )
			{
				auto pUnitMeshPreview = pWindowBody->GetElement<UI::UnitMesh>( UNITMESHID_BodyPreview );
				pUnitMeshPreview->FreeUnit();
				pUnitMeshPreview->SetRenderBody( TRUE );
				pUnitMeshPreview->PrepareUnitData( UNITDATA );
				RENDERER->SetUseNewRenderToLoad( true );
				pUnitMeshPreview->SetHeadModel( UNITDATA->sCharacterData.Player.szHeadModel );
				pUnitMeshPreview->SetBodyModel( ITEMHANDLER->GetArmorPatternName( UNITDATA, pcItemData->sItem.sItemID.ToInt() ) );
				RENDERER->ResetUseNewRenderToLoad();
				pUnitMeshPreview->SetCameraPosition( Point3D( pUnitMeshPreview->GetCameraPosition().iX, pUnitMeshPreview->GetCameraPosition().iY - (2 << 8), pUnitMeshPreview->GetCameraPosition().iZ ) );
				pWindowBody->Show();

				eLastItemBodyID = pcItemData->sItem.sItemID.ToItemID();
			}
		}
		else
			pWindowBody->Hide();
	}
	else
		pWindowBody->Hide();

	if ( pcItemData->sItem.eCraftType == ITEMCRAFTTYPE_Mixing )
	{
		switch ( pcItemData->sItem.eMixTypeName )
		{
			case MIXTYPENAME_Devine:
				AddString( 0, "Mezcla Devine", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
			 break;
			case MIXTYPENAME_Celesto:
				AddString( 0, "Mezcla Celesto", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
			 break;
			case MIXTYPENAME_Mirage:
				AddString( 0, "Mezcla Espejismo", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
			 break;
			case MIXTYPENAME_Inferna:
				AddString( 0, "Mezcla Inferna", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
			 break;
			case MIXTYPENAME_Enigma:
				AddString( 0, "Mezcla Enigma", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
			 break;
			case MIXTYPENAME_Bellum:
				AddString( 0, "Mezcla Bellum", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
			 break;
			case MIXTYPENAME_Oredo:
				AddString( 0, "Mezcla Oredo", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
			 break;

			case MIXTYPENAME_Devine2:
				AddString( 0, "Mezcla Devine #2", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
			 break;
			case MIXTYPENAME_Celesto2:
				AddString( 0, "Mezcla Celesto #2", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
			 break;
			case MIXTYPENAME_Mirage2:
				AddString( 0, "Mezcla Espejismo #2", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
			 break;
			case MIXTYPENAME_Inferna2:
				AddString( 0, "Mezcla Inferna #2", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
			 break;
			case MIXTYPENAME_Enigma2:
				AddString( 0, "Mezcla Enigma #2", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
			 break;
			case MIXTYPENAME_Bellum2:
				AddString( 0, "Mezcla Bellum #2", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
			 break;
			case MIXTYPENAME_Oredo2:
				AddString( 0, "Mezcla Oredo #2", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;

			case MIXTYPENAME_BellumDefense:
				AddString( 0, "Mezcla Bellum Defensa", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
			case MIXTYPENAME_BellumBlock:
				AddString( 0, "Mezcla Bellum Bloqueo", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
			case MIXTYPENAME_BellumVelocity:
				AddString( 0, "Mezcla Bellum Velocidad", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
			case MIXTYPENAME_BellumPower:
				AddString( 0, "Mezcla Bellum Poder", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
			case MIXTYPENAME_BellumCritical:
				AddString( 0, "Mezcla Bellum Cr\355tico", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
			case MIXTYPENAME_BellumRating:
				AddString( 0, "Mezcla Bellum Tasa", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
			case MIXTYPENAME_BellumVitality:
				AddString( 0, "Mezcla Bellum Vitalidad", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
			case MIXTYPENAME_OredoSwiftness:
				AddString( 0, "Mezcla Oredo Rapidez", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
			case MIXTYPENAME_OredoPower:
				AddString( 0, "Mezcla Oredo Poder", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
			case MIXTYPENAME_OredoCritical:
				AddString( 0, "Mezcla Oredo Cr\355tico", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
			case MIXTYPENAME_OredoDefense:
				AddString( 0, "Mezcla Oredo Defensa", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
			case MIXTYPENAME_OredoBlock:
				AddString( 0, "Mezcla Oredo Bloqueo", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
			case MIXTYPENAME_OredoRating:
				AddString( 0, "Mezcla Oredo Tasa", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
			case MIXTYPENAME_OredoVitality:
				AddString( 0, "Mezcla Oredo Vitalidad", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
			case MIXTYPENAME_OredoVelocity:
				AddString( 0, "Mezcla Oredo Velocidad", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
			case MIXTYPENAME_OredoEfficiency1:
				AddString( 0, "Mezcla Oredo Eficiencia #1", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
			case MIXTYPENAME_OredoEfficiency2:
				AddString( 0, "Mezcla Oredo Eficiencia #2", D3DCOLOR_ARGB( 255, 170, 160, 170 ) );
				AddString( 1, "" );
				break;
		}
	}
	if( pcItemData->sItem.sItemID.ToItemID() == ITEMID_ValentoRing )
	{
		AddString( 0, "\315tem de jefe", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToItemID() == ITEMID_KelvezuAmulet )
	{
		AddString( 0, "\315tem de jefe", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToItemID() == ITEMID_DraxosBoots )
	{
		AddString( 0, "\315tem de jefe", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
		AddString( 1, "" );
	}
	if( pcItemData->sItem.sItemID.ToInt() == ITEMID_MokovaBoots )
	{
		AddString( 0, "\315tem de jefe", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToItemID() == ITEMID_FurySheltom )
	{
		AddString( 0, "\315tem de jefe", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
		AddString( 1, "" );
	}
	if (pcItemData->sItem.sItemID.ToItemID() == ITEMID_ThroneSheltom)
	{
		AddString(0, "\315tem de jefe", D3DCOLOR_RGBA(0, 128, 128, 255));
		AddString(1, "");
	}
	if (pcItemData->sItem.sItemID.ToItemID() == ITEMID_ThroneAmulet )
	{
		AddString( 0, "\315tem de jefe", D3DCOLOR_RGBA(0, 128, 128, 255 ) );
		AddString( 1, "");
	}
	if ( pcItemData->sItem.sItemID.ToItemID() == ITEMID_TullaAmulet )
	{
		AddString( 0, "\315tem de jefe", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToItemID() == ITEMID_FallenRing )
	{
		AddString( 0, "\315tem de jefe", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToItemID() == ITEMID_DarkGuardianSheltom )
	{
		AddString( 0, "\315tem de jefe", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToItemID() == ITEMID_ArgonianGauntlets )
	{
		AddString( 0, "\315tem de jefe", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToItemID() == ITEMID_GreedyGauntlets )
	{
		AddString( 0, "\315tem de jefe", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToItemID() == ITEMID_DevilShyRing )
	{
		AddString( 0, "\315tem de jefe", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToItemID() == ITEMID_ThroneRing )
	{
		AddString(0, "\315tem de jefe", D3DCOLOR_RGBA(0, 128, 128, 255));
		AddString(1, "");
	}
	if ( pcItemData->sItem.sItemID.ToItemID() == ITEMID_GorgonyteEarring )
	{
		AddString( 0, "\315tem de jefe", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToItemID() == ITEMID_VolcanosEarring )
	{
		AddString( 0, "\315tem de jefe", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
		AddString( 1, "" );
	}
	if ( IsCostumeItem( pcItemData ) )
	{
		AddString( 0, "\315tem cosm\351tico", D3DCOLOR_RGBA( 255, 105, 180, 255 ) );
		AddString( 1, "" );
	}
	if ( ((pcItemData->sItem.sItemID.ToInt() & 0xFFFF0000) == ITEMID_RuneCodeManufacture1) || (pcItemData->sItem.sItemID.ToItemType() == ITEMTYPE_Crafting2) )
	{
		AddString( 0, "\315tem de fabricaci\363n", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		AddString( 1, "" );
	}
	if ( ( (pcItemData->sItem.sItemID.ToInt() & 0xFFFF0000 ) == ITEMID_RecipeCode ) )
	{
		AddString( 0, "Receta de fabricaci\363n", D3DCOLOR_ARGB( 255, 155, 50, 255 ) );
		AddString( 1, "" );

	//Betting
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_DOUBLETALE )
	{
		AddString( 0, "\241Prueba tu suerte!", D3DCOLOR_ARGB( 255, 155, 50, 255 ) );
		AddString( 1, "" );

		AddString( 0, "Gana 200M o pierde 100M TALE", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, "" );

		AddString( 0, "\241Acierta el premio mayor para obtener un \355tem valioso!", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_TRIPLETALE )
	{
		AddString( 0, "\241Prueba tu suerte!", D3DCOLOR_ARGB( 255, 155, 50, 255 ) );
		AddString( 1, "" );

		AddString( 0, "Gana 300M o pierde 100M TALE", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, "" );

		AddString( 0, "\241Acierta el premio mayor para obtener un \355tem valioso!", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_TIMESTENTALE )
	{
		AddString( 0, "\241Prueba tu suerte!", D3DCOLOR_ARGB( 255, 155, 50, 255 ) );
		AddString( 1, "" );

		AddString( 0, "Gana 1B o pierde 100M TALE", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, "" );

		AddString( 0, "\241Acierta el premio mayor para obtener un \355tem valioso!", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, "" );
	}
	//End Betting

//            WEAPONS RECIPE

		if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_WeaponRecipe )
		{
			AddString( 0, "> Hacha Antigua", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Garra Salamandra", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Martillo Gladiador", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Arco Onda", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Lanza Or\341culo", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Jabalina Extrema", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Espada Vengadora", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Bast\363n Reliquia", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Daga Piedra Lunar", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Phantom Pejula", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Anillo Runa +1", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
		}
		else if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_WeaponRecipeTier1 )
		{
			AddString( 0, "> Hacha Reliquia", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Garra F\351nix", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Martillo Arconte", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Ballesta Gran", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Guada\361a Inmortal", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Jabalina Drag\363n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Espada Tit\341n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Bast\363n Drag\363n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Daga Ca\363tica", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Phantom Luta", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Anillo Runa +2", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
		}
		else if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_WeaponRecipeTier2 )
		{
			AddString( 0, "> Hacha Extrema", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Garra Quimera", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Martillo de Justicia", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Arco Espejismo", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Lanza Extrema", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Jabalina con P\372as", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Espada Guiverno", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Vara Guiverno", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Daga Saqueadora", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Phantom Natanh", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Anillo Runa +3", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
		}
		else if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_WeaponRecipeTier3 )
		{
			AddString( 0, "> Hacha Minotauro", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Garra Extrema", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Martillo de Hueso de Drag\363n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Arco Venganza", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Lanza Fuego Infernal", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Jabalina Legendaria", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Espada Inmortal", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Bast\363n G\363tico", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Daga Enigma", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Phantom Kahsehtha", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Anillo Sellado", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
		}
		else if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_WeaponRecipeTier4 )
		{
			AddString( 0, "> Hacha Guiverno", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Garra V\355bora", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Martillo Guardi\341n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Arco Guiverno", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Lanza Acorazada", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Jabalina Inmortal", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Espada Justicia", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Vara Oracle", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Espada Doble Drag\363n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Phantom Niyaha", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Anillo Sellado +1", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
		}
		else if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_WeaponRecipeTier5 )
		{
			AddString( 0, "> Hacha Zecram", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Garra Injusticia", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Martillo de Perdici\363n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Arco Inmortal", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Guada\361a Segadora", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Jabalina Hereje", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Espada Extrema", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Bast\363n Celestial", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Daga Demon\355aca", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Phantom Acala", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Anillo Sellado +2", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
		}
		else if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_WeaponRecipeTier6 )
		{
			AddString( 0, "> Hacha Drag\363n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Garra Hereje", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Martillo Drag\363n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Arco Salamandra", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Lanza Drag\363n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Jabalina Salamandra", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Espada Espejismo", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Bast\363n \311lfico", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Daga Brillo Oscuro", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Phantom Wakinyan", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Anillo Sellado +3", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
		}
		else if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_WeaponRecipeTier7 )
		{
			AddString( 0, "> Hacha Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Hacha Legendaria", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Garra Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Martillo Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Arco Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Lanza Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Jabalina Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Espada Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Espada Legendaria", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Bast\363n Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Vara Legendaria", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Daga Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Phantom Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Anillo M\355stico", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
		}
		
//           DEFENCE RECIPE

		else if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_DefenseRecipe )
		{
			AddString( 0, "> Armadura Condena", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> T\372nica Alquimista", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Escudo Tit\341n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Mundano", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Brazaletes Tit\341n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Botas Guiverno", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Guanteletes Diamante", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Amuleto Runa +1", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
		}
		else if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_DefenseRecipeTier1 )
		{
			AddString( 0, "> Armadura Salamandra", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> T\372nica Astral", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Escudo M\355stico", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Cuentas Salamandra", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Brazaletes Sagrados", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Botas Runa", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Guanteletes \301ngel", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Amuleto Runa +2", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
		}
		else if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_DefenseRecipeTier2 )
		{
			AddString( 0, "> Armadura Guiverno", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> T\372nica Arconte", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Escudo Vampiro", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Cosmos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Brazaletes Guiverno", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Botas Reales", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Guanteletes Reliquia", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Amuleto Runa +3", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
		}
		else if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_DefenseRecipeTier3 )
		{
			AddString( 0, "> Armadura V\355bora", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> T\372nica F\351nix", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Escudo Drag\363n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Orbe Guiverno", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Brazaletes Antiguos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Botas Antiguas", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Guanteletes Antiguos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Amuleto Sellado", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
		}
		else if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_DefenseRecipeTier4 )
		{
			AddString( 0, "> Armadura F\351nix", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> T\372nica Ruah", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Escudo F\351nix", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Melenas de \311bano", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Brazaletes Infernales", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Botas Infernales", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Guanteletes Infernales", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Amuleto Sellado +1", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
		}
		else if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_DefenseRecipeTier5 )
		{
			AddString( 0, "> Armadura Frenes\355", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> T\372nica Eterna", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Escudo Acorazado", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Cuentas de Averno", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Brazaletes F\351nix", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Botas F\351nix", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Guanteletes F\351nix", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Amuleto Sellado +2", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
		}
		else if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_DefenseRecipeTier6 )
		{
			AddString( 0, "> Armadura Monta\361esa", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> T\372nica Arc\341ngel", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Escudo Infernal", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Rosario de Malicia", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Brazaletes Frenes\355", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Botas Frenes\355", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Guanteletes Frenes\355", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Amuleto Sellado +3", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
		}
		else if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_DefenseRecipeTier7 )
		{
			AddString( 0, "> Armadura Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> T\372nica Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Escudo Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Orbe Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Brazaletes Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Botas Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Guanteletes Kronus", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "> Amuleto M\355stico", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
		}
	}	
	
 // END
 
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_SilverLockedChest )
	{
		AddString( 0, "\315tem de Campo de Acci\363n", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_GoldenLockedChest )
	{
		AddString( 0, "\315tem de Campo de Acci\363n", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_BlueLockedChest )
	{
		AddString( 0, "\315tem de Campo de Acci\363n", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_PurpleLockedChest )
	{
		AddString( 0, "\315tem de Campo de Acci\363n", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_TropicalScroll )
	{
		AddString( 0, "\315tem de Campo de Acci\363n", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_ChestKey )
	{
		AddString( 0, "\315tem de Campo de Acci\363n", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_GhostBoots )
	{
		AddString( 0, "\315tem de Castillo Fantasma", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_GhostGauntlets )
	{
		AddString( 0, "\315tem de Castillo Fantasma", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_GhostBracelets )
	{
		AddString( 0, "\315tem de Castillo Fantasma", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_GhostCastleBracelets )
	{
		AddString( 0, "\315tem de Castillo Fantasma", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_ActionFieldPass )
	{
		AddString( 0, "\315tem de Castillo Fantasma", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_ActionFieldPassFD )
	{
		AddString( 0, "\315tem de Isla Tropical", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_ActionFieldPassDD )
	{
		AddString( 0, "\315tem de Mazmorra del Drag\363n", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_TropicalBracelets )
	{
		AddString( 0, "\315tem de Isla Tropical", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		AddString( 1, "" );
	}
	if ( pcItemData->sItem.sItemID.ToInt() == ITEMID_BrilliantStone )
	{
		AddString( 0, "\315tem de evento de Bellatra", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		AddString( 1, "" );
	}
	if ( PERFECTVIEWHANDLER->IsSet() )
	{
		AddString( 0, "\315tem perfecto", D3DCOLOR_RGBA( 0, 191, 255, 255 ) );
		AddString( 1, "" );
	}
	if( pcItemData->sItem.bPerfectItem )
	{
		AddString( 0, "\315tem perfecto", D3DCOLOR_RGBA( 0, 191, 255, 255 ) );
		AddString( 1, "" );
	}
	if( bIsEquippedItem && bCompareItem )
	{
		AddString( 0, "\315tem equipado", D3DCOLOR_RGBA( 70, 125, 80, 255 ) );
		AddString( 1, "" );
	}

	int iGender = ITEMHANDLER->GetItemGender( pcItemData->sItem.sItemID.ToInt() );
	if ( iGender != CHARACTERGENDER_None )
	{
		if ( iGender == CHARACTERGENDER_Male )
			AddString( 0, "\315tem masculino", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );
		else
			AddString( 0, "\315tem femenino", D3DCOLOR_RGBA( 255, 155, 50, 255 ) );

		AddString( 1, "" );
	}

	//Break Line
	AddString( 0, " " );
	AddString( 1, " " );

	EItemID eItemID = pcItemData->sBaseItemID.ToItemID();
	switch( eItemID )
	{
		case ITEMID_HopyCostumeTime:
		case ITEMID_CuepyCostumeTime:
/*			AddString( 0, "\315tem de evento de Pascua", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
			AddString( 1, "" );
			AddString( 0, " " );
			AddString( 1, " " ); */
			break;
		case ITEMID_EasterHat:
			AddString( 0, "\315tem de evento de Pascua", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
			AddString( 1, "" );
			AddString( 0, "Otorga +2 Vel. de movimiento\nOtorga +5% EXP", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_ChemistHat:
			AddString( 0, "\315tem de evento", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
			AddString( 1, "" );
			AddString( 0, "Otorga +1 bot\355n extra", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_PatronumHat:
		case ITEMID_GoldenHopyHat:
			AddString( 0, "\315tem de evento", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
			AddString( 1, "" );
			AddString( 0, "Otorga +3% cr\355tico", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_ObscureHat:
			AddString( 0, "\315tem de evento", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
			AddString( 1, "" );
			AddString( 0, "Otorga +5% poder de ataque", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_PartyCore:
			AddString( 0, "Clic derecho para elegir un\nmiembro del grupo y teletransportarte", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_ColorfulXmasTree:
		case ITEMID_SnowyXmasTree:
			AddString( 0, "Clic derecho para colocar este \341rbol de Navidad", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_SoulCrystal:
			AddString( 0, "Clic derecho para activar.\nMata un monstruo mientras el cristal\nest\341 activo para que su alma\nquede atrapada dentro", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			AddString( 0, "" );
			AddString( 1, "" );
			break;
		case ITEMID_SoulSummonCrystal:
			AddString( 0, "Clic derecho para invocar el alma\natrapada dentro del cristal.\nMonstruo atrapado:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			AddString( 0, pcItemData->sItem.szItemName, D3DCOLOR_ARGB( 255, 0, 191, 255 ), TRUE );
			AddString( 1, "" );
			AddString( 0, "" );
			AddString( 1, "" );
			break;
		case ITEMID_ActionFieldPass:
			AddString( 0, "\241Puedes entrar una vez m\341s a\nCastillo Fantasma el mismo d\355a\ncon este \355tem!", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_TropicalScroll:
			AddString( 0, "\241Puedes usar este \355tem para revivir en\nIsla Tropical sin\nperder EXP!", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_ActionFieldPassFD:
			AddString( 0, "\241Puedes entrar una vez m\341s a\nIsla Tropical el mismo d\355a\ncon este \355tem!", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_ActionFieldPassDD:
			AddString( 0, "\241Puedes entrar una vez m\341s a\nMazmorra del Drag\363n el mismo d\355a\ncon este \355tem!", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_LightPurpleRune:
			AddString( 0, "Se usa para fabricar el anillo Diablo T\355mido", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_LightSilverRune:
			AddString( 0, "Se usa para fabricar los pendientes Volcanos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_ThroneYellowRune:
			AddString(0, "Se usa para fabricar el anillo Trono", D3DCOLOR_ARGB(255, 245, 240, 218 ) );
			AddString(1, "");
			break;
		case ITEMID_ThroneRedRune:
			AddString(0, "Se usa para fabricar el amuleto Trono", D3DCOLOR_ARGB(255, 245, 240, 218 ) );
			AddString(1, "");
			break;
		case ITEMID_ThroneGreenRune:
			AddString(0, "Se usa para fabricar el sheltom Trono", D3DCOLOR_ARGB(255, 245, 240, 218 ) );
			AddString(1, "");
			break;
		case ITEMID_LightBlueRune:
			AddString( 0, "Se usa para fabricar el amuleto Tulla", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_DarkRedRune:
			AddString( 0, "Se usa para fabricar las botas Draxos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_LightRedRune:
			AddString( 0, "Se usa para fabricar los brazaletes Tropical", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_LightGreenRune:
			AddString( 0, "Se usa para fabricar el anillo Abyss", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_LightOrangeRune:
			AddString( 0, "Se usa para fabricar los guanteletes Greedy", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_GreenCrystalRune:
		case ITEMID_RedCrystalRune:
		case ITEMID_BlueCrystalRune:
			AddString( 0, "Se usa para fabricar el sheltom Furia", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_GoldCrystalRune:
		case ITEMID_SilverCrystalRune:
		case ITEMID_BronzeCrystalRune:
			AddString(0, "Se usa para fabricar el sheltom Trono", D3DCOLOR_ARGB(255, 245, 240, 218));
			AddString(1, "");
			break;
		case ITEMID_BrilliantStone:
			AddString( 0, "Intercambia en Ihin\nPNJ del evento Bellatra", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_BlueStone:
			AddString( 0, "Reinicia todos los puntos de atributos.", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_RedStone:
			AddString( 0, "Reinicia todos los puntos de habilidades.", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_GreenStone:
			AddString( 0, "Reinicia todos los puntos de\nhabilidades y atributos.", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_FatalEdge:
			AddString( 0, "+10% da\361o final\nSolo funciona en SoD", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_AvertScroll:
			AddString( 0, "+10% de absorci\363n\nSolo funciona en SoD", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_MatureStoneA:
			AddString( 0, "Madura la barra de envejecimiento del\narma equipada\na 100% al instante", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_MatureStoneB:
			AddString( 0, "Madura la barra de envejecimiento de\norbe o escudo equipado\na 100% al instante", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_MatureStoneC:
			AddString( 0, "Madura la barra de envejecimiento de\nt\372nica o armadura equipada\na 100% al instante", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_SapphireStone:
			AddString( 0, "Entrena todas las habilidades T1\na T3 al 100% al instante", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_RubyStone:
			AddString( 0, "Entrena todas las habilidades de T1\na T3 al 10%\nNivel req.: 1-95", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_SpecStoneFS:
		case ITEMID_SpecStoneMS:
		case ITEMID_SpecStoneAS:
		case ITEMID_SpecStonePS:
		case ITEMID_SpecStoneATA:
		case ITEMID_SpecStoneKS:
		case ITEMID_SpecStoneMG:
		case ITEMID_SpecStonePRS:
		case ITEMID_SpecStoneASS:
		case ITEMID_SpecStoneSHA:
		case ITEMID_DeluxeSpecStoneFS:
		case ITEMID_DeluxeSpecStoneMS:
		case ITEMID_DeluxeSpecStoneAS:
		case ITEMID_DeluxeSpecStonePS:
		case ITEMID_DeluxeSpecStoneATA :
		case ITEMID_DeluxeSpecStoneKS :
		case ITEMID_DeluxeSpecStoneMG :
		case ITEMID_DeluxeSpecStonePRS :
		case ITEMID_DeluxeSpecStoneASS :
		case ITEMID_DeluxeSpecStoneSHA:
			  AddString(0, "Combina esta piedra con 2 Jeras\no una Super Jera con el Maestro Shalon.", D3DCOLOR_ARGB(255, 245, 240, 218));
			  AddString(1, "");
			  break;

		case ITEMID_CaravanHopyCrystal:
		case ITEMID_CaravanRudolphCrystal:
		case ITEMID_CaravanArmaCrystal:
		case ITEMID_CaravanBumaCrystal:
		case ITEMID_CaravanCuepyCrystal:
		case ITEMID_CaravanHungkyCrystal:
		case ITEMID_CaravanRabieCrystal:
		case ITEMID_CaravanTobieCrystal:
		case ITEMID_CaravanSirKnightCrystal:
		case ITEMID_CaravanPinguCrystal:
		case ITEMID_CaravanHopyCheapCrystal:
		case ITEMID_CaravanYetiCrystal:
		case ITEMID_CaravanGoldenHopyCrystal:
			AddString( 0, "Lleva \355tems por ti", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );  
			AddString( 1, "" );
			break;
		case ITEMID_ExpUp1H:
		case ITEMID_ExpUp3H:
		case ITEMID_ExpUp24H:
		case ITEMID_ExpUp48H:
		case ITEMID_ExpUp72H:
			AddString( 0, "25% experiencia adicional", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_HPUp12H:
		case ITEMID_HPUp24H:
		case ITEMID_HPUp48H:
		case ITEMID_HPUp72H:
			AddString( 0, "+10 reg. HP", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_MPUp12H:
		case ITEMID_MPUp24H:
		case ITEMID_MPUp48H:
		case ITEMID_MPUp72H:
			AddString( 0, "+10 reg. man\341", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_MPDown12H:
		case ITEMID_MPDown24H:
		case ITEMID_MPDown48H:
		case ITEMID_MPDown72H:
			AddString( 0, "Reduce un 25% el uso de man\341", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_SPDown12H:
		case ITEMID_SPDown24H:
		case ITEMID_SPDown48H:
		case ITEMID_SPDown72H:
			AddString( 0, "Reduce un 25% el uso de stamina", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_TuttiFruttiHat:
			AddString( 0, "\315tem de Carnival", D3DCOLOR_ARGB( 255, 120, 255, 120 ) );
			AddString( 1, "" );
			AddString( 0, "+6% EXP", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_CarnivalLetterA:
		case ITEMID_CarnivalLetterC:
		case ITEMID_CarnivalLetterI:
		case ITEMID_CarnivalLetterL:
		case ITEMID_CarnivalLetterN:
		case ITEMID_CarnivalLetterR:
		case ITEMID_CarnivalLetterV:
		case ITEMID_CarnivalApple:
		case ITEMID_CarnivalBanana:
		case ITEMID_CarnivalJabuticaba:
		case ITEMID_CarnivalMaracuja:
		case ITEMID_CarnivalPitanga:
		case ITEMID_CarnivalStrawberry:
		case ITEMID_PCandyAxe:
		case ITEMID_PCandyDagger:
		case ITEMID_PCandyHammer:
		case ITEMID_PCandyWand:
		case ITEMID_PCandyPhantom:
		case ITEMID_PCandyScythe:
		case ITEMID_PCandyBow:
		case ITEMID_PCandySword:
		case ITEMID_PCandyJavelin:
		case ITEMID_PCandyShield:
			AddString( 0, "\315tem de Carnival", D3DCOLOR_ARGB( 255, 120, 255, 120 ) );
			AddString( 1, "" );
			break;

		case ITEMID_WitchHat:
		case ITEMID_CartolaHat:
		case ITEMID_HalloweenHat:
			AddString( 0, "\315tem de Halloween", D3DCOLOR_ARGB( 255, 180, 100, 175 ) );
			AddString( 1, "" );
			AddString( 0, "+10 reg. HP\n+10 HP adicional", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;

		case ITEMID_MountHog1:
		case ITEMID_MountHopy:
		case ITEMID_MountHopy1:
		case ITEMID_MountHopy2:
		case ITEMID_MountHorse:
		case ITEMID_MountHorse1:
		case ITEMID_MountHorse2:
		case ITEMID_MountUnicorn3:
		case ITEMID_MountGhostWolf:
		case ITEMID_MountHorsePTM:
		case ITEMID_MountWhiteDeer:
		case ITEMID_MountMecaballus:
		case ITEMID_MountRabie:
		case ITEMID_MountRaptor:
		case ITEMID_MountRaptor1:
		case ITEMID_MountRaptor2:
		case ITEMID_MountRaptor3:
			AddString( 0, "Montura com\372n", D3DCOLOR_ARGB( 255, 180, 100, 175 ) );
			AddString( 1, "" );
			AddString( 0, "\241Una montura com\372n adorable!", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;

		case ITEMID_MountObscureHog:
		case ITEMID_MountIronCharger:
		case ITEMID_MountRudolf:
			AddString(0, "Montura rara", D3DCOLOR_ARGB(255, 180, 100, 175));
			AddString(1, "");
			AddString(0, "\241Una montura rara para montar!", D3DCOLOR_ARGB(255, 245, 240, 218));
			AddString(1, "");
			break;

		case ITEMID_MountLion1:
		case ITEMID_MountTecnoTiger:
		case ITEMID_MountTecnoTiger1:
		case ITEMID_MountSnowdeer:
		case ITEMID_PinguMountMysterious:
		case ITEMID_MountIceTiger:
			AddString(0, "Montura \351pica", D3DCOLOR_ARGB(255, 180, 100, 175));
			AddString(1, "");
			AddString(0, "\241Una montura \351pica para montar!", D3DCOLOR_ARGB(255, 245, 240, 218));
			AddString(1, "");
			break;

		case ITEMID_MountHog:
		case ITEMID_MountUnicorn6:
		case ITEMID_MountSnowflakeUnicorn:
		case ITEMID_MountBlueDragon:
		case ITEMID_MountZira:
		case ITEMID_MountPingu1:
		case ITEMID_MountRedDragon:
		case ITEMID_MountLion5:
			AddString(0, "Montura legendaria", D3DCOLOR_ARGB(255, 180, 100, 175));
			AddString(1, "");
			AddString(0, "\241Una montura legendaria para montar!", D3DCOLOR_ARGB(255, 245, 240, 218));
			AddString(1, "");
			break;

		case ITEMID_VampireSuit:
		case ITEMID_Succubus:
		case ITEMID_HalloweenAxe:
		case ITEMID_HalloweenClaw:
		case ITEMID_HalloweenDagger:
		case ITEMID_HalloweenHammer:
		case ITEMID_HalloweenStaff:
		case ITEMID_HalloweenWand:
		case ITEMID_HalloweenPhantom:
		case ITEMID_HalloweenScythe:
		case ITEMID_HalloweenBow:
		case ITEMID_HalloweenSword:
		case ITEMID_HalloweenBladeSword:
		case ITEMID_HalloweenJavelin:
		case ITEMID_HalloweenShield:
		case ITEMID_RottenLantern:
		case ITEMID_EvilLantern:
		case ITEMID_InfernalLantern:
			AddString( 0, "\315tem de Halloween", D3DCOLOR_ARGB( 255, 180, 100, 175 ) );
			AddString( 1, "" );
			break;

		case ITEMID_IceCostumeMale:
		case ITEMID_IceCostumeFemale:
		case ITEMID_GoldenHopyCostumeMale:
		case ITEMID_GoldenHopyCostumeFemale:
		case ITEMID_GoldenHopyCostumeMaleTime:
		case ITEMID_GoldenHopyCostumeFemaleTime:
			AddString( 0, "\315tem de evento", D3DCOLOR_RGBA( 0, 128, 128, 255 ) );
			AddString( 1, "" );
			break;

		case ITEMID_XmasCostumeOldAxe:
		case ITEMID_XmasCostumeOldAxe1Hand:
		case ITEMID_XmasCostumeOldClaw:
		case ITEMID_XmasCostumeOldDagger:
		case ITEMID_XmasCostumeOldHammer:
		case ITEMID_XmasCostumeOldStaff:
		case ITEMID_XmasCostumeOldPhantom:
		case ITEMID_XmasCostumeOldScythe:
		case ITEMID_XmasCostumeOldBow:
		case ITEMID_XmasCostumeOldSword:
		case ITEMID_XmasCostumeOldSword1Hand:
		case ITEMID_XmasCostumeOldJavelin:

		case ITEMID_XmasCostumeAxe:
		case ITEMID_XmasCostumeAxe1Hand:
		case ITEMID_XmasCostumeClaw:
		case ITEMID_XmasCostumeDagger:
		case ITEMID_XmasCostumeHammer:
		case ITEMID_XmasCostumeStaff:
		case ITEMID_XmasCostumeWand:
		case ITEMID_XmasCostumePhantom:
		case ITEMID_XmasCostumeScythe:
		case ITEMID_XmasCostumeBow:
		case ITEMID_XmasCostumeSword:
		case ITEMID_XmasCostumeSword1Hand:
		case ITEMID_XmasCostumeJavelin:
		case ITEMID_XmasCostumeShield:
			AddString( 0, "\315tem de Navidad", D3DCOLOR_ARGB( 255, 255, 100, 100 ) );
			AddString( 1, "" );
			break;

		case ITEMID_KingStone:
			if ( pcItemData->sItem.eMixTypeName == ITEMCRAFTTYPE_TGFKingFury )
			{
				AddString( 0, "\315tem de Hagios", D3DCOLOR_ARGB( 255, 255, 248, 0 ) );
				AddString( 1, "" );
			}
			else if ( pcItemData->sItem.eMixTypeName == ITEMCRAFTTYPE_TGFLordBabel )
			{
				AddString( 0, "\315tem de Furia del Rey", D3DCOLOR_ARGB( 255, 255, 248, 0 ) );
				AddString( 1, "" );
			}
			AddString( 0, FormatString( "Muerto en %d minuto%s", pcItemData->sItem.sQuestMonsters.sCur, pcItemData->sItem.sQuestMonsters.sCur > 1 ? "s" : "" ), D3DCOLOR_ARGB( 255, 125, 180, 175 ) );
			AddString( 1, "" );
			break;
		case ITEMID_ThirdEye1H:
		case ITEMID_ThirdEye3H:
		case ITEMID_ThirdEye24H:
		case ITEMID_ThirdEye48H:
		case ITEMID_ThirdEye72H:
			AddString( 0, "Un bot\355n adicional", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_PhoenixEgg:
			AddString( 0, "Invoca una mascota\nF\351nix aleatoria", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_GravityStone72H:
			AddString( 0, "Otorga +1000 de peso", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_TeleportCore:
			AddString( 0, "Teletransporta a un mapa", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_StarterCore:
			AddString(0, "Teletransporta a un mapa inicial", D3DCOLOR_ARGB(255, 245, 240, 218));
			AddString(1, "");
			break;
		case ITEMID_AgingStone:
			AddString( 0, "Reduce un 10% la probabilidad\nde fallar envejecimiento", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_RipeStone:
			AddString( 0, "Reduce un 20% la probabilidad\nde fallar envejecimiento", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_FluenceStone:
			AddString( 0, "Reduce un 30% la probabilidad\nde fallar envejecimiento", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_ArcaneStone:
			AddString( 0, "Reduce un 40% la probabilidad\nde fallar envejecimiento", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_CopperOre:
			AddString( 0, "Evita que los \355tems\nse rompan", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_CleanItem:
			AddString( 0, "Limpia mezcla/edad\nde un \355tem", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_Fireworks:
			AddString( 0, "\241Celebremos!", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_HairPotionA:
		case ITEMID_HairPotionB:
		case ITEMID_HairPotionC:
		case ITEMID_HairPotionD:
		case ITEMID_HairPotionE:
		case ITEMID_HairPotionF:
		case ITEMID_HairPotionG:
		case ITEMID_HairPotionH:
		case ITEMID_HairPotionI:
		case ITEMID_HairPotionJ:
		case ITEMID_HairPotionK:
		case ITEMID_HairPotionL:
		case ITEMID_HairPotionM:
		case ITEMID_HairPotionN:
		case ITEMID_HairPotionO:
		case ITEMID_HairPotionP:
		case ITEMID_HairPotionQ:
		case ITEMID_HairPotionR:
		case ITEMID_HairPotionS:
		case ITEMID_IceHair:
		case ITEMID_SamuraiHair:
			AddString( 0, "\241Cambia tu peinado!", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_BigHeadHappyness:
			AddString( 0, "A\361ade +50 tasa de ataque", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_BigHeadSadness:
			AddString( 0, "A\361ade +10 reg. MP/MP", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_BigHeadShyness:
			AddString( 0, "A\361ade +100 defensa", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_BigHeadLove:
			AddString( 0, "A\361ade +10 reg. HP/HP", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_BigHeadAngry:
			AddString( 0, "A\361ade +50 HP/MP/STM", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_BigHeadSurprised:
			AddString( 0, "A\361ade +2% tasa de bloqueo", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_BigHeadSensual:
			AddString( 0, "A\361ade +2 cr\355tico", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_TopazStone:
			AddString( 0, "Madura el \355tem\nequipado a 100% al instante", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_TurquoiseStone:
			AddString( 0, "Una piedra de maduraci\363n d\351bil", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_EmeraldStone:
			AddString( 0, "Entrena 10%\ntodas las habilidades T1~T3", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_SheepHat:
			AddString( 0, "+150 defensa", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_HairHelmetNew:
			AddString( 0, "+100 defensa", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
//			AddString( 1, "+150 defensa", D3DCOLOR_ARGB( 255, 200, 255, 200 ) );
			AddString( 1, "" );
			break;			
		case ITEMID_GiraffeHat:
			AddString( 0, "A\361ade +75 tasa de ataque", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_SoccerHat:
			AddString( 0, "A\361ade +2 vel. de movimiento", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_XMasRedHat:
			AddString( 0, "A\361ade +50 MP/STM", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_FeatherTier1:
			AddString( 0, "Reduce el enfriamiento de\nhabilidades Tier 1 en 10%", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_FeatherTier2:
			AddString( 0, "Reduce el enfriamiento de\nhabilidades Tier 2 en 10%", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_FeatherTier3:
			AddString( 0, "Reduce el enfriamiento de\nhabilidades Tier 3 en 10%", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_FeatherTier4:
			AddString( 0, "Reduce el enfriamiento de\nhabilidades Tier 4 en 10%", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_FeatherTier5:
			AddString( 0, "Reduce el enfriamiento de\nhabilidades Tier 5 en 10%", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_HPBooster:
			AddString( 0, "A\361ade +15% HP", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_MPBooster:
			AddString( 0, "A\361ade +15% MP", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_STMBooster:
			AddString( 0, "A\361ade +15% STM", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_RicartenCore:
			AddString( 0, "Teletransporta a Ricarten", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_NaviskoCore:
			AddString( 0, "Teletransporta a Navisko", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_AtlantisCore:
			AddString( 0, "Teletransporta a Atlantis", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_PillaiCore:
			AddString( 0, "Teletransporta a Phillai", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_SpecialCore:
			AddString(0, "Teletransporta a Oblivion", D3DCOLOR_ARGB(255, 245, 240, 218));
			AddString(1, "");
			break;
		case ITEMID_UnionCore:
			AddString( 0, "Teletransporta a un jugador", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			if( cItemWrapper.sItem.szItemName[ lstrlenA( cItemWrapper.sItem.szItemName ) + 1 ] != 0 )
			{
				AddString( 0, FormatString( "%s", cItemWrapper.sItem.szItemName + lstrlenA( cItemWrapper.sItem.szItemName ) + 1 ), D3DCOLOR_ARGB( 255, 110, 165, 250 ) );
				AddString( 1, "" );
			}
			break;
		case ITEMID_MightPotionFighter:
			AddString( 0, "5% aumento de da\361o\ncontra Fighter\n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "Duraci\363n: 60 segundos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_MightPotionMechanician:
			AddString( 0, "5% aumento de da\361o\ncontra Mechanician\n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "Duraci\363n: 60 segundos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_MightPotionPikeman:
			AddString( 0, "5% aumento de da\361o\ncontra Pikeman\n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "Duraci\363n: 60 segundos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_MightPotionArcher:
			AddString( 0, "5% aumento de da\361o\ncontra Archer\n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "Duraci\363n: 60 segundos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_MightPotionKnight:
			AddString( 0, "5% aumento de da\361o\ncontra Knight\n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "Duraci\363n: 60 segundos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_MightPotionAtalanta:
			AddString( 0, "5% aumento de da\361o\ncontra Atalanta\n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "Duraci\363n: 60 segundos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_MightPotionMagician:
			AddString( 0, "5% aumento de da\361o\ncontra Magician\n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "Duraci\363n: 60 segundos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_MightPotionPriestess:
			AddString( 0, "5% aumento de da\361o\ncontra Priestess\n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "Duraci\363n: 60 segundos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_DeadlyEdge:
			AddString( 0, "A\361ade +5% tasa cr\355tica\nen zonas PvP", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "Duraci\363n: 60 segundos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_AvailOfEvade:
			AddString( 0, "A\361ade +5% tasa de evasi\363n\nen zonas PvP", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "Duraci\363n: 60 segundos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_BolsterRecovery:
			AddString( 0, "Recuperaci\363n HP/MP/SP\npara el grupo", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_Restoration:
			AddString( 0, "Pergamino de resurrecci\363n", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_DefianceStoneFire:
			AddString( 0, "Reduce da\361o en 50%\nde la Torre Cristal de Fuego", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "Duraci\363n: 60 segundos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "Atributo Fuego", D3DCOLOR_ARGB( 255, 255, 0, 0 ) );
			AddString( 1, "" );
			break;
		case ITEMID_DefianceStoneIce:
			AddString( 0, "Reduce da\361o en 50%\nde la Torre Cristal de Hielo", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "Duraci\363n: 60 segundos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "Atributo Hielo", D3DCOLOR_ARGB( 255, 255, 0, 0 ) );
			AddString( 1, "" );
			break;
		case ITEMID_DefianceStoneLight:
			AddString( 0, "Reduce da\361o en 50%\nde la Torre Cristal de Rayo", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "Duraci\363n: 60 segundos", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );

			AddString( 0, "Atributo Luz", D3DCOLOR_ARGB( 255, 255, 0, 0 ) );
			AddString( 1, "" );
			break;
		case ITEMID_GoldenLockedChest:
			AddString( 0, "\241\301brelo para obtener una\nexcelente recompensa!", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_SilverLockedChest:
			AddString( 0, "\241\301brelo para obtener una\nexcelente recompensa!", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_BlueLockedChest:
			AddString( 0, "\241\301brelo para obtener una\nexcelente recompensa!", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_PurpleLockedChest:
			AddString( 0, "\241\301brelo para obtener una\nexcelente recompensa!", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_ChestKey:
			AddString( 0, "Usa esta llave para abrir\nun cofre bloqueado.", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
		case ITEMID_GlamorousAttireGlaze:
			AddString( 0, "Clic derecho y apunta a una armadura\no t\372nica para convertirla en apariencia", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, "" );
			break;
        case ITEMID_GlamorousArmamentVarnish:
            AddString( 0, "Clic derecho y apunta a un arma\no escudo para convertirlo en apariencia", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
            AddString( 1, "" );
            break;
        case ITEMID_SecretRecipe:
            AddString( 0, "\241Fabrica esta receta con 3 Bellums\npara obtener una recompensa secreta!", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
            AddString( 1, "" );
            break;
		case ITEMID_LucidyForce:
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", 2 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d%%", 0 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Duraci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%ds", 500 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			break;
		case ITEMID_SerenoForce:
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", 4 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d%%", 0 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Duraci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%ds", 500 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			break;
		case ITEMID_FadeoForce:
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", 7 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d%%", 0 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Duraci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%ds", 500 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			break;
		case ITEMID_SparkyForce:
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", 10 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d%%", 0 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Duraci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%ds", 500 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			break;
		case ITEMID_RaidentForce:
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", 15 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d%%", 0 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Duraci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%ds", 700 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			break;
		case ITEMID_TransparoForce:
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", 25 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d%%", 0 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Duraci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%ds", 900 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			break;
		case ITEMID_MurkyForce:
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", 40 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d%%", 10 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Duraci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%ds", 1800 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			break;
		case ITEMID_DevineForce:
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", 60 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d%%", 10 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Duraci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%ds", 2400 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			break;
		case ITEMID_CelestoForce:
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", 80 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d%%", 10 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Duraci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%ds", 3600 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			break;
		case ITEMID_MirageForce:
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", 100 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d%%", 10 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Duraci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%ds", 4800 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			break;
		case ITEMID_InfernaForce:
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", 120 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d%%", 10 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Duraci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%ds", 6000 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			break;
		case ITEMID_EnigmaForce:
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", 140 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d%%", 10 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Duraci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%ds", 7200 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			break;
		case ITEMID_BellumForce:
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", 160 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d%%", 10 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Duraci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%ds", 8400 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			break;
		case ITEMID_OredoForce:
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", 180 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d%%", 10 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Duraci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%ds", 9600 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			break;
		case ITEMID_SapphireForce:
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", 200 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Poder de ataque adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d%%", 10 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			AddString( 0, "Duraci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%ds", 10800 ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
			break;
		case ITEMID_SolForce:
			AddString(0, "Poder de ataque adicional:", D3DCOLOR_ARGB(255, 245, 240, 218));
			AddString(1, FormatString("%d", 220), D3DCOLOR_ARGB(255, 240, 215, 150));
			AddString(0, "Poder de ataque adicional:", D3DCOLOR_ARGB(255, 245, 240, 218));
			AddString(1, FormatString("%d%%", 10), D3DCOLOR_ARGB(255, 240, 215, 150));
			AddString(0, "Duraci\363n:", D3DCOLOR_ARGB(255, 245, 240, 218));
			AddString(1, FormatString("%ds", 12000), D3DCOLOR_ARGB(255, 240, 215, 150));
			break;
		//case ITEMID_SoccerShirt:
		//	AddString( 0, "No funciona con disfraces", D3DCOLOR_ARGB( 255, 255, 0, 0 ) );
		//	AddString( 1, "" );
		//	
		//	AddString( 0, " " );
		//	AddString( 1, " " );
		//	break;


	}

	return TRUE;
}

DWORD ItemInfoBox::GetItemPlayTime( Item * psItem )
{
	DWORD dwTime = 0;
	switch ( psItem->sItemID.ToItemID() )
	{
		case ITEMID_BroyaleCostumeMale:
		case ITEMID_BroyaleCostumeFemale:
		case ITEMID_NewArmorHelmet:
			dwTime = (60 * 60 * 24 * 15);
			break;

		case ITEMID_GreenCrystalRune:
		case ITEMID_RedCrystalRune:
		case ITEMID_BlueCrystalRune:
		case ITEMID_GoldCrystalRune:
		case ITEMID_SilverCrystalRune:
		case ITEMID_BronzeCrystalRune:
		case ITEMID_PinguMountMysterious:
			dwTime = (60 * 60 * 24 * 30);
			break;

			// 7 Days
		// Beginner Set
		//case ITEMID_BeginnerAxe:
		//case ITEMID_BeginnerClaw:
		//case ITEMID_BeginnerHammer:
		//case ITEMID_BeginnerStaff:
		//case ITEMID_BeginnerSword:
		//case ITEMID_BeginnerJavelin:
		//case ITEMID_BeginnerScythe:
		//case ITEMID_BeginnerBow:
		//case ITEMID_BeginnerBoots:
		//case ITEMID_BeginnerBracelet:
		//case ITEMID_BeginnerDagger:
		//case ITEMID_BeginnerPhantom:
		//case ITEMID_BeginnerGauntlet:
		//case ITEMID_GrumpyArmor:
		//case ITEMID_GrumpyRobe:

		//Xmas
		case ITEMID_XMasElegantCostumeM:
		case ITEMID_XMasElegantCostumeF:
		case ITEMID_XMasCloatCostumeTM:
		case ITEMID_XMasCloatCostumeTF:
		case ITEMID_XMasCloatCostumeMM:
		case ITEMID_XMasCloatCostumeMF:
		
		//Halloween
		case ITEMID_VampireSuit:
		case ITEMID_Succubus:
		case ITEMID_HalloweenAxe:
		case ITEMID_HalloweenClaw:
		case ITEMID_HalloweenDagger:
		case ITEMID_HalloweenHammer:
		case ITEMID_HalloweenStaff:
		case ITEMID_HalloweenWand:
		case ITEMID_HalloweenPhantom:
		case ITEMID_HalloweenScythe:
		case ITEMID_HalloweenBow:
		case ITEMID_HalloweenSword:
		case ITEMID_HalloweenBladeSword:
		case ITEMID_HalloweenJavelin:
		case ITEMID_HalloweenShield:

		//Easter
//		case ITEMID_HopyCostumeTime:
//		case ITEMID_CuepyCostumeTime:

		case ITEMID_XmasCostumeOldAxe:
		case ITEMID_XmasCostumeOldAxe1Hand:
		case ITEMID_XmasCostumeOldClaw:
		case ITEMID_XmasCostumeOldDagger:
		case ITEMID_XmasCostumeOldHammer:
		case ITEMID_XmasCostumeOldStaff:
		case ITEMID_XmasCostumeOldPhantom:
		case ITEMID_XmasCostumeOldScythe:
		case ITEMID_XmasCostumeOldBow:
		case ITEMID_XmasCostumeOldSword:
		case ITEMID_XmasCostumeOldSword1Hand:
		case ITEMID_XmasCostumeOldJavelin:

		case ITEMID_CandyAxe:	
		case ITEMID_CandyAxe1Hand:
		case ITEMID_CandyClaw:
		case ITEMID_CandyDagger:		
		case ITEMID_CandyHammer:	
		case ITEMID_CandyStaff:	
		case ITEMID_CandyWand:	
		case ITEMID_CandyPhantom:		
		case ITEMID_CandyScythe:	
		case ITEMID_CandyBow:		
		case ITEMID_CandySword:		
		case ITEMID_CandySword1Hand:
		case ITEMID_CandyJavelin:	
		case ITEMID_CandyShield:	
		case ITEMID_CandySheltom:
		case ITEMID_CeruleanRing:
		case ITEMID_IceCostumeMale:
		case ITEMID_IceCostumeFemale:
		case ITEMID_GoldenHopyCostumeMaleTime:
		case ITEMID_GoldenHopyCostumeFemaleTime:
		case ITEMID_IceRecipe:
		case ITEMID_MysteriousBookRecipe:
		case ITEMID_HopyRune:
		case ITEMID_CuepyRune:
		case ITEMID_GoldenHopyRune:
			dwTime = (60 * 60 * 24 * 7);
			break;

		case ITEMID_HopyCostumeTime:
		case ITEMID_CuepyCostumeTime:
		case ITEMID_HopyCostumeIce:
		case ITEMID_CuepyCostumeIce:
		case ITEMID_ChemistCostumeMale:
		case ITEMID_ChemistCostumeFemale:
		case ITEMID_SandurrRedCostumeMale:
		case ITEMID_SandurrRedCostumeFemale:
			dwTime = (60 * 60 * 24);
			break;

		case ITEMID_GoldenLockedChest:
		case ITEMID_SilverLockedChest:
		case ITEMID_BlueLockedChest:
		case ITEMID_PurpleLockedChest:
		case ITEMID_ChestKey:
		case ITEMID_KingStone:
			dwTime = (60 * 60);
			break;

		default:
			break;
	}

	if ( (dwTime == 0) && psItem->bLockedItemType )
	{
		switch ( psItem->bLockedItemType )
		{
			case ITEMLOCKEDTYPE_1Hour:
				dwTime = (60 * 60);
				break;
			case ITEMLOCKEDTYPE_30Days:
				dwTime = (60 * 60 * 24 * 30);
				break;

			default:
				break;
		}

		if ( dwTime )
		{
			if ( PLAYTIME > (psItem->tTime + dwTime) )
			{
				if ( psItem->bLockedItemType != ITEMLOCKEDTYPE_None )
				{
					psItem->bLockedItemType = ITEMLOCKEDTYPE_None;

					dwTime = 0;
				}
			}
		}
	}

	return dwTime;
}

BOOL ItemInfoBox::IsExpiredItemTime( Item * psItemInfo )
{
	DWORD dwTime = ItemInfoBox::GetItemPlayTime( psItemInfo );
	
	if ( dwTime && psItemInfo->szItemName[0] != 0 )
	{
		if ( psItemInfo->bLockedItemType )
		{
			if ( PLAYTIME > (psItemInfo->tTime + dwTime) )
				psItemInfo->bLockedItemType = ITEMLOCKEDTYPE_None;

			return FALSE;
		}

		if ( PLAYTIME > (psItemInfo->tTime + dwTime) )
			return TRUE;
	}
	
	return FALSE;
}

BOOL ItemInfoBox::FormatItemTimeInfo( ItemData * pcItemData )
{
	DWORD dwTime		= 0;
	DWORD dwItemTime	= pcItemData->sItem.tTime;
	BOOL bResult		= FALSE;

	DWORD dwTotalTime = ItemInfoBox::GetItemPlayTime( &pcItemData->sItem );

	if ( dwTotalTime )
	{
		if ( ItemInfoBox::IsExpiredItemTime( &pcItemData->sItem ) )
		{
			AddString( 0, "" );
			AddString( 1, "" );
			AddString( 0, std::string( AY_OBFUSCATE( "\315tem expirado" ) ), D3DCOLOR_ARGB( 255, 125, 180, 175 ) );
			AddString( 1, "\n " );
		}
		else
		{
			AddString( 0, "" );
			AddString( 1, "" );
			dwTime = dwTotalTime - (PLAYTIME - dwItemTime);

			if ( pcItemData->sItem.bLockedItemType )
				AddString( 0, FormatString( AY_OBFUSCATE( "Tiempo para desbloquear: %02d:%02d:%02d" ), dwTime / 3600, (dwTime / 60) % 60, dwTime % 60 ), D3DCOLOR_ARGB( 255, 125, 180, 175 ) );
			else	
				AddString( 0, FormatString( AY_OBFUSCATE( "Tiempo restante: %02d:%02d:%02d" ), dwTime / 3600, (dwTime / 60) % 60, dwTime % 60 ), D3DCOLOR_ARGB( 255, 125, 180, 175 ) );

			AddString( 1, "\n " );
		}
		bResult = TRUE;
	}

	if ( pcItemData->sItem.bLockedItemType == 50 )
	{
		AddString( 0, "" );
		AddString( 1, "" );
		AddString( 0, std::string( AY_OBFUSCATE( "\315tem bloqueado" ) ), D3DCOLOR_ARGB( 255, 125, 180, 175 ) );
		AddString( 1, "\n " );
		bResult = TRUE;
	}

	return bResult;
}

BOOL ItemInfoBox::PrepareShowItem( ItemData * pcItemData, BOOL bShowBuyPrice, BOOL bShowSellPrice, BOOL bShowChecksums )
{
	//Clear Vectors
	vLeftText.clear();
	vRightText.clear();
	vCompareText.clear();
	vRowCompare.clear();
	iSocketCount = 0;
	bIsPerfectItem = FALSE;
	bCantUseItem = FALSE;
	bDisplayHelp = FALSE;
	bHasLargeName = FALSE;
	iSpecLine = 0;
	iStatLine = 0;
	cBackgroundColor1 = UI::Color( 235, 45, 39, 27 );

	// Item Data Copy
	{
		if ( pcItemData->iItemSlotFlag == ITEMSLOTFLAG_LeftRightHand && pcItemData->iItemSlot && !pcItemData->sItem.bCostumeItem )
		{
			CopyMemory( (void*)pdwItemInfoData, &INVENTORYITEMS[INVENTORYITEMSLOT[0].iItemIndex - 1].sItem, sizeof( Item ) );
			CopyMemory( &cItemWrapper, &INVENTORYITEMS[INVENTORYITEMSLOT[0].iItemIndex - 1], sizeof( ItemData ) );

			cItemWrapper.sPosition = pcItemData->sPosition;
		}
		else
		{
			CopyMemory( (void*)pdwItemInfoData, &pcItemData->sItem, sizeof( Item ) );
			CopyMemory( &cItemWrapper, pcItemData, sizeof( ItemData ) );
		}
	}

	//Copy psItem to cItemWrapper
	CopyMemory( &cItemWrapper.sItem, (void*)pdwItemInfoData, sizeof( Item ) );
	const EItemType eItemType = cItemWrapper.sBaseItemID.ToItemType();
	bDisplayHelp = IsRaritySkinnedEquipment( eItemType );
	bHasLargeName = IsRaritySkinnedEquipment( eItemType );

	BOOL bBeginner = IsBeginnerSet( &cItemWrapper );

	bCantUseItem = cItemWrapper.sItem.bCanNotUse;

	//Ítem perfecto
	if( cItemWrapper.sItem.bPerfectItem )
		bIsPerfectItem = TRUE;
	if( PERFECTVIEWHANDLER->IsSet() )
		bIsPerfectItem = TRUE;

	//Name Item
	if ( cItemWrapper.sBaseItemID.ToItemID() == ITEMID_SoulSummonCrystal )
	{
		AddString( 0, "Cristal de alma", -1, TRUE );
		AddString( 1, "" );
	}
	else
	{
		AddString( 0, cItemWrapper.sItem.szItemName, -1, TRUE );
		AddString( 1, "" );
	}

	//Color Name Item
	if( cItemWrapper.sItem.iItemUniqueID )
	{
		//Unique Color
		SetLineColor( D3DCOLOR_ARGB( 255, 128, 255, 128 ) );
	}
	else
	{
		//Default Color
		SetLineColor( D3DCOLOR_ARGB( 255, 222, 231, 255 ) );

		if ( bBeginner )
			SetLineColor( D3DCOLOR_ARGB( 255, 0, 222, 52 ) );

		//Set Special Colors
		if( cItemWrapper.sItem.eCraftType )
		{
			switch( cItemWrapper.sItem.eCraftType )
			{
				case ITEMCRAFTTYPE_Mixing:
					SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255) );
					break;
				case ITEMCRAFTTYPE_Aging:
					SetLineColor( D3DCOLOR_ARGB( 255, 100, 230, 255 ) );
					break;
				case ITEMCRAFTTYPE_QuestWeapon:
					SetLineColor( D3DCOLOR_ARGB( 255, 132, 50, 254 ) );
					break;
			}
		}
	}

	//Make Description Item
	FormatItemInfo( &cItemWrapper );

	//Aging Bar
	if( cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging )
	{
		AddString( 0, "\n " );
		AddString( 1, "\n " );
	}

	//Quest Item
	if( cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_QuestWeapon && cItemWrapper.sItem.sAgeLevel < 4 )
	{
		AddString( 0, "" );
		AddString( 1, "" );

		AddString( 0, FormatString( "%s:\n%d/%d", pszaQuestMonsterName[ cItemWrapper.sItem.bMaturing ], cItemWrapper.sItem.sMatureBar.sMax - cItemWrapper.sItem.sMatureBar.sCur, cItemWrapper.sItem.sMatureBar.sMax ), D3DCOLOR_ARGB( 255, 125, 180, 175 ) );
		AddString( 1, "\n " );

		AddString( 0, "" );
		AddString( 1, "" );
	}

	//Respec Stone Level Range
	RespecStone * psList = ( RespecStone* )0x0099A0A8;

	for( int i = 0; i < 4; i++ )
	{
		EItemID eItemID = cItemWrapper.sBaseItemID.ToItemID();
		if( psList[ i ].eItemID == eItemID )
		{
			AddString( 0, "Nivel req.:" );
			AddString( 1, FormatString( "%d-%d", psList[i].iMinLevel, psList[i].iMaxLevel ) );
			break;
		}
	}

	//Attack Power
	const int iDisplayedDamageMin = GetDisplayedRarityWeaponDamageMin( &cItemWrapper.sItem );
	const int iDisplayedDamageMax = GetDisplayedRarityWeaponDamageMax( &cItemWrapper.sItem );
	if( iDisplayedDamageMin || iDisplayedDamageMax )
	{
		AddString( 0, "Poder de ataque:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d-%d", iDisplayedDamageMin, iDisplayedDamageMax ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Mix Color
		if( ( cItemWrapper.sItem.eMixEffect & MIXEFFECT_MinAttackPower ) || ( cItemWrapper.sItem.eMixEffect & MIXEFFECT_MaxAttackPower ) )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

		//Aging Color
		if( ( cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging ) && ( cItemWrapper.sBaseItemID.ToItemBase() == ITEMBASE_Weapon ) )
			SetLineColor( D3DCOLOR_ARGB( 255, 100, 230, 255 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = iDisplayedDamageMin - GetDisplayedRarityWeaponDamageMin( &cItemCompare.sItem );
			int iCalcMax = iDisplayedDamageMax - GetDisplayedRarityWeaponDamageMax( &cItemCompare.sItem );
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 || iCalcMax != 0 )
				AddCompareString( FormatString( "(%s%d-%d)", iCalc > 0 ? "+" : "", iCalc, iCalcMax ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Attack fMovementSpeed
	if( cItemWrapper.sItem.iAttackSpeed )
	{
		AddString( 0, "Vel. de ataque:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d", cItemWrapper.sItem.iAttackSpeed ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Mix Color
		if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_WeaponSpeed )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.iAttackSpeed - cItemCompare.sItem.iAttackSpeed;
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}

	}

	//Range
	if( cItemWrapper.sItem.iAttackRange )
	{
		AddString( 0, "Alcance:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d", cItemWrapper.sItem.iAttackRange ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.iAttackRange - cItemCompare.sItem.iAttackRange;
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Critical
	const int iDisplayedCritical = GetDisplayedRarityWeaponCritical( &cItemWrapper.sItem );
	if( iDisplayedCritical )
	{
		AddString( 0, "Tasa cr\355tica:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d%%", iDisplayedCritical ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Mix Color
		if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_Critical )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

		//Aging Color
		if( ( cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging ) && ( cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Claw || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Scythe || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Dagger || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Hammer ||
			cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Bow || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Javelin || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Sword || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Wand || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Phantom ) )
			SetLineColor( D3DCOLOR_ARGB( 255, 100, 230, 255 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = iDisplayedCritical - GetDisplayedRarityWeaponCritical( &cItemCompare.sItem );
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Defense
	const int iDisplayedDefense = GetDisplayedRarityDefense( &cItemWrapper.sItem );
	if( iDisplayedDefense )
	{
		AddString( 0, "Defensa:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d", iDisplayedDefense ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Mix Color
		if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_DefenseRating )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

		//Aging Color
		if( ( cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging ) && ( cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Orb || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Armor || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Robe ||
			cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Boots || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Gauntlets || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Bracelets || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Shield ) )
			SetLineColor( D3DCOLOR_ARGB( 255, 100, 230, 255 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = iDisplayedDefense - GetDisplayedRarityDefense( &cItemCompare.sItem );
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Attack Rating
	const int iDisplayedAttackRating = GetDisplayedRarityWeaponAttackRating( &cItemWrapper.sItem );
	if( iDisplayedAttackRating )
	{
		AddString( 0, "Tasa de ataque:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d", iDisplayedAttackRating ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Mix Color
		if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_AttackRating )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

		//Aging Color
		if( ( cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging ) && ( cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Axe || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Claw || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Wand ||
			cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Hammer || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Scythe || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Sword || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Bracelets ||
			cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Phantom || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Dagger ) )
			SetLineColor( D3DCOLOR_ARGB( 255, 100, 230, 255 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = iDisplayedAttackRating - GetDisplayedRarityWeaponAttackRating( &cItemCompare.sItem );
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );
			
			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Absorption
	const float fDisplayedAbsorb = GetDisplayedRarityAbsorb( &cItemWrapper.sItem );
	if( fDisplayedAbsorb )
	{
		AddString( 0, "Absorci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%.1f", fDisplayedAbsorb ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Mix Color
		if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_AbsorbRating )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

		//Aging Color
		if( ( cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging ) && ( cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Orb || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Armor || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Robe ||
			cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Shield || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Gauntlets || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Boots ) )
			SetLineColor( D3DCOLOR_ARGB( 255, 100, 230, 255 ), 1 );
	
		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			float fCalc = fDisplayedAbsorb - GetDisplayedRarityAbsorb( &cItemCompare.sItem );
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( fCalc != 0 )
				AddCompareString( FormatString( "(%s%.1f)", fCalc > 0 ? "+" : "", fCalc ), fCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Block
	const float fDisplayedBlock = GetDisplayedRarityBlock( &cItemWrapper.sItem );
	if( fDisplayedBlock )
	{
		AddString( 0, "Bloqueo:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );

		if( fabs( fDisplayedBlock - round( fDisplayedBlock ) ) < FLT_MIN )
			AddString( 1, FormatString( "%.0f%%", round( fDisplayedBlock ) ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
		else
			AddString( 1, FormatString( "%.1f%%", fDisplayedBlock ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Mix Color
		if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_Block )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

		//Aging Color
		if( ( cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging ) && ( cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Shield ) )
			SetLineColor( D3DCOLOR_ARGB( 255, 100, 230, 255 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			float fCalc = fDisplayedBlock - GetDisplayedRarityBlock( &cItemCompare.sItem );
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( fCalc != 0 )
				AddCompareString( FormatString( "(%s%.1f%%)", fCalc > 0 ? "+" : "", fCalc ), fCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Evade
	if ( cItemWrapper.sItem.bEvade )
	{
		AddString( 0, "Evasi\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d%%", (int)cItemWrapper.sItem.bEvade ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Compare Item
		if ( bCompareItem && bIsEquippedItem )
		{
			int iCalc = (int)(cItemWrapper.sItem.bEvade - cItemCompare.sItem.bEvade);
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if ( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d%%)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}


	//Movement Speed
	if ( cItemWrapper.sItem.fMovementSpeed )
	{
		AddString( 0, "Velocidad:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%.1f", cItemWrapper.sItem.fMovementSpeed ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Mix Color
		if ( cItemWrapper.sItem.eMixEffect & MIXEFFECT_WalkSpeed )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255 ), 1 );

		//Compare Item
		if ( bCompareItem && bIsEquippedItem )
		{
			float fCalc = cItemWrapper.sItem.fMovementSpeed - cItemCompare.sItem.fMovementSpeed;
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if ( fCalc != 0 )
				AddCompareString( FormatString( "(%s%.1f)", fCalc > 0 ? "+" : "", fCalc ), fCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Integrity
	if( cItemWrapper.sItem.sIntegrity.sCur || cItemWrapper.sItem.sIntegrity.sMax )
	{
		AddString( 0, "Integridad:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d/%d", cItemWrapper.sItem.sIntegrity.sCur, cItemWrapper.sItem.sIntegrity.sMax ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Aging Color
		if( cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging )
			SetLineColor( D3DCOLOR_ARGB( 255, 100, 230, 255 ), 1 );

		//Zero Integrity
		if ( cItemWrapper.sItem.sIntegrity.sCur == 0 )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 140, 0 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.sIntegrity.sCur - cItemCompare.sItem.sIntegrity.sCur;
			int iCalcMax = cItemWrapper.sItem.sIntegrity.sMax - cItemCompare.sItem.sIntegrity.sMax;
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d/%d)", iCalc > 0 ? "+" : "", iCalc, iCalcMax ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Mana
	if( cItemWrapper.sItem.sMPRecovery.sMin || cItemWrapper.sItem.sMPRecovery.sMax )
	{
		AddString( 0, "Recuperaci\363n MP:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d-%d", cItemWrapper.sItem.sMPRecovery.sMin, cItemWrapper.sItem.sMPRecovery.sMax ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
	
		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.sMPRecovery.sMin - cItemCompare.sItem.sMPRecovery.sMin;
			int iCalcMax = cItemWrapper.sItem.sMPRecovery.sMax - cItemCompare.sItem.sMPRecovery.sMax;
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d-%d)", iCalc > 0 ? "+" : "", iCalc, iCalcMax ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//HP
	if( cItemWrapper.sItem.sHPRecovery.sMin || cItemWrapper.sItem.sHPRecovery.sMax )
	{
		AddString( 0, "Recuperaci\363n HP:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d-%d", cItemWrapper.sItem.sHPRecovery.sMin, cItemWrapper.sItem.sHPRecovery.sMax ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
	
		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.sHPRecovery.sMin - cItemCompare.sItem.sHPRecovery.sMin;
			int iCalcMax = cItemWrapper.sItem.sHPRecovery.sMax - cItemCompare.sItem.sHPRecovery.sMax;
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d-%d)", iCalc > 0 ? "+" : "", iCalc, iCalcMax ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//STM
	if( cItemWrapper.sItem.sSPRecovery.sMin || cItemWrapper.sItem.sSPRecovery.sMax )
	{
		AddString( 0, "Recuperaci\363n STM:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d-%d", cItemWrapper.sItem.sSPRecovery.sMin, cItemWrapper.sItem.sSPRecovery.sMax ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );
	
		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.sSPRecovery.sMin - cItemCompare.sItem.sSPRecovery.sMin;
			int iCalcMax = cItemWrapper.sItem.sSPRecovery.sMax - cItemCompare.sItem.sSPRecovery.sMax;
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d-%d)", iCalc > 0 ? "+" : "", iCalc, iCalcMax ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Resistances
	{
		if( cItemWrapper.sItem.saElementalDef[0] )
		{
			AddString( 0, "Org\341nico:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", cItemWrapper.sItem.saElementalDef[0] ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

			//Mix Color
			if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_Organic )
				SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

			//Compare Item
			if( bCompareItem && bIsEquippedItem )
			{
				int iCalc = cItemWrapper.sItem.saElementalDef[0] - cItemCompare.sItem.saElementalDef[0];
				SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

				if( iCalc != 0 )
					AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
			}
		}

		if( cItemWrapper.sItem.saElementalDef[2] )
		{
			AddString( 0, "Fuego:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", cItemWrapper.sItem.saElementalDef[2] ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

			//Mix Color
			if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_Flame )
				SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

			//Compare Item
			if( bCompareItem && bIsEquippedItem )
			{
				int iCalc = cItemWrapper.sItem.saElementalDef[ 2 ] - cItemCompare.sItem.saElementalDef[ 2 ];
				SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

				if( iCalc != 0 )
					AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
			}
		}

		if( cItemWrapper.sItem.saElementalDef[3] )
		{
			AddString( 0, "Hielo:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", cItemWrapper.sItem.saElementalDef[3] ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

			//Mix Color
			if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_Frost )
				SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

			//Compare Item
			if( bCompareItem && bIsEquippedItem )
			{
				int iCalc = cItemWrapper.sItem.saElementalDef[ 3 ] - cItemCompare.sItem.saElementalDef[ 3 ];
				SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

				if( iCalc != 0 )
					AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
			}
		}

		if( cItemWrapper.sItem.saElementalDef[4] )
		{
			AddString( 0, "Rayo:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", cItemWrapper.sItem.saElementalDef[4] ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

			//Mix Color
			if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_Light )
				SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

			//Compare Item
			if( bCompareItem && bIsEquippedItem )
			{
				int iCalc = cItemWrapper.sItem.saElementalDef[ 4 ] - cItemCompare.sItem.saElementalDef[ 4 ];
				SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

				if( iCalc != 0 )
					AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
			}
		}

		if( cItemWrapper.sItem.saElementalDef[5] )
		{
			AddString( 0, "Veneno:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", cItemWrapper.sItem.saElementalDef[5] ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

			//Mix Color
			if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_Poison )
				SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

			//Compare Item
			if( bCompareItem && bIsEquippedItem )
			{
				int iCalc = cItemWrapper.sItem.saElementalDef[ 5 ] - cItemCompare.sItem.saElementalDef[ 5 ];
				SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

				if( iCalc != 0 )
					AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
			}
		}
	}

	//HP Regen
	if( cItemWrapper.sItem.fHPRegen && cItemWrapper.sBaseItemID.ToItemType() != ITEMTYPE_ForceOrb )
	{
		AddString( 0, "Reg. HP:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%.1f", cItemWrapper.sItem.fHPRegen ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Mix Color
		if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_HPRegen )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			float fCalc = cItemWrapper.sItem.fHPRegen - cItemCompare.sItem.fHPRegen;
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( fCalc != 0 )
				AddCompareString( FormatString( "(%s%.1f)", fCalc > 0 ? "+" : "", fCalc ), fCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//MP Regen
	if( cItemWrapper.sItem.fMPRegen && cItemWrapper.sBaseItemID.ToItemType() != ITEMTYPE_ForceOrb )
	{
		AddString( 0, "Reg. MP:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%.1f", cItemWrapper.sItem.fMPRegen ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Mix Color
		if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_MPRegen )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			float fCalc = cItemWrapper.sItem.fMPRegen - cItemCompare.sItem.fMPRegen;
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( fCalc != 0 )
				AddCompareString( FormatString( "(%s%.1f)", fCalc > 0 ? "+" : "", fCalc ), fCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//STM Regen
	if( cItemWrapper.sItem.fSPRegen && cItemWrapper.sBaseItemID.ToItemType() != ITEMTYPE_ForceOrb )
	{
		AddString( 0, "Reg. STM:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%.1f", cItemWrapper.sItem.fSPRegen ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Mix Color
		if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_SPRegen )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			float fCalc = cItemWrapper.sItem.fSPRegen - cItemCompare.sItem.fSPRegen;
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( fCalc != 0 )
				AddCompareString( FormatString( "(%s%.1f)", fCalc > 0 ? "+" : "", fCalc ), fCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Add HP
	const float fDisplayedAddHP = GetDisplayedRarityAddHP( &cItemWrapper.sItem );
	if( fDisplayedAddHP )
	{
		AddString( 0, "HP adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%.0f", fDisplayedAddHP ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Mix Color
		if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_HP )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			float fCalc = fDisplayedAddHP - GetDisplayedRarityAddHP( &cItemCompare.sItem );
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( fCalc != 0 )
				AddCompareString( FormatString( "(%s%.0f)", fCalc > 0 ? "+" : "", fCalc ), fCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Add MP
	const float fDisplayedAddMP = GetDisplayedRarityAddMP( &cItemWrapper.sItem );
	if( fDisplayedAddMP )
	{
		AddString( 0, "MP adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%.0f", fDisplayedAddMP ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Mix Color
		if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_MP )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

		//Aging Color
		if( ( cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging ) && ( cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Wand || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Phantom || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Bow || cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Javelin ) )
			SetLineColor( D3DCOLOR_ARGB( 255, 100, 230, 255 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			float fCalc = fDisplayedAddMP - GetDisplayedRarityAddMP( &cItemCompare.sItem );
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( fCalc != 0 )
				AddCompareString( FormatString( "(%s%.0f)", fCalc > 0 ? "+" : "", fCalc ), fCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Add STM
	const float fDisplayedAddSP = GetDisplayedRarityAddSP( &cItemWrapper.sItem );
	if( fDisplayedAddSP )
	{
		AddString( 0, "STM adicional:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%.0f", fDisplayedAddSP ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Mix Color
		if( cItemWrapper.sItem.eMixEffect & MIXEFFECT_SP )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			float fCalc = fDisplayedAddSP - GetDisplayedRarityAddSP( &cItemCompare.sItem );
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( fCalc != 0 )
				AddCompareString( FormatString( "(%s%.0f)", fCalc > 0 ? "+" : "", fCalc ), fCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Potion Storage
	const int iDisplayedPotionStorage = GetDisplayedRarityPotionStorage( &cItemWrapper.sItem );
	if( iDisplayedPotionStorage )
	{
		AddString( 0, "Cant. pociones:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d", iDisplayedPotionStorage ), D3DCOLOR_ARGB( 255, 240, 215, 150 ) );

		//Mix Color
		if ( cItemWrapper.sItem.eMixEffect & MIXEFFECT_PotionCount )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 110, 255 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = iDisplayedPotionStorage - GetDisplayedRarityPotionStorage( &cItemCompare.sItem );
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Attribute
	if ( auto pcItemAttributeInstance = ITEMSETATTRIBUTEHANDLER->GetAttributes( &cItemWrapper.sItem, TRUE ) )
	{
		auto pcAttribute = pcItemAttributeInstance->GetItemAttribute();

		BOOL bEquipped = FALSE;

		AddString( 0, "\n" );
		AddString( 1, "\n" );

		AddString( 0, pcAttribute->GetName(), D3DCOLOR_XRGB( 208, 32, 144 ) );
		AddString( 1, "\n" );

		AddString( 0, "\n" );
		AddString( 1, "\n" );

		for ( auto & psItem : pcAttribute->GetItems() )
		{
			CItemAttributeInstance::ItemDataEquipped * psItemEquipped = NULL;

			for ( auto & pcItem : pcItemAttributeInstance->GetEquippedItems() )
			{
				if ( pcItem->psItem == psItem )
				{
					psItemEquipped = pcItem;
					break;
				}
			}

			int iItemCount = 0;

			DWORD dwColor = D3DCOLOR_XRGB( 110, 110, 110 );

			if ( psItemEquipped )
			{
				iItemCount = psItemEquipped->iCount;
				if ( iItemCount > psItemEquipped->psItem->iCount )
					iItemCount = psItemEquipped->psItem->iCount;

				dwColor = D3DCOLOR_XRGB( 208, 32, 144 );
			}

			if ( psItem->iCount > 1 )
				AddString( 0, FormatString( "%s (%d/%d)", pcAttribute->GetTextItem( psItem->iTextID )->strText.c_str(), iItemCount, psItem->iCount ), dwColor );
			else
				AddString( 0, pcAttribute->GetTextItem( psItem->iTextID )->strText.c_str(), dwColor );

			AddString( 1, "\n" );
		}

		AddString( 0, "\n" );
		AddString( 1, "\n" );

		AddString( 0, "Efecto de set:", D3DCOLOR_XRGB( 255, 140, 0 ) );
		AddString( 1, "\n" );

		int iItemCount = pcItemAttributeInstance->GetItemCount();
		for ( auto & psText : pcAttribute->GetTextEffects() )
		{
			if ( psText->iClass == UNITDATA->sCharacterData.iClass )
			{
				AddString( 0, FormatString( "%d", psText->iItemCount ) );
				AddString( 1, psText->strText.c_str(), iItemCount >= psText->iItemCount ? D3DCOLOR_XRGB( 255, 140, 0 ) : D3DCOLOR_XRGB( 110, 110, 110 ) );

				if ( pcAttribute->IsUnique() )
					break;
			}
		}
	}

	// Time on item
	FormatItemTimeInfo( &cItemWrapper );

	// Define line before requirements
	if ( cItemWrapper.sItem.iLevel || cItemWrapper.sItem.iStrength || cItemWrapper.sItem.iSpirit || cItemWrapper.sItem.iTalent || cItemWrapper.sItem.iAgility || cItemWrapper.sItem.iHealth )
	{
		iStatLine = vLeftText.size();
		AddString( 0, " " );
		AddString( 1, " " );
	}

	//Req Level
	if( cItemWrapper.sItem.iLevel )
	{
		AddString( 0, "Nivel req.:" );
		AddString( 1, FormatString( "%d", cItemWrapper.sItem.iLevel ) );

		if( PLAYERDATA->iLevel < cItemWrapper.sItem.iLevel )
		{
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 0, 0 ) );
			bCantUseItem = TRUE;
		}
		else
			SetLineColor( D3DCOLOR_ARGB( 255, 125, 120, 100 ) );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.iLevel - cItemCompare.sItem.iLevel;
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc < 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Req Strenght
	if( cItemWrapper.sItem.iStrength )
	{
		AddString( 0, "Req. Fuerza:" );
		AddString( 1, FormatString( "%d", cItemWrapper.sItem.iStrength ) );

		if( PLAYERDATA->iStrength < cItemWrapper.sItem.iStrength )
		{
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 0, 0 ) );
			bCantUseItem = TRUE;
		}
		else
			SetLineColor( D3DCOLOR_ARGB( 255, 125, 120, 100 ) );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.iLevel - cItemCompare.sItem.iLevel;
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc < 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Req Spirit
	if( cItemWrapper.sItem.iSpirit )
	{
		AddString( 0, "Req. Esp\355ritu:" );
		AddString( 1, FormatString( "%d", cItemWrapper.sItem.iSpirit ) );

		if( PLAYERDATA->iSpirit < cItemWrapper.sItem.iSpirit )
		{
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 0, 0 ) );
			bCantUseItem = TRUE;
		}
		else
			SetLineColor( D3DCOLOR_ARGB( 255, 125, 120, 100 ) );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.iSpirit - cItemCompare.sItem.iSpirit;
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc < 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Req Talent
	if( cItemWrapper.sItem.iTalent )
	{
		AddString( 0, "Req. Talento:" );
		AddString( 1, FormatString( "%d", cItemWrapper.sItem.iTalent ) );

		if( PLAYERDATA->iTalent < cItemWrapper.sItem.iTalent )
		{
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 0, 0 ) );
			bCantUseItem = TRUE;
		}
		else
			SetLineColor( D3DCOLOR_ARGB( 255, 125, 120, 100 ) );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.iTalent - cItemCompare.sItem.iTalent;
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc < 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Req Agility
	if( cItemWrapper.sItem.iAgility )
	{
		AddString( 0, "Req. Agilidad:" );
		AddString( 1, FormatString( "%d", cItemWrapper.sItem.iAgility ) );

		if( PLAYERDATA->iAgility < cItemWrapper.sItem.iAgility )
		{
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 0, 0 ) );
			bCantUseItem = TRUE;
		}
		else
			SetLineColor( D3DCOLOR_ARGB( 255, 125, 120, 100 ) );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.iAgility - cItemCompare.sItem.iAgility;
			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc < 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Req Health
	if( cItemWrapper.sItem.iHealth )
	{
		AddString( 0, "Req. Salud:" );
		AddString( 1, FormatString( "%d", cItemWrapper.sItem.iHealth ) );

		if( PLAYERDATA->iHealth < cItemWrapper.sItem.iHealth )
		{
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 0, 0 ) );
			bCantUseItem = TRUE;
		}
		else
			SetLineColor( D3DCOLOR_ARGB( 255, 125, 120, 100 ) );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.iHealth - cItemCompare.sItem.iHealth;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc < 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec
	if( cItemWrapper.sItem.eSpecialization )
	{
		iSpecLine = vLeftText.size();
		AddString( 0, " " );
		AddString( 1, " " );

		EClassFlag e = static_cast<EClassFlag>( cItemWrapper.sItem.eSpecialization );
		AddString( 0, FormatString( "%s Esp.", GetCharacterClassByFlag( e ) ) );
		AddString( 1, "" );

		if( PLAYERDATA->iFlag == cItemWrapper.sItem.eSpecialization )
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 220, 0 ) );
		else
			SetLineColor( D3DCOLOR_ARGB( 255, 255, 0, 0 ) );
	}

	//Spec ATK fMovementSpeed
	if( cItemWrapper.sItem.sSpecData.iSpecAttackSpeed )
	{
		AddString( 0, "Vel. de ataque:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d", cItemWrapper.sItem.sSpecData.iSpecAttackSpeed ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.sSpecData.iSpecAttackSpeed - cItemCompare.sItem.sSpecData.iSpecAttackSpeed;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec Critical
	if( cItemWrapper.sItem.sSpecData.iSpecCritical )
	{
		AddString( 0, "Tasa cr\355tica:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d%%", cItemWrapper.sItem.sSpecData.iSpecCritical ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.sSpecData.iSpecCritical - cItemCompare.sItem.sSpecData.iSpecCritical;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d%%)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec Defense
	if( cItemWrapper.sItem.sSpecData.iSpecDefenseRating )
	{
		AddString( 0, "Defensa:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d", cItemWrapper.sItem.sSpecData.iSpecDefenseRating ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.sSpecData.iSpecDefenseRating - cItemCompare.sItem.sSpecData.iSpecDefenseRating;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec fAbsorbRating
	if( cItemWrapper.sItem.sSpecData.fSpecAbsorbRating )
	{
		AddString( 0, "Absorci\363n:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%.1f", cItemWrapper.sItem.sSpecData.fSpecAbsorbRating ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			float fCalc = cItemWrapper.sItem.sSpecData.fSpecAbsorbRating - cItemCompare.sItem.sSpecData.fSpecAbsorbRating;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( fCalc != 0.0f )
				AddCompareString( FormatString( "(%s%.1f)", fCalc > 0 ? "+" : "", fCalc ), fCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec Block
	if( cItemWrapper.sItem.sSpecData.fSpecBlockRating )
	{
		AddString( 0, "Bloqueo:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );

		if( fabs( cItemWrapper.sItem.sSpecData.fSpecBlockRating - round( cItemWrapper.sItem.sSpecData.fSpecBlockRating ) ) < FLT_MIN )
			AddString( 1, FormatString( "%.0f%%", round( cItemWrapper.sItem.sSpecData.fSpecBlockRating ) ) );
		else
			AddString( 1, FormatString( "%.1f%%", cItemWrapper.sItem.sSpecData.fSpecBlockRating ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			float fCalc = cItemWrapper.sItem.sSpecData.fSpecBlockRating - cItemCompare.sItem.sSpecData.fSpecBlockRating;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( fCalc != 0 )
				AddCompareString( FormatString( "(%s%.1f%%)", fCalc > 0 ? "+" : "", fCalc ), fCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec MagicAPT
	if( cItemWrapper.sItem.sSpecData.fSpecMagicMastery )
	{
		AddString( 0, "APT m\341gica:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%.0f", cItemWrapper.sItem.sSpecData.fSpecMagicMastery ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			float fCalc = cItemWrapper.sItem.sSpecData.fSpecMagicMastery - cItemCompare.sItem.sSpecData.fSpecMagicMastery;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( fCalc != 0 )
				AddCompareString( FormatString( "(%s%.0f)", fCalc > 0 ? "+" : "", fCalc ), fCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec fMovementSpeed
	if( cItemWrapper.sItem.sSpecData.fSpecMovementSpeed )
	{
		AddString( 0, "Velocidad:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%.1f", cItemWrapper.sItem.sSpecData.fSpecMovementSpeed ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			float fCalc = cItemWrapper.sItem.sSpecData.fSpecMovementSpeed - cItemCompare.sItem.sSpecData.fSpecMovementSpeed;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( fCalc != 0 )
				AddCompareString( FormatString( "(%s%.1f)", fCalc > 0 ? "+" : "", fCalc ), fCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec Resistances
	{
		if( cItemWrapper.sItem.sSpecData.saSpecElementalDef[0] )
		{
			AddString( 0, "Org\341nico:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", cItemWrapper.sItem.sSpecData.saSpecElementalDef ) );

			SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

			//Compare Item
			if( bCompareItem && bIsEquippedItem )
			{
				int iCalc = cItemWrapper.sItem.sSpecData.saSpecElementalDef[0] - cItemCompare.sItem.sSpecData.saSpecElementalDef[0];

				SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

				if( iCalc != 0 )
					AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
			}
		}

		if( cItemWrapper.sItem.sSpecData.saSpecElementalDef[2] )
		{
			AddString( 0, "Fuego:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", cItemWrapper.sItem.sSpecData.saSpecElementalDef[2] ) );

			SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

			//Compare Item
			if( bCompareItem && bIsEquippedItem )
			{
				int iCalc = cItemWrapper.sItem.sSpecData.saSpecElementalDef[2] - cItemCompare.sItem.sSpecData.saSpecElementalDef[2];

				SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

				if( iCalc != 0 )
					AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
			}
		}

		if( cItemWrapper.sItem.sSpecData.saSpecElementalDef[3] )
		{
			AddString( 0, "Hielo:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", cItemWrapper.sItem.sSpecData.saSpecElementalDef[3] ) );

			SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

			//Compare Item
			if( bCompareItem && bIsEquippedItem )
			{
				int iCalc = cItemWrapper.sItem.sSpecData.saSpecElementalDef[3] - cItemCompare.sItem.sSpecData.saSpecElementalDef[3];

				SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

				if( iCalc != 0 )
					AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
			}
		}

		if( cItemWrapper.sItem.sSpecData.saSpecElementalDef[4] )
		{
			AddString( 0, "Rayo:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", cItemWrapper.sItem.sSpecData.saSpecElementalDef[4] ) );

			SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

			//Compare Item
			if( bCompareItem && bIsEquippedItem )
			{
				int iCalc = cItemWrapper.sItem.sSpecData.saSpecElementalDef[4] - cItemCompare.sItem.sSpecData.saSpecElementalDef[4];

				SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

				if( iCalc != 0 )
					AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
			}
		}

		if( cItemWrapper.sItem.sSpecData.saSpecElementalDef[5] )
		{
			AddString( 0, "Veneno:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
			AddString( 1, FormatString( "%d", cItemWrapper.sItem.sSpecData.saSpecElementalDef[5] ) );

			SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );
		}
	}

	//Spec ATK Power
	if( cItemWrapper.sItem.sSpecData.iSpecAttackPowerDiv )
	{
		AddString( 0, "Poder de ataque:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "NV/%d", cItemWrapper.sItem.sSpecData.iSpecAttackPowerDiv ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.sSpecData.iSpecAttackPowerDiv - cItemCompare.sItem.sSpecData.iSpecAttackPowerDiv;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%sNV/%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 225, 30, 0 ) : D3DCOLOR_ARGB( 255, 0, 130, 255 ) );
		}
	}

	//Spec ATK Rtg
	if( cItemWrapper.sItem.sSpecData.iSpecAttackRatingDiv )
	{
		AddString( 0, "Tasa de ataque:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "NV/%d", cItemWrapper.sItem.sSpecData.iSpecAttackRatingDiv ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.sSpecData.iSpecAttackRatingDiv - cItemCompare.sItem.sSpecData.iSpecAttackRatingDiv;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%sNV/%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 225, 30, 0 ) : D3DCOLOR_ARGB( 255, 0, 130, 255 ) );
		}
	}

	//Spec Range
	if( cItemWrapper.sItem.sSpecData.iSpecAttackRange )
	{
		AddString( 0, "Alcance:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d", cItemWrapper.sItem.sSpecData.iSpecAttackRange ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.sSpecData.iSpecAttackRange - cItemCompare.sItem.sSpecData.iSpecAttackRange;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec Penetration
	if ( cItemWrapper.sItem.sSpecData.sSpecPenetration )
	{
		AddString( 0, "Penetraci\363n esp.:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d", cItemWrapper.sItem.sSpecData.sSpecPenetration ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if ( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.sSpecData.sSpecPenetration - cItemCompare.sItem.sSpecData.sSpecPenetration;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if ( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec HP Potion Efficience
	if ( cItemWrapper.sItem.sSpecData.sSpecHPPotionEfficience )
	{
		AddString( 0, "Efic. poci\363n HP esp.:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d%%", cItemWrapper.sItem.sSpecData.sSpecHPPotionEfficience ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if ( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.sSpecData.sSpecHPPotionEfficience - cItemCompare.sItem.sSpecData.sSpecHPPotionEfficience;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if ( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d%%)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec MP Potion Efficience
	if ( cItemWrapper.sItem.sSpecData.sSpecMPPotionEfficience )
	{
		AddString( 0, "Efic. poci\363n MP esp.:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d%%", cItemWrapper.sItem.sSpecData.sSpecMPPotionEfficience ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if ( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.sSpecData.sSpecMPPotionEfficience - cItemCompare.sItem.sSpecData.sSpecMPPotionEfficience;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if ( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d%%)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec SP Potion Efficience
	if ( cItemWrapper.sItem.sSpecData.sSpecSPPotionEfficience )
	{
		AddString( 0, "Efic. poci\363n SP esp.:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%d%%", cItemWrapper.sItem.sSpecData.sSpecSPPotionEfficience ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if ( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.sSpecData.sSpecSPPotionEfficience - cItemCompare.sItem.sSpecData.sSpecSPPotionEfficience;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if ( iCalc != 0 )
				AddCompareString( FormatString( "(%s%d%%)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec HP Boost
	if ( cItemWrapper.sItem.sSpecData.iSpecAddHPDiv )
	{
		AddString( 0, "Aumento m\341x. HP:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "NV/%d", cItemWrapper.sItem.sSpecData.iSpecAddHPDiv ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if ( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.sSpecData.iSpecAddHPDiv - cItemCompare.sItem.sSpecData.iSpecAddHPDiv;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if ( iCalc != 0 )
				AddCompareString( FormatString( "(%sNV/%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec MP Boost
	if( cItemWrapper.sItem.sSpecData.iSpecAddMPDiv )
	{
		AddString( 0, "Aumento m\341x. MP:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "NV/%d", cItemWrapper.sItem.sSpecData.iSpecAddMPDiv ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			int iCalc = cItemWrapper.sItem.sSpecData.iSpecAddMPDiv - cItemCompare.sItem.sSpecData.iSpecAddMPDiv;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( iCalc != 0 )
				AddCompareString( FormatString( "(%sNV/%d)", iCalc > 0 ? "+" : "", iCalc ), iCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec HP Regen
	if( cItemWrapper.sItem.sSpecData.fSpecHPRegen && cItemWrapper.sBaseItemID.ToItemType() != ITEMTYPE_ForceOrb )
	{
		AddString( 0, "Reg. HP:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%.1f", cItemWrapper.sItem.sSpecData.fSpecHPRegen ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			float fCalc = cItemWrapper.sItem.sSpecData.fSpecHPRegen - cItemCompare.sItem.sSpecData.fSpecHPRegen;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( fCalc != 0 )
				AddCompareString( FormatString( "(%s%.1f)", fCalc > 0 ? "+" : "", fCalc ), fCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec MP Regen
	if( cItemWrapper.sItem.sSpecData.fSpecMPRegen && cItemWrapper.sBaseItemID.ToItemType() != ITEMTYPE_ForceOrb )
	{
		AddString( 0, "Reg. MP:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%.1f", cItemWrapper.sItem.sSpecData.fSpecMPRegen ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if( bCompareItem && bIsEquippedItem )
		{
			float fCalc = cItemWrapper.sItem.sSpecData.fSpecMPRegen - cItemCompare.sItem.sSpecData.fSpecMPRegen;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if( fCalc != 0 )
				AddCompareString( FormatString( "(%s%.1f)", fCalc > 0 ? "+" : "", fCalc ), fCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	//Spec STM Regen
	if ( cItemWrapper.sItem.sSpecData.fSpecSPRegen && cItemWrapper.sBaseItemID.ToItemType() != ITEMTYPE_ForceOrb )
	{
		AddString( 0, "Reg. STM:", D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
		AddString( 1, FormatString( "%.1f", cItemWrapper.sItem.sSpecData.fSpecSPRegen ) );

		SetLineColor( D3DCOLOR_ARGB( 255, 235, 190, 60 ), 1 );

		//Compare Item
		if ( bCompareItem && bIsEquippedItem )
		{
			float fCalc = cItemWrapper.sItem.sSpecData.fSpecSPRegen - cItemCompare.sItem.sSpecData.fSpecSPRegen;

			SetLineColor( D3DCOLOR_ARGB( 255, 165, 157, 140 ), 0 );

			if ( fCalc != 0 )
				AddCompareString( FormatString( "(%s%.1f)", fCalc > 0 ? "+" : "", fCalc ), fCalc > 0 ? D3DCOLOR_ARGB( 255, 0, 130, 255 ) : D3DCOLOR_ARGB( 255, 225, 30, 0 ) );
		}
	}

	// Price
	// Shop is open?
	if ( (*(BOOL*)0x03653E40) )
	{
		// Next Line
		AddString( 0, "" );
		AddString( 1, "" );

		if ( bShowBuyPrice )
		{
			// Normal, price
			if ( bShowBuyPrice == 2 )
			{
				// Get Inventory Price Item
				PriceItem sSellItemData = { 0, 0, 0 };
				ITEMHANDLER->GetItemPrice( (ItemData*)pcItemData, &sSellItemData );
				pcItemData->iSalePrice = sSellItemData.iPrice;

				// Set Price Item		
				AddString( 0, "Precio:" );
				AddString( 1, pcItemData->iSalePrice > 0 ? FormatString("%s Oro",FormatNumber( pcItemData->iSalePrice )) : "Gratis" );
			}
			if ( bShowBuyPrice == 1 )
			{
				// Set Text
				char szTempText[32] = { 0 };
				int iPrice = GetDisplayedRarityBuyPrice( &cItemWrapper.sItem );

				// Get Price with BC Tax
				__asm
				{
					PUSH iPrice;
					MOV EAX, 0x004E5A10;
					CALL EAX;
					MOV iPrice, EAX;
				}
				
				AddString( 0, "Precio:" );
				AddString( 1, iPrice > 0 ? FormatString("%s Oro",FormatNumber( iPrice )) : "Gratis" );
			}
		}
	}

	// Personal Shop is open?
	if ( PERSONALSHOPHANDLER->GetWindow()->IsOpen() )
	{
		if ( auto[bRet, psPrice] = PERSONALSHOPHANDLER->GetPrice( cItemWrapper.sItem.sItemID.ToInt(), cItemWrapper.sItem.iChk1, cItemWrapper.sItem.iChk2 ); bRet )
		{
			// Next Line
			AddString( 0, "" );
			AddString( 1, "" );

			if ( psPrice->bCanBuy )
			{
				AddString( 0, "Precio:" );

				if ( psPrice->bCredits )
					AddString( 1, psPrice->iPrice > 0 ? FormatString( "%s monedas", FormatNumber( psPrice->iPrice ) ) : "Gratis", D3DCOLOR_XRGB( 255, 140, 0 ) );
				else
					AddString( 1, psPrice->iPrice > 0 ? FormatString( "%s gp", FormatNumber( psPrice->iPrice ) ) : "Gratis" );
			}
			else
			{
				AddString( 0, "Solo vista", D3DCOLOR_XRGB( 84, 174, 232 ), TRUE );
				AddString( 1, "" );
			}
		}
	}

	//Debug Item Info
	if( bShowChecksums )
	{
		AddString( 0, "\n" );
		AddString( 1, "" );

		AddString( 0, FormatString( "%d", cItemWrapper.sItem.iChk1 ) );
		AddString( 1, "" );

		AddString( 0, FormatString( "%d", cItemWrapper.sItem.iChk2 ) );
		AddString( 1, "" );
	}

	//Socket Item
	if( cItemWrapper.sItem.sSocketData[0].eSocketType != SOCKETTYPE_None )
	{
		AddString( 0, "\n\n " );
		AddString( 1, "\n\n " );
	}


	//Is Ítem perfecto?
	if ( bIsPerfectItem )
	{
		cBackgroundColor1 = UI::Color( 235, 45, 39, 27 );
		//cBackgroundColor2 = UI::Color( 245, 24, 42, 56 );
	}
	//Can't use item?
	else if ( bCantUseItem )
	{
		cBackgroundColor1 = UI::Color( 235, 10, 10, 10 );
		cBackgroundColor2 = UI::Color( 235, 75, 25, 25 );
	}
	else
		cBackgroundColor2 = UI::Color( 245, 9, 23, 22 );


	//Clear Text
	paSocketText[0][0]->SetText( "" );
	paSocketText[0][1]->SetText( "" );
	paSocketText[1][0]->SetText( "" );
	paSocketText[1][1]->SetText( "" );

	for( int i = 0; i < 2; i++ )
	{
		if( cItemWrapper.sItem.sSocketData[i].eSocketType != SOCKETTYPE_None )
		{
			iSocketCount += 1;

			//Get Gem Image
			switch( cItemWrapper.sItem.sSocketData[i].eGemItem )
			{
				case GEMITEM_Ruby:
					iSocketGem[i] = 0;
				break;
				case GEMITEM_Topaz:
					iSocketGem[i] = 3;
				break;
				case GEMITEM_Emerald:
					iSocketGem[i] = 6;
				break;
				case GEMITEM_Aquamarine:
					iSocketGem[i] = 9;
				break;
				case GEMITEM_Amethyst:
					iSocketGem[i] = 12;
				break;
			}

			//Format Gem Type
			if( cItemWrapper.sItem.sSocketData[i].eGemType == GEMTYPE_Triangular )
				paSocketText[i][1]->SetText( "+2" );
			else if( cItemWrapper.sItem.sSocketData[i].eGemType == GEMTYPE_Square )
			{
				paSocketText[i][1]->SetText( "+4" );
				iSocketGem[i] += 1;
			}
			else if( cItemWrapper.sItem.sSocketData[i].eGemType == GEMTYPE_Marquise )
			{
				paSocketText[i][1]->SetText( "+6" );
				iSocketGem[i] += 2;
			}

			//Format Name and Stats of Gem
			switch( cItemWrapper.sItem.sSocketData[i].eGemItem )
			{
				case GEMITEM_Topaz:
					paSocketText[i][0]->SetColor( D3DCOLOR_ARGB( 255, 255, 220, 0 ) );
					paSocketText[i][0]->SetText( "Gema de topacio" );

					paSocketText[i][1]->AppendText( " Talento" );
				break;
				case GEMITEM_Aquamarine:
					paSocketText[i][0]->SetColor( D3DCOLOR_ARGB( 255, 0, 150, 255 ) );
					paSocketText[i][0]->SetText( "Gema de aguamarina" );

					paSocketText[i][1]->AppendText( " Espiritu" );
				break;
				case GEMITEM_Ruby:
					paSocketText[i][0]->SetColor( D3DCOLOR_ARGB( 255, 180, 25, 25 ) );
					paSocketText[i][0]->SetText( "Gema de rub\355" );

					paSocketText[i][1]->AppendText( " Fuerza" );
				break;
				case GEMITEM_Amethyst:
					paSocketText[i][0]->SetColor( D3DCOLOR_ARGB( 255, 150, 5, 235 ) );
					paSocketText[i][0]->SetText( "Gema de amatista" );

					paSocketText[i][1]->AppendText( " Salud" );
				break;
				case GEMITEM_Emerald:
					paSocketText[i][0]->SetColor( D3DCOLOR_ARGB( 255, 0, 170, 10 ) );
					paSocketText[i][0]->SetText( "Gema de esmeralda" );

					paSocketText[i][1]->AppendText( " Agilidad" );
				break;
			}
		}
	}

	//Not have description or stats? So only show the Title of Item
	if( vLeftText.size() < 3 )
	{
		vLeftText.erase( vLeftText.begin() + 1 );
		vRightText.erase( vRightText.begin() + 1 );
	}

	return TRUE;
}

void ItemInfoBox::Render( int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY )
{
	//If player is viewing Item
	if( *( BOOL* )0x036286EC )
	{
		//Adjusting the iItemSlot
		iX = ( cItemWrapper.sPosition.iX + ( cItemWrapper.iWidth / 2 ) ) - 90;
		iY = cItemWrapper.sPosition.iY - ( vLeftText.size() * 14 ) - 14;
		std::vector<std::string> vTitleLines;
		std::vector<Text_ptr> vTitleTexts;
		bool bCanRenderItemPreview = CanRenderTooltipItemPreview( cItemWrapper );
		int iPreviewWidth = cItemWrapper.iWidth;
		int iPreviewHeight = cItemWrapper.iHeight;
		int iPreviewLargestDimension = max( cItemWrapper.iWidth, cItemWrapper.iHeight );
		int iTopContentOffsetY = 0;
		int iTextStartOffsetY = 5;

		int iSocketHeightExtra = 0;

		for( int i = 0; i < 2; i++ )
		{
			if( cItemWrapper.sItem.sSocketData[i].eSocketType )
				iSocketHeightExtra += i > 0 ? 36 : 8;
		}

		//Set iWidth and iHeight of Box
		int iItemInfoBoxWidth = 200 - 16 + 26;
		int iItemInfoBoxHeight = ( 14 * vLeftText.size() );
		const RarityBorderSet & sRaritySkin = GetRarityBorderSet( cItemWrapper.sItem.eRarity );
		const bool bShowPerfectInfoPanel = bDisplayHelp && !bIsPerfectItem && sRaritySkin.pInfo && sRaritySkin.pInfoLeft && sRaritySkin.pInfoRight && pImageGradient && pImagePKey;

		if ( bCanRenderItemPreview )
		{
			if ( iPreviewLargestDimension > 0 )
			{
				const float fScale = min( 1.0f, 30.0f / static_cast<float>( iPreviewLargestDimension ) );
				iPreviewWidth = max( 12, static_cast<int>( round( cItemWrapper.iWidth * fScale ) ) );
				iPreviewHeight = max( 12, static_cast<int>( round( cItemWrapper.iHeight * fScale ) ) );
			}
		}

		if ( bHasLargeName && !vLeftText.empty() )
		{
			vTitleLines = BuildTooltipTitleLines( vLeftText[0]->GetText() );

			const int iEdgeSpacing = 20;
			int iGreatestTitleWidth = 0;
			for ( const auto & strLine : vTitleLines )
			{
				Text_ptr pTitleText = std::make_shared<Text>( strLine, Rectangle2D( 0, 0, 180, 50 ), FALSE, D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
				pTitleText->SetFont( "Arial", 16, 6, FALSE, FALSE, -1 );
				pTitleText->SetMultiLine( TRUE );
				pTitleText->SetNoClip( TRUE );
				pTitleText->SetColor( D3DCOLOR_ARGB( 255, 245, 240, 218 ) );
				pTitleText->SetHorizontalAlign( ALIGN_Center );
				vTitleTexts.push_back( pTitleText );

				iGreatestTitleWidth = max( iGreatestTitleWidth, pTitleText->GetTextWidth() + ( iEdgeSpacing * 2 ) );
			}

			if ( bCanRenderItemPreview )
				iGreatestTitleWidth += 24 + iPreviewWidth + 22;

			iTopContentOffsetY = ( vTitleTexts.size() > 1 ) ? 30 : 22;
			iTextStartOffsetY += iTopContentOffsetY;

			iItemInfoBoxWidth = max( iItemInfoBoxWidth, iGreatestTitleWidth );
		}

		if ( pWindowHair->IsOpen() )
		{
			iItemInfoBoxHeight += pWindowHair->GetHeight() + 10;
			iY -= (pWindowHair->GetHeight() + 10);
		}

		if ( pWindowBody->IsOpen() )
		{
			iItemInfoBoxHeight += pWindowBody->GetHeight() + 10;
			iY -= (pWindowBody->GetHeight() + 10);
		}

		//iItemSlot of box is out the window?
		if( iX < 0 )
			iX = 0;

		if( iY < 0 )
			iY = 16;

		if( iX + iItemInfoBoxWidth > (int)RESOLUTION_WIDTH )
			iX -= ( ( iX + iItemInfoBoxWidth ) - RESOLUTION_WIDTH ) + 16;

		//Fix position if is showing from Inventory
		if( *( UINT* )0x036286EC == 2 )
			iY += RESOLUTION_HEIGHT - 600 - iSocketHeightExtra;

		//Update Item Info Box Width and Height
		iItemInfoBoxWidth += 10;
		iItemInfoBoxHeight += 20 + iSocketHeightExtra + iTopContentOffsetY;

		if ( bShowPerfectInfoPanel )
			iItemInfoBoxHeight += 26;

		//Draw Item Info Box Background
		DrawItemInfoBox( iX, iY, iItemInfoBoxWidth, iItemInfoBoxHeight );

		if ( bHasLargeName )
			RenderRarityNameFrame( sRaritySkin, iX, iY, iItemInfoBoxWidth );

		if ( bHasLargeName && !vTitleTexts.empty() )
		{
			if ( vTitleTexts.size() > 1 )
			{
				vTitleTexts[0]->SetBox( Rectangle2D( ( iItemInfoBoxWidth - vTitleTexts[0]->GetWidth() ) / 2, 4, vTitleTexts[0]->GetWidth(), vTitleTexts[0]->GetHeightText() ) );
				vTitleTexts[1]->SetBox( Rectangle2D( ( iItemInfoBoxWidth - vTitleTexts[1]->GetWidth() ) / 2, 18, vTitleTexts[1]->GetWidth(), vTitleTexts[1]->GetHeightText() ) );
			}
			else
			{
				vTitleTexts[0]->SetBox( Rectangle2D( ( iItemInfoBoxWidth - vTitleTexts[0]->GetWidth() ) / 2, 9, vTitleTexts[0]->GetWidth(), vTitleTexts[0]->GetHeightText() ) );
			}
		}

		RenderRarityBorder( sRaritySkin, iX, iY, iItemInfoBoxWidth, iItemInfoBoxHeight );

		if ( bShowPerfectInfoPanel )
			RenderRarityInfoPanel( sRaritySkin, iX, iY, iItemInfoBoxWidth, iItemInfoBoxHeight );

		if ( pWindowHair->IsOpen() )
		{
			pWindowHair->SetPosition( iX + (iItemInfoBoxWidth >> 1) - (pWindowHair->GetWidth() >> 1), iY + iItemInfoBoxHeight - pWindowHair->GetHeight() - 20 );
			pWindowHair->Render( 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0 );
		}

		if ( pWindowBody->IsOpen() )
		{
			pWindowBody->SetPosition( iX + (iItemInfoBoxWidth >> 1) - (pWindowBody->GetWidth() >> 1), iY + iItemInfoBoxHeight - pWindowBody->GetHeight() - 20 );
			pWindowBody->Render( 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0 );
		}

		bool bRenderedItemPreview = false;
		if ( bHasLargeName && bCanRenderItemPreview )
		{
			ItemData cItemPreviewData;
			ZeroMemory( &cItemPreviewData, sizeof( ItemData ) );

			if ( ITEMHANDLER->LoadItemImage( &cItemWrapper.sItem, &cItemPreviewData ) && cItemPreviewData.pcInventoryTexture )
			{
				EXESurfaceOld * psItemPreviewSurface = reinterpret_cast<EXESurfaceOld *>( cItemPreviewData.pcInventoryTexture );
				const int iSourceWidth = ( cItemPreviewData.iWidth > 0 ) ? cItemPreviewData.iWidth : cItemWrapper.iWidth;
				const int iSourceHeight = ( cItemPreviewData.iHeight > 0 ) ? cItemPreviewData.iHeight : cItemWrapper.iHeight;
				const int iSourceLargestDimension = max( iSourceWidth, iSourceHeight );
				float fPreviewScale = 1.0f;

				if ( iSourceLargestDimension > 0 )
				{
					fPreviewScale = min( 1.0f, 30.0f / static_cast<float>( iSourceLargestDimension ) );
					iPreviewWidth = max( 12, static_cast<int>( round( iSourceWidth * fPreviewScale ) ) );
					iPreviewHeight = max( 12, static_cast<int>( round( iSourceHeight * fPreviewScale ) ) );
				}

				const int iItemDrawPosX = iX + iItemInfoBoxWidth - iPreviewWidth - 20;
				const int iItemDrawPosY = iY + max( 5, ( iTopContentOffsetY - iPreviewHeight ) / 2 );

				if ( psItemPreviewSurface && psItemPreviewSurface->sTexture.pcD3DTexture )
				{
					UI::ImageRender::Render( psItemPreviewSurface->sTexture.pcD3DTexture, iItemDrawPosX, iItemDrawPosY, iSourceWidth, iSourceHeight, 0, 0, -1, fPreviewScale );
					bRenderedItemPreview = true;
				}
			}
		}

		//Render Item Type Icon
		if( !bRenderedItemPreview && cItemWrapper.IsOneHandedWeapon() )
		{
			if( pImageIconWeaponOneHand )
				UI::ImageRender::Render( pImageIconWeaponOneHand, iX + iItemInfoBoxWidth - 30, iY, 18, 16, 0, 0, -1 );
		}
		else if( !bRenderedItemPreview && cItemWrapper.IsTwoHandedWeapon() )
		{
			if( pImageIconWeaponTwoHand )
				UI::ImageRender::Render( pImageIconWeaponTwoHand, iX + iItemInfoBoxWidth - 30, iY, 18, 16, 0, 0, -1 );
		}
		else if( !bRenderedItemPreview && cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Armor )
		{
			if( pImageIconArmor )
				UI::ImageRender::Render( pImageIconArmor, iX + iItemInfoBoxWidth - 30, iY, 18, 16, 0, 0, -1 );
		}
		else if( !bRenderedItemPreview && cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Robe )
		{
			if( pImageIconRobe )
				UI::ImageRender::Render( pImageIconRobe, iX + iItemInfoBoxWidth - 30, iY, 18, 16, 0, 0, -1 );
		}
		else if( !bRenderedItemPreview && cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Orb )
		{
			if( pImageIconRobe )
				UI::ImageRender::Render( pImageIconRobe, iX + iItemInfoBoxWidth - 30, iY, 18, 16, 0, 0, -1 );
		}

		//Render Compare Text
		if( bIsEquippedItem && bCompareItem )
		{
			for( UINT i = 0; i < vRowCompare.size(); i++ )
			{
				Text_ptr pLeftText = vLeftText[ vRowCompare[i] - 1 ];
				Text_ptr pRightText = vRightText[ vRowCompare[i] - 1 ];
				Text_ptr pCompareText = vCompareText[i];

				//Load Texts
				pCompareText->SetNoClip( TRUE );
				pCompareText->SetHorizontalAlign( ALIGN_Left );
				pCompareText->SetBox( Rectangle2D( pLeftText->GetTextWidth() + pRightText->GetTextWidth() + 22, iTextStartOffsetY + ( 14 * (vRowCompare[i]-1) ), 180, iHeight ) );

				//Render Texts
				pCompareText->Render( iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0 );
			}
		}

		//Render Text
		if( vLeftText.size() == vRightText.size() )
		{
			for( size_t i = 0; i < vLeftText.size(); i++ )
			{
				if ( bHasLargeName && i == 0 )
					continue;

				Text_ptr pLeftText = vLeftText[ i ];
				Text_ptr pRightText = vRightText[ i ];

				//Load Texts
				pLeftText->SetMultiLine( TRUE );
				pLeftText->SetNoClip( TRUE );

				pRightText->SetNoClip( TRUE );

				pLeftText->SetHorizontalAlign( ALIGN_Left );
				pLeftText->SetBox( Rectangle2D( 20, iTextStartOffsetY + ( 14 * i ), 180, iHeight ) );

				pRightText->SetHorizontalAlign( ALIGN_Left );
				pRightText->SetBox( Rectangle2D( pLeftText->GetTextWidth() + 25, iTextStartOffsetY + ( 14 * i ), 180, iHeight ) );

				//Render Texts
				pLeftText->Render( iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0 );
				pRightText->Render( iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0 );
			}
		}

		if ( bHasLargeName )
		{
			for ( const auto & pTitleText : vTitleTexts )
				pTitleText->Render( iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0 );
		}

		RenderRarityDivider( sRaritySkin, iX, iY + iTopContentOffsetY, iItemInfoBoxWidth, iStatLine );
		RenderRarityDivider( sRaritySkin, iX, iY + iTopContentOffsetY, iItemInfoBoxWidth, iSpecLine );

		//Render Aging Bar
		if( cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging )
		{
			int iYExtra = 0;

			if( (bCompareItem && bIsEquippedItem) || bIsPerfectItem )
				iYExtra = 15;

			if( cItemWrapper.sItem.sMatureBar.sMax )
			{
				int iBarLenght = ( int )( ( float )( ( float )125 * ( ( ( float )cItemWrapper.sItem.sMatureBar.sCur / ( float )cItemWrapper.sItem.sMatureBar.sMax ) ) ) );
				
				if( pImageAgingBar )
					UI::ImageRender::Render( pImageAgingBar, ( iX + 92 ) - ( 130 >> 1 ), iY + 26 + iYExtra + iTopContentOffsetY, 130, 19, 0, 0, -1 );
			
				if( pImageAgingBarGage )
					UI::ImageRender::Render( pImageAgingBarGage, ( ( iX + 92 ) - ( 125 >> 1 ) ) - 1, iY + 33 + iYExtra + iTopContentOffsetY, iBarLenght, 4, 0, 0, -1 );
			}
			else
			{
				if( pImageAgingBarNum )
					UI::ImageRender::Render( pImageAgingBarNum, ( iX + 92 ) - ( 26 >> 1 ), iY + 26 + iYExtra + iTopContentOffsetY, 23, 19, 0, 0, -1 );
			}

			//Render Aging Text
			if( pTextAging )
			{
				pTextAging->SetNoClip( TRUE );
				pTextAging->SetText( FormatString("+%d",cItemWrapper.sItem.sAgeLevel) );
				pTextAging->SetBox( Rectangle2D( 79, 26 + iYExtra + iTopContentOffsetY, 23, 18 ) );
				pTextAging->SetHorizontalAlign( ALIGN_Center );
				pTextAging->SetVerticalAlign( ALIGN_Center );
				pTextAging->Render( iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0 );
			}
		}

		//Render Socket System
		if( iSocketHeightExtra )
		{
			GRAPHICENGINE->DrawRectangle2D( Rectangle2D( iX + 15, iY + iItemInfoBoxHeight - 30, 150, 1 ), D3DCOLOR_ARGB( 255, 160, 130, 105 ) );

			for( int i = 0; i < iSocketCount; i++ )
			{
				//Render Socket Info
				paSocketText[i][0]->SetNoClip( TRUE );
				paSocketText[i][0]->SetBox( Rectangle2D( 56, iItemInfoBoxHeight - 22 + ( i * 38 ), 120, 18 ) );
				paSocketText[i][0]->SetHorizontalAlign( ALIGN_Left );
				paSocketText[i][0]->Render( iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0 );

				paSocketText[i][1]->SetNoClip( TRUE );
				paSocketText[i][1]->SetBox( Rectangle2D( 56, iItemInfoBoxHeight - 8 + ( i * 38 ), 120, 18 ) );
				paSocketText[i][1]->SetHorizontalAlign( ALIGN_Left );
				paSocketText[i][1]->Render( iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0 );

				//Render Socket Background
				if( pImageSocketBackground )
					UI::ImageRender::Render( pImageSocketBackground, iX + 17, iY + iItemInfoBoxHeight - 18 + ( i * 38 ), 27, 27, -1 );

				//Render Socket Type
				for( int k = 1; k < SOCKETTYPE_Count; k++ )
				{
					if( cItemWrapper.sItem.sSocketData[i].eSocketType == (ESocketType)k )
					{
						UI::ImageRender::Render( paSocket[k-1], iX + 16, iY + iItemInfoBoxHeight - 19 + ( i * 38 ), 29, 29, -1 );
						break;
					}
				}

				//Render Socket Gem
				if( cItemWrapper.sItem.sSocketData[i].eGemItem != GEMITEM_None && paSocketGems[iSocketGem[i]] )
					UI::ImageRender::Render( paSocketGems[iSocketGem[i]], iX + 19, iY + iItemInfoBoxHeight - 15 + ( i * 38 ), 22, 22, -1 );
			}
		}
	}
}

void ItemInfoBox::Update( float fTime )
{
	if( bIsPerfectItem || ((cItemWrapper.sItem.sIntegrity.sCur == 0) && (cItemWrapper.sItem.sIntegrity.sMax > 0)) )
	{
		float fNewTime = fTime / (1000.0f / 70.0f);
		if( bFadeToColor )
		{
			fProgress += 0.01f * fNewTime;

			if( fProgress > 1.0f )
			{
				bFadeToColor = FALSE;
				fProgress = 1.0f;
			}
		}
		else if( !bFadeToColor )
		{
			fProgress -= 0.005f * fNewTime;

			if( fProgress < 0.0f )
			{
				bFadeToColor = TRUE;
				fProgress = 0.0f;
			}
		}

		if ( (cItemWrapper.sItem.sIntegrity.sCur == 0) )
			cBackgroundColor2 = UI::Color( 245, 9 + (int)(86.0f * fProgress), 23 + (int)(27.0f * fProgress), 0 );
		else
			cBackgroundColor2 = UI::Color( 245, 9 + (int)(15.0f * fProgress), 23 + (int)(19.0f * fProgress), 22 + (int)(34.0f * fProgress) );
	}

	if ( pWindowHair->IsOpen() )
	{
		auto pUnitMeshPreview = pWindowHair->GetElement<UI::UnitMesh>( UNITMESHID_HeadPreview );
		pUnitMeshPreview->SetAngle( pUnitMeshPreview->GetAngle() + 10 );
	}

	if ( pWindowBody->IsOpen() )
	{
		auto pUnitMeshPreview = pWindowBody->GetElement<UI::UnitMesh>( UNITMESHID_BodyPreview );
		pUnitMeshPreview->SetAngle( pUnitMeshPreview->GetAngle() + 10 );
	}
}

void ItemInfoBox::DrawItemInfoBox( int iX, int iY, int iWidth, int iHeight )
{
	//Draw Item Info Box Background
	if ( pRenderTargetMask )
	{
		if ( GetGraphicsDevice()->SetRenderTarget( pRenderTargetMask ) )
		{
			//Clear Render Target
			GetGraphicsDevice()->Clear( TRUE, TRUE, FALSE );

			//Draw Background
			GRAPHICENGINE->DrawRectangle2D( Rectangle2D( 0, 0, iWidth, iHeight ), cBackgroundColor1.Get(), cBackgroundColor2.Get() );

			//Drawing Mask Border
			UI::ImageRender::Render( pImageMaskLeftTop, 0, 0, pImageMaskLeftTop->GetWidth(), pImageMaskLeftTop->GetHeight(), -1 );
			UI::ImageRender::Render( pImageMaskRightTop, iWidth - pImageMaskRightTop->GetWidth(), 0, pImageMaskRightTop->GetWidth(), pImageMaskRightTop->GetHeight(), -1 );
			UI::ImageRender::Render( pImageMaskLeftBottom, 0, iHeight - pImageMaskLeftBottom->GetHeight(), pImageMaskLeftBottom->GetWidth(), pImageMaskLeftBottom->GetHeight(), -1 );
			UI::ImageRender::Render( pImageMaskRightBottom, iWidth - pImageMaskRightTop->GetWidth(), iHeight - pImageMaskLeftBottom->GetHeight(), pImageMaskRightBottom->GetWidth(), pImageMaskRightBottom->GetHeight(), -1 );

			//Back Old Render Target
			GetGraphicsDevice()->UnsetRenderTarget();
		}

		//Set Sprite Effect...
		UI::ImageRender::SetEffect( pEffectMask );
		pEffectMask->SetTechnique( "Mask" );

		if ( pEffectMask->Begin() >= 0 )
		{
			//Render the Render Target and mask it on effect
			UI::ImageRender::Render( pRenderTargetMask->GetTexture(), iX, iY - 10, pRenderTargetMask->GetWidth(), pRenderTargetMask->GetHeight(), 0, 0, D3DCOLOR_XRGB( 255, 255, 255 ), FALSE );

			pEffectMask->End();
		}
		UI::ImageRender::SetEffect( NULL );
	}
}

}
