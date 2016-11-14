#pragma once

// Uncomment this at your own risk.
//#define UNTRUSTED_SETTINGS

// Uncomment to enable buggy/experimental settings.
//#define EXPERIMENTAL_SETTINGS

/* generic constants */
#define LIFE_ALIVE 0
#define VPANEL unsigned long long
typedef unsigned long long FONT;

struct CGlowObjectManager;

/* function prototypes */
typedef void* (*CreateInterfaceFn) (const char*, int*);
typedef CGlowObjectManager* (*GlowObjectManagerFn) (void);
typedef bool (*MsgFunc_ServerRankRevealAllFn) (float*);
typedef void (*SendClanTagFn) (const char*, const char*);

struct WeaponInfo_t {
	float m_flWeaponArmorRatio;
	float m_flPenetration;
	int m_iDamage;
	float m_flRange;
	float m_flRangeModifier;
};

enum class FontFeature: int
{
	FONT_FEATURE_ANTIALIASED_FONTS = 1,
	FONT_FEATURE_DROPSHADOW_FONTS = 2,
	FONT_FEATURE_OUTLINE_FONTS = 6
};

enum FontFlags: int
{
	FONTFLAG_NONE = 0,
	FONTFLAG_ITALIC = 0x1,
	FONTFLAG_UNDERLINE = 0x2,
	FONTFLAG_STRIKEOUT = 0x4,
	FONTFLAG_SYMBOL = 0x8,
	FONTFLAG_ANTIALIAS = 0x10,
	FONTFLAG_GAUSSIANBLUR = 0x20,
	FONTFLAG_ROTARY = 0x40,
	FONTFLAG_DROPSHADOW = 0x80,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

enum FontDrawType_t: int
{
	// Use the "additive" value from the scheme file
	FONT_DRAW_DEFAULT = 0,

	// Overrides
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,

	FONT_DRAW_TYPE_COUNT = 2,
};

enum ClientFrameStage_t: int
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

enum ObserverMode_t: int
{
	OBS_MODE_NONE = 0,
	OBS_MODE_DEATHCAM = 1,
	OBS_MODE_FREEZECAM = 2,
	OBS_MODE_FIXED = 3,
	OBS_MODE_IN_EYE = 4,
	OBS_MODE_CHASE = 5,
	OBS_MODE_ROAMING = 6
};

enum ItemDefinitionIndex: int
{
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516
};

enum SkinDefinitionIndex: int
{
	GROUNDWATER1 = 2,
	CANDY_APPLE = 3,
	FOREST_DDPAT = 5,
	ARCTIC_CAMO = 6,
	DESERT_STORM = 8,
	BENGAL_TIGER = 9,
	COPPERHEAD = 10,
	SKULLS = 11,
	CRIMSON_WEB_DEAGLE = 12,
	BLUE_STREAK = 13,
	RED_LAMINATE = 14,
	GUNSMOKE = 15,
	JUNGLE_TIGER = 16,
	URBAN_DDPAT = 17,
	VIRUS = 20,
	GRANITE_MARBLEIZED = 21,
	CONTRAST_SPRAY = 22,
	FOREST_LEAVES = 25,
	LICHEN_DASHED = 26,
	BONE_MASK = 27,
	ANODIZED_NAVY = 28,
	SNAKE_CAMO = 30,
	SILVER = 32,
	HOT_ROD_AUG = 33,
	METALLIC_DDPAT = 34,
	OSSIFIED = 36,
	BLAZE = 37,
	FADE = 38,
	BULLDOZER = 39,
	NIGHT = 40,
	COPPER = 41,
	BLUE_STEEL = 42,
	STAINED = 43,
	CASE_HARDENED = 44,
	CONTRACTOR = 46,
	COLONY = 47,
	DRAGON_TATTOO = 48,
	LIGHTNING_STRIKE = 51,
	SLAUGHTER = 59,
	DARK_WATER = 60,
	HYPNOTIC = 61,
	BLOOMSTICK = 62,
	COLD_BLOODED = 67,
	CARBON_FIBER = 70,
	SCORPION = 71,
	SAFARI_MESH = 72,
	WINGS = 73,
	POLAR_CAMO = 74,
	BLIZZARD_MARBLEIZED = 75,
	WINTER_FOREST = 76,
	BOREAL_FOREST = 77,
	FOREST_NIGHT = 78,
	ORANGE_DDPAT = 83,
	PINK_DDPAT = 84,
	MUDDER = 90,
	CYANOSPATTER = 92,
	CARAMEL = 93,
	GRASSLAND = 95,
	BLUE_SPRUCE = 96,
	ULTRAVIOLET = 98,
	SAND_DUNE1 = 99,
	STORM = 100,
	TORNADO_M4A4 = 101,
	WHITEOUT = 102,
	GRASSLAND_LEAVES = 104,
	POLAR_MESH = 107,
	CONDEMNED = 110,
	GLACIER_MESH = 111,
	SAND_MESH = 116,
	SAGE_SPRAY = 119,
	JUNGLE_SPRAY = 122,
	SAND_SPRAY = 124,
	URBAN_PERFORATED = 135,
	WAVES_PERFORATED = 136,
	ORANGE_PEEL = 141,
	URBAN_MASKED = 143,
	JUNGLE_DASHED = 147,
	SAND_DASHED = 148,
	URBAN_DASHED = 149,
	JUNGLE1 = 151,
	DEMOLITION = 153,
	AFTERIMAGE = 154,
	BULLET_RAIN = 155,
	DEATH_BY_KITTY = 156,
	PALM1 = 157,
	WALNUT = 158,
	BRASS = 159,
	SPLASH = 162,
	MODERN_HUNTER = 164,
	SPLASH_JAM = 165,
	BLAZE_ORANGE = 166,
	RADIATION_HAZARD1 = 167,
	NUCLEAR_THREAT1 = 168,
	FALLOUT_WARNING1 = 169,
	PREDATOR = 170,
	IRRADIATED_ALERT = 171,
	BLACK_LAMINATE_AK47 = 172,
	BOOM = 174,
	SCORCHED = 175,
	FADED_ZEBRA = 176,
	MEMENTO = 177,
	DOOMKITTY = 178,
	NUCLEAR_THREAT2 = 179,
	FIRE_SERPENT = 180,
	CORTICERA = 181,
	EMERALD_DRAGON = 182,
	OVERGROWTH = 183,
	CORTICERA_AWP = 184,
	GOLDEN_KOI = 185,
	WAVE_SPRAY = 186,
	ZIRKA = 187,
	GRAVEN = 188,
	BRIGHT_WATER_M4A1S = 189,
	BLACK_LIMBA = 190,
	TEMPEST = 191,
	SHATTERED = 192,
	BONE_PILE = 193,
	SPITFIRE = 194,
	DEMETER = 195,
	EMERALD = 196,
	ANODIZED_NAVY2 = 197,
	HAZARD2 = 198,
	DRY_SEASON = 199,
	MAYAN_DREAMS = 200,
	PALM2 = 201,
	JUNGLE_DDPAT = 202,
	RUST_COAT2 = 203,
	MOSAICO = 204,
	JUNGLE2 = 205,
	TORNADO = 206,
	FACETS = 207,
	SAND_DUNE2 = 208,
	GROUNDWATER2 = 209,
	ANODIZED_GUNMETAL = 210,
	OCEAN_FOAM_MP7 = 211,
	GRAPHITE2 = 212,
	OCEAN_FOAM_P2000 = 213,
	GRAPHITE1 = 214,
	X_RAY = 215,
	BLUE_TITANIUM = 216,
	BLOOD_TIGER = 217,
	HEXANE = 218,
	HIVE = 219,
	HEMOGLOBIN = 220,
	SERUM = 221,
	BLOOD_IN_THE_WATER = 222,
	NIGHTSHADE = 223,
	WATER_SIGIL = 224,
	GHOST_CAMO = 225,
	BLUE_LAMINATE = 226,
	ELECTRIC_HIVE = 227,
	BLIND_SPOT = 228,
	AZURE_ZEBRA = 229,
	STEEL_DISRUPTION = 230,
	COBALT_DISRUPTION = 231,
	CRIMSON_WEB_KNIFE = 232,
	TROPICAL_STORM = 233,
	ASH_WOOD = 234,
	VARICAMO = 235,
	NIGHT_OPS = 236,
	URBAN_RUBBLE = 237,
	VARICAMO_BLUE = 238,
	CALICAMO = 240,
	HUNTING_BLIND = 241,
	ARMY_MESH = 242,
	GATOR_MESH = 243,
	TEARDOWN = 244,
	ARMY_RECON = 245,
	AMBER_FADE_SSG = 246,
	DAMASCUS_STEEL3 = 247,
	RED_QUARTZ = 248,
	COBALT_QUARTZ = 249,
	FULL_STOP = 250,
	PIT_VIPER = 251,
	SILVER_QUARTZ = 252,
	ACID_FADE = 253,
	NITRO_M4A1S = 254,
	ASIIMOV_M4A4 = 255,
	THE_KRAKEN = 256,
	GUARDIAN1 = 257,
	MEHNDI = 258,
	REDLINE_AWP = 259,
	PULSE_260 = 260,
	MARINA = 261,
	ROSE_IRON = 262,
	RISING_SKULL = 263,
	SANDSTORM1 = 264,
	KAMI1 = 265,
	MAGMA = 266,
	COBALT_HALFTONE = 267,
	TREAD_PLATE = 268,
	THE_FUSCHIA_IS_NOW = 269,
	VICTORIA = 270,
	UNDERTOW = 271,
	TITANIUM_BIT = 272,
	HEIRLOOM = 273,
	COPPER_GALAXY = 274,
	RED_FRAGCAM = 275,
	PANTHER = 276,
	STAINLESS = 277,
	BLUE_FISSURE = 278,
	ASIIMOV_AWP = 279,
	CHAMELEON = 280,
	CORPORAL = 281,
	REDLINE_AK47 = 282,
	TRIGON = 283,
	HEAT_MAC10 = 284,
	TERRAIN = 285,
	ANTIQUE_NOVA = 286,
	PULSE_SG553 = 287,
	SERGEANT = 288,
	SANDSTORM2 = 289,
	GUARDIAN2 = 290,
	HEAVEN_GUARD_MAG7 = 291,
	DEATH_RATTLE = 293,
	GREEN_APPLE = 294,
	FRANKLIN = 295,
	METEORITE = 296,
	TUXEDO = 297,
	ARMY_SHEEN = 298,
	CAGED_STEEL = 299,
	EMERALD_PINSTRIPE = 300,
	ATOMIC_ALLOY = 301,
	VULCAN = 302,
	ISAAC = 303,
	SLASHED = 304,
	TORQUE_AUG = 305,
	ANTIQUE_PPBIZON = 306,
	RETRIBUTION = 307,
	KAMI2 = 308,
	HOWL = 309,
	CURSE = 310,
	DESERT_WARFARE = 311,
	CYREX_SCAR20 = 312,
	ORION = 313,
	HEAVEN_GUARD_XMX1014 = 314,
	POISON_DART = 315,
	JAGUAR = 316,
	BRATATAT = 317,
	ROAD_RASH = 318,
	DETOUR = 319,
	RED_PYTHON = 320,
	MASTER_PIECE = 321,
	NITRO_CZ75 = 322,
	RUST_COAT1 = 323,
	CHALICE = 325,
	KNIGHT = 326,
	CHAINMAIL = 327,
	HAND_CANNON = 328,
	DARK_AGE = 329,
	BRIAR = 330,
	ROYAL_BLUE = 332,
	INDIGO = 333,
	TWIST = 334,
	MODULE = 335,
	DESERT_STRIKE_M4A4 = 336,
	TATTER = 337,
	PULSE_P2000 = 338,
	CAIMAN = 339,
	JET_SET = 340,
	FIRST_CLASS_AK47 = 341,
	LEATHER = 342,
	COMMUTER = 343,
	DRAGON_LORE = 344,
	FIRST_CLASS_SAWEDOFF = 345,
	COACH_CLASS = 346,
	PILOT = 347,
	RED_LEATHER = 348,
	OSIRIS = 349,
	TIGRIS = 350,
	CONSPIRACY = 351,
	FOWL_PLAY = 352,
	WATER_ELEMENTAL = 353,
	URBAN_HAZARD2 = 354,
	DESERT_STRIKE_NEGEV = 355,
	KOI = 356,
	IVORY = 357,
	SUPERNOVA = 358,
	ASIIMOV_P90 = 359,
	CYREX_M4A1S = 360,
	ABYSS = 361,
	LABYRINTH = 362,
	TRAVELER = 363,
	BUSINESS_CLASS = 364,
	OLIVE_PLAID = 365,
	GREEN_PLAID = 366,
	REACTOR = 367,
	SETTING_SUN = 368,
	NUCLEAR_WASTE = 369,
	BONE_MACHINE = 370,
	STYX = 371,
	NUCLEAR_GARDEN = 372,
	CONTAMINATION = 373,
	TOXIC = 374,
	RADIATION_HAZARD2 = 375,
	CHEMICAL_GREEN = 376,
	HOT_SHOT = 377,
	FALLOUT_WARNING2 = 378,
	CERBERUS = 379,
	WASTELAND_REBEL_AK47 = 380,
	GRINDER = 381,
	MURKY = 382,
	BASILISK = 383,
	GRIFFIN = 384,
	FIRESTARTER = 385,
	DART = 386,
	URBAN_HAZARD1 = 387,
	CARTEL_P250 = 388,
	FIRE_ELEMENTAL = 389,
	HIGHWAYMAN = 390,
	CARDIAC = 391,
	DELUSION = 392,
	TRANQUILITY = 393,
	CARTEL_AK47 = 394,
	MAN_O_WAR_AWP = 395,
	URBAN_SHOCK = 396,
	NAGA = 397,
	CHATTERBOX = 398,
	CATACOMBS = 399,
	DRAGON_KING = 400,
	SYSTEM_LOCK = 401,
	MALACHITE = 402,
	DEADLY_POISON = 403,
	MUERTOS = 404,
	SERENITY = 405,
	GROTTO = 406,
	QUICKSILVER = 407,
	TIGER_TOOTH = 409,
	DAMASCUS_STEEL1 = 410,
	DAMASCUS_STEEL2 = 411,
	MARBLE_FADE = 413,
	RUST_COAT3 = 414,
	DOPPLER_RUBY = 415,
	DOPPLER_SAPPHIRE = 416 ,
	DOPPLER_BLACK_PEARL = 417 ,
	DOPPLER_PHASE_1 = 418,
	DOPPLER_PHASE_2 = 419,
	DOPPLER_PHASE_3 = 420,
	DOPPLER_PHASE_4 = 421,
	ELITE_BUILD_AK47 = 422,
	ARMOR_CORE = 423,
	WORM_GOD = 424,
	BRONZE_DECO = 425,
	VALENCE_P250 = 426,
	MONKEY_BUSINESS = 427,
	ECO = 428,
	DJINN = 429,
	HYPER_BEAST_M4A1S = 430,
	HEAT_MAG7 = 431,
	MAN_O_WAR_NEGEV = 432,
	NEON_RIDER = 433,
	ORIGAMI = 434,
	POLE_POSITION = 435,
	GRAND_PRIX = 436,
	TWILIGHT_GALAXY = 437,
	CHRONOS = 438,
	HADES = 439,
	ICARUS_FELL = 440,
	MINOTAURS_LABRYNTH = 441,
	ASTERION = 442,
	PATHFINDER = 443,
	DAEDALUS = 444,
	HOT_ROD_M4A1S = 445,
	MEDUSA = 446,
	DUELIST = 447,
	PANDORAS_BOX = 448,
	POSEIDON = 449,
	MOON_IN_LIBRA = 450,
	SUN_IN_LEO = 451,
	SHIPPING_FORECAST = 452,
	EMERALD_CZ75 = 453,
	PARA_GREEN = 454,
	AKIHABARA_ACCEPT = 455,
	HYDROPONIC = 456,
	BAMBOO_PRINT = 457,
	BAMBOO_SHADOW = 458,
	BAMBOO_FOREST = 459,
	AQUA_TERRACE = 460,
	COUNTER_TERRACE = 462,
	TERRACE = 463,
	NEON_KIMONO = 464,
	ORANGE_KIMONO = 465,
	CRIMSON_KIMONO = 466,
	MINT_KIMONO = 467,
	MIDNIGHT_STORM = 468,
	SUNSET_STORM_1 = 469,
	SUNSET_STORM_2 = 470,
	DAYBREAK = 471,
	IMPACT_DRILL = 472,
	SEABIRD = 473,
	AQUAMARINE_REVENGE = 474,
	HYPER_BEAST_AWP = 475,
	YELLOW_JACKET = 476,
	NEURAL_NET = 477,
	ROCKET_POP = 478,
	BUNSEN_BURNER = 479,
	EVIL_DAIMYO = 480,
	NEMESIS = 481,
	RUBY_POISON_DART = 482,
	LOUDMOUTH = 483,
	RANGER = 484,
	HANDGUN = 485,
	ELITE_BUILD_P90 = 486,
	CYREX_SG553 = 487,
	RIOT = 488,
	TORQUE_USP = 489,
	FRONTSIDE_MISTY = 490,
	DUALING_DRAGONS = 491,
	SURVIVOR_Z = 492,
	FLUX = 493,
	STONE_COLD = 494,
	WRAITHS = 495,
	NEBULA_CRUSADER = 496,
	GOLDEN_COIL = 497,
	RANGEEN = 498,
	COBALT_CORE = 499,
	SPECIAL_DELIVERY = 500,
	WINGSHOT = 501,
	GREEN_MARINE = 502,
	BIG_IRON = 503,
	KILL_CONFIRMED = 504,
	SCUMBRIA_XMX1014 = 505,
	POINT_DISARRAY = 506,
	RICOCHET = 507,
	FUEL_ROD = 508,
	CORINTHIAN = 509,
	RETROBUTION = 510,
	THE_EXECUTIONER = 511,
	ROYAL_PALADIN = 512,
	POWER_LOADER = 514,
	IMPERIAL = 515,
	SHAPEWOOD = 516,
	YORICK = 517,
	OUTBREAK = 518,
	TIGER_MOTH = 519,
	AVALANCHE = 520,
	TECLU_BURNER = 521,
	FADE_REVOLER = 522,
	AMBER_FADE = 523,
	FUEL_INJECTOR_AK47 = 524,
	ELITE_BUILD_AWP = 525,
	PHOTIC_ZONE = 526,
	KUMICHO_DRAGON = 527,
	CARTEL = 528,
	VALENCE_FAMAS = 529,
	TRIUMVIRATE = 530,
	ROYAL_LEGION = 532,
	THE_BATTLESTAR = 533,
	LAPIS_GATOR = 534,
	PRAETORIAN = 535,
	IMPIRE = 536,
	HYPER_BEAST2 = 537,
	NECROPOS = 538,
	JAMBIYA = 539,
	LEAD_CONDUIT = 540,
	FLEET_FLOCK = 541,
	JUDGEMENT_OF_ANUBIS = 542,
	RED_ASTOR = 543,
	VENTILATORS = 544,
	ORANGE_CRASH = 545,
	FIREFIGHT = 546,
	SPECTRE = 547,
	CHANTICO = 548,
	BIOLEAK = 549,
	OCEANIC = 550,
	ASIIMOV = 551,
	FUBAR = 552,
	ATLAS = 553,
	GHOST_CRUSADER = 554,
	RE_ENTRY = 555,
	PRIMAL_SABER = 556,
	BLACK_TIE = 557,
	LORE_BAYONET = 558,
	LORE_FLIP = 559,
	LORE_GUT = 560,
	LORE_KARAMBIT = 561,
	LORE_M9_BAYONET = 562,
	BLACK_LAMINATE_BAYONET = 563,
	BLACK_LAMINATE_FLIP = 564,
	BLACK_LAMINATE_GUT = 565,
	BLACK_LAMINATE_KARAMBIT = 566,
	BLACK_LAMINATE_M9_BAYONET = 567,
	GAMMA_DOPPLER_EMERALD_MARBLE = 568,
	GAMMA_DOPPLER_PHASE_1 = 569,
	GAMMA_DOPPLER_PHASE_2 = 570,
	GAMMA_DOPPLER_PHASE_3 = 571,
	GAMMA_DOPPLER_PHASE_4 = 572,
	AUTOTRONIC_BAYONET = 573,
	AUTOTRONIC_FLIP = 574,
	AUTOTRONIC_GUT = 575,
	AUTOTRONIC_KARAMBIT = 576,
	AUTOTRONIC_M9_BAYONET = 577,
	BRIGHT_WATER1 = 578,
	BRIGHT_WATER2 = 579,
	FREEHAND1 = 580,
	FREEHAND2 = 581,
	FREEHAND3 = 582,
	ARISTOCRAT = 583,
	PHOBOS = 584,
	VIOLENT_DAIMYO = 585,
	WASTELAND_REBEL_GLOCK = 586,
	MECHA_INDUSTRIES = 587,
	DESOLATE_SPACE = 588,
	CARNIVORE = 589,
	EXO = 590,
	IMPERIAL_DRAGON = 591,
	IRON_CLAD = 592,
	CHOPPER = 593,
	HARVESTER = 594,
	REBOOT = 595,
	LIMELIGHT = 596,
	BLOODSPORT = 597,
	AERIAL = 598,
	ICE_CAP = 599,
	NEON_REVOLUTION = 600,
	SYD_MEAD = 601,
	IMPRINT = 602,
	DIRECTIVE = 603,
	ROLL_CAGE = 604,
	SCUMBRIA_57 = 605,
	VENTILATOR = 606,
	WEASEL = 607,
	PETROGLYPH = 608,
	AIRLOCK = 609,
	DAZZLE = 610,
	GRIM = 611,
	POWERCORE = 612,
	TRIARCH = 613,
	FUEL_INJECTOR_TEC9 = 614,
	BRIEFING = 615,
	SLIPSTREAM = 616,
};

enum EClassIds: int
{
	CAI_BaseNPC = 0,
	CAK47,
	CBaseAnimating,
	CBaseAnimatingOverlay,
	CBaseAttributableItem,
	CBaseButton,
	CBaseCombatCharacter,
	CBaseCombatWeapon,
	CBaseCSGrenade,
	CBaseCSGrenadeProjectile,
	CBaseDoor,
	CBaseEntity,
	CBaseFlex,
	CBaseGrenade,
	CBaseParticleEntity,
	CBasePlayer,
	CBasePropDoor,
	CBaseTeamObjectiveResource,
	CBaseTempEntity,
	CBaseToggle,
	CBaseTrigger,
	CBaseViewModel,
	CBaseVPhysicsTrigger,
	CBaseWeaponWorldModel,
	CBeam,
	CBeamSpotlight,
	CBoneFollower,
	CBreakableProp,
	CBreakableSurface,
	CC4,
	CCascadeLight,
	CChicken,
	CColorCorrection,
	CColorCorrectionVolume,
	CCSGameRulesProxy,
	CCSPlayer,
	CCSPlayerResource,
	CCSRagdoll,
	CCSTeam,
	CDEagle,
	CDecoyGrenade,
	CDecoyProjectile,
	CDynamicLight,
	CDynamicProp,
	CEconEntity,
	CEmbers,
	CEntityDissolve,
	CEntityFlame,
	CEntityFreezing,
	CEntityParticleTrail,
	CEnvAmbientLight,
	CEnvDetailController,
	CEnvDOFController,
	CEnvParticleScript,
	CEnvProjectedTexture,
	CEnvQuadraticBeam,
	CEnvScreenEffect,
	CEnvScreenOverlay,
	CEnvTonemapController,
	CEnvWind,
	CFEPlayerDecal,
	CFireCrackerBlast,
	CFireSmoke,
	CFireTrail,
	CFish,
	CFlashbang,
	CFogController,
	CFootstepControl,
	CFunc_Dust,
	CFunc_LOD,
	CFuncAreaPortalWindow,
	CFuncBrush,
	CFuncConveyor,
	CFuncLadder,
	CFuncMonitor,
	CFuncMoveLinear,
	CFuncOccluder,
	CFuncReflectiveGlass,
	CFuncRotating,
	CFuncSmokeVolume,
	CFuncTrackTrain,
	CGameRulesProxy,
	CHandleTest,
	CHEGrenade,
	CHostage,
	CHostageCarriableProp,
	CIncendiaryGrenade,
	CInferno,
	CInfoLadderDismount,
	CInfoOverlayAccessor,
	CItem_Healthshot,
	CKnife,
	CKnifeGG,
	CLightGlow,
	CMaterialModifyControl,
	CMolotovGrenade,
	CMolotovProjectile,
	CMovieDisplay,
	CParticleFire,
	CParticlePerformanceMonitor,
	CParticleSystem,
	CPhysBox,
	CPhysBoxMultiplayer,
	CPhysicsProp,
	CPhysicsPropMultiplayer,
	CPhysMagnet,
	CPlantedC4,
	CPlasma,
	CPlayerResource,
	CPointCamera,
	CPointCommentaryNode,
	CPoseController,
	CPostProcessController,
	CPrecipitation,
	CPrecipitationBlocker,
	CPredictedViewModel,
	CProp_Hallucination,
	CPropDoorRotating,
	CPropJeep,
	CPropVehicleDriveable,
	CRagdollManager,
	CRagdollProp,
	CRagdollPropAttached,
	CRopeKeyframe,
	CSCAR17,
	CSceneEntity,
	CSensorGrenade,
	CSensorGrenadeProjectile,
	CShadowControl,
	CSlideshowDisplay,
	CSmokeGrenade,
	CSmokeGrenadeProjectile,
	CSmokeStack,
	CSpatialEntity,
	CSpotlightEnd,
	CSprite,
	CSpriteOriented,
	CSpriteTrail,
	CStatueProp,
	CSteamJet,
	CSun,
	CSunlightShadowControl,
	CTeam,
	CTeamplayRoundBasedRulesProxy,
	CTEArmorRicochet,
	CTEBaseBeam,
	CTEBeamEntPoint,
	CTEBeamEnts,
	CTEBeamFollow,
	CTEBeamLaser,
	CTEBeamPoints,
	CTEBeamRing,
	CTEBeamRingPoint,
	CTEBeamSpline,
	CTEBloodSprite,
	CTEBloodStream,
	CTEBreakModel,
	CTEBSPDecal,
	CTEBubbles,
	CTEBubbleTrail,
	CTEClientProjectile,
	CTEDecal,
	CTEDust,
	CTEDynamicLight,
	CTEEffectDispatch,
	CTEEnergySplash,
	CTEExplosion,
	CTEFireBullets,
	CTEFizz,
	CTEFootprintDecal,
	CTEFoundryHelpers,
	CTEGaussExplosion,
	CTEGlowSprite,
	CTEImpact,
	CTEKillPlayerAttachments,
	CTELargeFunnel,
	CTEMetalSparks,
	CTEMuzzleFlash,
	CTEParticleSystem,
	CTEPhysicsProp,
	CTEPlantBomb,
	CTEPlayerAnimEvent,
	CTEPlayerDecal,
	CTEProjectedDecal,
	CTERadioIcon,
	CTEShatterSurface,
	CTEShowLine,
	CTesla,
	CTESmoke,
	CTESparks,
	CTESprite,
	CTESpriteSpray,
	CTest_ProxyToggle_Networkable,
	CTestTraceline,
	CTEWorldDecal,
	CTriggerPlayerMovement,
	CTriggerSoundOperator,
	CVGuiScreen,
	CVoteController,
	CWaterBullet,
	CWaterLODControl,
	CWeaponAug,
	CWeaponAWP,
	CWeaponBaseItem,
	CWeaponBizon,
	CWeaponCSBase,
	CWeaponCSBaseGun,
	CWeaponCycler,
	CWeaponElite,
	CWeaponFamas,
	CWeaponFiveSeven,
	CWeaponG3SG1,
	CWeaponGalil,
	CWeaponGalilAR,
	CWeaponGlock,
	CWeaponHKP2000,
	CWeaponM249,
	CWeaponM3,
	CWeaponM4A1,
	CWeaponMAC10,
	CWeaponMag7,
	CWeaponMP5Navy,
	CWeaponMP7,
	CWeaponMP9,
	CWeaponNegev,
	CWeaponNOVA,
	CWeaponP228,
	CWeaponP250,
	CWeaponP90,
	CWeaponSawedoff,
	CWeaponSCAR20,
	CWeaponScout,
	CWeaponSG550,
	CWeaponSG552,
	CWeaponSG556,
	CWeaponSSG08,
	CWeaponTaser,
	CWeaponTec9,
	CWeaponTMP,
	CWeaponUMP45,
	CWeaponUSP,
	CWeaponXM1014,
	CWorld,
	DustTrail,
	MovieExplosion,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail
};

enum Bone: unsigned int
{
	BONE_PELVIS = 0,
	BONE_HIP,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_NECK,
	BONE_HEAD,
};

enum Hitbox: unsigned int
{
	HITBOX_HEAD = 0,
	HITBOX_NECK,
	HITBOX_PELVIS,
	HITBOX_SPINE,
	HITBOX_LEGS,
	HITBOX_ARMS,
};

enum HitGroups: int
{
	HITGROUP_GENERIC = 0,
	HITGROUP_HEAD,
	HITGROUP_CHEST,
	HITGROUP_STOMACH,
	HITGROUP_LEFTARM,
	HITGROUP_RIGHTARM,
	HITGROUP_LEFTLEG,
	HITGROUP_RIGHTLEG,
	HITGROUP_GEAR
};

#define FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define FL_WATERJUMP			(1<<2)	// player jumping out of water
#define FL_ONTRAIN				(1<<3)	// Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<4)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<5)	// Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<6)	// Player can't move, but keeps key inputs for controlling another entity
#define FL_CLIENT				(1<<7)	// Is a player
#define FL_FAKECLIENT			(1<<8)	// Fake client, simulated server side; don't send network messages to them
// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
#define FL_INWATER				(1<<9)	// In water

#define CONTENTS_EMPTY			0		// No contents

#define CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define CONTENTS_AUX			0x4
#define CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define CONTENTS_SLIME			0x10
#define CONTENTS_WATER			0x20
#define CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define LAST_VISIBLE_CONTENTS	CONTENTS_OPAQUE

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200

// unused
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
// CONTENTS_OPAQUE + SURF_NODRAW count as CONTENTS_OPAQUE (shadow-casting toolsblocklight textures)
#define CONTENTS_BLOCKLIGHT		0x400

#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE		0x4000

// remaining contents are non-visible, and don't eat brushes
#define CONTENTS_AREAPORTAL		0x8000

#define CONTENTS_PLAYERCLIP		0x10000
#define CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define CONTENTS_CURRENT_0		0x40000
#define CONTENTS_CURRENT_90		0x80000
#define CONTENTS_CURRENT_180	0x100000
#define CONTENTS_CURRENT_270	0x200000
#define CONTENTS_CURRENT_UP		0x400000
#define CONTENTS_CURRENT_DOWN	0x800000

#define CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define CONTENTS_DEBRIS			0x4000000
#define CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace

#define MASK_SHOT	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)

// These are given to FindMaterial to reference the texture groups that show up on the
#define TEXTURE_GROUP_LIGHTMAP						"Lightmaps"
#define TEXTURE_GROUP_WORLD							"World textures"
#define TEXTURE_GROUP_MODEL							"Model textures"
#define TEXTURE_GROUP_VGUI							"VGUI textures"
#define TEXTURE_GROUP_PARTICLE						"Particle textures"
#define TEXTURE_GROUP_DECAL							"Decal textures"
#define TEXTURE_GROUP_SKYBOX						"SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				"ClientEffect textures"
#define TEXTURE_GROUP_OTHER							"Other textures"
#define TEXTURE_GROUP_PRECACHED						"Precached"				// TODO: assign texture groups to the precached materials
#define TEXTURE_GROUP_CUBE_MAP						"CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					"RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED					"Unaccounted textures"	// Textures that weren't assigned a texture group.
//#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER		"Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			"Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		"Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	"Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	"World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	"Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	"Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			"Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			"Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER					"DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL					"ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS					"Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS				"Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			"RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS					"Morph Targets"

#define MAXSTUDIOBONES 128
#define BONE_USED_BY_HITBOX 0x100

#define MASK_SHOT	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)

// NOTE: These are stored in a short in the engine now.  Don't use more than 16 bits
#define SURF_LIGHT		0x0001		// value will hold the light strength
#define SURF_SKY2D		0x0002		// don't draw, indicates we should skylight + draw 2d sky but not draw the 3D skybox
#define SURF_SKY		0x0004		// don't draw, but add to skybox
#define SURF_WARP		0x0008		// turbulent water warp
#define SURF_TRANS		0x0010
#define SURF_NOPORTAL	0x0020	// the surface can not have a portal placed on it
#define SURF_TRIGGER	0x0040	// FIXME: This is an xbox hack to work around elimination of trigger surfaces, which breaks occluders
#define SURF_NODRAW		0x0080	// don't bother referencing the texture

#define SURF_HINT		0x0100	// make a primary bsp splitter

#define SURF_SKIP		0x0200	// completely ignore, allowing non-closed brushes
#define SURF_NOLIGHT	0x0400	// Don't calculate light
#define SURF_BUMPLIGHT	0x0800	// calculate three lightmaps for the surface for bumpmapping
#define SURF_NOSHADOWS	0x1000	// Don't receive shadows
#define SURF_NODECALS	0x2000	// Don't receive decals
#define SURF_NOPAINT	SURF_NODECALS	// the surface can not have paint placed on it
#define SURF_NOCHOP		0x4000	// Don't subdivide patches on this surface
#define SURF_HITBOX		0x8000	// surface is part of a hitbox

#define MASK_ALL					(0xFFFFFFFF)
// everything that is normally solid
#define MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks npc movement
#define MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks fluid movement
#define MASK_NPCFLUID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
// water physics in these contents
#define MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
// everything that blocks lighting
#define MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
// bullets see these as solid, except monsters (world+brush only)
#define MASK_SHOT_BRUSHONLY			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC_FLUID	(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)

// UNDONE: This is untested, any moving water
#define MASK_CURRENT				(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)

// everything that blocks corpse movement
// UNDONE: Not used yet / may be deleted
#define MASK_DEADSOLID				(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)

#define SEQUENCE_DEFAULT_DRAW						0
#define SEQUENCE_DEFAULT_IDLE1						1
#define SEQUENCE_DEFAULT_IDLE2						2
#define SEQUENCE_DEFAULT_LIGHT_MISS1				3
#define SEQUENCE_DEFAULT_LIGHT_MISS2				4
#define SEQUENCE_DEFAULT_HEAVY_MISS1				9
#define SEQUENCE_DEFAULT_HEAVY_HIT1					10
#define SEQUENCE_DEFAULT_HEAVY_BACKSTAB				11
#define SEQUENCE_DEFAULT_LOOKAT01					12

#define SEQUENCE_BUTTERFLY_DRAW						0
#define SEQUENCE_BUTTERFLY_DRAW2					1
#define SEQUENCE_BUTTERFLY_LOOKAT01					13
#define SEQUENCE_BUTTERFLY_LOOKAT03					15

#define SEQUENCE_FALCHION_IDLE1						1
#define SEQUENCE_FALCHION_HEAVY_MISS1				8
#define SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP		9
#define SEQUENCE_FALCHION_LOOKAT01					12
#define SEQUENCE_FALCHION_LOOKAT02					13

#define SEQUENCE_DAGGERS_IDLE1						1
#define SEQUENCE_DAGGERS_LIGHT_MISS1 				2
#define SEQUENCE_DAGGERS_LIGHT_MISS5 				6
#define SEQUENCE_DAGGERS_HEAVY_MISS2 				11
#define SEQUENCE_DAGGERS_HEAVY_MISS1 				12

#define SEQUENCE_BOWIE_IDLE1 						1
