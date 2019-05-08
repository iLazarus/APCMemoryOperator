#include "decrypt.h"
#include "common.h"


decrypt::decrypt()
{
}


decrypt::~decrypt()
{
}


uint64_t decrypt::de_gnames(uint64_t gnames)
{
	return uint64_t();
}

uint64_t decrypt::de_world(uint64_t world)
{
	uint64_t a1 = READ64(GAMEBASE + world);
	__int64 v8;
	unsigned __int64 v1 = a1;
	unsigned int v2 = (unsigned int)a1 >> 16;
	unsigned int v3 = v2;
	unsigned int v4 = (v3 ^ (unsigned __int16)v1 | ((__ROL2__(v2, 8)) << 16)) + 1930643229;
	unsigned int v5 = v4 >> 16;
	LODWORD(v8) = ((v5 << 16) | v5 ^ (unsigned __int16)v4) ^ 0x7313471D;
	v1 >>= 32;
	int v6 = (v1 & 0xFFFF0000 | (unsigned __int16)__ROR2__(v1 ^ WORD1(v1), 8)) - 218303939;
	HIDWORD(v8) = (((unsigned __int16)__ROL2__(HIWORD(v6), 8) << 16) | (unsigned __int16)__ROR2__(HIWORD(v6) ^ v6, 8)) ^ 0xD030DC3;
	return v8;
}

uint64_t decrypt::de_level(uint64_t level)
{
	uint64_t a1 = READ64(g_UWorld + level);
	uint64_t v19;
	LODWORD(v19) = __ROR4__(~__ROR4__(a1, 16) + 1362226655, 16) ^ 0xAECE1220;
	HIDWORD(v19) = __ROR4__(~__ROR4__(a1 >> 32, 8) - 796995521, 8) ^ 0xD07ED03E;
	return v19;
}

uint64_t decrypt::de_actor(uint64_t actor)
{
	uint64_t a1 = READ64(g_ULevel + actor);
	uint64_t v27;
	LODWORD(v27) = (a1 - 536271410) ^ 0x505010B0;
	HIDWORD(v27) = (HIDWORD(a1) - 1028982112) ^ 0xB050B050;
	return v27;
}

uint64_t decrypt::de_inst(uint64_t inst)
{
	uint64_t v1 = READ64(g_UWorld + inst);
	uint64_t v3;
	LODWORD(v3) = __ROL4__(__ROL4__(v1 - 1103232067, 16) + 1933023572, 16) ^ 0x19F99597;
	HIDWORD(v3) = __ROR4__(__ROR4__(HIDWORD(v1) + 594396904, 8) + 1453613023, 8) ^ 0x67C96709;
	return v3;

}

uint64_t decrypt::de_local(uint64_t local)
{
	uint64_t a1 = READ64(READ64(g_GameInstance + local));
	uint64_t a9;
	LODWORD(a9) = __ROL4__(__ROL4__(a1 - 567082051, 16) - 1303627468, 16) ^ 0x39193577;
	HIDWORD(a9) = __ROR4__(__ROR4__((a1 >> 32) + 1130546920, 8) - 1770422337, 8) ^ 0x47E94729;
	return a9;
}

uint64_t decrypt::de_controller(uint64_t controller)
{
	uint64_t v9 = READ64(g_ULocalPlayer + controller);
	uint64_t v16;
	LODWORD(v16) = (~(~(~(_DWORD)v9 - 0x36A37571) + 0x2D8DD943) + 0x585C8A8F) ^ 0xD27226BC;
	HIDWORD(v16) = (~(~(~HIDWORD(v9) + 0x3AFDD578) - 0x539D53DD) - 0x36022A88) ^ 0xAC62AC22;
	return v16;
}

uint64_t decrypt::de_prop(uint64_t prop)
{
	uint64_t a1 = READ64(prop);
	uint64_t v19;
	LODWORD(v19) = __ROR4__(~__ROR4__(a1, 16) + 1362226655, 16) ^ 0xAECE1220;
	HIDWORD(v19) = __ROR4__(~__ROR4__(HIDWORD(a1), 8) - 796995521, 8) ^ 0xD07ED03E;
	return v19;
}

