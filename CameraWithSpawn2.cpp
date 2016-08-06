// Fill out your copyright notice in the Description page of Project Settings.

#include "SunTemple.h"
#include "CameraWithSpawn.h"

#define CAPTURE_FINAL (1)

const int startVariationIndex = 148 * 11;

const TCHAR* objectList[NUM_OBJECT] = {
    // 1 個目 (InfinityBladeAdversaries)
    _T("/Game/Assets/Enemy_Bear_LOD0.Enemy_Bear_LOD0"),
    _T("/Game/Assets/Enemy_Bear_LOD1.Enemy_Bear_LOD1"),
    _T("/Game/Assets/Enemy_Bear_LOD2.Enemy_Bear_LOD2"),
    _T("/Game/Assets/Enemy_Bear_LOD3.Enemy_Bear_LOD3"),
    _T("/Game/Assets/Enemy_Bear_LOD4.Enemy_Bear_LOD4"),
    _T("/Game/Assets/Enemy_Bear_LOD5.Enemy_Bear_LOD5"),

    _T("/Game/Assets/SK_Elemental_Boss_Robot_LOD0.SK_Elemental_Boss_Robot_LOD0"),
    _T("/Game/Assets/SK_Elemental_Boss_Robot_LOD1.SK_Elemental_Boss_Robot_LOD1"),
    _T("/Game/Assets/SK_Elemental_Boss_Robot_LOD2.SK_Elemental_Boss_Robot_LOD2"),
    _T("/Game/Assets/SK_Elemental_Boss_Robot_LOD3.SK_Elemental_Boss_Robot_LOD3"),
    _T("/Game/Assets/SK_Elemental_Boss_Robot_LOD4.SK_Elemental_Boss_Robot_LOD4"),
    _T("/Game/Assets/SK_Elemental_Boss_Robot_LOD5.SK_Elemental_Boss_Robot_LOD5"),

    _T("/Game/Assets/S_Survival_CA_Chicken_LOD0.S_Survival_CA_Chicken_LOD0"),
    _T("/Game/Assets/S_Survival_CA_Chicken_LOD1.S_Survival_CA_Chicken_LOD1"),
    _T("/Game/Assets/S_Survival_CA_Chicken_LOD2.S_Survival_CA_Chicken_LOD2"),
    _T("/Game/Assets/S_Survival_CA_Chicken_LOD3.S_Survival_CA_Chicken_LOD3"),
    _T("/Game/Assets/S_Survival_CA_Chicken_LOD4.S_Survival_CA_Chicken_LOD4"),
    _T("/Game/Assets/S_Survival_CA_Chicken_LOD5.S_Survival_CA_Chicken_LOD5"),

    _T("/Game/Assets/SK_Enemy_Clot_Worm_LOD0.SK_Enemy_Clot_Worm_LOD0"),
    _T("/Game/Assets/SK_Enemy_Clot_Worm_LOD1.SK_Enemy_Clot_Worm_LOD1"),
    _T("/Game/Assets/SK_Enemy_Clot_Worm_LOD2.SK_Enemy_Clot_Worm_LOD2"),
    _T("/Game/Assets/SK_Enemy_Clot_Worm_LOD3.SK_Enemy_Clot_Worm_LOD3"),
    _T("/Game/Assets/SK_Enemy_Clot_Worm_LOD4.SK_Enemy_Clot_Worm_LOD4"),
    _T("/Game/Assets/SK_Enemy_Clot_Worm_LOD5.SK_Enemy_Clot_Worm_LOD5"),

    _T("/Game/Assets/SK_EXO_Creature_Spider02_LOD0.SK_EXO_Creature_Spider02_LOD0"),
    _T("/Game/Assets/SK_EXO_Creature_Spider02_LOD1.SK_EXO_Creature_Spider02_LOD1"),
    _T("/Game/Assets/SK_EXO_Creature_Spider02_LOD2.SK_EXO_Creature_Spider02_LOD2"),
    _T("/Game/Assets/SK_EXO_Creature_Spider02_LOD3.SK_EXO_Creature_Spider02_LOD3"),
    _T("/Game/Assets/SK_EXO_Creature_Spider02_LOD4.SK_EXO_Creature_Spider02_LOD4"),
    _T("/Game/Assets/SK_EXO_Creature_Spider02_LOD5.SK_EXO_Creature_Spider02_LOD5"),

    // 6 個目
    _T("/Game/Assets/SK_Enemy_FrostGiant_Captain_LOD0.SK_Enemy_FrostGiant_Captain_LOD0"),
    _T("/Game/Assets/SK_Enemy_FrostGiant_Captain_LOD1.SK_Enemy_FrostGiant_Captain_LOD1"),
    _T("/Game/Assets/SK_Enemy_FrostGiant_Captain_LOD2.SK_Enemy_FrostGiant_Captain_LOD2"),
    _T("/Game/Assets/SK_Enemy_FrostGiant_Captain_LOD3.SK_Enemy_FrostGiant_Captain_LOD3"),
    _T("/Game/Assets/SK_Enemy_FrostGiant_Captain_LOD4.SK_Enemy_FrostGiant_Captain_LOD4"),
    _T("/Game/Assets/SK_Enemy_FrostGiant_Captain_LOD5.SK_Enemy_FrostGiant_Captain_LOD5"),

    _T("/Game/Assets/SK_Fire_Golem_LOD0.SK_Fire_Golem_LOD0"),
    _T("/Game/Assets/SK_Fire_Golem_LOD1.SK_Fire_Golem_LOD1"),
    _T("/Game/Assets/SK_Fire_Golem_LOD2.SK_Fire_Golem_LOD2"),
    _T("/Game/Assets/SK_Fire_Golem_LOD3.SK_Fire_Golem_LOD3"),
    _T("/Game/Assets/SK_Fire_Golem_LOD4.SK_Fire_Golem_LOD4"),
    _T("/Game/Assets/SK_Fire_Golem_LOD5.SK_Fire_Golem_LOD5"),

    _T("/Game/Assets/SK_Greater_Spider_LOD0.SK_Greater_Spider_LOD0"),
    _T("/Game/Assets/SK_Greater_Spider_LOD1.SK_Greater_Spider_LOD1"),
    _T("/Game/Assets/SK_Greater_Spider_LOD2.SK_Greater_Spider_LOD2"),
    _T("/Game/Assets/SK_Greater_Spider_LOD3.SK_Greater_Spider_LOD3"),
    _T("/Game/Assets/SK_Greater_Spider_LOD4.SK_Greater_Spider_LOD4"),
    _T("/Game/Assets/SK_Greater_Spider_LOD5.SK_Greater_Spider_LOD5"),

    _T("/Game/Assets/SK_Greater_Spider_Boss_LOD0.SK_Greater_Spider_Boss_LOD0"),
    _T("/Game/Assets/SK_Greater_Spider_Boss_LOD1.SK_Greater_Spider_Boss_LOD1"),
    _T("/Game/Assets/SK_Greater_Spider_Boss_LOD2.SK_Greater_Spider_Boss_LOD2"),
    _T("/Game/Assets/SK_Greater_Spider_Boss_LOD3.SK_Greater_Spider_Boss_LOD3"),
    _T("/Game/Assets/SK_Greater_Spider_Boss_LOD4.SK_Greater_Spider_Boss_LOD4"),
    _T("/Game/Assets/SK_Greater_Spider_Boss_LOD5.SK_Greater_Spider_Boss_LOD5"),

    _T("/Game/Assets/SK_Exodus_Gruntling_LOD0.SK_Exodus_Gruntling_LOD0"),
    _T("/Game/Assets/SK_Exodus_Gruntling_LOD1.SK_Exodus_Gruntling_LOD1"),
    _T("/Game/Assets/SK_Exodus_Gruntling_LOD2.SK_Exodus_Gruntling_LOD2"),
    _T("/Game/Assets/SK_Exodus_Gruntling_LOD3.SK_Exodus_Gruntling_LOD3"),
    _T("/Game/Assets/SK_Exodus_Gruntling_LOD4.SK_Exodus_Gruntling_LOD4"),
    _T("/Game/Assets/SK_Exodus_Gruntling_LOD5.SK_Exodus_Gruntling_LOD5"),

    // 11 個目
    _T("/Game/Assets/SK_Gruntling_Avalanche_LOD0.SK_Gruntling_Avalanche_LOD0"),
    _T("/Game/Assets/SK_Gruntling_Avalanche_LOD1.SK_Gruntling_Avalanche_LOD1"),
    _T("/Game/Assets/SK_Gruntling_Avalanche_LOD2.SK_Gruntling_Avalanche_LOD2"),
    _T("/Game/Assets/SK_Gruntling_Avalanche_LOD3.SK_Gruntling_Avalanche_LOD3"),
    _T("/Game/Assets/SK_Gruntling_Avalanche_LOD4.SK_Gruntling_Avalanche_LOD4"),
    _T("/Game/Assets/SK_Gruntling_Avalanche_LOD5.SK_Gruntling_Avalanche_LOD5"),

    _T("/Game/Assets/SK_Gruntling_Glacer_LOD0.SK_Gruntling_Glacer_LOD0"),
    _T("/Game/Assets/SK_Gruntling_Glacer_LOD1.SK_Gruntling_Glacer_LOD1"),
    _T("/Game/Assets/SK_Gruntling_Glacer_LOD2.SK_Gruntling_Glacer_LOD2"),
    _T("/Game/Assets/SK_Gruntling_Glacer_LOD3.SK_Gruntling_Glacer_LOD3"),
    _T("/Game/Assets/SK_Gruntling_Glacer_LOD4.SK_Gruntling_Glacer_LOD4"),
    _T("/Game/Assets/SK_Gruntling_Glacer_LOD5.SK_Gruntling_Glacer_LOD5"),

    _T("/Game/Assets/SK_Gruntling_Guardian_LOD0.SK_Gruntling_Guardian_LOD0"),
    _T("/Game/Assets/SK_Gruntling_Guardian_LOD1.SK_Gruntling_Guardian_LOD1"),
    _T("/Game/Assets/SK_Gruntling_Guardian_LOD2.SK_Gruntling_Guardian_LOD2"),
    _T("/Game/Assets/SK_Gruntling_Guardian_LOD3.SK_Gruntling_Guardian_LOD3"),
    _T("/Game/Assets/SK_Gruntling_Guardian_LOD4.SK_Gruntling_Guardian_LOD4"),
    _T("/Game/Assets/SK_Gruntling_Guardian_LOD5.SK_Gruntling_Guardian_LOD5"),

    _T("/Game/Assets/SK_Gruntling_Scud_LOD0.SK_Gruntling_Scud_LOD0"),
    _T("/Game/Assets/SK_Gruntling_Scud_LOD1.SK_Gruntling_Scud_LOD1"),
    _T("/Game/Assets/SK_Gruntling_Scud_LOD2.SK_Gruntling_Scud_LOD2"),
    _T("/Game/Assets/SK_Gruntling_Scud_LOD3.SK_Gruntling_Scud_LOD3"),
    _T("/Game/Assets/SK_Gruntling_Scud_LOD4.SK_Gruntling_Scud_LOD4"),
    _T("/Game/Assets/SK_Gruntling_Scud_LOD5.SK_Gruntling_Scud_LOD5"),

    _T("/Game/Assets/SK_Master_Grunt_LOD0.SK_Master_Grunt_LOD0"),
    _T("/Game/Assets/SK_Master_Grunt_LOD1.SK_Master_Grunt_LOD1"),
    _T("/Game/Assets/SK_Master_Grunt_LOD2.SK_Master_Grunt_LOD2"),
    _T("/Game/Assets/SK_Master_Grunt_LOD3.SK_Master_Grunt_LOD3"),
    _T("/Game/Assets/SK_Master_Grunt_LOD4.SK_Master_Grunt_LOD4"),
    _T("/Game/Assets/SK_Master_Grunt_LOD5.SK_Master_Grunt_LOD5"),

    // 16 個目
    _T("/Game/Assets/SK_Robo_Golem_LOD0.SK_Robo_Golem_LOD0"),
    _T("/Game/Assets/SK_Robo_Golem_LOD1.SK_Robo_Golem_LOD1"),
    _T("/Game/Assets/SK_Robo_Golem_LOD2.SK_Robo_Golem_LOD2"),
    _T("/Game/Assets/SK_Robo_Golem_LOD3.SK_Robo_Golem_LOD3"),
    _T("/Game/Assets/SK_Robo_Golem_LOD4.SK_Robo_Golem_LOD4"),
    _T("/Game/Assets/SK_Robo_Golem_LOD5.SK_Robo_Golem_LOD5"),

    _T("/Game/Assets/SK_Spiderling_LOD0.SK_Spiderling_LOD0"),
    _T("/Game/Assets/SK_Spiderling_LOD1.SK_Spiderling_LOD1"),
    _T("/Game/Assets/SK_Spiderling_LOD2.SK_Spiderling_LOD2"),
    _T("/Game/Assets/SK_Spiderling_LOD3.SK_Spiderling_LOD3"),
    _T("/Game/Assets/SK_Spiderling_LOD4.SK_Spiderling_LOD4"),
    _T("/Game/Assets/SK_Spiderling_LOD5.SK_Spiderling_LOD5"),

    _T("/Game/Assets/Enemy_Task_Master_LOD0.Enemy_Task_Master_LOD0"),
    _T("/Game/Assets/Enemy_Task_Master_LOD1.Enemy_Task_Master_LOD1"),
    _T("/Game/Assets/Enemy_Task_Master_LOD2.Enemy_Task_Master_LOD2"),
    _T("/Game/Assets/Enemy_Task_Master_LOD3.Enemy_Task_Master_LOD3"),
    _T("/Game/Assets/Enemy_Task_Master_LOD4.Enemy_Task_Master_LOD4"),
    _T("/Game/Assets/Enemy_Task_Master_LOD5.Enemy_Task_Master_LOD5"),

    _T("/Game/Assets/SK_Troll_Poison_LOD0.SK_Troll_Poison_LOD0"),
    _T("/Game/Assets/SK_Troll_Poison_LOD1.SK_Troll_Poison_LOD1"),
    _T("/Game/Assets/SK_Troll_Poison_LOD2.SK_Troll_Poison_LOD2"),
    _T("/Game/Assets/SK_Troll_Poison_LOD3.SK_Troll_Poison_LOD3"),
    _T("/Game/Assets/SK_Troll_Poison_LOD4.SK_Troll_Poison_LOD4"),
    _T("/Game/Assets/SK_Troll_Poison_LOD5.SK_Troll_Poison_LOD5"),

    _T("/Game/Assets/SK_Enemy_Wolf_Armored_LOD0.SK_Enemy_Wolf_Armored_LOD0"),
    _T("/Game/Assets/SK_Enemy_Wolf_Armored_LOD1.SK_Enemy_Wolf_Armored_LOD1"),
    _T("/Game/Assets/SK_Enemy_Wolf_Armored_LOD2.SK_Enemy_Wolf_Armored_LOD2"),
    _T("/Game/Assets/SK_Enemy_Wolf_Armored_LOD3.SK_Enemy_Wolf_Armored_LOD3"),
    _T("/Game/Assets/SK_Enemy_Wolf_Armored_LOD4.SK_Enemy_Wolf_Armored_LOD4"),
    _T("/Game/Assets/SK_Enemy_Wolf_Armored_LOD5.SK_Enemy_Wolf_Armored_LOD5"),

    // 21 個目 (InfinityBladeWarriors) 
    _T("/Game/Assets/SK_CharM_Barbarous_LOD0.SK_CharM_Barbarous_LOD0"),
    _T("/Game/Assets/SK_CharM_Barbarous_LOD1.SK_CharM_Barbarous_LOD1"),
    _T("/Game/Assets/SK_CharM_Barbarous_LOD2.SK_CharM_Barbarous_LOD2"),
    _T("/Game/Assets/SK_CharM_Barbarous_LOD3.SK_CharM_Barbarous_LOD3"),
    _T("/Game/Assets/SK_CharM_Barbarous_LOD4.SK_CharM_Barbarous_LOD4"),
    _T("/Game/Assets/SK_CharM_Barbarous_LOD5.SK_CharM_Barbarous_LOD5"),

    _T("/Game/Assets/sk_CharM_Base_LOD0.sk_CharM_Base_LOD0"),
    _T("/Game/Assets/sk_CharM_Base_LOD1.sk_CharM_Base_LOD1"),
    _T("/Game/Assets/sk_CharM_Base_LOD2.sk_CharM_Base_LOD2"),
    _T("/Game/Assets/sk_CharM_Base_LOD3.sk_CharM_Base_LOD3"),
    _T("/Game/Assets/sk_CharM_Base_LOD4.sk_CharM_Base_LOD4"),
    _T("/Game/Assets/sk_CharM_Base_LOD5.sk_CharM_Base_LOD5"),

    _T("/Game/Assets/SK_CharM_Bladed_LOD0.SK_CharM_Bladed_LOD0"),
    _T("/Game/Assets/SK_CharM_Bladed_LOD1.SK_CharM_Bladed_LOD1"),
    _T("/Game/Assets/SK_CharM_Bladed_LOD2.SK_CharM_Bladed_LOD2"),
    _T("/Game/Assets/SK_CharM_Bladed_LOD3.SK_CharM_Bladed_LOD3"),
    _T("/Game/Assets/SK_CharM_Bladed_LOD4.SK_CharM_Bladed_LOD4"),
    _T("/Game/Assets/SK_CharM_Bladed_LOD5.SK_CharM_Bladed_LOD5"),

    _T("/Game/Assets/SK_CharM_Cardboard_LOD0.SK_CharM_Cardboard_LOD0"),
    _T("/Game/Assets/SK_CharM_Cardboard_LOD1.SK_CharM_Cardboard_LOD1"),
    _T("/Game/Assets/SK_CharM_Cardboard_LOD2.SK_CharM_Cardboard_LOD2"),
    _T("/Game/Assets/SK_CharM_Cardboard_LOD3.SK_CharM_Cardboard_LOD3"),
    _T("/Game/Assets/SK_CharM_Cardboard_LOD4.SK_CharM_Cardboard_LOD4"),
    _T("/Game/Assets/SK_CharM_Cardboard_LOD5.SK_CharM_Cardboard_LOD5"),

    _T("/Game/Assets/SK_CharM_Forge_LOD0.SK_CharM_Forge_LOD0"),
    _T("/Game/Assets/SK_CharM_Forge_LOD1.SK_CharM_Forge_LOD1"),
    _T("/Game/Assets/SK_CharM_Forge_LOD2.SK_CharM_Forge_LOD2"),
    _T("/Game/Assets/SK_CharM_Forge_LOD3.SK_CharM_Forge_LOD3"),
    _T("/Game/Assets/SK_CharM_Forge_LOD4.SK_CharM_Forge_LOD4"),
    _T("/Game/Assets/SK_CharM_Forge_LOD5.SK_CharM_Forge_LOD5"),

    // 26 個目
    _T("/Game/Assets/SK_CharM_FrostGiant_LOD0.SK_CharM_FrostGiant_LOD0"),
    _T("/Game/Assets/SK_CharM_FrostGiant_LOD1.SK_CharM_FrostGiant_LOD1"),
    _T("/Game/Assets/SK_CharM_FrostGiant_LOD2.SK_CharM_FrostGiant_LOD2"),
    _T("/Game/Assets/SK_CharM_FrostGiant_LOD3.SK_CharM_FrostGiant_LOD3"),
    _T("/Game/Assets/SK_CharM_FrostGiant_LOD4.SK_CharM_FrostGiant_LOD4"),
    _T("/Game/Assets/SK_CharM_FrostGiant_LOD5.SK_CharM_FrostGiant_LOD5"),

    _T("/Game/Assets/SK_CharM_Golden_LOD0.SK_CharM_Golden_LOD0"),
    _T("/Game/Assets/SK_CharM_Golden_LOD1.SK_CharM_Golden_LOD1"),
    _T("/Game/Assets/SK_CharM_Golden_LOD2.SK_CharM_Golden_LOD2"),
    _T("/Game/Assets/SK_CharM_Golden_LOD3.SK_CharM_Golden_LOD3"),
    _T("/Game/Assets/SK_CharM_Golden_LOD4.SK_CharM_Golden_LOD4"),
    _T("/Game/Assets/SK_CharM_Golden_LOD5.SK_CharM_Golden_LOD5"),

    _T("/Game/Assets/SK_CharM_Natural_LOD0.SK_CharM_Natural_LOD0"),
    _T("/Game/Assets/SK_CharM_Natural_LOD1.SK_CharM_Natural_LOD1"),
    _T("/Game/Assets/SK_CharM_Natural_LOD2.SK_CharM_Natural_LOD2"),
    _T("/Game/Assets/SK_CharM_Natural_LOD3.SK_CharM_Natural_LOD3"),
    _T("/Game/Assets/SK_CharM_Natural_LOD4.SK_CharM_Natural_LOD4"),
    _T("/Game/Assets/SK_CharM_Natural_LOD5.SK_CharM_Natural_LOD5"),

    _T("/Game/Assets/SK_CharM_Pit_LOD0.SK_CharM_Pit_LOD0"),
    _T("/Game/Assets/SK_CharM_Pit_LOD1.SK_CharM_Pit_LOD1"),
    _T("/Game/Assets/SK_CharM_Pit_LOD2.SK_CharM_Pit_LOD2"),
    _T("/Game/Assets/SK_CharM_Pit_LOD3.SK_CharM_Pit_LOD3"),
    _T("/Game/Assets/SK_CharM_Pit_LOD4.SK_CharM_Pit_LOD4"),
    _T("/Game/Assets/SK_CharM_Pit_LOD5.SK_CharM_Pit_LOD5"),

    _T("/Game/Assets/SK_CharM_Ragged0_LOD0.SK_CharM_Ragged0_LOD0"),
    _T("/Game/Assets/SK_CharM_Ragged0_LOD1.SK_CharM_Ragged0_LOD1"),
    _T("/Game/Assets/SK_CharM_Ragged0_LOD2.SK_CharM_Ragged0_LOD2"),
    _T("/Game/Assets/SK_CharM_Ragged0_LOD3.SK_CharM_Ragged0_LOD3"),
    _T("/Game/Assets/SK_CharM_Ragged0_LOD4.SK_CharM_Ragged0_LOD4"),
    _T("/Game/Assets/SK_CharM_Ragged0_LOD5.SK_CharM_Ragged0_LOD5"),

    // 31 個目
    _T("/Game/Assets/SK_CharM_RaggedElite_LOD0.SK_CharM_RaggedElite_LOD0"),
    _T("/Game/Assets/SK_CharM_RaggedElite_LOD1.SK_CharM_RaggedElite_LOD1"),
    _T("/Game/Assets/SK_CharM_RaggedElite_LOD2.SK_CharM_RaggedElite_LOD2"),
    _T("/Game/Assets/SK_CharM_RaggedElite_LOD3.SK_CharM_RaggedElite_LOD3"),
    _T("/Game/Assets/SK_CharM_RaggedElite_LOD4.SK_CharM_RaggedElite_LOD4"),
    _T("/Game/Assets/SK_CharM_RaggedElite_LOD5.SK_CharM_RaggedElite_LOD5"),

    _T("/Game/Assets/SK_CharM_Ram_LOD0.SK_CharM_Ram_LOD0"),
    _T("/Game/Assets/SK_CharM_Ram_LOD1.SK_CharM_Ram_LOD1"),
    _T("/Game/Assets/SK_CharM_Ram_LOD2.SK_CharM_Ram_LOD2"),
    _T("/Game/Assets/SK_CharM_Ram_LOD3.SK_CharM_Ram_LOD3"),
    _T("/Game/Assets/SK_CharM_Ram_LOD4.SK_CharM_Ram_LOD4"),
    _T("/Game/Assets/SK_CharM_Ram_LOD5.SK_CharM_Ram_LOD5"),

    _T("/Game/Assets/SK_CharM_Robo_LOD0.SK_CharM_Robo_LOD0"),
    _T("/Game/Assets/SK_CharM_Robo_LOD1.SK_CharM_Robo_LOD1"),
    _T("/Game/Assets/SK_CharM_Robo_LOD2.SK_CharM_Robo_LOD2"),
    _T("/Game/Assets/SK_CharM_Robo_LOD3.SK_CharM_Robo_LOD3"),
    _T("/Game/Assets/SK_CharM_Robo_LOD4.SK_CharM_Robo_LOD4"),
    _T("/Game/Assets/SK_CharM_Robo_LOD5.SK_CharM_Robo_LOD5"),

    _T("/Game/Assets/SK_CharM_Shell_LOD0.SK_CharM_Shell_LOD0"),
    _T("/Game/Assets/SK_CharM_Shell_LOD1.SK_CharM_Shell_LOD1"),
    _T("/Game/Assets/SK_CharM_Shell_LOD2.SK_CharM_Shell_LOD2"),
    _T("/Game/Assets/SK_CharM_Shell_LOD3.SK_CharM_Shell_LOD3"),
    _T("/Game/Assets/SK_CharM_Shell_LOD4.SK_CharM_Shell_LOD4"),
    _T("/Game/Assets/SK_CharM_Shell_LOD5.SK_CharM_Shell_LOD5"),

    _T("/Game/Assets/SK_CharM_solid_LOD0.SK_CharM_solid_LOD0"),
    _T("/Game/Assets/SK_CharM_solid_LOD1.SK_CharM_solid_LOD1"),
    _T("/Game/Assets/SK_CharM_solid_LOD2.SK_CharM_solid_LOD2"),
    _T("/Game/Assets/SK_CharM_solid_LOD3.SK_CharM_solid_LOD3"),
    _T("/Game/Assets/SK_CharM_solid_LOD4.SK_CharM_solid_LOD4"),
    _T("/Game/Assets/SK_CharM_solid_LOD5.SK_CharM_solid_LOD5"),

    // 36 個目
    _T("/Game/Assets/SK_CharM_Standard_LOD0.SK_CharM_Standard_LOD0"),
    _T("/Game/Assets/SK_CharM_Standard_LOD1.SK_CharM_Standard_LOD1"),
    _T("/Game/Assets/SK_CharM_Standard_LOD2.SK_CharM_Standard_LOD2"),
    _T("/Game/Assets/SK_CharM_Standard_LOD3.SK_CharM_Standard_LOD3"),
    _T("/Game/Assets/SK_CharM_Standard_LOD4.SK_CharM_Standard_LOD4"),
    _T("/Game/Assets/SK_CharM_Standard_LOD5.SK_CharM_Standard_LOD5"),

    _T("/Game/Assets/SK_CharM_Tusk_LOD0.SK_CharM_Tusk_LOD0"),
    _T("/Game/Assets/SK_CharM_Tusk_LOD1.SK_CharM_Tusk_LOD1"),
    _T("/Game/Assets/SK_CharM_Tusk_LOD2.SK_CharM_Tusk_LOD2"),
    _T("/Game/Assets/SK_CharM_Tusk_LOD3.SK_CharM_Tusk_LOD3"),
    _T("/Game/Assets/SK_CharM_Tusk_LOD4.SK_CharM_Tusk_LOD4"),
    _T("/Game/Assets/SK_CharM_Tusk_LOD5.SK_CharM_Tusk_LOD5"),

    // 38 個目 (KiteDemo)
    /*
    _T("/Game/Assets/SM_Cliff01_LOD0.SM_Cliff01_LOD0"),
    _T("/Game/Assets/SM_Cliff01_LOD1.SM_Cliff01_LOD1"),
    _T("/Game/Assets/SM_Cliff01_LOD2.SM_Cliff01_LOD2"),
    _T("/Game/Assets/SM_Cliff01_LOD3.SM_Cliff01_LOD3"),
    _T("/Game/Assets/SM_Cliff01_LOD4.SM_Cliff01_LOD4"),
    _T("/Game/Assets/SM_Cliff01_LOD5.SM_Cliff01_LOD5"),

    _T("/Game/Assets/BogMyrtle_01_LOD0.BogMyrtle_01_LOD0"),
    _T("/Game/Assets/BogMyrtle_01_LOD1.BogMyrtle_01_LOD1"),
    _T("/Game/Assets/BogMyrtle_01_LOD2.BogMyrtle_01_LOD2"),
    _T("/Game/Assets/BogMyrtle_01_LOD3.BogMyrtle_01_LOD3"),
    _T("/Game/Assets/BogMyrtle_01_LOD4.BogMyrtle_01_LOD4"),
    _T("/Game/Assets/BogMyrtle_01_LOD5.BogMyrtle_01_LOD5"),

    _T("/Game/Assets/BogMyrtleBush_01_LOD0.BogMyrtleBush_01_LOD0"),
    _T("/Game/Assets/BogMyrtleBush_01_LOD1.BogMyrtleBush_01_LOD1"),
    _T("/Game/Assets/BogMyrtleBush_01_LOD2.BogMyrtleBush_01_LOD2"),
    _T("/Game/Assets/BogMyrtleBush_01_LOD3.BogMyrtleBush_01_LOD3"),
    _T("/Game/Assets/BogMyrtleBush_01_LOD4.BogMyrtleBush_01_LOD4"),
    _T("/Game/Assets/BogMyrtleBush_01_LOD5.BogMyrtleBush_01_LOD5"),

    // 41 個目
    _T("/Game/Assets/SM_Fern_01_LOD0.SM_Fern_01_LOD0"),
    _T("/Game/Assets/SM_Fern_01_LOD1.SM_Fern_01_LOD1"),
    _T("/Game/Assets/SM_Fern_01_LOD2.SM_Fern_01_LOD2"),
    _T("/Game/Assets/SM_Fern_01_LOD3.SM_Fern_01_LOD3"),
    _T("/Game/Assets/SM_Fern_01_LOD4.SM_Fern_01_LOD4"),
    _T("/Game/Assets/SM_Fern_01_LOD5.SM_Fern_01_LOD5"),

    _T("/Game/Assets/SM_FieldScabious_01_LOD0.SM_FieldScabious_01_LOD0"),
    _T("/Game/Assets/SM_FieldScabious_01_LOD1.SM_FieldScabious_01_LOD1"),
    _T("/Game/Assets/SM_FieldScabious_01_LOD2.SM_FieldScabious_01_LOD2"),
    _T("/Game/Assets/SM_FieldScabious_01_LOD3.SM_FieldScabious_01_LOD3"),
    _T("/Game/Assets/SM_FieldScabious_01_LOD4.SM_FieldScabious_01_LOD4"),
    _T("/Game/Assets/SM_FieldScabious_01_LOD5.SM_FieldScabious_01_LOD5"),

    _T("/Game/Assets/SM_Yarrow3_LOD0.SM_Yarrow3_LOD0"),
    _T("/Game/Assets/SM_Yarrow3_LOD1.SM_Yarrow3_LOD1"),
    _T("/Game/Assets/SM_Yarrow3_LOD2.SM_Yarrow3_LOD2"),
    _T("/Game/Assets/SM_Yarrow3_LOD3.SM_Yarrow3_LOD3"),
    _T("/Game/Assets/SM_Yarrow3_LOD4.SM_Yarrow3_LOD4"),
    _T("/Game/Assets/SM_Yarrow3_LOD5.SM_Yarrow3_LOD5"),

    _T("/Game/Assets/SM_FieldGrass_01_LOD0.SM_FieldGrass_01_LOD0"),
    _T("/Game/Assets/SM_FieldGrass_01_LOD1.SM_FieldGrass_01_LOD1"),
    _T("/Game/Assets/SM_FieldGrass_01_LOD2.SM_FieldGrass_01_LOD2"),
    _T("/Game/Assets/SM_FieldGrass_01_LOD3.SM_FieldGrass_01_LOD3"),
    _T("/Game/Assets/SM_FieldGrass_01_LOD4.SM_FieldGrass_01_LOD4"),
    _T("/Game/Assets/SM_FieldGrass_01_LOD5.SM_FieldGrass_01_LOD5"),

    _T("/Game/Assets/SM_Boulder05a_LOD0.SM_Boulder05a_LOD0"),
    _T("/Game/Assets/SM_Boulder05a_LOD1.SM_Boulder05a_LOD1"),
    _T("/Game/Assets/SM_Boulder05a_LOD2.SM_Boulder05a_LOD2"),
    _T("/Game/Assets/SM_Boulder05a_LOD3.SM_Boulder05a_LOD3"),
    _T("/Game/Assets/SM_Boulder05a_LOD4.SM_Boulder05a_LOD4"),
    _T("/Game/Assets/SM_Boulder05a_LOD5.SM_Boulder05a_LOD5"),

    // 46 個目 (KiteDemo)
    _T("/Game/Assets/SM_GroundRevealRock001_LOD0.SM_GroundRevealRock001_LOD0"),
    _T("/Game/Assets/SM_GroundRevealRock001_LOD1.SM_GroundRevealRock001_LOD1"),
    _T("/Game/Assets/SM_GroundRevealRock001_LOD2.SM_GroundRevealRock001_LOD2"),
    _T("/Game/Assets/SM_GroundRevealRock001_LOD3.SM_GroundRevealRock001_LOD3"),
    _T("/Game/Assets/SM_GroundRevealRock001_LOD4.SM_GroundRevealRock001_LOD4"),
    _T("/Game/Assets/SM_GroundRevealRock001_LOD5.SM_GroundRevealRock001_LOD5"),

    _T("/Game/Assets/SM_GroundRevealRock002_LOD0.SM_GroundRevealRock002_LOD0"),
    _T("/Game/Assets/SM_GroundRevealRock002_LOD1.SM_GroundRevealRock002_LOD1"),
    _T("/Game/Assets/SM_GroundRevealRock002_LOD2.SM_GroundRevealRock002_LOD2"),
    _T("/Game/Assets/SM_GroundRevealRock002_LOD3.SM_GroundRevealRock002_LOD3"),
    _T("/Game/Assets/SM_GroundRevealRock002_LOD4.SM_GroundRevealRock002_LOD4"),
    _T("/Game/Assets/SM_GroundRevealRock002_LOD5.SM_GroundRevealRock002_LOD5"),

    _T("/Game/Assets/LargeVolcanicRock_001_LOD0.LargeVolcanicRock_001_LOD0"),
    _T("/Game/Assets/LargeVolcanicRock_001_LOD1.LargeVolcanicRock_001_LOD1"),
    _T("/Game/Assets/LargeVolcanicRock_001_LOD2.LargeVolcanicRock_001_LOD2"),
    _T("/Game/Assets/LargeVolcanicRock_001_LOD3.LargeVolcanicRock_001_LOD3"),
    _T("/Game/Assets/LargeVolcanicRock_001_LOD4.LargeVolcanicRock_001_LOD4"),
    _T("/Game/Assets/LargeVolcanicRock_001_LOD5.LargeVolcanicRock_001_LOD5"),

    _T("/Game/Assets/Medium_Boulder_001_LOD0.Medium_Boulder_001_LOD0"),
    _T("/Game/Assets/Medium_Boulder_001_LOD1.Medium_Boulder_001_LOD1"),
    _T("/Game/Assets/Medium_Boulder_001_LOD2.Medium_Boulder_001_LOD2"),
    _T("/Game/Assets/Medium_Boulder_001_LOD3.Medium_Boulder_001_LOD3"),
    _T("/Game/Assets/Medium_Boulder_001_LOD4.Medium_Boulder_001_LOD4"),
    _T("/Game/Assets/Medium_Boulder_001_LOD5.Medium_Boulder_001_LOD5"),

    _T("/Game/Assets/ScotsPineTall_01_LOD0.ScotsPineTall_01_LOD0"),
    _T("/Game/Assets/ScotsPineTall_01_LOD1.ScotsPineTall_01_LOD1"),
    _T("/Game/Assets/ScotsPineTall_01_LOD2.ScotsPineTall_01_LOD2"),
    _T("/Game/Assets/ScotsPineTall_01_LOD3.ScotsPineTall_01_LOD3"),
    _T("/Game/Assets/ScotsPineTall_01_LOD4.ScotsPineTall_01_LOD4"),
    _T("/Game/Assets/ScotsPineTall_01_LOD5.ScotsPineTall_01_LOD5"),

    // 51 個目 (KiteDemo)
    _T("/Game/Assets/Tree_Stump_01_LOD0.Tree_Stump_01_LOD0"),
    _T("/Game/Assets/Tree_Stump_01_LOD1.Tree_Stump_01_LOD1"),
    _T("/Game/Assets/Tree_Stump_01_LOD2.Tree_Stump_01_LOD2"),
    _T("/Game/Assets/Tree_Stump_01_LOD3.Tree_Stump_01_LOD3"),
    _T("/Game/Assets/Tree_Stump_01_LOD4.Tree_Stump_01_LOD4"),
    _T("/Game/Assets/Tree_Stump_01_LOD5.Tree_Stump_01_LOD5"),

    _T("/Game/Assets/SM_Vegetation_Debris_002_LOD0.SM_Vegetation_Debris_002_LOD0"),
    _T("/Game/Assets/SM_Vegetation_Debris_002_LOD1.SM_Vegetation_Debris_002_LOD1"),
    _T("/Game/Assets/SM_Vegetation_Debris_002_LOD2.SM_Vegetation_Debris_002_LOD2"),
    _T("/Game/Assets/SM_Vegetation_Debris_002_LOD3.SM_Vegetation_Debris_002_LOD3"),
    _T("/Game/Assets/SM_Vegetation_Debris_002_LOD4.SM_Vegetation_Debris_002_LOD4"),
    _T("/Game/Assets/SM_Vegetation_Debris_002_LOD5.SM_Vegetation_Debris_002_LOD5"),
    */
};

const TCHAR* materialList[NUM_MATERIAL] = {
    // 1 個目 (InfinityBladeAdversaries)
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Bear/Materials/M_Bear_Master.M_Bear_Master"),
    _T("/Game/InfinityBladeAdversaries/Enemy/Elemental_Robot/Materials/M_Elemental_Robot_Master.M_Elemental_Robot_Master"),
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Chicken/Materials/M_EnemyChicken.M_EnemyChicken"),
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Clot_Worm/Materials/M_Clot_Worm.M_Clot_Worm"),
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Creature_Spider/Materials/CharM_Creature_Spider.CharM_Creature_Spider"),
    // 6 個目
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Frost_Giant/Materials/CharM_Frost_Giant.CharM_Frost_Giant"),
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Golem/Materials/CharM_Fire_Golem.CharM_Fire_Golem"),
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Great_Spider/Materials/CharM_Greater_Spider.CharM_Greater_Spider"),
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Greater_Spider_Boss/Materials/CharM_Greater_Spider_Boss.CharM_Greater_Spider_Boss"),
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Gruntling/Materials/CharM_Gruntling.CharM_Gruntling"),
    // 11 個目
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Gruntling_Avalanche/Materials/CharM_Gruntling_Avalanche.CharM_Gruntling_Avalanche"),
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Gruntling_Glacer/Materials/CharM_Gruntling_Glacer.CharM_Gruntling_Glacer"),
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Gruntling_Guardian/Materials/CharM_Gruntling_Guardian.CharM_Gruntling_Guardian"),
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Gruntling_Scud/Materials/CharM_Gruntling_Scud_C.CharM_Gruntling_Scud_C"),
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Master_Grunt/Materials/CharM_Master_Grunt.CharM_Master_Grunt"),
    // 16 個目
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Robo_Golem/Materials/CharM_Robo_Golem.CharM_Robo_Golem"),
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Spiderling/Materials/CharM_Spiderling.CharM_Spiderling"),
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Task_Master/Materials/M_Enemy_Task_Master.M_Enemy_Task_Master"),
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Troll/Materials/CharM_Troll.CharM_Troll"),
    _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Wolf/Materials/CharM_Enemy_Wolf.CharM_Enemy_Wolf"),

    // 21 個目 (InfinityBladeWarriors) 
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Barbarous/M_Char_Barbrous.M_Char_Barbrous"),
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Base/M_CharM_Base.M_CharM_Base"),
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Bladed/M_CharM_Bladed.M_CharM_Bladed"),
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Cardboard/M_Char_Cardboard.M_Char_Cardboard"),
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Forge/M_Char_Forge.M_Char_Forge"),
    // 26 個目
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_FrostGiant/M_Char_FrostGiant.M_Char_FrostGiant"),
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Golden/M_Char_Golden.M_Char_Golden"),
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Natural/M_Char_Natural.M_Char_Natural"),
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Pit/M_Char_Pit.M_Char_Pit"),
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Ragged/M_Char_RaggedElite.M_Char_RaggedElite"),
    // 31 個目
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Ram/M_Char_Ram.M_Char_Ram"),
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Robo/M_Char_Robo.M_Char_Robo"),
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Shell/M_Char_Shell.M_Char_Shell"),
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_solid/M_CharM_Solid_Alternate.M_CharM_Solid_Alternate"),
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Standard/M_Char_Standard_Elite.M_Char_Standard_Elite"),
    // 36 個目
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Tusk/M_Char_Horn.M_Char_Horn"),
    _T("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Warrior/M_Char_Warrior.M_Char_Warrior"),

    // 38 個目 (KiteDemo)
    /*
    _T("/Game/KiteDemo/Environments/Cliffs/Cliff01/MI_Cliff01.MI_Cliff01"),
    _T("/Game/KiteDemo/Environments/Foliage/BogMyrtle_01/BogMyrtle_01_Fronds_Mat.BogMyrtle_01_Fronds_Mat"),
    _T("/Game/KiteDemo/Environments/Foliage/BogMyrtleBush_01/MI_BogMyrtleBush_01_Billboard.MI_BogMyrtleBush_01_Billboard"),
    // 41 個目
    _T("/Game/KiteDemo/Environments/Foliage/Ferns/M_Fern_01.M_Fern_01"),
    _T("/Game/KiteDemo/Environments/Foliage/Flowers/FieldScabious/M_FieldScabious_01.M_FieldScabious_01"),
    _T("/Game/KiteDemo/Environments/Foliage/Flowers/Yarrow/M_Yarrow_Inst.M_Yarrow_Inst"),
    _T("/Game/KiteDemo/Environments/Foliage/Grass/FieldGrass/M_FieldGrass_01.M_FieldGrass_01"),
    _T("/Game/KiteDemo/Environments/Rocks/Boulder_05a/MI_Boulder05a.MI_Boulder05a"),
    // 46 個目
    _T("/Game/KiteDemo/Environments/Rocks/GroundRevealRock001/MI_GroundRevealRock001a.MI_GroundRevealRock001a"),
    _T("/Game/KiteDemo/Environments/Rocks/GroundRevealRock002/MI_GroundRevealRock002.MI_GroundRevealRock002"),
    _T("/Game/KiteDemo/Environments/Rocks/Large_Volcanic_Rock_001/MI_Large_VolcanicRock_002.MI_Large_VolcanicRock_002"),
    _T("/Game/KiteDemo/Environments/Rocks/Medium_Boulder_001/MI_MediumBoulder_0012.MI_MediumBoulder_0012"),
    _T("/Game/KiteDemo/Environments/Trees/ScotsPineTall_01/ScotsPineTall_01_Billboard_Mat.ScotsPineTall_01_Billboard_Mat"),
    // 51 個目
    _T("/Game/KiteDemo/Environments/Trees/Tree_Stump_01/MI_Tree_Stump_01.MI_Tree_Stump_01"),
    _T("/Game/KiteDemo/Environments/Trees/Vegetation_Debris_002/MI_Vegetation_Debris_002.MI_Vegetation_Debris_002"),
    */
};

const float scaleList[NUM_MATERIAL] = {
    1.0f, 1.2f, 8.0f, 1.0f, 1.3f, 0.7f, 1.3f, 0.9f, 0.7f, 1.9f,
    1.8f, 1.9f, 2.0f, 2.0f, 1.1f, 0.6f, 1.2f, 1.0f, 0.9f, 1.3f,
    1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f,
    1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f, /*0.3f, 2.5f, 3.0f,
                                              2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                              1.0f, 1.0f,*/
};

const float xRotateList[NUM_MATERIAL] = {
    0.0f, -90.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, /*0.0f, 0.0f, 0.0f,
                                                0.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                                0.0f,   0.0f,*/
};

// Sets default values
ACameraWithSpawn::ACameraWithSpawn(const FObjectInitializer& ObjectInitializer)
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Set this pawn to be controlled by the lowest-numbered player (このポーンが最小値のプレイヤーで制御されるように設定)
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    // ダミーキャラクターを置く
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    // Create a dummy root component we can attach things to.(親子付け可能なダミーのルートコンポーネントを作成)
    UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));

    // Attach our camera and visible object to our root component. (カメラと可視オブジェクトをルートコンポーネントに親子付け。カメラをオフセットして回転)
    OurCamera->AttachTo(RootComponent);
    OurCamera->SetRelativeLocation(FVector(-350.0f, 0.0f, 100.0f));
    OurCamera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

    for (size_t i = 0; i < NUM_MATERIAL; i++)
    {
        ConstructorHelpers::FObjectFinder<UMaterial>* pMaterialAsset = new ConstructorHelpers::FObjectFinder<UMaterial>(materialList[i]);
        if (pMaterialAsset->Succeeded())
        {
            mMaterial[i] = pMaterialAsset->Object;
            UE_LOG(LogTemp, Warning, TEXT("output : %s %s"), materialList[i], L"マテリアルロードに成功しました");
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("output : %s %s"), materialList[i], L"マテリアルロードに失敗しました");
        }
    }

    materialIndex = variationIndex = 0;
    for (size_t i = 0; i < NUM_OBJECT; i++)
    {
        ConstructorHelpers::FObjectFinder<UStaticMesh>* pMeshAsset = new ConstructorHelpers::FObjectFinder<UStaticMesh>(objectList[i]);
        if (pMeshAsset->Succeeded())
        {
            mStaticMesh[i] = pMeshAsset->Object;
            mStaticMesh[i]->Materials[0] = mMaterial[i / NUM_LOD];
            UE_LOG(LogTemp, Warning, TEXT("output : %s %s"), objectList[i], L"メッシュロードに成功しました");
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("output : %s %s"), objectList[i], L"メッシュロードに失敗しました");
        }
    }

    mStaticMeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMeshName"));
    // オブジェクトが生成出来ました
    if (mStaticMeshComponent)
    {
        mStaticMeshComponent->SetStaticMesh(mStaticMesh[0]);
        mStaticMeshComponent->AttachTo(RootComponent);
    }
}

// Called when the game starts or when spawned
void ACameraWithSpawn::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ACameraWithSpawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bStartCapture)
    {
#if CAPTURE_FINAL
        const float timeToNextObject = 0.1f;
#else
        const float timeToNextObject = 0.05f;
#endif
        if (objectIndex == NUM_OBJECT)
        {
            // キャプチャを終了する
            bStartCapture = false;
            accumulateTime = 0;
            objectIndex = remeshIndex = materialIndex = 0;
            mStaticMeshComponent->SetStaticMesh(mStaticMesh[0]);
            mStaticMeshComponent->SetRelativeScale3D(FVector(scaleList[materialIndex]));
            mStaticMeshComponent->SetRelativeRotation(FRotator(0.0f, currentYRotation, 0.0f));
        }
        else if ((accumulateTime > timeToNextObject / 2) && screenShotFlag)
        {
            TCHAR tmpchar[128];
            FString filename;
            // 比較を行うバリエーション / リメッシュのバリエーション
            if (!firstObjectFlag)
            {
                _stprintf_s(tmpchar, sizeof(tmpchar), _T("%.7d_%.1d.png"), startVariationIndex + variationIndex, remeshIndex);
                filename.AppendChars(tmpchar, sizeof(tmpchar));

                // スクリーンショットの撮影
                FScreenshotRequest screenshot = FScreenshotRequest();
                screenshot.RequestScreenshot(filename, false, false);
            }
            else {
                firstObjectFlag = false;
                variationIndex--;
            }
            screenShotFlag = false;
        }
        else if (accumulateTime > timeToNextObject)
        {
            if (currentYRotation > 270.0f)
            {
                objectIndex++; remeshIndex++;
                if (remeshIndex == NUM_LOD)
                {
                    // 次のジオメトリに飛ぶ
                    remeshIndex = 0;
                    variationIndex++;
                    materialIndex++;
                    currentYRotation = FMath::RandRange(0.1f, 89.f);
#if CAPTURE_FINAL
                    accumulateTime = -1.0f;
#endif
                }
                else
                {
                    // 次のリメッシュに飛ぶ
                    variationIndex -= 3;
                    currentYRotation -= 270.0f;
                    accumulateTime = 0.0f;
#if CAPTURE_FINAL
                    accumulateTime = -0.1f;
#endif
                }
                UE_LOG(LogTemp, Warning, TEXT("object index is %d"), objectIndex);
                mStaticMeshComponent->SetStaticMesh(mStaticMesh[objectIndex]);
            }
            else
            {
                // ローテーションのバリエーションを行う
                variationIndex++;
                accumulateTime = 0.0f;
                currentYRotation += 90.0f;
#if CAPTURE_FINAL
                accumulateTime = -0.1f;
#endif
            }
            mStaticMeshComponent->SetRelativeScale3D(FVector(scaleList[materialIndex]));
            mStaticMeshComponent->SetRelativeRotation(FRotator(0.0f, currentYRotation, 0.0f));

            screenShotFlag = true;
        }
        else {
            accumulateTime += DeltaTime;
        }
    }
    // Handle growing and shrinking based on our "Grow" action (Grow アクションに基づいて拡大と縮小を処理)
    else
    {
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw += CameraInput.X;
        SetActorRotation(NewRotation);

        if (!MovementInput.IsZero())
        {
            //Scale our movement input axis values by 100 units per second (移動入力軸の値を 1 秒あたり 100 単位でスケーリング)
            MovementInput = MovementInput.SafeNormal() * 100.0f;
            FVector NewLocation = GetActorLocation();
            NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime * 5.0f;
            NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime * 5.0f;
            SetActorLocation(NewLocation);
        }
    }
}

// Called to bind functionality to input
void ACameraWithSpawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);

    //Hook up every-frame handling for our four axes (4 つの軸に各フレーム処理を接続)
    InputComponent->BindAxis("MoveForward", this, &ACameraWithSpawn::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &ACameraWithSpawn::MoveRight);
    InputComponent->BindAxis("CameraPitch", this, &ACameraWithSpawn::PitchCamera);
    InputComponent->BindAxis("CameraYaw", this, &ACameraWithSpawn::YawCamera);

    // Respond when our "Grow" key is pressed or released. (StartCapture キーがリリースされた時に反応)
    InputComponent->BindAction("StartCapture", IE_Pressed, this, &ACameraWithSpawn::StartCapture);
}

//Input functions (入力関数)
void ACameraWithSpawn::MoveForward(float AxisValue)
{
    MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void ACameraWithSpawn::MoveRight(float AxisValue)
{
    MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void ACameraWithSpawn::PitchCamera(float AxisValue)
{
    CameraInput.Y = AxisValue;
}

void ACameraWithSpawn::YawCamera(float AxisValue)
{
    CameraInput.X = AxisValue;
}

void ACameraWithSpawn::StartCapture()
{
    UE_LOG(LogTemp, Warning, TEXT("start capture"));
    accumulateTime = 0;
    objectIndex = 0;
    bStartCapture = screenShotFlag = firstObjectFlag = true;
    materialIndex = remeshIndex = 0;
    currentYRotation = 0.1f;
}