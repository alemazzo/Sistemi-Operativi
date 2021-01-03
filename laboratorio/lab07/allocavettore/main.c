#include <stdio.h>
#include "macro.h"

int main(){
  int i;
  int *ptr;
  MACRO(ptr);
  if (ptr != NULL){
    for(i = -19; i <= -10; i++){
      ptr[i+19] = i;
    }
  }

  return 0;
}
