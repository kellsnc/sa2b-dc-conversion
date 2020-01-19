#include "stdafx.h"

NJS_TEXLIST * oldtexlist;

void LandManagerHook(int a1, LandTable *a2)
{
	LandTableSA2BModels = 0;
	LoadLandManager(a2);
}

void ReplaceLevelFiles(HMODULE* hmodule, const char *path, char id) {
	std::string str = "objLandTable00" + std::to_string(id);
	LandTable *land = (LandTable *)GetProcAddress(*hmodule, str.c_str());
	oldtexlist = land->TextureList;

	str = std::string(path) + "\\gd_PC\\stg" + std::to_string(id) + "_dc.sa2lvl";
	*land = *(new LandTableInfo(str.c_str()))->getlandtable();

	str = "landtx" + std::to_string(id) + "_dc";
	char *cstr = new char[str.length() + 1];
	strcpy_s(cstr, 12, str.c_str());

	land->TextureName = cstr;
	land->TextureList = oldtexlist;

	for (int i = 0; i < land->ChunkModelCount; ++i) {
		land->COLList[i].field_18 = 0xC00;
		land->COLList->Radius *= 100;
	}
}

extern "C"
{
	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions)
	{
		if (helperFunctions.Version < 5) {
			MessageBoxA(MainWindowHandle, "Your copy of the mod loader does not support API version 5. Some functionality will not be available.\n\nPlease exit the game and update the mod loader for the best experience.", "SA2B Dreamcast Conversion", MB_ICONWARNING);
		}

		HMODULE hmodule = GetModuleHandle(__TEXT("Data_DLL_orig"));
		ReplaceLevelFiles(&hmodule, path, LevelIDs_CityEscape);

		WriteCall((void*)0x5DCDF7, LandManagerHook);
		WriteData((char*)0x5DD4F0, (char)0xC3);
		WriteData<2>((void*)0x47C2BC, 0x90u);
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}