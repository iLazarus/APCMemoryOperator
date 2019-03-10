#include "common.h"

driver drv;
graphics dx;
decrypt dpt;
mutex mx;

uint64_t g_UGname = 0;
uint64_t g_UWorld = 0;	//base->world
uint64_t g_GameInstance = 0;//world->inst
uint64_t g_ULevel = 0;		//world->level
uint64_t g_ULocalPlayer = 0;	//inst->local
uint64_t g_APlayerController = 0;//local->ctl
uint64_t g_UPlayerCameraManager = 0;
uint64_t g_USelf = 0;
uint64_t g_MeshSelf = 0;
PlayerData g_BestAimTarget;

bool esp = false;
bool autobot = false;
bool vehicle = false;
bool skeltch = true;
bool itemgoods = false;

uint32_t __ROL4__(uint32_t x, unsigned int count) {
	count %= 32;
	return (x << count) | (x >> (32 - count));
}

uint32_t __ROR4__(uint32_t x, unsigned int count) {
	count %= 32;
	return (x << (32 - count)) | (x >> count);
}

uint16_t __ROL2__(uint16_t x, unsigned int count) {
	count %= 16;
	return (x << count) | (x >> (16 - count));
}

uint16_t __ROR2__(uint16_t x, unsigned int count) {
	count %= 16;
	return (x << (16 - count)) | (x >> count);
}