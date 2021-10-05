#include "stdafx.h"
#include <string>
#include "mod.h"
#include "levels.h"

void LoadChunkLandManager(int a1, LandTable* land)
{
	LandTableSA2BModels = 0;
	LoadLandManager(land);
}

//Replace the landtable and its texture file
LandTableInfo* LoadAndReplaceLandTable(char id, NJS_TEXLIST* texlist)
{
	std::string idstr;

	if (id < 10)
	{
		idstr += "0";
	}

	idstr += std::to_string(id);

	std::string str = "objLandTable00" + idstr;

	auto exportname = str.c_str();
	auto exportptr = reinterpret_cast<LandTable*>(GetProcAddress(**datadllhandle, exportname));

	if (exportptr)
	{
		std::string path = "resource\\gd_PC\\STG" + idstr + "_DC.sa2lvl";
		auto landname = path.c_str();
		auto landinfo = new LandTableInfo(gHelperFunctions->GetReplaceablePath(landname));

		auto land = landinfo->getlandtable();

		if (land)
		{
			auto oldtexlist = exportptr->TextureList;

			std::string texname = "LANDTX" + idstr + "_DC";
			char* cstr = new char[texname.length() + 1];
			strcpy_s(cstr, 12, texname.c_str());

			std::string texexportname = "texlist_landtx" + idstr;
			auto texexportptr = reinterpret_cast<NJS_TEXLIST*>(GetProcAddress(**datadllhandle, texexportname.c_str()));

			if (texexportptr)
			{
				*texexportptr = *texlist;
			}
			
			land->TextureName = cstr;
			land->TextureList = texlist;

			*exportptr = *land;
		}
		else
		{
			PrintDebug("[DC] Cannot find DC landtable at \"\s\"", landname);
		}
	}
	else
	{
		PrintDebug("[DC] Cannot find dll export \"\s\"", exportname);
	}

	return nullptr;
}