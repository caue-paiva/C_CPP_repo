#include "macros_and_structs.h"

//static functions are only available in the file they are defined, they cant be linked or exported to other files
//naming them with __ also signifies its an internal func
static bool __func() {
   return false;
}

int main(){

   int a = 4;
   int b = 7;
   int *pA =&a;
   //d_printf("teste %d %d %p",3,2,pA);

   const int* const PA = &a;

   *PA = 6;

   printf("%d\n", *PA);

   int arr[9] = {1,2,3,4,5,6,7,8};
   int val = arr_size(arr);

   //printf("%d \n",val);
}
