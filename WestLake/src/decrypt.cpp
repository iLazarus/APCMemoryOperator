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

	uint32_t eax = rcx;
	eax = eax ^ 0x88A2FC42;
	eax = ~eax;
	eax = eax - 0x6DADF532;
	eax = eax ^ 0x800F0973;


	uint32_t ecx = HIDWORD(rcx);
	ecx = ecx ^ 0x23733917;
	ecx = ~ecx;
	ecx = ecx - 0x6EF26E72;
	ecx = ecx ^ 0x197EA89A;

	LODWORD(uworld) = eax;
	HIDWORD(uworld) = ecx;
	return uworld;
}

uint64_t decrypt::de_level(uint64_t level)
{
	uint64_t v7 = READ64(g_UWorld + level);
	uint64_t v15;
	LODWORD(v15) = (v7 - 0x5919B186) ^ 0xA6E64E7A;
	HIDWORD(v15) = (HIDWORD(v7) - 0x5AC65A46) ^ 0x5AC65A46;
	return v15;
}

uint64_t decrypt::de_actor(uint64_t actor)
{
	uint64_t v6 = READ64(g_ULevel + actor);
	uint64_t v25 = 0;
	uint64_t v7 = HIDWORD(v6);
	uint64_t v8 = HIWORD(HIDWORD(v6));
	LODWORD(v6) = (((unsigned int)v6 >> 16 << 16) | (unsigned __int16)(WORD1(v6) ^ v6)) + 0x2E6EB672;
	LODWORD(v25) = ((unsigned __int16)(v6 ^ WORD1(v6)) | ((unsigned __int16)__ROR2__(WORD1(v6), 8) << 16)) ^ 0x2E6EB672;
	HIDWORD(v25) = ((((unsigned __int16)__ROR2__(v8 ^ v7, 8) | ((unsigned __int16)__ROR2__(v8, 8) << 16)) + 0x2D312DB2) & 0xFFFF0000 | (unsigned __int16)__ROR2__((__ROR2__(v8 ^ v7, 8) + 0x2DB2) ^ ((((unsigned __int16)__ROR2__(v8 ^ v7, 8) | ((unsigned int)(unsigned __int16)__ROR2__(v8, 8) << 16)) + 0x2D312DB2) >> 16), 8)) ^ 0xD2CED24E;
	return v25;
}

uint64_t decrypt::de_inst(uint64_t inst)
{
	uint64_t v1 = READ64(g_UWorld + inst);
	uint64_t v3;
	LODWORD(v3) = (v1 + 0x2666CEFA) ^ 0x2666CEFA;
	HIDWORD(v3) = (HIDWORD(v1) + 0x25B9253A) ^ 0xDA46DAC6;
	return v3;
}

uint64_t decrypt::de_local(uint64_t local)
{
	uint64_t a1 = READ64(READ64(g_GameInstance + local));


	__int64 v15;
	__int64 v24 = a1;
	__int64 v25 = a1 >> 32;
	LODWORD(v15) = ((unsigned __int16)(((v24 ^ WORD1(v24)) + 14568) ^ ((unsigned __int64)((v24 & 0xFFFF0000 | (unsigned __int16)(v24 ^ WORD1(v24)))
		- 1734854424) >> 16)) | ((v24 & 0xFFFF0000 | (unsigned __int16)(v24 ^ WORD1(v24))) - 1734854424) & 0xFFFF0000) ^ 0x989838E8;
	HIDWORD(v15) = ((unsigned __int16)__ROL2__(
		(__ROL2__(WORD1(v25) ^ v25, 8) - 26648) ^ (((((unsigned __int16)__ROR2__(WORD1(v25), 8) << 16) | (unsigned int)(unsigned __int16)__ROL2__(WORD1(v25) ^ v25, 8))
			- 1746429976) >> 16),
		8) | ((unsigned __int16)__ROR2__(
		((((unsigned __int16)__ROR2__(WORD1(v25), 8) << 16) | (unsigned int)(unsigned __int16)__ROL2__(WORD1(v25) ^ v25, 8))
			- 1746429976) >> 16,
			8) << 16)) ^ 0x68186818;
	return v15;
}

uint64_t decrypt::de_controller(uint64_t controller)
{
	uint64_t v17 = READ64(g_ULocalPlayer + controller);
	uint64_t v13;
	LODWORD(v13) = __ROL4__(__ROL4__(v17, 16) - 1945314124, 16) ^ 0x8C0CDCB4;
	HIDWORD(v13) = __ROR4__(__ROR4__(HIDWORD(v17), 8) - 1959556300, 8) ^ 0x74CC74CC;
	return v13;
}

uint64_t decrypt::de_prop(uint64_t prop)
{
	uint64_t v7 = READ64(prop);
	uint64_t v14;
	LODWORD(v14) = (v7 + 0x3F95C5AE) ^ 0x7070B090;
	HIDWORD(v14) = (HIDWORD(v7) + 0x21F71A80) ^ 0x90709070;
	return v14;
}

