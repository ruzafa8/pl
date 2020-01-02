#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

typedef enum {
    /*EXITO*/
    SUCCESS,
    /*RELACIONADOS CON LOS TIPOS */
    TYPE_ERROR, // Error de tipo genérico
    TYPE_DOESNT_AGREE, // Los tipos no coinciden

    OUT_OF_BOUNDS_ERROR,
    /* RELACIONADOS CON LAS VARIABLES */
    VAR_NOT_FOUND_ERROR, //La variable no existe
    VAR_ALREADY_EXISTS_ERROR //La variable ya existe
}EXIT_CODE;

#endif // ERROR_H_INCLUDED
