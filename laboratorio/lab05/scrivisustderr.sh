#!/bin/bash

while read STRINGA; do
	WORD=${STRINGA%% *}
	echo "${WORD}" 1>&2
	echo EVVIVA
done;
