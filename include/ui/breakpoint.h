#ifndef __UI_BREAKPOINT_H__
#define __UI_BREAKPOINT_H__

#include "common.h"

#define INT3_CODE 0xcc

typedef struct breakpoint {
	int NO;
	struct breakpoint *next;
	uint32_t addr;
	uint32_t inst;
	int type;
	uint32_t watch_value;
	char *watch_expr;
	/* TODO: Add more members if necessary */
} BP;

#endif
