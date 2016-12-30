// debugging
int debug = 0,quickdebug = 0,colourblind = 1,cplay = 0,
qdbtoggle = 1,sdbtoggle = 1,cdbtoggle = 1,ldbtoggle = 1,tdbtoggle = 1;
int *pdb,*ndb,*edb,*wdb;


void handDebug(Table *t, int p = P) {
  gotoxyc(t->window.cellAnchor(CELL_OUTPUT).add(0, 5));
  switch (p) {
    case P: printf("P: "); break;
    case N: printf("N: "); break;
    case E: printf("E: "); break;
    case W: printf("W: "); break;
  }
  int i;
  t->sort(t->players[p].cards);
  for (i = 0; i < 13; i++) {
    printCard(t->players[p].cards[i]);
    printf(" ");
  }
}

void cdb(char *s) {
  if (debug && cdbtoggle) {
    gotoxy(38, 17);printf("                                              ");
    gotoxy(38, 17);printf("%s", s);
    if (!quickdebug) {
      int u = getch();
      debug = (u == ';') ? (debug == 1) ? 0 : 1:debug;
    }
  }
}

void qdb(char *s) {
  if (debug && qdbtoggle) {
    if (debug) {
      gotoxy(38, 7);
      printf("        ");
      gotoxy(38, 7);
      printf("%s", s);
      //hud(ndb, edb, pdb, wdb);
      if (!quickdebug) {
        getch();
      }
    }
  }
}

void sdb(char *s) {
  if (debug&&sdbtoggle) {
    gotoxy(38, 16);
    printf("     ");
    gotoxy(38, 16);
    printf("%s", s);
  }
}

void ldb(int numPlayed) {
  /*if (debug && ldbtoggle) {
    char l = (lastplay == N)? 'N' :
    (lastplay == E)? 'E' : (lastplay == P)? 'P' : 'W';
    char n = (lastplay == N)? 'E' :
    (lastplay == E)? 'P' : (lastplay == P)? 'W' : 'N';
    if (numPlayed == 4) {
      n = '0';
    }
    gotoxy(38, 3);
    printf("last %c", l);
    gotoxy(38, 4);
    printf("next %c", n);
    return;
  }*/
}

void tdb(int *trick) {
  if (debug && tdbtoggle) {
    char lastPlay;
    int i;
    gotoxy(1, 1);
    for (i = 0; i < 4; i++) {
      lastPlay = (i == 0)? 'N' : (i == 1)? 'E' : (i == 2)? 'P' : 'W';
      printf("%c:", lastPlay);
      if (trick[i] == -1) {
        printf("-1");
      } else {
        //out('h', trick[i], "", 0);
      }
      printf(", ");
    }
    printf("%i", trick[4]);
  }
}


int debuggingoptions() {
  int read = -1;

  while (read != 0) {
    clrscr();
    (colourblind == 0)? printf("1: Using colours and letters") :
    printf("1: Using symbols");
    printf("\n2: Toggle debug - ");
    (debug == 1)? printf("ON") : printf("OFF");

    if (debug) {
      printf("\n3: Toggle quick debug - ");
      (quickdebug == 1)? printf("ON") : printf("OFF");
      printf("\n4: Toggle computer only - ");
      (cplay == 1)? printf("ON") : printf("OFF");
      printf("\n5: Toggle queen debug - ");
      (qdbtoggle == 1)? printf("ON") : printf("OFF");
      printf("\n6: Toggle function debug - ");
      (sdbtoggle == 1)? printf("ON") : printf("OFF");
      printf("\n7: Toggle comp turn debug - ");
      (cdbtoggle == 1)? printf("ON") : printf("OFF");
      printf("\n8: Toggle lastplay debug - ");
      (ldbtoggle == 1)? printf("ON") : printf("OFF");
      printf("\n9: Toggle trick debug - ");
      (tdbtoggle == 1)? printf("ON") : printf("OFF");
    }
    printf("\n0: Main menu\n\n> ");

    read = getch() - '0';
    switch (read) {
      case 0:
        return 1;
        break;
        case 1:
        colourblind = (colourblind == 1)? 0 : 1;
        break;
      case 2:
        debug = (debug == 1)? 0 : 1;
        break;
      case 3:
        quickdebug = (quickdebug == 1)? 0 : 1;
        break;
      case 4:
        cplay = (cplay == 1)? 0 : 1;
        break;
      case 5:
        qdbtoggle = (qdbtoggle == 1)? 0 : 1;
        break;
      case 6:
        sdbtoggle = (sdbtoggle == 1)? 0 : 1;
        break;
      case 7:
        cdbtoggle = (cdbtoggle == 1)? 0 : 1;
        break;
      case 8:
        ldbtoggle = (ldbtoggle == 1)? 0 : 1;
        break;
      case 9:
        tdbtoggle = (tdbtoggle == 1)? 0 : 1;
        break;
      default:
        break;
    }
  }
}

