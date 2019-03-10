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
	uint64_t uworld = 0;
	uint64_t rcx = READ64(GAMEBASE + world);

	uint32_t eax = LODWORD(rcx);
	eax = eax ^ 0x0B8B7FC42;
	eax = ~eax;
	uint32_t ecx = 0;
	ecx = HIDWORD(rcx) ^ 0x53883917;
	eax = eax + 0x62229AFE;
	ecx = ~ecx;
	eax = eax ^ 0x806A9943;
	ecx = ecx + 0x613D61BE;
	ecx = ecx ^ 0x0D9B558AA;

	LODWORD(uworld) = eax;
	HIDWORD(uworld) = ecx;
	return uworld;

}

uint64_t decrypt::de_level(uint64_t level)
{
	uint64_t v12 = READ64(g_UWorld + level);
	uint64_t v19  = 0;
	LODWORD(v19) = v12 + 0x6F6F151E;
	HIDWORD(v19) = HIDWORD(v12) + 0x52B1AAF0;
	return v19;
}

uint64_t decrypt::de_actor(uint64_t actor)
{
	uint64_t v15 = READ64(g_ULevel + actor);
	uint64_t v20 = 0;
	LODWORD(v20) = __ROL4__(__ROL4__(v15, 16) + 0x3CBCCC04, 16) ^ 0x3CBCCC04;
	HIDWORD(v20) = __ROR4__(__ROR4__(HIDWORD(v15), 8) + 0x3B833B84, 8) ^ 0xC47CC47C;
	return v20;
}

uint64_t decrypt::de_inst(uint64_t inst)
{
	uint64_t v1 = READ64(g_UWorld + inst);
	uint64_t v3;
	LODWORD(v3) = ((v1 ^ 0x97C873EB) + 2050642534) ^ 0x30F2218D;
	HIDWORD(v3) = ((HIDWORD(v1) ^ 0xE447A658) + 2040887590) ^ 0x111D2082;
	return v3;
}

uint64_t decrypt::de_local(uint64_t local)
{
	uint64_t v2 = READ64(READ64(g_GameInstance + local));
	uint64_t v15;
	LODWORD(v15) = ((unsigned __int16)((v2 ^ WORD1(v2)) - 0x77A8) ^ ((((unsigned __int16)v2 ^ ((unsigned int)v2 >> 16) | ((unsigned __int16)__ROR2__(WORD1(v2), 8) << 16))
		+ 0x28288858) >> 16) | ((unsigned __int16)__ROR2__((((unsigned __int16)v2 ^ ((unsigned int)v2 >> 16) | ((unsigned __int16)__ROR2__(WORD1(v2), 8) << 16)) + 0x28288858) >> 16, 8) << 16)) ^ 0x28288858;
	HIDWORD(v15) = (((HIDWORD(v2) & 0xFFFF0000 | (unsigned __int16)__ROL2__(WORD2(v2) ^ WORD1(HIDWORD(v2)), 8)) + 0x27572758) & 0xFFFF0000 | (unsigned __int16)__ROL2__((HIDWORD(v2) & 0xFFFF0000 | (unsigned __int16)__ROL2__(WORD2(v2) ^ WORD1(HIDWORD(v2)), 8)) + 0x27572758 ^ HIWORD((HIDWORD(v2) & 0xFFFF0000 | (unsigned __int16)__ROL2__(WORD2(v2) ^ WORD1(HIDWORD(v2)), 8)) + 0x27572758), 8)) ^ 0xD8A8D8A8;
	return v15;
}

uint64_t decrypt::de_controller(uint64_t controller)
{
	uint64_t v10 = READ64(g_ULocalPlayer + controller);
	uint64_t v17;
	LODWORD(v17) = __ROL4__(__ROL4__(v10, 16) + 0x1C9C2C24, 16) ^ 0x1C9C2C24;
	HIDWORD(v17) = __ROR4__(__ROR4__(HIDWORD(v10), 8) + 0x1BA31BA4, 8) ^ 0xE45CE45C;
	return v17;
}

uint64_t decrypt::de_prop(uint64_t prop)
{
	uint64_t v6 = READ64(prop);
	uint64_t v12;
	LODWORD(v12) = __ROL4__(
		__ROL4__(__ROR4__(__ROR4__((v6 + 0x6F6F151E) ^ 0xC9A985E7, 16) + 752842332, 16), 16) - 752842332,
		16) ^ 0xC9A985E7;
	HIDWORD(v12) = __ROR4__(
		__ROR4__(__ROL4__(__ROL4__((HIDWORD(v6) + 0x52B1AAF0) ^ 0xB779B7B9, 8) + 1221783761, 8), 8)
		- 1221783761,
		8) ^ 0xB779B7B9;
	return v12;
}

