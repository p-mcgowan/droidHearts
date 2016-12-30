// Coordinate point object
//
typedef struct Coord {
  int x;
  int y;

  Coord() {
    x = -1;
    y = -1;
  }

  Coord(int a, int b) {
    x = a;
    y = b;
  }
  
  void set(int a, int b) {
    x = a;
    y = b;
  }

  // Add or subtract values to a coordinate
  Coord add(int a, int b) {
    return Coord(x + a, y + b);
  }

  // Get the difference between 2 points
  Coord distance(Coord a) {
    return Coord(a.x - x, a.y - y);
  }

  // Print the coordinate pair
  void printPair() {
    printf("(%d, %d)", x, y);
    return;
  }

} Coord;

// Window drawing object
typedef struct Frame {
  int *hDivs;
  int *vDivs;
  int height;
  int width;
  int hCells;
  int vCells;
  Coord anchor;
  
  Frame() {}

  Frame(int w, int h, Coord start = {.x = 1, .y = 1}) {
    height = h;
    width = w;
    hCells = 0;
    vCells = 0;
    anchor.x = start.x;
    anchor.y = start.y;
  }
  
  void set(int w, int h, Coord start = {.x = 1, .y = 1}) {
    height = h;
    width = w;
    hCells = 0;
    vCells = 0;
    anchor.x = start.x;
    anchor.y = start.y;
  } 
  
  // Append a division to the window
  void addDiv(char dir, int value) {
    if (dir == 'h') {
      if (hCells != 0) {
        realloc(hDivs, hCells + 1);
      } else {
        hDivs = (int*)malloc(sizeof(int));
      }
      hDivs[hCells] = value;
      hCells++;
    } else if (dir == 'v') {
      if (vCells != 0) {
        realloc(vDivs, vCells + 1);
      } else {
        vDivs = (int*)malloc(sizeof(int));
      }
      vDivs[vCells] = value;
      vCells++;
    } else {
      return;
    }
  }
  
  // Remove a division from the window
  int rmDiv(char dir, int value) {
    int *divisions, *newDivs;
    int c, count, i;
    if (dir == 'h') {
      if (hCells == 0) {
        return -1;
      }
      divisions = hDivs;
      c = hCells;
    } else if (dir == 'v') {
      if (vCells == 0) {
        return -1;
      }
      divisions = vDivs;
      c = vCells;
    } else {
      return -1;
    }
    newDivs = (int*)malloc(c * sizeof(int));
    count = 0;
    for (i = 0; i < c; i++) {
      if (divisions[i] != value) {
        newDivs[count++] = divisions[i];
      }
    }

    if (dir == 'h') {
      free(hDivs);
      realloc(newDivs, count);
      hDivs = newDivs;
      hCells = count;
    } else {
      free(vDivs);
      realloc(newDivs, count);
      vDivs = newDivs;
      vCells = count;
    }

    return 1;
  }

  // Create divisions from a list
  void createDivs(char dir, int n, ...) {
    register int i;
    int *divs = (int*)malloc(n * sizeof(int));
    va_list ap;
    va_start(ap, n);
    for (i = 0; i < n; i++) {
      divs[i] = va_arg(ap, int);
    }
    va_end(ap);
    if (dir == 'h') {
      hDivs = divs;
      hCells = n;
    } else if (dir == 'v') {
      vDivs = divs;
      vCells = n;
    } else {
      return;
    }
  }

  // Print a horizontal division
  void drawHDiv(Coord start, int x) {
    int i;
    gotoxy(start.x, start.y);
    printf("+");
    for (i = 1; i < x - 1; i++) {
      printf("-");
    }
    printf("+");
    return;
  }

  // Print a vertical division
  void drawVDiv(Coord start, int y) {
    int i;
    gotoxy(start.x, start.y);
    printf("+");
    for (i = 1; i < y - 1; i++) {
      gotoxy(start.x, start.y + i);
      printf("|");
    }
    gotoxy(start.x, start.y + i);
    printf("+");
    return;
  }

  // Draw the window
  void draw(Coord start = {.x = -1, .y = -1}) {
    int i;
    if (start.x > 0 && start.y > 0) {
      anchor.x = start.x;
      anchor.y = start.y;
    }

    // Draw border
    drawHDiv(anchor, width);
    for (i = 1; i < height - 1; i++) {
      gotoxy(anchor.x, anchor.y + i);
      printf("|");
      gotoxy(width + anchor.x - 1, anchor.y + i);
      printf("|");
    }
    drawHDiv(anchor.add(0, height - 1), width);
  
    // Draw cell divisions, if any
    for (i = 0; i < hCells; i++) {
      if (hDivs[i] < height) {
        drawHDiv(anchor.add(0, hDivs[i] - 1), width);
      }
    }
    for (i = 0; i < vCells; i++) {
      if (vDivs[i] < width) {
        drawVDiv(anchor.add(vDivs[i] - 1, 0), height);
      }
    }
  }

  // Replace cell contents with a character
  void fillCell(int cell, char fill, char dir) {
    int i;
    if ((dir == 'h' && cell > hCells) || (dir == 'v' && cell > vCells) ||
    cell < 0 || anchor.x == -1 || anchor.y == -1) {
      return;
    }
    Coord s = cellAnchor(cell, dir);
    Coord e = cellCorner(cell, dir);
    /*if (hCells == 0 && vCells == 0) {
      s = anchor;
      e = Coord(width + anchor.x - 1, height + anchor.y - 1);
    } else {
      s = cellAnchor(cell, dir);
      e = cellCorner(cell, dir);
    }*/
    
    char spc[e.x - s.x + 1];
    memset(spc, fill, e.x - s.x + 1);
    spc[e.x - s.x + 1] = '\0';
    for (i = s.y; i <= e.y; i++) {
      gotoxy(s.x, i);
      printf("%s", spc);
    }
  }

  void clearCell(int cell = 0, char dir = 'h') {
    fillCell(cell, ' ', dir);
  }

  void clearCells(char dir = 'h') {
    int i;
    for (i = 0; i <= hCells; i++) {
      fillCell(i, ' ', dir);
    }
  }

  // Get the coordinate of the upper left-most point in a cell
  Coord cellAnchor(int cell = 0, char div = 'h') {
    int a, s;
    int *divs;
    if ((div == 'h' && cell > hCells) || (div == 'v' && cell > vCells) ||
    cell < 0 || anchor.x == -1 || anchor.y == -1 || (div != 'h' && div != 'v')) {
      return Coord(-1, -1);
    }
    if (div == 'v') {
      a = anchor.x;
      divs = vDivs;
    } else {
      a = anchor.y;
      divs = hDivs;
    }

    if (cell == 0) {
      s = a + 1;
    } else {
      s = a + divs[cell - 1];
    }

    if (div == 'v') {
      return Coord(s, anchor.y + 1);
    } else {
      return Coord(anchor.x + 1, s);
    }
  }

  // Get the coordinate of the bottom right-most point in a cell
  Coord cellCorner(int cell = 0, char div = 'h') {
    int a, c, s;
    int *divs;
    if ((div == 'h' && cell > hCells) || (div == 'v' && cell > vCells) ||
    cell < 0 || anchor.x == -1 || anchor.y == -1 || (div != 'h' && div != 'v')) {
      return Coord(-1, -1);
    }
    if (div == 'v') {
      a = width;
      c = vCells;
      divs = vDivs;
    } else {
      a = height;
      c = hCells;
      divs = hDivs;
    }

    if (cell == c) {
      s = a - 1;
    } else {
      s = divs[cell] - 1;
    }

    if (div == 'v') {
      return Coord(s + anchor.x - 1, anchor.y + height - 2);
    } else {
      return Coord(anchor.x + width - 2, s + anchor.y - 1);
    }
  }

  // Get coords of the cell center
  Coord cellCenter(int cell = 0, char div = 'h') {
    Coord a = cellAnchor(cell, div);
    Coord c = cellCorner(cell, div);
    return Coord(a.x + (c.x - a.x) / 2, a.y + (c.y - a.y) / 2);
  }

} Frame;


// Player hand
//
typedef struct Hand {
  int cards[N_HAND];

  void sort(int *card) {
    int i, t = 0, s;
    while (t == 0) {
      t = 1;
      for (i = 0; i < 12; i++) {
        if (card[i + 1] < card[i]) {
          t = 0;
          s = card[i];
          card[i] = card[i + 1];
          card[i + 1] = s;
        }
      }
    }
  }
  
  int suitCount(int *card) {
  }
 
} Hand;


// Deck
//
typedef struct Deck {
  int cards[N_CARDS];

  void initialize() {
    int i;
    for (i = 0; i < N_CARDS; i++) {
      cards[i] = i;
    }
  }

  void shuf() {
    int i, j, k;
    initialize();
    if ((unsigned)time(NULL) != seed) {
      srand((unsigned)time(NULL));
      seed = ((unsigned)time(NULL));
    }
    for (i = 0; i < N_CARDS; i++) {
      k = rand() % N_CARDS;
      j = cards[i];
      cards[i] = cards[k];
      cards[k] = j;
    }
  }  

  int draw() {
    int i, j;
    for (i = 0; i < 52; i++) {
      j = cards[i];
      if (j != -1) {
        cards[i] = -1;
        return j;
      } else {
        if (i == 51) {
          shuf();
          i = 0;
        }
      }
    }
  }

} Deck;


// Player object
//
typedef struct Player {
  int cards[N_HAND];
  int trick, round, total;
  char name[NAME_LENGTH];
  Frame trickCard;
  Coord nameCenter;

  Player() {
    trick = 0;
    round = 0;
    total = 0;
    memset(cards, -1, N_HAND);
  }

  int nameLength() {
    return strlen(name);
  }

  int suitCount(int suit = -1) {
    int i, s, h, d, c;
    s = h = d = c = 0;
    for (i = 0; i < N_HAND; i++) {
      switch (cards[i] / N_HAND) {
        case CLB:
          c++;
          break;
        case HRT:
          h++;
          break;
        case DIM:
          d++;
          break;
        case SPD:
          s++;
          break;
      }
    }
    switch (suit) {
      case -1:
        int t;
        t = 0;
        t += (c > 0)? 1 : 0;
        t += (s > 0)? 1 : 0;
        t += (h > 0)? 1 : 0;
        t += (d > 0)? 1 : 0;
        return t;
      case CLB:
        return c;
        break;
      case DIM:
        return d;
        break;
      case SPD:
        return s;
        break;
      case HRT:
        return h;
        break;
    }
  }

  int cardCount() {
    int i, c;
    for (i = 0, c = 0; i < N_HAND; i++) {
      if (cards[i] != -1) {
        c++;
      }
    }
    return c;
  }

} Player;


// Deck, players, and game variables object
//
typedef struct Table {
  Frame window;
  Player players[PLAYERS];
  Deck deck;
  int strat[N_STRAT], trick[N_TRICK];
  int pass, round, lastplay;

  Table() {}

  void initialize(int newGame = 0) {
    int i;
    pass = 0;
    round = 0;

    deck.initialize();
    for (i = 0; i < N_STRAT; i++) {
      strat[i % N_STRAT] = 0;
      trick[i % N_TRICK] = -1;
    }
    deck.shuf();
    for (i = 0; i < N_HAND; i++) {
      players[NORTH].cards[i] = deck.draw();
      players[EAST].cards[i] = deck.draw();
      players[PLAYER].cards[i] = deck.draw();
      players[WEST].cards[i] = deck.draw();
    }

    if (newGame) {
      /*for (i = N; i <= W; i++) {
        players[i].name = (char*)malloc(NAME_LENGTH * sizeof(char));
        memset(players[i].name, '\0', NAME_LENGTH);
      }
      players[N].name = (char*)"North";
      players[E].name = (char*)"East";
      players[S].name = (char*)"Player";
      players[W].name = (char*)"West";*/
      players[N].nameCenter = Coord(32, 3);
      players[E].nameCenter = Coord(51, 11);
      players[S].nameCenter = Coord(32, 19);
      players[W].nameCenter = Coord(12, 11);
      players[N].trickCard = Frame(CARD_WIDTH, CARD_HEIGHT, Coord(30, 6));
      players[E].trickCard = Frame(CARD_WIDTH, CARD_HEIGHT, Coord(40, 10));
      players[S].trickCard = Frame(CARD_WIDTH, CARD_HEIGHT, Coord(30, 14));
      players[W].trickCard = Frame(CARD_WIDTH, CARD_HEIGHT, Coord(20, 10));

      window = Frame(65, 39, Coord(1, 1));
      window.createDivs(HORIZ, 3, 21, 28, 34);
    }
  }
  
  void drawNames() {
    int i, start;
    for (i = 0; i < PLAYERS; i++) {
      start = players[i].nameCenter.x - players[i].nameLength() / 2;
      gotoxy(start, players[i].nameCenter.y);
      printf("%s", players[i].name);
    }
  }

  void drawTrick() {
    int i;
    for (i = 0; i < PLAYERS; i++) {
      players[i].trickCard.draw();
      players[i].trickCard.clearCell();
    }
  }
  
  void drawScore() {
    int i;
    window.clearCell(CELL_SCORE);
    Coord start = window.cellAnchor(CELL_SCORE);
    gotoxy(start.x + 1, start.y);
    printf("NAME                              TRICK   ROUND   TOTAL");
    for (i = 1; i <= PLAYERS; i++) {
      gotoxy(start.x + 1, start.y + i);
      printf("%s", players[i - 1].name);
    }
    for (i = 1; i <= PLAYERS; i++) {
      gotoxy(start.x + 35, start.y + i);
      printf("%d", players[i - 1].trick);
    }
    for (i = 1; i <= PLAYERS; i++) {
      gotoxy(start.x + 43, start.y + i);
      printf("%d", players[i - 1].round);
    }
    for (i = 1; i <= PLAYERS; i++) {
      gotoxy(start.x + 50, start.y + i);
      printf("%d", players[i - 1].total);
    }
  }

  void drawPlayerHand() {
    int i, suit, suits, suitIndex, totalWidth;
    int u;
    window.clearCell(CELL_CARDS);

    suits = players[P].suitCount();
    totalWidth = CARD_WIDTH + (CARD_WIDTH - 1) * (players[P].cardCount() - 1) + suits;
    Coord start = window.cellAnchor(CELL_CARDS);
    Coord suitStart = start.add((window.width - totalWidth - 1) / 2 - 1, 0);

    sort(players[P].cards);
    for (suitIndex = 0; suitIndex < N_HAND; suitIndex++) {
      if (players[P].cards[suitIndex] != -1) {
        break;
      }
    }
    suit = players[P].suitCount(CLB);
    if (suit > 0) {
      Frame clubs(CARD_WIDTH + (CARD_WIDTH - 1) * (suit -1), CARD_HEIGHT, suitStart);
      for (i = 0; i < suit; i++) {
        clubs.addDiv(VERT, CARD_WIDTH + i * (CARD_WIDTH - 1));
      }
      suitStart = suitStart.add(1 + clubs.width, 0);
      clubs.draw();
      for (i = 0; i < suit; i++) {
        gotoxyc(clubs.cellAnchor(i, VERT));
        printCard(players[P].cards[suitIndex++]);
      }
    }
    suit = players[P].suitCount(DIM);
    if (suit > 0) {
      Frame dims(CARD_WIDTH + (CARD_WIDTH - 1) * (suit -1), CARD_HEIGHT, suitStart);
      for (i = 0; i < suit; i++) {
        dims.addDiv(VERT, CARD_WIDTH + i * (CARD_WIDTH - 1));
      }
      suitStart = suitStart.add(1 + dims.width, 0);
      dims.draw();
      for (i = 0; i < suit; i++) {
        gotoxyc(dims.cellAnchor(i, VERT));
        printCard(players[P].cards[suitIndex++]);
      }
    }
    suit = players[P].suitCount(SPD);
    if (suit > 0) {
      Frame spades(CARD_WIDTH + (CARD_WIDTH - 1) * (suit -1), CARD_HEIGHT, suitStart);
      for (i = 0; i < suit; i++) {
        spades.addDiv(VERT, CARD_WIDTH + i * (CARD_WIDTH - 1));
      }
      suitStart = suitStart.add(1 + spades.width, 0);
      spades.draw();
      for (i = 0; i < suit; i++) {
        gotoxyc(spades.cellAnchor(i, VERT));
        printCard(players[P].cards[suitIndex++]);
      }
    }
    suit = players[P].suitCount(HRT);
    if (suit > 0) {
      Frame hearts(CARD_WIDTH + (CARD_WIDTH - 1) * (suit -1), CARD_HEIGHT, suitStart);
      for (i = 0; i < suit; i++) {
        hearts.addDiv(VERT, CARD_WIDTH + i * (CARD_WIDTH - 1));
      }
      suitStart = suitStart.add(1 + hearts.width, 0);
      hearts.draw();
      for (i = 0; i < suit; i++) {
        gotoxyc(hearts.cellAnchor(i, VERT));
        printCard(players[P].cards[suitIndex++]);
      }
    }
  }

  void redraw() {
    clrscr();
    window.draw();
    drawNames();
    drawTrick();
    drawScore();
    drawPlayerHand();
  }

  int trickCount() {
    int i, count;
    count = 0;
    for (i = 0; i < PLAYERS; i++) {
      count += (trick[i] != -1) ? 1 : 0;
    }
    return count;
  }

  int trickmax(int suit = N_CARDS) {
    int i, m;
    if (suit == N_CARDS) {
      suit = trick[TRICK_SUIT];
    }
    m = -1;
    for (i = 0; i < PLAYERS; i++) {
      if (trick[i] > m && trick[i] / 13 == suit) {
        m = trick[i];
      }
    }
    return m;
  } 
  
  int trickmin(int suit = -1) {
    int i, m;
    if (suit == -1) {
      suit = trick[TRICK_SUIT];
    }
    m = N_CARDS;
    for (i = 0; i < PLAYERS; i++) {
      if (trick[i] < m && trick[i] / 13 == suit && trick[i] != -1) {
        m = trick[i];
      }
    }
    return (m == N_CARDS) ? -1 : m;
  }

  int currentPlayer() {
    return (lastplay + 1) % PLAYERS;
  }

  int trickSuit() {
    return trick[TRICK_SUIT];
  }

  int roundScore() {
    int i, total;
    total = 0;
    for (i = 0; i < PLAYERS; i++) {
      total += players[i].round;
    }
    return total;
  }

  int start() {
    int i;
    for (i = 0; i < PLAYERS; i++) {
      if (trick[i] != -1) {
        return 0;
      }
    }
    return 1;
  }

  void playCard(int slot) {
    trick[currentPlayer()] = players[currentPlayer()].cards[slot];
    if (trickCount() == 1) {  // starting
      trick[TRICK_SUIT] = players[currentPlayer()].cards[slot] / N_SUITS;
    }
    lastplay = currentPlayer();

    gotoxyc(players[currentPlayer()].trickCard.cellAnchor());
    printCard(players[currentPlayer()].cards[slot]);
    players[currentPlayer()].cards[slot] = -1;
  }
  
  void sort(int *card) {
    int i, t = 0, s;
    while (t == 0) {
      t = 1;
      for (i = 0; i < 12; i++) {
        if (card[i + 1] < card[i]) {
          t = 0;
          s = card[i];
          card[i] = card[i + 1];
          card[i + 1] = s;
        }
      }
    }
  }
 
} Table;

