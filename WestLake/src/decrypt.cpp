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
	uint64_t rcx = READ64(GAMEBASE + world);
	uint64_t uworld;
	LODWORD(uworld) = __ROR4__(__ROR4__(rcx, 8) - 0x78587437, 8) ^ 0x87A78BC9;
	HIDWORD(uworld) = (HIDWORD(rcx) + 0x6280669) ^ 0x0F9D7F997;
	return uworld;

}

uint64_t decrypt::de_level(uint64_t level)
{
	uint64_t a1 = READ64(g_UWorld + level);
	uint64_t v19;
	LODWORD(v19) = (a1 + 0x5683F945) ^ 0x2585F1CB;
	HIDWORD(v19) = ((a1 >> 32) - 0x61B7CD85) ^ 0x5B155B55;
	return v19;
}

uint64_t decrypt::de_actor(uint64_t actor)
{
	uint64_t a1 = READ64(g_ULevel + actor);
	uint64_t v21;
	LODWORD(v21) = __ROR4__((__ROR4__(a1 ^ 0x89FF03BD, 16) + 0x24A4149C) ^ 0x24FF03BD, 16) ^ 0x24A4149C;
	HIDWORD(v21) = __ROR4__((__ROR4__((a1 >> 32) ^ 0xEE2EC6E8, 8) + 0x231B231C) ^ 0x892EC6E8, 8) ^ 0xDCE4DCE4;
	return v21;
}

uint64_t decrypt::de_inst(uint64_t inst)
{
	uint64_t v1 = READ64(g_UWorld + inst);
	uint32_t v2 = v1 >> 32;
	uint64_t v4;
	LODWORD(v1) = ((unsigned __int16)__ROR2__(v1 ^ WORD1(v1), 8) | v1 & 0xFFFF0000) - 29473118;
	LODWORD(v4) = (((unsigned __int16)__ROR2__(WORD1(v1), 8) << 16) | (unsigned __int16)__ROR2__(v1 ^ WORD1(v1), 8)) ^ 0xFE3E46A2;
	HIDWORD(v4) = ((((HIDWORD(v1) >> 16) ^ (unsigned __int16)v2 | ((unsigned __int16)__ROR2__(WORD1(v2), 8) << 16))
		- 43909662) & 0xFFFF0000 | (unsigned __int16)((WORD1(v2) ^ v2) - 542) ^ ((((HIDWORD(v1) >> 16) ^ (unsigned __int16)v2 | ((unsigned __int16)__ROR2__(WORD1(v2), 8) << 16))
			- 43909662) >> 16)) ^ 0x29E021E;
	return v4;
}

uint64_t decrypt::de_local(uint64_t local)
{
	uint64_t v9 = READ64(READ64(g_GameInstance + local));
	uint64_t v15;

	LODWORD(v15) = (~(~(~v9 + 1775274639) + 1303214371) - 120550769) ^ 0xB25286DC;
	HIDWORD(v15) = (~(~(~(v9 >> 32) - 630073992) - 868037629) + 1769067896) ^ 0xCC42CC02;

	return v15;
	//1E3436DC800
}

uint64_t decrypt::de_controller(uint64_t controller)
{
	uint64_t v14 = READ64(g_ULocalPlayer + controller);
	uint64_t a9;
	LODWORD(a9) = __ROL4__(~__ROL4__(v14, 8) + 0x41211DEF, 8) ^ 0xBEDEE210;
	HIDWORD(a9) = __ROR4__(~__ROR4__(HIDWORD(v14), 16) - 0x3F713FB1, 16) ^ 0xC08EC04E;
	return a9;
	//1E332A7B890
}

uint64_t decrypt::de_prop(uint64_t prop)
{
	uint64_t a1 = READ64(prop);
	uint64_t v19;
	LODWORD(v19) = (a1 + 0x5683F945) ^ 0x2585F1CB;
	HIDWORD(v19) = ((a1 >> 32) - 0x61B7CD85) ^ 0x5B155B55;
	return v19;
}

