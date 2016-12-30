struct Coord;
struct Deck;
struct Frame;
struct Player;
struct Table;

int compturn(Table *table);
int draw(int *deck);
int game(Table *table, int newgame);
int gameOptions(Table *table);
int getchoice(Table *table);
int hasQueen(int *cards);
int loadgame(Table *table);
int nosuitsnext(Table *table);
int onlypts(int *h);
int playmax(Table *table, int tmax, int suit);
int playmaxavg(Table *table, int nosuits);
int playmin(Table *table, int max, int suit);
int pointscannotbetaken(Table *table);
int ptsintrick(int *t);
int save(Table *table);
int score(Table *table);
int start(Table *table);
int suitsleft(Table *table, int suit);
int validtrick(Table *table, int card);
int won(Table *table);
void clrin();
void changeNames(Table *table);
void maxCardPass(int *p, int *pp);
void give(int *rx, int *tx);
void gotoxyc(Coord s);
void hud(Table *table);
void passcards(Table *table);
void printCard(int card);
void shuf(int *deck);
void sort(int *p);

// Development
int debuggingoptions();
void handDebug(Table *table, int p);
void cdb(char *s);
void ldb(int numPlayed);
void qdb(char *s);
void sdb(char *s);
void tdb(int *trick);

// Refactor / reimplement
void out(char pos, int card, char* name, int n);
void phud(int *p);
void ppass(int *p, int *pp, int w);
void printplayers(Table *table);

// Deprecated?
void clrn(char *n);
void compwait();
void hassuit(int *p, int *strat, int tsuit, int suit);

