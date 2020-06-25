#!/bin/sh


LIB="-I../src/include ../src/s7lib.c ../src/s7lib_parser.c -I$HOME/aclib/include/c_string/ $HOME/aclib/c_string/c_string.c -L../lib/ -lsnap7"
OUTPUT_PATH="."
OUTPUT_FILE_NAME="s7lib_test"
FILES="main.c"

gcc -Wall -O2 $FILES $LIB -o $OUTPUT_PATH/$OUTPUT_FILE_NAME && $OUTPUT_PATH/$OUTPUT_FILE_NAME
