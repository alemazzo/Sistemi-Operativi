#!/bin/bash

NUM=$#;
while (( NUM > 0 )); do
	echo ${!NUM};
	(( NUM=NUM-1 ));
done;
