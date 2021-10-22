#!/bin/bash

read input

for DIR in $input; do
     if [ -d "$DIR" ]; then
	ls $DIR | grep ".c$"
	ls $DIR | grep ".cpp$"
	#echo `grep '.c$' $DIR`
        #echo `grep '.cpp$' $DIR`
     fi
done

