#include "stdafx.h"
#include "SA2ModLoader.h"
#include "StageBinary.h"
#include "Trampoline.h"
#include "common.h"
#include "levels.h"
#include "stg10_metalharbor.h"

static NJS_TEXNAME LANDTX10_DC_TEXNAMES[] {
	{ (void*)"pr128_12", 0, 0 },
	{ (void*)"pr128_14", 0, 0 },
	{ (void*)"pr128_15", 0, 0 },
	{ (void*)"pr128_16", 0, 0 },
	{ (void*)"pr128_17", 0, 0 },
	{ (void*)"pr128_18", 0, 0 },
	{ (void*)"pr128_20", 0, 0 },
	{ (void*)"pr128_21", 0, 0 },
	{ (void*)"pr128_22", 0, 0 },
	{ (void*)"pr128_23", 0, 0 },
	{ (void*)"pr128_24", 0, 0 },
	{ (void*)"pr128_25", 0, 0 },
	{ (void*)"pr128_26", 0, 0 },
	{ (void*)"pr128_27", 0, 0 },
	{ (void*)"pr128_28", 0, 0 },
	{ (void*)"pr128_32", 0, 0 },
	{ (void*)"pr128_33", 0, 0 },
	{ (void*)"pr128_34", 0, 0 },
	{ (void*)"pr128_35", 0, 0 },
	{ (void*)"pr128_37", 0, 0 },
	{ (void*)"pr128_5", 0, 0 },
	{ (void*)"pr128_6", 0, 0 },
	{ (void*)"pr128_7", 0, 0 },
	{ (void*)"pr128_8", 0, 0 },
	{ (void*)"pr256_2", 0, 0 },
	{ (void*)"pr256_5", 0, 0 },
	{ (void*)"pr256_7", 0, 0 },
	{ (void*)"pr32_1", 0, 0 },
	{ (void*)"pr32_2", 0, 0 },
	{ (void*)"pr32_3", 0, 0 },
	{ (void*)"pr32_4", 0, 0 },
	{ (void*)"pr64_1", 0, 0 },
	{ (void*)"pr64_10", 0, 0 },
	{ (void*)"pr64_11", 0, 0 },
	{ (void*)"pr64_12", 0, 0 },
	{ (void*)"pr64_14", 0, 0 },
	{ (void*)"pr64_15", 0, 0 },
	{ (void*)"pr64_16", 0, 0 },
	{ (void*)"pr64_17", 0, 0 },
	{ (void*)"pr64_18", 0, 0 },
	{ (void*)"pr64_19", 0, 0 },
	{ (void*)"pr64_20", 0, 0 },
	{ (void*)"pr64_21", 0, 0 },
	{ (void*)"pr64_23", 0, 0 },
	{ (void*)"pr64_3", 0, 0 },
	{ (void*)"pr64_9", 0, 0 },
	{ (void*)"pr_2kage32", 0, 0 },
	{ (void*)"pr_3kage32", 0, 0 },
	{ (void*)"pr_kage32", 0, 0 },
	{ (void*)"pr128_29", 0, 0 }
};

static NJS_TEXLIST LANDTX10_DC_TEXLIST = { arrayptrandlength(LANDTX10_DC_TEXNAMES) };

static Trampoline* MetalHarbor_Init_t;
static Trampoline* MetalHarbor_Free_t;

static StageBinary* MetalHarborStageFile;

static void __cdecl MetalHarbor_Init_r()
{
	MetalHarborStageFile = new StageBinary("STG10.PRS", 0x8C500000);

	auto land = MetalHarborStageFile->GetLandTable(0x897DC);
	land->TextureList = &LANDTX10_DC_TEXLIST;

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
	
	DataDLL_Set<NJS_TEXLIST>("texlist_landtx10", &LANDTX10_DC_TEXLIST);
}
