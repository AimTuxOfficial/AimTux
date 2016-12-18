#pragma once
#include <map>

static std::vector<std::pair<int, const char*>> guns = {
		{ WEAPON_AK47,				"AK-47" },
		{ WEAPON_AUG,				"AUG" },
		{ WEAPON_AWP,				"AWP" },
		{ WEAPON_CZ75A,				"CZ-75" },
		{ WEAPON_DEAGLE,			"Deagle" },
		{ WEAPON_ELITE,				"Dual Berettas" },
		{ WEAPON_FAMAS,				"Famas" },
		{ WEAPON_FIVESEVEN, 		"Five-SeveN" },
		{ WEAPON_GALILAR,			"Galil AR" },
		{ WEAPON_G3SG1,				"G3SG1" },
		{ WEAPON_GLOCK,				"Glock" },
		{ WEAPON_M249,				"M249" },
		{ WEAPON_M4A1_SILENCER, 	"M4A1-S" },
		{ WEAPON_M4A1,				"M4A4" },
		{ WEAPON_MAC10,				"MAC-10" },
		{ WEAPON_MAG7,				"MAG-7" },
		{ WEAPON_MP7,				"MP7" },
		{ WEAPON_MP9,				"MP9" },
		{ WEAPON_NEGEV,				"Negev" },
		{ WEAPON_NOVA,				"Nova" },
		{ WEAPON_HKP2000,			"P2000" },
		{ WEAPON_P250,				"P250" },
		{ WEAPON_P90,				"P90" },
		{ WEAPON_BIZON,				"PP-19 Bizon" },
		{ WEAPON_REVOLVER,			"Revolver" },
		{ WEAPON_SAWEDOFF,			"Sawed-Off" },
		{ WEAPON_SCAR20,			"SCAR-20" },
		{ WEAPON_SG556,				"SG553" },
		{ WEAPON_SSG08,				"SSG08" },
		{ WEAPON_TEC9,				"Tec-9" },
		{ WEAPON_UMP45,				"UMP-45" },
		{ WEAPON_USP_SILENCER,		"USP-S" },
		{ WEAPON_XM1014,			"XM1014" },
};

static std::vector<std::pair<int, const char*>> knives = {
		{ 0,  "Bayonet" },
		{ 5,  "Flip" },
		{ 6,  "Gut" },
		{ 7,  "Karambit" },
		{ 8,  "M9 Bayonet" },
		{ 9,  "Huntsman" },
		{ 12, "Falchion" },
		{ 14, "Bowie" },
		{ 15, "Butterfly" },
		{ 16, "Shadow Daggers" },
};

static std::vector<std::pair<int, const char*>> weapon_skins = {
		{ 0,   "<-Default->" },
		{ 361, "Abyss" },
		{ 253, "Acid Fade" },
		{ 598, "Aerial" },
		{ 154, "Afterimage" },
		{ 609, "Airlock" },
		{ 455, "Akihabara Accept" },
		{ 523, "Amber Fade (Revolver)" },
		{ 246, "Amber Fade" },
		{ 210, "Anodized Gunmetal" },
		{ 197, "Anodized Navy" },
		{ 28,  "Anodized Navy" },
		{ 286, "Antique (Nova)" },
		{ 306, "Antique (PP Bizon)" },
		{ 460, "Aqua Terrace" },
		{ 474, "Aquamarine Revenge" },
		{ 6,   "Arctic Camo" },
		{ 583, "Aristocrat" },
		{ 423, "Armor Core" },
		{ 242, "Army Mesh" },
		{ 245, "Army Recon" },
		{ 298, "Army Sheen" },
		{ 234, "Ash Wood" },
		{ 279, "Asiimov (AWP)" },
		{ 255, "Asiimov (M4A4)" },
		{ 551, "Asiimov (P250)" },
		{ 359, "Asiimov (P90)" },
		{ 442, "Asterion" },
		{ 553, "Atlas" },
		{ 301, "Atomic Alloy" },
		{ 573, "Autotronic (Bayonet)" },
		{ 574, "Autotronic (Flip)" },
		{ 575, "Autotronic (Gut)" },
		{ 576, "Autotronic (Karambit)" },
		{ 577, "Autotronic (M9 Bayonet)" },
		{ 520, "Avalanche" },
		{ 229, "Azure Zebra" },
		{ 174, "BOOM" },
		{ 459, "Bamboo Forest" },
		{ 457, "Bamboo Print" },
		{ 458, "Bamboo Shadow" },
		{ 383, "Basilisk" },
		{ 9,   "Bengal Tiger" },
		{ 503, "Big Iron" },
		{ 549, "Bioleak" },
		{ 172, "Black Laminate (AK-47)" },
		{ 563, "Black Laminate (Bayonet)" },
		{ 564, "Black Laminate (Flip)" },
		{ 565, "Black Laminate (Gut)" },
		{ 566, "Black Laminate (Karambit)" },
		{ 567, "Black Laminate (M9 Bayonet)" },
		{ 190, "Black Limba" },
		{ 629, "Black Sand" },
		{ 557, "Black Tie" },
		{ 166, "Blaze Orange" },
		{ 37,  "Blaze" },
		{ 228, "Blind Spot" },
		{ 75,  "Blizzard Marbleized" },
		{ 217, "Blood Tiger" },
		{ 222, "Blood in the Water" },
		{ 597, "Bloodsport" },
		{ 62,  "Bloomstick" },
		{ 278, "Blue Fissure" },
		{ 226, "Blue Laminate" },
		{ 96,  "Blue Spruce" },
		{ 42,  "Blue Steel" },
		{ 13,  "Blue Streak" },
		{ 216, "Blue Titanium" },
		{ 370, "Bone Machine" },
		{ 27,  "Bone Mask" },
		{ 193, "Bone Pile" },
		{ 77,  "Boreal Forest" },
		{ 159, "Brass" },
		{ 317, "Bratatat" },
		{ 330, "Briar" },
		{ 615, "Briefing" },
		{ 578, "Bright Water (Knife)" },
		{ 579, "Bright Water (Knife)" },
		{ 189, "Bright Water (M4A1-S)" },
		{ 425, "Bronze Deco" },
		{ 39,  "Bulldozer" },
		{ 155, "Bullet Rain" },
		{ 479, "Bunsen Burner" },
		{ 364, "Business Class" },
		{ 632, "Buzz Kill" },
		{ 299, "Caged Steel" },
		{ 339, "Caiman" },
		{ 240, "CaliCamo" },
		{ 3,   "Candy Apple" },
		{ 93,  "Caramel" },
		{ 70,  "Carbon Fiber" },
		{ 391, "Cardiac" },
		{ 589, "Carnivore" },
		{ 388, "Cartel" },
		{ 394, "Cartel" },
		{ 528, "Cartel" },
		{ 44,  "Case Hardened" },
		{ 399, "Catacombs" },
		{ 379, "Cerberus" },
		{ 327, "Chainmail" },
		{ 325, "Chalice" },
		{ 280, "Chameleon" },
		{ 548, "Chantico's Fire" },
		{ 398, "Chatterbox" },
		{ 376, "Chemical Green" },
		{ 593, "Chopper" },
		{ 438, "Chronos" },
		{ 627, "Cirrus" },
		{ 346, "Coach Class" },
		{ 499, "Cobalt Core" },
		{ 231, "Cobalt Disruption" },
		{ 267, "Cobalt Halftone" },
		{ 249, "Cobalt Quartz" },
		{ 67,  "Cold Blooded" },
		{ 47,  "Colony" },
		{ 343, "Commuter" },
		{ 110, "Condemned" },
		{ 351, "Conspiracy" },
		{ 373, "Contamination" },
		{ 46,  "Contractor" },
		{ 22,  "Contrast Spray" },
		{ 274, "Copper Galaxy" },
		{ 41,  "Copper" },
		{ 10,  "Copperhead" },
		{ 509, "Corinthian" },
		{ 281, "Corporal" },
		{ 181, "Corticera (AWP)" },
		{ 184, "Corticera (P2000)" },
		{ 462, "Counter Terrace" },
		{ 466, "Crimson Kimono" },
		{ 12,  "Crimson Web (Deagle)" },
		{ 232, "Crimson Web" },
		{ 310, "Curse" },
		{ 92,  "Cyanospatter" },
		{ 360, "Cyrex (M4A1-S)" },
		{ 312, "Cyrex (SCAR-20)" },
		{ 487, "Cyrex (SG 553)" },
		{ 637, "Cyrex (USP)" },
		{ 444, "Daedalus" },
		{ 411, "Damascus Steel (Knife)" },
		{ 410, "Damascus Steel (Knife)" },
		{ 247, "Damascus Steel (SG 553)" },
		{ 329, "Dark Age" },
		{ 60,  "Dark Water" },
		{ 386, "Dart" },
		{ 471, "Daybreak" },
		{ 610, "Dazzle" },
		{ 403, "Deadly Poison" },
		{ 293, "Death Rattle" },
		{ 156, "Death by Kitty" },
		{ 392, "Delusion" },
		{ 195, "Demeter" },
		{ 153, "Demolition" },
		{ 8,   "Desert Storm" },
		{ 311, "Desert Warfare" },
		{ 336, "Desert-Strike" },
		{ 355, "Desert-Strike" },
		{ 588, "Desolate Space" },
		{ 319, "Detour" },
		{ 603, "Directive" },
		{ 429, "Djinn" },
		{ 178, "Doomkitty" },
		{ 417, "Doppler (Black Pearl)" },
		{ 418, "Doppler (Phase 1)" },
		{ 419, "Doppler (Phase 2)" },
		{ 420, "Doppler (Phase 3)" },
		{ 421, "Doppler (Phase 4)" },
		{ 415, "Doppler (Ruby)" },
		{ 416, "Doppler (Sapphire)" },
		{ 400, "龍王 Dragon King" },
		{ 344, "Dragon Lore" },
		{ 48,  "Dragon Tattoo" },
		{ 624, "Dragonfire" },
		{ 199, "Dry Season" },
		{ 491, "Dualing Dragons" },
		{ 447, "Duelist" },
		{ 428, "Eco" },
		{ 227, "Electric Hive" },
		{ 422, "Elite Build (AK-47)" },
		{ 525, "Elite Build (AWP)" },
		{ 486, "Elite Build (P90)" },
		{ 182, "Emerald Dragon" },
		{ 300, "Emerald Pinstripe" },
		{ 196, "Emerald" },
		{ 453, "Emerald" },
		{ 480, "Evil Daimyo" },
		{ 590, "Exo" },
		{ 207, "Facets" },
		{ 522, "Fade (Revolver)" },
		{ 38,  "Fade" },
		{ 176, "Faded Zebra" },
		{ 169, "Fallout Warning" },
		{ 378, "Fallout Warning" },
		{ 389, "Fire Elemental" },
		{ 180, "Fire Serpent" },
		{ 546, "Firefight" },
		{ 385, "Firestarter" },
		{ 341, "First Class" },
		{ 345, "First Class" },
		{ 631, "Flashback" },
		{ 541, "Fleet Flock" },
		{ 493, "Flux" },
		{ 5,   "Forest DDPAT" },
		{ 25,  "Forest Leaves" },
		{ 78,  "Forest Night" },
		{ 352, "Fowl Play" },
		{ 295, "Franklin" },
		{ 580, "Freehand" },
		{ 581, "Freehand" },
		{ 582, "Freehand" },
		{ 490, "Frontside Misty" },
		{ 552, "Fubar" },
		{ 524, "Fuel Injector (AK-47)" },
		{ 614, "Fuel Injector (Tec-9)" },
		{ 508, "Fuel Rod" },
		{ 250, "Full Stop" },
		{ 568, "Gamma Doppler (Emerald Marble)" },
		{ 569, "Gamma Doppler (Phase 1)" },
		{ 570, "Gamma Doppler (Phase 2)" },
		{ 571, "Gamma Doppler (Phase 3)" },
		{ 572, "Gamma Doppler (Phase 4)" },
		{ 243, "Gator Mesh" },
		{ 225, "Ghost Camo" },
		{ 554, "Ghost Crusader" },
		{ 634, "Gila" },
		{ 111, "Glacier Mesh" },
		{ 497, "Golden Coil" },
		{ 185, "Golden Koi" },
		{ 436, "Grand Prix" },
		{ 21,  "Granite Marbleized" },
		{ 212, "Graphite" },
		{ 214, "Graphite" },
		{ 104, "Grassland Leaves" },
		{ 95,  "Grassland" },
		{ 188, "Graven" },
		{ 294, "Green Apple" },
		{ 502, "Green Marine" },
		{ 366, "Green Plaid" },
		{ 384, "Griffin" },
		{ 611, "Grim" },
		{ 381, "Grinder" },
		{ 406, "Grotto" },
		{ 2,   "Groundwater" },
		{ 209, "Groundwater" },
		{ 257, "Guardian" },
		{ 290, "Guardian" },
		{ 15,  "Gunsmoke" },
		{ 439, "Hades" },
		{ 328, "Hand Cannon" },
		{ 485, "Handgun" },
		{ 594, "Harvester" },
		{ 198, "Hazard" },
		{ 284, "Heat" },
		{ 431, "Heat" },
		{ 291, "Heaven Guard" },
		{ 314, "Heaven Guard" },
		{ 273, "Heirloom" },
		{ 220, "Hemoglobin" },
		{ 218, "Hexane" },
		{ 390, "Highwayman" },
		{ 219, "Hive" },
		{ 33,  "Hot Rod" },
		{ 445, "Hot Rod" },
		{ 377, "Hot Shot" },
		{ 309, "Howl" },
		{ 241, "Hunting Blind" },
		{ 456, "Hydroponic" },
		{ 475, "Hyper Beast (AWP)" },
		{ 430, "Hyper Beast (M4A1-S)" },
		{ 537, "Hyper Beast (Nova)" },
		{ 61,  "Hypnotic" },
		{ 440, "Icarus Fell" },
		{ 599, "Ice Cap" },
		{ 472, "Impact Drill" },
		{ 591, "Imperial Dragon" },
		{ 515, "Imperial" },
		{ 536, "Impire" },
		{ 602, "Imprint" },
		{ 333, "Indigo" },
		{ 592, "Iron Clad" },
		{ 623, "Ironwork" },
		{ 171, "Irradiated Alert" },
		{ 303, "Isaac" },
		{ 357, "Ivory" },
		{ 316, "Jaguar" },
		{ 539, "Jambiya" },
		{ 340, "Jet Set" },
		{ 542, "Judgement of Anubis" },
		{ 202, "Jungle DDPAT" },
		{ 147, "Jungle Dashed" },
		{ 122, "Jungle Spray" },
		{ 16,  "Jungle Tiger" },
		{ 151, "Jungle" },
		{ 205, "Jungle" },
		{ 265, "Kami (Five-SeveN)" },
		{ 308, "Kami (Galil-AR)" },
		{ 504, "Kill Confirmed" },
		{ 326, "Knight" },
		{ 356, "Koi" },
		{ 527, "Kumicho Dragon" },
		{ 362, "Labyrinth" },
		{ 534, "Lapis Gator" },
		{ 540, "Lead Conduit" },
		{ 342, "Leather" },
		{ 26,  "Lichen Dashed" },
		{ 51,  "Lightning Strike" },
		{ 596, "Limelight" },
		{ 558, "Lore (Bayonet)" },
		{ 559, "Lore (Flip)" },
		{ 560, "Lore (Gut)" },
		{ 561, "Lore (Karambit)" },
		{ 562, "Lore (M9 Bayonet)" },
		{ 483, "Loudmouth" },
		{ 266, "Magma" },
		{ 402, "Malachite" },
		{ 395, "Man-o'-war (AWP)" },
		{ 432, "Man-o'-war (Negev)" },
		{ 413, "Marble Fade" },
		{ 261, "Marina" },
		{ 321, "Master Piece" },
		{ 200, "Mayan Dreams" },
		{ 587, "Mecha Industries (M4A1-S)" },
		{ 626, "Mecha Industries (Famas)" },
		{ 446, "Medusa" },
		{ 258, "Mehndi" },
		{ 177, "Memento" },
		{ 34,  "Metallic DDPAT" },
		{ 296, "Meteorite" },
		{ 468, "Midnight Storm" },
		{ 441, "Minotaur's Labyrinth" },
		{ 467, "Mint Kimono" },
		{ 164, "Modern Hunter" },
		{ 335, "Module" },
		{ 427, "Monkey Business" },
		{ 450, "Moon in Libra" },
		{ 204, "Mosaico" },
		{ 90,  "Mudder" },
		{ 404, "Muertos" },
		{ 382, "Murky" },
		{ 397, "Naga" },
		{ 496, "Nebula Crusader" },
		{ 538, "Necropos" },
		{ 481, "Nemesis" },
		{ 464, "Neon Kimono" },
		{ 600, "Neon Revolution" },
		{ 433, "Neon Rider" },
		{ 477, "Neural Net" },
		{ 236, "Night Ops" },
		{ 40,  "Night" },
		{ 223, "Nightshade" },
		{ 254, "Nitro" },
		{ 322, "Nitro" },
		{ 372, "Nuclear Garden" },
		{ 168, "Nuclear Threat" },
		{ 179, "Nuclear Threat" },
		{ 369, "Nuclear Waste" },
		{ 211, "Ocean Foam" },
		{ 213, "Ocean Foam" },
		{ 550, "Oceanic" },
		{ 365, "Olive Plaid" },
		{ 545, "Orange Crash" },
		{ 83,  "Orange DDPAT" },
		{ 465, "Orange Kimono" },
		{ 141, "Orange Peel" },
		{ 434, "Origami" },
		{ 313, "Orion" },
		{ 349, "Osiris" },
		{ 36,  "Ossified" },
		{ 518, "Outbreak" },
		{ 183, "Overgrowth" },
		{ 157, "Palm" },
		{ 201, "Palm" },
		{ 448, "Pandora's Box" },
		{ 276, "Panther" },
		{ 454, "Para Green" },
		{ 443, "Pathfinder" },
		{ 608, "Petroglyph" },
		{ 584, "Phobos" },
		{ 526, "Photic Zone" },
		{ 347, "Pilot" },
		{ 84,  "Pink DDPAT" },
		{ 251, "Pit Viper" },
		{ 506, "Point Disarray" },
		{ 315, "Poison Dart" },
		{ 74,  "Polar Camo" },
		{ 107, "Polar Mesh" },
		{ 435, "Pole Position" },
		{ 622, "Polymer" },
		{ 449, "Poseidon" },
		{ 514, "Power Loader" },
		{ 612, "Powercore" },
		{ 535, "Praetorian" },
		{ 170, "Predator" },
		{ 556, "Primal Saber" },
		{ 260, "Pulse" },
		{ 287, "Pulse" },
		{ 338, "Pulse" },
		{ 407, "Quicksilver" },
		{ 167, "Radiation Hazard" },
		{ 375, "Radiation Hazard" },
		{ 498, "Rangeen" },
		{ 484, "Ranger" },
		{ 555, "Re-Entry" },
		{ 367, "Reactor" },
		{ 595, "Reboot" },
		{ 543, "Red Astor" },
		{ 275, "Red FragCam" },
		{ 14,  "Red Laminate" },
		{ 348, "Red Leather" },
		{ 320, "Red Python" },
		{ 248, "Red Quartz" },
		{ 259, "Redline" },
		{ 282, "Redline" },
		{ 307, "Retribution" },
		{ 510, "Retrobution" },
		{ 507, "Ricochet" },
		{ 488, "Riot" },
		{ 263, "Rising Skull" },
		{ 318, "Road Rash" },
		{ 478, "Rocket Pop" },
		{ 604, "Roll Cage" },
		{ 262, "Rose Iron" },
		{ 332, "Royal Blue" },
		{ 625, "Royal Consorts" },
		{ 532, "Royal Legion" },
		{ 512, "Royal Paladin" },
		{ 482, "Ruby Poison Dart" },
		{ 203, "Rust Coat" },
		{ 323, "Rust Coat" },
		{ 414, "Rust Coat" },
		{ 72,  "Safari Mesh" },
		{ 119, "Sage Spray" },
		{ 148, "Sand Dashed" },
		{ 208, "Sand Dune" },
		{ 99,  "Sand Dune" },
		{ 116, "Sand Mesh" },
		{ 630, "Sand Scale" },
		{ 124, "Sand Spray" },
		{ 264, "Sandstorm" },
		{ 289, "Sandstorm" },
		{ 175, "Scorched" },
		{ 71,  "Scorpion" },
		{ 605, "Scumbria (Five-SeveN)" },
		{ 505, "Scumbria (XM1014)" },
		{ 473, "Seabird" },
		{ 405, "Serenity" },
		{ 288, "Sergeant" },
		{ 221, "Serum" },
		{ 368, "Setting Sun" },
		{ 636, "Shallow Grave" },
		{ 516, "Shapewood" },
		{ 192, "Shattered" },
		{ 452, "Shipping Forecast" },
		{ 252, "Silver Quartz" },
		{ 32,  "Silver" },
		{ 11,  "Skulls" },
		{ 304, "Slashed" },
		{ 59,  "Slaughter" },
		{ 616, "Slipstream" },
		{ 30,  "Snake Camo" },
		{ 633, "Sonar" },
		{ 500, "Special Delivery" },
		{ 547, "Spectre" },
		{ 194, "Spitfire" },
		{ 165, "Splash Jam" },
		{ 162, "Splash" },
		{ 43, "Stained" },
		{ 277, "Stainless" },
		{ 230, "Steel Disruption" },
		{ 628, "Stinger" },
		{ 494, "Stone Cold" },
		{ 100, "Storm" },
		{ 371, "Styx" },
		{ 451, "Sun in Leo" },
		{ 469, "Sunset Storm 壱"  },
		{ 470, "Sunset Storm 弐" },
		{ 358, "Supernova" },
		{ 492, "Survivor Z" },
		{ 601, "Syd Mead" },
		{ 401, "System Lock" },
		{ 337, "Tatter" },
		{ 244, "Teardown" },
		{ 521, "Teclu Burner" },
		{ 191, "Tempest" },
		{ 463, "Terrace" },
		{ 285, "Terrain" },
		{ 533, "The Battlestar" },
		{ 511, "The Executioner" },
		{ 269, "The Fuschia Is Now" },
		{ 256, "The Kraken" },
		{ 519, "Tiger Moth" },
		{ 409, "Tiger Tooth" },
		{ 350, "Tigris" },
		{ 272, "Titanium Bit" },
		{ 101, "Tornado" },
		{ 206, "Tornado" },
		{ 305, "Torque" },
		{ 489, "Torque" },
		{ 374, "Toxic" },
		{ 393, "Tranquility" },
		{ 363, "Traveler" },
		{ 268, "Tread Plate" },
		{ 613, "Triarch" },
		{ 283, "Trigon" },
		{ 530, "Triumvirate" },
		{ 233, "Tropical Storm" },
		{ 635, "Turf" },
		{ 297, "Tuxedo" },
		{ 437, "Twilight Galaxy" },
		{ 334, "Twist" },
		{ 98,  "Ultraviolet" },
		{ 271, "Undertow" },
		{ 17,  "Urban DDPAT" },
		{ 149, "Urban Dashed" },
		{ 354, "Urban Hazard" },
		{ 387, "Urban Hazard" },
		{ 143, "Urban Masked" },
		{ 135, "Urban Perforated" },
		{ 237, "Urban Rubble" },
		{ 396, "Urban Shock" },
		{ 426, "Valence" },
		{ 529, "Valence" },
		{ 238, "VariCamo Blue" },
		{ 235, "VariCamo" },
		{ 606, "Ventilator" },
		{ 544, "Ventilators" },
		{ 270, "Victoria" },
		{ 585, "Violent Daimyo" },
		{ 20,  "Virus" },
		{ 302, "Vulcan" },
		{ 158, "Walnut" },
		{ 380, "Wasteland Rebel (AK-47)" },
		{ 586, "Wasteland Rebel (Glock)" },
		{ 353, "Water Elemental" },
		{ 224, "Water Sigil" },
		{ 186, "Wave Spray" },
		{ 136, "Waves Perforated" },
		{ 607, "Weasel" },
		{ 102, "Whiteout" },
		{ 73,  "Wings" },
		{ 501, "Wingshot" },
		{ 76,  "Winter Forest" },
		{ 424, "Worm God" },
		{ 495, "Wraiths" },
		{ 215, "X-Ray" },
		{ 476, "Yellow Jacket" },
		{ 517, "Yorick" },
		{ 187, "Zirka" },
};
