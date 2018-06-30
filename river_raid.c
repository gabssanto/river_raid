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

int LINHAS; // = 10;
int COLUNAS; // = 135;
int probX; //70
int probF; //70
int probO; //99
int probT; //97
int velocidade; //50000

int nlinhas, ncolunas;

FILE *gridzise;
FILE *probabilidade;
FILE *game;

int jogo = 0; /*inicializar o jogo*/
int personagemcor = 1; /*cor personagem padrao*/
int bordascor = 4; /*cor das bordas padrao*/
int tirocor = 4; /*cor do tiro padrao*/
int configpontos = 0; /*ativa ou desativa ganhar pontos por segundo nas configuracoes*/
int sair; /*definir saida do jogo*/
int plays = 0;

int ranked_mode = 0;//setar 0 dps

typedef struct{
    char nome[11];
    int score;
}Player;
Player jogador;

void gameranking(){
    int i, escolha;
    int size = 0;
    system(CLEAR);

    game = fopen("ranking.bin","rb");
    if (game == NULL){
        printf("Error! opening file");
    }
    while(!feof(game)){
        fread(&jogador, sizeof(Player), 1, game); 
        size++;  
    }

    fclose(game); 

    game = fopen("ranking.bin","rb");
    if (game == NULL){
        printf("Error! opening file");
    }
    printf("Ranking do jogo\n");
    
    i=0;
    
    while(i=0;i<size-1;i++){
        fread(&jogador, sizeof(Player), 1, game); 
        printf("%s score : %d\n",jogador.nome, jogador.score);   
    }
    fclose(game); 
    printf("Aperte 1 para voltar ao menu");
    scanf("%d", &escolha);
    if(escolha == 1){
        gamemenu();
    }
    
    getchar();
    
}

void probs(){
    system(CLEAR);

    probabilidade = fopen("probabilidade.txt", "w");

	if(probabilidade == NULL){
		printf("erro inesperado, nao existe arquivo o probabilidade.txt\n");
	}
	printf("Escolha a probabilidade de surgimento do X\n");
    scanf("%d", &probX);
	fprintf(probabilidade,"%d\n", probX);
	
    printf("Escolha a probabilidade de surgimento do F\n");
    scanf("%d", &probF);
	fprintf(probabilidade,"%d\n", probF);

    printf("Escolha a probabilidade de surgimento do O\n");
    scanf("%d", &probO);
	fprintf(probabilidade,"%d\n", probO);

    printf("Escolha a probabilidade de surgimento do T\n");
    scanf("%d", &probT);
	fprintf(probabilidade,"%d\n", probT);

    printf("Escolha a velocidade do jogo em microssegundos\n");
    scanf("%d", &velocidade);
	fprintf(probabilidade,"%d\n", velocidade);

	fclose(probabilidade);

    probabilidade = fopen("probabilidade.txt", "r");

	if(probabilidade == NULL){
		printf("erro inesperado, nao existe arquivo o probabilidade.txt\n");
	}
	fscanf(probabilidade,"%d\n", &probX);
	fscanf(probabilidade,"%d\n", &probF);
    fscanf(probabilidade,"%d\n", &probO);
    fscanf(probabilidade,"%d\n", &probT);
    fscanf(probabilidade,"%d\n", &velocidade);

	fclose(probabilidade);
    gamemenu();
}

void changegridzise(){
    system(CLEAR);
    
    int nLINHAS, nCOLUNAS;
    int linha, coluna;

	gridzise = fopen("gridsize.txt", "w");

	if(gridzise == NULL){
		printf("erro inesperado, nao existe arquivo o gridzise.txt\n");
	}
	printf("Escolha o numero de linhas e colunas, nessa ordem ");
    scanf("%d", &nLINHAS);
    scanf("%d", &nCOLUNAS);

	fprintf(gridzise,"%d\n", nLINHAS);
	fprintf(gridzise,"%d\n", nCOLUNAS);

	fclose(gridzise);

    gridzise = fopen("gridsize.txt", "r");

	if(gridzise == NULL){
		printf("erro inesperado, nao existe arquivo o gridzise.txt\n");
	}
	fscanf(gridzise,"%d\n", &nlinhas);
	fscanf(gridzise,"%d\n", &ncolunas);
	fclose(gridzise);

    LINHAS = nlinhas;
    COLUNAS = ncolunas;


    gamemenu();
}

/*tela de game over*/
void gameover(int *pontos, int *printcombustivel){
    system(CLEAR);
    int i,j;
    printf("Game over\n");

    if(ranked_mode == 1){
        int i,size=0;
        
        game = fopen("ranking.bin","ab");
    
        if (game == NULL){
        printf("Error! opening file");
        }
        printf("Digite seu nome: ");
        scanf("%s", jogador.nome);

        for(i=0;jogador.nome[i]!='\0';i++){
            size++;
        }
        if(size < 1 || size > 10){
            printf("Por favor, digite entre 1 e 10 caracteres: ");
            scanf("%s", jogador.nome);
        }
        //scanf("%d", &jogador.score);
        jogador.score = *pontos;
        plays++;
        fwrite(&jogador, sizeof(Player), 1, game); 
        fclose(game); 

            if(*printcombustivel <= 0){
                printf("Seu combustivel acabou\n");
            }
            else{
                printf("%s foi atingido pelo inimigo\n", jogador.nome);
            }
            printf("%s obteu %d pontos nessa partida\n", jogador.nome,jogador.score);
        getch();

    }
    if(ranked_mode == 0){
        if(*printcombustivel <= 0){
            printf("Seu combustivel acabou\n");
        }
        else{
            printf("Você foi atingido pelo inimigo\n");
        }
        printf("Você obteu %d pontos nessa partida\n", *pontos);
        getch();
    }
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
    if(ranked_mode == 1){
        printf("#Modo Ranqueado ativo\n");
    }
    printf("1 - Tamanho do jogo\n");
    printf("2 - NPC's\n");
    printf("3 - Modo ranqueado\n");
    printf("4 - Selecione para alterar a cor da nave\n");
    printf("5 - Selecione para alterar a cor da borda do mapa\n");
    printf("6 - Selecione para alterar a cor do tiro\n");
    printf("7 - Selecione para ativar a pontuacao por segundo\n");
    printf("8 - Voltar\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);
    while(escolha != 1 && escolha != 2 && escolha != 3 && escolha != 4 && escolha != 5 &&
          escolha != 6 && escolha != 7 && escolha != 8){
        printf("Opcao invalida, ");
        printf("Escolha sua opcao: ");
        scanf("%d", &escolha);
    }
    if(escolha == 1){
        changegridzise();
    }
    if(escolha == 2){
        probs();
    }
    if(escolha == 3){
        if(ranked_mode == 0){
            ranked_mode = 1;
        }
        
       else if(ranked_mode == 1){
            ranked_mode = 0;
        }       
        configuracoes();
    }
    if(escolha == 4){
        corpersonagem();
    }
    if(escolha == 5){
        corbordas();
    }
    if(escolha == 6){
        cortiros();
    }
    if(escolha == 7){
        configpontos = 1;
        gamemenu();
    }
    if(escolha == 8){
        gamemenu();
    }
}

/*tela de menu do jogo*/
void gamemenu(){
    system(CLEAR);
    int escolha;
    if(ranked_mode == 1){
        printf("#Modo Ranqueado ativo\n");
    }
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
        gameranking();
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
    char river_raid[10][135] = {
        {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
        {'*','#','#','#','_','_','_','_','_','_','_','#','#','_','_','_','#','#','_','_','_','#','#','#','#','#','#','_','_','_','#','_','_','_','_','_','_','_','#','#','#','_','_','_','_','_','_','_','_','#','#','#','#','#','#','#','#','#','#','_','_','_','_','_','_','_','_','#','#','_','_','_','_','_','_','_','_','#','#','_','_','_','#','#','_','_','_','_','_','_','_','_','#','#','#','#','#','#','*'},
        {'*','#','|','\\','#','#','#','_','_','#','#','\\','|','\\','#','#','\\','|','\\','#','#','\\','#','#','#','#','/','#','#','/','|','\\','#','#','_','_','_','#','\\','#','|','\\','#','#','#','_','_','#','#','\\','#','#','#','#','#','#','#','#','|','\\','#','#','#','_','_','#','#','\\','|','\\','#','#','#','_','_','#','#','\\','|','\\','#','#','\\','|','\\','#','#','#','_','_','_','#','\\','#','#','#','#','#','*'},
        {'*','#','\\','#','\\','#','#','\\','|','\\','#','#','\\','#','\\','#','#','\\','#','\\','#','#','\\','#','#','/','#','#','/','#','|','#','\\','#','#','#','_','_','/','|','\\','#','\\','#','#','\\','|','\\','#','#','\\','#','#','#','#','#','#','#','\\','#','\\','#','#','\\','|','\\','#','#','\\','#','\\','#','#','\\','|','\\','#','#','\\','#','\\','#','#','\\','#','\\','#','#','\\','_','|','\\','#','\\','#','#','#','#','*'},
        {'*','#','#','\\','#','\\','#','#','#','_','#','#','_','\\','#','\\','#','#','\\','#','\\','#','#','\\','/','#','#','/','#','/','#','\\','#','\\','#','#','\\','_','|','/','_','\\','#','\\','#','#','#','_','#','#','_','\\','#','#','#','#','#','#','#','\\','#','\\','#','#','#','_','#','#','_','\\','#','\\','#','#','#','_','_','#','#','\\','#','\\','#','#','\\','#','\\','#','#','\\','#','\\','\\','#','\\','#','#','#','*'},
        {'*','#','#','#','\\','#','\\','#','#','\\','\\','#','#','\\','\\','#','\\','#','#','\\','#','\\','#','#','#','#','/','#','/','#','#','#','\\','#','\\','#','#','\\','_','|','\\','#','\\','#','\\','#','#','\\','\\','#','#','\\','|','#','#','#','#','#','#','#','\\','#','\\','#','#','\\','\\','#','#','\\','\\','#','\\','#','#','\\','#','\\','#','#','\\','#','\\','#','#','\\','#','\\','#','#','\\','_','\\','\\','#','\\','#','#','*'},
        {'*','#','#','#','#','\\','#','\\','_','_','\\','\\','#','_','\\','\\','#','\\','_','_','\\','#','\\','_','_','/','#','/','#','#','#','#','#','\\','#','\\','_','_','_','_','_','_','_','\\','#','\\','_','_','\\','\\','#','_','\\','#','#','#','#','#','#','#','#','\\','#','\\','_','_','\\','\\','#','_','\\','\\','#','\\','_','_','\\','#','\\','_','_','\\','#','\\','_','_','\\','#','\\','_','_','_','_','_','_','_','\\','#','*'},
        {'*','#','#','#','#','#','\\','|','_','_','|','\\','|','_','_','|','\\','|','_','_','|','\\','|','_','_','|','/','#','#','#','#','#','#','#','\\','|','_','_','_','_','_','_','_','|','\\','|','_','_','|','\\','|','_','_','|','#','#','#','#','#','#','#','#','\\','|','_','_','|','\\','|','_','_','|','\\','|','_','_','|','\\','|','_','_','|','\\','|','_','_','|','\\','|','_','_','_','_','_','_','_','|','#','*'},
        {'*','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','*'},
        {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
    };

    for(i=0;i<10;i++){
        for(j=0;j<135;j++){
            if(river_raid[i][j] == '*'){
                printf(ANSI_COLOR_WHITE ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, river_raid[i][j]);
            }
            else if(river_raid[i][j] == '#'){
                printf(ANSI_COLOR_RED ANSI_COLOR_BK_RED "%c" ANSI_COLOR_RESET, river_raid[i][j]);
            }
            else if(river_raid[i][j] == '_' || river_raid[i][j] == '|' || river_raid[i][j] == '\\' || river_raid[i][j] == '/'){
                printf(ANSI_COLOR_WHITE ANSI_COLOR_BK_RED "%c" ANSI_COLOR_RESET, river_raid[i][j]);
            }
        }
       
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

                if(x == COLUNAS-1){
                    map[y][x] = ' ';
                }
                if(x >= COLUNAS || x <= 0 ){
                    map[y][x] = ' ';
                }
                if(map[y][x+1] == ' '){
                    map[y][x] = ' ';
                    map[y][x+1] = '>';
                }
                if(map[y][x+1] == 'F'){
                    map[y][x] = ' ';
                    map[y][x+1] = ' ';
                }
                if(map[y][x+1] == 'X'){
                    *pontos = *pontos + 50; /* adiciona 50 pontos ao destruir 'X' */
                    map[y][x] = ' ';
                    map[y][x+1] = ' ';
                }

            }        
        }
    }
}

/*mover tiro do T*/
void movertiroT(char map[LINHAS][COLUNAS]){
    int x,y,i,j;
    for(i=0;i<LINHAS;i++){
        for(j=0;j<COLUNAS;j++){
            if(map[i][j] == '<'){
                x = j;
                y = i;
                if(map[y][x-2] == 'F'){
                    map[y][x] = ' ';
                    map[y][x-3] = '<';
                }
                if(map[y][x-2] == 'X'){
                    map[y][x] = ' ';
                    map[y][x-3] = '<';
                }
                if(x == COLUNAS-1){
                    map[y][x] = ' ';
                }
                if(x >= COLUNAS || x <= 0 ){
                    map[y][x] = ' ';
                }
                if(map[y][x-2] == ' '){
                    map[y][x] = ' ';
                    map[y][x-2] = '<';
                }
                if(map[y][x-2] == 'C'){
                    
                }
            }        
        }
    }
}

/*mover T*/
void moverinimigoT(char map[LINHAS][COLUNAS]){
    int i, j=COLUNAS-1,random, randomspawn;
    int tirosT;
    int x,y;

    random = rand() % (LINHAS-2) + 1;
    randomspawn = rand()%100 + 1;
    if(map[random][COLUNAS-1] == ' ' && randomspawn >= (100-probT)/*97*/ && randomspawn < 100){
        map[random][j] = 'T'; 
    }
    
    for(i=0;i<LINHAS;i++){
        for(j=0;j<COLUNAS;j++){
            if(map[i][j] == 'T'){
                x = j;
                y = i;
                
                /* if(map[y][x-1] == ' ' && tirosT > 0){
                    tirosT = 3;
                    map[y][x] = ' ';
                    map[y][x-2] = '<';
                    tirosT--;
                    
                } */

                if(map[y][x-1] == ' '){
                    map[y][x] = ' ';
                    map[y][x-1] = 'T';
                }
                if(map[y][x-1] == '>'){
                    map[y][x] = ' ';
                    map[y][x-1] = ' ';
                }
               /*fazer game over*/
               if(map[y][x-1] == 'C'){
                    map[y][x] = ' ';
                    map[y][x-1] = 'T';
                    jogo = 0;
                }
            }
        }
        if(map[i][0] == 'T'){
            map[i][0] = ' ';
        }
    } 
}

/*mover O*/
void moverinimigoO(char map[LINHAS][COLUNAS]){
    int i, j=COLUNAS-1,random, randomspawn;
    int x,y;

    random = rand() % (LINHAS-2) + 1;
    randomspawn = rand()%100 + 1;

    if(map[random][COLUNAS-1] == ' ' && randomspawn >= (100-probO)/*99*/ && randomspawn < 100){
        map[random][j] = 'O'; 
    }

    for(i=0;i<LINHAS;i++){
        for(j=0;j<COLUNAS;j++){
            if(map[i][j] == 'O'){
                x = j;
                y = i;

                if(map[y][x-1] == ' '){
                    map[y][x] = ' ';
                    map[y][x-1] = 'O';
                }
                if(map[y][x-1] == '>'){
                    map[y][x] = ' ';
                    map[y][x-1] = ' ';
                }
               /*fazer game over*/
               if(map[y][x-1] == 'C'){
                    map[y][x] = ' ';
                    map[y][x-1] = 'O';
                    jogo = 0;
                }
            }
        }
        if(map[i][0] == 'O'){
            map[i][0] = ' ';
        }
    } 
}

/*mover F*/
void moverfuel(char map[LINHAS][COLUNAS], int *printcombustivel){
    int i, j=COLUNAS-1,random, randomspawn;
    int x,y;

    random = rand() % (LINHAS-2) + 1;
    randomspawn = rand()%100 + 1;

    if(map[random][COLUNAS-1] == ' ' && randomspawn >= (100-probF)/*70*/ && randomspawn < 100){
        map[random][j] = 'F'; 
    }
    
    for(i=0;i<LINHAS;i++){
        for(j=0;j<COLUNAS;j++){
            if(map[i][j] == 'F'){
                x = j;
                y = i;

                if(map[y][x-1] == ' '){
                    map[y][x] = ' ';
                    map[y][x-1] = 'F';
                }
                if(map[y][x-1] == '>'){
                    map[y][x] = ' ';
                    map[y][x-1] = ' ';
                }
                /*pegar combustivel*/
                if(map[y][x-1] == 'C'){
                    map[y][x] = ' ';
                    map[y][x-1] = 'C';
                    *printcombustivel = *printcombustivel + 40;
                }               
                if(x < 0 || x > COLUNAS){
                   map[y][x-1] = map[y][x];
                } 
            }
        }
        if(map[i][0] == 'F'){
            map[i][0] = ' ';
        }
    } 
}

/*mover X*/
void moverinimigoX(char map[LINHAS][COLUNAS], int *pontos){
    int i, j=COLUNAS-1,random, randomspawn;
    int x,y;

    random = rand() % (LINHAS-2) + 1;
    randomspawn = rand()%100 + 1;
    
    if(map[random][COLUNAS-1] == ' ' && randomspawn >= (100-probX)/*70*/ && randomspawn < 100){
        map[random][j] = 'X'; 
    }
    
    for(i=0;i<LINHAS;i++){
        for(j=0;j<COLUNAS;j++){
            if(map[i][j] == 'X'){
                x = j;
                y = i;

                if(map[y][x-1] == ' '){
                    map[y][x] = ' ';
                    map[y][x-1] = 'X';
                }
                if(map[y][x-1] == '>'){
                    map[y][x] = ' ';
                    map[y][x-1] = ' ';
                    *pontos = *pontos + 50; /* adiciona 50 pontos ao destruir 'X' */
                }
               /*fazer game over*/
               if(map[y][x-1] == 'C'){
                    map[y][x] = ' ';
                    map[y][x-1] = 'X';
                    jogo = 0;
                }
            }
        }
        if(map[i][0] == 'X'){
            map[i][0] = ' ';
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
                map[y][x] = ' ';
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
            if((y+1)>LINHAS-2){
                map[y][x] = 'C';
            }
            else if(map[y][x] == 'C'){
                map[y][x] = ' ';
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
            
            if((x+1)>COLUNAS-1){
                map[y][x] = 'C';
            }
            else if(map[y][x] == 'C'){
                map[y][x] = ' ';
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
        
            if((x-1)<0){
                map[y][x] = 'C';
            }
            else if(map[y][x] == 'C'){
                map[y][x] = ' ';
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
            if((x+1)> COLUNAS-1){
                map[y][x] = ' ';
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
            if(map[i][j] == ' '){
                printf(ANSI_COLOR_WHITE ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
            }
            if(map[i][j] == 'X' && j != 0){
                printf(ANSI_COLOR_RED ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
            }
            if(map[i][j] == 'F' && j != 0){
                printf(ANSI_COLOR_GREEN ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
            }
            if(map[i][j] == 'O' && j != 0){
                printf(ANSI_COLOR_YELLOW ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
            }
            if(map[i][j] == 'T' && j != 0){
                printf(ANSI_COLOR_BLUE ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
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
            if(map[i][j] == '<'){
                printf(ANSI_COLOR_RED ANSI_COLOR_BK_WHITE "%c" ANSI_COLOR_RESET, map[i][j]);
            }
            if(j==COLUNAS-1){
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

    system(CLEAR);
    welcome();
    system(CLEAR);
    gamemenu();
    

    gridzise = fopen("gridsize.txt", "r");

	if(gridzise == NULL){
		printf("erro inesperado, nao existe arquivo o gridzise.txt\n");
	}
	fscanf(gridzise,"%d\n", &nlinhas);
	fscanf(gridzise,"%d\n", &ncolunas);
	fclose(gridzise);

    LINHAS = nlinhas;
    COLUNAS = ncolunas;

    probabilidade = fopen("probabilidade.txt", "r");

	if(probabilidade == NULL){
		printf("erro inesperado, nao existe arquivo o probabilidade.txt\n");
	}
	fscanf(probabilidade,"%d\n", &probX);
	fscanf(probabilidade,"%d\n", &probF);
    fscanf(probabilidade,"%d\n", &probO);
    fscanf(probabilidade,"%d\n", &probT);
    fscanf(probabilidade,"%d\n", &velocidade);

	fclose(probabilidade);

    if(ranked_mode == 1){
        LINHAS = 10;
        COLUNAS = 135; 
        probX = 25;
        probF = 10;
        probO = 1;
        probT = 4;
        velocidade = 60000;
    }

    char map[LINHAS][COLUNAS];


    for(i=0;i<LINHAS;i++){
        for(j=0;j<COLUNAS;j++){
            if(i == 0 || i == LINHAS-1){
                map[i][j] = '=';
            }
            else if(i == 5 && j == 0){
                map[i][j] = 'C';
            }
            else{
                map[i][j] = ' ';
            }
        }
    }

    
    while(jogo == 1){
        system(CLEAR);
        combustivel_pontos(&printcombustivel, &pontos);
        moverinimigoX(map, &pontos);
        moverinimigoO(map);
        moverinimigoT(map);
        moverfuel(map, &printcombustivel);
        movertiro(map, &printcombustivel, &pontos);
        movertiroT(map);
        printarmatriz(map);
        moverpersonagem(map, &printcombustivel, &pontos); 
        usleep(50000);
    }
    if(jogo == 0 && sair != 5){
        gameover(&pontos, &printcombustivel);
    }
    return 0;
}
