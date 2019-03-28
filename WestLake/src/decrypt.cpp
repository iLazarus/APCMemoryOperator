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
	LODWORD(uworld) = __ROR4__((__ROR4__(LODWORD(rcx) ^ 0x0E93303BD, 16) - 0x7BFB0BC4) ^ 0x843303BD, 16) ^ 0x8404F43C;
	HIDWORD(uworld) = __ROR4__((__ROR4__(HIDWORD(rcx) ^ 0x4E62C6E8, 8) - 0x7C447C44) ^ 0xE962C6E8, 8) ^ 0x7C447C44;
	return uworld;
}

uint64_t decrypt::de_level(uint64_t level)
{
	uint64_t v7 = READ64(g_UWorld + level);
	uint64_t v15;
	LODWORD(v15) = (~(LODWORD(v7) ^ 0xB8CCFC42) + 0x62229AFE) ^ 0x80119943;
	HIDWORD(v15) = (~(HIDWORD(v7) ^ 0x539D3917) + 0x613D61BE) ^ 0xD9A058AA;
	return v15;
}

uint64_t decrypt::de_actor(uint64_t actor)
{
	uint64_t v6 = READ64(g_ULevel + actor);
	uint64_t v19;
	LODWORD(v19) = (LODWORD(v6) - 0x1AE496EB) ^ 0x55B5619B;
	HIDWORD(v19) = (HIDWORD(v6) + 0x2E80624B) ^ 0x2B452B85;
	return v19;
}

uint64_t decrypt::de_inst(uint64_t inst)
{
	uint64_t v1 = READ64(g_UWorld + inst);
	uint64_t v3;
	LODWORD(v3) = __ROR4__(__ROL4__(LODWORD(v1) + 0x43618A8F, 8) - 0x3E8F2190, 16) ^ 0xEF0F53E1;
	HIDWORD(v3) = __ROR4__(__ROR4__(HIDWORD(v1) - 0x4BFD2A88, 16) - 0x4EBCBC07, 8) ^ 0x91BF917F;
	return v3;
}

uint64_t decrypt::de_local(uint64_t local)
{
	uint64_t v4 = READ64(READ64(g_GameInstance + local));
	uint32_t v6 = ((v4 ^ 0xE74373EB) + 0x4A0AE296) ^ 0xD049917D;
	uint32_t v7 = (((v4 >> 32) ^ 0x34C2A658) + 0x49D54956) ^ 0x51E810F2;
	return __PAIR__(v7, v6);
}

uint64_t decrypt::de_controller(uint64_t controller)
{
	uint64_t v12 = READ64(g_ULocalPlayer + controller);
	uint64_t v20;
	uint64_t v13 = v12 >> 32;
	uint64_t v14 = (v12 & 0xFFFF0000 | (unsigned __int16)__ROR2__(v12 ^ WORD1(v12), 8)) + 1048479330;
	LODWORD(v20) = ((unsigned __int16)__ROR2__(v14 ^ HIWORD(v14), 8) | ((unsigned __int16)__ROR2__(HIWORD(v14), 8) << 16)) ^ 0x3E7E8662;
	HIDWORD(v20) = ((((unsigned __int16)v13 ^ ((unsigned int)v13 >> 16) | ((unsigned __int16)__ROR2__(WORD1(v13), 8) << 16))
		+ 1025588642) & 0xFFFF0000 | (unsigned __int16)((v13 ^ WORD1(v13)) + 15778) ^ ((((unsigned __int16)v13 ^ ((unsigned int)v13 >> 16) | ((unsigned __int16)__ROR2__(WORD1(v13), 8) << 16))
			+ 1025588642) >> 16)) ^ 0xC2DEC25E;
	return v20;
}

uint64_t decrypt::de_prop(uint64_t prop)
{
	uint64_t v7 = READ64(prop);
	uint64_t v15;
	LODWORD(v15) = (~(LODWORD(v7) ^ 0xB8CCFC42) + 0x62229AFE) ^ 0x80119943;
	HIDWORD(v15) = (~(HIDWORD(v7) ^ 0x539D3917) + 0x613D61BE) ^ 0xD9A058AA;
	return v15;
}

