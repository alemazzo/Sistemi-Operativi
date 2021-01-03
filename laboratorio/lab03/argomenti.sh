#!/bin/bash

NUM=$#;
(( INDEX=2 ));
STR="";
while (( ${INDEX}<=NUM )); do
	STR="$STR ${!INDEX}";
	(( INDEX=INDEX+2 ));
done;

(( INDEX=1 ));
while (( ${INDEX}<=NUM )); do
	STR="$STR ${!INDEX}";
	(( INDEX=INDEX+2 ));
done;

echo $STR;
