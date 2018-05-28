/* 
Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao
Algoritmos e Programação de Computadores – 1/2018
Aluno(a): Gabriel Oliveira do Espirito Santo
Matricula: 180041835
Turma: A
Versão do compilador:  gcc version 7.2.0
Descricao: Jogo baseado no classico river raid. 
Metodo de compilacao: gcc -ansi -o 180041835_01 180041835_01.c
*/

#include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>

    #ifdef _WIN32
        #define CLEAR "cls"
    #else
        #define CLEAR "clear"
    #endif

    #ifndef _WIN32
    int kbhit(){
    struct termios oldt, newt;
    int ch, oldf;
    tcgetattr(STDIN_FILENO,&oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF){
    ungetc(ch,stdin);
    return 1;
    }
    return 0;
    }
    int getch(void) {
    int ch;
    struct termios oldt;
    struct termios newt;
    tcgetattr(STDIN_FILENO,&oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
    }
    #else
    #include <conio.h>
    #endif

    #define LINHAS 10
    #define COLUNAS 135

    #define ANSI_COLOR_BK_RED     "\x1b[41m"
    #define ANSI_COLOR_BK_GREEN   "\x1b[42m"
    #define ANSI_COLOR_BK_YELLOW  "\x1b[43m"
    #define ANSI_COLOR_BK_BLUE    "\x1b[44m"
    #define ANSI_COLOR_BK_MAGENTA "\x1b[45m"
    #define ANSI_COLOR_BK_CYAN    "\x1b[46m"
    #define ANSI_COLOR_BK_WHITE   "\x1b[47m"

    #define ANSI_COLOR_RED     "\x1b[31m"
    #define ANSI_COLOR_GREEN   "\x1b[32m"
    #define ANSI_COLOR_YELLOW  "\x1b[33m"
    #define ANSI_COLOR_BLUE    "\x1b[34m"
    #define ANSI_COLOR_MAGENTA "\x1b[35m"
    #define ANSI_COLOR_CYAN    "\x1b[36m"
    #define ANSI_COLOR_WHITE  "\x1B[37m"
    #define ANSI_COLOR_BLACK "\033[22;30m"
    #define ANSI_COLOR_BK_BLACK "\033[22;40m"

    #define ANSI_COLOR_RESET   "\x1b[0m"

    #define LINHAS 10
#define COLUNAS 135


int jogo = 0; /*inicializar o jogo*/
int personagemcor = 1; /*cor personagem padrao*/
int bordascor = 4; /*cor das bordas padrao*/
int tirocor = 4; /*cor do tiro padrao*/
int configpontos = 0; /*ativa ou desativa ganhar pontos por segundo nas configuracoes*/
int dificuldade = 1; /*alterar a dificuldade do jogo*/
int sair; /*definir saida do jogo*/

void jogodificuldade(){
    system(CLEAR);
    int escolha;
    printf("Escolha a dificuldade do jogo\n");
    printf("1 - Facil\n"); 
    printf("2 - Medio\n");
    printf("3 - Dicifil\n");

    printf("Escolha a dificuldade: ");
    scanf("%d", &escolha);
    while(escolha != 1 && escolha != 2 && escolha != 3){
        printf("Opcao invalida, ");
        printf("Escolha sua opcao: ");
        scanf("%d", &escolha);
    }
    if(escolha == 1){
        dificuldade = 1;
        gamemenu();
    }
    if(escolha == 2){
        dificuldade = 2;
        gamemenu();
    }
    if(escolha == 3){
        dificuldade = 3;
        gamemenu();
    }
}
/*tela de game over*/
void gameover(int *pontos, int *printcombustivel){
    system(CLEAR);
    int i,j;
    printf("Game over\n");
    if(*printcombustivel <= 0){
        printf("Seu combustivel acabou\n");
    }
    else{
        printf("Voce morreu\n");
    }
    printf("Pontos obtidos = %d\n", *pontos);
    getch();
}

/*instrucoes do jogo*/
void instrucoes(){
    system(CLEAR);
    int escolha;
    printf("Instrucoes :\n");
    printf("|   Neste jogo voce deve destruir os inimigos marcados com um X e coletar o combustivel marcado com um F\n");
    printf("|   Voce pode mudar a cor do personagem, do tiro e da borda do mapa ao entrar nas configuracoes\n");
    printf("|   Nas configuracoes voce tambem pode ativar a pontuacao por segundo, caso deseje\n");
    printf("|   Para mover o personagem voce pode usar:\n");
    printf("|   |   w para mover o personagem para cima\n");
    printf("|   |   s para mover o personagem para baixo\n");
    printf("|   |   d para atirar e destruir o inimigo (X) e destruir o combustivel(F)\n");
    printf("|   Caso seu combustivel chegue a 0 ou voce seja atingido por um inimigo voce morre\n");
    printf("|   Lembre que os inimigos sempre se movem da esquerda para a direita\n");
    printf("|   Boa sorte, divirta-se\n");
    printf("Digite 1 para voltar ao menu: ");
    scanf("%d", &escolha);
    while(escolha != 1){
        printf("Opcao invalida, ");
        printf("digite 1 para voltar ao menu: ");
        scanf("%d", &escolha);
    }
    if(escolha == 1){
        gamemenu();
    }
}

/*alterar a cor da nave*/
void corpersonagem(){
    system(CLEAR);
    int escolha;
    printf("Escolha a cor do seu personagem\n");
    printf("1 - Vermelho "); 
    printf(ANSI_COLOR_RED     "C"     ANSI_COLOR_RESET "\n");
    printf("2 - Verde ");
    printf(ANSI_COLOR_GREEN   "C"   ANSI_COLOR_RESET "\n");
    printf("3 - Amarelo ");
    printf(ANSI_COLOR_YELLOW  "C"  ANSI_COLOR_RESET "\n");
    printf("4 - Azul ");
    printf(ANSI_COLOR_BLUE    "C"    ANSI_COLOR_RESET "\n");
    printf("5 - Magenta ");
    printf(ANSI_COLOR_MAGENTA "C" ANSI_COLOR_RESET "\n");
    printf("6 - Ciano ");
    printf(ANSI_COLOR_CYAN    "C"    ANSI_COLOR_RESET "\n");
    printf("7 - Preto ");
    printf(ANSI_COLOR_BLACK    "C"    ANSI_COLOR_RESET "\n");

    printf("Escolha a opcao para alterar a cor da nave: ");
    scanf("%d", &escolha);
    while(escolha != 1 && escolha != 2 && escolha != 3 && escolha != 4 && escolha != 5 && escolha != 6 && escolha != 7){
        printf("Opcao invalida, ");
        printf("Escolha sua opcao: ");
        scanf("%d", &escolha);
    }
    if(escolha == 1){
        personagemcor = 1;
        gamemenu();
    }
    if(escolha == 2){
        personagemcor = 2;
        gamemenu();
    }
    if(escolha == 3){
        personagemcor = 3;
        gamemenu();
    }
    if(escolha == 4){
        personagemcor = 4;
        gamemenu();
    }
    if(escolha == 5){
        personagemcor = 5;
        gamemenu();
    }
    if(escolha == 6){
        personagemcor = 6;
        gamemenu();
    }
    if(escolha == 7){
        personagemcor = 7;
        gamemenu();
    }
}

void cortiros(){
    system(CLEAR);
    int escolha;
    printf("Escolha a cor do seu tiro\n");
    printf("1 - Vermelho "); 
    printf(ANSI_COLOR_RED     ">"     ANSI_COLOR_RESET "\n");
    printf("2 - Verde ");
    printf(ANSI_COLOR_GREEN    ">"   ANSI_COLOR_RESET "\n");
    printf("3 - Amarelo ");
    printf(ANSI_COLOR_YELLOW   ">"  ANSI_COLOR_RESET "\n");
    printf("4 - Azul ");
    printf(ANSI_COLOR_BLUE     ">"    ANSI_COLOR_RESET "\n");
    printf("5 - Magenta ");
    printf(ANSI_COLOR_MAGENTA  ">" ANSI_COLOR_RESET "\n");
    printf("6 - Ciano ");
    printf(ANSI_COLOR_CYAN     ">"    ANSI_COLOR_RESET "\n");
    printf("7 - Preto ");
    printf(ANSI_COLOR_BLACK    ">"    ANSI_COLOR_RESET "\n");

    printf("Escolha a opcao para alterar a cor do seu tiro: ");
    scanf("%d", &escolha);
    while(escolha != 1 && escolha != 2 && escolha != 3 && escolha != 4 && escolha != 5 && escolha != 6 && escolha != 7){
        printf("Opcao invalida, ");
        printf("Escolha sua opcao: ");
        scanf("%d", &escolha);
    }
    if(escolha == 1){
        tirocor = 1;
        gamemenu();
    }
    if(escolha == 2){
        tirocor = 2;
        gamemenu();
    }
    if(escolha == 3){
        tirocor = 3;
        gamemenu();
    }
    if(escolha == 4){
        tirocor = 4;
        gamemenu();
    }
    if(escolha == 5){
        tirocor = 5;
        gamemenu();
    }
    if(escolha == 6){
        tirocor = 6;
        gamemenu();
    }
    if(escolha == 7){
        tirocor = 7;
        gamemenu();
    }

}

/*alterar a cor das bordas do mapa*/
void corbordas(){
    system(CLEAR);
    int escolha;
    printf("Escolha a cor da borda mapa\n");
    printf("1 - Vermelho "); 
    printf(ANSI_COLOR_RED ANSI_COLOR_BK_RED     "C"     ANSI_COLOR_RESET "\n");
    printf("2 - Verde ");
    printf(ANSI_COLOR_GREEN ANSI_COLOR_BK_GREEN   "C"   ANSI_COLOR_RESET "\n");
    printf("3 - Amarelo ");
    printf(ANSI_COLOR_YELLOW ANSI_COLOR_BK_YELLOW  "C"  ANSI_COLOR_RESET "\n");
    printf("4 - Azul ");
    printf(ANSI_COLOR_BLUE ANSI_COLOR_BK_BLUE    "C"    ANSI_COLOR_RESET "\n");
    printf("5 - Magenta ");
    printf(ANSI_COLOR_MAGENTA ANSI_COLOR_BK_MAGENTA "C" ANSI_COLOR_RESET "\n");
    printf("6 - Ciano ");
    printf(ANSI_COLOR_CYAN ANSI_COLOR_BK_CYAN    "C"    ANSI_COLOR_RESET "\n");
    printf("7 - Preto ");
    printf(ANSI_COLOR_BLACK ANSI_COLOR_BK_BLACK    "C"    ANSI_COLOR_RESET "\n");

    printf("Escolha a opcao para alterar a cor do seu mapa: ");
    scanf("%d", &escolha);
    while(escolha != 1 && escolha != 2 && escolha != 3 && escolha != 4 && escolha != 5 && escolha != 6 && escolha != 7){
        printf("Opcao invalida, ");
        printf("Escolha sua opcao: ");
        scanf("%d", &escolha);
    }
    if(escolha == 1){
        bordascor = 1;
        gamemenu();
    }
    if(escolha == 2){
        bordascor = 2;
        gamemenu();
    }
    if(escolha == 3){
        bordascor = 3;
        gamemenu();
    }
    if(escolha == 4){
        bordascor = 4;
        gamemenu();
    }
    if(escolha == 5){
        bordascor = 5;
        gamemenu();
    }
    if(escolha == 6){
        bordascor = 6;
        gamemenu();
    }
    if(escolha == 7){
        bordascor = 7;
        gamemenu();
    }
}

/*configuracoes do jogo*/
void configuracoes(){
    system(CLEAR);
    int escolha;
    printf("1 - Selecione para alterar a cor da nave\n");
    printf("2 - Selecione para alterar a cor da borda do mapa\n");
    printf("3 - Selecione para alterar a cor do tiro\n");
    printf("4 - Selecione para ativar a pontuacao por segundo\n");
    printf("5 - Selecione para alterar a dificuldade\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);
    while(escolha != 1 && escolha != 2 && escolha != 3 && escolha != 4 && escolha != 5){
        printf("Opcao invalida, ");
        printf("Escolha sua opcao: ");
        scanf("%d", &escolha);
    }
    if(escolha == 1){
        corpersonagem();
    }
    if(escolha == 2){
        corbordas();
    }
    if(escolha == 3){
        cortiros();
    }
    if(escolha == 4){
        configpontos = 1;
        gamemenu();
    }
    if(escolha == 5){
        jogodificuldade();
    }
}

/*tela de menu do jogo*/
void gamemenu(){
    system(CLEAR);
    int escolha;
    printf("1 - Jogar\n");
    printf("2 - Configuracoes\n");
    printf("3 - Ranking\n");
    printf("4 - Instrucoes\n");
    printf("5 - Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);

    while(escolha != 1 && escolha != 2 && escolha != 3 && escolha != 4 && escolha != 5){
        printf("Opcao invalida, escolha novamente\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
    }

    /*comecar jogo*/
    if(escolha == 1){
        jogo = 1;
    }
    /*implementar dps*/
    else if(escolha == 2){
        configuracoes();
    }
    /*implementar dps*/
    else if(escolha == 3){
        gamemenu();
    }
    else if(escolha == 4){
        instrucoes();
    }
    else if(escolha == 5){
        sair = escolha;
        system("exit");
    }
}

/*tela de boas vindas ao jogo*/
void welcome(){
    int i,j;
    char river_raid[LINHAS][COLUNAS] = {
        {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
        {'*','.','.','.','_','_','_','_','_','_','_','.','.','_','_','_','.','.','_','_','_','.','.','.','.','.','.','_','_','_','.','_','_','_','_','_','_','_','.','.','.','_','_','_','_','_','_','_','_','.','.','.','.','.','.','.','.','.','.','_','_','_','_','_','_','_','_','.','.','_','_','_','_','_','_','_','_','.','.','_','_','_','.','.','_','_','_','_','_','_','_','_','.','.','.','.','.','.','*'},
        {'*','.','|','\\','.','.','.','_','_','.','.','\\','|','\\','.','.','\\','|','\\','.','.','\\','.','.','.','.','/','.','.','/','|','\\','.','.','_','_','_','.','\\','.','|','\\','.','.','.','_','_','.','.','\\','.','.','.','.','.','.','.','.','|','\\','.','.','.','_','_','.','.','\\','|','\\','.','.','.','_','_','.','.','\\','|','\\','.','.','\\','|','\\','.','.','.','_','_','_','.','\\','.','.','.','.','.','*'},
        {'*','.','\\','.','\\','.','.','\\','|','\\','.','.','\\','.','\\','.','.','\\','.','\\','.','.','\\','.','.','/','.','.','/','.','|','.','\\','.','.','.','_','_','/','|','\\','.','\\','.','.','\\','|','\\','.','.','\\','.','.','.','.','.','.','.','\\','.','\\','.','.','\\','|','\\','.','.','\\','.','\\','.','.','\\','|','\\','.','.','\\','.','\\','.','.','\\','.','\\','.','.','\\','_','|','\\','.','\\','.','.','.','.','*'},
        {'*','.','.','\\','.','\\','.','.','.','_','.','.','_','\\','.','\\','.','.','\\','.','\\','.','.','\\','/','.','.','/','.','/','.','\\','.','\\','.','.','\\','_','|','/','_','\\','.','\\','.','.','.','_','.','.','_','\\','.','.','.','.','.','.','.','\\','.','\\','.','.','.','_','.','.','_','\\','.','\\','.','.','.','_','_','.','.','\\','.','\\','.','.','\\','.','\\','.','.','\\','.','\\','\\','.','\\','.','.','.','*'},
        {'*','.','.','.','\\','.','\\','.','.','\\','\\','.','.','\\','\\','.','\\','.','.','\\','.','\\','.','.','.','.','/','.','/','.','.','.','\\','.','\\','.','.','\\','_','|','\\','.','\\','.','\\','.','.','\\','\\','.','.','\\','|','.','.','.','.','.','.','.','\\','.','\\','.','.','\\','\\','.','.','\\','\\','.','\\','.','.','\\','.','\\','.','.','\\','.','\\','.','.','\\','.','\\','.','.','\\','_','\\','\\','.','\\','.','.','*'},
        {'*','.','.','.','.','\\','.','\\','_','_','\\','\\','.','_','\\','\\','.','\\','_','_','\\','.','\\','_','_','/','.','/','.','.','.','.','.','\\','.','\\','_','_','_','_','_','_','_','\\','.','\\','_','_','\\','\\','.','_','\\','.','.','.','.','.','.','.','.','\\','.','\\','_','_','\\','\\','.','_','\\','\\','.','\\','_','_','\\','.','\\','_','_','\\','.','\\','_','_','\\','.','\\','_','_','_','_','_','_','_','\\','.','*'},
        {'*','.','.','.','.','.','\\','|','_','_','|','\\','|','_','_','|','\\','|','_','_','|','\\','|','_','_','|','/','.','.','.','.','.','.','.','\\','|','_','_','_','_','_','_','_','|','\\','|','_','_','|','\\','|','_','_','|','.','.','.','.','.','.','.','.','\\','|','_','_','|','\\','|','_','_','|','\\','|','_','_','|','\\','|','_','_','|','\\','|','_','_','|','\\','|','_','_','_','_','_','_','_','|','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
    };

    for(i=0;i<LINHAS;i++){
        for(j=0;j<COLUNAS;j++){
            if(river_raid[i][j] == '*'){
                printf(ANSI_COLOR_WHITE ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, river_raid[i][j]);
            }
            else if(river_raid[i][j] == '.'){
                printf(ANSI_COLOR_BLACK ANSI_COLOR_BK_BLACK "%c" ANSI_COLOR_RESET, river_raid[i][j]);
            }
            else if(river_raid[i][j] == '_' || river_raid[i][j] == '|' || river_raid[i][j] == '\\' || river_raid[i][j] == '/'){
                printf(ANSI_COLOR_WHITE ANSI_COLOR_BK_BLACK "%c" ANSI_COLOR_RESET, river_raid[i][j]);
            }
        }
        /*atrasar a atualizacao da tela para parecer antigo */
        /* usleep(100000); */
        printf("\n");
    }
    getchar();
}

/*printar combustivel e pontos*/
void combustivel_pontos(int *printcombustivel, int *pontos){
    /*encerra jogo se o combustivel acabar*/
    int x,y,i,j;
    if (*printcombustivel <= 0){
        jogo = 0;
    }
    
    else if (*printcombustivel > 0){
        printf(ANSI_COLOR_RED "Combustivel = %d" ANSI_COLOR_RESET, *printcombustivel);
        printf(ANSI_COLOR_GREEN "    Pontos = %d\n" ANSI_COLOR_RESET, *pontos);/*printa combustivel*/
        *printcombustivel = *printcombustivel - 1;
        if(configpontos == 1){
            *pontos = *pontos + 1;
        }
    }   
}

/*mover tiro*/
void movertiro(char map[LINHAS][COLUNAS], int *printcombustivel, int *pontos){
    int x,y,i,j;
    for(i=0;i<LINHAS;i++){
        for(j=COLUNAS;j>=0;j--){
            if(map[i][j] == '>'){
                x = j;
                y = i;

                if(x == 134){
                    map[y][x] = '.';
                }
                if(x >= COLUNAS || x <= 0 ){
                    map[y][x] = '.';
                }
                if(map[y][x+1] == '.'){
                    map[y][x] = '.';
                    map[y][x+1] = '>';
                }
                if(map[y][x+1] == 'F'){
                    map[y][x] = '.';
                    map[y][x+1] = '.';
                }
                if(map[y][x+1] == 'X'){
                    *pontos = *pontos + 50; /* adiciona 50 pontos ao destruir 'X' */
                    map[y][x] = '.';
                    map[y][x+1] = '.';
                }

            }        
        }
    }
}

/*mover F*/
void moverfuel(char map[LINHAS][COLUNAS], int *printcombustivel){
    int i, j=134,random, randomspawn;
    int x,y;

    random = rand() % 8 + 1;
    randomspawn = rand()%100 + 1;

    if(dificuldade == 1){
        if(map[random][134] == '.' && randomspawn >= 70 && randomspawn < 100){
            map[random][j] = 'F'; 
        }
    }
    if(dificuldade == 2){
        if(map[random][134] == '.' && randomspawn >= 60 && randomspawn < 100){
            map[random][j] = 'F'; 
        }
    }
    if(dificuldade == 3){
        if(map[random][134] == '.' && randomspawn >= 50 && randomspawn < 100){
            map[random][j] = 'F'; 
        }
    }

    
    for(i=0;i<LINHAS;i++){
        for(j=0;j<COLUNAS;j++){
            if(map[i][j] == 'F'){
                x = j;
                y = i;

                if(map[y][x-1] == '.'){
                    map[y][x] = '.';
                    map[y][x-1] = 'F';
                }
                if(map[y][x-1] == '>'){
                    map[y][x] = '.';
                    map[y][x-1] = '.';
                }
                /*pegar combustivel*/
                if(map[y][x-1] == 'C'){
                    map[y][x] = '.';
                    map[y][x-1] = 'C';
                    *printcombustivel = *printcombustivel + 40;
                }               
                if(x < 0 || x > COLUNAS){
                   map[y][x-1] = map[y][x];
                } 
            }
        }
        if(map[i][0] == 'F'){
            map[i][0] = '.';
        }
    } 
}

/*mover X*/
void moverinimigo(char map[LINHAS][COLUNAS]){
    int i, j=134,random, randomspawn;
    int x,y;

    random = rand() % 8 + 1;
    randomspawn = rand()%100 + 1;
    if(dificuldade == 1){
        if(map[random][134] == '.' && randomspawn >= 70 && randomspawn < 100){
            map[random][j] = 'X'; 
        }
    }
    if(dificuldade == 2){
        if(map[random][134] == '.' && randomspawn >= 50 && randomspawn < 100){
            map[random][j] = 'X'; 
        }
    }
    if(dificuldade == 3){
        if(map[random][134] == '.' && randomspawn >= 30 && randomspawn < 100){
            map[random][j] = 'X'; 
        }
    }
    for(i=0;i<LINHAS;i++){
        for(j=0;j<COLUNAS;j++){
            if(map[i][j] == 'X'){
                x = j;
                y = i;

                if(map[y][x-1] == '.'){
                    map[y][x] = '.';
                    map[y][x-1] = 'X';
                }
                if(map[y][x-1] == '>'){
                    map[y][x] = '.';
                    map[y][x-1] = '.';
                }
               /*fazer game over*/
               if(map[y][x-1] == 'C'){
                    map[y][x] = '.';
                    map[y][x-1] = 'X';
                    jogo = 0;
                }
            }
        }
        if(map[i][0] == 'X'){
            map[i][0] = '.';
        }
    } 
}

/*mover C*/
void moverpersonagem(char map[LINHAS][COLUNAS], int *printcombustivel, int *pontos){
    char move;
    int i, j;
    int x, y;
    if(kbhit() == 1){
        move = getch();

        /*mover para cima*/
        if (move == 'w'){
            *printcombustivel = *printcombustivel - 2; /*combustivel perdido ao mover*/
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
            else if(map[y][x] == 'C'){
                map[y][x] = '.';
                map[y-1][x] = 'C';
            }
        }   
        /*mover para baixo*/
        if (move == 's'){
            *printcombustivel = *printcombustivel - 2; /*combustivel perdido ao mover*/
            for(i=0;i<LINHAS;i++){
                for(j=0;j<COLUNAS;j++){
                    if(map[i][j] == 'C'){
                        x = j;
                        y = i;
                    }
                }
            }
            /*delimitar tamanho de novo dps*/
            if((y+1)>8){
                map[y][x] = 'C';
            }
            else if(map[y][x] == 'C'){
                map[y][x] = '.';
                map[y+1][x] = 'C';
            }
        }
        /*mover para direita*/
        if (move == 'd'){
            *printcombustivel = *printcombustivel - 2; /*combustivel perdido ao mover*/
            for(i=0;i<LINHAS;i++){
                for(j=0;j<COLUNAS;j++){
                    if(map[i][j] == 'C'){
                        x = j;
                        y = i;
                    }
                }
            }
            
            if((x+1)>134){
                map[y][x] = 'C';
            }
            else if(map[y][x] == 'C'){
                map[y][x] = '.';
                map[y][x+1] = 'C';
            }
        }
        /*mover para esquerda*/
        if (move == 'a'){
            *printcombustivel = *printcombustivel - 2; /*combustivel perdido ao mover*/
            for(i=0;i<LINHAS;i++){
                for(j=0;j<COLUNAS;j++){
                    if(map[i][j] == 'C'){
                        x = j;
                        y = i;
                    }
                }
            }
        
            if((x-1)>134){
                map[y][x] = 'C';
            }
            else if(map[y][x] == 'C'){
                map[y][x] = '.';
                map[y][x-1] = 'C';
            }
        }
        /*criar tiro*/
        if (move == ' '){
            *printcombustivel = *printcombustivel - 3; /*combustivel perdido ao atirar*/
            for(i=0;i<LINHAS;i++){
                for(j=0;j<COLUNAS;j++){
                    if(map[i][j] == 'C'){
                        x = j;
                        y = i;
                        map[y][x+1] = '>';
                    }
                }
            }
            if((x+1)> 134){
                map[y][x] = '.';
            }
        }
    }
}

/*printar matriz*/
void printarmatriz(char map[LINHAS][COLUNAS]){
    int i,j;
    int x,y;
    
    for(i=0;i<LINHAS;i++){
        for(j=0;j<COLUNAS;j++){
            if(map[i][j] == 'C'){
                /*alterar cor para vermelho*/
                if(personagemcor == 1){
                    printf(ANSI_COLOR_RED ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para verde*/
                if(personagemcor == 2){
                    printf(ANSI_COLOR_GREEN ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para amarelo*/
                if(personagemcor == 3){
                    printf(ANSI_COLOR_YELLOW ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para azul*/
                if(personagemcor == 4){
                    printf(ANSI_COLOR_BLUE ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para magenta*/
                if(personagemcor == 5){
                    printf(ANSI_COLOR_MAGENTA ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para ciano*/
                if(personagemcor == 6){
                    printf(ANSI_COLOR_CYAN ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para preto*/
                if(personagemcor == 7){
                    printf(ANSI_COLOR_BLACK ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
                }
            }
            if(map[i][j] == '='){
                /*alterar cor para vermelho*/
                if(bordascor == 1){
                    printf(ANSI_COLOR_RED ANSI_COLOR_BK_RED "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para verde*/
                if(bordascor == 2){
                    printf(ANSI_COLOR_GREEN ANSI_COLOR_BK_GREEN "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para amarelo*/
                if(bordascor == 3){
                    printf(ANSI_COLOR_YELLOW ANSI_COLOR_BK_YELLOW "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para azul*/
                if(bordascor == 4){
                    printf(ANSI_COLOR_BLUE ANSI_COLOR_BK_BLUE "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para magenta*/
                if(bordascor == 5){
                    printf(ANSI_COLOR_MAGENTA ANSI_COLOR_BK_MAGENTA "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para ciano*/
                if(bordascor == 6){
                    printf(ANSI_COLOR_CYAN ANSI_COLOR_BK_CYAN "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para preto*/
                if(bordascor == 7){
                    printf(ANSI_COLOR_BLACK ANSI_COLOR_BK_BLACK "%c" ANSI_COLOR_RESET, map[i][j]);
                }
            }
            if(map[i][j] == '.'){
                printf(ANSI_COLOR_WHITE ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
            }
            if(map[i][j] == 'X' && j != 0){
                printf(ANSI_COLOR_RED ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
            }
            if(map[i][j] == 'F' && j != 0){
                printf(ANSI_COLOR_GREEN ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
            }
            if(map[i][j] == '>'){
                /*alterar cor para vermelho*/
                if(tirocor == 1){
                    printf(ANSI_COLOR_RED ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para verde*/
                if(tirocor == 2){
                    printf(ANSI_COLOR_GREEN ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para amarelo*/
                if(tirocor == 3){
                    printf(ANSI_COLOR_YELLOW ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para azul*/
                if(tirocor == 4){
                    printf(ANSI_COLOR_BLUE ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para magenta*/
                if(tirocor == 5){
                    printf(ANSI_COLOR_MAGENTA ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para ciano*/
                if(tirocor == 6){
                    printf(ANSI_COLOR_CYAN ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /*alterar cor para preto*/
                if(tirocor == 7){
                    printf(ANSI_COLOR_BLACK ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
                }
                /* printf(ANSI_COLOR_BLUE ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]); */
            }
            if(j==134){
            }
        }
        printf("\n");
    }
}


int main(){
    int i=0, j=0;
    int cont = 0;
    int printcombustivel = 400;
    int pontos = 0;

    srand(time(NULL));

    char map[LINHAS][COLUNAS] = {
       
        {'=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '='},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'C', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '='},
        
    };

    system(CLEAR);
    welcome();
    system(CLEAR);
    gamemenu();
    while(jogo == 1){
        system(CLEAR);
        combustivel_pontos(&printcombustivel, &pontos);
        moverinimigo(map);
        moverfuel(map, &printcombustivel);
        movertiro(map, &printcombustivel, &pontos);
        printarmatriz(map);
        moverpersonagem(map, &printcombustivel, &pontos);
        
        if(dificuldade == 1){
            usleep(50000);
        }
        if(dificuldade == 2 || dificuldade == 3){
            usleep(45000);
        }        
    }
    if(jogo == 0 && sair != 5){
        gameover(&pontos, &printcombustivel);
    }
    return 0;
}
