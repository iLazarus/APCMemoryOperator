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
	uint64_t uworld = 0;
	uint32_t eax = rcx;
	eax = ~eax;
	rcx = rcx >> 32;
	eax = eax - 0x26E57571;
	uint32_t ecx = rcx;
	ecx = ~ecx;
	eax = ~eax;
	ecx += 0x4ABBD578;
	eax += 0x7DDDE9F3;
	ecx = ~ecx;
	eax = ~eax;
	ecx -= 0x3ED032D;
	eax += 0x681A8A8F;
	ecx = ~ecx;
	eax = eax ^ 0x8222160C;
	ecx -= 0x26442A88;
	ecx = ecx ^ 0x0FC12FCD2;
	LODWORD(uworld) = eax;
	HIDWORD(uworld) = ecx;
	return uworld;

}

uint64_t decrypt::de_level(uint64_t level)
{
	uint64_t a1 = READ64(g_UWorld + level);
	uint64_t v3;
	LODWORD(v3) = ((a1 & 0x15151515 ^ a1 & 0xEAEAEAEA) + 1543212981) ^ 0x5BFB8FB5;
	HIDWORD(v3) = HIDWORD(g_UWorld);
	return v3;
}

uint64_t decrypt::de_actor(uint64_t actor)
{
	uint64_t a1 = READ64(g_ULevel + actor);
	uint64_t v3;
	LODWORD(v3) = (a1 + 1182730485) ^ 0x75D5017B;
	HIDWORD(v3) = HIDWORD(g_UWorld);
	return v3;
}

uint64_t decrypt::de_inst(uint64_t inst)
{
	uint64_t v1 = READ64(g_UWorld + inst);
	uint64_t v3;
	LODWORD(v3) = ((v1 ^ 0xD74573EB) - 0x45856DDA) ^ 0x303FE1CD;
	HIDWORD(v3) = HIDWORD(g_UWorld);
	return v3;
}

uint64_t decrypt::de_local(uint64_t local)
{
	uint64_t v6 = READ64(READ64(g_GameInstance + local));
	uint64_t v15;
	LODWORD(v15) = ((((unsigned __int16)v6 ^ ((unsigned int)v6 >> 16) | ((unsigned __int16)__ROL2__(WORD1(v6), 8) << 16))
		+ 1139005261) & 0xFFFF0000 | (unsigned __int16)((v6 ^ WORD1(v6)) - 10419) ^ ((((unsigned __int16)v6 ^ ((unsigned int)v6 >> 16) | ((unsigned __int16)__ROL2__(WORD1(v6), 8) << 16))
			+ 1139005261) >> 16)) ^ 0x43E3D74D;
	HIDWORD(v15) = HIDWORD(g_UWorld);
	return v15;
}

uint64_t decrypt::de_controller(uint64_t controller)
{
	uint64_t v15 = READ64(g_ULocalPlayer + controller);
	uint64_t a9;
	LODWORD(a9) = __ROR4__(__ROR4__(v15, 8) + 0x37577B19, 8) ^ 0x37577B19;
	HIDWORD(a9) = HIDWORD(g_UWorld);
	return a9;
}

uint64_t decrypt::de_prop(uint64_t prop)
{
	uint64_t a1 = READ64(prop);
	uint64_t v3;
	LODWORD(v3) = ((a1 & 0x15151515 ^ a1 & 0xEAEAEAEA) + 1543212981) ^ 0x5BFB8FB5;
	HIDWORD(v3) = HIDWORD(g_UWorld);
	return v3;
}

