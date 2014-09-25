#ifndef __UI_BREAKPOINT_H__
#define __UI_BREAKPOINT_H__

#include "common.h"

#define INT3_CODE 0xcc

typedef struct breakpoint {
	int NO;
	struct breakpoint *next;
	uint32_t addr;
	uint32_t inst;
	/* TODO: Add more members if necessary */


} BP;

#endif
