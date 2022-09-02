#include "stdafx.h"
#include "SA2ModLoader.h"
#include "IniFile.hpp"
#include "mod.h"
#include "levels.h"

#include "stg03_greenforest/stg03_greenforest.h"
#include "stg10_metalharbor/stg10_metalharbor.h"
#include "stg13_cityescape/stg13_cityescape.h"

void LoadChunkLandManager(int a1, LandTable* land)
{
	LandTableSA2BModels = 0;
	LoadLandManager(land);
}

void Levels_Init(const IniFile* config)
{
	if (config->getBool("Levels", "GreenForest", true) == true)
	{
		STG03_INIT();
	}

	if (config->getBool("Levels", "MetalHarbor", true) == true)
	{
		STG10_INIT();
	}

	if (config->getBool("Levels", "CityEscape", true) == true)
	{
		STG13_INIT();
	}
}
