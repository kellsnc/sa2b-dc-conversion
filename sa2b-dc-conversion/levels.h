#pragma once

struct ColorMap
{
	uint32_t color;
	uint32_t blockbit;
};

void LoadChunkLandManager(int a1, LandTable* a2);
void LoadLandTableFile(LandTableInfo** info, const char* name);
void FreeLandTableFile(LandTableInfo** info);
void SetLandTableTexInfo(LandTableInfo* info, NJS_TEXLIST* texlist, const char* name);