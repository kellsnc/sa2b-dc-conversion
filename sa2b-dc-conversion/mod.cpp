#include "stdafx.h"
#include <SA2ModLoader.h>
#include <IniFile.hpp>
#include "mod.h"

#include "levels.h"

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

		const auto config = new IniFile(std::string(path) + "\\config.ini");

		Levels_Init(config);
		
		delete config;
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}