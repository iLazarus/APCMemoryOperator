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
	HIDWORD(v3) = (((a1 >> 32) & 0x15151515 ^ (a1 >> 32) & 0xEAEAEAEA) - 627778859) ^ 0x256B252B;
	return v3;
}

uint64_t decrypt::de_actor(uint64_t actor)
{
	uint64_t a1 = READ64(g_ULevel + actor);
	uint64_t v3;
	LODWORD(v3) = (a1 + 1182730485) ^ 0x75D5017B;
	HIDWORD(v3) = ((a1 >> 32) - 0x725B7DD5) ^ 0xB650BA5;
	return v3;
}

uint64_t decrypt::de_inst(uint64_t inst)
{
	uint64_t v1 = READ64(g_UWorld + inst);
	uint64_t v3;
	LODWORD(v3) = ((v1 ^ 0xD74573EB) - 0x45856DDA) ^ 0x303FE1CD;
	HIDWORD(v3) = ((HIDWORD(v1) ^ 0x24C4A658) - 0x469A461A) ^ 0x915EE042;
	return v3;
}

uint64_t decrypt::de_local(uint64_t local)
{
	uint64_t rbx = READ64(g_GameInstance + local);
	uint64_t r10 = READ64(READ64(g_GameInstance + local));
	uint32_t ecx = r10;
	ecx = ecx >> 16;
	uint64_t r8 = r10;
	uint16_t cx = ecx;
	uint32_t eax = cx;
	r8 = r8 >> 32;
	uint16_t ax = eax;
	ax = __ROL2__(ax, 8);
	uint32_t edx = ax;
	edx = edx << 16;
	uint16_t r10w = r10;
	eax = r10w;
	ecx = ecx ^ eax;
	edx = edx | ecx;
	edx += 0x43E3D74D;
	uint16_t dx = edx;
	eax = edx;
	ecx = edx;
	ecx = ecx >> 16;
	edx = edx & 0x0FFFF0000;
	ecx = ecx ^ eax;
	uint32_t r8d = r8;
	eax = r8d;
	ecx = ecx | edx;
	eax = eax >> 16;
	ax = eax;
	uint16_t r8w = r8;
	ax = ax ^ r8w;
	ecx = ecx ^ 0x43E3D74D;
	ax = __ROR2__(ax, 8);
	r8d = r8d & 0x0FFFF0000;

	uint64_t v15;
	LODWORD(v15) = ecx;
	HIDWORD(v15) = HIDWORD(g_UWorld);
	return v15;
}

uint64_t decrypt::de_controller(uint64_t controller)
{
	uint64_t v15 = READ64(g_ULocalPlayer + controller);
	uint64_t a9;
	LODWORD(a9) = __ROR4__(__ROR4__(v15, 8) + 0x37577B19, 8) ^ 0x37577B19;
	HIDWORD(a9) = HIDWORD(v15) = (HIDWORD(v15) - 0x49874947) ^ 0x49874947;
	return a9;
}

uint64_t decrypt::de_prop(uint64_t prop)
{
	uint64_t a1 = READ64(prop);
	uint64_t v3;
	LODWORD(v3) = ((a1 & 0x15151515 ^ a1 & 0xEAEAEAEA) + 1543212981) ^ 0x5BFB8FB5;
	HIDWORD(v3) = (((a1 >> 32) & 0x15151515 ^ (a1 >> 32) & 0xEAEAEAEA) - 627778859) ^ 0x256B252B;
	return v3;
}

