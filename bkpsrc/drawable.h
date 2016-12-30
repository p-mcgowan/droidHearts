void phud(int *p) {
  int c = 0, i, x, t = 0;
  if (!debug) {
    if (debug) {
      gotoxy(1, 18);  // gotoxy(1, 15); <-- default
    } else {
      gotoxy(1, 15);
    }
    for (i = 0; i < 50; i++) {
      printf(" ");
    }
    if (debug) {
      gotoxy(1, 18);  // gotoxy(1, 15); <-- default
    } else {
      gotoxy(1, 15);
    }
    sort(p);
    for (i = 0; i < 13; i++) {
      if (p[i] != -1) {
        c++;
        if (p[i] % 13 == 8) {
          t++;
        }
      }
    }
    if (debug) {
      gotoxy(30 - c * 2 - t, 14);
    } else {
      gotoxy(30 - c * 2 - t, 15);
    }
    for (i = 0; i < 13; i++) {
      if (p[i] != -1) {
        out('h', p[i], "", 0);
        printf(" ");
      }
    }
  }
}

void out(char pos, int card, char* name, int n) {
  if (pos == 'p') {
    gotoxy(18, 11);printf("     ");
    if (name != "") {
      gotoxy(20 + ceil((-5 * n + 5) / 9), 10);
      printf("%s", name);
    }
    gotoxy(20, 11);
  } else if (pos == 'n') {
    gotoxy(18, 3);printf("     ");
    if (name != "") {
      gotoxy(20 + ceil((-5 * n + 5) / 9), 2);
      printf("%s", name);
    }
    gotoxy(20, 3);
  } else if (pos == 'e') {
    gotoxy(25, 7);printf("     ");
    if (name != "") {
      gotoxy(27 + ceil((-5 * n + 5) / 9), 6);
      printf("%s", name);
    }
    gotoxy(27, 7);
  } else if (pos == 'w') {
    gotoxy(11, 7);printf("     ");
    if (name != "") {
      gotoxy(13 + ceil((-5 * n + 5) / 9), 6);
      printf("%s", name);
    }
    gotoxy(13, 7);
  }
  if (card % 13 < 8) {
    printf("%c", card % 13 + '2');
  } else {
    if (card % 13 == 8 && card != NAME) {
      printf("10");
    }
    if (card % 13 == 9 && card != NAME) {
      printf("J");
    }
    if (card % 13 == 10 && card != NAME) {
      printf("Q");
    }
    if (card % 13 == 11 && card != NAME) {
      printf("K");
    }
    if (card % 13 == 12 && card != NAME) {
      printf("A");
    }
  }
  printf(YLW);
  if (card / 13 == 0) {
    printf( "C");
  }
  if (card / 13 == 2) {
    printf("S");
  }
  printf(RED);
  if (card / 13 == 1) {
    printf("D");
  }
  if (card / 13 == 3) {
    printf("H");
  }
  printf(RST);
}

void clrin() {
  int i, j;
  for (i = 17; i < 28; i++) {
    gotoxy(1, i);
    for (j = 0; j < 47; j++) {
      printf(" ");
    }
  }
}

void clrn(char *n) {
  int i;
  for (i = 0; i < 11; i++) {
    n[i] = 0;
  }
}

void hud(int *n, int *e, int *p, int *w) {
  char test;
  int *who;
  int c = 0, i, x, t = 0, j; 
  gotoxy(1, 15);
  for (j = 0; j < 4; j++) {
    gotoxy(1, 20 + j);
    for (i = 0; i < 40; i++) {
      printf(" ");
    }
  }
  gotoxy(1, 20);
  sort(p);
  sort(n);
  sort(e);
  sort(w);
  for (j = 0; j < 4; j++) {
    who = (j == 0) ? n : (j == 1) ? e : (j == 2)? p : w;
    for (i = 0; i < 13; i++) {
      if (who[i] != -1) {
        c++;
        if (who[i] % 13 == 8) {
          t++;
        }
      }
    }
    gotoxy(30 - c * 2 - t, 20 + j);
    for (i = 0; i < 13; i++) {
      if (who[i] != -1) {
        out('h', who[i], "", 0);
        printf(" ");
      }
    }
    gotoxy(43, 20 + j);
    test = (j == N) ? 'N' : (j == E) ? 'E' : (j == P) ? 'P' : 'W';
    printf("%c", test);
    c = 0;
    t = 0;
  }
}

// TODO
void printplayers(int *trick, char *nname, char *ename, char *pname, char *wname) {
  int i;
  if (trick[0] != -1) {
    out('n', trick[0], nname, nname[11]);
  } else {
    out('n', NAME, nname, nname[11]);
  }
  if (trick[1] != -1) {
    out('e', trick[1], ename, ename[11]);
  } else {
    out('e', NAME, ename, ename[11]);
  }
  if (trick[2] != -1) {
    out('p', trick[2], pname, pname[11]);
  } else {
    out('p', NAME, pname, pname[11]);
  }
  if (trick[3] != -1) {
    out('w', trick[3], wname, wname[11]);
  } else {
    out('w', NAME, wname, wname[11]);
  }
}

