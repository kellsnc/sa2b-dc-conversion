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
