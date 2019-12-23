#ifndef INTERFACE_H
#define INTERFACE_H

/* CORES PARA O TERMINAL */
#define  ALL_NORMAL "\033[0m"
#define  FG_BLACK   "\033[22;30m"
#define  FG_MAROON  "\033[22;31m"     /* Dark red */
#define  FG_GREEN   "\033[22;32m"
#define  FG_OLIVE   "\033[22;33m"     /* Brown */
#define  FG_NAVY    "\033[22;34m"     /* Dark blue */
#define  FG_PURPLE  "\033[22;35m"
#define  FG_TEAL    "\033[22;36m"     /* Dark cyan */
#define  FG_SILVER  "\033[22;37m"     /* Light gray */
#define  FG_GRAY    "\033[1;30m"      /* Dark gray */
#define  FG_RED     "\033[1;31m"      /* Light red */
#define  FG_LIME    "\033[1;32m"      /* Light green */
#define  FG_YELLOW  "\033[1;33m"
#define  FG_BLUE    "\033[1;34m"
#define  FG_FUCHSIA "\033[1;35m"      /* Light purple */
#define  FG_AQUA    "\033[1;36m"      /* Light cyan */
#define  FG_WHITE   "\033[1;37m"
#define  BG_BLACK   "\033[40m"
#define  BG_MAROON  "\033[41m"
#define  BG_GREEN   "\033[42m"
#define  BG_OLIVE   "\033[43m"
#define  BG_NAVY    "\033[44m"
#define  BG_PURPLE  "\033[45m"
#define  BG_TEAL    "\033[46m"
#define  BG_SILVER  "\033[47m"

/* SIMBOLOS ESPECIAIS */
#define RECT_SUP_DIR 187        // Canto superior direito
#define RECT_SUP_ESQ 201        // Canto superior esquerdo
#define RECT_INF_DIR 188        // Canto inferior direito
#define RECT_INF_ESQ 200        // Canto inferior esquerdo
#define RECT_BAR_HOR 205        // 
#define RECT_BAR_VER 186
#define DUAL_ARROW_D 175
#define DUAL_ARROW_E 175
#define RECT_CMP_BLK 219
#define RECT_EMP_BLK 176

/* TECLAS */
#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_RIGHT   77
#define KEY_LEFT    75

/* RETONOR */
#define SCR_SUCESSO 1
#define SCR_FAIL -1
#define SCR_PROCESSANDO -2

typedef struct threadLoadArgs TH_LOAD_ARGS;
typedef int (*CB_SCRLOAD) (TH_LOAD_ARGS *param);

typedef struct threadLoadArgs{
    int porcentagem;
    int isFinished;
    CB_SCRLOAD cb_scrload;
} TH_LOAD_ARGS;

/*
* @brief Defini a cor do terminal
*/
void scrClear();

/*
* @brief Reseta para a cor padrao
*/
void scrRstCor();

/*
* @brief Defini a cor do terminal
* @param char *cor - Texto a ser enviado
*/
void scrSetCor(char *cor);

/*
* @brief Printa texto com cor
* @param char *fgColor Constante da cor do texto
* @param char *bgColor constante da cor do fundo
* @param char *format - Texto a ser enviado
* @param ... - Argumentos
*/
void scrPrint(char *fgColor, char *bgColor, char *format, ...);

/*
* @brief Printa texto com cor e pula linha
* @param char *fgColor Constante da cor do texto
* @param char *bgColor constante da cor do fundo
* @param char *format - Texto a ser enviado
* @param ... - Argumentos
*/
void scrPrintLn(char *fgColor, char *bgColor, char *format, ...);

void scrPrintCoord (int x, int y, char *format, ...);

void scrPrintCoordColored (char *fgColor, char *bgColor, int x, int y, char *format, ...);

void scrDrawnRect(int x, int y, int width, int height);

void scrDrawnRectFill(int x, int y, int width, int height, char background);

int scrLoad(char *titulo, CB_SCRLOAD cbScrLoad);

#endif //MAP_H