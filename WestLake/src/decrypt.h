#pragma once
#ifndef DECRYPT_H
#define DECRYPT_H

#include <stdint.h>

class decrypt
{
public:
	decrypt();
	~decrypt();

	uint64_t de_world(uint64_t world);
	uint64_t de_gnames(uint64_t gnames);
	uint64_t de_level(uint64_t level);
	uint64_t de_actor(uint64_t actor);
	uint64_t de_inst(uint64_t inst);
	uint64_t de_local(uint64_t local);
	uint64_t de_controller(uint64_t controller);
	uint64_t de_prop(uint64_t prop);
};

#endif