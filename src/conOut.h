#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37


void gotoxy(unsigned int x, unsigned int y){
  printf("\033[%d;%df", y, x);
}

void clrscr() {
  printf("\033[2J");
  gotoxy(1, 1);
}

void setC(int c) {
  printf("\033[0;%dm", c);
}

void setCB(int c, int b) {
  printf("\033[0;%dm\033[0;m", c, b + 10);
}

void clrscrc(int c, int b) {  
  setCB(c, b);
  clrscr();
}

/*void cursor() {
  std::cout << "\033[?25l";
  // \033?25h 
}*/

