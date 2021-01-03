#include <stdio.h>

#include <math.h>

static double salva;

double metaCoseno(double x){
  salva = cos(x)/2;
  return salva;
}
