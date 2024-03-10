#include "macros_and_structs.h"

//static functions are only available in the file they are defined, they cant be linked or exported to other files
//naming them with __ also signifies its an internal func




static bool __func() {
   return false;
}

bool const_ptr_exp(){
   int a = 1;

   const int* pA = &a;  //this means that the DATA POINTED TO cant be changed

   int* const pA2 = &a;  // this means that the memory adress of the pA2 variable cant be changed, but the data it 
   // points to can be

   const int* const pA3 = &a;  // this combines the 2 above consts, neither the data or adress can be changed

}

bool const_structs_exp(){
   /*
   explaining how to use const in struct fields to create structs which are forced to have all their values set 
   at variable creation, this can be useful for enforcing this behavior and ensuring that structs have runtime consistency
   */

   typedef struct {
        const int max1;
        const int max2;
   } PARAM;
  
   //having const struct fields means they can only be initialized at variable definition, so below is allowed
   PARAM param1 = { .max1 = 3, .max2 = 7};

    // but this isnt:
    /*
    param1.max1 = 4; compile error
    
    */

  
   //without typedef
   struct param2 {
        const int max1;
        const int max2;
   } parameter = {3,7};

   // parameter.max1 = 5;  this is a compile error, bc the parameter struct was already initialized

   //this is allowed bc you are creating another struct variable
   struct param2 parameter2 = {.max1 = 3, .max2 =7};
}

int* fn_ptr_test(int* arg1){
   return arg1;
}

int add (int a, int b) {
    return a + b;
}

int* ptr_add(int* a, int*b, int c){
   int * ptr =  (int*) malloc(sizeof(int));

   *ptr = (*a) + (*b);
   
   return ptr;
}

int mixed_add(int a, int *b){
    return a + (*b);
}


int main(){

   int a = 4;
   int b = 7;

   (int) (*fn_ptr) (int,int*) = mixed_add;

   //fn_ptr_t(add_t,int,int,int);
   //add_t add_ptr = add;
   //fn_ptr(int*,int*,int*) add1 = ptr_add;
   //fn_ptr(int,int,int*) add1 = mixed_add;

   // printf("%d \n",add_ptr(a,b)  );


   //int open_data_file_flag = open("ahahah", O_APPEND);
   if (0)
    d_printf("var1 %d ptr1 %p", a, &b);
   else
     printf("");



  // errno_check(open_data_file_flag);
   

   //printf("%d \n",command_num_lookup['a']);

}