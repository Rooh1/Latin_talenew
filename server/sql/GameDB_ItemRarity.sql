SET NOCOUNT ON;

/*
	Bootstrap base para el port de rareza v1.
	- Mantiene el sistema en COMMON hasta que cargues chances reales.
	- Los boosts baseline/spec quedan neutrales.
	- Es seguro ejecutar el script multiples veces.
*/

IF OBJECT_ID(N'dbo.RarityChanceGroup', N'U') IS NULL
BEGIN
	CREATE TABLE dbo.RarityChanceGroup
	(
		[ID] INT NOT NULL PRIMARY KEY,
		[MinLevel] INT NOT NULL,
		[MaxLevel] INT NOT NULL
	);
END;

IF OBJECT_ID(N'dbo.RarityChance', N'U') IS NULL
BEGIN
	CREATE TABLE dbo.RarityChance
	(
		[RarityChanceGroup] INT NOT NULL,
		[Rarity] INT NOT NULL,
		[Chance] INT NOT NULL,
		CONSTRAINT PK_RarityChance PRIMARY KEY ([RarityChanceGroup], [Rarity]),
		CONSTRAINT FK_RarityChance_RarityChanceGroup FOREIGN KEY ([RarityChanceGroup]) REFERENCES dbo.RarityChanceGroup([ID])
	);
END;

IF OBJECT_ID(N'dbo.RarityChanceMod', N'U') IS NULL
BEGIN
	CREATE TABLE dbo.RarityChanceMod
	(
		[Type] INT NOT NULL PRIMARY KEY,
		[ModCommon] FLOAT NOT NULL CONSTRAINT DF_RarityChanceMod_ModCommon DEFAULT (1.0),
		[ModUncommon] FLOAT NOT NULL CONSTRAINT DF_RarityChanceMod_ModUncommon DEFAULT (1.0),
		[ModRare] FLOAT NOT NULL CONSTRAINT DF_RarityChanceMod_ModRare DEFAULT (1.0),
		[ModEpic] FLOAT NOT NULL CONSTRAINT DF_RarityChanceMod_ModEpic DEFAULT (1.0),
		[ModLegendary] FLOAT NOT NULL CONSTRAINT DF_RarityChanceMod_ModLegendary DEFAULT (1.0)
	);
END;

IF OBJECT_ID(N'dbo.BaselineMod', N'U') IS NULL
BEGIN
	CREATE TABLE dbo.BaselineMod
	(
		[Class] INT NOT NULL PRIMARY KEY,
		[PercentBaselineStrength] INT NOT NULL CONSTRAINT DF_BaselineMod_Str DEFAULT (0),
		[PercentBaselineSpirit] INT NOT NULL CONSTRAINT DF_BaselineMod_Spr DEFAULT (0),
		[PercentBaselineTalent] INT NOT NULL CONSTRAINT DF_BaselineMod_Tal DEFAULT (0),
		[PercentBaselineAgility] INT NOT NULL CONSTRAINT DF_BaselineMod_Agi DEFAULT (0),
		[PercentBaselineHealth] INT NOT NULL CONSTRAINT DF_BaselineMod_Hea DEFAULT (0)
	);
END;

IF OBJECT_ID(N'dbo.ItemSpecMod', N'U') IS NULL
BEGIN
	CREATE TABLE dbo.ItemSpecMod
	(
		[ID] INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
		[AddSpecClass01] INT NOT NULL CONSTRAINT DF_ItemSpecMod_Class01 DEFAULT (0),
		[AddSpecClass02] INT NOT NULL CONSTRAINT DF_ItemSpecMod_Class02 DEFAULT (0),
		[AddSpecClass03] INT NOT NULL CONSTRAINT DF_ItemSpecMod_Class03 DEFAULT (0),
		[AddSpecClass04] INT NOT NULL CONSTRAINT DF_ItemSpecMod_Class04 DEFAULT (0),
		[AddSpecClass05] INT NOT NULL CONSTRAINT DF_ItemSpecMod_Class05 DEFAULT (0),
		[AddSpecClass06] INT NOT NULL CONSTRAINT DF_ItemSpecMod_Class06 DEFAULT (0),
		[AddSpecClass07] INT NOT NULL CONSTRAINT DF_ItemSpecMod_Class07 DEFAULT (0),
		[AddSpecClass08] INT NOT NULL CONSTRAINT DF_ItemSpecMod_Class08 DEFAULT (0),
		[AddSpecClass09] INT NOT NULL CONSTRAINT DF_ItemSpecMod_Class09 DEFAULT (0),
		[AddSpecClass10] INT NOT NULL CONSTRAINT DF_ItemSpecMod_Class10 DEFAULT (0),
		[ItemType] VARCHAR(12) NOT NULL,
		[PercentReqStrength] INT NOT NULL CONSTRAINT DF_ItemSpecMod_Str DEFAULT (0),
		[PercentReqSpirit] INT NOT NULL CONSTRAINT DF_ItemSpecMod_Spr DEFAULT (0),
		[PercentReqTalent] INT NOT NULL CONSTRAINT DF_ItemSpecMod_Tal DEFAULT (0),
		[PercentReqAgility] INT NOT NULL CONSTRAINT DF_ItemSpecMod_Agi DEFAULT (0),
		[PercentReqHealth] INT NOT NULL CONSTRAINT DF_ItemSpecMod_Hea DEFAULT (0)
	);
END;

IF NOT EXISTS (SELECT 1 FROM dbo.RarityChanceGroup WHERE [ID] = 1)
	INSERT INTO dbo.RarityChanceGroup ([ID], [MinLevel], [MaxLevel]) VALUES (1, 1, 79);

IF NOT EXISTS (SELECT 1 FROM dbo.RarityChanceGroup WHERE [ID] = 2)
	INSERT INTO dbo.RarityChanceGroup ([ID], [MinLevel], [MaxLevel]) VALUES (2, 80, 99);

IF NOT EXISTS (SELECT 1 FROM dbo.RarityChanceGroup WHERE [ID] = 3)
	INSERT INTO dbo.RarityChanceGroup ([ID], [MinLevel], [MaxLevel]) VALUES (3, 100, 112);

IF NOT EXISTS (SELECT 1 FROM dbo.RarityChanceGroup WHERE [ID] = 4)
	INSERT INTO dbo.RarityChanceGroup ([ID], [MinLevel], [MaxLevel]) VALUES (4, 113, 200);

/*
	Mapeo de rareza:
	2 = Uncommon
	3 = Rare
	4 = Epic
	5 = Legendary

	Se dejan todas en 0 para que Common sea el remanente completo.
*/
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChance WHERE [RarityChanceGroup] = 1 AND [Rarity] = 2)
	INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance]) VALUES (1, 2, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChance WHERE [RarityChanceGroup] = 1 AND [Rarity] = 3)
	INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance]) VALUES (1, 3, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChance WHERE [RarityChanceGroup] = 1 AND [Rarity] = 4)
	INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance]) VALUES (1, 4, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChance WHERE [RarityChanceGroup] = 1 AND [Rarity] = 5)
	INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance]) VALUES (1, 5, 0);

IF NOT EXISTS (SELECT 1 FROM dbo.RarityChance WHERE [RarityChanceGroup] = 2 AND [Rarity] = 2)
	INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance]) VALUES (2, 2, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChance WHERE [RarityChanceGroup] = 2 AND [Rarity] = 3)
	INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance]) VALUES (2, 3, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChance WHERE [RarityChanceGroup] = 2 AND [Rarity] = 4)
	INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance]) VALUES (2, 4, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChance WHERE [RarityChanceGroup] = 2 AND [Rarity] = 5)
	INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance]) VALUES (2, 5, 0);

IF NOT EXISTS (SELECT 1 FROM dbo.RarityChance WHERE [RarityChanceGroup] = 3 AND [Rarity] = 2)
	INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance]) VALUES (3, 2, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChance WHERE [RarityChanceGroup] = 3 AND [Rarity] = 3)
	INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance]) VALUES (3, 3, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChance WHERE [RarityChanceGroup] = 3 AND [Rarity] = 4)
	INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance]) VALUES (3, 4, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChance WHERE [RarityChanceGroup] = 3 AND [Rarity] = 5)
	INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance]) VALUES (3, 5, 0);

IF NOT EXISTS (SELECT 1 FROM dbo.RarityChance WHERE [RarityChanceGroup] = 4 AND [Rarity] = 2)
	INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance]) VALUES (4, 2, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChance WHERE [RarityChanceGroup] = 4 AND [Rarity] = 3)
	INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance]) VALUES (4, 3, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChance WHERE [RarityChanceGroup] = 4 AND [Rarity] = 4)
	INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance]) VALUES (4, 4, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChance WHERE [RarityChanceGroup] = 4 AND [Rarity] = 5)
	INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance]) VALUES (4, 5, 0);

/*
	Tipos cargados por el servidor:
	0 = None
	1 = Boss
	2 = EventMimic
	3 = EventMimicHighLevel
	4 = BossHighLevel
*/
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChanceMod WHERE [Type] = 0)
	INSERT INTO dbo.RarityChanceMod ([Type], [ModCommon], [ModUncommon], [ModRare], [ModEpic], [ModLegendary]) VALUES (0, 1.0, 1.0, 1.0, 1.0, 1.0);
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChanceMod WHERE [Type] = 1)
	INSERT INTO dbo.RarityChanceMod ([Type], [ModCommon], [ModUncommon], [ModRare], [ModEpic], [ModLegendary]) VALUES (1, 1.0, 1.0, 1.0, 1.0, 1.0);
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChanceMod WHERE [Type] = 2)
	INSERT INTO dbo.RarityChanceMod ([Type], [ModCommon], [ModUncommon], [ModRare], [ModEpic], [ModLegendary]) VALUES (2, 1.0, 1.0, 1.0, 1.0, 1.0);
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChanceMod WHERE [Type] = 3)
	INSERT INTO dbo.RarityChanceMod ([Type], [ModCommon], [ModUncommon], [ModRare], [ModEpic], [ModLegendary]) VALUES (3, 1.0, 1.0, 1.0, 1.0, 1.0);
IF NOT EXISTS (SELECT 1 FROM dbo.RarityChanceMod WHERE [Type] = 4)
	INSERT INTO dbo.RarityChanceMod ([Type], [ModCommon], [ModUncommon], [ModRare], [ModEpic], [ModLegendary]) VALUES (4, 1.0, 1.0, 1.0, 1.0, 1.0);

/*
	Mods neutrales por clase. Ajusta las claves segun tu enum real si quieres
	poblarlas con otro rango.
*/
IF NOT EXISTS (SELECT 1 FROM dbo.BaselineMod WHERE [Class] = 0)
	INSERT INTO dbo.BaselineMod ([Class], [PercentBaselineStrength], [PercentBaselineSpirit], [PercentBaselineTalent], [PercentBaselineAgility], [PercentBaselineHealth])
	VALUES (0, 0, 0, 0, 0, 0);

/*
	ItemSpecMod queda sin filas por defecto. El loader soporta tabla vacia y
	cae a mods neutros.
*/

IF OBJECT_ID(N'dbo.ItemRarityRuntimeMod', N'U') IS NULL
BEGIN
	CREATE TABLE dbo.ItemRarityRuntimeMod
	(
		[Category] VARCHAR(32) NOT NULL,
		[LevelBand] VARCHAR(16) NOT NULL,
		[DamageMin] INT NOT NULL CONSTRAINT DF_ItemRarityRuntimeMod_DamageMin DEFAULT (0),
		[DamageMax] INT NOT NULL CONSTRAINT DF_ItemRarityRuntimeMod_DamageMax DEFAULT (0),
		[AttackRating] INT NOT NULL CONSTRAINT DF_ItemRarityRuntimeMod_AttackRating DEFAULT (0),
		[Critical] INT NOT NULL CONSTRAINT DF_ItemRarityRuntimeMod_Critical DEFAULT (0),
		[DefenseRating] INT NOT NULL CONSTRAINT DF_ItemRarityRuntimeMod_DefenseRating DEFAULT (0),
		[AbsorbRating] FLOAT NOT NULL CONSTRAINT DF_ItemRarityRuntimeMod_AbsorbRating DEFAULT (0),
		[BlockRating] FLOAT NOT NULL CONSTRAINT DF_ItemRarityRuntimeMod_BlockRating DEFAULT (0),
		[AddHP] FLOAT NOT NULL CONSTRAINT DF_ItemRarityRuntimeMod_AddHP DEFAULT (0),
		[AddMP] FLOAT NOT NULL CONSTRAINT DF_ItemRarityRuntimeMod_AddMP DEFAULT (0),
		[AddSP] FLOAT NOT NULL CONSTRAINT DF_ItemRarityRuntimeMod_AddSP DEFAULT (0),
		[PotionStorage] INT NOT NULL CONSTRAINT DF_ItemRarityRuntimeMod_PotionStorage DEFAULT (0),
		CONSTRAINT PK_ItemRarityRuntimeMod PRIMARY KEY ([Category], [LevelBand])
	);
END;

/*
	Config runtime segura.
	Los valores son por nivel de rareza sobre Common:
	Uncommon=1x, Rare=2x, Epic=3x, Legendary=4x.

	Categorias:
	- Weapon
	- Armor
	- Boots
	- DefenseBracelet
	- Shield
	- MiscBracelet
	- Amulet
	- Ring
	- Orb

	LevelBand:
	- Low / Mid / High segun corresponda a cada categoria.
*/
IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'Weapon' AND [LevelBand] = 'Low')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('Weapon', 'Low', 3, 3, 10, 1, 0, 0, 0, 0, 0, 0, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'Weapon' AND [LevelBand] = 'Mid')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('Weapon', 'Mid', 4, 4, 13, 1, 0, 0, 0, 0, 0, 0, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'Weapon' AND [LevelBand] = 'High')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('Weapon', 'High', 5, 5, 20, 1, 0, 0, 0, 0, 0, 0, 0);

IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'Armor' AND [LevelBand] = 'Low')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('Armor', 'Low', 0, 0, 0, 0, 15, 1.4, 0.0, 0, 0, 0, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'Armor' AND [LevelBand] = 'High')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('Armor', 'High', 0, 0, 0, 0, 25, 4.0, 0.0, 0, 0, 0, 0);

IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'Boots' AND [LevelBand] = 'Low')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('Boots', 'Low', 0, 0, 0, 0, 7, 0.7, 0.0, 0, 0, 0, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'Boots' AND [LevelBand] = 'High')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('Boots', 'High', 0, 0, 0, 0, 20, 1.6, 0.0, 0, 0, 0, 0);

IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'DefenseBracelet' AND [LevelBand] = 'Low')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('DefenseBracelet', 'Low', 0, 0, 0, 0, 6, 0.0, 0.0, 0, 0, 0, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'DefenseBracelet' AND [LevelBand] = 'High')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('DefenseBracelet', 'High', 0, 0, 0, 0, 14, 0.0, 0.0, 0, 0, 0, 0);

IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'Shield' AND [LevelBand] = 'Low')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('Shield', 'Low', 0, 0, 0, 0, 7, 0.5, 0.3, 0, 0, 0, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'Shield' AND [LevelBand] = 'Mid')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('Shield', 'Mid', 0, 0, 0, 0, 13, 0.7, 0.3, 0, 0, 0, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'Shield' AND [LevelBand] = 'High')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('Shield', 'High', 0, 0, 0, 0, 20, 1.0, 0.5, 0, 0, 0, 0);

IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'MiscBracelet' AND [LevelBand] = 'Low')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('MiscBracelet', 'Low', 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 3);
IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'MiscBracelet' AND [LevelBand] = 'High')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('MiscBracelet', 'High', 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 4);

IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'Amulet' AND [LevelBand] = 'Low')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('Amulet', 'Low', 0, 0, 0, 0, 0, 0, 0, 2.0, 2.0, 0.0, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'Amulet' AND [LevelBand] = 'High')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('Amulet', 'High', 0, 0, 0, 0, 0, 0, 0, 3.0, 4.0, 0.0, 0);

IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'Ring' AND [LevelBand] = 'Low')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('Ring', 'Low', 0, 0, 0, 0, 0, 0, 0, 1.0, 0.0, 2.0, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'Ring' AND [LevelBand] = 'High')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('Ring', 'High', 0, 0, 0, 0, 0, 0, 0, 3.0, 0.0, 4.0, 0);

IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'Orb' AND [LevelBand] = 'Low')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('Orb', 'Low', 1, 1, 2, 0, 0, 0, 0, 0.0, 0.0, 0.0, 0);
IF NOT EXISTS (SELECT 1 FROM dbo.ItemRarityRuntimeMod WHERE [Category] = 'Orb' AND [LevelBand] = 'High')
	INSERT INTO dbo.ItemRarityRuntimeMod ([Category], [LevelBand], [DamageMin], [DamageMax], [AttackRating], [Critical], [DefenseRating], [AbsorbRating], [BlockRating], [AddHP], [AddMP], [AddSP], [PotionStorage])
	VALUES ('Orb', 'High', 2, 2, 4, 0, 0, 0, 0, 0.0, 0.0, 0.0, 0);
