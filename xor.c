#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fxor_types.h"
#include "xor.h"


void run_xor(fxor_opts * data, fxor_error * err) {

	fxor_key	key;
	char * 		in_buffer;
	char * 		out_buffer;
	int		fread_status;
	
	switch (data->key_format) {
		case HEX_FMT:
			err->code = build_hex_key(data->key, &key);
			break; 
		case BINARY_FMT:
			err->code = build_bin_key(data->key, &key);
			break;
		case DECIMAL_FMT:
			err->code = build_dec_key(data->key, &key);
			break;
		case UTF_8_FMT: //to be implemented
		case UTF_64_FMT:
		case ASCII_FMT:
			err->code = build_ascii_key(data->key, &key);
			break;
		default:
			err->code = INVALID_KEY_FMT; 
	}

	if ( err->code == NO_ERROR ) {
		in_buffer = (char*)malloc(sizeof(char) * key.len);
		out_buffer = (char*)malloc(sizeof(char) * key.len);
		 do {
			fread_status = fread(in_buffer, sizeof(char), key.len, data->in_file);
			for (int pos = 0; pos < fread_status; ++pos) {
				out_buffer[pos] = key.key[pos] ^ in_buffer[pos];
			}
			fwrite(out_buffer, sizeof(char), fread_status, data->out_file);
		} while ( fread_status == key.len );

		if ( fread_status != 0 ) {
			err->code = UNEVEN_FILE_LEN;
		}	
	} else {
		err->data = (char*)malloc(sizeof(char) * (strlen(data->key)+1));
		strcpy(err->data, data->key);
	}

	free(in_buffer);
	free(out_buffer);
	free(key.key);
}

unsigned char build_hex_key(char * in_key, fxor_key * ret_key) {
	int		in_key_len = strlen(in_key);
	int		e_key_len = in_key_len;
	unsigned char	return_code = NO_ERROR;
	int		pos_shift = 0;
	bool 		even_len;

	if ( in_key[1] == 'x' || in_key[1] == 'X') {
		e_key_len = e_key_len - 2;
		pos_shift = 2;
	}

	if ( e_key_len % 2 == 0 ) { 
		ret_key->len = e_key_len / 2;
		even_len = true;
	} else {
		ret_key->len = (e_key_len / 2) + 1;
		even_len = false;
	}

	ret_key->key = (char*)malloc(sizeof(char) * ret_key->len);
	memset(ret_key->key, 0, sizeof(char)*ret_key->len);

	for (int pos = pos_shift; pos < in_key_len; ++pos) {
		int shift;

		if ( even_len ) 
			shift = pos % 2 == 0 ? 4 : 0;
		else
			shift = pos % 2 == 0 ? 0 : 4;

		switch (in_key[pos]) {
			case '0':
				break;
			case '1':
				ret_key->key[(pos-pos_shift)/2] += ( 0x1 << shift );
				break;
			case '2':
				ret_key->key[(pos-pos_shift)/2] += ( 0x2 << shift );
				break;
			case '3':
				ret_key->key[(pos-pos_shift)/2] += ( 0x3 << shift );
				break;
			case '4':
				ret_key->key[(pos-pos_shift)/2] += ( 0x4 << shift );
				break;
			case '5':
				ret_key->key[(pos-pos_shift)/2] += ( 0x5 << shift );
				break;
			case '6':
				ret_key->key[(pos-pos_shift)/2] += ( 0x6 << shift );
				break;
			case '7':
				ret_key->key[(pos-pos_shift)/2] += ( 0x7 << shift );
				break;
			case '8':
				ret_key->key[(pos-pos_shift)/2] += ( 0x8 << shift );
				break;
			case '9':
				ret_key->key[(pos-pos_shift)/2] += ( 0x9 << shift );
				break;
			case 'A':
			case 'a':
				ret_key->key[(pos-pos_shift)/2] += ( 0xA << shift );
				break;
			case 'B':
			case 'b':
				ret_key->key[(pos-pos_shift)/2] += ( 0xB << shift );
				break;
			case 'C':
			case 'c':
				ret_key->key[(pos-pos_shift)/2] += ( 0xC << shift );
				break;
			case 'D':
			case 'd':
				ret_key->key[(pos-pos_shift)/2] += ( 0xD << shift );
				break;
			case 'E':
			case 'e':
				ret_key->key[(pos-pos_shift)/2] += ( 0xE << shift );
				break;
			case 'F':
			case 'f':
				ret_key->key[(pos-pos_shift)/2] += ( 0xF << shift );
				break;
			default:
				return_code = INVALID_HEX_CHAR;				
		}
		if (return_code != NO_ERROR)
			break;
	}
	return return_code;
}

unsigned char build_bin_key(char * in_key, fxor_key * ret_key) {       
	unsigned char	return_code = NO_ERROR;
	int		in_key_len = strlen(in_key);
	int		pos_shift;

	if ( in_key_len % 8 == 0 ) {
		ret_key->len = in_key_len / 8;
		pos_shift = 0;
	} else {
		ret_key->len = (in_key_len / 8) + 1;
		pos_shift = in_key_len % 8;
	}		

	ret_key->key = (char*)malloc(sizeof(char) * ret_key->len);
	memset(ret_key->key, 0, sizeof(char)*ret_key->len);

	for (int pos = 0; pos < in_key_len; ++pos) {
		if ( in_key[pos] == '0' ) {
			ret_key->key[(pos+pos_shift)/8] = ret_key->key[(pos+pos_shift)/8] << 1;
		} else if ( in_key[pos] == '1' ) {
			ret_key->key[(pos+pos_shift)/8] = (ret_key->key[(pos+pos_shift)/8] << 1) | 0x1;
		} else {
			return_code = INVALID_BIN_CHAR;
			break;
		}
	}


	return return_code;
}

unsigned char build_dec_key(char * in_key, fxor_key * ret_key) {
	unsigned char	return_code = NO_ERROR;
	long int	in_key_conv = 0;
	int		in_key_len = strlen(in_key);
	int		bits = 0;

	for (int i = 0; i < in_key_len; ++i) {
		if ( in_key[i] >= 0x30 && in_key[i] <= 0x39 ) {
			in_key_conv = (in_key_conv * 10) + (in_key[i]^0x30);  
		} else {
			return_code = INVALID_DEC_CHAR;
		}
	}
	
	ret_key->key = (char*)malloc(sizeof(char) * 8);
	memset(ret_key->key, 0, sizeof(char)*8);
	ret_key->len = 0;	

	while ( in_key_conv != 0 && return_code == NO_ERROR ) {
		ret_key->key[ret_key->len] = (ret_key->key[ret_key->len] << 1) | ((in_key_conv & 0x80000000) == 0x80000000);
		in_key_conv = in_key_conv << 1;
		if ( ++bits % 8 == 0 && ret_key->key[ret_key->len] != 0) {
			ret_key->len += 1;
		}
	}
	
	
	return return_code;
}
unsigned char build_ascii_key(char * in_key, fxor_key * ret_key) {
	unsigned char 	return_code = NO_ERROR;
	
	ret_key->len = strlen(in_key);
	ret_key->key = (char*)malloc(sizeof(char)*(ret_key->len));
	
	for (int pos = 0; pos < ret_key->len; ++pos) {
		ret_key->key[pos] = in_key[pos];
	}

	return return_code;
}

