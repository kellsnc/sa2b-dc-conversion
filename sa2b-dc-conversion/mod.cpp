#include "stdafx.h"
#include <SA2ModLoader.h>
#include "mod.h"

#include "stg13_cityescape/stg13_cityescape.h"

std::string gModPath;
const HelperFunctions* gHelperFunctions;

extern "C"
{
	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions)
	{
		if (helperFunctions.Version < 5)
		{
			MessageBoxA(MainWindowHandle, 
				"The Mod Loader is outdated, please update it to the latest version.", 
				"SA2B Dreamcast Conversion", 
				MB_ICONWARNING);
		}

		gModPath = static_cast<std::string>(path);
		gHelperFunctions = &helperFunctions;

		STG13_INIT(helperFunctions);
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}