NUM=$1;
RISULTATO=1;
while (( $NUM>1 )); do
	((RISULTATO=RISULTATO*$NUM));
	((NUM=$NUM-1));
done;
echo $RISULTATO;
