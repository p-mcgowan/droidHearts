int main() {
  int p[16], n[16], e[16], w[16], trick[5] = {-1, -1, -1, -1, 0},
  deck[52], pass = 3, rnd = 0, strat[16];
  char nname[12] = "North"; nname[11] = 5;
  char ename[12] = "East"; ename[11] = 4;
  char pname[12] = "Player"; pname[11] = 6;
  char wname[12] = "West"; wname[11] = 4;
  int read = -1;
  while (read != 0) {
    clrscr();
    printf("1: New game\n2: Load game (WIP)\n3: Options\n0: Quit\n\n> ");
    read = getch() - '0';
    switch (read) {
      case 0:
        clrscr();
        printf("Thanks for playing!");
        return 0;
        break;
      case 1:
        clrscr();
        game(n, e, p, w, strat, trick, rnd, nname, ename, pname, wname,
        deck, pass, NEWGAME);
        break;
      case 2:
        if (loadgame(n, e, p, w, strat, trick, &rnd, 
        nname, ename, pname, wname, deck, &pass)) {
          clrscr();
          printplayers(trick, nname, ename, pname, wname);
          game(n, e, p, w, strat, trick, rnd, 
          nname, ename, pname, wname, deck, pass, LOAD);
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

void ldb(int numPlayed) {
  if (debug&&ldbtoggle) {
    char l = (lastplay == N)? 'N' :
    (lastplay == E)? 'E' : (lastplay == P)? 'P' : 'W';
    char n = (lastplay == N)? 'E' : 
    (lastplay == E)? 'P' : (lastplay == P)? 'W' : 'N';
    if (numPlayed == 4)
      n = '0';
    gotoxy(38, 3);
    printf("last %c", l);
    gotoxy(38, 4);
    printf("next %c", n);
    return;
  }
}

void tdb(int *trick) {
  if (debug&&tdbtoggle) {
    char lp;
    int i;
    gotoxy(1, 1);
    for(i = 0; i < 4; i++) {
      lp = (i == 0)? 'N' : (i == 1)? 'E' : (i == 2)? 'P' : 'W';
      printf("%c:", lp);
      (trick[i] == -1)? printf("-1") : out('h', trick[i], "", 0);
      printf(", ");
    }
    printf("%i", trick[4]);
  }
}

int loadgame(int *n, int *e, int *p, int *w, int *strat, int *trick, int *rnd,
char *nname, char *ename, char *pname, char *wname, int *deck, int *pass) {
  FILE *fp, *fp2;
  int i = 0;
  char fname[128], in[128];
  in[0] = -1;
  while(!(in[0] >= '0' && in[0] <= '2')) {
    clrscr();
    printf("Saves:\n\n");
    fp = fopen("saves", "r");
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) {
      printf("No saves. Press any key to continue\n> ");
      fname[0] = getch();
      fclose(fp);
      return 0;
    } else {
      fclose(fp);
      fp = fopen("saves", "r");
      fgets(in, 128, fp);
      while(!feof(fp)) {
        printf("%s", in);
        fgets(in, 128, fp);
      }
      fclose(fp);
    }
    printf("\n1: Load\t\t2: Delete\t0: Back\n> ");
    in[0] = getch();
  }
  // while invalid clear print & scan
  if (in[0] == '0')
    return 0;
  printf("Enter filename:\n> ");
  scanf("%s", fname);
  if (in[0] == '1') {
    fp = fopen(fname, "r");
    if (fp == NULL) {
      printf("\nCould not open \"%s\"", fname);
      in[0] = getch();;  // cleans input stream
      in[0] = getch();
      clrscr();
      return 0;
    }
    else{
      in[0] = getch();  // cleans input stream
      for(i = 0; i < 16; i++)
        fscanf(fp, "%d", &n[i]);
      for(i = 0; i < 16; i++)
        fscanf(fp, "%d", &e[i]);
      for(i = 0; i < 16; i++)
        fscanf(fp, "%d", &p[i]);
      for(i = 0; i < 16; i++)
        fscanf(fp, "%d", &w[i]);
      for(i = 0; i < 5; i++)
        fscanf(fp, "%d", &trick[i]);
      for(i = 0; i < 52; i++)
        fscanf(fp, "%d", &deck[i]);
      for(i = 0; i < 16; i++)
        fscanf(fp, "%d", &strat[i]);
      fgetc(fp);  // clear formatting space between strat5 and nname
      for(i = 0;i < 12; i++)
        nname[i] = fgetc(fp);
      for(i = 0;i < 12; i++)
        ename[i] = fgetc(fp);
      for(i = 0;i < 12; i++)
        pname[i] = fgetc(fp);
      for(i = 0;i < 12; i++)
        wname[i] = fgetc(fp);
      rnd = fgetc(fp);
      pass = fgetc(fp);
      lastplay = fgetc(fp);
      debug = fgetc(fp);
      quickdebug = fgetc(fp);
      cplay = fgetc(fp);
      qdbtoggle = fgetc(fp);
      sdbtoggle = fgetc(fp);
      cdbtoggle = fgetc(fp);
      ldbtoggle = fgetc(fp);
      tdbtoggle = fgetc(fp);
      printf("%s loaded sucessfully.\nPress any key to continue...", fname);
      in[0] = getch();
      fclose(fp);
      return 1;
    }
  }
  else if (in[0] == '2') {
    if (access(fname, R_OK) != -1) {
      printf("Really delete %s (y/n)?:\n>", fname);
      scanf("%s", in);
    }
    else{
      in[0] = getch();
      printf("File \"%s\" not found...", fname);
      in[0] = getch();
      in[0] == 'n';
    }
    if (in[0] == 'y') {
      unlink(fname);
      rename("saves", "tmp");
      fp = fopen("tmp", "r");
      fp2 = fopen("saves", "w");
      while(!feof(fp)) {
        fgets(in, 128, fp);
        if (strstr(in, fname) == NULL)
          fputs(in, fp2);
      }
      fclose(fp);
      fclose(fp2);
      unlink("tmp");
      printf("\n%s deleted.\nPress any key to continue...", fname);
      in[0] = getch();
      return 0;
    }
  }
  return 0;
}

int  save(int *n, int *e, int *p, int *w, int *strat, int *trick, int rnd,
char *nname, char *ename, char *pname, char *wname, int *deck, int pass) {
  FILE *fp, *fp2;
  int i = -1;
  char fname[128], in[128];
  in[0] = -1;
  clrscr();
  printf("Saves:\n\n");
  fp = fopen("saves", "r");
  fseek(fp, 0, SEEK_END);
  if (ftell(fp) == 0) {
    printf("No saves.\n");
  }
  else{
    fclose(fp);
    fp = fopen("saves", "r");
    fgets(fname, 128, fp);
    while(!feof(fp)) {
      printf("%s", fname);
      fgets(fname, 128, fp);
    }
  }
  fclose(fp);
  printf("\nSave game(y/n)?:\n> ");
  in[0] = getch();
  if (in[0] == 'n')
    return 1;
  printf("\nSave game as:\n>");
  scanf("%s", fname);
  if (access(fname, R_OK) != -1) {
    printf("%s already exists, overwrite (y/n)?:\n>", fname);
    in[0] = getch();  // cleans input stream
    in[0] = getch();
    if (in[0] == 'y') {
      unlink(fname);
      rename("saves", "tmp");
      fp = fopen("tmp", "r");
      fp2 = fopen("saves", "w");
      while(!feof(fp)) {
        fgets(in, 128, fp);
        if (strstr(in, fname) == NULL)
          fputs(in, fp2);
      }
      fclose(fp);
      fclose(fp2);
      unlink("tmp");
    }
    else{
      fclose(fp);
      return 1;
    }
  }
  fp = fopen(fname, "w");  // write save
  for(i = 0; i < 16; i++)
    fprintf(fp, "%d ", n[i]);  // fputc(n[i], fp);
  for(i = 0; i < 16; i++)
    fprintf(fp, "%d ", e[i]);  // fputc(e[i], fp);
  for(i = 0; i < 16; i++)
    fprintf(fp, "%d ", p[i]);  // fputc(p[i], fp);
  for(i = 0; i < 16; i++)
    fprintf(fp, "%d ", w[i]);  // fputc(w[i], fp);
  for(i = 0; i < 5; i++)
    fprintf(fp, "%d ", trick[i]);  // fputc(trick[i], fp);
  for(i = 0; i < 52; i++)
    fprintf(fp, "%d ", deck[i]);  // fputc(deck[i], fp);
  for(i = 0; i < 16; i++)
    fprintf(fp, "%d ", strat[i]);  // fputc(strat[i], fp);
  for(i = 0; i < 12; i++)
    fputc(nname[i], fp);
  for(i = 0; i < 12; i++)
    fputc(ename[i], fp);
  for(i = 0; i < 12; i++)
    fputc(pname[i], fp);
  for(i = 0; i < 12; i++)
    fputc(wname[i], fp);
  fputc(rnd, fp);
  fputc(pass, fp);
  fputc(lastplay, fp);
  fputc(debug, fp);
  fputc(quickdebug, fp);
  fputc(cplay, fp);
  fputc(qdbtoggle, fp);
  fputc(sdbtoggle, fp);
  fputc(cdbtoggle, fp);
  fputc(ldbtoggle, fp);
  fputc(tdbtoggle, fp);
  fclose(fp);
  fp = fopen("saves", "a");
  fputs(fname, fp);
  fputs("\n", fp);
  fclose(fp);
  printf("%s saved sucessfully.\nPress any key to continue...", fname);
  in[0] = getch();
  return 1;
 }
int gameOptions(int *n, int *e, int *p, int *w, int *strat, int *trick, int rnd, 
char *nname, char *ename, char *pname, char *wname, int *deck, int pass) {
  int input = -1;
  while (input == -1) {
    clrscr();
    printf("1: Save and exit\n2: Options\n0: Back to game\n> ");
    input = getch() - '0';
    switch (input) {
      case 1:
        save(n, e, p, w, strat, trick, rnd,
        nname, ename, pname, wname, deck, pass);
        return 0;
        break;
      case 2:
        debuggingoptions();
        input = -1;
        break;
      case 0:
        clrscr();
        return -1;  // sends -1 to gChoice to continue loop
        break;
      default:
        input = -1;
        break;
    }
  }
}

void printplayers(int *trick, char *nname, char *ename, char *pname, char *wname) {
  int i;
  if (trick[0] != -1)
    out('n', trick[0], nname, nname[11]);
  else
    out('n', NAME, nname, nname[11]);
  if (trick[1] != -1)
    out('e', trick[1], ename, ename[11]);
  else
    out('e', NAME, ename, ename[11]);
  if (trick[2] != -1)
    out('p', trick[2], pname, pname[11]);
  else
    out('p', NAME, pname, pname[11]);
  if (trick[3] != -1)
    out('w', trick[3], wname, wname[11]);
  else
    out('w', NAME, wname, wname[11]);
}

int game(int *n, int *e, int *p, int *w, int *strat, int *trick, int *rnd,
char *nname, char *ename, char *pname, char *wname,
int *deck, int *pass, int newgame) {
    int nd = 0, ed = 0, pd = 0, wd = 0, name = 1;
    int i, j, rounds;  // , pass = 3;  // pass = 0;
    ndb = n;edb = e;pdb = p;wdb = w;
    int s = 0, t; char test, u = 0;
    int gChoice = -1;  // get choice - for save
  // gameOptions(n, e.p, w, strat, trick, rnd, nname, ename, pname, wname, deck, pass);
    while(1) {
        while(newgame||!won(n, e, p, w)) {
  // p[TOT] = e[TOT] = w[TOT] = n[TOT] = 0;
      if (newgame) {
        names(nname, ename, pname, wname, name);
        name = 0;
        init(n, e, p, w, deck, strat);
        if (debug) {
          hud(n, e, p, w);gotoxy(1, 1);}
        u = getchar();  // debug = (u == ';')?(debug == 1)? 0 : 1:debug;  // getch?
            passcards(n, e, p, w, pass);
           lastplay = start(n, e, p, w);
            tsuit = 4;s = 0;
           t = 0;
            trick[lastplay] = C2;
            trick[4]++;
          }
            for(rounds = 0;rounds<51;rounds++) {
              sdb("   ");
              pass = 3;
                if (debug) {
          sdb("D1 ");
                    gotoxy(38, 1);printf("strt %i", s);
                    /*gotoxy(1, 3);
                    test = (lastplay == N)?'N':(lastplay == E)?'E':(lastplay == P)?'P':'W';
                    printf("last %c", test);*/  // replaced by ldb
                    ldb(trick[4]);
                  gotoxy(38, 2);printf("suit ");
                  (tsuit == 0||tsuit == 4)?printf("♣"):(tsuit == 1)?
                  printf("♦"):(tsuit == 2)?printf("♠"):printf("♥");
                  gotoxy(38, 5);printf("rnd %i", rnd);
                  gotoxy(38, 6);printf("    ");
                  nd = ed = pd = wd = 0;
                  for(i = 0;i<13;i++) {
                      if (n[i] != -1)
                          nd++;
                      if (e[i] != -1)
                          ed++;
                      if (p[i] != -1)
                         pd++;
                      if (w[i] != -1)
                          wd++;
          }
                gotoxy(38, 7);printf("n %i %i %i    ", nd, n[SCR], n[TOT]);
          gotoxy(38, 8);printf("e %i %i %i    ", ed, e[SCR], e[TOT]);
                gotoxy(38, 9);printf("p %i %i %i    ", pd, p[SCR], p[TOT]);
              gotoxy(38, 10);printf("w %i %i %i    ", wd, w[SCR], w[TOT]);
                gotoxy(1, 12);
                  for(i = 0;i<16;i++) {
                      if (i%4 == 0&&i != 0)
                          printf(" ");
                    printf("%i ", strat[i]);
                  }
                  /*gotoxy(10, 1);
                 for(i = 0;i<4;i++) {
                       test = (i == N)?'N':(i == E)?'E':(i == P)?'P':'W';
                       printf("%c:", test);
                     (trick[i] == -1)?printf("-1"):out('h', trick[i], "", 0);
                     printf(", ");
          }
          printf("%i", trick[4]);*/  // replaced by tdb
          tdb(trick);
          hud(n, e, p, w);
          sdb("D1\\");
          u = getch();
        }
        if (lastplay == E) {
          sdb("P1 ");
          phud(p);
          if (debug) {
  // gotoxy(1, 4);printf("next P");  // replaced by ldb
            ldb(trick[4]);
          }
          if (cplay) {
            lastplay = compturn(p, trick, rnd, s, 'p', strat, n, e, w);
            if (debug&&ldbtoggle) {
              gotoxy(38, 11);printf("lp %i", lastplay);}
          }
          else {
            gChoice = -1;
  // gChoice = getchoice(p, s, rnd, trick, strat);
            while (gChoice == -1) {
              phud(p);
              if (debug) hud(n, e, p, w);
              gChoice = getchoice(p, s, rnd, trick, strat);
              if (gChoice == 1) {
                gChoice = gameOptions( n, e, p, w, strat, trick, rnd, nname, ename, pname, wname, deck, pass);
              }
              if (gChoice == 0) {
                return 0;}
              printplayers(trick, nname, ename, pname, wname);
            }
            lastplay = P;
            if (debug&&ldbtoggle) {
              gotoxy(38, 11);printf("lp %i", lastplay);}
          }
          trick[4]++;
          if (debug&&ldbtoggle) {ldb(trick[4]);}
          sdb("P1\\");
        }
        else if (lastplay == P) {
          sdb("W1 ");
          if (debug) {
  // gotoxy(1, 4);printf("next W");  // replaced by ldb
              ldb(trick[4]);
          }  // u = getch();debug = (u == ';')?(debug == 1)? 0 : 1:debug;}
          lastplay = compturn(w, trick, rnd, s, 'w', strat, n, e, p);
          if (debug&&ldbtoggle) {
          gotoxy(38, 11);printf("lp %i", lastplay);}
          trick[4]++;
          if (debug&&ldbtoggle) {ldb(trick[4]);}
          sdb("W1\\");
        }
        else if (lastplay == W) {
          sdb("N1 ");
          if (debug) {
  // gotoxy(1, 4);printf("next N");  // replaced by ldb
            ldb(trick[4]);
          }  // u = getch();debug = (u == ';')?(debug == 1)? 0 : 1:debug;}
          lastplay = compturn(n, trick, rnd, s, 'n', strat, e, p, w);
          if (debug&&ldbtoggle) {
          gotoxy(38, 11);printf("lp %i", lastplay);}
          trick[4]++;
          if (debug&&ldbtoggle) {ldb(trick[4]);}
          sdb("N1\\");
        }
        else if (lastplay == N) {
          sdb("E1 ");
          if (debug) {
  // gotoxy(1, 4);printf("next E");  // replaced by ldb
            ldb(trick[4]);
            }  // u = getch();debug = (u == ';')?(debug == 1)? 0 : 1:debug;}
          lastplay = compturn(e, trick, rnd, s, 'e', strat, w, n, p);
          if (debug&&ldbtoggle) {
          gotoxy(38, 11);printf("lp %i", lastplay);}
          trick[4]++;
          if (debug&&ldbtoggle) {ldb(trick[4]);}
          sdb("E1\\");
        }
  // qdb("et");
        tdb(trick);
        if (trick[4] == 4) {
          sdb("T1 ");
          s = 1;
          trick[4] = 0;
          phud(p);
          sdb("Ta ");
          lastplay = score(n, e, p, w, trick, 0);
          sdb("Tb ");
          u = getch();
          for(i = 0;i<4;i++) {
            trick[i] = -1;}
          sdb("Tc ");
          trick[4] = 0;
          sdb("Td ");
          if (debug)
            gotoxy(35, 1);
          else
            gotoxy(1, 1);
          sdb("Te ");/*
          scanf("%c", &u);
          i = getch();*/
  // if (!quickdebug) {
  // u = getch();
  // }
  // debug = (u == ';')?(debug == 1)? 0 : 1:debug;
          sdb("Tg ");
  // names(nname, ename, pname, wname, name);
          sdb("Th ");
          out('n', NAME, "", 0);
          out('e', NAME, "", 0);
          out('p', NAME, "", 0);
          out('w', NAME, "", 0);  // clr out
          sdb("T1\\");
        }
        else{
          sdb("T2 ");
          s = 0;
  // trick[4]++;  // for tdb - updates after lastplay does
          tdb(trick);
          ldb(trick[4]);
          sdb("T2\\");
        }
        rnd = n[SCR]+e[SCR]+p[SCR]+w[SCR];
        n[RND] = e[RND] = p[RND] = w[RND] = 0;
  // if (!quickdebug) {u = getch();  // }
              if (debug) {
                 hud(n, e, p, w);}  // gotoxy(1, 1);}
  // u = getch();  // right place
      }  // round end
      newgame = 0;
      pass = (pass == 3)?0:pass+1;
      if (n[SCR] == 26) {
        e[TOT]+ = 26;
        p[TOT]+ = 26;
        w[TOT]+ = 26;
      }
      else if (e[SCR] == 26) {
        n[TOT]+ = 26;
        p[TOT]+ = 26;
        w[TOT]+ = 26;
      }
      else if (p[SCR] == 26) {
        n[TOT]+ = 26;
        e[TOT]+ = 26;
        w[TOT]+ = 26;
      }
      else if (w[SCR] == 26) {
        n[TOT]+ = 26;
        e[TOT]+ = 26;
        p[TOT]+ = 26;
      }
      else{
        n[TOT]+ = n[SCR];
        e[TOT]+ = e[SCR];
        p[TOT]+ = p[SCR];
        w[TOT]+ = w[SCR];
      }
      n[SCR] = e[SCR] = w[SCR] = p[SCR] = 0;
      clrscr();
      score(n, e, p, w, trick, 1);
  // hud(n, e, p, w);
      getch();
      clrscr();
    }
    }
}
/*void clrscr() {
  system("clear");
}
void gotoxy(int x, int y) {
  printf("%c[%d;%df", 0x1B, y, x);
}*/
void sdb(char *s) {if (debug&&sdbtoggle) {
  gotoxy(38, 16);
  printf("     ");
  gotoxy(38, 16);
  printf("%s", s);
}}
void compwait() {
  int u;
  // gotoxy(1, 1);printf("sleep");  // u = getch();
  int i, j, k = 0;
  for(i = 0;i<10000;i++) {
    for(j = 0;j<1000;j++) {
      k++;
    }
  }
  // gotoxy(1, 1);printf("sleep\\");  // u = getch();
}
void give(int *rx, int *tx) {
    int i;
    sort(rx);
    for(i = 0;i<3;i++) {
        rx[i] = tx[i];
    }
}
void ppass(int *p, int *pp, int w) {
    char c; int r, s, pass[4] = {-1, -1, -1, 0}, i, pi;
    while(pass[0] == -1||pass[1] == -1||pass[2] == -1) {
        while(!(c>'1'&&c<= '9')&&c != 'j'&&c != 'q'&&c != 'k'&&c != 'a'&&c != 10) {
            clrin();
            phud(p);
            gotoxy(1, 17);printf("Enter cards to pass ");
            (w == LEFT)?printf("left"):(w == RIGHT)?printf("right"):printf("across");
            printf(", 0 to reset:");
            gotoxy(1, 18);
            printf("Enter a rank (2-10, J-A): ");
            c = getch();
            printf("%c", c);
            if (c == '1') {
                c = getch();
                if (c == '0') {
                    printf("%c", c);
                    c = 10;}
                else c = 0;
            }
            if (c == '0') {
                for(i = 0;i<3;i++) {
                    if (pass[i] != -1)
                        p[i] = pass[i];
                    pass[i] = -1;}
                pass[3] = 0;
                gotoxy(1, 16);printf("               ");
            }
        }
        r = ((c>'1'&&c<= '9')||c == 10)?
        (c == 10)?c-2:c-'0'-2:(c == 'j')?9:
        (c == 'q')?10:(c == 'k')?11:12;
        c = 0;
        while(c != 'h'&&c != 'c'&&c != 'd'&&c != 's') {
            gotoxy(1, 19);
            printf("Enter a suit (C, D, S, H): ");
            c = getch();
            printf("%c", c);
        }
        s = (c == 'c')?0:(c == 'd')?1:(c == 's')? 2 : 3;
        for(i = 0;i<13;i++) {
            if (p[i] == r+13*s) {
                gotoxy(1, 20);
                printf("Pass the ");
                out('c', r+13*s, "", 0);
                printf(" (y/n)? ");
                while(c != 'y'&&c != 'n') {
          c = getch();}
                pi = i;
                break;}
        }
        if (c == 'y') {
            pass[3]++;
            for(i = 0;i<4;i++) {
                if (pass[i] == -1) {
                    pass[i] = r+13*s;
                    p[pi] = -1;
                    break;}
            }
        }
        gotoxy(1, 16);printf("               ");
        for(i = 0;i<3;i++) {
            if (pass[i] != -1) {
                gotoxy(1+4*i, 16);
                out('t', pass[i], "", 0);}
        }
        if (pass[3] == 3) {
            clrin();
            phud(p);
            gotoxy(1, 16);printf("               ");
            for(i = 0;i<3;i++) {
                if (pass[i] != -1) {
                    gotoxy(1+4*i, 16);
                    out('t', pass[i], "", 0);}
            }
            c = 0;
            gotoxy(1, 18);printf("Pass these cards (y/n)? ");
            while(c != 'y'&&c != 'n') {
              c = getch();}
            if (c == 'y')
                break;
            else{
                for(i = 0;i<3;i++) {
                    p[i] = pass[i];
                    pass[i] = -1;}
                pass[3] = 0;
                gotoxy(1, 16);printf("               ");
            }
        }
    }
    for(i = 0;i<3;i++) {
        pp[i] = pass[i];}
    return;
}
void cmax(int *p, int *pp) {
    int max = 0, imax = -1, pass[3], i, j;
    sort(p);
    for(j = 0;j<3;j++) {
       for(i = 12;i>= 0;i--) {
           if (p[i]%13>max) {
               max = p[i]%13;
               imax = i;}
       }
       pass[j] = p[imax];
       p[imax] = -1;
       imax = -1;
       max = 0;
   }
   for(i = 0;i<3;i++) {
       pp[i] = pass[i];}
   sort(p);
   return;
}
void passcards(int *n, int *e, int *p, int *w, int pass) {
   int i, np[3], ep[3], pp[3], wp[3], max;
   if (pass == HOLD)
       return;
   cmax(n, np); cmax(e, ep); cmax(w, wp);
   ppass(p, pp, pass);
   gotoxy(1, 1);
   if (pass == LEFT) {
       give(n, wp);
       give(e, np);
       give(p, ep);
       give(w, pp);
   }
   if (pass == RIGHT) {
       give(n, ep);
       give(e, pp);;
       give(p, wp);
       give(w, np);
   }
   if (pass == ACROSS) {
       give(n, pp);
       give(e, wp);
       give(p, np);
       give(w, ep);
   }
   clrin();
   gotoxy(1, 16);printf("               ");
   gotoxy(1, 17);printf("Received: ");
   for(i = 0;i<3;i++) {
        gotoxy(1+4*i, 18);
        out('t', p[i], "", 0);
    }
    phud(p);
    gotoxy(1, 1);
    i = getch();
    clrin();
    return;
}
int won(int *n, int *e, int *p, int *w) {
    if (n[TOT]>99||e[TOT]>99||p[TOT]>99||w[TOT]>99)
        return 1;
    return 0;
}
void qdb(char *s) { if (debug&&qdbtoggle) {
    int u;  // if (0) {
    if (debug) {
    gotoxy(38, 7);
    printf("        ");
    gotoxy(38, 7);
    printf("%s", s);
   hud(ndb, edb, pdb, wdb);
   if (!quickdebug) {
    u = getch();}}}
}
int suitsleft(int *strat, int suit, int who) {
    if (debug) {gotoxy(38, 6);printf("sut");if (!quickdebug) {int u = getch();
    debug = (u == ';')?(debug == 1)? 0 : 1:debug;}}
    int i, left = 0;
    for(i = 0;i<4;i++) {
        if (i != who&&strat[i*4+suit]>0)
            left++;
    }
    if (left == 3)
        return 0;
    return 1;
}
void hassuit(int *p, int *strat, int tsuit, int suit) {
     if (debug) {gotoxy(1, 6);printf("has");if (!quickdebug) {int u = getch();
    debug = (u == ';')?(debug == 1)? 0 : 1:debug;}}
    int i, j, c = 0, d = 0, s = 0, h = 0;
        for(i = 0;i<13;i++) {
            if (p[i]/13 == CLB)
                c++;
            if (p[i]/13 == DIM)
                d++;
            if (p[i]/13 == SPD)
                s++;
            if (p[i]/13 == HRT)
                h++;
        }
        gotoxy(1, 17);
        if (tsuit != suit) {
            if (c == 0)
                strat[8]++;
            if (d == 0)
                strat[9]++;
            if (s == 0)
                strat[10]++;
            if (h == 0)
                strat[11]++;
        }
}
void hud(int *n, int *e, int *p, int *w) {
int c = 0, i, x, t = 0, j, *who; char test;
    gotoxy(1, 15);
    for(j = 0;j<4;j++) {
        gotoxy(1, 20+j);
    for(i = 0;i<40;i++)
        printf(" ");
    }
    gotoxy(1, 20);
    sort(p);
    sort(n);
    sort(e);
    sort(w);
    for(j = 0;j<4;j++) {
    who = (j == 0)?n:(j == 1)?e:(j == 2)?p:w;
    for(i = 0;i<13;i++) {
        if (who[i] != -1) {
            c++;
            if (who[i]%13 == 8)
                t++;
        }
    }
    gotoxy(30-c*2-t, 20+j);
    for(i = 0;i<13;i++) {
        if (who[i] != -1) {
            out('h', who[i], "", 0);
            printf(" ");
        }
    }
    gotoxy(43, 20+j);
    test = (j == N)?'N':(j == E)?'E':(j == P)?'P':'W';
    printf("%c", test);
    c = 0;t = 0;
    }
}
int score(int *n, int *e, int *p, int *w, int *trick, int print) {
    int i, pts = 0, max = -1, winner, s = (tsuit == 4)?0:tsuit;
    for(i = 0;i<4;i++) {
        if (trick[i]>= H2)
            pts++;
        if (trick[i] == SQ)
            pts+ = 13;
        if (trick[i]/13 == s&&trick[i]%13>max) {
            winner = i;
            max = trick[i]%13;}
   }
   if (winner == N&&!print) {
       n[RND]+ = pts;}
   if (winner == E&&!print) {
       e[RND]+ = pts;}
   if (winner == P&&!print) {
       p[RND]+ = pts;}
   if (winner == W&&!print) {
       w[RND]+ = pts;}
  if (!print) {
     n[SCR]+ = n[RND];
      e[SCR]+ = e[RND];
      p[SCR]+ = p[RND];
     w[SCR]+ = w[RND];
  }
   if (!debug) {
    i = (print == 0)? 9 : 0;
       gotoxy(1, 10+i);printf("Name\t\tRound\tTotal\tOverall");i++;
       gotoxy(1, 10+i);printf("North\t\t%i\t%i\t%i", n[RND], n[SCR], n[TOT]);i++;
       gotoxy(1, 10+i);printf("East\t\t%i\t%i\t%i", e[RND], e[SCR], e[TOT]);i++;
       gotoxy(1, 10+i);printf("Player\t\t%i\t%i\t%i", p[RND], p[SCR], p[TOT]);i++;
       gotoxy(1, 10+i);;printf("West\t\t%i\t%i\t%i", w[RND], w[SCR], w[TOT]);i++;
  }
   return (winner == N)?W:winner-1;
}
int onlypts(int *p) {
    int i;
    for(i = 0;i<13;i++) {
        if (p[i] != -1&&p[i] != SQ&&p[i]<H2)
            return 0;
    }
    return 1;
}
int playmaxavg(int *p, char who, int start, int *trick, int rnd, int *strat, int nosuits) {
int u;
     if (debug) {gotoxy(38, 6);printf("avg");if (!quickdebug) {u = getch();
    debug = (u == ';')?(debug == 1)? 0 : 1:debug;}}
    float nh = 0, ns = 0, nc = 0, nd = 0, sh = 0, ss = 0, sc = 0, sd = 0;
    int i, qs = -1;
    float ah = 0, ac = 0, as = 0, ad = 0;
   int istrat = (who == 'n')?N:(who == 'e')?E:(who == 'p')?P:W;
    for(i = 0;i<13;i++) {
        if (p[i] == SQ) {
            qs = i;
            break;}
    }
    for(i = 0;i<13;i++) {
        if (p[i] != -1&&p[i]/13 == CLB) {
            nc++;
            sc+ = p[i]%13+2;}
        if (p[i] != -1&&p[i]/13 == DIM) {
            nd++;
            sd+ = p[i]%13+2;}
        if (p[i] != -1&&p[i]/13 == SPD) {
            ns++;
            ss+ = p[i]%13+2;}
        if (p[i] != -1&&p[i]/13 == HRT) {
            nh++;
            sh+ = p[i]%13+2;}
    }
     if (debug) {
        gotoxy(38, 12);printf("nc %1.0f, sc %1.0f", nc, sc);
        gotoxy(38, 13);printf("nd %1.0f, sd %1.0f", nd, sd);
        gotoxy(38, 14);printf("ns %1.0f, ss %1.0f", ns, ss);
        gotoxy(38, 15);printf("nh %1.0f, sh %1.0f", nh, sh);
        gotoxy(38, 13);if (!quickdebug) {u = getch();
      debug = (u == ';')?(debug == 1)? 0 : 1:debug;}
        gotoxy(38, 12);(nh != 0)?printf("ah %3.2f        ", sh/nh):printf("ah 0");
        gotoxy(38, 13);(nc != 0)?printf("ac %3.2f        ", sc/nc):printf("ac 0");
        gotoxy(38, 14);(ns != 0)?printf("as %3.2f        ", ss/ns):printf("as 0");
        gotoxy(38, 13);(nd != 0)?printf("ad %3.2f       ", sd/nd):printf("nd 0");
      if (!quickdebug) {u = getch();debug = (u == ';')?(debug == 1)? 0 : 1:debug;}}
    if (start) {
        if (nc<3&&sc<10&&nc != 0&&suitsleft(strat, CLB, istrat))
            ac = 50;
         else
            ac = nc;
        if (nd<3&&sd<10&&nd != 0&&suitsleft(strat, DIM, istrat))
            ad = 50;
        else
            ad = nd;
        if (ns<3&&ss<10&&ns != 0&&suitsleft(strat, SPD, istrat))
            as = 50;
        else
            as = ns;
        if (nh<3&&sh<10&&nh != 0&&suitsleft(strat, HRT, istrat))
            ah = 50;
        else
            ah = nh;
    }
    else{
  if (nc != 0)
        ac = sc/nc;
    if (nd != 0)
        ad = sd/nd;
     if (ns != 0)
        as = ss/ns;
    if (nh != 0)
        ah = sh/nh;
    }
    if (tsuit == 4||(rnd == 0&&start == 1&&!onlypts(p)))
        ah = 0;
  if (debug) {
  gotoxy(38, 12);printf("ah %3.2f        ", ah);
    gotoxy(38, 13);printf("ac %3.2f        ", ac);
    gotoxy(38, 14);printf("as %3.2f        ", as);
    gotoxy(38, 15);printf("ad %3.2f       ", ad);
    if (!quickdebug) {u = getch();debug = (u == ';')?(debug == 1)? 0 : 1:debug;}}
    if (qs != -1&&start == 0&&tsuit != 4) {
        out(who, SQ, "", 0);
        trick[istrat] = SQ;
        p[qs] = -1;
        return 1;}
    if (ac>= as&&ac>= ad&&ac>= ah&&(suitsleft(strat, CLB, istrat)
    ||nosuits)) {
        if (start == 0)
            playmax(p, CLB, 52, who, trick, start);
        else
            playmin(p, CLB, 52, who, trick, start, rnd);
        return 1;
    }
    if (ad>= as&&ad>= ah&&ad>= ac&&(suitsleft(strat, DIM, istrat)
    ||nosuits)) {
        if (start == 0)
            playmax(p, DIM, 52, who, trick, start);
        else
            playmin(p, DIM, 52, who, trick, start, rnd);
        return 1;
    }
    if (as>= ac&&as>= ad&&as>= ah&&(suitsleft(strat, SPD, istrat)
    ||nosuits)) {
        if (start == 0)
            playmax(p, SPD, 52, who, trick, start);
        else
            playmin(p, SPD, 52, who, trick, start, rnd);
        return 1;
    }
    if (ah>= as&&ah>= ad&&ah>= ac&&(suitsleft(strat, HRT, istrat)
    ||nosuits)) {
        if (start == 0)
            playmax(p, HRT, 52, who, trick, start);
        else
            playmin(p, HRT, 52, who, trick, start, rnd);
        return 1;
    }
    playmaxavg(p, who, start, trick, rnd, strat, 1);
    return 1;
}
int ptsintrick(int *t) {
    int i;
    for(i = 0;i<4;i++) {
        if (t[i] == SQ||t[i]>= H2)
            return 1;
    }
    return 0;
}
int playmax(int *p, int suit, int tmax, char who, int *trick, int start) {
     if (debug) {gotoxy(38, 6);printf("max");
     if (!quickdebug) {int u = getch();debug = (u == ';')?(debug == 1)? 0 : 1:debug;}}
    int i, max = -1, imax = -1, queen = 0, qs = -1;
    int w = (who == 'n')?N:(who == 'e')?E:(who == 'p')?P:W;
    for(i = 0;i<13;i++) {
        if (p[i] != -1&&p[i]/13 == suit&&p[i]>max&&p[i]<tmax) {
            max = p[i];imax = i;}
        if (p[i] == SQ)
            qs = i;
    }
    if (imax != -1) {
        if (p[imax] == SQ&&playmax(p, suit, SQ, who, trick, start))
            return 1;  // can play under SQ
        for(i = 0;i<4;i++) {
            if (trick[i] == SK||trick[i] == SA)
                queen = 1;
        }
        if (qs != -1&&suit == SPD&&queen == 1) {
            out(who, p[qs], "", 0);
            trick[w] = SQ;
            p[qs] = -1;
            return 1;}
        out(who, p[imax], "", 0);
        trick[w] = p[imax];
        if (start)
            tsuit = p[imax]/13;
        p[imax] = -1;
        return 1;
    }
    else
        return 0;
}
int trickmax(int *p, int s) {
    int i, m = -1;
    for(i = 0;i<4;i++) {
        if (p[i]>m&&p[i]/13 == s)
            m = p[i];
    }
    return m;
}
int trickmin(int *p, int s) {
    int i, m = 100;
    for(i = 0;i<4;i++) {
        if (p[i]<m&&p[i]/13 == s&&p[i] != -1)
            m = p[i];
    }
    return (m == 100)?-1:m;
}
int playmin(int *p, int suit, int max, char who, int *trick, int start, int rnd) {
     if (debug) {gotoxy(38, 6);printf("min");
     if (!quickdebug) {int u = getch();debug = (u == ';')?(debug == 1)? 0 : 1:debug;}}
    int i, min = 52, imin = -1;
    int w = (who == 'n')?N:(who == 'e')?E:(who == 'p')?P:W;
    for(i = 0;i<13;i++) {
        if (p[i] != -1&&p[i]/13 == suit&& p[i]<min&&p[i]<max) {
            if (validtrick(p, p[i], start, rnd)) {
                min = p[i];imin = i;}
        }
    }
    if (imin != -1) {
        if (p[imin] == SQ&&playmax(p, suit, 52, who, trick, start))
            return 1;  // can play higher than SQ
        out(who, p[imin], "", 0);
        trick[w] = p[imin];
        if (start)
            tsuit = p[imin]/13;
        p[imin] = -1;
        return 1;
    }
    return 0;
}
int nosuitsnext(char who, int *strat, int *trick, int suit) {
  if (who == 'n') {
    if ((trick[W] == -1&&strat[4*W+suit] == 0)||(trick[E] == -1&&strat[4*E] == 0)||
    (trick[P] == -1&&strat[4*P+suit] == 0))
      return 0;
    else
      return 1;
    return 0;
  }
  if (who == 'e') {
    if ((trick[N] == -1&&strat[4*N+suit] == 0)||(trick[W] == -1&&strat[4*W] == 0)||
    (trick[P] == -1&&strat[4*P+suit] == 0))
      return 0;
    else
      return 1;
    return 0;
  }
  if (who == 'w') {
    if ((trick[N] == -1&&strat[4*N+suit] == 0)||(trick[E] == -1&&strat[4*E] == 0)||
    (trick[P] == -1&&strat[4*P+suit] == 0))
      return 0;
    else
      return 1;
    return 0;
  }
}
int pointscannotbetaken(int *trick, int suit, int *a, int*b, int *c, int *p) {
  cdb("queen");
  int i, q = 1;
  if (suit == HRT)
    return 0;
  for(i = 0;i<4;i++) {
    if (trick[i]>H2||trick[i] == SQ)
      return 0;
  }
  if (suit != SPD)
    return 1;
  else{
    for(i = 0;i<13;i++) {
      if (p[i] == SQ)
        return 1;
    }
    for(i = 0;i<13;i++) {
      if (a[i] == SQ||b[i] == SQ||c[i] == SQ) {
        q = 0;
        break;
      }
    }
    cdb("\\queen");
    return q;
  }
}
void cdb(char *s) {if (debug&&cdbtoggle) {
gotoxy(38, 17);
printf("                                              ");gotoxy(38, 17);printf("%s", s);
if (!quickdebug) {int u = getch();debug = (u == ';')?(debug == 1)? 0 : 1:debug;}}}
int compturn(int* p, int *trick, int rnd, int start, char who, int *strat, int *a, int *b, int *c) {
    int i, j = 0, s = 0, low, u, qs = 0;
    int suit = (tsuit == 4)?0:tsuit;
    int played = (lastplay == W)?N:lastplay+1;
    int istrat = (who == 'n')?0:(who == 'e')? 1 : 3;
     cdb("ct");
        if (start == 0) {  // not starting
            cdb("not start");
            for(i = 0;i<13;i++) {
                if (p[i] != -1&&p[i]/13 == suit)
                    s++;}
                if (debug) {
                    gotoxy(45, 2);printf("s:%i", s);}
            if (s>0) {  // has same suit
                cdb("same suit");
                if (s == 1) {  // last card of that suit
                cdb("last card");
                    playmin(p, suit, 52, who, trick, start, rnd);
                    return played;
                }
                else{  // has more than one
                cdb("more than 1");
                    if (trick[4] == 3||nosuitsnext(who, strat, trick, suit)) {  // last to play
                        cdb("last to play");
                        if (ptsintrick(trick)) {
                         cdb("pntsintrick");
                            if (playmax(p, suit, trickmax(trick, suit), who, trick, start)) {
                              cdb("can play under");
  // can play under
                                return played;}
                            else{  // cant play under
                            cdb("cant play under");
                                playmax(p, suit, 52, who, trick, start);
                                return played;}
                        }
                        else{  // no pts in trick
                        cdb("!pntintrick");
                            playmax(p, suit, 52, who, trick, start);
                            return played;
                        }
                    }
                    else{  // not last to play
                    cdb("!last to play");
                        if (tsuit == 4) {
                         cdb("first trick");
                            if (playmax(p, suit, 52, who, trick, start)) {
                             cdb("play max");
                                return played;
                            }
                        }
                        if (playmax(p, suit, trickmax(trick, suit), who, trick, start)) {
                         cdb("!first trick&can play under");
                            return played;
                       }
                        else{  // cant play under
              cdb("!first trick&cant play under");
              if (trick[4] == 2&&pointscannotbetaken(trick, suit, a, b, c, p)) {
                playmax(p, suit, 52, who, trick, start);
              }
              else{
                             playmin(p, suit, 52, who, trick, start, rnd);
              }
                         cdb("!frst&cantunder\\");
                            return played;
                        }
                    }
                }
            }
            else{  // doesnt have same suit
                 cdb("no suit");
                strat[istrat*4+suit]++;
                playmaxavg(p, who, start, trick, rnd, strat, 1);
                return played;
            }
        }
        else{  // starting
             cdb("starting");
            playmaxavg(p, who, start, trick, rnd, strat, 0);
            return played;
        }
}
void clrn(char *n) {
    int i;
    for(i = 0;i<11;i++)
        n[i] = 0;
}
void names(char *n, char *e , char* p, char *w, int name) {
    char buff[128]; int i, j, dum;
    if (name == 1) {
      printf("Change names (y/n)? >");
      i = getch();
    if (i == 'y') {
        for(i = 0;i<11;i++) {
            n[i] = 0;buff[i] = 0;}
        clrscr();printf("Name North:\n> ");
        scanf("%s", buff);
        i = getch();
        for(i = 0;i<10;i++) {
            n[i] = buff[i];
            if (buff[i+1] == 0||i == 9) {
                n[11] = i+1;
                break;}
        }
        for(i = 0;i<11;i++) {
            e[i] = 0;buff[i] = 0;}
        clrscr();printf("Name East:\n> ");
        scanf("%s", buff);
        i = getch();
        for(i = 0;i<10;i++) {
            e[i] = buff[i];
            if (buff[i+1] == 0||i == 9) {
                e[11] = i+1;
                break;}
        }
        for(i = 0;i<11;i++) {
            p[i] = 0;buff[i] = 0;}
        clrscr();printf("Name Player:\n> ");
        scanf("%s", buff);
        i = getch();
        for(i = 0;i<10;i++) {
            p[i] = buff[i];
            if (buff[i+1] == 0||i == 9) {
                p[11] = i+1;
                break;}
        }
        for(i = 0;i<11;i++) {
            w[i] = 0;buff[i] = 0;}
        clrscr();printf("Name West:\n> ");
        scanf("%s", buff);
        i = getch();
        for(i = 0;i<10;i++) {
            w[i] = buff[i];
            if (buff[i+1] == 0||i == 9) {
                w[11] = i+1;
                break;}
        }
    }
    else{
    n[11] = 5;
    e[11] = 4;
    p[11] = 6;
    w[11] = 4;
    }
    }
    clrscr();
    out('n', NAME, n, (int)(n[11]));
    out('e', NAME, e, (int)(e[11]));
    out('p', NAME, p, (int)(p[11]));
    out('w', NAME, w, (int)(w[11]));
}
int validtrick(int *p, int card, int start, int rnd) {
    int hrts = 0, spds = 0, dims = 0, clbs = 0;
    int i, j = 0, s = card/13;
    for(i = 0;i<13;i++) {
        if (p[i]>= C2&&p[i]<= CA)
            clbs++;
        if (p[i]>= D2&&p[i]<= DA)
            dims++;
        if (p[i]>= S2&&p[i]<= SA)
            spds++;
        if (p[i]>= H2&&p[i]<= HA)
            hrts++;}
  // pts not broken-chk rnd pts
    if (start == 1) {  // if your starting
        if (rnd != 0)
            return 1;
        else{  // rnd == 0
            for(i = 0;i<13;i++) {  // if have non pts
                if (p[i] != -1&&p[i] != SQ&&p[i]<H2) {
                    j = 1;  // have non pnt
                    if (card == p[i])
                        return 1;
                }
            }
            if (j != 1)
                return 1;
            return 0;
        }
    }
    else{  // not starting
        if (tsuit == 4) {
            if (s == CLB|| (clbs == 0&&s != HRT&&card != SQ)) {
                return 1;}
            for(i = 0;i<13;i++) {
                if (p[i] != -1&& (p[i] == SQ||p[i]>= H2) ) {
                     j++;}
            }  // if only pts cards
            if (j == 13)
                return 1;
            else
                return 0;
        }
        else{  // not first rnd
             if (s == tsuit)
                return 1;
             else{
                 if ((tsuit == SPD&&spds == 0)||
                    (tsuit == DIM&&dims == 0)||
                    (tsuit == HRT&&hrts == 0)||
                    (tsuit == CLB&&clbs == 0) ) {
                      return 1;}
               }
               return 0;
         }
     }
}
void clrin() {
    int i, j;
    for(i = 17;i<28;i++) {
        gotoxy(1, i);
        for(j = 0;j<47;j++)
            printf(" ");
    }
}
int getchoice(int *p, int start, int rnd, int *trick, int *strat) {
    int i, r, s, suit = (tsuit == 4)?0:tsuit;
    char c = 0;
     while(!(c>= '0'&&c<= '9')&&c != 'j'&&c != 'q'&&c != 'k'&&c != 'a'&&c != 10) {
        if (!debug)
            clrin();
        gotoxy(1, 17);
        printf("Enter a rank (2-10, J-A) or 0 for options: ");
        c = getch();
        if (c == ';')
            debug = (debug == 0)? 1 : 0;
        printf("%c", c);
        if (c == '0') {
          return 1;}
        if (c == '1') {
            c = getch();
            if (c == '0') {
                printf("%c", c);
                c = 10;}
            else c = 0;
        }
    }
    r = ((c>'1'&&c<= '9')||c == 10)?
    (c == 10)?c-2:c-'0'-2:(c == 'j')?9:
    (c == 'q')?10:(c == 'k')?11:12;
    c = 0;
    while(c != 'h'&&c != 'c'&&c != 'd'&&c != 's') {
        gotoxy(1, 18);
        printf("Enter a suit (C, D, S, H): ");
        c = getch();
        printf("%c", c);
    }
    s = (c == 'c')? 0 : (c == 'd')? 1 : (c == 's')? 2 : 3;
    for(i = 0;i<13;i++) {
        if (p[i] == r+13*s) {
            gotoxy(1, 19);
            printf("Play the ");
            out('c', r+13*s, "", 0);
            printf(" (y/n)? ");  // seg fault
            c = 0;
            while(c != 'y'&&c != 'n') {
        c = getch();}
            break;
    }
  }
  if (c == 'y'&&(validtrick(p, r+13*s, start, rnd))) {
        out('p', r+13*s, "", 0);
        trick[P] = r+13*s;
        if (start)
            tsuit = s;
    p[i] = -1;
        if (!start&&suit != s) {
            strat[P*4+suit]++;
        }
        clrin();  // debug
        return P;}
    clrin();
    return -1;
}
void sort(int *p) {
  int i, t = 0, s;
  while (t == 0) {
    t = 1;
    for(i = 0; i < 12; i++) {
      if (p[i + 1] < p[i]) {
        t = 0;
        s = p[i];
        p[i] = p[i + 1];
        p[i + 1] = s;
      }
    }
  }
}

void phud(int *p) {
  if (!debug) {
    int c = 0, i, x, t = 0;
    if (debug)
      gotoxy(1, 18);  // gotoxy(1, 15); <-- default
    else
      gotoxy(1, 15);
    for(i = 0; i < 50; i++)
      printf(" ");
    if (debug)
      gotoxy(1, 18);  // gotoxy(1, 15); <-- default
    else
      gotoxy(1, 15);
    sort(p);
    for(i = 0; i < 13; i++) {
      if (p[i] != -1) {
        c++;
        if (p[i] % 13 == 8)
          t++;
      }
    }
    if (debug)
      gotoxy(30 - c * 2 - t, 14);
    else
      gotoxy(30 - c * 2 - t, 15);
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
    gotoxy(17, 11);printf("    ");
    if (name != "") {
      gotoxy(20 + ceil((-5 * n + 5) / 9), 10);
      printf("%s", name);
    }
    gotoxy(20, 11);
  } else if (pos == 'n') {
    gotoxy(17, 3);printf("    ");
    if (name != "") {
      gotoxy(20 + ceil((-5 * n + 5) / 9), 2);
      printf("%s", name);
    }
    gotoxy(20, 3);
  } else if (pos == 'e') {
    gotoxy(24, 7);printf("    ");
    if (name != "") {
      gotoxy(27 + ceil((-5 * n + 5) / 9), 6);
      printf("%s", name);
    }
    gotoxy(27, 7);
  } else if (pos == 'w') {
    gotoxy(10, 7);printf("    ");
    if (name != "") {
      gotoxy(13 + ceil((-5 * n + 5) / 9), 6);
      printf("%s", name);
    }
    gotoxy(13, 7);
  }
  if (card % 13 < 8) {
    printf("%c", card % 13 + '2');
  } else {
    if (card % 13 == 8 && card != NAME)
      printf("10");
    if (card % 13 == 9 && card != NAME)
      printf("J");
    if (card % 13 == 10 && card != NAME)
      printf("Q");
    if (card % 13 == 11 && card != NAME)
      printf("K");
    if (card % 13 == 12 && card != NAME)
      printf("A");
  }
  if (colourblind) {
    if (card / 13 == 0)
     printf( "♣");
    if (card / 13 == 1)
     printf("♦");
    if (card / 13 == 2)
     printf("♠");
    if (card / 13 == 3)
     printf("♥");
  }
  else{
    printf(YLW);
    if (card / 13 == 0)
      printf( "C");
    if (card / 13 == 2)
      printf("S");
    printf(RED);
    if (card / 13 == 1)
      printf("D");
    if (card / 13 == 3)
      printf("H");
    printf(RST);
  }
}

int start(int *n, int *e, int *p, int *w) {
  int i, who;
  for (i = 0; i < 13; i++) {
    if (p[i] == C2) {
      out('p', C2, "", 0);
      p[i] = -1;
      who = P;
      break;
    } else if (n[i] == C2) {
      out('n', C2, "", 0);
      n[i] = -1;
      who = N;
      break;
    } else if (e[i] == C2) {
      out('e', C2, "", 0);
      e[i] = -1;
      who = E;
      break;
    } else if (w[i] == C2) {
      out('w', C2, "", 0);
      w[i] = -1;
      who = W;
      break;
    }
  }
  return who;
}
void init(int *n, int *e, int *p, int *w, int *deck, int *strat) {
  int i;
  for(i = 0; i <= TOT;i++)
    n[i] = e[i] = p[i] = w[0] = 0;
  shuf(deck);
  for(i = 0; i < 16; i++)
    strat[i] = 0;
  for(i = 0; i < 13; i++)
    p[i] = draw(deck);
  for(i = 0; i < 13; i++)
    n[i] = draw(deck);
  for(i = 0; i < 13; i++)
    e[i] = draw(deck);
  for(i = 0; i < 13; i++)
    w[i] = draw(deck);
}

void shuf(int *deck) {
  int i, j, k;
  for (i = 0; i < 52; i++)
    deck[i] = i;
  if ((unsigned)time(NULL) != seed) {
    srand((unsigned)time(NULL));
    seed = ((unsigned)time(NULL));}
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
