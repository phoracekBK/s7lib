#include <s7lib.h>
#include <stdio.h>
#include <stdlib.h>

void read_all_at_once(s7lib * s7lib_ref)
{
    uint8_t * byte_array = s7lib_read(s7lib_ref, 0, 534);

    printf("input bool: %s\n", s7lib_parser_read_bool(byte_array, 0, 0)==true ? "true" : "false");
    printf("input integer: %d\n", s7lib_parser_read_int(byte_array, 2));
    printf("input_dword: %u\n", s7lib_parser_read_dword(byte_array, 6));
    printf("input real: %f\n", s7lib_parser_read_real(byte_array, 14));

    char * input_string = s7lib_parser_read_string(byte_array, 22, 255);
    printf("input string: %s\n", input_string);
    free(input_string);

    s7lib_parser_write_bool(byte_array, 0,1,true);
    s7lib_parser_write_int(byte_array, 4, 510);
    s7lib_parser_write_dword(byte_array, 10, 0xFFFFFF);
    s7lib_parser_write_real(byte_array, 18, 3.14159);
    s7lib_parser_write_string(byte_array, 278, "Hello world from c-program", 255);

    s7lib_write(s7lib_ref, byte_array, 0, 534);
}

void read_separated(s7lib * s7lib_ref)
{
  printf("input bool: %s\n", s7lib_read_bool(s7lib_ref, 0, 0)==true ? "true" : "false");
  printf("input integer: %d\n", s7lib_read_int(s7lib_ref, 2));
  printf("input_dword: %u\n", s7lib_read_dword(s7lib_ref, 6));
  printf("input real: %f\n", s7lib_read_real(s7lib_ref, 14));
  char * input_string = s7lib_read_string(s7lib_ref, 22, 255);
  printf("input string: %s\n", input_string);
  free(input_string);

  //fflush(stdout);

  if (s7lib_write_bool(s7lib_ref, 0,1,true))
    printf("bool write true\n");
  else
    printf("bool write false\n");

  if(s7lib_write_int(s7lib_ref, 4, 510))
    printf("int write true\n");
  else
    printf("int write false\n");

  if(s7lib_write_dword(s7lib_ref, 10, 0xFFFFFF))
    printf("dword write true\n");
  else
    printf("dword write false\n");

  if(s7lib_write_real(s7lib_ref, 18, 3.14159))
    printf("real write true\n");
  else
    printf("real write false\n");

  if(s7lib_write_string(s7lib_ref, 278, "Hello world from c-program at once", 254))
    printf("string write true\n");
  else
    printf("string write false\n");


}


int main(int argv, char ** argc)
{

  s7lib * s7lib_ref = s7lib_new("192.168.2.1", 0, 1, 2);

  read_all_at_once(s7lib_ref);
  putchar('\n');
  read_separated(s7lib_ref);

  s7lib_finalize(s7lib_ref);

  return 0;
}
