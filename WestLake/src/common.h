#pragma once

#ifndef COMMON_H
#define COMMON_H


#include <stdint.h>
#include <mutex>
#include "driver.h"
#include "graphics.h"
#include "game.h"
#include "decrypt.h"

using namespace std;

extern driver drv;
extern graphics dx;
extern decrypt dpt;
extern mutex mx;
extern mutex mxdx;

extern uint64_t g_UGname;
extern uint64_t g_UWorld;	//base->world
extern uint64_t g_GameInstance;//world->inst
extern uint64_t g_ULevel;		//world->level
extern uint64_t g_ULocalPlayer;	//inst->local
extern uint64_t g_APlayerController;//local->ctl
extern uint64_t g_UPlayerCameraManager;
extern uint64_t g_USelf;
extern uint64_t g_MeshSelf;
extern PlayerData g_BestAimTarget;

extern bool esp;
extern bool autobot;
extern bool vehicle;
extern bool itemgoods;
extern bool skeltch;


#define READ64(addr) (drv.RPM<uint64_t>(addr))
#define READ32(addr) (drv.RPM<uint32_t>(addr))
#define READINT(addr) (drv.RPM<int>(addr))
#define READBYTE(addr) (drv.RPM<BYTE>(addr))
#define READFLT(addr) (drv.RPM<float>(addr))
#define READT(T, address, size) (drv.RPM<T>(address, size))
#define READSIZE(addr, out, size) (drv.RPM(addr,out,size))
#define GAMEBASE	(drv.GetGameModule())

#define _WORD  uint16_t
#define _DWORD uint32_t
#define LODWORD(x)  (*((_DWORD*)&(x)))
#define HIDWORD(x)  (*((_DWORD*)&(x)+1))
#define WORDn(x, n)   (*((_WORD*)&(x)+n))
#define WORD1(x)   WORDn(x,  1)
#define WORD2(x)   WORDn(x,  2)
#define __PAIR__(high, low) (((uint64_t)(high)<<sizeof(high)*8) | low)

uint32_t __ROL4__(uint32_t x, unsigned int count);
uint32_t __ROR4__(uint32_t x, unsigned int count);
uint16_t __ROL2__(uint16_t x, unsigned int count);
uint16_t __ROR2__(uint16_t x, unsigned int count);



#define SCREENX 1920
#define SCREENY	1080


// E8 ? ? ? ? 48 8B 8B ? ? ? ? 48 85 C0 74 0D 
//000000014014D888                 lea     rax, unk_144145AA8
//000000014014D88F                 mov[rbx], rax
//000000014014D892                 lea     rax, sub_1418A12A0
// BRO.ClearIDCLevel
#define UWORLD					0x68DE5B8

// 48 8D 3D ? ? ? ? 33 C0 B9 ? ? ? ? F3 48 AB 48 8D 3D ? ? ? ? B9 ? ? ? ? F3 48 AB 48 8B 3D + 1FA0
#define GNAMES					0x66E9DC0 + 0x1FA0

// c1 ? ? 8b ? c1 ? 1f 03 ? 69 ? ? ? ? ? 44 2b f8
#define GNAMECHUNKSIZE			0x413C
#define GNAMESUFFIX				0x10

// 88 41 10 C7 41 12 01 ? ? ? 66 C7 41 1C ? 01 88 41 16
#define	AACTORID				0x18

// 88 41 10 C7 41 12 01 ? ? ? 66 C7 41 1C ? 01 88 41 16
#define DECID(v10) __ROL4__(v10 ^ 0x4894FA74, 2) ^ (__ROL4__(v10 ^ 0x4894FA74, 2) << 16) ^ 0x1237A4DC


//  E8 ? ? ? ? 84 C0 74 16 F6 83 ? ? ? ? ?        ACTORS
//  E8 ? ? ? ? 39 5C 24 48 7E 29                  LEVEL
#define LEVEL					0x338
#define ACTORS					0x250

// E8 ? ? ? ? 48 8B C8 33 D2 E8 ? ? ? ? 48 ? ? 48 ? ? 0F
#define GAMEINSTANCE			0x78

// 48 8B C8 33 D2 E8 ? ? ? ? 48 3B C6 0F 85 ? ? ? ?
#define LOCALPLAYER				0xE0
#define PLAYERCONTROLLER		0x38

// 41 ff 90 ? ? ? ? ? 8b ? ? ? ? ? 48 85 c9 74 ? 48 8b 01 4c 8d
#define PLAYERCAMERAMANAGER		0x4A0 // mov     rcx, [rdi+490h]
//prop 也用这个
// 48 89 5C 24 10 48 89 4C 24 08 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 D9 48 81 EC 90 ? ? ? 48
#define SELF					0x410

// 48 8B 99 ? ? ? ? 48 ? ? 48 ? ? 0F 84 ? ? ? ? 0F 10
#define MESH					0x4A0 // mov     rbx, [rcx+4A0h]

// 0F 57 C0 0F 2F 81 ? ? ? ? 72 0C
#define HEALTH					0xC08
#define GROGGYHEALTH			0xC50

// 44 0F B6 81 ? ? ? ? 41 0F B6 C0 24 01 3A C2 74 13 41 80 E0 FE 44 0A C2 44 88 81 ? ? ? ? E9 ? ? ? ?
#define DROPPEDITEMARRAY		0x160 // 0x318  jmp     sub_1424CECF0

// 48 8B 8F ? ? ? ? 48 63 D3 48 8B 14 D1 48
#define ITEMPACKAGE				0x520 //  mov     rcx, [rdi+518h]

// 0F B6 F8 48 85 D2 74 13 4C 8B CE 4C 8B C5 49 8B CE ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?
#define UITEM					0x600  //mov     rdx, [rbx+600h]

// LastTeamNum
#define TEAM					0xB10 // 19A0

// 83 F8 03 74 08 48 8B CB E8 ? ? ? ? B0 01 48 8B 4D ? 48 33 CC E8
#define ROOTCOMPONET			0x3D8	//mov     rdx, [rbx+148h] 下面一个

// 0F 2F 83 ? ? ? ? 0F 42 C8
#define LASTRENDERTIME			0x758

// FOV cc cc cc f3 0f 10 ? ? ? ? ? 0f ? ? 0f ? ? 77 08 f3 0f 10 ? ? ? ? ? c3
// ROT f2 0f 10 81 ? ? ? ? f2 41 0f 11 ? 8b 81 ? ? ? ? 41 89 ? ? c3
// LOT cc f2 0f 10 81 ? ? ? ? f2 0f 11 ? 8b 81 ? ? ? ? 89 42 ? f2
#define CAMERACACHE				0x4C8 - 0x10

// 41 3B 84 C8 ?? ?? ?? ?? 0F 8D ?? ?? ?? ?? 0F 10 ??
#define BONEARRAY				0xA10     //F3 0F 10 81 ?? ?? ?? ?? F3 0F 10 0D ?? ?? ?? ?? 0F 2F C1
#define COMPONENTTOWORLD		0x2B0

// 48 85 C0 74 23 0F 10 88 ?? ?? 00 00 0F 28 C1
#define RELATIVELOCATION		0x2C0

//#define CHARACTERMOVEMENT		0x4F0 //0x4b0
//#define LASTUPDATEVELOCITY		0x3B0
#define COMPONENTVELOCITY		0x1F0
#define ANIMSCRIPTINSTANCE		0xBA8
#define CONTROLROTATION_CP		0x680


#define WEAPONPROCESSOR			0xCC8
#define EQUIPPEDWEAPONS			0x2A0
#define WEAPONTRAJECTORYDATA	0xD20
#define TRAJECTORYCONFIG		0xB8
#define VDRAGCOEFFICIENT		0x20
#define TRAJECTORYGRAVITYZ		0xC18
#define SIMULATIONSUBSTEPTIME	0x1C


#define VEHICLERIDERCOMPONENT	0x16C8
// WeaponIconColorParmName UVehicleRiderComponent
//48 83 EC 58 48 C7 44 24 ? ? ? ? ? 48 C7 44 24 ? ? ? ? ? 48 C7 44 24 ? ? ? ? ? C6 44 24 ? ? 48 8D 05 ? ? ? ? 48 89 44 24 ? 4C 8D 0D ? ? ? ? 4C 8D 05 ? ? ? ? 48 8D 15 ? ? ? ?
#define SEATINDEX				0x1F8  // ATslPassBluezoneArea WeaponFire
#define REPLICATEDMOVEMENT		0x60
#define LASTVEHICLEPAWN			0x230


#define AIMBOTCIRCLESIZE		100.f
#define LOGCACHE				0

#endif