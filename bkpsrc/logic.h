int suitsleft(int *strat, int suit, int who) {
  if (debug) {
    gotoxy(38, 6);printf("sut");
    if (!quickdebug) {
      int u = getch();
      debug = (u == ';')?(debug == 1)? 0 : 1:debug;
    }
  }
  int i, left = 0;
  for (i = 0; i < 4; i++) {
    if (i != who && strat[i * 4 + suit] > 0) {
      left++;
    }
  }
  if (left == 3) {
    return 0;
  }
  return 1;
}

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

int validtrick(int *p, int card, int start, int rnd) {
  int hrts = 0, spds = 0, dims = 0, clbs = 0;
  int i, j = 0, s = card / 13;
  for (i = 0; i < 13; i++) {
    if (p[i]>= C2&&p[i]<= CA) {
      clbs++;
    }
    if (p[i]>= D2&&p[i]<= DA) {
      dims++;
    }
    if (p[i]>= S2&&p[i]<= SA) {
      spds++;
    }
    if (p[i]>= H2&&p[i]<= HA) {
      hrts++;
    }
  }
  // pts not broken-chk rnd pts
  if (start == 1) {  // if your starting
    if (rnd != 0) {
      return 1;
    } else {  // rnd == 0
      for (i = 0; i < 13; i++) {  // if have non pts
        if (p[i] != -1 && p[i] != SQ && p[i] < H2) {
          j = 1;  // have non pnt
          if (card == p[i]) {
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
    if (tsuit == 4) {
      if (s == CLB || (clbs == 0 && s != HRT && card != SQ)) {
        return 1;
      }
      for (i = 0; i < 13; i++) {
        if (p[i] != -1 && (p[i] == SQ || p[i] >= H2)) {
          j++;
        }
      }  // if only pts cards
      if (j == 13) {
        return 1;
      } else {
        return 0;
      }
    } else {  // not first rnd
      if (s == tsuit) {
        return 1;
      } else {
        if ((tsuit == SPD && spds == 0) ||
        (tsuit == DIM && dims == 0) ||
        (tsuit == HRT && hrts == 0) ||
        (tsuit == CLB && clbs == 0)) {
          return 1;
        }
      }
      return 0;
    }
  }
}

int min(int n, ...) {
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
