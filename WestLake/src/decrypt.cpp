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
	/*
	
	___:00000001420D8140                 movzx   eax, dx
___:00000001420D8143                 mov     ecx, edx
___:00000001420D8145                 mov     r8, rdx
___:00000001420D8148                 shr     ecx, 10h
___:00000001420D814B                 xor     ecx, eax
___:00000001420D814D                 shr     r8, 20h
___:00000001420D8151                 and     edx, 0FFFF0000h
___:00000001420D8157                 mov     [rsp+28h+arg_8], rdi
___:00000001420D815C                 or      ecx, edx
___:00000001420D815E                 add     ecx, 5858F828h
___:00000001420D8164                 movzx   eax, cx
___:00000001420D8167                 mov     edx, ecx
___:00000001420D8169                 shr     edx, 10h
___:00000001420D816C                 and     ecx, 0FFFF0000h
___:00000001420D8172                 xor     edx, eax
___:00000001420D8174                 or      edx, ecx
___:00000001420D8176                 xor     edx, 5858F828h
___:00000001420D817C                 mov     dword ptr [rsp+28h+arg_8], edx
	*/
	uint64_t rdx = READ64(GAMEBASE + world);
	unsigned __int64 v1;
	unsigned int v2;
	int v3;
	__int64 v5;

	v1 = rdx;
	v2 = (((unsigned int)rdx >> 16 << 16) | ((unsigned int)rdx >> 16) ^ (unsigned __int16)rdx) + 1482225704;
	LODWORD(v5) = ((v2 >> 16 << 16) | (v2 >> 16) ^ (unsigned __int16)v2) ^ 0x5858F828;
	v1 >>= 32;
	v3 = (((unsigned __int16)__ROR2__(WORD1(v1), 8) << 16) | (unsigned __int16)__ROL2__(WORD1(v1) ^ v1, 8)) + 1462196008;
	HIDWORD(v5) = (((unsigned __int16)__ROR2__(HIWORD(v3), 8) << 16) | (unsigned __int16)__ROL2__(HIWORD(v3) ^ v3, 8)) ^ 0xA8D8A8D8;
	return v5;
}

uint64_t decrypt::de_level(uint64_t level)
{
	uint64_t v7 = READ64(g_UWorld + level);
	uint64_t v24;
	LODWORD(v24) = (v7 + 0x36769EEA) ^ 0x36769EEA;
	HIDWORD(v24) = (HIDWORD(v7) + 0x35A9352A) ^ 0xCA56CAD6;
	return v24;
}

uint64_t decrypt::de_actor(uint64_t actor)
{
	uint64_t v6 = READ64(g_ULevel + actor);
	uint64_t v19;
	LODWORD(v19) = __ROR4__((__ROR4__(v6 ^ 0x793303BD, 16) + 345261228) ^ 0x143303BD, 16) ^ 0x149444AC;
	HIDWORD(v19) = __ROR4__((__ROR4__((v6 >> 32) ^ 0xDE62C6E8, 8) + 321590060) ^ 0x7962C6E8, 8) ^ 0xECD4ECD4; 
	return v19;
}

uint64_t decrypt::de_inst(uint64_t inst)
{
	uint64_t v1 = READ64(g_UWorld + inst);
	uint64_t v3;
	LODWORD(v3) = (v1 + 734732261) ^ 0x2BCB1FE5;
	HIDWORD(v3) = (HIDWORD(v1) - 1429951995) ^ 0x553B55FB;
	return v3;
}

uint64_t decrypt::de_local(uint64_t local)
{
	uint64_t v2 = READ64(READ64(g_GameInstance + local));
	uint64_t v14;
	uint64_t v4 = v2 >> 32;
	uint64_t v5 = ((unsigned __int16)v2 ^ ((unsigned int)v2 >> 16) | v2 & 0xFFFF0000) + 509535874;
	LODWORD(v14) = ((unsigned __int16)v5 ^ (v5 >> 16) | ((unsigned __int16)__ROR2__(HIWORD(v5), 8) << 16)) ^ 0x1E5EE682;
	HIDWORD(v14) = ((((unsigned __int16)__ROR2__((unsigned int)(v2 >> 32) ^ WORD1(v4), 8) | ((unsigned __int16)__ROR2__(WORD1(v4), 8) << 16))
		+ 490806722) & 0xFFFF0000 | (unsigned __int16)__ROR2__(
		(__ROR2__((unsigned int)(v2 >> 32) ^ WORD1(v4), 8)
			+ 7618) ^ ((((unsigned __int16)__ROR2__(
			(unsigned int)(v2 >> 32) ^ WORD1(v4),
				8) | ((unsigned int)(unsigned __int16)__ROR2__(WORD1(v4), 8) << 16))
				+ 490806722) >> 16),
			8)) ^ 0xE2BEE23E;
	return v14;
}

uint64_t decrypt::de_controller(uint64_t controller)
{
	uint64_t v7 = READ64(g_ULocalPlayer + controller);
	uint64_t v15;
	LODWORD(v15) = (~(v7 ^ 0x8CCFC42) + 315787854) ^ 0x80E189F3;
	HIDWORD(v15) = (~(HIDWORD(v7) ^ 0xA39D3917) + 294457614) ^ 0x1910281A;
	return v15;
}

uint64_t decrypt::de_prop(uint64_t prop)
{
	uint64_t v7 = READ64(prop);
	uint64_t v24;
	LODWORD(v24) = (v7 + 0x36769EEA) ^ 0x36769EEA;
	HIDWORD(v24) = (HIDWORD(v7) + 0x35A9352A) ^ 0xCA56CAD6;
	return v24;
}

