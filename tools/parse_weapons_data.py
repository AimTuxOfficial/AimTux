#!/bin/python3
import re, glob

def parseFile(filename):
    lines = [ line.rstrip('\n') for line in open(filename) ]

    items = [
        [ "WeaponArmorRatio", "float" ],
        [ "Penetration", "float" ],
        [ "Damage", "int" ],
        [ "Range", "float" ],
        [ "RangeModifier", "float" ]
    ]
    itemsPrefixes = {
        "float": "m_fl",
        "int": "m_i"
    }
    sharedWeapons = {
        "WEAPON_M4A1": [ "WEAPON_M4A1_SILENCER" ]
    }

    weapon = filename[15:-4].upper()

    print("case %s:" % weapon)

    if weapon in sharedWeapons:
        for item in sharedWeapons[weapon]:
            print("case %s:" % item)

    for line in lines:
        for item in items:
            if item[0] in line:
                line = line.strip()
                line = re.sub(' +', ' ', line)
                line = re.sub('\t+', ' ', line)

                if line.split(" ")[0].replace("\"", "") == item[0]:
                    line = line.replace("  ", " ")
                    print("    weaponInfo.%s%s = %s;" % (itemsPrefixes[item[1]], item[0], line.split(" ")[1].replace("\"", "")))

    print("    break;")

skip = [
    "./csgo/scripts/weapon_manifest.txt",
    "./csgo/scripts/weapon_cubemap.txt",
    "./csgo/scripts/weapon_rifle.txt",
    "./csgo/scripts/weapon_healthshot.txt",
    "./csgo/scripts/weapon_knifegg.txt",
    "./csgo/scripts/weapon_tagrenade.txt"
]

for file in glob.glob('./csgo/scripts/weapon_*.txt'):
   if not file in skip:
       parseFile(file)
