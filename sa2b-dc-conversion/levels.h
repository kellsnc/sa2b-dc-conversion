#pragma once

struct ColorMap
{
	uint32_t color;
	uint32_t blockbit;
};

void LoadChunkLandManager(int a1, LandTable* a2);
LandTableInfo* LoadAndReplaceLandTable(char id, NJS_TEXLIST* texlist);