#include "stdafx.h"

NJS_TEXLIST * oldtexlist;

//Use the dreamcast model format for landtables
void LandManagerHook(int a1, LandTable *a2)
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

	str = std::string(path) + "\\gd_PC\\stg" + id_string + "_dc.sa2lvl";
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

		HMODULE hmodule = GetModuleHandle(__TEXT("Data_DLL_orig"));

		ReplaceLevelFiles(&hmodule, path, LevelIDs_GreenForest);
		ReplaceLevelFiles(&hmodule, path, LevelIDs_MetalHarbor);
		ReplaceLevelFiles(&hmodule, path, LevelIDs_CityEscape);
		ReplaceLevelFiles(&hmodule, path, LevelIDs_CrazyGadget);
		ReplaceLevelFiles(&hmodule, path, LevelIDs_PyramidCave);
		ReplaceLevelFiles(&hmodule, path, LevelIDs_FinalRush);
		ReplaceLevelFiles(&hmodule, path, LevelIDs_GreenHill);

		// Dreamcast landtable fixes
		WriteCall((void*)0x5DCDF7, LandManagerHook);
		WriteData((char*)0x5DD4F0, (char)0xC3);
		WriteData<2>((void*)0x47C2BC, 0x90u);
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}