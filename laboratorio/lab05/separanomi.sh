#!/bin/bash

P=${PATH//":"/"\n"}
P=${P//"/"/" "}
echo -e $P
