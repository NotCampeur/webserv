#!/bin/bash

for file in requests/*; do
	[ -f "$file" ] || continue
	echo $file
	./webclient 1 $file 8080 8080
done
