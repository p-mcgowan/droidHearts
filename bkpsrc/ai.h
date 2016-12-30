void cmax(int *p, int *pp) {
  int max = 0, imax = -1, i, j;
  int pass[3];

  sort(p);
  for (j = 0; j < 3; j++) {
    for (i = 12; i >= 0; i--) {
      if (p[i] % 13 > max) {
        max = p[i] % 13;
        imax = i;
      }
    }
    pass[j] = p[imax];
    p[imax] = -1;
    imax = -1;
    max = 0;
  }
  for (i = 0; i < 3; i++) {
    pp[i] = pass[i];
  }
  sort(p);
  return;
}

int onlypts(int *p) {
  int i;
  for (i = 0; i < 13; i++) {
    if (p[i] != -1 && p[i] != SQ && p[i] < H2) {
      return 0;
    }
  }
  return 1;
}

int playmaxavg(int *p, char who, int start, int *trick, int rnd, int *strat, int nosuits) {
  int istrat = (who == 'n')?N:(who == 'e')?E:(who == 'p')?P:W;
  int u, i, qs = -1;
  float nh = 0, ns = 0, nc = 0, nd = 0, sh = 0, ss = 0, sc = 0, sd = 0;
  float ah = 0, ac = 0, as = 0, ad = 0;
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
  if (start) {
    if (nc < 3 && sc < 10 && nc != 0 && suitsleft(strat, CLB, istrat)) {
      ac = 50;
    } else {
      ac = nc;
    }
    if (nd < 3 && sd < 10 && nd != 0 && suitsleft(strat, DIM, istrat)) {
      ad = 50;
    } else {
      ad = nd;
    }
    if (ns < 3 && ss < 10 && ns != 0 && suitsleft(strat, SPD, istrat)) {
      as = 50;
    } else {
      as = ns;
    }
    if (nh < 3 && sh < 10 && nh != 0 && suitsleft(strat, HRT, istrat)) {
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
  if (tsuit == 4||(rnd == 0&&start == 1&&!onlypts(p))) {
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
  if (qs != -1 && start == 0 && tsuit != 4) {
    out(who, SQ, "", 0);
    trick[istrat] = SQ;
    p[qs] = -1;
    return 1;
  }
  if (ac >= as && ac >= ad && ac >= ah &&
  (suitsleft(strat, CLB, istrat) ||nosuits)) {
    if (start == 0)
    playmax(p, CLB, 52, who, trick, start);
    else
    playmin(p, CLB, 52, who, trick, start, rnd);
    return 1;
  }
  if (ad >= as && ad >= ah && ad >= ac &&
  (suitsleft(strat, DIM, istrat) || nosuits)) {
    if (start == 0) {
      playmax(p, DIM, 52, who, trick, start);
    } else {
      playmin(p, DIM, 52, who, trick, start, rnd);
    }
    return 1;
  }
  if (as >= ac && as >= ad && as >= ah &&
  (suitsleft(strat, SPD, istrat) || nosuits)) {
    if (start == 0) {
      playmax(p, SPD, 52, who, trick, start);
    } else {
      playmin(p, SPD, 52, who, trick, start, rnd);
    }
    return 1;
  }
  if (ah >= as && ah >= ad && ah >= ac &&
  (suitsleft(strat, HRT, istrat) || nosuits)) {
    if (start == 0) {
      playmax(p, HRT, 52, who, trick, start);
    } else {
      playmin(p, HRT, 52, who, trick, start, rnd);
    }
    return 1;
  }
  playmaxavg(p, who, start, trick, rnd, strat, 1);
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

int playmax(int *p, int suit, int tmax, char who, int *trick, int start) {
  int i, max = -1, imax = -1, queen = 0, qs = -1;
  int w = (who == 'n') ? N : (who == 'e') ? E : (who == 'p') ? P : W;
  if (debug) {
    gotoxy(38, 6);printf("max");
    if (!quickdebug) {
      int u = getch();
      debug = (u == ';') ? (debug == 1) ? 0 : 1 : debug;
    }
  }
  for (i = 0;i<13;i++) {
    if (p[i] != -1 && p[i] / 13 == suit && p[i] > max && p[i] < tmax) {
      max = p[i];imax = i;
    }
    if (p[i] == SQ) {
      qs = i;
    }
  }
  if (imax != -1) {
    if (p[imax] == SQ && playmax(p, suit, SQ, who, trick, start)) {
      return 1;  // can play under SQ
    }
    for (i = 0; i < 4; i++) {
      if (trick[i] == SK || trick[i] == SA) {
        queen = 1;
      }
    }
    if (qs != -1 && suit == SPD && queen == 1) {
      out(who, p[qs], "", 0);
      trick[w] = SQ;
      p[qs] = -1;
      return 1;
    }
    out(who, p[imax], "", 0);
    trick[w] = p[imax];
    if (start) {
      tsuit = p[imax] / 13;
    }
    p[imax] = -1;
    return 1;
  } else {
    return 0;
  }
}

int trickmax(int *p, int s) {
  int i, m = -1;
  for (i = 0; i < 4; i++) {
    if (p[i] > m && p[i] / 13 == s) {
      m = p[i];
    }
  }
  return m;
}

int trickmin(int *p, int s) {
  int i, m = 100;
  for (i = 0; i < 4; i++) {
    if (p[i] < m && p[i] / 13 == s && p[i] != -1) {
      m = p[i];
    }
  }
  return (m == 100) ? -1 : m;
}

int playmin(int *p, int suit, int max, char who, int *trick, int start, int rnd) {
  if (debug) {
    gotoxy(38, 6);printf("min");
    if (!quickdebug) {
      int u = getch();
      debug = (u == ';') ? (debug == 1) ? 0 : 1 : debug;
    }
  }
  int i, min = 52, imin = -1;
  int w = (who == 'n') ? N : (who == 'e') ? E : (who == 'p') ? P : W;
  for (i = 0; i < 13; i++) {
    if (p[i] != -1 && p[i] / 13 == suit && p[i] < min && p[i] < max) {
      if (validtrick(p, p[i], start, rnd)) {
        min = p[i];
        imin = i;
      }
    }
  }
  if (imin != -1) {
    if (p[imin] == SQ&&playmax(p, suit, 52, who, trick, start)) {
      return 1;  // can play higher than SQ
    }
    out(who, p[imin], "", 0);
    trick[w] = p[imin];
    if (start) {
      tsuit = p[imin]/13;
    }
    p[imin] = -1;
    return 1;
  }
  return 0;
}

int nosuitsnext(char who, int *strat, int *trick, int suit) {
  if (who == 'n') {
    if ((trick[W] == -1 && strat[4 * W + suit] == 0) ||
    (trick[E] == -1 && strat[4 * E] == 0) ||
    (trick[P] == -1 && strat[4 * P + suit] == 0)) {
      return 0;
    } else {
      return 1;
    }
    return 0;
  }
  if (who == 'e') {
    if ((trick[N] == -1 && strat[4 * N + suit] == 0) ||
    (trick[W] == -1 && strat[4 * W] == 0) ||
    (trick[P] == -1 && strat[4 * P + suit] == 0)) {
      return 0;
    } else {
      return 1;
    }
    return 0;
  }
  if (who == 'w') {
    if ((trick[N] == -1 && strat[4 * N + suit] == 0) || 
    (trick[E] == -1 && strat[4 * E] == 0) || 
    (trick[P] == -1 && strat[4 * P + suit] == 0)) {
      return 0;
    } else {
      return 1;
    }
    return 0;
  }
}

int pointscannotbetaken(int *trick, int suit, int *a, int*b, int *c, int *p) {
  cdb("queen");
  int i, q = 1;
  if (suit == HRT) {
    return 0;
  }
  for (i = 0; i < 4; i++) {
    if (trick[i] > H2 || trick[i] == SQ) {
      return 0;
    }
  }
  if (suit != SPD) {
    return 1;
  } else {
    for (i = 0; i < 13; i++) {
      if (p[i] == SQ) {
        return 1;
      }
    }
    for (i = 0; i < 13; i++) {
      if (a[i] == SQ || b[i] == SQ || c[i] == SQ) {
        q = 0;
        break;
      }
    }
    cdb("\\queen");
    return q;
  }
}

int compturn(int* p, int *trick, int rnd, int start, char who, int *strat, int *a, int *b, int *c) {
  int i, j = 0, s = 0, low, u, qs = 0;
  int suit = (tsuit == 4) ?  0 : tsuit;
  int played = (lastplay == W) ? N : lastplay + 1;
  int istrat = (who == 'n') ? 0 : (who == 'e') ? 1 : 3;
  cdb("ct");
  if (start == 0) {  // not starting
    cdb("not start");
    for (i = 0; i < 13; i++) {
      if (p[i] != -1 && p[i] / 13 == suit) {
        s++;
      }
    }
    if (debug) {
      gotoxy(45, 2);printf("s:%i", s);
    }
    if (s > 0) {  // has same suit
      cdb("same suit");
      if (s == 1) {  // last card of that suit
        cdb("last card");
        playmin(p, suit, 52, who, trick, start, rnd);
        return played;
      } else {  // has more than one
        cdb("more than 1");
        if (trick[4] == 3 || nosuitsnext(who, strat, trick, suit)) {  // last to play
          cdb("last to play");
          if (ptsintrick(trick)) {
            cdb("pntsintrick");
            if (playmax(p, suit, trickmax(trick, suit), who, trick, start)) {
              cdb("can play under");
              // can play under
              return played;
            } else {  // cant play under
              cdb("cant play under");
              playmax(p, suit, 52, who, trick, start);
              return played;
            }
          } else {  // no pts in trick
            cdb("!pntintrick");
            playmax(p, suit, 52, who, trick, start);
            return played;
          }
        } else {  // not last to play
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
          } else {  // cant play under
            cdb("!first trick&cant play under");
            if (trick[4] == 2 && pointscannotbetaken(trick, suit, a, b, c, p)) {
              playmax(p, suit, 52, who, trick, start);
            } else {
              playmin(p, suit, 52, who, trick, start, rnd);
            }
            cdb("!frst&cantunder\\");
            return played;
          }
        }
      }
    } else {  // doesnt have same suit
      cdb("no suit");
      strat[istrat * 4 + suit]++;
      playmaxavg(p, who, start, trick, rnd, strat, 1);
      return played;
    }
  } else {  // starting
    cdb("starting");
    playmaxavg(p, who, start, trick, rnd, strat, 0);
    return played;
  }
}


