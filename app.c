#include <stdio.h>
#include "color_test.c"
#include <stdlib.h>
/*#include <ncurses.h>*/
#include <time.h>

#define LINHAS 5 //10
#define COLUNAS 10 //135

void mover(char map[LINHAS][COLUNAS]){
    char move;
    int i, j;
    int x, y;
    /*set not enter(only on unix)*/
    system ("/bin/stty raw");

    move = getchar();
    /*scanf("%c", &move);*/
    /*mover para cima*/
    if (move == 'w'){
        for(i=0;i<LINHAS;i++){
            for(j=0;j<COLUNAS;j++){
                if(map[i][j] == 'C'){
                    x = j;
                    y = i;
                }
                
            }
        }
        if((y-1)<1){
            map[y][x] = 'C';
        }
        else{
            map[y][x] = '.';
            map[y-1][x] = 'C';
        }
    }
    /*mover para baixo*/
    if (move == 's'){
        for(i=0;i<LINHAS;i++){
            for(j=0;j<COLUNAS;j++){
                if(map[i][j] == 'C'){
                    x = j;
                    y = i;
                }
                
            }
        }/*delimitar tamanho de novo dps*/
        if((y+1)>3){
            map[y][x] = 'C';
        }
        else{
            map[y][x] = '.';
            map[y+1][x] = 'C';
        }
    }
    /*mover para direita*/
    if (move == 'd'){
        for(i=0;i<LINHAS;i++){
            for(j=0;j<COLUNAS;j++){
                if(map[i][j] == 'C'){
                    x = j;
                    y = i;
                }
                
            }
        }/*delimitar tamanho de novo dps*/
        if((x+1)> 8){
            map[y][x] = 'C';
        }
        else{
            map[y][x] = '.';
            map[y][x+1] = 'C';
        }
    }
    if (move == 'a'){
        for(i=0;i<LINHAS;i++){
            for(j=0;j<COLUNAS;j++){
                if(map[i][j] == 'C'){
                    x = j;
                    y = i;
                }
                
            }
        }
        if((x-1)<1){
            map[y][x] = 'C';
        }
        else{
            map[y][x] = '.';
            map[y][x-1] = 'C';
        }
    }/*set enter again (only on unix)*/
    system ("/bin/stty cooked");
}
/*printar o mapa do jogo com as modificacoes*/
void printar(char map[LINHAS][COLUNAS]){
    int i,j;
    for(i=0;i<LINHAS;i++){
        for(j=0;j<COLUNAS;j++){
            if(map[i][j] == 'C'){
                printf(ANSI_COLOR_RED ANSI_COLOR_BK_RED "%c" ANSI_COLOR_RESET, map[i][j]);
            }
            /*Arrumar tamanho do vetor*/
            else if(i==0 || j==0 || i==9 || j==9 || i ==4){
                printf(ANSI_COLOR_WHITE ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
                /*printf("%c",map[i][j]);*/
            }else {
                printf(ANSI_COLOR_BLUE ANSI_COLOR_BK_BLUE "%c" ANSI_COLOR_RESET, map[i][j]);
            }
        }
        printf("\n");
    }
}


int main(){
    clock_t before = clock();
    int jogo = 1;
    int msec = 0, trigger = 250;

    char map[LINHAS][COLUNAS] = {
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', 'C', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        
    };
    
while(jogo == 1){
    do {
        clock_t difference = clock() - before;
        msec = difference * 1000 / CLOCKS_PER_SEC;
    } while ( msec < trigger );
    msec = 0;
    system(CLEAR);
    printar(map);
    mover(map);
    before = clock();
 }
    return 0;
}
