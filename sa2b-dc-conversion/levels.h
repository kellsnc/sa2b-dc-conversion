#pragma once

struct ColorMap
{
	uint32_t color;
	uint32_t blockbit;
};

void LoadChunkLandManager(int a1, LandTable* a2);
void Levels_Init(const IniFile* config);
