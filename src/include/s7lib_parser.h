#ifndef _S7LIB_PARSER_H_
#define _S7LIB_PARSER_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

uint8_t * s7lib_parser_write_bool(uint8_t *, int, int, bool);
uint8_t * s7lib_parser_write_int(uint8_t *, int, int16_t);
uint8_t * s7lib_parser_write_dword(uint8_t *, int, int32_t);
uint8_t * s7lib_parser_write_real(uint8_t *, int, float);
uint8_t * s7lib_parser_write_string(uint8_t *, int, char *, uint8_t);

bool s7lib_parser_read_bool(uint8_t *, int, int);
int16_t s7lib_parser_read_int(uint8_t *, int);
uint32_t s7lib_parser_read_dword(uint8_t *, int);
float s7lib_parser_read_real(uint8_t *, int);
char * s7lib_parser_read_string(uint8_t *, int, uint8_t);


#endif
