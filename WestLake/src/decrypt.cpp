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
	eax = eax ^ 0x0E74173EB;
	eax += 0x4A0AE296;
	uint32_t ecx = 0;
	ecx = HIDWORD(rcx) ^ 0x34C0A658;
	eax = eax ^ 0x0D04B917D;
	ecx += 0x49D54956;
	ecx = ecx ^ 0x51EA10F2;
	LODWORD(uworld) = eax;
	HIDWORD(uworld) = ecx;
	return uworld;
}

uint64_t decrypt::de_level(uint64_t level)
{
	uint64_t v2 = READ64(g_UWorld + level);
	uint32_t v4 = v2 >> 32;
	uint64_t v24 = 0;
	LODWORD(v24) = ((unsigned __int16)(((WORD1(v2) ^ v2) - 30632) ^ ((((unsigned __int16)(WORD1(v2) ^ v2) | ((unsigned int)v2 >> 16 << 16))
		+ 673744984) >> 16)) | (((unsigned __int16)(WORD1(v2) ^ v2) | ((unsigned int)v2 >> 16 << 16))
			+ 673744984) & 0xFFFF0000) ^ 0x28288858;
	uint32_t v5 = ((unsigned __int16)__ROL2__(WORD1(v4) ^ WORD2(v2), 8) | ((unsigned __int16)__ROR2__(WORD1(v4), 8) << 16))
		+ 660023128;
	HIDWORD(v24) = ((unsigned __int16)__ROL2__(v5 ^ HIWORD(v5), 8) | ((unsigned __int16)__ROR2__(HIWORD(v5), 8) << 16)) ^ 0xD8A8D8A8;
	return v24;
}

uint64_t decrypt::de_actor(uint64_t actor)
{
	uint64_t v7 = READ64(g_ULevel + actor);
	uint64_t v12 = 0;
	LODWORD(v12) = (v7 + 1722158778) ^ 0x66A60EBA;
	HIDWORD(v12) = (HIDWORD(v7) + 1702454778) ^ 0x9A869A06;
	return v12;
}

uint64_t decrypt::de_inst(uint64_t inst)
{
	uint64_t v1 = READ64(g_UWorld + inst);
	uint64_t v3;
	LODWORD(v3) = (~(v1 ^ 0x186EFC42) + 46316126) ^ 0x8053B9E3;
	HIDWORD(v3) = (~(HIDWORD(v1) ^ 0xB33F3917) + 27066654) ^ 0x19A2380A;
	return v3;
}

uint64_t decrypt::de_local(uint64_t local)
{
	uint64_t v2 = READ64(READ64(g_GameInstance + local));
	uint64_t v12;
	LODWORD(v12) = (v2 - 527620658) ^ 0x505010B0;
	HIDWORD(v12) = ((v2 >> 32) - 1053885792) ^ 0xB050B050;
	return v12;
}

uint64_t decrypt::de_controller(uint64_t controller)
{
	uint64_t v5 = READ64(g_ULocalPlayer + controller);
	uint64_t v13;
	LODWORD(v13) = __ROR4__((__ROR4__(v5 ^ 0xA90403BD, 8) + 1153741948) ^ 0x440403BD, 8) ^ 0x44C4B47C;
	HIDWORD(v13) = ((HIDWORD(v5) ^ 0xE33C6E8) + 1140540412) ^ 0x15377AEC;
	return v13;
}

uint64_t decrypt::de_prop(uint64_t prop)
{
	uint64_t v2 = READ64(prop);
	uint32_t v4 = v2 >> 32;
	uint64_t v24 = 0;
	LODWORD(v24) = ((unsigned __int16)(((WORD1(v2) ^ v2) - 30632) ^ ((((unsigned __int16)(WORD1(v2) ^ v2) | ((unsigned int)v2 >> 16 << 16))
		+ 673744984) >> 16)) | (((unsigned __int16)(WORD1(v2) ^ v2) | ((unsigned int)v2 >> 16 << 16))
			+ 673744984) & 0xFFFF0000) ^ 0x28288858;
	uint32_t v5 = ((unsigned __int16)__ROL2__(WORD1(v4) ^ WORD2(v2), 8) | ((unsigned __int16)__ROR2__(WORD1(v4), 8) << 16))
		+ 660023128;
	HIDWORD(v24) = ((unsigned __int16)__ROL2__(v5 ^ HIWORD(v5), 8) | ((unsigned __int16)__ROR2__(HIWORD(v5), 8) << 16)) ^ 0xD8A8D8A8;
	return v24;
}

