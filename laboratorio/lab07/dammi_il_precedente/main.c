#include <stdlib.h>

unsigned int dammi_il_precedente(unsigned int x){
  static unsigned int prev = 0;
  unsigned int temp = prev;
  prev = x;
  return temp;
}

int main(){
  while(1){
    if(dammi_il_precedente(rand()) % 10 == 3) return 0;
  }  
}
