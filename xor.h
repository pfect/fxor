#include "fxor_types.h"

#ifndef XOR_H
#define XOR_H

void run_xor(fxor_opts * data, fxor_error * err);
unsigned char build_hex_key(char * in_key, fxor_key * ret_key);
unsigned char build_bin_key(char * in_key, fxor_key * ret_key);
unsigned char build_dec_key(char * in_key, fxor_key * ret_key);
unsigned char build_ascii_key(char * in_key, fxor_key * ret_key);


#endif


