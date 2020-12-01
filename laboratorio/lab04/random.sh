
COUNT=0;
NUMBER=0;

while (( ${NUMBER} != 2 )); do
	(( NUMBER=$RANDOM%10 ));
	(( COUNT+=1 ));
	#echo "NUMBER = ${NUMBER}";
	#echo "COUNT = ${COUNT}";
done;
echo "${COUNT}"
