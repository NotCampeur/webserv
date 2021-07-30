#!/bin/bash

do_all() {
for file in requests/* 
do
	[ -f "$file" ] || continue
	echo $file
	./webclient 1 $file 8080 8080
done
}

if [ $# -eq 0 ]
then
	do_all
else
	./webclient 1 $1 8080 8080
fi
