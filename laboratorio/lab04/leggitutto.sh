
exec {FD}<./miofileNoNL.txt;
if (( $? == 0 )); then
	while read -u ${FD} LINE; [[ $? == 0 || ${LINE} != "" ]]; do
		echo ${LINE};
	done;
	exec {FD}>&-;
fi;

