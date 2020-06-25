#!/bin/sh

LIB_DIR="$HOME/s7lib"

if [ ! -d $LIB_DIR ] ; then
	mkdir $LIB_DIR -v
	mkdir $LIB_DIR/include/ -v
	mkdir $LIB_DIR/lib -v
fi

cp src/s7lib.c $LIB_DIR/ -v
cp src/s7lib_parser.c $LIB_DIR/ -v
cp src/include/s7lib.h $LIB_DIR/include/ -v
cp src/include/s7lib_parser.h $LIB_DIR/include/ -v
cp src/include/snap7.h $LIB_DIR/include/ -v
cp lib/snap7.dll $LIB_DIR/lib -v
cp lib/snap7.lib $LIB_DIR/lib -v
