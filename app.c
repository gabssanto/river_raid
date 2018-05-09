#include <stdio.h>
#include "color_test.c"
#include <stdlib.h>
#include <time.h>

#define LINHAS 5
#define COLUNAS 10

void mover(char map[LINHAS][COLUNAS]){
    char move;
    int i, j;
    int x, y;
    scanf("%c", &move);
    //mover para cima//
    if (move == 'w'){
        for(i=0;i<LINHAS;i++){
            for(j=0;j<COLUNAS;j++){
                if(map[i][j] == 'C'){
                    x = j;
                    y = i;
                }
                
            }
        }
        if((y-1)<0){
            map[y][x] = 'C';
        }
        else{
            map[y][x] = '.';
            map[y-1][x] = 'C';
        }
    }
    //mover para baixo//
    if (move == 's'){
        for(i=0;i<LINHAS;i++){
            for(j=0;j<COLUNAS;j++){
                if(map[i][j] == 'C'){
                    x = j;
                    y = i;
                }
                
            }
        }//delimitar tamanho de novo dps//
        if((y+1)>4){
            map[y][x] = 'C';
        }
        else{
            map[y][x] = '.';
            map[y+1][x] = 'C';
        }
    }
    //mover para direita//
    if (move == 'd'){
        for(i=0;i<LINHAS;i++){
            for(j=0;j<COLUNAS;j++){
                if(map[i][j] == 'C'){
                    x = j;
                    y = i;
                }
                
            }
        }//delimitar tamanho de novo dps//
        if((x+1)> 9){
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
        if((x-1)<0){
            map[y][x] = 'C';
        }
        else{
            map[y][x] = '.';
            map[y][x-1] = 'C';
        }
    }
}

void printar(char map[LINHAS][COLUNAS]){
    int i,j;
    for(i=0;i<LINHAS;i++){
        for(j=0;j<COLUNAS;j++){
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
}


int main(){
    clock_t before = clock();
    int i=0, j=0;
    int jogo = 1;
    int cont = 0;
    int msec = 0, trigger = 250;


    char map[LINHAS][COLUNAS] = {
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'C', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
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