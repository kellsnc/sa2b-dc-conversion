#include "stdafx.h"
#include "SA2ModLoader.h"
#include "ModelInfo.h"
#include "LandTableInfo.h"
#include "StageBinary.h"

StageBinary::StageBinary(std::string& filename, intptr_t base)
{
	Init(filename.c_str(), base);
}

StageBinary::StageBinary(const char* filename, intptr_t base)
{
	Init(filename, base);
}

StageBinary::~StageBinary()
{
	if (filedata)
	{
		FreeMemory(filedata, __FILE__, __LINE__);
	}
}

void StageBinary::FixBasicModelPointers(NJS_MODEL* model)
{
	FixPointer(model->points);
	FixPointer(model->normals);

	if (model->meshsets != nullptr)
	{
		FixPointer(model->meshsets);

		if (fixedpointers.find(model->meshsets) == fixedpointers.end())
		{
			fixedpointers.insert(model->meshsets);

			for (int i = 0; i < model->nbMeshset; i++)
			{
				FixPointer(model->meshsets[i].meshes);
				FixPointer(model->meshsets[i].attrs);
				FixPointer(model->meshsets[i].normals);
				FixPointer(model->meshsets[i].vertcolor);
				FixPointer(model->meshsets[i].vertuv);
			}
		}
	}

	FixPointer(model->mats);
}

void StageBinary::FixChunkModelPointers(NJS_CNK_MODEL* model)
{
	FixPointer(model->vlist);
	FixPointer(model->plist);
}

void StageBinary::FixSA2BModelPointers(SA2B_Model* model)
{
	if (model->Vertices != nullptr)
	{
		FixPointer(model->Vertices);

		if (fixedpointers.find(model->Vertices) == fixedpointers.end())
		{
			fixedpointers.insert(model->Vertices);
			for (SA2B_VertexData* vd = model->Vertices; vd->DataType != -1; ++vd)
				FixPointer(vd->Data);
		}
	}

	if (model->OpaqueGeoData != nullptr)
	{
		FixPointer(model->OpaqueGeoData);

		if (fixedpointers.find(model->OpaqueGeoData) == fixedpointers.end())
		{
			fixedpointers.insert(model->OpaqueGeoData);

			for (int i = 0; i < model->OpaqueGeometryCount; i++)
			{
				FixPointer(model->OpaqueGeoData[i].PrimitiveOffset);
				FixPointer(model->OpaqueGeoData[i].ParameterOffset);
			}
		}
	}

	if (model->TranslucentGeoData != nullptr)
	{
		FixPointer(model->TranslucentGeoData);

		if (fixedpointers.find(model->TranslucentGeoData) == fixedpointers.end())
		{
			fixedpointers.insert(model->TranslucentGeoData);

			for (int i = 0; i < model->TranslucentGeometryCount; i++)
			{
				FixPointer(model->TranslucentGeoData[i].PrimitiveOffset);
				FixPointer(model->TranslucentGeoData[i].ParameterOffset);
			}
		}
	}
}

void StageBinary::FixObjectPointers(NJS_OBJECT* object, ModelType tyoe)
{
	if (object->model != nullptr)
	{
		FixPointer(object->model);

		if (fixedpointers.find(object->model) == fixedpointers.end())
		{
			fixedpointers.insert(object->model);

			switch (tyoe)
			{
			case ModelType_Basic:
				FixBasicModelPointers(object->basicmodel);
				break;
			case ModelType_Chunk:
				FixChunkModelPointers(object->chunkmodel);
				break;
			case ModelType_SA2B:
				FixSA2BModelPointers(object->sa2bmodel);
				break;
			}
		}
	}

	if (object->child != nullptr)
	{
		FixPointer(object->child);

		if (fixedpointers.find(object->child) == fixedpointers.end())
		{
			fixedpointers.insert(object->child);
			FixObjectPointers(object->child, tyoe);
		}
	}

	if (object->sibling != nullptr)
	{
		FixPointer(object->sibling);

		if (fixedpointers.find(object->sibling) == fixedpointers.end())
		{
			fixedpointers.insert(object->sibling);
			FixObjectPointers(object->sibling, tyoe);
		}
	}
}

void StageBinary::FixLandtablePointers(LandTable* landtable)
{
	if (landtable->COLList != nullptr)
	{
		FixPointer(landtable->COLList);

		for (int i = 0; i < landtable->COLCount; i++)
		{
			if (landtable->COLList[i].Model != nullptr)
			{
				FixPointer(landtable->COLList[i].Model);
				if (fixedpointers.find(landtable->COLList[i].Model) == fixedpointers.end())
				{
					fixedpointers.insert(landtable->COLList[i].Model);

					bool visible = false;

					if (landtable->VisibleModelCount != -1)
						visible = i < landtable->VisibleModelCount;
					else
						visible = landtable->COLList[i].Flags < 0;

					FixObjectPointers(landtable->COLList[i].Model, visible ? (LandTableSA2BModels ? ModelType_SA2B : ModelType_Chunk) : ModelType_Basic);
				}
			}
		}
	}

	FixPointer(landtable->TextureName);
}

NJS_OBJECT* StageBinary::GetModel(intptr_t offset, ModelType tyoe)
{
	if (!filedata)
	{
		return nullptr;
	}

	auto mdl = reinterpret_cast<NJS_OBJECT*>(*(intptr_t*)&filedata + offset);
	FixObjectPointers(mdl, tyoe);
	return mdl;
}

LandTable* StageBinary::GetLandTable(intptr_t offset)
{
	if (!filedata)
	{
		return nullptr;
	}

	auto land = reinterpret_cast<LandTable*>(*(intptr_t*)&filedata + offset);
	FixLandtablePointers(land);
	return land;
}

void StageBinary::Init(const char* filename, intptr_t base)
{
	filedata = LoadPRSFile(filename);
	filebase = -base + *(intptr_t*)&filedata;
}
