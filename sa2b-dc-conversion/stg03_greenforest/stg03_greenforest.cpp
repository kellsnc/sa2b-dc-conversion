#include "stdafx.h"
#include "SA2ModLoader.h"
#include "StageBinary.h"
#include "Trampoline.h"
#include "common.h"
#include "levels.h"
#include "stg03_greenforest.h"

static ColorMap GreenForestColorMap[] {
	{ 0xFF000000, 0xFFFFFFFF },
	{ 0xFFFFFF00, 0x18432	 },
	{ 0xFFFF0000, 0x3D826	 },
	{ 0xFFFF00FF, 0xC0104	 },
	{ 0xFF00FFFF, 0x830C	 },
	{ 0xFFFF7D00, 0x46008	 },
	{ 0xFF0000FF, 0x218		 },
	{ 0xFF007D00, 0x60CD0	 },
	{ 0xFF7D007D, 0x10860	 },
	{ 0xFF7D0000, 0x3040	 },
	{ 0xFF007D7D, 0x1080	 },
	{ 0xFF00FF00, 0x4200	 },
	{ 0xFF00007D, 0x2180	 }
};

static NJS_VECTOR GreenForest_MapOffset = { -3000.0f, 0.0f, 16640.0f };
static NJS_VECTOR GreenForest_MapUnit = { 33.14917f, 0.0f, 33.203125 };

static Trampoline* GreenForest_Init_t;
static Trampoline* GreenForest_Free_t;

static StageBinary* GreenForestStageFile;

static void __cdecl GreenForest_Init_r()
{
	GreenForestStageFile = new StageBinary("STG03.PRS", 0x8C500000);

	auto land = GreenForestStageFile->GetLandTable(0x4FB64);
	land->TextureList = DataDLL_Get<NJS_TEXLIST>("texlist_landtx03");
	DataDLL_Set<LandTable>("objLandTable0003", land);

	TRAMPOLINE(GreenForest_Init)();
}

static void __cdecl GreenForest_Free_r()
{
	delete GreenForestStageFile;
	GreenForestStageFile = nullptr;

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
}
