void maxCardPass(int *p, int *pp) {
  int max = 0, imax = -1, i, j;
  //int pass[3];

  Table t;
  t.sort(p);
  for (j = 0; j < 3; j++) {
    for (i = 12; i >= 0; i--) {
      if (p[i] % 13 > max) {
        max = p[i] % 13;
        imax = i;
      }
    }
    pp[j] = p[imax];
    //pass[j] = p[imax];
    p[imax] = -1;
    imax = -1;
    max = 0;
  }
  /*for (i = 0; i < 3; i++) {
    pp[i] = pass[i];
  }*/
  t.sort(p);
  return;
}

int onlypts(int *h) {
  int i;
  for (i = 0; i < 13; i++) {
    if (h[i] != -1 && h[i] != SQ && h[i] < H2) {
      return 0;
    }
  }
  return 1;
}

int playmaxavg(Table *table, int nosuits) {
  //int istrat = (who == 'n') ? N : (who == 'e') ? E : (who == 'p') ? P : W;
  float nh, ns, nc, nd, sh, ss, sc, sd, ah, ac, as, ad;
  int u, i, qs = -1;
  int *p;
  p = table->players[table->currentPlayer()].cards;
  nh = ns = nc = nd = sh = ss = sc = sd = ah = ac = as = ad = 0;
  if (debug) {
    gotoxy(38, 6);printf("avg");
    if (!quickdebug) {
      u = getch();
      debug = (u == ';') ? (debug == 1)? 0 : 1 : debug;
    }
  }
  for (i = 0; i < 13; i++) {
    if (p[i] == SQ) {
      qs = i;
      break;
    }
  }
  for (i = 0; i < 13; i++) {
    if (p[i] != -1 && p[i] / 13 == CLB) {
      nc++;
      sc += p[i] % 13 + 2;
    }
    if (p[i] != -1 && p[i] / 13 == DIM) {
      nd++;
      sd += p[i] % 13 + 2;
    }
    if (p[i] != -1 && p[i] / 13 == SPD) {
      ns++;
      ss += p[i] % 13 + 2;
    }
    if (p[i] != -1 && p[i] / 13 == HRT) {
      nh++;
      sh += p[i] % 13 + 2;
    }
  }
  if (debug) {
    gotoxy(38, 12);printf("nc %1.0f, sc %1.0f", nc, sc);
    gotoxy(38, 13);printf("nd %1.0f, sd %1.0f", nd, sd);
    gotoxy(38, 14);printf("ns %1.0f, ss %1.0f", ns, ss);
    gotoxy(38, 15);printf("nh %1.0f, sh %1.0f", nh, sh);
    gotoxy(38, 13);
    if (!quickdebug) {
      u = getch();
      debug = (u == ';') ? (debug == 1) ? 0 : 1 : debug;
    }
    gotoxy(38, 12);(nh != 0)?printf("ah %3.2f        ", sh/nh):printf("ah 0");
    gotoxy(38, 13);(nc != 0)?printf("ac %3.2f        ", sc/nc):printf("ac 0");
    gotoxy(38, 14);(ns != 0)?printf("as %3.2f        ", ss/ns):printf("as 0");
    gotoxy(38, 13);(nd != 0)?printf("ad %3.2f       ", sd/nd):printf("nd 0");
    if (!quickdebug) {
      u = getch();
      debug = (u == ';') ? (debug == 1)? 0 : 1 : debug;
    }
  }
  if (table->start()) {
    if (nc < 3 && sc < 10 && nc != 0 && suitsleft(table, CLB)) {
      ac = 50;
    } else {
      ac = nc;
    }
    if (nd < 3 && sd < 10 && nd != 0 && suitsleft(table, DIM)) {
      ad = 50;
    } else {
      ad = nd;
    }
    if (ns < 3 && ss < 10 && ns != 0 && suitsleft(table, SPD)) {
      as = 50;
    } else {
      as = ns;
    }
    if (nh < 3 && sh < 10 && nh != 0 && suitsleft(table, HRT)) {
      ah = 50;
    } else {
      ah = nh;
    }
  } else {
    if (nc != 0) {
      ac = sc / nc;
    }
    if (nd != 0) {
      ad = sd / nd;
    }
    if (ns != 0) {
      as = ss / ns;
    }
    if (nh != 0) {
      ah = sh / nh;
    }
  }
  if (table->trickSuit() == 4 ||
  (table->roundScore() == 0 && table->start() == 1 && !onlypts(p))) {
    ah = 0;
  }
  if (debug) {
    gotoxy(38, 12);printf("ah %3.2f        ", ah);
    gotoxy(38, 13);printf("ac %3.2f        ", ac);
    gotoxy(38, 14);printf("as %3.2f        ", as);
    gotoxy(38, 15);printf("ad %3.2f       ", ad);
    if (!quickdebug) {
      u = getch();
      debug = (u == ';') ? (debug == 1) ? 0 : 1 : debug;
    }
  }
  if (qs != -1 && table->start() == 0 && table->trickSuit() != 4) {
    //out(who, SQ, "", 0);
    table->playCard(qs);
    return 1;
  }
  // TODO unroll with loop
  if (ac >= as && ac >= ad && ac >= ah &&
  (suitsleft(table, CLB) || nosuits)) {
    if (start == 0) {
      playmax(table, N_CARDS, CLB);
    } else {
      playmin(table, N_CARDS, CLB);
    }
    return 1;
  }
  if (ad >= as && ad >= ah && ad >= ac &&
  (suitsleft(table, DIM) || nosuits)) {
    if (start == 0) {
      playmax(table, N_CARDS, DIM);
    } else {
      playmin(table, N_CARDS, DIM);
    }
    return 1;
  }
  if (as >= ad && as >= ah && as >= ac &&
  // if (max(3, as, ac, ad) == as &&
  (suitsleft(table, SPD) || nosuits)) {
    if (start == 0) {
      playmax(table, N_CARDS, SPD);
    } else {
      playmin(table, N_CARDS, SPD);
    }
    return 1;
  }
  if (ah >= ad && ah >= as && ah >= ac &&
  (suitsleft(table, HRT) || nosuits)) {
    if (start == 0) {
      playmax(table, N_CARDS, HRT);
    } else {
      playmin(table, N_CARDS, HRT);
    }
    return 1;
  }
  playmaxavg(table, 1);
  return 1;
}

int ptsintrick(int *t) {
  int i;
  for (i = 0; i < 4; i++) {
    if (t[i] == SQ || t[i] >= H2)
    return 1;
  }
  return 0;
}

int playmax(Table *table, int tmax, int suit) {
  int i, max, imax, queen, qs;
  int *p;
  max = -1;
  imax = -1;
  queen = 0;
  qs = -1;
  p = table->players[table->currentPlayer()].cards;
  for (i = 0; i < 13; i++) {
    if (p[i] != -1 && p[i] / 13 == suit && p[i] > max && p[i] < tmax) {
      max = p[i];
      imax = i;
    }
    if (p[i] == SQ) {
      qs = i;
    }
  }
  if (imax != -1) {
    if (p[imax] == SQ && playmax(table, SQ, suit)) {
      return 1;  // can play under SQ
    }
    for (i = 0; i < 4; i++) {
      if (table->trick[i] == SK || table->trick[i] == SA) {
        queen = 1;
      }
    }
    if (qs != -1 && suit == SPD && queen == 1) {
      table->playCard(qs);
      return 1;
    }
    table->playCard(imax);
    return 1;
  } else {
    return 0;
  }
}

int playmin(Table *table, int max, int suit) {
  int i, imin, min, u;
  int *p;
  min = 52;
  imin = -1;
  p = table->players[table->currentPlayer()].cards;

  for (i = 0; i < 13; i++) {
    if (p[i] != -1 && p[i] / 13 == suit && p[i] < min && p[i] < max) {
      if (validtrick(table, p[i])) {
        min = p[i];
        imin = i;
      }
    }
  }
  if (imin != -1) {
    if (p[imin] == SQ && playmax(table, N_CARDS, suit)) {
      return 1;  // can play higher than SQ
    }
    table->playCard(imin);
    return 1;
  }
  return 0;
}

int nosuitsnext(Table *table) {
  int next, suit, i;
  next = (table->currentPlayer() + 1) % PLAYERS;
  suit = table->trickSuit();

  for (i = 0; i < 3; i++) {
    if (table->trick[next] == -1 && table->strat[4 * next + suit] == 0) {
      return 0;
    }
    next = (next + 1) % PLAYERS;
  }
  return 1;
}

int hasQueen(int *cards) {
  int i;
  for (i = 0; i < N_HAND; i++) {
    if (cards[i] == SQ) {
      return 1;
    }
  }
  return 0;
}

int pointscannotbetaken(Table *table) {
  cdb("queen");
  int i, q = 1;
  if (ptsintrick(table->trick)) {
    return 0;
  }
  if (table->trickSuit() != SPD) {
    return 1;
  } else {
    for (i = 0; i < PLAYERS; i++) {
      if (table->trick[i] == -1 && hasQueen(table->players[i].cards)) {
        return 0;
      }
    }
    cdb("\\queen");
  }
  return 1;
}

int compturn(Table *table) {
  int i, j, s, low, u, qs, suit;
  int *p;
  p = table->players[table->currentPlayer()].cards;
  suit = table->trickSuit() % 4;
  s = 0;
  qs = 0;
  if (start == 0) {  // not starting
    for (i = 0; i < N_HAND; i++) {
      if (p[i] != -1 && p[i] / 13 == suit) {
        s++;
      }
    }
    if (s > 0) {  // has same suit
      if (s == 1) {  // last card of that suit
        playmin(table, N_CARDS, suit);
        return table->currentPlayer();
      } else {  // has more than one
        if (table->trickCount() == 3 || nosuitsnext(table)) {
        // last to play
          if (ptsintrick(table->trick)) {
            if (playmax(table, table->trickmax(suit), suit)) {
              // can play under
              return table->currentPlayer();
            } else {  // cant play under
              playmax(table, N_CARDS, suit);
              return table->currentPlayer();
            }
          } else {  // no pts in trick
            playmax(table, N_CARDS, suit);
            return table->currentPlayer();
          }
        } else {  // not last to play
          if (table->trickSuit() == 4) {
            if (playmax(table, N_CARDS, suit)) {
              return table->currentPlayer();
            }
          }
          if (playmax(table, table->trickmax(suit), suit)) {
            return table->currentPlayer();
          } else {  // cant play under
            if (table->trickCount() == 2 && pointscannotbetaken(table)) {
              playmax(table, N_CARDS, suit);
            } else {
              playmin(table, N_CARDS, suit);
            }
            return table->currentPlayer();
          }
        }
      }
    } else {  // doesnt have same suit
      table->strat[table->currentPlayer() * 4 + suit]++;
      playmaxavg(table, NO_SUITS);
      return table->currentPlayer();
    }
  } else {  // starting
    playmaxavg(table, HAS_SUITS);
    return table->currentPlayer();
  }
}

