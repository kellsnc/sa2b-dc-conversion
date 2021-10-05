#include "stdafx.h"

NJS_TEXLIST * oldtexlist;

struct ColorMap
{
	uint32_t color;
	uint32_t blockbit;
};

ColorMap CityEscapeColorMap[]
{
	{ 0xFF000000, 0xFFFFFFFF },
	{ 0xFFFFFF00, 0x18432	 },
	{ 0xFFFF0000, 0x3D826	 },
	{ 0xFFFF00FF, 0xC0104	 },
	{ 0xFF00FFFF, 0x830C	 },
	{ 0xFFFF7D00, 0x46008	 },
	{ 0xFF007D00, 0x60CD0	 },
	{ 0xFF7D007D, 0x10860	 },
	{ 0xFF7D0000, 0x3040	 },
	{ 0xFF007D7D, 0x1080	 },
	{ 0xFF00FF00, 0x4200	 },
	{ 0xFF00007D, 0x2180	 }
};

NJS_VECTOR CityEscape_MapOffset = { -3000.0f, 0.0f, 16640.0f };
NJS_VECTOR CityEscape_MapUnit = { 33.14917f, 0.0f, 33.203125 };

NJS_TEXNAME LANDTX13_DC_TEXNAMES[]
{
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
	{ (void*)"miu32_ce003", 0, 0 },
};

NJS_TEXLIST LANDTX13_DC_TEXLIST = { arrayptrandlength(LANDTX13_DC_TEXNAMES) };

void LoadChunkLandManager(int a1, LandTable *a2)
{
	LandTableSA2BModels = 0;
	LoadLandManager(a2);
}

//Replace the landtable and its texture file
void ReplaceLevelFiles(HMODULE* hmodule, const char *path, char id) {
	std::string id_string;
	
	if (id < 10) {
		id_string += "0";
	}
	
	id_string += std::to_string(id);

	std::string str = "objLandTable00" + id_string;

	LandTable *land = (LandTable *)GetProcAddress(*hmodule, str.c_str());
	oldtexlist = land->TextureList;

	str = std::string(path) + "\\gd_PC\\STG" + id_string + "_DC.sa2lvl";
	*land = *(new LandTableInfo(str.c_str()))->getlandtable();

	str = "landtx" + std::to_string(id) + "_dc";
	char *cstr = new char[str.length() + 1];
	strcpy_s(cstr, 12, str.c_str());

	land->TextureName = cstr;
	land->TextureList = oldtexlist;
}

extern "C"
{
	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions)
	{
		if (helperFunctions.Version < 5) {
			MessageBoxA(MainWindowHandle, 
				"The Mod Loader is outdated, please update it to the latest version.", 
				"SA2B Dreamcast Conversion", 
				MB_ICONWARNING);
		}

		WriteData((ColorMap**)0x5DCE24, CityEscapeColorMap);
		WriteData((NJS_VECTOR*)0x10DC800, CityEscape_MapOffset);
		WriteData((NJS_VECTOR*)0x10DC80C, CityEscape_MapUnit);

		HMODULE hmodule = GetModuleHandle(__TEXT("Data_DLL_orig"));

		ReplaceLevelFiles(&hmodule, path, LevelIDs_GreenForest);
		ReplaceLevelFiles(&hmodule, path, LevelIDs_MetalHarbor);
		ReplaceLevelFiles(&hmodule, path, LevelIDs_CityEscape);
		ReplaceLevelFiles(&hmodule, path, LevelIDs_CrazyGadget);
		ReplaceLevelFiles(&hmodule, path, LevelIDs_PyramidCave);
		ReplaceLevelFiles(&hmodule, path, LevelIDs_FinalRush);
		ReplaceLevelFiles(&hmodule, path, LevelIDs_GreenHill);

		// Dreamcast landtable fixes
		WriteCall((void*)0x5DCDF7, LoadChunkLandManager);
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}