#include "gWindow.h"

#include <stdlib.h>

struct gWindow{
    int width;
    int height;
};

GWINDOW gWindowInit(){

    int ret;
    GWINDOW *win;

    win = (GWINDOW) malloc(sizeof(struct gWindow));
    if(win == NULL){
        printf(" [ERRO] Ocorreu um erro ao alocar memoria para Gwindow");
        return NULL;
    }

    memset(win, 0, sizeof(struct gWindow));
    
    // Inicializando com valores padrao
    ret = gWindowSet(win, VAR_HEIGHT, 50);
    if(ret != RET_OK){
        printf(" [ERRO] Ocorreu um erro definir altura padrao");
        return NULL;
    }

    gWindowSet(win, VAR_WIDTH, 50);
    if(ret != RET_OK){
        printf(" [ERRO] Ocorreu um erro ao definir largura padrao");
        return NULL;
    }

    return win;
}

int gWindowSet(GWINDOW obj, int type, void *value){

    switch (type){
        case VAR_HEIGHT:
            obj->height = (int) value;
            return RET_OK;
        case VAR_WIDTH:
            obj->width = (int) value;
            return RET_OK;
    }

    return RET_FAIL;
}

void *gWindowGet(GWINDOW obj, int type){

    switch (type){
        case VAR_HEIGHT:
            return obj->height;
        case VAR_WIDTH:
            return obj->width;
    }

    return RET_FAIL;
}