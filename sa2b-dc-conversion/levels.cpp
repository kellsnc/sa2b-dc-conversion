#include "stdafx.h"
#include <SA2ModLoader.h>
#include <LandTableInfo.h>
#include <string>
#include "mod.h"
#include "levels.h"

void LoadChunkLandManager(int a1, LandTable* land)
{
	LandTableSA2BModels = 0;
	LoadLandManager(land);
}

void LoadLandTableFile(LandTableInfo** info, const char* name)
{
	std::string fullPath = "resource\\gd_PC\\" + (std::string)name + ".sa2lvl";

	LandTableInfo* lnd = new LandTableInfo(gHelperFunctions->GetReplaceablePath(fullPath.c_str()));

	if (lnd->getlandtable() == nullptr)
	{
		PrintDebug("[DC] Error: failed to load LandTable \"%s\".\n", name);
		delete lnd;
		*info = nullptr;
	}
	else
	{
		PrintDebug("[DC] Successfully loaded LandTable \"%s\".\n", name);
		*info = lnd;
	}
}

void FreeLandTableFile(LandTableInfo** info)
{
	if (*info)
	{
		delete* info;
		info = nullptr;
	}
}

void SetLandTableTexInfo(LandTableInfo* info, NJS_TEXLIST* texlist, const char* name)
{
	auto land = info->getlandtable();

	if (land)
	{
		land->TextureList = texlist;
		land->TextureName = name;
	}
}