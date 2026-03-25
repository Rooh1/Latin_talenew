#pragma once
#include "SocketSystemHandler.h"

enum AgeStoneList
{
	AgingStone = 0x080B0A00,
	CooperOre = 0x080B0B00,
	MaxAge = 0x080C5200,
};

enum class ERarityChanceModType : int
{
	None = 0,
	Boss = 1,
	EventMimic = 2,
	EventMimicHighLevel = 3,
	BossHighLevel = 4
};

struct ItemRarity
{
	EItemRarity				eRarity = ITEMRARITY_None;
	int						iRarityGroup = 0;
	int						iChance = 0;
};

struct ItemRarityChanceGroup
{
	int						iRarityGroup = 0;
	int						iMinLevel = 0;
	int						iMaxLevel = 0;
};

struct ItemRarityChanceMod
{
	float					fModCommon = 1.0f;
	float					fModUncommon = 1.0f;
	float					fModRare = 1.0f;
	float					fModEpic = 1.0f;
	float					fModLegendary = 1.0f;
};

struct StatModifier
{
	int						iStrength = 0;
	int						iSpirit = 0;
	int						iTalent = 0;
	int						iAgility = 0;
	int						iHealth = 0;
};

struct ItemSpecMod
{
	int						iSpecClass01 = 0;
	int						iSpecClass02 = 0;
	int						iSpecClass03 = 0;
	int						iSpecClass04 = 0;
	int						iSpecClass05 = 0;
	int						iSpecClass06 = 0;
	int						iSpecClass07 = 0;
	int						iSpecClass08 = 0;
	int						iSpecClass09 = 0;
	int						iSpecClass10 = 0;
	char					sItemType[12]{};
	StatModifier			sStatModifier;
};

struct ItemBaselineMod
{
	int						iClass = 0;
	StatModifier			sStatModifier;
};

// DOUBLETALE constants
#define DOUBLETALE_MIN_BALANCE 100  // 100M
#define DOUBLETALE_MAX_BALANCE 10000 // 1B
#define DOUBLETALE_BET_AMOUNT 100   // 100M
#define DOUBLETALE_WIN_AMOUNT 200   // 200M
#define DOUBLETALE_WIN_PROBABILITY 30.0f    // 2% probability to win

// TRIPLETALE constants
#define TRIPLETALE_MIN_BALANCE 300   // 200M
#define TRIPLETALE_MAX_BALANCE 10000  // 2B
#define TRIPLETALE_BET_AMOUNT 300    // 200M
#define TRIPLETALE_WIN_AMOUNT 900    // 600M
#define TRIPLETALE_WIN_PROBABILITY 20.0f     // 1% probability to win

// TIMESTENTALE constants
#define TIMESTENTALE_MIN_BALANCE 500  // 500M
#define TIMESTENTALE_MAX_BALANCE 20000 // 5B
#define TIMESTENTALE_BET_AMOUNT 500   // 500M
#define TIMESTENTALE_WIN_AMOUNT 5000  // 5B
#define TIMESTENTALE_WIN_PROBABILITY 1.0f    // 0.5% probability to win
/*
// Original constants (kept for compatibility)
#define MIN_TALE_BALANCE 100000000  // 100M
#define MAX_TALE_BALANCE 1000000000 // 1B
#define TALE_BET_AMOUNT 100000000   // 100M
#define TALE_WIN_AMOUNT 200000000   // 200M
#define WIN_PROBABILITY 2.0f         // 2% probabilidad de ganar
*/
static const int CRC_ITEMSHOP_UNIQUEID = 0x684871;

struct LoadItemDataHandler
{
	BOOL				bLoaded;
	int					iID;
	ItemLoadData		sItem;

	char				szCode[64];
};


#define SOCKETSYSTEMHANDLER						ItemServer::pcSocketSystemHandler			

class ItemServer
{
protected:

	static const DWORD								pfnCheckItem			= 0x00445FA0;
	static const DWORD								pfnDeleteItem			= 0x00550EA0;
	static const DWORD								pfnAddItem				= 0x00568410;
	static const DWORD								pfnIncreaseAgingState	= 0x004BD540;
	static const DWORD								pfnSaveItemData			= 0x005555B0;
	static const DWORD								pfnRecordAgingLog		= 0x00553D70;
	static const DWORD								pfnRecordItemChangeLog	= 0x00554C90;
	static const DWORD								pfnCreateDefItem		= 0x0043C580;
	static const DWORD								pfnCreateItemCount		= 0x00552890;
	static const DWORD								pfnIncreaseAging		= 0x004BD540;
	static const DWORD								pfnSetAgingChecksum		= 0x004461C0;

	typedef											INT( __cdecl *tfnDeleteItem )(UserData * pcUserData, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);
	typedef											INT( __cdecl *tfnAddItem )(UserData * pcUserData, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);
	typedef											BOOL( __cdecl *tfnCheckItem )(const Item * psItem);
	typedef											BOOL( __cdecl *tfnIncreaseAgingState )(Item * psItem);
	typedef											BOOL( __cdecl *tfnSaveItemData )(Item * psItem);
	typedef											void( __cdecl *tfnRecordAgingLog )(UserData * pcUserData, Item * psItemSource, Item * psItemDest );
	typedef											void( __cdecl *tfnRecordItemChangeLog )(UserData * pcUserData, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, DWORD dwNewItemCode, DWORD dwNewHead, DWORD dwNewChkSum, int Flag);
	typedef											void( __cdecl *tfnCreateDefItem )(Item * psItem, DefinitionItem * psDefItem, int iSpeck);
	typedef											void( __cdecl *tfnCreateItemCount )(UserData * pcUserData, DWORD dwItemCode, int iCount);
	typedef											void( __cdecl *tfnIncreaseAging )(Item * psItem);
	typedef											void( __cdecl *tfnSetAgingChecksum )(Item * psItem);

private:

	EItemTimerType								GetPremiumType( DWORD dwCode );
	PremiumItem									* GetPremiumInfo( DWORD dwCode );
	void										SendItemTimer( User * pcUser, EItemID iItemID, EItemTimerType iType, DWORD dwTimeLeft, DWORD dwTimeTotal );

	static LoadItemDataHandler					* psRecoveryQueue;
	static HANDLE								hThreadRecovery;
	static HANDLE								hEventRecoveryQueue;

	std::vector<ItemRarity>						vItemRarity;
	std::vector<ItemRarityChanceGroup>			vItemRarityChanceGroup;
	std::vector<ItemSpecMod>					vItemSpecMods;
	std::vector<ItemBaselineMod>				vItemBaselineMods;
	std::map<ERarityChanceModType, ItemRarityChanceMod> mRarityChanceMod;
	ItemRarityRuntimeConfig						sItemRarityRuntimeConfig;

private:
	void										LoadDefaultRarityData();
	void										LoadDefaultBaselineData();
	void										LoadDefaultSpecModData();
	void										LoadDefaultRuntimeConfig();
	BOOL										IsBossOrSpecialItem( DWORD dwItemID ) const;
	void										SendItemRarityRuntimeConfig( User * pcUser ) const;
	void										BroadcastItemRarityRuntimeConfig() const;
	void										EnsureItemRarity( Item * psItem, EItemSource eItemSource = EItemSource::Unknown );
	EItemRarity									ResolveItemRarity( const Item * psItem ) const;
	EItemRarity									GetLegacyItemRarity( const Item * psItem ) const;
	EItemRarity									ChooseItemRarity( int iLevel, ERarityChanceModType eModType ) const;
	void										ApplyRarityToItem( Item * psItem, EItemRarity eItemRarity, BOOL bReverse = FALSE );
	void										ApplyRarityToDefinition( DefinitionItem * psDefItem, EItemRarity eItemRarity ) const;
	BOOL										ShouldNormalizeLegacyItemRarity( const Item * psItem ) const;
	void										NormalizeLegacyItemRarity( Item * psItem, EItemRarity & eStoredRarity );
	void										RestoreLegacyItemRarity( Item * psItem, EItemRarity eStoredRarity );
	int											GetItemBasePrice( DWORD dwItemID ) const;
	int											GetItemBaseIntegrity( DWORD dwItemID, SHORT sFallbackMax ) const;
	BOOL										IsItemAbleToHaveRarity( const Item * psItem ) const;
	BOOL										IsItemAbleToHaveRarity( const DefinitionItem * psDefItem ) const;

public:
	ItemServer();
	virtual ~ItemServer();

	static CSocketSystemHandler					* pcSocketSystemHandler;

	BOOL										CheckQuestItemAging( const char * pszItemName, int iItemID = 0 );

	ItemData *										FindItemPointerTable( const char * szCode );
	ItemData *										FindItemPointerTable( const UINT uCode );
	DefinitionItem *								FindItemDefByCode( DWORD dwCode );
	DefinitionItem *								FindItemDefByCode( const char * pszCode );
	DefinitionItem *									FindItemDefByLevelBase( int iItemBase, int iLevel );
	int											FindItemPositionTable( char * pszName );
	BOOL 										FindItemName( UINT uCode, char * szBufName );
	BOOL 										FindItemName( char * pszCode, char * szBufName );
	int											GetItemIDByItemCode( char * pszCode );

	BOOL										IsDropableItem( int iItemID );

	int											SpecStoneToCharacterSpec( int iItemID );

	BOOL										IsDeluxeStone( int iItemID );

	static CharacterClassData					* GetItemSpecClassJob( int iClass, DefinitionItem * psDefItem );

	int											UseItem( UserData * pcUserData, DWORD dwCode, DWORD dwHead, DWORD dwChkSum );
	int											UseItem( User * pcUser, DWORD dwCode, DWORD dwHead, DWORD dwChkSum );
	int											AddItemInventory( UserData * pcUserData, DWORD dwCode, DWORD dwHead, DWORD dwChkSum );
	int 										FindItemInventory( UserData * pcUserData, DWORD dwCode, DWORD dwHead, DWORD dwChkSum );
	BOOL 										GetItemInventoryCheksum( User * pcUser, EItemID iItemID, int & iChk1, int & iChk2 );

	void										SendDeleteItem( User * pcUser, EItemID iItemID, int iChk1, int iChk2 );

	BOOL										IsItemSafe( UserData * pcUserData, int iItemID, int iChk1, int iChk2, int iGold, DWORD dwSec1, DWORD dwSec2, DWORD dwSec3, DWORD dwSec4, int * piaPotionCount );
	static BOOL									IsItemSafeServer( UserData * pcUserData, int iItemID, int iChk1, int iChk2, int iGold, DWORD dwSec1, DWORD dwSec2, DWORD dwSec3, DWORD dwSec4, int * piaPotionCount );

	void										SaveItemData( Item * psItem );
	BOOL										CheckValidItem(const Item * psItem);
	void										CreateItem( Item * psItem, DefinitionItem * psDefItem, int iSpeck = 0 );
	void										CreateItem( Item * psItem, DefinitionItem * psDefItem, EItemSource eItemSource, int iSpeck = 0, int iSpecAtkRating = 0, int iAgeLevel = 0, EItemRarity eForcedRarity = ITEMRARITY_None );
	void										CreateItem( UserData * pcUserdata, EItemID eItem, int iCount );
	void										CreatePerfectItem( Item * psOut, DefinitionItem * psIn, int iSpeck = 0 );

	int											AddPotion( UserData * pcUserData, EItemID iItemID, int iCount );

	BOOL										GetDropPotion( UserData * pcUserData, int iItemID );
	BOOL										AddDropPotion( UserData * pcUserData, int iItemID );

	BOOL										CreatePremium( UserData * pcUserData, EItemID iItemID, int iType, DWORD dwTime );

	void										SetAgingItem( ItemData * psItemData );

	int											DecodeItemsData( void * pItemData, void * pItemDest, int iSize );
	int											EncodeItemsData( void * pItemData, void * pItemDest, int iSize );
	int											EncodeItemsData( void * pItemData, void * pItemDest, int iSize, int iSizeDest );

	static int									DecodeItemsDataPotion( UserData * pcUserData, void * pItemData, void * pItemDest, int iSize, void * pRecorData );

	static int 									ComparePotions( UserData * pcUserData, CharacterSave * psCharacterSave );

	static int									LoadForceOrb( UserData * pcUserData, CharacterSave * psCharacterSave );

	void										OnSetItemPerfect( Item * pItem );

	void										SendMixDescription( UserData * pcUserData, UINT puMix );

	int											GetAgingType( UserData * pcUserData );

	void										CreateMixingList();
	BOOL										OnUpgradeAgingItem( UserData * pcUserData, PacketItem * psPacket );
	BOOL										OnAgingItem( UserData * pcUserData, PacketAgingItem * psPacket );

	void										ProcessIntegrity( User * pcUser, EIntegrityUpdate eUpdate );
	void										UpdateIntegrity( Item * psItem, int iValueCur, int iValueMax = 0 );

	DWORD										OnPhoenixPet( UserData * pcUserData, DWORD dwCode, BOOL bDelete, int iElementType = PHOENIXTYPEID_None );
	BOOL										OnPremiumItem( DWORD dwCode, int iX, int iY, int iZ, UserData * pcUserData );

	BOOL										ValidateItem( ItemData * psItem );
	BOOL										ValidateItem( Item * psItem );
	void										ValidateItemTime( Item * psItem );
	void										RegisterItemSecCode( UserData * pcUserData, PacketItem * psItem );

	void										SendItemData( UserData * pcUserData, Item * psItem );

	BOOL										OnSaveItemData( Item * psItem );
	BOOL										OnLoadItemData( ItemLoadData * psItem, const char * pszCode );
	void										UpdateItemRarityChanceGroup();
	void										UpdateItemRarityMods();
	void										UpdateItemRarity();
	void										UpdateItemRarityRuntimeConfig();
	void										GetBaselineMod();
	void										GetItemSpecMod();
	int											GetItemBuyPrice( DWORD dwItemID, bool bHasSpec, int iItemRarityNum ) const;
	int											GetItemSellPrice( DWORD dwItemID, bool bHasSpec, SHORT sDurability, SHORT sDurabilityMax, int iItemRarityNum ) const;
	int											GetItemRepairPrice( DWORD dwItemID, bool bHasSpec, SHORT sDurability, SHORT sDurabilityMax, int iItemRarityNum ) const;

	ItemPremium									* GetPremiumUse( UserData * pcUserData, EItemTimerType eType );
	ItemPremium									* GetPremiumUse( UserData * pcUserData, EItemID eID );

	void										OnLoadUser( User * pcUser );
	void										OnUnLoadUser( User * pcUser );
	void										UpdateItemTimer( User * pcUser );

	void										OnUseCrystal( UserData * pcUserData, int iID, DWORD dwItemID, DWORD dwTime );
	void										OnUseCrystalDie( UserData * pcUserData, int iID );

	BOOL										SQLGetItemTimer( User * pcUser, int iType, EItemID & iItemID, DWORD & dwTimeLeft, DWORD & dwTimeTotal );
	void										SQLUpdateItemTimer( User * pcUser, int iType, DWORD dwTimeLeft );
	void										SQLDeleteItemTimer( User * pcUser, int iItemID );
	BOOL										SQLAddItemTimer( User * pcUser, int iType, EItemID iItemID, DWORD dwTimeTotal );

	void										UpdateItemTimerEXP( User * pcUser, int iType, bool bRemove );

	BOOL										OnMixingItem( User * pcUser, struct PacketMixServer * psPacket );

	BOOL										OnResetItem( User * pcUser, struct PacketResetItem * psPacket );

	BOOL										OnSocketItem( User * pcUser, struct PacketSocketSystem * psPacket );

	void										OnManufactureItem( User * pcUser, struct PacketManufactureItem * psPacket );
	void										OnManufactureWeightPrice( User * pcUser );

	void										PHGetPerfectItem( User * pcUser, struct PacketGetItemPerfectView * psPacket );

	void										HandlePacket( User * pcUser, PacketGetItem * psPacket );

	BOOL										SQLLoadItemBox( User * pcUser );
	void										SQLItemLogBox( const char * pszAccountName, ItemLogBox * psItemLogBox, BOOL bAccepted );
	void										SQLItemLogBox( User * pcUser, Item * psItem, int iID, int iAmount, BOOL bAccepted );
	int											SQLItemBoxCount( const char * pszAccountName );
	int											SQLItemBoxCount( const char * pszAccountName, EItemID eItemID );
	BOOL										OpenItemBox( User * pcUser, PacketNPCItemBox * psPacket );

	BOOL										AddItemOpenBox( UserData * pcUserData, const char * pszItemName, int iSpec = 0, int iQuantity = 1 );
	BOOL										AddItemOpenBox( const char * pszAccountName, const char * pszItemName, int iSpec = 0, int iQuantity = 1 );
	BOOL										AddItemOpenBox( const char * pszAccountName, Item * psItem, const char * pszSender = "Server" );

	void										PHCheckItemUsing( UserData * pcUserData, PacketListUsingItem * psPacket );
	void										PHCheckItemUsingEx( UserData * pcUserData, PacketListUsingItem * psPacket );

	void										UpgradeNewItem( Item * psItemOld, Item * psItemNew );

	void										HandlePacket( User * pcUser, PacketBuyNPCShop * psPacket );

	void										HandlePacket( User * pcUser, PacketNewItemTimer * psPacket );
	void										HandlePacket( User * pcUser, PacketCancelItemTimer * psPacket );

	void										HandlePacket( User * pcUser, PacketOldHeadUse * psPacket );

	void										HandlePacket( User * pcUser, PacketSlotItemHandle * psPacket );

	void										HandlePacket( User * pcUser, PacketNPCItemBoxSend * psPacket );
	
	void										HandlePacket( User * pcUser, PacketRequestBeginnerItemsTimer * psPacket );
	void										HandlePacket( User * pcUser, PacketRequestChemistItemTimer * psPacket );

	static void									UpdateQueueRecovery();

	static void									DeleteQueue();

	void										CheckItemRecovery( User * pcUser );
	void										AddItemRecovery( User * pcUser, const char * pszCode );

	bool										IsItemTimerFreezedMap( EMapID iMapID, EItemTimerType iType );

	BOOL										SendItemShopList( User * pcUser, UnitData * pcUnitData );

};
