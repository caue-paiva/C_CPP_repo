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
     
    //macros

    //assert macros to assert 2,3 pointers to not be null at once, still retains info on what pointer failed the assert
    #define assert_2ptrs(p1,p2) assert(p1); assert(p2);
    #define assert_3ptrs(p1,p2,p3) assert_2ptrs(p1,p2); assert(p3);

    //simple max macro
    #define max(x, y)  ((x) > (y) ? (x) : (y))

    //frees a pointer and sets it to NULL
    #define null_free(ptr) \
      free(ptr);            \
      ptr = NULL
    

    // if a function  returns -1, this raises an error and prints the errno messages, this is useful for stdlib functions that change
    // errno val
    #define errno_check(X) do {                                          \
        if ((X) == -1) {                                                  \
            printf("ERROR: (FILE: %s , LINE: %d) -- %s \n",__FILE__,__LINE__, strerror(errno));\
            exit(-1);                                                       \
        }                                                                    \
        } while (0)
        //strerror comes from string.h and prints the messages from the errno error


    //get the size of an array
    #define arr_size(arr) (sizeof(arr) / sizeof((arr)[0]))


    // debug macros
    #define DEBUG 1 //debug or not flag
    #if DEBUG //printf with more debug info
        #define d_printf(...)                                             \
            printf("[DEBUG] (FILE: %s , LINE: %d) -- ",__FILE__,__LINE__); \
            printf(__VA_ARGS__);                                            \
            printf("\n")
    #else    //does not print anything
        #define d_printf(...) (void)0
    #endif                               
    



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

#endif