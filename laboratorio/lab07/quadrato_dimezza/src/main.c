#include <stdio.h>

#include "dimezza.h"
#include "quadrato.h"

double salva;

void main(){
  double var = 13.17;
  salva = metaCoseno(var);
  printf("%f", salva);
}
