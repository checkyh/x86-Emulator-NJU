#include "common.h"

#include <unistd.h>

void load_table();
void main_loop();
void set_main_args(int, char * []);
void init_bp_pool();
void init_regex();
void init_signal();
void reg_test();
void init_device();
void init_sdl();
int enable_debug = false;
int quiet = false;

static void process_args(int argc, char *argv[]) {
	int opt;
	while( (opt = getopt(argc, argv, "dq")) != -1) {
		switch(opt) {
			case 'd'://调试模式
				enable_debug = true;
				break;
			case 'q'://安静模式
				quiet = true;
				break;
			default:
				test(0, "bad option = %s\n", optarg);
				break;
		}
	}

	test(argc > optind, "Program is not given\n");

	set_main_args(argc - optind, argv + optind);
}

int main(int argc, char *argv[]) {
	process_args(argc, argv);

	/* Perform some global initialization */
	init_regex();
	init_signal();
	init_bp_pool();
	load_table();


	/* Test whether the 'CPU_state' structure is organized correctly. */
	reg_test();
	init_device();
	init_sdl();
	main_loop();

	return 0;
}
