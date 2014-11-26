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
	char watch_expr[100];
	/* TODO: Add more members if necessary */
} BP;
void free_bp(int NO);
void new_bp(uint32_t addr);
void new_watch(char *q);
void printbreak();
void setbreak();
void free_bp(int NO);
void free_all(BP *head);
bool findwatch();
uint32_t break_addr;
void break_tcl(uint32_t addr);
int have_watch;
int break_state;
#endif
