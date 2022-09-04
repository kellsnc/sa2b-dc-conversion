#include "stdafx.h"
#include "SA2ModLoader.h"
#include "StageBinary.h"
#include "Trampoline.h"
#include "common.h"
#include "levels.h"
#include "stg13_cityescape.h"

DataPointer(NJS_OBJECT, object_city_lamp, 0x10A9150);
DataPointer(SA2B_Model, model_city_fence_small, 0x10ABCF4);
DataPointer(NJS_OBJECT, object_city_fence_small, 0x10AC210);
DataPointer(SA2B_Model, model_city_fence_large, 0x10ABE2C);
DataPointer(NJS_OBJECT, object_city_fence_large, 0x10ACF30);
DataPointer(NJS_OBJECT, object_city_trash_can, 0x109FC10);
DataPointer(NJS_OBJECT, object_city_bush_small, 0x10A0560);
DataPointer(NJS_OBJECT, object_city_bench_normal, 0x10A0EE8);
DataPointer(NJS_OBJECT, object_city_bench_poster, 0x10A1870);
DataPointer(NJS_OBJECT, object_city_lamp_post, 0x10A1F68);
DataPointer(NJS_OBJECT, object_city_mailbox1, 0x10A2894);
DataPointer(NJS_OBJECT, object_city_mailbox2, 0x10A33E0);
DataPointer(NJS_OBJECT, object_city_palmtree1, 0x10A392C);
DataPointer(NJS_OBJECT, object_city_palmtree2, 0x10A3F80);
DataPointer(NJS_OBJECT, object_city_palmtree3, 0x10A44DC);
DataPointer(NJS_OBJECT, object_city_sign_marking1, 0x10A54A0);
DataPointer(NJS_OBJECT, object_city_sign_marking2, 0x10A565C);
DataPointer(NJS_OBJECT, object_city_sign_marking3, 0x10A5818);
DataPointer(NJS_OBJECT, object_city_sign_dual1, 0x10A5D44);
DataPointer(NJS_OBJECT, object_city_sign_dual2, 0x10A6470);
DataPointer(NJS_OBJECT, object_city_sign_stop, 0x10A699C);
DataPointer(NJS_OBJECT, object_city_sign_small, 0x10A6DB8);
DataPointer(NJS_OBJECT, object_city_sign_tall, 0x10A73F0);
DataPointer(NJS_TEXLIST, texlist_city_sign_stop, 0x109F12C);
DataPointer(NJS_TEXLIST, texlist_city_sign_small, 0x109F158);
DataPointer(NJS_TEXLIST, texlist_city_sign_tall, 0x109F19C);
DataPointer(NJS_OBJECT, object_city_bg, 0x10DC390);
DataPointer(NJS_OBJECT, object_city_squaretree1, 0x10DCF9C);
DataPointer(NJS_OBJECT, object_city_squaretree1_leaves, 0x10DCDB8);
DataPointer(NJS_OBJECT, object_city_squaretree2, 0x10DD780);
DataPointer(NJS_OBJECT, object_city_squaretree2_leaves, 0x10DD574);
DataPointer(NJS_OBJECT, object_city_squaretree3, 0x10DDFFC);
DataPointer(NJS_OBJECT, object_city_squaretree3_leaves, 0x10DDD58);
DataPointer(NJS_OBJECT, object_city_squaretree4, 0x10DE898);
DataPointer(NJS_OBJECT, object_city_squaretree4_leaves, 0x10DE5D4);
DataPointer(NJS_OBJECT, object_city_squaretree5, 0x10DF054);
DataPointer(NJS_OBJECT, object_city_squaretree5_leaves, 0x10DEE70);
DataPointer(NJS_OBJECT, object_city_trick_bar, 0x10AB980);
DataPointer(NJS_OBJECT, object_city_slider, 0x10AB5A8);
DataPointer(NJS_OBJECT, object_city_signboard, 0x10A86DC);
DataPointer(NJS_OBJECT, object_city_treest, 0x10921B8);
DataPointer(NJS_OBJECT, object_city_treestnb, 0x1092980);
DataPointer(NJS_OBJECT, object_city_tree_leaves, 0x1092838);
DataPointer(NJS_OBJECT, object_city_tire, 0x1093A70);
DataPointer(NJS_OBJECT, object_city_ramp, 0x10934D0);
DataPointer(NJS_OBJECT, object_city_hammer, 0x1094294);
DataPointer(NJS_OBJECT, object_city_palm, 0x10AAEB8);
DataPointer(NJS_OBJECT, object_city_sarrow, 0x1094908);
DataPointer(NJS_OBJECT, object_city_greenb, 0x10AA118);
DataPointer(NJS_OBJECT, object_city_sblg, 0x10A98B0);
DataPointer(NJS_OBJECT, object_city_taxi, 0x10AF9B0);
DataPointer(NJS_OBJECT, object_city_trolley, 0x10C2D68);
DataPointer(NJS_OBJECT, object_city_car_white, 0x10B1250);
DataPointer(NJS_OBJECT, object_city_car_black, 0x10B2B24);
DataPointer(NJS_OBJECT, object_city_car_blue, 0x10B4660);
DataPointer(NJS_OBJECT, object_city_car_red, 0x10B5FA4);
DataPointer(NJS_OBJECT, object_city_car_civic, 0x10B77B8);
DataPointer(NJS_OBJECT, object_city_s_taxi, 0x10B9034);
DataPointer(NJS_OBJECT, object_city_car_s_white, 0x10BA760);
DataPointer(NJS_OBJECT, object_city_car_s_black, 0x10BBE7C);
DataPointer(NJS_OBJECT, object_city_car_s_blue, 0x10BD7C0);
DataPointer(NJS_OBJECT, object_city_car_s_red, 0x10BEF4C);
DataPointer(NJS_OBJECT, object_city_car_s_civic, 0x10C05C8);
DataPointer(NJS_OBJECT, object_city_a_taxi, 0x10C47B4);
DataPointer(NJS_OBJECT, object_city_a_trolley, 0x10D7E40);
DataPointer(NJS_OBJECT, object_city_car_a_white, 0x10C6120);
DataPointer(NJS_OBJECT, object_city_car_a_black, 0x10C7A54);
DataPointer(NJS_OBJECT, object_city_car_a_blue, 0x10C95A8);
DataPointer(NJS_OBJECT, object_city_car_a_red, 0x10CAF58);
DataPointer(NJS_OBJECT, object_city_car_a_civic, 0x10CC7C0);

static ColorMap CityEscapeColorMap[] {
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

static NJS_VECTOR CityEscape_MapOffset = { -3000.0f, 0.0f, 16640.0f };
static NJS_VECTOR CityEscape_MapUnit = { 33.14917f, 0.0f, 33.203125 };

static NJS_TEXNAME texname_city_sign_stop_dc[] {
	{ (void*)"ce64_ita002", 0, 0 },
	{ (void*)"ce64_ita002", 0, 0 },
	{ (void*)"miu64_ce038", 0, 0 },
	{ (void*)"scity_kage32", 0, 0 }
};

static NJS_TEXLIST texlist_city_sign_stop_dc = { arrayptrandlength(texname_city_sign_stop_dc) };

static NJS_TEXNAME texname_city_sign_small_dc[]{
	{ (void*)"ce64_ita002", 0, 0 },
	{ (void*)"scity32_14", 0, 0 },
	{ (void*)"miu64_ce039", 0, 0 },
	{ (void*)"scity_kage32", 0, 0 }
};

static NJS_TEXLIST texlist_city_sign_small_dc = { arrayptrandlength(texname_city_sign_small_dc) };

static NJS_TEXNAME texname_city_sign_tall_dc[]{
	{ (void*)"ce64_ita002", 0, 0 },
	{ (void*)"ce64_ita002", 0, 0 },
	{ (void*)"miu64_ce040", 0, 0 },
	{ (void*)"miu64_ce042", 0, 0 },
	{ (void*)"miu64_ce043", 0, 0 },
	{ (void*)"scity_kage32", 0, 0 }
};

static NJS_TEXLIST texlist_city_sign_tall_dc = { arrayptrandlength(texname_city_sign_tall_dc) };

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
	*object_city_fence_small.chunkmodel = *CityEscapeStageFile->GetModel(0x1887A0, StageBinary::ModelType_Chunk)->getchunkmodel();
	*object_city_fence_large.chunkmodel = *CityEscapeStageFile->GetModel(0x1892FC, StageBinary::ModelType_Chunk)->getchunkmodel();
	object_city_trash_can = *CityEscapeStageFile->GetModel(0x18A4D4, StageBinary::ModelType_Chunk);
	object_city_bush_small = *CityEscapeStageFile->GetModel(0x18ACF4, StageBinary::ModelType_Chunk);
	object_city_bench_normal = *CityEscapeStageFile->GetModel(0x18B6E4, StageBinary::ModelType_Chunk);
	object_city_bench_poster = *CityEscapeStageFile->GetModel(0x18B718, StageBinary::ModelType_Chunk);
	object_city_lamp_post = *CityEscapeStageFile->GetModel(0x18BCE0, StageBinary::ModelType_Chunk);
	object_city_mailbox1 = *CityEscapeStageFile->GetModel(0x18C4D4, StageBinary::ModelType_Chunk);
	object_city_mailbox2 = *CityEscapeStageFile->GetModel(0x18CE70, StageBinary::ModelType_Chunk);
	object_city_palmtree1 = *CityEscapeStageFile->GetModel(0x18D2E4, StageBinary::ModelType_Chunk);
	object_city_palmtree2 = *CityEscapeStageFile->GetModel(0x18D82C, StageBinary::ModelType_Chunk);
	object_city_palmtree3 = *CityEscapeStageFile->GetModel(0x18DCBC, StageBinary::ModelType_Chunk);
	object_city_sign_marking1 = *CityEscapeStageFile->GetModel(0x18E828, StageBinary::ModelType_Chunk);
	object_city_sign_marking2 = *CityEscapeStageFile->GetModel(0x18E960, StageBinary::ModelType_Chunk);
	object_city_sign_marking3 = *CityEscapeStageFile->GetModel(0x18EA98, StageBinary::ModelType_Chunk);
	object_city_sign_dual1 = *CityEscapeStageFile->GetModel(0x18EE78, StageBinary::ModelType_Chunk);
	object_city_sign_dual2 = *CityEscapeStageFile->GetModel(0x18F404, StageBinary::ModelType_Chunk);
	object_city_sign_stop = *CityEscapeStageFile->GetModel(0x18F798, StageBinary::ModelType_Chunk);
	texlist_city_sign_stop = texlist_city_sign_stop_dc;
	object_city_sign_small = *CityEscapeStageFile->GetModel(0x18FA64, StageBinary::ModelType_Chunk);
	texlist_city_sign_small = texlist_city_sign_small_dc;
	object_city_sign_tall = *CityEscapeStageFile->GetModel(0x18FECC, StageBinary::ModelType_Chunk);
	texlist_city_sign_tall = texlist_city_sign_tall_dc;
	object_city_bg = *CityEscapeStageFile->GetModel(0x4E33C, StageBinary::ModelType_Chunk);
	object_city_squaretree1 = *CityEscapeStageFile->GetModel(0x4ED0C, StageBinary::ModelType_Chunk);
	object_city_squaretree1_leaves = *object_city_squaretree1.child;
	object_city_squaretree2 = *CityEscapeStageFile->GetModel(0x4F2F4, StageBinary::ModelType_Chunk);
	object_city_squaretree2_leaves = *object_city_squaretree2.child;
	object_city_squaretree3 = *CityEscapeStageFile->GetModel(0x4F97C, StageBinary::ModelType_Chunk);
	object_city_squaretree3_leaves = *object_city_squaretree3.child;
	object_city_squaretree4 = *CityEscapeStageFile->GetModel(0x50004, StageBinary::ModelType_Chunk);
	object_city_squaretree4_leaves = *object_city_squaretree4.child;
	object_city_squaretree5 = *CityEscapeStageFile->GetModel(0x505C0, StageBinary::ModelType_Chunk);
	object_city_squaretree5_leaves = *object_city_squaretree5.child;
	*object_city_trick_bar.chunkmodel = *CityEscapeStageFile->GetModel(0x188064, StageBinary::ModelType_Chunk)->getchunkmodel();
	*object_city_slider.chunkmodel = *CityEscapeStageFile->GetModel(0x187D10, StageBinary::ModelType_Chunk)->getchunkmodel();
	*object_city_signboard.chunkmodel = *CityEscapeStageFile->GetModel(0x190FE4, StageBinary::ModelType_Chunk)->getchunkmodel();
	object_city_treest = *CityEscapeStageFile->GetModel(0x185608, StageBinary::ModelType_Chunk);
	object_city_treestnb = *CityEscapeStageFile->GetModel(0x1915FC, StageBinary::ModelType_Chunk);
	*object_city_tire.chunkmodel = *CityEscapeStageFile->GetModel(0x1921C0, StageBinary::ModelType_Chunk)->getchunkmodel();
	*object_city_ramp.chunkmodel = *CityEscapeStageFile->GetModel(0x17ED40, StageBinary::ModelType_Chunk)->getchunkmodel();
	*object_city_hammer.chunkmodel = *CityEscapeStageFile->GetModel(0x17F558, StageBinary::ModelType_Chunk)->getchunkmodel();
	*object_city_palm.chunkmodel = *CityEscapeStageFile->GetModel(0x18777C, StageBinary::ModelType_Chunk)->getchunkmodel();
	object_city_sarrow = *CityEscapeStageFile->GetModel(0x191904, StageBinary::ModelType_Chunk);
	*object_city_greenb.chunkmodel = *CityEscapeStageFile->GetModel(0x186BB8, StageBinary::ModelType_Chunk)->getchunkmodel();
	*object_city_sblg.chunkmodel = *CityEscapeStageFile->GetModel(0x186470, StageBinary::ModelType_Chunk)->getchunkmodel();
	
	object_city_taxi = *CityEscapeStageFile->GetModel(0x16BD78, StageBinary::ModelType_Chunk);
	object_city_trolley = *CityEscapeStageFile->GetModel(0x17C04C, StageBinary::ModelType_Chunk);
	object_city_car_white = *CityEscapeStageFile->GetModel(0x16D264, StageBinary::ModelType_Chunk);
	object_city_car_black = *CityEscapeStageFile->GetModel(0x16E708, StageBinary::ModelType_Chunk);
	object_city_car_blue = *CityEscapeStageFile->GetModel(0x16FDE0, StageBinary::ModelType_Chunk);
	object_city_car_red = *CityEscapeStageFile->GetModel(0x1712DC, StageBinary::ModelType_Chunk);
	object_city_car_civic = *CityEscapeStageFile->GetModel(0x172728, StageBinary::ModelType_Chunk);
	object_city_s_taxi = *CityEscapeStageFile->GetModel(0x173C3C, StageBinary::ModelType_Chunk);
	object_city_car_s_white = *CityEscapeStageFile->GetModel(0x176404, StageBinary::ModelType_Chunk);
	object_city_car_s_black = *CityEscapeStageFile->GetModel(0x17503C, StageBinary::ModelType_Chunk);
	object_city_car_s_blue = *CityEscapeStageFile->GetModel(0x1779FC, StageBinary::ModelType_Chunk);
	object_city_car_s_red = *CityEscapeStageFile->GetModel(0x178E1C, StageBinary::ModelType_Chunk);
	object_city_car_s_civic = *CityEscapeStageFile->GetModel(0x17A18C, StageBinary::ModelType_Chunk);
	object_city_a_taxi = object_city_taxi;
	object_city_a_trolley = object_city_trolley;
	object_city_car_a_white = object_city_car_white;
	object_city_car_a_black = object_city_car_black;
	object_city_car_a_blue = object_city_car_blue;
	object_city_car_a_red = object_city_car_red;
	object_city_car_a_civic = object_city_car_civic;

	auto object_bane = CityEscapeStageFile->GetModel(0x19CF80, StageBinary::ModelType_Chunk);
	*object_bane_banebottom_banebottom.chunkmodel = *object_bane->getchunkmodel();
	object_bane_banebottom_spring = *object_bane->child;
	object_bane_banebottom_banehead.chunkmodel = object_bane->child->child->getchunkmodel();
	object_bane = CityEscapeStageFile->GetModel(0x19D964, StageBinary::ModelType_Chunk);
	*object_bane_type_b_type_b_type_b.chunkmodel = *object_bane->getchunkmodel();
	object_bane_type_b_type_b_spring = *object_bane->child;
	object_bane_type_b_type_b_banehead = *object_bane->child->child;
	*object_obj_ring_ring.chunkmodel = *CityEscapeStageFile->GetModel(0x196088, StageBinary::ModelType_Chunk)->getchunkmodel();
	*object_obj_ring_ring_near.chunkmodel = *CityEscapeStageFile->GetModel(0x195B78, StageBinary::ModelType_Chunk)->getchunkmodel();
	*object_obj_ring_ring_far.chunkmodel = *CityEscapeStageFile->GetModel(0x1956EC, StageBinary::ModelType_Chunk)->getchunkmodel();
	*object_obj_box_wood.chunkmodel = *CityEscapeStageFile->GetModel(0x1B0FF4, StageBinary::ModelType_Chunk)->getchunkmodel();

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

	// They blanked out most of the palm tree displays
	WriteData((void**)0x10A7A24, (void*)0x5E3750);
	WriteData((void**)0x10A7A50, (void*)0x5E3750);
	WriteData((void**)0x10A7A7C, (void*)0x5E3750);

	// SkyBox display
	WriteCall((void*)0x5DD651, (void*)0x42E730);
}
