#include "stdafx.h"
#include <SA2ModLoader.h>
#include <LandTableInfo.h>
#include <Trampoline.h>
#include "..\common.h"
#include "..\levels.h"
#include "stg03_greenforest.h"

static ColorMap GreenForestColorMap[]
{
	{ 0xFF000000, 0xFFFFFFFF },
	{ 0xFFFFFF00, 0x18432 },
	{ 0xFFFF0000, 0x3D826 },
	{ 0xFFFF00FF, 0xC0104 },
	{ 0xFF00FFFF, 0x830C },
	{ 0xFFFF7D00, 0x46008 },
	{ 0xFF0000FF, 0x218 },
	{ 0xFF007D00, 0x60CD0 },
	{ 0xFF7D007D, 0x10860 },
	{ 0xFF7D0000, 0x3040 },
	{ 0xFF007D7D, 0x1080 },
	{ 0xFF00FF00, 0x4200 },
	{ 0xFF00007D, 0x2180 }
};

static NJS_VECTOR GreenForest_MapOffset = { -3000.0f, 0.0f, 16640.0f };
static NJS_VECTOR GreenForest_MapUnit = { 33.14917f, 0.0f, 33.203125 };

static NJS_TEXNAME LANDTX03_DC_TEXNAMES[] {
	{ (void*)"jungle128_1", 0, 0 },
	{ (void*)"jungle128_10", 0, 0 },
	{ (void*)"jungle128_11", 0, 0 },
	{ (void*)"jungle128_12", 0, 0 },
	{ (void*)"jungle128_13", 0, 0 },
	{ (void*)"jungle128_14", 0, 0 },
	{ (void*)"jungle128_15", 0, 0 },
	{ (void*)"jungle128_3", 0, 0 },
	{ (void*)"jungle128_4", 0, 0 },
	{ (void*)"jungle128_5", 0, 0 },
	{ (void*)"jungle128_6", 0, 0 },
	{ (void*)"jungle128_7", 0, 0 },
	{ (void*)"jungle128_8", 0, 0 },
	{ (void*)"jungle128_9", 0, 0 },
	{ (void*)"jungle256_1", 0, 0 },
	{ (void*)"jungle256_2", 0, 0 },
	{ (void*)"jungle256_4", 0, 0 },
	{ (void*)"jungle256_5", 0, 0 },
	{ (void*)"jungle256_6", 0, 0 },
	{ (void*)"jungle256_9", 0, 0 },
	{ (void*)"jungle64_1", 0, 0 },
	{ (void*)"jungle64_2", 0, 0 },
	{ (void*)"jungle64_3", 0, 0 },
	{ (void*)"jungle64_4", 0, 0 },
	{ (void*)"txJungle001", 0, 0 },
	{ (void*)"txJungle002", 0, 0 },
	{ (void*)"txJungle003", 0, 0 },
	{ (void*)"txJungle004", 0, 0 },
	{ (void*)"txJungle005", 0, 0 },
	{ (void*)"txJungle006", 0, 0 },
	{ (void*)"txJungle007", 0, 0 },
	{ (void*)"txJungle008", 0, 0 },
	{ (void*)"txJungle009", 0, 0 },
	{ (void*)"txJungle010", 0, 0 },
	{ (void*)"txJungle011", 0, 0 },
	{ (void*)"txJungle012", 0, 0 },
	{ (void*)"txJungle013", 0, 0 },
	{ (void*)"txJungle014", 0, 0 },
};

static NJS_TEXLIST LANDTX03_DC_TEXLIST = { arrayptrandlength(LANDTX03_DC_TEXNAMES) };

static Trampoline* GreenForest_Init_t;
static Trampoline* GreenForest_Free_t;

static LandTableInfo* GreenForestLandInfo;

static void __cdecl GreenForest_Init_r()
{
	LoadLandTableFile(&GreenForestLandInfo, "stg03_dc");
	SetLandTableTexInfo(GreenForestLandInfo, &LANDTX03_DC_TEXLIST, "LANDTX03_DC");
	DataDLL_Set<LandTable>("objLandTable0003", GreenForestLandInfo->getlandtable());

	TRAMPOLINE(GreenForest_Init)();
}

static void __cdecl GreenForest_Free_r()
{
	FreeLandTableFile(&GreenForestLandInfo);

	TRAMPOLINE(GreenForest_Free)();
}

void STG03_INIT()
{
	GreenForest_Init_t = new Trampoline(0x5ED0D0, 0x5ED0D7, GreenForest_Init_r);
	GreenForest_Free_t = new Trampoline(0x5ED4A0, 0x5ED4A6, GreenForest_Free_r);

	WriteData((ColorMap**)0x5ED148, GreenForestColorMap);
	WriteData((NJS_VECTOR*)0x1089398, GreenForest_MapOffset);
	WriteData((NJS_VECTOR*)0x10893A4, GreenForest_MapUnit);

	WriteCall((void*)0x5ED138, LoadChunkLandManager);
	
	DataDLL_Set<NJS_TEXLIST>("texlist_landtx03", &LANDTX03_DC_TEXLIST);
}