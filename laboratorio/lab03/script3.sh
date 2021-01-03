#!/bin/bash
for name in ~; do
	echo "";
	echo "file is ${name}";
	ls -ld ${name};
done;
