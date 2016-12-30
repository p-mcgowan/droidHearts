void give(int *rx, int *tx) {
  Table t;
  int i;
  t.sort(rx);
  for (i = 0; i < 3; i++) {
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
        //printf("Pass the ");
        printf("Pass the %i", r+13*s);
        //out('c', r+13*s, "", 0);
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
        //out('t', pass[i], "", 0);
      }
    }
    if (pass[3] == 3) {
      clrin();
      phud(p);
      gotoxy(1, 16);printf("               ");
      for (i = 0;i<3;i++) {
        if (pass[i] != -1) {
          gotoxy(1+4*i, 16);
         // out('t', pass[i], "", 0);
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

void passcards(Table *table) {
  int i, np[3], ep[3], pp[3], wp[3], max;
  if (table->pass == HOLD) {
    return;
  }
  return;  // TODO remove - debug
  maxCardPass(table->players[N].cards, np);
  maxCardPass(table->players[E].cards, ep);
  maxCardPass(table->players[W].cards, wp);
  ppass(table->players[P].cards, pp, table->pass);
  gotoxy(1, 1);
  if (table->pass == LEFT) {
    give(table->players[N].cards, wp);
    give(table->players[E].cards, np);
    give(table->players[P].cards, ep);
    give(table->players[W].cards, pp);
  }
  if (table->pass == RIGHT) {
    give(table->players[N].cards, ep);
    give(table->players[E].cards, pp);;
    give(table->players[P].cards, wp);
    give(table->players[W].cards, np);
  }
  if (table->pass == ACROSS) {
    give(table->players[N].cards, pp);
    give(table->players[E].cards, wp);
    give(table->players[P].cards, np);
    give(table->players[W].cards, ep);
  }
  clrin();
  gotoxy(1, 16);printf("               ");
  gotoxy(1, 17);printf("Received: ");
  for (i = 0; i < 3; i++) {
    gotoxy(1 + 4 * i, 18);
   // out('t', table->players[P].cards[i], "", 0);
  }
  phud(table->players[P].cards);
  gotoxy(1, 1);
  i = getch();
  clrin();
  return;
}

int won(Table *table) {
  if (table->players[N].total > 99 || table->players[E].total > 99 ||
  table->players[P].total > 99 || table->players[W].total > 99) {
    return 1;
  }
  return 0;
}

int score(Table *table) {
  int i, pts, max, winner, s;
  pts = 0;
  max = -1;
  s = table->trick[TRICK_SUIT] % 4;
  for (i = 0; i < 4; i++) {
    if (table->trick[i] >= H2) {
      pts++;
    }
    if (table->trick[i] == SQ) {
      pts += 13;
    }
    if (table->trick[i] / 13 == s && table->trick[i] % 13 > max) {
      winner = i;
      max = table->trick[i] % 13;
    }
  }
  table->players[winner].trick += pts;
  table->players[winner].round += pts;
  table->players[winner].total += pts;
  return (winner == N) ? W : winner - 1;
}

void changeNames(Table *table) {
  int i, j, dum;
  char buf[1024];
  printf("Change names (y/n)? >");
  i = getch();
  if (i == 'y') {
    for (i = 0; i < PLAYERS; i++) {
      clrscr();
      printf("Name ");
      switch (i) {
        case 0:
          printf("North");
          break;
        case 1:
          printf("East");
          break;
        case 2:
          printf("Player");
          break;
        case 3:
          printf("West");
          break;
      }
      printf(":\n> ");
      scanf("%s", buf);
      sprintf(table->players[i].name, "%10s", buf);
    }
  } else {
    sprintf(table->players[N].name, "North");
    sprintf(table->players[E].name, "East");
    sprintf(table->players[P].name, "Player");
    sprintf(table->players[W].name, "West");
  }
}

int getchoice(Table *table) {
  int i, r, s, suit;
  suit = table->trick[TRICK_SUIT] % 4;
  char c = 0;
  while(!(c >= '0' && c <= '9') && c != 'j' && c != 'q' && c != 'k' && c != 'a' && c != 10) {
    table->window.clearCell(CELL_OUTPUT);
    gotoxyc(table->window.cellAnchor(CELL_OUTPUT).add(1, 1));
    printf("Enter a card (eg 10S) or 0 for options: ");
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
    //gotoxyc(table->cellAnchor(CELL_OUTPUT).add(1, 2));
    //printf("Enter a suit (C, D, S, H): ");
    c = getch();
    printf("%c", c);
  }
  s = (c == 'c') ? 0 : (c == 'd') ? 1 : (c == 's') ? 2 : 3;
  for (i = 0; i < 13; i++) {
    if (table->players[P].cards[i] == r + 13 * s) {
      // TODO need confirmation stage?
      gotoxyc(table->window.cellAnchor(CELL_OUTPUT).add(1, 2));
      printf("Play the ");
      printCard(r + 13 * s);
     // out('c', r + 13 * s, "", 0);
      printf(" (y/n)? ");
      c = 0;
      while(c != 'y' && c != 'n') {
        c = getch();
      }
      break;
    }
  }
  if (c == 'y' && validtrick(table, r + 13 * s)) {
   // out('p', r + 13 * s, "", 0);
    table->playCard(i);
    if (!start && suit != s) {
      table->strat[P * STRAT_NO_SUIT + suit]++;
    }
    return P;
  }
  return -1;
}

int start(Table *table) {
  int i;
  for (i = N; i <= W; i++) {
    table->sort(table->players[i].cards);
  }
  for (i = N; i <= W; i++) {
    gotoxy(1, 60);handDebug(table, i);getch();
    if (table->players[i].cards[0] == C2) {
      table->lastplay = (i + 3) % 4;
      table->playCard(0);
      return i;
    }
  }
  printf("NO START"); getch();
  return -1;
}

int loadgame(Table *table) {
  return 0;  // TODO
  FILE *fp, *fp2;
  int i, j;
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
      for (j = N; j <= W; j++) {
        for (i = 0; i < N_HAND; i++) {
          fscanf(fp, "%d", &table->players[j].cards[i]);
        }
      }
      for (i = 0; i < N_TRICK; i++) {
        fscanf(fp, "%d", &table->trick[i]);
      }
      for (i = 0; i < N_CARDS; i++) {
        fscanf(fp, "%d", &table->deck.cards[i]);
      }
      for (i = 0; i < N_STRAT; i++) {
        fscanf(fp, "%d", &table->strat[i]);
      }
      fgetc(fp);  // clear formatting space between strat5 and nname
      /*for (i = 0;i < 12; i++) {
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
      table->lastplay = fgetc(fp);
      debug = fgetc(fp);
      quickdebug = fgetc(fp);
      cplay = fgetc(fp);
      qdbtoggle = fgetc(fp);
      sdbtoggle = fgetc(fp);
      cdbtoggle = fgetc(fp);
      ldbtoggle = fgetc(fp);
      tdbtoggle = fgetc(fp);
      */
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
int save(Table *table) {
  return 0;
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
  /*for (i = 0; i < 16; i++) {
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
  fputc(tdbtoggle, fp);*/
  fclose(fp);
  fp = fopen("saves", "a");
  fputs(fname, fp);
  fputs("\n", fp);
  fclose(fp);
  printf("%s saved sucessfully.\nPress any key to continue...", fname);
  in[0] = getch();
  return 1;
}

int gameOptions(Table *table) {
  int input = -1;
  while (input == -1) {
    clrscr();
    printf("1: Save/quit\n2: Options\n0: Back to game\n> ");
    input = getch() - '0';
    switch (input) {
      case 1:
        save(table);
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

int game(Table *table, int newgame) {
  int i, j, rounds;
  int gChoice;
  int dummy = 0;

  while (!won(table)) {
    table->initialize(newgame);
    if (newgame) {
      table->round = 0;
      changeNames(table);
      table->redraw();
      gotoxyc(table->window.cellAnchor(CELL_OUTPUT));
      printf("%d", dummy++);getch();
      start(table);
      table->trick[TRICK_SUIT] = 4;
      newgame = 0;
    }
    passcards(table);
    for (; table->round < N_CARDS; (table->round)++) {
      table->redraw();
      handDebug(table);
      gotoxyc(table->window.cellAnchor(CELL_OUTPUT));
      printf("%d", dummy++);getch();
      if (table->lastplay == E) {
        if (cplay) {
          compturn(table);
        } else {
          gChoice = -1;
          while (gChoice == -1) {
            gChoice = getchoice(table);
            if (gChoice == 1) {
              gChoice = gameOptions(table);
            }
            if (gChoice == 0) {
              return 0;
            }
          }
        }
        table->drawPlayerHand();
      } else {
        printf("'%d-%d-%d'", table->lastplay, compturn(table), table->lastplay);
        getch();
      }
      if (table->trickCount() == 4) {
        table->lastplay = score(table);
        printf("%d", dummy++);getch();
        for (i = 0; i < PLAYERS; i++) {
          table->trick[i] = -1;
        }
        table->redraw();
      }
    }  // deck expired (round == 51)
    //table->pass = (table->pass + 1) % 4;
    score(table);
  }
}

