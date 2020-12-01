#include <stdlib.h>

#define MACRO(x) do{\
                  int i;\
                  x = malloc(sizeof(int) * 10);\
                  if (x != NULL){\
                      for(i=-1000; i<=-991; i++) x[i+1000] = i;\
                  }\
                  } while(0);
