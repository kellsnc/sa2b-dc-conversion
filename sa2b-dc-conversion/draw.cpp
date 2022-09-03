#include "stdafx.h"
#include "SA2ModLoader.h"
#include "IniFile.hpp"
#include "mod.h"

DataPointer(NJS_COLOR, ConstantMaterial, 0x25EFFD0);
FunctionPointer(void, DrawChunkModel_Clip, (NJS_CNK_MODEL* model), 0x42E660);

static Trampoline* DrawSA2BModel_Clip_t;
static Trampoline* DrawSA2BModel_t;
static Trampoline* DrawSA2BModel_Color_Clip_t;
static Trampoline* DrawSA2BModel_Color_t;

#pragma region DrawSA2BModel
void __cdecl DrawSA2BModel_o(SA2B_Model* model)
{
	const auto funcptr = DrawSA2BModel_t->Target();

	__asm
	{
		mov ebx, model
		call funcptr
	}
}

void __cdecl DrawSA2BModel_c(SA2B_Model* model)
{
	// If this unknown variable is very large it's likely a pointer so chunk model
	if (model->field_4 > 0x100000)
	{
		DrawChunkModel((NJS_CNK_MODEL*)model);
	}
	else
	{
		DrawSA2BModel_o(model);
	}
}

static void __declspec(naked) DrawSA2BModel_asm()
{
	__asm
	{
		push ebx
		call DrawSA2BModel_c
		pop ebx
		retn
	}
}
#pragma endregion

#pragma region DrawSA2BModel_Clip
void __cdecl DrawSA2BModel_Clip_o(SA2B_Model* model)
{
	const auto funcptr = DrawSA2BModel_Clip_t->Target();

	__asm
	{
		mov eax, model
		call funcptr
	}
}

void __cdecl DrawSA2BModel_Clip_c(SA2B_Model* model)
{
	// If this unknown variable is very large it's likely a pointer so chunk model
	if (model->field_4 > 0x100000)
	{
		DrawChunkModel_Clip((NJS_CNK_MODEL*)model);
	}
	else
	{
		DrawSA2BModel_Clip_o(model);
	}
}

static void __declspec(naked) DrawSA2BModel_Clip_asm()
{
	__asm
	{
		push eax
		call DrawSA2BModel_Clip_c
		pop eax
		retn
	}
}
#pragma endregion

#pragma region DrawSA2BModel_Color
void __cdecl DrawSA2BModel_Color_r(SA2B_Model* model, NJS_COLOR color)
{
	// If this unknown variable is very large it's likely a pointer so chunk model
	if (model->field_4 > 0x100000)
	{
		// Todo: apply the diffuse
		DrawChunkModel((NJS_CNK_MODEL*)model);
	}
	else
	{
		TRAMPOLINE(DrawSA2BModel_Color)(model, color);
	}
}
#pragma endregion

#pragma region DrawSA2BModel_Color_Clip
void __cdecl DrawSA2BModel_Color_Clip_o(SA2B_Model* model, NJS_COLOR color)
{
	const auto funcptr = DrawSA2BModel_Color_Clip_t->Target();

	__asm
	{
		push[color]
		mov ebx, model
		call funcptr
		add esp, 4
	}
}

void __cdecl DrawSA2BModel_Color_Clip_c(SA2B_Model* model, NJS_COLOR color)
{
	// If this unknown variable is very large it's likely a pointer so chunk model
	if (model->field_4 > 0x100000)
	{
		// Todo: apply the diffuse
		DrawChunkModel_Clip((NJS_CNK_MODEL*)model);
	}
	else
	{
		DrawSA2BModel_Color_Clip_o(model, color);
	}
}

static void __declspec(naked) DrawSA2BModel_Color_Clip_asm()
{
	__asm
	{
		push[esp + 04h]
		push ebx
		call DrawSA2BModel_Color_Clip_c
		pop ebx
		add esp, 4
		retn
	}
}
#pragma endregion

void InitDrawPatches()
{
	DrawSA2BModel_Clip_t = new Trampoline(0x004932C0, 0x004932C6, DrawSA2BModel_Clip_asm);
	DrawSA2BModel_t = new Trampoline(0x0042B5A0, 0x0042B5A6, DrawSA2BModel_asm);
	DrawSA2BModel_Color_Clip_t = new Trampoline(0x00493860, 0x00493866, DrawSA2BModel_Color_Clip_asm);
	DrawSA2BModel_Color_t = new Trampoline(0x00494890, 0x0049489A, DrawSA2BModel_Color_r);
}
