#!/bin/bash

FINDPATH="$1";
FINDFILENAME="$2";

find ${FINDPATH} -name "${FINDFILENAME}" -print

