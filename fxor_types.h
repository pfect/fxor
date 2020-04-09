#ifndef FXOR_TYPES_H
#define	FXOR_TYPES_H

typedef struct fxor_opts {
	FILE 	*in_file;
	FILE	*out_file;
	char	*key;
	int	 key_format;	

} fxor_opts;

#define		IN_DEFAULT	NULL
#define		OUT_DEFAULT	stdout
#define		KEY_DEFAULT	"FF"
#define		KEY_DEFAULT_LEN 2
#define		KEY_FMT_DEFAULT	HEX_FMT

#define		HEX_FMT		0
#define		BINARY_FMT	1
#define		DECIMAL_FMT	2
#define		ASCII_FMT	3
#define		UTF_8_FMT	4
#define		UTF_64_FMT	5


//Error handling types

typedef struct fxor_error {
	unsigned char 	code;
	char * 		data;
} fxor_error;

#define		ERR_CODE_DEFAULT	NO_ERROR
#define		ERR_DATA_DEFAULT	NULL

#define		NO_ERROR		0
#define		PRINT_HELP		1
#define		NO_IN_FILE		2
#define		INF_DUPL		3
#define		INF_OPEN_ERR		4
#define		OUTF_DUPL		5
#define		OUTF_OPEN_ERR		6
#define		KEY_DUPL		7
#define		INVALID_OPT		8
#define		NO_ARG			9
#define		INVALID_KEY_FMT 	10
#define		UNEVEN_FILE_LEN		11
#define		INVALID_HEX_CHAR	12
#define		INVALID_BIN_CHAR	13
#define		INVALID_DEC_CHAR	14

#define		TERMINATE	1
#define		CONTINUE	0

//Command line option types

#define		ABBR_OPT_LEN		2
#define		INF_OPT			"-i"
#define		INF_OPT_LONG		"--in-file"
#define		INF_OPT_LONG_LEN	9
#define		OUTF_OPT		"-o"
#define		OUTF_OPT_LONG		"--out-file"
#define		OUTF_OPT_LONG_LEN	10
#define		KEY_OPT			"-k"
#define		KEY_OPT_LONG		"--key"
#define		KEY_OPT_LONG_LEN	5
#define		HEX_FMT_OPT		"-hex"
#define		BINARY_FMT_OPT		"-bin"
#define		DECIMAL_FMT_OPT		"-dec"
#define		ASCII_FMT_OPT		"-string"
#define		UTF_8_FMT_OPT		"-utf8"
#define		UTF_16_FMT_OPT		"-utf64"

typedef struct fxor_key {
	char	*	key;
	int		len;
} fxor_key;

#endif
