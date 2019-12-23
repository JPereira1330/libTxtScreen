#ifndef G_WINDOW_H
#define G_WINDOW_H

#include "gType.h"

typedef struct gWindow *GWINDOW;

/**
 * @brief Inicializa windows
 * @return GWINDOW 
 */
GWINDOW gWindowInit();

/**
 * @brief Seta um valor no atributo da window
 * 
 * @param obj Window a ser manipulada
 * @param type Variavel a ser alterada
 * @param value Valor a ser atribuido a variavel
 * @return int 1 se funcionou, -1 para tipo errado 
 */
int gWindowSet(GWINDOW obj, int type, void *value);

/**
 * @brief Captura o valor do atribudo da window
 * 
 * @param obj window a ser utilizada
 * @param type Atributo a ser manipulado
 * @return void* 
 */
void *gWindowGet(GWINDOW obj, int type);

#endif