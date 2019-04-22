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
	LODWORD(uworld) = ((LODWORD(rcx) ^ 0x95D03BD) - 0x5BDB6BE4) ^ 0x7997A1;
	HIDWORD(uworld) = __ROL4__((__ROL4__(HIDWORD(rcx) ^ 0x6E8CC6E8, 8) - 0x5C645C64) ^ 0x98CC6E8, 8) ^ 0x5C645C64;
	return uworld;
}

uint64_t decrypt::de_level(uint64_t level)
{
	uint64_t v7 = READ64(g_UWorld + level);
	uint64_t v15;
	LODWORD(v15) = (~(LODWORD(v7) ^ 0x98A2FC42) - 0x7DBDC522) ^ 0x801F3963;
	HIDWORD(v15) = (~(HIDWORD(v7) ^ 0x33733917) - 0x7EE27E62) ^ 0x196EB88A;
	return v15;
}

uint64_t decrypt::de_actor(uint64_t actor)
{
	uint64_t v8 = READ64(g_ULevel + actor);
	uint64_t v13;
	LODWORD(v13) = __ROR4__(__ROR4__(LODWORD(v8), 8) + 0x7797BBD9, 8) ^ 0x7797BBD9;
	HIDWORD(v13) = (HIDWORD(v8) - 0x9C70987) ^ 0x9C70987;
	return v13;
}

uint64_t decrypt::de_inst(uint64_t inst)
{
	uint64_t v1 = READ64(g_UWorld + inst);
	uint64_t v3;
	LODWORD(v3) = __ROR4__(__ROL4__(LODWORD(v1) - 0x7CED7571, 8) + 0x41621E30, 16) ^ 0x2F4F93A1;
	HIDWORD(v3) = __ROR4__(__ROR4__(HIDWORD(v1) - 0xB4C2A88, 16) + 0x31B483B9, 8) ^ 0x51FF51BF;
	return v3;
}

uint64_t decrypt::de_local(uint64_t local)
{
	uint64_t v2 = READ64(READ64(g_GameInstance + local));
	uint64_t a9;
	LODWORD(a9) = ((LODWORD(v2) ^ 0x74D73EB) + 0x6A2A8276) ^ 0xD067F19D;
	HIDWORD(a9) = ((HIDWORD(v2) ^ 0x54CCA658) + 0x69B56936) ^ 0x91863092;
	return a9;
}

uint64_t decrypt::de_controller(uint64_t controller)
{
	uint64_t v6 = READ64(g_ULocalPlayer + controller);
	uint64_t v15;
	uint64_t v7 = v6 >> 32;
	LODWORD(v6) = ((unsigned __int16)v6 ^ ((unsigned int)v6 >> 16) | v6 & 0xFFFF0000) + 1587422786;
	LODWORD(v15) = ((unsigned __int16)v6 ^ ((unsigned int)v6 >> 16) | ((unsigned __int16)__ROR2__(WORD1(v6), 8) << 16)) ^ 0x5E9E2642;
	HIDWORD(v15) = (((((unsigned __int16)__ROR2__(WORD1(v7), 8) << 16) | (unsigned __int16)__ROR2__(v7 ^ WORD1(v7), 8))
		+ 1560370562) & 0xFFFF0000 | (unsigned __int16)__ROR2__(
		(__ROR2__(v7 ^ WORD1(v7), 8) + 23938) ^ (((((unsigned __int16)__ROR2__(WORD1(v7), 8) << 16) | (unsigned int)(unsigned __int16)__ROR2__(v7 ^ WORD1(v7), 8)) + 1560370562) >> 16),
			8)) ^ 0xA2FEA27E;
	return v15;
}

uint64_t decrypt::de_prop(uint64_t prop)
{
	uint64_t v7 = READ64(prop);
	uint64_t v15;
	LODWORD(v15) = (~(LODWORD(v7) ^ 0x98A2FC42) - 0x7DBDC522) ^ 0x801F3963;
	HIDWORD(v15) = (~(HIDWORD(v7) ^ 0x33733917) - 0x7EE27E62) ^ 0x196EB88A;
	return v15;
}

