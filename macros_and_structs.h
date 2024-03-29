/*
The purpose of this file is to write useful macros and to display how to modularize code by defining structs and their typedefs on headers,
so that they can be directly acessed (. or -> operators) from many different .c files

*/


#ifndef MACROS_STRUCTS_H
   #define MACROS_STRUCTS_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <assert.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <string.h>
     
    //macros below: 

    /*
    OBS: the do {...}  while(0)  macro pattern is useful for executing statements in multiple lines
    it can create macros safe and more robust to use inside if() and while() statements.
    
    
    */

    //assert macros to assert 2,3 pointers to not be null at once, still retains info on what pointer failed the assert
    #define assert_2ptrs(p1,p2) assert(p1); assert(p2);
    #define assert_3ptrs(p1,p2,p3) assert_2ptrs(p1,p2); assert(p3);

    //simple max and min macro
    #define max(x, y)  ((x) > (y) ? (x) : (y))

    #define min(x, y)  ((x) > (y) ? (y) : (x))

    //frees the pointer pointed by the double pointer and sets it to NULL, this CAN be used on a ptr passed to a func
    #define safe_free_double(double_ptr) do {\
      free(*(double_ptr));\
      *(double_ptr) = NULL;\
    } while(0)
    
    //frees a pointer and sets it to NULL, this CANT be used on a ptr passed to a func
    #define safe_free(ptr) do {\
      free((ptr));\
      (ptr) = NULL;\
    } while(0)
    
    // if a function  returns -1, this raises an error and prints the errno messages, this is useful for stdlib functions that change
    // errno val
    #define errno_check(X) do {\
        if ((X) == -1) {\
            printf("ERROR: (VAR NAME: %s , FILE: %s , LINE: %d) -- Error name: %s \n", #X ,__FILE__,__LINE__, strerror(errno));\
            exit(1);\
        }\
        } while (0)
        //strerror comes from string.h and prints the messages from the errno error


    //nullptr and errno check macro
    #define null_errno_check(ptr) do {\
        void* __null_errno_ptr = (ptr);\
        if((__null_errno_ptr) == NULL){\
           printf("NULL PTR ERROR: (VAR NAME: %s , FILE: %s , LINE: %d) -- Error name: %s \n", #ptr ,__FILE__,__LINE__, strerror(errno));\
           exit(1);\
        }\
    } while(0)

    #define err_exit(...) do {\
            printf("[ERROR] (FILE: %s , LINE: %d) -- ",__FILE__,__LINE__);\
            printf(__VA_ARGS__);\
            printf("\n");\
    } while(0)
    //used to check for null ptrs and displaying errno messages, useful for file opening routines

    // debug macros
    #define DEBUG 1 //debug or not flag
    #if DEBUG //printf with more debug info
        #define d_printf(...) do {\
            printf("[DEBUG] (FILE: %s , LINE: %d) -- ",__FILE__,__LINE__);\
            printf(__VA_ARGS__);\
            printf("\n");\
        } while(0)
    #else    //does not print anything
        #define d_printf(...) (void)0
    #endif  

    //single line debug printf macro, its reliant on a GCC ##__VA_ARGS__ variable so it might be less portable, it can also work if d_printf is called with no args
    //#define d_printf2(format, ...) printf("[DEBUG] (FILE: %s , LINE: %d) -- " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)



    //ATTENTION: warning arg needs to be a string
    #define warn_printf(warning) printf("[WARNING] %s (FILE: %s , LINE: %d) -- \n", (warning) ,__FILE__,__LINE__);\
  
    


    //generic func pointer macro
    #define fn_ptr(name,return_type,...)  return_type (*name)(__VA_ARGS__)      
    //use like this:  fn_ptr(name , return_arg , args1 ....) = func_name;


    //defines a function ptr type to an specific function signature (return and arg types)
    #define fn_ptr_t(name,return_type,...) typedef return_type (*name)(__VA_ARGS__)
    //good for reusability , use like this: 
    //    fn_ptr_t(add_t,int,int,int);
    //    add_t add_ptr = add;
                    
    

    // Very cool thing, if you declare a typedef for an struct or enum and name it varname_t it will be highlighted green on VScode
    typedef struct grafo grafo_t;
    typedef enum conexao conexao_t;
    typedef int valor_t;

    enum conexao {
        bidirecional = 0,
        entrada  = 1,
        saida = 2
    };

    struct grafo {
        valor_t valor;
        int num_conexoes;
        conexao_t tipo_conexao;
        grafo_t** conexoes;
    };


    typedef struct {
        const int max1;
        const int max2;
    } PARAM;

    //this pattern creates a struct with const values and then defines a macro variable that is a struct compound literal with some values
    //useful for centralizing macro constants in a struct for code config
    struct code_config {
        const int config1;
        const int config2;
        const int config3;
    };

    #define config (struct  code_config){.config1=3,.config2=5,.config3=9}


    //lookup tables
    


    //keys[key] need to be an unsigned int or a char

    // values assigned to keys need to be of the type of the declared array, in this case int
    const int command_num_lookup[] = {
        ['a'] = 1,
        ['s'] = 2,
        ['d'] = 3,
        ['m'] = 4,
    };

    // this is a bitfield struct and the int after the : signifies how many bits does each area of the struct hold
    struct bitfield {
        int area1 : 4;
        int area2 : 4;
        int area3 : 1;
        int area4 : 7;
    };

    // if you use functions like read() to read bits from a file, the contents of the read size are
    // parsed automatically to this bitfield struct, useful for FILE reading, or Network communication
    // other functions like write() to file also work with this

   // typedef struct bitfield bitfield_t;

  

#endif