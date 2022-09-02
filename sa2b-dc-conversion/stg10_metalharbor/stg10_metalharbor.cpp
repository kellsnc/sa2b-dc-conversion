#include "stdafx.h"
#include "SA2ModLoader.h"
#include "StageBinary.h"
#include "Trampoline.h"
#include "common.h"
#include "levels.h"
#include "stg10_metalharbor.h"

static Trampoline* MetalHarbor_Init_t;
static Trampoline* MetalHarbor_Free_t;

static StageBinary* MetalHarborStageFile;

static void __cdecl MetalHarbor_Init_r()
{
	MetalHarborStageFile = new StageBinary("STG10.PRS", 0x8C500000);

	auto land = MetalHarborStageFile->GetLandTable(0x897DC);
	land->TextureList = DataDLL_Get<NJS_TEXLIST>("texlist_landtx10");

	DataDLL_Set<LandTable>("objLandTable0010", land);

	TRAMPOLINE(MetalHarbor_Init)();
}

static void __cdecl MetalHarbor_Free_r()
{
	delete MetalHarborStageFile;
	MetalHarborStageFile = nullptr;

	TRAMPOLINE(MetalHarbor_Free)();
}

void STG10_INIT()
{
	MetalHarbor_Init_t = new Trampoline(0x6F2910, 0x6F2915, MetalHarbor_Init_r);
	MetalHarbor_Free_t = new Trampoline(0x6F2C70, 0x6F2C76, MetalHarbor_Free_r);

	WriteCall((void*)0x6F293E, LoadChunkLandManager);
}
