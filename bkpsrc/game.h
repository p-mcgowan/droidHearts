void give(int *rx, int *tx) {
  int i;
  sort(rx);
  for (i = 0;i<3;i++) {
    rx[i] = tx[i];
  }
}

void ppass(int *p, int *pp, int w) {
  char c;
  int r, s, i, pi;
  int pass[4] = {-1, -1, -1, 0};
  while(pass[0] == -1 || pass[1] == -1 || pass[2] == -1) {
    while(!(c > '1' && c <= '9') && c != 'j' && c != 'q' && c != 'k' && c != 'a'
    && c != 10) {
      clrin();
      phud(p);
      gotoxy(1, 17);
      printf("Enter cards to pass ");
      (w == LEFT) ? printf("left") : (w == RIGHT) ?
      printf("right") : printf("across");
      printf(", 0 to reset:");
      gotoxy(1, 18);
      printf("Enter a rank (2-10, J-A): ");
      c = getch();
      printf("%c", c);
      if (c == '1') {
        c = getch();
        if (c == '0') {
          printf("%c", c);
          c = 10;
        } else {
          c = 0;
        }
      }
      if (c == '0') {
        for (i = 0;i<3;i++) {
        if (pass[i] != -1) {
          p[i] = pass[i];
        }
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
    for (i = 0;i<13;i++) {
      if (p[i] == r+13*s) {
        gotoxy(1, 20);
        printf("Pass the ");
        out('c', r+13*s, "", 0);
        printf(" (y/n)? ");
        while(c != 'y'&&c != 'n') {
          c = getch();
        }
        pi = i;
        break;
      }
    }
    if (c == 'y') {
      pass[3]++;
      for (i = 0;i<4;i++) {
        if (pass[i] == -1) {
          pass[i] = r+13*s;
          p[pi] = -1;
          break;
        }
      }
    }
    gotoxy(1, 16);printf("               ");
    for (i = 0;i<3;i++) {
      if (pass[i] != -1) {
        gotoxy(1+4*i, 16);
        out('t', pass[i], "", 0);
      }
    }
    if (pass[3] == 3) {
      clrin();
      phud(p);
      gotoxy(1, 16);printf("               ");
      for (i = 0;i<3;i++) {
        if (pass[i] != -1) {
          gotoxy(1+4*i, 16);
          out('t', pass[i], "", 0);
        }
      }
      c = 0;
      gotoxy(1, 18);printf("Pass these cards (y/n)? ");
      while(c != 'y'&&c != 'n') {
      c = getch();}
      if (c == 'y') {
        break;
      } else {
        for (i = 0;i<3;i++) {
        p[i] = pass[i];
        pass[i] = -1;}
        pass[3] = 0;
        gotoxy(1, 16);printf("               ");
      }
    }
  }
  for (i = 0;i<3;i++) {
  pp[i] = pass[i];}
  return;
}

void passcards(int *n, int *e, int *p, int *w, int pass) {
  int i, np[3], ep[3], pp[3], wp[3], max;
  if (pass == HOLD) {
    return;
  }
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
  for (i = 0; i < 3; i++) {
    gotoxy(1 + 4 * i, 18);
    out('t', p[i], "", 0);
  }
  phud(p);
  gotoxy(1, 1);
  i = getch();
  clrin();
  return;
}

int won(int *n, int *e, int *p, int *w) {
  if (n[TOT] > 99 || e[TOT] > 99 || p[TOT] > 99 || w[TOT] > 99) {
    return 1;
  }
  return 0;
}

int score(int *n, int *e, int *p, int *w, int *trick, int print) {
  int i, pts = 0, max = -1, winner, s = (tsuit == 4) ? 0 : tsuit;
  for (i = 0; i < 4; i++) {
    if (trick[i] >= H2) {
      pts++;
    }
    if (trick[i] == SQ) {
      pts += 13;
    }
    if (trick[i] / 13 == s && trick[i] % 13 > max) {
      winner = i;
      max = trick[i] % 13;
    }
  }
  if (winner == N && !print) {
    n[RND] += pts;
  }
  if (winner == E && !print) {
    e[RND] += pts;
  }
  if (winner == P && !print) {
    p[RND] += pts;
  }
  if (winner == W && !print) {
    w[RND] += pts;
  }
  if (!print) {
    n[SCR] += n[RND];
    e[SCR] += e[RND];
    p[SCR] += p[RND];
    w[SCR] += w[RND];
  }
  if (!debug) {
    i = (print == 0)? 9 : 0;
    gotoxy(1, 10+i);printf("Name\t\tRound\tTotal\tOverall");i++;
    gotoxy(1, 10+i);printf("North\t\t%i\t%i\t%i", n[RND], n[SCR], n[TOT]);i++;
    gotoxy(1, 10+i);printf("East\t\t%i\t%i\t%i", e[RND], e[SCR], e[TOT]);i++;
    gotoxy(1, 10+i);printf("Player\t\t%i\t%i\t%i", p[RND], p[SCR], p[TOT]);i++;
    gotoxy(1, 10+i);printf("West\t\t%i\t%i\t%i", w[RND], w[SCR], w[TOT]);i++;
  }
  gotoxy(1, 11 + i); printf("Press any key to continue...");
  return (winner == N) ? W : winner - 1;
}

void names(char *n, char *e , char* p, char *w, int name) {
  char buff[128]; int i, j, dum;
  if (name == 1) {
    printf("Change names (y/n)? >");
    i = getch();
    if (i == 'y') {
      for (i = 0; i < 11; i++) {
        n[i] = 0;
        buff[i] = 0;
      }
      clrscr();printf("Name North:\n> ");
      scanf("%s", buff);
      i = getch();
      for (i = 0; i < 10; i++) {
        n[i] = buff[i];
        if (buff[i + 1] == 0 || i == 9) {
          n[11] = i + 1;
          break;
        }
      }
      for (i = 0;i < 11; i++) {
        e[i] = 0;
        buff[i] = 0;
      }
      clrscr();
      printf("Name East:\n> ");
      scanf("%s", buff);
      i = getch();
      for (i = 0; i < 10; i++) {
        e[i] = buff[i];
        if (buff[i + 1] == 0 || i == 9) {
          e[11] = i + 1;
          break;
        }
      }
      for (i = 0; i < 11; i++) {
        p[i] = 0;
        buff[i] = 0;
      }
      clrscr();
      printf("Name Player:\n> ");
      scanf("%s", buff);
      i = getch();
      for (i = 0;i<10;i++) {
        p[i] = buff[i];
        if (buff[i + 1] == 0 || i == 9) {
          p[11] = i + 1;
          break;
        }
      }
      for (i = 0; i < 11; i++) {
        w[i] = 0;
        buff[i] = 0;
      }
      clrscr();
      printf("Name West:\n> ");
      scanf("%s", buff);
      i = getch();
      for (i = 0; i < 10; i++) {
        w[i] = buff[i];
        if (buff[i + 1] == 0 || i == 9) {
          w[11] = i + 1;
          break;
        }
      }
    } else {
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

int getchoice(int *p, int start, int rnd, int *trick, int *strat) {
  int i, r, s, suit = (tsuit == 4) ? 0 : tsuit;
  char c = 0;
  while(!(c >= '0' && c <= '9') && c != 'j' && c != 'q' && c != 'k' && c != 'a' && c != 10) {
    if (!debug)
    clrin();
    gotoxy(1, 17);
    printf("Enter a rank (2-10, J-A) or 0 for options: ");
    c = getch();
    if (c == ';') {
      debug = (debug == 0) ? 1 : 0;
    }
    printf("%c", c);
    if (c == '0') {
      return 1;
    }
    if (c == '1') {
      c = getch();
      if (c == '0') {
        printf("%c", c);
        c = 10;
      } else {
        c = 0;
      }
    }
  }
  r = ((c > '1' && c <= '9') || c == 10) ?
  (c == 10) ? c - 2 : c - '0' - 2 : (c == 'j') ? 9 :
  (c == 'q') ? 10 : (c == 'k') ? 11 : 12;
  c = 0;
  while(c != 'h' && c != 'c' && c != 'd' && c != 's') {
    gotoxy(1, 18);
    printf("Enter a suit (C, D, S, H): ");
    c = getch();
    printf("%c", c);
  }
  s = (c == 'c') ? 0 : (c == 'd') ? 1 : (c == 's') ? 2 : 3;
  for (i = 0; i < 13; i++) {
    if (p[i] == r + 13 * s) {
      gotoxy(1, 19);
      printf("Play the ");
      out('c', r+13*s, "", 0);
      printf(" (y/n)? ");
      // TODO need?
      c = 0;
      while(c != 'y' && c != 'n') {
        c = getch();
      }
      break;
    }
  }
  if (c == 'y'&&(validtrick(p, r+13*s, start, rnd))) {
    out('p', r+13*s, "", 0);
    trick[P] = r+13*s;
    if (start) {
      tsuit = s;
    }
    p[i] = -1;
    if (!start&&suit != s) {
      strat[P*4+suit]++;
    }
    clrin();  // debug
    return P;
  }
  clrin();
  return -1;
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
  for (i = 0; i < TOT; i++) {
    n[i] = e[i] = p[i] = w[i] = 0;
  }
  shuf(deck);
  for (i = 0; i < 16; i++) {
    strat[i] = 0;
  }
  for (i = 0; i < 13; i++) {
    p[i] = draw(deck);
  }
  for (i = 0; i < 13; i++) {
    n[i] = draw(deck);
  }
  for (i = 0; i < 13; i++) {
    e[i] = draw(deck);
  }
  for (i = 0; i < 13; i++) {
    w[i] = draw(deck);
  }
}

int loadgame(int *n, int *e, int *p, int *w, int *strat, int *trick, int *rnd, char *nname, char *ename, char *pname, char *wname, int *deck, int *pass) {
  FILE *fp, *fp2;
  int i = 0;
  char fname[128], in[128];
  in[0] = -1;
  while(!(in[0] >= '0' && in[0] <= '2')) {
    clrscr();
    printf("Saves:\n\n");
    fp = fopen("saves", "r");
    if (!fp) {
      fp = fopen("saves", "w");
      if (!fp) {
        printf("Error writing save file...\nPress any key to continue: ");
        in[0] = getch();
        return -1;
      }
      fclose(fp);
      fp = fopen("saves", "r");
      if (!fp) {
        printf("Error writing save file...\nPress any key to continue: ");
        in[0] = getch();
        return -1;
      }

    }

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
  if (in[0] == '0') {
    return 0;
  }
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
    } else {
      in[0] = getch();  // cleans input stream
      for (i = 0; i < 16; i++) {
        fscanf(fp, "%d", &n[i]);
      }
      for (i = 0; i < 16; i++) {
        fscanf(fp, "%d", &e[i]);
      }
      for (i = 0; i < 16; i++) {
        fscanf(fp, "%d", &p[i]);
      }
      for (i = 0; i < 16; i++) {
        fscanf(fp, "%d", &w[i]);
      }
      for (i = 0; i < 5; i++) {
        fscanf(fp, "%d", &trick[i]);
      }
      for (i = 0; i < 52; i++) {
        fscanf(fp, "%d", &deck[i]);
      }
      for (i = 0; i < 16; i++) {
        fscanf(fp, "%d", &strat[i]);
      }
      fgetc(fp);  // clear formatting space between strat5 and nname
      for (i = 0;i < 12; i++) {
        nname[i] = fgetc(fp);
      }
      for (i = 0;i < 12; i++) {
        ename[i] = fgetc(fp);
      }
      for (i = 0;i < 12; i++) {
        pname[i] = fgetc(fp);
      }
      for (i = 0;i < 12; i++) {
        wname[i] = fgetc(fp);
      }
      *rnd = fgetc(fp);
      *pass = fgetc(fp);
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
  } else if (in[0] == '2') {
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

// TODO
int save(int *n, int *e, int *p, int *w, int *strat, int *trick, int rnd, char *nname, char *ename, char *pname, char *wname, int *deck, int pass) {
  FILE *fp, *fp2;
  int i = -1;
  char fname[128], in[128];
  in[0] = -1;
  clrscr();
  printf("Saves:\n\n");
  fp = fopen("saves", "r");
  if (!fp) {
    fp = fopen("saves", "w");
    if (!fp) {
      printf("Error writing save file...\nPress any key to continue: ");
      in[0] = getch();
      return -1;
    }
    fclose(fp);
    fp = fopen("saves", "r");
    if (!fp) {
      printf("Error writing save file...\nPress any key to continue: ");
      in[0] = getch();
      return -1;
    }
  }

  fseek(fp, 0, SEEK_END);
  if (ftell(fp) == 0) {
    printf("No saves.\n");
  } else {
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
  while (in[0] != 'n' && in[0] != 'y') {
    gotoxy(1, 6); printf("> ");
    in[0] = getch();
  }
  if (in[0] == 'n') {
    return 1;
  }
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
        if (strstr(in, fname) == NULL) {
          fputs(in, fp2);
        }
      }
      fclose(fp);
      fclose(fp2);
      unlink("tmp");
    } else {
      fclose(fp);
      return 1;
    }
  }

  fp = fopen(fname, "w");  // write save
  for (i = 0; i < 16; i++) {
    fprintf(fp, "%d ", n[i]);  // fputc(n[i], fp);
  }
  for (i = 0; i < 16; i++) {
    fprintf(fp, "%d ", e[i]);  // fputc(e[i], fp);
  }
  for (i = 0; i < 16; i++) {
    fprintf(fp, "%d ", p[i]);  // fputc(p[i], fp);
  }
  for (i = 0; i < 16; i++) {
    fprintf(fp, "%d ", w[i]);  // fputc(w[i], fp);
  }
  for (i = 0; i < 5; i++) {
    fprintf(fp, "%d ", trick[i]);  // fputc(trick[i], fp);
  }
  for (i = 0; i < 52; i++) {
    fprintf(fp, "%d ", deck[i]);  // fputc(deck[i], fp);
  }
  for (i = 0; i < 16; i++) {
    fprintf(fp, "%d ", strat[i]);  // fputc(strat[i], fp);
  }
  for (i = 0; i < 12; i++) {
    fputc(nname[i], fp);
  }
  for (i = 0; i < 12; i++) {
    fputc(ename[i], fp);
  }
  for (i = 0; i < 12; i++) {
    fputc(pname[i], fp);
  }
  for (i = 0; i < 12; i++) {
    fputc(wname[i], fp);
  }
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

int gameOptions(int *n, int *e, int *p, int *w, int *strat, int *trick, int rnd, char *nname, char *ename, char *pname, char *wname, int *deck, int pass) {
  int input = -1;
  while (input == -1) {
    clrscr();
    printf("1: Save/quit\n2: Options\n0: Back to game\n> ");
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

int game(int *n, int *e, int *p, int *w, int *strat, int *trick, int *rnd, char *nname, char *ename, char *pname, char *wname, int *deck, int *pass, int newgame) {
  int nd = 0, ed = 0, pd = 0, wd = 0, name = 1;
  int i, j, rounds;  // , pass = 3;  // pass = 0;
  ndb = n;edb = e;pdb = p;wdb = w;
  int s = 0, t; char test, u = 0;
  int gChoice = -1;  // get choice - for save
  // gameOptions(n, e.p, w, strat, trick, rnd, nname, ename, pname, wname, deck, pass);
  for (;;) {
    while(newgame || !won(n, e, p, w)) {
      if (newgame) {
        names(nname, ename, pname, wname, name);
        name = 0;
        init(n, e, p, w, deck, strat);
        n[TOT] = e[TOT] = p[TOT] = w[TOT] = 0;
        if (debug) {
          hud(n, e, p, w);
          gotoxy(1, 1);
          u = getchar();  // debug = (u == ';')?(debug == 1)? 0 : 1:debug;  // getch?
        }
        passcards(n, e, p, w, *pass);
        lastplay = start(n, e, p, w);
        tsuit = 4;s = 0;
        t = 0;
        trick[lastplay] = C2;
        trick[4]++;
      }
      for (rounds = 0;rounds<51;rounds++) {
        gotoxy(1, 26);printf("--------------------------------------------------");
        for (i = 1; i <= 26; i++) {
          gotoxy(50, i);printf("%d",i);
        }
        sdb("   ");
        *pass = 3;
        if (debug) {
          sdb("D1 ");
          gotoxy(38, 1);printf("strt %i", s);
          ldb(trick[4]);
          gotoxy(38, 2);printf("suit %o", tsuit);
          gotoxy(38, 5);printf("rnd %i", rnd);
          gotoxy(38, 6);printf("    ");
          nd = ed = pd = wd = 0;
          for (i = 0;i<13;i++) {
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
          for (i = 0;i<16;i++) {
            if (i%4 == 0&&i != 0)
            printf(" ");
            printf("%i ", strat[i]);
          }
          tdb(trick);
          hud(n, e, p, w);
          sdb("D1\\");
          u = getch();
        }
        if (lastplay == E) {
          sdb("P1 ");
          phud(p);
          ldb(trick[4]);
          if (cplay) {
            lastplay = compturn(p, trick, *rnd, s, 'p', strat, n, e, w);
          } else {
            gChoice = -1;
            // gChoice = getchoice(p, s, rnd, trick, strat);
            while (gChoice == -1) {
              phud(p);
              if (debug) {
                hud(n, e, p, w);
              }
              gChoice = getchoice(p, s, *rnd, trick, strat);
              if (gChoice == 1) {
                gChoice = gameOptions(n, e, p, w, strat, trick, *rnd, nname, ename, pname, wname, deck, *pass);
              }
              if (gChoice == 0) {
                return 0;
              }
              printplayers(trick, nname, ename, pname, wname);
            }
            lastplay = P;
          }
          trick[4]++;
          sdb("P1\\");
        } else if (lastplay == P) {
          sdb("W1 ");
          if (debug) {
            ldb(trick[4]);
          }
          lastplay = compturn(w, trick, *rnd, s, 'w', strat, n, e, p);
          trick[4]++;
          ldb(trick[4]);
          sdb("W1\\");
        } else if (lastplay == W) {
          sdb("N1 ");
          if (debug) {
            ldb(trick[4]);
          }
          lastplay = compturn(n, trick, *rnd, s, 'n', strat, e, p, w);
          trick[4]++;
          ldb(trick[4]);
          sdb("N1\\");
        } else if (lastplay == N) {
          sdb("E1 ");
          if (debug) {
            ldb(trick[4]);
          }
          lastplay = compturn(e, trick, *rnd, s, 'e', strat, w, n, p);
          if (debug&&ldbtoggle) {
            gotoxy(38, 11);
            printf("lp %i", lastplay);
          }
          trick[4]++;
          ldb(trick[4]);
          sdb("E1\\");
        }
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
          for (i = 0;i<4;i++) {
            trick[i] = -1;
          }
          sdb("Tc ");
          trick[4] = 0;
          sdb("Td ");
          if (debug) {
            gotoxy(35, 1);
          } else {
            gotoxy(1, 1);
          }
          sdb("Te ");
          sdb("Tg ");
          // names(nname, ename, pname, wname, name);
          sdb("Th ");
          out('n', NAME, "", 0);
          out('e', NAME, "", 0);
          out('p', NAME, "", 0);
          out('w', NAME, "", 0);  // clr out
          sdb("T1\\");
        } else {
          sdb("T2 ");
          s = 0;
          // trick[4]++;  // for tdb - updates after lastplay does
          tdb(trick);
          ldb(trick[4]);
          sdb("T2\\");
        }
        *rnd = n[SCR]+e[SCR]+p[SCR]+w[SCR];
        n[RND] = e[RND] = p[RND] = w[RND] = 0;
        if (debug) {
          hud(n, e, p, w);
        }
        // u = getch();  // right place
      }  // round end
      newgame = 0;
      *pass = (*pass == 3) ? 0 : *pass + 1;
      if (n[SCR] == 26) {
        e[TOT] += 26;
        p[TOT] += 26;
        w[TOT] += 26;
      } else if (e[SCR] == 26) {
        n[TOT] += 26;
        p[TOT] += 26;
        w[TOT] += 26;
      } else if (p[SCR] == 26) {
        n[TOT] += 26;
        e[TOT] += 26;
        w[TOT] += 26;
      } else if (w[SCR] == 26) {
        n[TOT] += 26;
        e[TOT] += 26;
        p[TOT] += 26;
      } else {
        n[TOT] += n[SCR];
        e[TOT] += e[SCR];
        p[TOT] += p[SCR];
        w[TOT] += w[SCR];
      }
      n[SCR] = e[SCR] = w[SCR] = p[SCR] = 0;
      clrscr();
      score(n, e, p, w, trick, 1);
      getch();
      clrscr();
      hud(n, e, p, w);
      init(n, e, p, w, deck, strat);
      printplayers(trick, nname, ename, pname, wname);
      newgame = 1;
    }
  }
}

