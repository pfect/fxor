#include <stdio.h>
#include <stdlib.h>
#include "fxor_types.h"
#include "handler.h"


int handle_errors(fxor_error *err) {
	int return_status;
	
	switch (err->code) {
		case NO_ERROR:
			return_status = CONTINUE;
			break;
		case PRINT_HELP:
			return_status = TERMINATE;
			fprintf(stdout, "Usage: fxor -i /in/file/path [-o /out/file/path][-k key][-hex|-bin|-dec|-string]\n");
			break;
		case NO_IN_FILE:
			return_status = TERMINATE;
			fprintf(stderr, "Include a file to xor with the -i option.\n");
			break;
		case INF_DUPL:
			return_status = TERMINATE;
			fprintf(stderr, "Multiple input files supplied, fxor currently only supports one.\n");
			break;
		case INF_OPEN_ERR:
			return_status = TERMINATE;
			fprintf(stderr, "Could not open %s for reading.\n", err->data);
			break;
		case OUTF_DUPL:
			return_status = CONTINUE;
			fprintf(stdout, "Multiple output files specified. Using the last provided.\n");
			break;
		case OUTF_OPEN_ERR:
			return_status = TERMINATE;
			fprintf(stderr, "Could not open %s for writing.\n", err->data);
			break;
		case KEY_DUPL:
			return_status = CONTINUE;
			fprintf(stdout, "Multiple keys specified. Using the last provided.\n");
			break;
		case INVALID_OPT:
			return_status = TERMINATE;
			fprintf(stderr, "%s is not a valid option.\n", err->data);
			break;
		case NO_ARG:
			return_status = TERMINATE;
			fprintf(stderr, "No argument provided for %s option.\n", err->data);
			break;
		case UNEVEN_FILE_LEN:
			return_status = CONTINUE;
			fprintf(stdout, "Length of file does not match length of key. We tried our best.\n");
			break;
		case INVALID_HEX_CHAR:
			return_status = TERMINATE;
			fprintf(stderr, "Key includes invalid hex characters. We all make mistakes.\n");
			break;
		case INVALID_BIN_CHAR:
			return_status = TERMINATE;
			fprintf(stderr, "Key includes invalid binary characters. We all make mistakes.\n");
			break;
		case INVALID_DEC_CHAR:
			return_status = TERMINATE;
			fprintf(stderr, "Key includes invalid decimal characters. We all make mistakes.\n");
			break;
		default:
			return_status = TERMINATE;
			fprintf(stderr, "Terminating due to unknown error, code: %d\n", err->code);
			break;
	}

	err->code = NO_ERROR;
	free(err->data);

	return return_status;
}
