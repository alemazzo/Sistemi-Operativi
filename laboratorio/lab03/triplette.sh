#!/bin/bash

for name1 in *; do
	for name2 in *; do
		for name3 in *; do
			echo "(${name1}, ${name2}, ${name3})";
		done;
	done;
done;
