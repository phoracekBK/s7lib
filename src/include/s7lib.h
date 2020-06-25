#ifndef _s7lib_H_
#define _s7lib_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <c_string/c_string.h>
#include <unistd.h>

#include <s7lib_parser.h>

struct _s7lib_;
typedef struct _s7lib_ s7lib;



s7lib * s7lib_new(char *, int, int, int);
bool s7lib_connect(s7lib *);
bool s7lib_disconnect(s7lib *);
bool s7lib_reconnect(s7lib *, uint8_t);
void s7lib_finalize(s7lib *);
uint8_t * s7lib_read(s7lib *, int, int);
bool s7lib_write(s7lib *, uint8_t *, int, int);

bool s7lib_read_bool(s7lib *, int, int);
bool s7lib_write_bool(s7lib *, int, int, bool);
int16_t s7lib_read_int(s7lib *, int);
bool s7lib_write_int(s7lib *, int, int16_t);
bool s7lib_write_dword(s7lib *, int, int32_t);
uint32_t s7lib_read_dword(s7lib *, int);
bool s7lib_write_real(s7lib *, int, float);
float s7lib_read_real(s7lib *, int);
bool s7lib_write_string(s7lib *, int, char *, uint8_t);
char * s7lib_read_string(s7lib *, int, uint8_t);



#endif
