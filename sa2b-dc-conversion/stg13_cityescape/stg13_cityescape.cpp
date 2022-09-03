#include "stdafx.h"
#include "SA2ModLoader.h"
#include "StageBinary.h"
#include "Trampoline.h"
#include "common.h"
#include "levels.h"
#include "stg13_cityescape.h"

DataPointer(NJS_OBJECT, object_city_lamp, 0x10A9150);

static ColorMap CityEscapeColorMap[] {
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

static NJS_VECTOR CityEscape_MapOffset = { -3000.0f, 0.0f, 16640.0f };
static NJS_VECTOR CityEscape_MapUnit = { 33.14917f, 0.0f, 33.203125 };

static NJS_TEXNAME LANDTX13_DC_TEXNAMES[] {
	{ (void*)"miu128_ce005", 0, 0 },
	{ (void*)"miu256_ce001", 0, 0 },
	{ (void*)"miu64_ce001", 0, 0 },
	{ (void*)"miu64_ce049", 0, 0 },
	{ (void*)"scity128_1", 0, 0 },
	{ (void*)"scity128_10", 0, 0 },
	{ (void*)"scity128_11", 0, 0 },
	{ (void*)"scity128_12", 0, 0 },
	{ (void*)"scity128_13", 0, 0 },
	{ (void*)"scity128_15", 0, 0 },
	{ (void*)"scity128_16", 0, 0 },
	{ (void*)"scity128_17", 0, 0 },
	{ (void*)"scity128_18", 0, 0 },
	{ (void*)"scity128_19", 0, 0 },
	{ (void*)"scity128_2", 0, 0 },
	{ (void*)"scity128_20", 0, 0 },
	{ (void*)"scity128_21", 0, 0 },
	{ (void*)"scity128_22", 0, 0 },
	{ (void*)"scity128_23", 0, 0 },
	{ (void*)"scity128_24", 0, 0 },
	{ (void*)"scity128_25", 0, 0 },
	{ (void*)"scity128_26", 0, 0 },
	{ (void*)"scity128_28", 0, 0 },
	{ (void*)"scity128_29", 0, 0 },
	{ (void*)"scity128_3", 0, 0 },
	{ (void*)"scity128_30", 0, 0 },
	{ (void*)"scity128_31", 0, 0 },
	{ (void*)"scity128_32", 0, 0 },
	{ (void*)"scity128_33", 0, 0 },
	{ (void*)"scity128_34", 0, 0 },
	{ (void*)"scity128_35", 0, 0 },
	{ (void*)"scity128_36", 0, 0 },
	{ (void*)"scity128_37", 0, 0 },
	{ (void*)"scity128_38", 0, 0 },
	{ (void*)"scity128_39", 0, 0 },
	{ (void*)"scity128_4", 0, 0 },
	{ (void*)"scity128_40", 0, 0 },
	{ (void*)"scity128_41", 0, 0 },
	{ (void*)"scity128_42", 0, 0 },
	{ (void*)"scity128_43", 0, 0 },
	{ (void*)"scity128_44", 0, 0 },
	{ (void*)"scity128_45", 0, 0 },
	{ (void*)"scity128_46", 0, 0 },
	{ (void*)"scity128_47", 0, 0 },
	{ (void*)"scity128_49", 0, 0 },
	{ (void*)"scity128_5", 0, 0 },
	{ (void*)"scity128_6", 0, 0 },
	{ (void*)"scity128_7", 0, 0 },
	{ (void*)"scity128_8", 0, 0 },
	{ (void*)"scity128_9", 0, 0 },
	{ (void*)"scity256_1", 0, 0 },
	{ (void*)"scity256_4", 0, 0 },
	{ (void*)"scity256_5", 0, 0 },
	{ (void*)"scity256_6", 0, 0 },
	{ (void*)"scity32_1", 0, 0 },
	{ (void*)"scity32_10", 0, 0 },
	{ (void*)"scity32_11", 0, 0 },
	{ (void*)"scity32_12", 0, 0 },
	{ (void*)"scity32_13", 0, 0 },
	{ (void*)"scity32_14", 0, 0 },
	{ (void*)"scity32_15", 0, 0 },
	{ (void*)"scity32_2", 0, 0 },
	{ (void*)"scity32_3", 0, 0 },
	{ (void*)"scity32_4", 0, 0 },
	{ (void*)"scity32_5", 0, 0 },
	{ (void*)"scity32_6", 0, 0 },
	{ (void*)"scity32_9", 0, 0 },
	{ (void*)"scity64_1", 0, 0 },
	{ (void*)"scity64_10", 0, 0 },
	{ (void*)"scity64_11", 0, 0 },
	{ (void*)"scity64_12", 0, 0 },
	{ (void*)"scity64_14", 0, 0 },
	{ (void*)"scity64_15", 0, 0 },
	{ (void*)"scity64_16", 0, 0 },
	{ (void*)"scity64_17", 0, 0 },
	{ (void*)"scity64_18", 0, 0 },
	{ (void*)"scity64_19", 0, 0 },
	{ (void*)"scity64_2", 0, 0 },
	{ (void*)"scity64_20", 0, 0 },
	{ (void*)"scity64_21", 0, 0 },
	{ (void*)"scity64_22", 0, 0 },
	{ (void*)"scity64_23", 0, 0 },
	{ (void*)"scity64_24", 0, 0 },
	{ (void*)"scity64_25", 0, 0 },
	{ (void*)"scity64_26", 0, 0 },
	{ (void*)"scity64_27", 0, 0 },
	{ (void*)"scity64_28", 0, 0 },
	{ (void*)"scity64_29", 0, 0 },
	{ (void*)"scity64_3", 0, 0 },
	{ (void*)"scity64_30", 0, 0 },
	{ (void*)"scity64_31", 0, 0 },
	{ (void*)"scity64_32", 0, 0 },
	{ (void*)"scity64_34", 0, 0 },
	{ (void*)"scity64_35", 0, 0 },
	{ (void*)"scity64_37", 0, 0 },
	{ (void*)"scity64_38", 0, 0 },
	{ (void*)"scity64_39", 0, 0 },
	{ (void*)"scity64_4", 0, 0 },
	{ (void*)"scity64_40", 0, 0 },
	{ (void*)"scity64_43", 0, 0 },
	{ (void*)"scity64_44", 0, 0 },
	{ (void*)"scity64_45", 0, 0 },
	{ (void*)"scity64_46", 0, 0 },
	{ (void*)"scity64_47", 0, 0 },
	{ (void*)"scity64_48", 0, 0 },
	{ (void*)"scity64_49", 0, 0 },
	{ (void*)"scity64_5", 0, 0 },
	{ (void*)"scity64_50", 0, 0 },
	{ (void*)"scity64_51", 0, 0 },
	{ (void*)"scity64_52", 0, 0 },
	{ (void*)"scity64_53", 0, 0 },
	{ (void*)"scity64_6", 0, 0 },
	{ (void*)"scity64_7", 0, 0 },
	{ (void*)"scity64_8", 0, 0 },
	{ (void*)"scity64_9", 0, 0 },
	{ (void*)"scity_kage32", 0, 0 },
	{ (void*)"t_lower128_11", 0, 0 },
	{ (void*)"t_lower128_5", 0, 0 },
	{ (void*)"t_lower128_8", 0, 0 },
	{ (void*)"t_senro128", 0, 0 },
	{ (void*)"t_win128_4", 0, 0 },
	{ (void*)"t_win128_5", 0, 0 },
	{ (void*)"t_win128_9", 0, 0 },
	{ (void*)"miu32_ce003", 0, 0 }
};

static NJS_TEXLIST LANDTX13_DC_TEXLIST = { arrayptrandlength(LANDTX13_DC_TEXNAMES) };

static Trampoline* CityEscape_Init_t;
static Trampoline* CityEscape_Free_t;

static StageBinary* CityEscapeStageFile;

static void __cdecl CityEscape_Init_r()
{
	CityEscapeStageFile = new StageBinary("STG13.PRS", 0x8C500000);

	auto land = CityEscapeStageFile->GetLandTable(0xAC774);
	land->TextureList = &LANDTX13_DC_TEXLIST;

	DataDLL_Set<LandTable>("objLandTable0013", land);

	object_city_lamp = *CityEscapeStageFile->GetModel(0x185EF4, StageBinary::ModelType_Chunk);
	
	TRAMPOLINE(CityEscape_Init)();
}

static void __cdecl CityEscape_Free_r()
{
	delete CityEscapeStageFile;
	CityEscapeStageFile = nullptr;

	TRAMPOLINE(CityEscape_Free)();
}

void STG13_INIT()
{
	CityEscape_Init_t = new Trampoline(0x5DCD50, 0x5DCD56, CityEscape_Init_r);
	CityEscape_Free_t = new Trampoline(0x5DD340, 0x5DD346, CityEscape_Free_r);

	WriteData((ColorMap**)0x5DCE24, CityEscapeColorMap);
	WriteData((NJS_VECTOR*)0x10DC800, CityEscape_MapOffset);
	WriteData((NJS_VECTOR*)0x10DC80C, CityEscape_MapUnit);

	WriteCall((void*)0x5DCDF7, LoadChunkLandManager);
	
	DataDLL_Set<NJS_TEXLIST>("texlist_landtx13", &LANDTX13_DC_TEXLIST);
}
