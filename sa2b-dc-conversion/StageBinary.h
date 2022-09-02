#pragma once

#include <unordered_set>
#include "SA2ModLoader.h"

class StageBinary
{
public:
	enum ModelType
	{
		ModelType_Invalid,
		ModelType_Basic,
		ModelType_Chunk,
		ModelType_SA2B
	};

	StageBinary(const char* filename, intptr_t base);
	StageBinary(std::string& filename, intptr_t base);
	~StageBinary();

	NJS_OBJECT* GetModel(intptr_t offset, ModelType type);
	LandTable* GetLandTable(intptr_t offset);
private:
	std::unordered_set<void*> fixedpointers;
	intptr_t filebase = 0x8C500000;
	void* filedata = nullptr;

	template<typename T>
	void FixPointer(T*& ptr)
	{
		if (ptr != nullptr)
			ptr = (T*)((intptr_t)ptr + filebase);
	}

	void FixBasicModelPointers(NJS_MODEL* model);
	void FixChunkModelPointers(NJS_CNK_MODEL* model);
	void FixSA2BModelPointers(SA2B_Model* model);
	void FixObjectPointers(NJS_OBJECT* object, ModelType tyoe);
	void FixLandtablePointers(LandTable* landtable);

	void Init(const char* filename, intptr_t base);
};
