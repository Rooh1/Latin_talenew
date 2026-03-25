SET NOCOUNT ON;

/*
	Preset agresivo de prueba para ver rarezas altas rapido.
	Aplica sobre las tablas ya creadas por GameDB_ItemRarity.sql.

	Distribucion base por grupo:
	- Common:    10%
	- Uncommon:  30%
	- Rare:      25%
	- Epic:      20%
	- Legendary: 15%

	Los boss/mimic usan multiplicadores adicionales para empujar aun mas
	las rarezas altas durante pruebas.
*/

IF OBJECT_ID(N'dbo.RarityChanceGroup', N'U') IS NULL
	THROW 50001, 'RarityChanceGroup no existe. Ejecuta primero GameDB_ItemRarity.sql', 1;

IF OBJECT_ID(N'dbo.RarityChance', N'U') IS NULL
	THROW 50002, 'RarityChance no existe. Ejecuta primero GameDB_ItemRarity.sql', 1;

IF OBJECT_ID(N'dbo.RarityChanceMod', N'U') IS NULL
	THROW 50003, 'RarityChanceMod no existe. Ejecuta primero GameDB_ItemRarity.sql', 1;

DECLARE @RarityChance TABLE
(
	[RarityChanceGroup] INT NOT NULL,
	[Rarity] INT NOT NULL,
	[Chance] INT NOT NULL
);

INSERT INTO @RarityChance ([RarityChanceGroup], [Rarity], [Chance])
VALUES
	(1, 2, 3000000), (1, 3, 2500000), (1, 4, 2000000), (1, 5, 1500000),
	(2, 2, 3000000), (2, 3, 2500000), (2, 4, 2000000), (2, 5, 1500000),
	(3, 2, 3000000), (3, 3, 2500000), (3, 4, 2000000), (3, 5, 1500000),
	(4, 2, 3000000), (4, 3, 2500000), (4, 4, 2000000), (4, 5, 1500000);

UPDATE TARGET
SET TARGET.[Chance] = SOURCE.[Chance]
FROM dbo.RarityChance AS TARGET
INNER JOIN @RarityChance AS SOURCE
	ON TARGET.[RarityChanceGroup] = SOURCE.[RarityChanceGroup]
	AND TARGET.[Rarity] = SOURCE.[Rarity];

INSERT INTO dbo.RarityChance ([RarityChanceGroup], [Rarity], [Chance])
SELECT SOURCE.[RarityChanceGroup], SOURCE.[Rarity], SOURCE.[Chance]
FROM @RarityChance AS SOURCE
WHERE NOT EXISTS
(
	SELECT 1
	FROM dbo.RarityChance AS TARGET
	WHERE TARGET.[RarityChanceGroup] = SOURCE.[RarityChanceGroup]
	  AND TARGET.[Rarity] = SOURCE.[Rarity]
);

DECLARE @RarityChanceMod TABLE
(
	[Type] INT NOT NULL,
	[ModCommon] FLOAT NOT NULL,
	[ModUncommon] FLOAT NOT NULL,
	[ModRare] FLOAT NOT NULL,
	[ModEpic] FLOAT NOT NULL,
	[ModLegendary] FLOAT NOT NULL
);

INSERT INTO @RarityChanceMod ([Type], [ModCommon], [ModUncommon], [ModRare], [ModEpic], [ModLegendary])
VALUES
	(0, 1.00, 1.00, 1.00, 1.00, 1.00),
	(1, 0.50, 1.10, 1.35, 1.75, 2.25),
	(2, 0.45, 1.10, 1.40, 1.85, 2.40),
	(3, 0.35, 1.15, 1.55, 2.10, 3.00),
	(4, 0.30, 1.10, 1.60, 2.20, 3.20);

UPDATE TARGET
SET
	TARGET.[ModCommon] = SOURCE.[ModCommon],
	TARGET.[ModUncommon] = SOURCE.[ModUncommon],
	TARGET.[ModRare] = SOURCE.[ModRare],
	TARGET.[ModEpic] = SOURCE.[ModEpic],
	TARGET.[ModLegendary] = SOURCE.[ModLegendary]
FROM dbo.RarityChanceMod AS TARGET
INNER JOIN @RarityChanceMod AS SOURCE
	ON TARGET.[Type] = SOURCE.[Type];

INSERT INTO dbo.RarityChanceMod ([Type], [ModCommon], [ModUncommon], [ModRare], [ModEpic], [ModLegendary])
SELECT SOURCE.[Type], SOURCE.[ModCommon], SOURCE.[ModUncommon], SOURCE.[ModRare], SOURCE.[ModEpic], SOURCE.[ModLegendary]
FROM @RarityChanceMod AS SOURCE
WHERE NOT EXISTS
(
	SELECT 1
	FROM dbo.RarityChanceMod AS TARGET
	WHERE TARGET.[Type] = SOURCE.[Type]
);
