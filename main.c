#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "fxor_types.h"
#include "opt.h"
#include "handler.h"
#include "xor.h"


void exit_gracefully(fxor_opts *opts, char exit_code);

int main(int argc, char ** argv) {
	fxor_opts	user_opts;
	fxor_error	err;

	parse_opts(argc, argv, &user_opts, &err);
	if ( handle_errors(&err) ) {
		exit_gracefully(&user_opts, EXIT_FAILURE);
	}
	
	run_xor(&user_opts, &err);
	if ( handle_errors(&err) ) {
		exit_gracefully(&user_opts, EXIT_FAILURE);
	} else {
		exit_gracefully(&user_opts, EXIT_SUCCESS);
	}
}


void exit_gracefully(fxor_opts *opts, char exit_code) {
	if ( opts->in_file != NULL ) {
		fclose(opts->in_file);
	}
	if ( opts->out_file != NULL && opts->out_file != stdout ) {
		fclose(opts->out_file);
	}
	free(opts->key);

	exit(exit_code);
}
