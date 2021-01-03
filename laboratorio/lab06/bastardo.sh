#!/bin/bash

( sleep 2; ls -d /usr/include/ ) && { [[ (! ( "false" > "true" )) ||
( 3 -le 5 ) ]] ; } && if [[ $? < "01" ]] ; then exit 0; else exit 1 ; fi ;
exit $!
