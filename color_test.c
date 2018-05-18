#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

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

#define ANSI_COLOR_RESET   "\x1b[0m"

int colors (int argc, char const *argv[]) {

  printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_GREEN   "This text is GREEN!"   ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_YELLOW  "This text is YELLOW!"  ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_BLUE    "This text is BLUE!"    ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_MAGENTA "This text is MAGENTA!" ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_CYAN    "This text is CYAN!"    ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_WHITE    "This text is WHITE!"  ANSI_COLOR_RESET "\n");

  printf(ANSI_COLOR_BK_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_BK_GREEN   "This text is GREEN!"   ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_BK_YELLOW  "This text is YELLOW!"  ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_BK_BLUE    "This text is BLUE!"    ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_BK_MAGENTA "This text is MAGENTA!" ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_BK_CYAN    "This text is CYAN!"    ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_BK_WHITE    "This text is WHITE!"  ANSI_COLOR_RESET "\n");

  return 0;
}