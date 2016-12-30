#include "droidHearts.h"
//#include "test.h"

int main() {
  int read;

  Table *table = (Table*)malloc(sizeof(Table));
  table->initialize(NEWGAME);
  
  //table->redraw();
  //gotoxy(1, 60);
  //return 0;

  read = -1;
  while (read != 0) {
    clrscr();
    printf("1: New game\n2: Load game (WIP)\n3: Options\n0: Quit\n\n> ");
    read = getch() - '0';
    switch (read) {
      case 0:
        clrscr();
        printf("Thanks for playing!\n");
        return 0;
        break;
      case 1:
        clrscr();
        game(table, NEWGAME);
        break;
      case 2:
        break;  // TODO save/load
        if (loadgame(table)) {
          clrscr();
          printplayers(table);
          game(table, LOAD);
        }
        break;
      case 3:
        debuggingoptions();
        break;
      default:
        break;
    }
  }
  return 0;
}


