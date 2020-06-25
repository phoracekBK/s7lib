#include "include/s7lib_parser.h"


uint8_t * s7lib_parser_write_bool(uint8_t * byte_array, int byte_index, int bit_index, bool value)
{
	if(value == true)
		byte_array[byte_index] |= ((uint8_t) 1 << bit_index);
	else
		byte_array[byte_index] &= ((uint8_t) ~(1<< bit_index));

	return byte_array;
}

uint8_t * s7lib_parser_write_int(uint8_t * byte_array, int byte_index, int16_t value)
{
	byte_array[byte_index + 1] = ((uint8_t*) &value)[0];
	byte_array[byte_index] = ((uint8_t*) &value)[1];

	return byte_array;
}

uint8_t * s7lib_parser_write_dword(uint8_t * byte_array, int byte_index, int32_t value)
{
	byte_array[byte_index + 3] =  ((uint8_t*)&value)[0];
	byte_array[byte_index + 2] =  ((uint8_t*)&value)[1];
	byte_array[byte_index + 1] =  ((uint8_t*)&value)[2];
	byte_array[byte_index] =  ((uint8_t*)&value)[3];

	return byte_array;
}

uint8_t * s7lib_parser_write_real(uint8_t * byte_array, int byte_index, float value)
{
	byte_array[byte_index + 3] =  ((uint8_t*)&value)[0];
	byte_array[byte_index + 2] =  ((uint8_t*)&value)[1];
	byte_array[byte_index + 1] =  ((uint8_t*)&value)[2];
	byte_array[byte_index] =  ((uint8_t*)&value)[3];
	
  return byte_array;
}

static uint8_t s7lib_parser_get_string_length(int string_length, int size)
{
	return ((string_length >= size) ? size : string_length);
}

uint8_t * s7lib_parser_write_string(uint8_t * byte_array, int byte_index, char * string, uint8_t size)
{
	snprintf((char*) (byte_array+byte_index), size+3, "%c%c%s", size, s7lib_parser_get_string_length(strlen(string), size), string);

	return byte_array;
}

bool s7lib_parser_read_bool(uint8_t * byte_array, int byte_index, int bit_index)
{
	return (byte_array[byte_index] & (1 << bit_index));
}

int16_t s7lib_parser_read_int(uint8_t * byte_array, int byte_index)
{
	uint32_t value = (byte_array[byte_index+1]);
	((uint8_t*)&value)[1] = (byte_array[byte_index]);

	return value;
}

uint32_t s7lib_parser_read_dword(uint8_t * byte_array, int byte_index)
{
	uint32_t value = (byte_array[byte_index+3]);
	((uint8_t*)&value)[1] = (byte_array[byte_index+2]);
	((uint8_t*)&value)[2] = (byte_array[byte_index+1]);
	((uint8_t*)&value)[3] = (byte_array[byte_index]);

	return value;
}

float s7lib_parser_read_real(uint8_t * byte_array, int byte_index)
{
	float value = (byte_array[byte_index+3]);
	((uint8_t*)&value)[1] = (byte_array[byte_index+2]);
	((uint8_t*)&value)[2] = (byte_array[byte_index+1]);
	((uint8_t*)&value)[3] = (byte_array[byte_index]);

  return value;
}

char * s7lib_parser_read_string(uint8_t * byte_array, int byte_index, uint8_t size)
{
	uint8_t length = byte_array[byte_index + 1] > size ? size : byte_array[byte_index + 1];

	char * string = malloc(sizeof(char)*length+1);
	memset(string, 0, length+1);
	strncpy(string, (char*) (byte_array+byte_index+2), length);

	return string;
}
