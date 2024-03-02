#ifndef STRUCT_FN_PTR
  #define STRUCT_FN_PTR
   #include <stdlib.h>
   #include <stdio.h>
   #include <stdbool.h>
   #include <assert.h>
   #include <string.h>
   #include <errno.h>


   #define FILE_NAME_SIZE 256
   #define FILE_TYPE_SIZE 5

   #define assert_2ptrs(p1,p2) assert(p1); assert(p2);
   #define assert_3ptrs(p1,p2,p3) assert_2ptrs(p1,p2); assert(p3);

   #define null_errno_check(ptr) do {\
        void* __null_errno_ptr = (ptr);\
        if((__null_errno_ptr) == NULL){\
           printf("NULL PTR ERROR: (VAR NAME: %s , FILE: %s , LINE: %d) -- Error name: %s \n", #ptr ,__FILE__,__LINE__, strerror(errno));\
           return false;\
        }\
    } while(0)
    //checks if a file was opened correctly and returns false if it wasnt 
   
   
   //ATTENTION: warning arg needs to be a string
   #define warn_printf(warning) printf("[WARNING] %s (FILE: %s , LINE: %d) -- \n", (warning) ,__FILE__,__LINE__);\
   
   /*
   When working with function pointer sin struct its better to not use
   typedefs to declare them as shorter types, as that creates compilation issues
   its better to write the full synthax, which shouldnt be too verbose since you will only do it once
   */
   typedef struct file_s file_t; // Forward declaration

   //change mode to be a char mode[2] bc there are modes like "rb" or "wb"
   struct file_s {
      char name[FILE_NAME_SIZE];
      char mode;
      /// add other fields for more info 

      union {
         struct {
            uint (*get_file_size)(struct file_s*);
            bool (*append_to_other)(struct file_s*, struct file_s*);
            bool (*append_to_self)(struct file_s*, struct file_s*);
            bool (*copy_to_other)(struct file_s*, struct file_s*);
         } a;
         struct {
            uint (*get_file_size)(struct file_s*);
            bool (*copy_to_other)(struct file_s*, struct file_s*);
            bool (*copy_to_self)(struct file_s*, struct file_s*);
            bool (*append_to_other)(struct file_s*, struct file_s*);
         } w;
      
         struct {
            uint (*get_file_size)(struct file_s*);
            bool (*copy_to_other)(struct file_s*, struct file_s*);
            bool (*append_to_other)(struct file_s*, struct file_s*);
         } r;
      } fn;

     // const bool (*assign_fp) (struct file_s*, const char*);
   };


   /* 
   An interesting pattern for encapsulation is to define an internal static function
   and them make a struct that has a field with a fn_ptr to that static function
   so you are giving external users acess to the function only trought the struct

   To make this work you could define an external constructor like function that returns that struct with the function pointers set but the other values
   empty, this can be seen in the .c

   */

   

 
  


#endif