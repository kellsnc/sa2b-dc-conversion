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