### Nei commenti iche seguono vedete dei suggerimenti sull'algoritmo da
### seguire per produrre l'output corretto.
###
# I voti della seconda prova li devo mettere tutti nello standard output


# Poi devo mettere nello standard output i voti della prima prova
# ottenuti dagli studenti che non hanno un voto nella seconda prova

while read MATRICOLA STUDENTE; do
    if [[ `cat esame2.txt | grep $MATRICOLA` != "" ]]; then
        echo `cat esame2.txt | grep $MATRICOLA`
    else
        echo $MATRICOLA $STUDENTE;
    fi;
done < esame1.txt;

while read MATRICOLA STUDENTE; do
    if [[ `cat esame1.txt | grep $MATRICOLA` == "" ]]; then
        echo $MATRICOLA $STUDENTE;
    fi;
done < esame2.txt;


