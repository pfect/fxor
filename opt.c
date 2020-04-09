#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "opt.h"
#include "fxor_types.h"


void parse_opts(const int argc, char ** argv, fxor_opts *opts, fxor_error *err) {
	//Initialize defaults	
	err->code = 		ERR_CODE_DEFAULT;
	err->data = 		ERR_DATA_DEFAULT;	
	opts->in_file = 	IN_DEFAULT;
	opts->out_file = 	OUT_DEFAULT;
	opts->key = 		(char*)malloc(sizeof(char) * KEY_DEFAULT_LEN);
				strcpy(opts->key, KEY_DEFAULT);
	opts->key_format = 	KEY_FMT_DEFAULT;	
	
	//Check for existence of arguments
	if ( argc == 1 ) {
		err->code = PRINT_HELP;
	} else {
		for (int arg = 1; arg < argc; ++arg) {
			//Parse input file
			if ( strcmp(argv[arg], INF_OPT) == 0 || strcmp(argv[arg], INF_OPT_LONG) == 0 ) {
				if ( opts->in_file != IN_DEFAULT ) {
					err->code = INF_DUPL;
					break;
				} if ( arg == argc - 1 ) {
					err->code = NO_ARG;
					err->data = (char *)malloc(sizeof(char) * (strlen(argv[arg])+1));
					strcpy(err->data, argv[arg]);
					break;
				}
				opts->in_file = fopen(argv[arg+1], "rb");
				if (!opts->in_file) {
					err->code = INF_OPEN_ERR;
					err->data = (char *)malloc(sizeof(char) * (strlen(argv[arg+1])+1));
					strcpy(err->data, argv[arg+1]);
					break;	
				}
				++arg;
			}
			//Parse output file
			else if ( strcmp(argv[arg], OUTF_OPT) == 0 || strcmp(argv[arg], OUTF_OPT_LONG) == 0 ) {
				if ( opts->out_file != OUT_DEFAULT ) {
					err->code = OUTF_DUPL;
				} if ( arg == argc - 1 ) {
					err->code = NO_ARG;
					err->data = (char *)malloc(sizeof(char) * (strlen(argv[arg])+1));
					strcpy(err->data, argv[arg]);
					break;
				}
				opts->out_file = fopen(argv[arg+1], "wb");
				if ( !opts->out_file ) {
					err->code = OUTF_OPEN_ERR;
					err->data = (char *)malloc(sizeof(char) * (strlen(argv[arg+1])+1));
					strcpy(err->data, argv[arg+1]);
					break;
				}
				++arg;
			}
			//Parse key
			else if ( strcmp(argv[arg], KEY_OPT) == 0 || strcmp(argv[arg], KEY_OPT_LONG) == 0 ) {
				if ( arg == argc - 1 ) {
					err->code = NO_ARG;
					err->data = (char *)malloc(sizeof(char) * (strlen(argv[arg])+1));
					strcpy(err->data, argv[arg]);
					break;
				}
				opts->key = (char *)malloc(sizeof(char) * (strlen(argv[arg+1])+1));
				strcpy(opts->key, argv[arg+1]);
				++arg;
			}
			//Parse key format NEED TO IMPLEMENT UTF-8 AND UTF-64
			else if ( strcmp(argv[arg], HEX_FMT_OPT) == 0 ) {
				opts->key_format = HEX_FMT;
			} else if ( strcmp(argv[arg], BINARY_FMT_OPT) == 0 ) {
				opts->key_format = BINARY_FMT;
			} else if ( strcmp(argv[arg], DECIMAL_FMT_OPT) == 0 ) {
				opts->key_format = DECIMAL_FMT;
			} else if ( strcmp(argv[arg], ASCII_FMT_OPT) == 0 ) {
				opts->key_format = ASCII_FMT;
			} else if ( strcmp(argv[arg], UTF_8_FMT_OPT) == 0 ) {
				opts->key_format = ASCII_FMT;
			} else if ( strcmp(argv[arg], UTF_16_FMT_OPT) == 0 ) {
				opts->key_format = ASCII_FMT;
			}
			
			//Report invalid options
			else {
				err->code = INVALID_OPT;
				err->data = (char *)malloc(sizeof(char) * (strlen(argv[arg])+1));
				strcpy(err->data, argv[arg]);
				break;
			}
		}
	
		//check for required options left unset
		if ( opts->in_file == IN_DEFAULT ) {
			err->code = NO_IN_FILE;
		}
	}

} 
