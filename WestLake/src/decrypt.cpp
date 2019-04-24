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
	uint64_t tmp = rcx + 0x2BCB1FE5;
	LODWORD(uworld) = LODWORD(tmp) ^ 0x2BCB1FE5;
	HIDWORD(uworld) = (HIDWORD(rcx) - 0x553B55FB) ^ 0x553B55FB;
	return uworld;
}

uint64_t decrypt::de_level(uint64_t level)
{
	uint64_t v7 = READ64(g_UWorld + level);
	uint64_t v25;
	LODWORD(v25) = __ROL4__(__ROL4__(v7 - 0x5188FC43, 16) + 0x5360C964, 16) ^ 0x9E9C5A7;
	HIDWORD(v25) = __ROR4__(__ROR4__((v7 >> 32) + 0x13A6C6E8, 8) + 0x36ED4EEF, 8) ^ 0x77B977F9;
	return v25;
}

uint64_t decrypt::de_actor(uint64_t actor)
{
	uint64_t v6 = READ64(g_ULevel + actor);
	uint64_t v13;
	uint64_t v7 = v6 >> 32;
	uint64_t v8 = (unsigned int)(v6 >> 32) >> 16;
	uint64_t v9 = ((unsigned __int16)(v6 ^ WORD1(v6)) | ((unsigned __int16)__ROR2__(WORD1(v6), 8) << 16)) - 117958520;
	LODWORD(v6) = v9 >> 16;
	LODWORD(v13) = ((unsigned __int16)(v9 ^ v6) | ((unsigned __int16)__ROR2__(v6, 8) << 16)) ^ 0xF8F81888;
	HIDWORD(v13) = ((((v8 << 16) | (unsigned __int16)__ROL2__(v8 ^ v7, 8)) - 142084216) & 0xFFFF0000 | (unsigned __int16)__ROL2__((__ROL2__(v8 ^ v7, 8) - 2168) ^ ((((v8 << 16) | (unsigned __int16)__ROL2__(v8 ^ v7, 8)) - 142084216) >> 16), 8)) ^ 0x8780878;
	return v13;
}

uint64_t decrypt::de_inst(uint64_t inst)
{
	uint64_t v1 = READ64(g_UWorld + inst);
	uint64_t v3;
	LODWORD(v3) = (~(v1 ^ 0x6888FC42) - 0x4D8D5552) ^ 0x8005A913;
	HIDWORD(v3) = (~(HIDWORD(v1) ^ 0x3593917) - 0x4E124E92) ^ 0xD9B4887A;
	return v3;
}

uint64_t decrypt::de_local(uint64_t local)
{
	uint64_t v2 = READ64(READ64(g_GameInstance + local));
	uint64_t a9;
	LODWORD(a9) = __ROR4__(~__ROR4__(v2, 16) + 823217663, 16) ^ 0xCEEEB200;
	HIDWORD(a9) = __ROR4__(~__ROR4__(v2 >> 32, 8) - 1331777441, 8) ^ 0xB09EB05E;
	return a9;
}

uint64_t decrypt::de_controller(uint64_t controller)
{
	uint64_t v9 = READ64(g_ULocalPlayer + controller);
	uint64_t v15;
	LODWORD(v15) = (v9 - 0x6AF6477B) ^ 0xE545B10B;
	HIDWORD(v15) = (HIDWORD(v9) - 0x21B20D45) ^ 0x9BD59B15;
	return v15;
}

uint64_t decrypt::de_prop(uint64_t prop)
{
	uint64_t v7 = READ64(prop);
	uint64_t v25;
	LODWORD(v25) = __ROL4__(__ROL4__(v7 - 0x5188FC43, 16) + 0x5360C964, 16) ^ 0x9E9C5A7;
	HIDWORD(v25) = __ROR4__(__ROR4__((v7 >> 32) + 0x13A6C6E8, 8) + 0x36ED4EEF, 8) ^ 0x77B977F9;
	return v25;
}

