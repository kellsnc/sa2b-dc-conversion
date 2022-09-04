#pragma once

#define TRAMPOLINE(name) ((decltype(name##_r)*)name##_t->Target())

template <typename T>
T* DataDLL_Get(const char* name)
{
	return reinterpret_cast<T*>(GetProcAddress(**datadllhandle, name));
}

template <typename T>
void DataDLL_Set(const char* name, T* data)
{
	auto addr = reinterpret_cast<T*>(GetProcAddress(**datadllhandle, name));

	if (addr)
	{
		*addr = *data;
	}
}

static const void* const FreeMemoryPtr = (void*)0x77DF80;
static inline void FreeMemory(void* pMemory, const char* file, int line)
{
	__asm
	{
		mov ecx, [line]
		mov edx, [file]
		mov eax, [pMemory]
		call FreeMemoryPtr
	}
}

static const void* const GetFileSize_Ptr = (void*)0x428CD0;
static inline void GetFileSize_(const char* filename, int* output)
{
	__asm
	{
		push[output]
		mov ecx, [filename]
		call GetFileSize_Ptr
		add esp, 4
	}
}

static const void* const OpenFile_Ptr = (void*)0x4532C0;
static inline int OpenFile_(void* idk, const char* filename, void* output)
{
	int result;
	__asm
	{
		push[output]
		mov esi, [filename]
		mov edi, [idk]
		call OpenFile_Ptr
		add esp, 4
		mov result, eax
	}
	return result;
}

static const void* const DecompressPRSPtr = (void*)0x48F980;
static inline int DecompressPRS(void* prs, void* output)
{
	int result;
	__asm
	{
		push[output]
		mov ecx, [prs]
		call DecompressPRSPtr
		mov result, eax
		add esp, 4
	}
	return result;
}

DataPointer(NJS_OBJECT, object_bane_banebottom_banebottom, 0xB55540);
DataPointer(NJS_OBJECT, object_bane_banebottom_spring, 0xB55038);
DataPointer(NJS_OBJECT, object_bane_banebottom_banehead, 0xB54CC0);
DataPointer(NJS_OBJECT, object_bane_type_b_type_b_type_b, 0xB56184);
DataPointer(NJS_OBJECT, object_bane_type_b_type_b_spring, 0xB55D68);
DataPointer(NJS_OBJECT, object_bane_type_b_type_b_banehead, 0xB559F0);
DataPointer(NJS_OBJECT, object_obj_ring_ring_far, 0xB57580);
DataPointer(NJS_OBJECT, object_obj_ring_ring_near, 0xB57A90);
DataPointer(NJS_OBJECT, object_obj_ring_ring, 0xB58020);
DataPointer(NJS_OBJECT, object_obj_box_wood, 0xB47E78);
