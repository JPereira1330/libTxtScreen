#include "libTxtScreen.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>

void scrClear(){
    printf("\033[2J");
}

void scrRstCor(){
    printf("%s", ALL_NORMAL);
}

void scrSetCor(char *cor){
    printf("%s", cor);
}

void scrPrint(char *fgColor, char *bgColor, char *format, ...){

    va_list v1;
    char buffer[1024];

    va_start(v1, format);
    vsnprintf(buffer, sizeof(buffer), format, v1);
    va_end(v1);

    if(fgColor != NULL)
        scrSetCor(fgColor);

    if(bgColor != NULL)
        scrSetCor(bgColor);
    
    printf("%s", buffer);

    if(fgColor != NULL || bgColor != NULL)
        scrRstCor();
}

void scrPrintLn(char *fgColor, char *bgColor, char *format, ...){

    va_list v1;
    char buffer[1024];

    va_start(v1, format);
    vsnprintf(buffer, sizeof(buffer), format, v1);
    scrPrint(fgColor, bgColor, buffer);
    va_end(v1);

    printf("\n");
}

void scrPrintCoord (int x, int y, char *format, ...){
    va_list v1;
    char buffer[1024];

    va_start(v1, format);
    vsnprintf(buffer, sizeof(buffer), format, v1);
    printf("\033[%d;%dH%s", x, y, buffer);
    va_end(v1);
}

void scrPrintCoordColored (char *fgColor, char *bgColor, int x, int y, char *format, ...){
    va_list v1;
    char buffer[1024];

    va_start(v1, format);
    vsnprintf(buffer, sizeof(buffer), format, v1);
    
    if(fgColor != NULL)
        scrSetCor(fgColor);

    if(bgColor != NULL)
        scrSetCor(bgColor);
    
    printf("\033[%d;%dH%s", x, y, buffer);

    if(fgColor != NULL || bgColor != NULL)
        scrRstCor();
        
    va_end(v1);
}


void *threadLoad(void *param){
    TH_LOAD_ARGS *thArgs;
    thArgs = (TH_LOAD_ARGS *) param;
    thArgs->cb_scrload(thArgs);
}

int scrLoad(char *titulo, CB_SCRLOAD cbScrLoad){

    int i, ret;
    char auxiliar[150];

    char cabecalho[25];
    int tam_cabecalho = 14;
    int atual_cabecalho = 0;
    char buffer_cabecalho[tam_cabecalho+1];

    pthread_t thread;
    TH_LOAD_ARGS thArgs;

    char tam_barra = 80;
    char buffer_barra[tam_barra+1];

    int contador = 0;
    char txtLoading[150];

    memset(cabecalho, 0, sizeof(cabecalho));
    memset(&thArgs, 0, sizeof(TH_LOAD_ARGS));
    snprintf(cabecalho, sizeof(cabecalho), titulo);

    thArgs.isFinished = SCR_PROCESSANDO;
    thArgs.cb_scrload = cbScrLoad;

    ret = pthread_create(&thread, NULL, threadLoad, &thArgs);

    do{

        if(strlen(buffer_cabecalho) <  tam_cabecalho){
            for(i = 0; i < tam_cabecalho; i++){
                buffer_cabecalho[i] = cabecalho[atual_cabecalho];
                if(atual_cabecalho < strlen(cabecalho)){
                    atual_cabecalho++;
                }
            }
        }
        
        atual_cabecalho = atual_cabecalho - (tam_cabecalho - 1);

        for(i = 0; i < tam_cabecalho; i++){
            buffer_cabecalho[i] = cabecalho[atual_cabecalho];
            if(atual_cabecalho < strlen(cabecalho)){
                atual_cabecalho++;
            }else{
                atual_cabecalho = 0;
            }
        }

        memset(buffer_barra, 0, sizeof(buffer_barra));
        for(i = 0; i < tam_barra; i++){

            if(buffer_barra != NULL){
                snprintf(auxiliar, sizeof(auxiliar), "%s", buffer_barra);
            }else{
                auxiliar == NULL;
            }

            if(i < (float) thArgs.porcentagem / 100 * (float) tam_barra){
                snprintf(buffer_barra, sizeof(buffer_barra), "%s%c", auxiliar, RECT_CMP_BLK);
            }else{
                snprintf(buffer_barra, sizeof(buffer_barra), "%s%c", auxiliar, RECT_EMP_BLK);
            }
        }

        memset(txtLoading, 0, sizeof(txtLoading));
        snprintf(txtLoading, sizeof(txtLoading), "%s |%s| %d%%", buffer_cabecalho, buffer_barra, thArgs.porcentagem);
        printf("\r%s", txtLoading);
        Sleep(300);
    }while(thArgs.isFinished == SCR_PROCESSANDO);

    pthread_join(thread, NULL);

    return SCR_SUCESSO;
}