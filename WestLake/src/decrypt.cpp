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
	uint64_t tmp = rcx - 0x2C4C7571;
	LODWORD(uworld) = __ROR4__(__ROL4__(LODWORD(tmp), 8) + 0x22936DA0, 16) ^ 0x0BFDFE311;
	HIDWORD(uworld) = __ROR4__(__ROR4__(HIDWORD(rcx) + 0x4454D578, 16) + 0x11C51429, 8) ^ 0x0C18FC14F;
	return uworld;
}

uint64_t decrypt::de_level(uint64_t level)
{
	uint64_t v7 = READ64(g_UWorld + level);
	uint64_t v15;

	LODWORD(v15) = (~(~(~(LODWORD(v7)) + 0x79B38A8F) - 0x6202762D) + 0x8B38A8F) ^ 0x6202762C;
	HIDWORD(v15) = (~(~(~HIDWORD(v7) - 0x15AB2A88) + 0x1CF21CB3) + 0x7954D578) ^ 0x1CF21CB2;

	return v15;
}

uint64_t decrypt::de_actor(uint64_t actor)
{
	uint64_t v6 = READ64(g_ULevel + actor);
	uint64_t v19;
	LODWORD(v19) = __ROR4__(~__ROR4__(LODWORD(v6), 16) - 0x3E5E6291, 16) ^ 0x3E5E6290;
	HIDWORD(v19) = __ROR4__(~__ROR4__(HIDWORD(v6), 8) + 0x400E40CF, 8) ^ 0x400E40CE;
	return v19;
}

uint64_t decrypt::de_inst(uint64_t inst)
{
	uint64_t v1 = READ64(g_UWorld + inst);
	uint64_t v3;
	LODWORD(v3) = ((LODWORD(v1) ^ 0x774B73EB) + 0x5A1AB286) ^ 0x7051C16D;
	HIDWORD(v3) = ((HIDWORD(v1) ^ 0xC4CAA658) + 0x59C55946) ^ 0xD1F000E2;
	return v3;
}

uint64_t decrypt::de_local(uint64_t local)
{
	uint64_t v9 = READ64(READ64(g_GameInstance + local));
	uint64_t a9;
	LODWORD(a9) = (LODWORD(v9) + 0x765BD8E5) ^ 0x85E5D16B;
	HIDWORD(a9) = (HIDWORD(v9) - 0x40A06DE5) ^ 0xFB75FBB5;
	return a9;
}

uint64_t decrypt::de_controller(uint64_t controller)
{
	uint64_t v15 = READ64(g_ULocalPlayer + controller);
	uint64_t a9;
	LODWORD(a9) = __ROL4__(__ROL4__(LODWORD(v15) + 0x1EBB03BD, 16) + 0x331478F4, 16) ^ 0x79597537;
	HIDWORD(a9) = __ROR4__(__ROR4__(HIDWORD(v15) - 0x7C153918, 8) + 0x17C1BF7F, 8) ^ 0x7290769;
	return a9;
}

uint64_t decrypt::de_prop(uint64_t prop)
{
	uint64_t v7 = READ64(prop);
	uint64_t v15;
	LODWORD(v15) = (~(~(~(LODWORD(v7)) + 0x79B38A8F) - 0x6202762D) + 0x8B38A8F) ^ 0x6202762C;
	HIDWORD(v15) = (~(~(~HIDWORD(v7) - 0x15AB2A88) + 0x1CF21CB3) + 0x7954D578) ^ 0x1CF21CB2;
	return v15;
}

