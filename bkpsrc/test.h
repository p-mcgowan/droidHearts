typedef struct Player {
  int cards[13];
  int trick, round, total;
  char *name;

  int nameLength() {
    return strlen(name);
  }

} Player;

typedef struct Table {
  Player players[PLAYERS];
  int deck[N_CARDS], strat[N_STRAT], trick[PLAYERS + 1];
  int pass, round;

  void initialize(int newGame) {
    int i;
    pass = 3;
    round = 0;
    trick[NORTH] = -1;
    trick[EAST] = -1;
    trick[PLAYER] = -1;
    trick[WEST] = -1;
    trick[TRICK_COUNT] = 0;
    for (i = 0; i < N_CARDS; i++) {
      deck[i] = i;
    }
    for (i = 0; i < N_STRAT; i++) {
      strat[i] = 0;
    }
    shuf(deck);

    for (i = 0; i < CARDS_IN_HAND; i++) {
      players[NORTH].cards[i] = draw(deck);
      players[EAST].cards[i] = draw(deck);
      players[PLAYER].cards[i] = draw(deck);
      players[WEST].cards[i] = draw(deck);
    }
    if (newGame) {
      for (i = 0; i < PLAYERS; i++) {
        players[i].trick = 0;
        players[i].round = 0;
        players[i].total = 0;
      }
    }
  }

} Table;

void test() {
  Player p;

  p.name = "Johnny";
  printf("%d: %s", p.nameLength(), p.name);
/*  system("clear");
  char d = 'h';
  int i, u;

  Frame mainWindow(65, 39);
  mainWindow.createDivs(d, 3, 21, 28, 34);
  mainWindow.draw();

  int nClubs = 3;
  Coord clubStart = mainWindow.cellAnchor(CELL_CARDS, d).add(2, 0);
  Frame clubs(nClubs * (CARD_WIDTH - 1) + 1, CARD_HEIGHT, clubStart);
  for (i = 0; i < nClubs - 1; i++) {
    clubs.addDiv('v', CARD_WIDTH + (CARD_WIDTH - 1 ) * i);
  }
  clubs.draw();

  gotoxy(1, 45);
  return;*/
}
/*
+---------------------------------------------------------------+
|                                                               |
|                            north                              |
|                                                               |
|                                                               |
|                            +---+                              |
|                            |AD |                              |
|                            +---+                              |
|                                                               |
|                  +---+              +---+                     |
|         west     |AD |              |AD |     east            |
|                  +---+              +---+                     |
|                                                               |
|                            +---+                              |
|                            |AD |                              |
|                            +---+                              |
|                                                               |
|                                                               |
|                            south                              |
|                                                               |
+---------------------------------------------------------------+
|  +---+---+---+ +---+---+---+ +---+---+---+ +---+---+---+---+  |
|  |10D|AD |AD | |AD |10D|AD | |10D|AD |AD | |10D|AD |AD |AD |  |
|  +---+---+---+ +---+---+---+ +---+---+---+ +---+---+---+---+  |
|  +---+---+---+                                                |
|  |10D|10D|10D|                                                |
|  +---+---+---+                                                |
+---------------------------------------------------------------+
| Name                              Round   Total  Overall      |
| North                              16      25     100         |
| East                               16      25     100         |
| South                              16      25     100         |
| West                               16      25     100         |
+---------------------------------------------------------------+
| Enter a card (eg 10D): 10D                                    |
| Play the 10D [y/N]? y                                         |
|                                                               |
|                                                               |
+---------------------------------------------------------------+

12345678901234567890123456789012345678901234567890123456789012345
         10        20        30        40        50        60
*/
