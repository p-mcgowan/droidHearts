#include "droidHearts.h"
#include "test.h"

int main() {
  char nname[12] = "North";
  char ename[12] = "East";
  char pname[12] = "Player";
  char wname[12] = "West";
  int pass = 3, rnd = 0, read = -1;
  int trick[5] = {-1, -1, -1, -1, 0};
  int p[16], n[16], e[16], w[16], deck[52], strat[16];
  nname[11] = 5;
  ename[11] = 4;
  pname[11] = 6;
  wname[11] = 4;

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
        game(n, e, p, w, strat, trick, &rnd, nname, ename, pname, wname,
        deck, &pass, NEWGAME);
        break;
      case 2:
        if (loadgame(n, e, p, w, strat, trick, &rnd, nname, ename, pname,
        wname, deck, &pass)) {
          clrscr();
          printplayers(trick, nname, ename, pname, wname);
          game(n, e, p, w, strat, trick, &rnd, 
          nname, ename, pname, wname, deck, &pass, LOAD);
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

void sort(int *p) {
  int i, t = 0, s;
  while (t == 0) {
    t = 1;
    for (i = 0; i < 12; i++) {
      if (p[i + 1] < p[i]) {
        t = 0;
        s = p[i];
        p[i] = p[i + 1];
        p[i + 1] = s;
      }
    }
  }
}

void shuf(int *deck) {
  int i, j, k;
  for (i = 0; i < 52; i++) {
    deck[i] = i;
  }
  if ((unsigned)time(NULL) != seed) {
    srand((unsigned)time(NULL));
    seed = ((unsigned)time(NULL));
  }
  for (i = 0; i < 52; i++) {
    k = rand() % 52;
    j = deck[i];
    deck[i] = deck[k];
    deck[k] = j;
  }
}

int draw(int *deck) {
  int i, j;
  for (i = 0; i < 52; i++) {
    j = deck[i];
    if (j != -1) {
      deck[i] = -1;
      return j;
    } else {
      if (i == 51) {
        shuf(deck);
        i = 0;
      }
    }
  }
}

