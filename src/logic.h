int suitsleft(Table *table, int suit) {
  int i, left;
  left = 0;
  if (debug) {
    gotoxy(38, 6);printf("sut");
    if (!quickdebug) {
      int u = getch();
      debug = (u == ';')? (debug == 1)? 0 : 1 : debug;
    }
  }
  for (i = N; i <= W; i++) {
    if (i == (table->lastplay + 1) % PLAYERS) {
      continue;
    }
    if (table->strat[i * 4 + suit] > 0) {
      left++;
    }
  }
  if (left == 3) {
    return 0;
  }
  return 1;
}

//TODO unused...
void hassuit(int *p, int *strat, int tsuit, int suit) {
  int i, j, c = 0, d = 0, s = 0, h = 0;
  if (debug) {
    gotoxy(1, 6);printf("has");
    if (!quickdebug) {
      int u = getch();
      debug = (u == ';') ? (debug == 1) ? 0 : 1 : debug;
    }
  }
  for (i = 0; i < 13; i++) {
    if (p[i] / 13 == CLB) {
      c++;
    }
    if (p[i] / 13 == DIM) {
      d++;
    }
    if (p[i] / 13 == SPD) {
      s++;
    }
    if (p[i] / 13 == HRT) {
      h++;
    }
  }
  gotoxy(1, 17);
  if (tsuit != suit) {
    if (c == 0) {
      strat[8]++;
    }
    if (d == 0) {
      strat[9]++;
    }
    if (s == 0) {
      strat[10]++;
    }
    if (h == 0) {
      strat[11]++;
    }
  }
}

//TODO
int pointsBroken() {
return 1;
}

int validtrick(Table *table, int card) {
  int i, j, suit, start;
  int hrts, spds, dims, clbs;
  int *cards;
  cards = table->players[(table->lastplay + 1) % PLAYERS].cards;
  suit = card / 13;
  hrts = spds = dims = clbs = 0;
  start = (table->trickCount() == 0)? 1 : 0;
  for (i = 0; i < 13; i++) {
    if (cards[i] >= C2 && cards[i] <= CA) {
      clbs++;
    }
    if (cards[i] >= D2 && cards[i] <= DA) {
      dims++;
    }
    if (cards[i] >= S2 && cards[i] <= SA) {
      spds++;
    }
    if (cards[i] >= H2 && cards[i] <= HA) {
      hrts++;
    }
  }

  if (start == 1) {  // if your starting
    if (pointsBroken()) {
      return 1;
    } else {
      j = 0;
      for (i = 0; i < 13; i++) {  // if have non pts
        if (cards[i] != -1 && cards[i] != SQ && cards[i] < H2) {
          j = 1;  // have non pnt
          if (card == cards[i]) {  // trying to play non point
            return 1;
          }
        }
      }
      if (j != 1) {
        return 1;
      }
      return 0;
    }
  } else {  // not starting
    if (table->trick[TRICK_SUIT] == 4) {
      if (suit == CLB || (clbs == 0 && suit != HRT && card != SQ)) {
        return 1;
      }
      j = 0;
      for (i = 0; i < 13; i++) {
        if (cards[i] != -1 && (cards[i] == SQ || cards[i] >= H2)) {
          j++;
        }
      }  // if only pts cards
      if (j == 13) {
        return 1;
      } else {
        return 0;
      }
    } else {  // not first rnd
      if (suit == table->trick[TRICK_SUIT]) {
        return 1;
      } else {
        if ((table->trick[TRICK_SUIT] == SPD && spds == 0) ||
        (table->trick[TRICK_SUIT] == DIM && dims == 0) ||
        (table->trick[TRICK_SUIT] == HRT && hrts == 0) ||
        (table->trick[TRICK_SUIT] == CLB && clbs == 0)) {
          return 1;
        }
      }
      return 0;
    }
  }
}

int min(int n, ...) {
  return 0;
  register int i;
  int min, x;
  va_list ap;
  va_start(ap, n);
  min = va_arg(ap, int);
  for (i = 0; i <= n; i++) {
    if ((x = va_arg(ap, int)) < min) {
      min = x;
    }
  }
  va_end(ap);
  return min;
}

int max(int n, ...) {
  return 0;
  register int i;
  int max, x;
  va_list ap;
  va_start(ap, n);
  max = va_arg(ap, int);
  for (i = 0; i <= n; i++) {
    if ((x = va_arg(ap, int)) > max) {
      max = x;
    }
  }
  va_end(ap);
  return max;
}

