
PRINT=1;

while read LINE; do
	if (( ${PRINT} == 1 )); then
		echo "${LINE}";
		(( PRINT=0 ));
	else
		(( PRINT=1 ));
	fi;
done;
