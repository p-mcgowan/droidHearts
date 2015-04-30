#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#define RND 13
#define SCR 14
#define TOT 15
#define C2 0
#define C3 1
#define C4 2
#define C5 3
#define C6 4
#define C7 5
#define C8 6
#define C9 7
#define C10 8
#define CJ 9
#define CQ 10
#define CK 11
#define CA 12
#define D2 13
#define D3 14
#define D4 15
#define D5 16
#define D6 17
#define D7 18
#define D8 19
#define D9 20
#define D10 21
#define DJ 22
#define DQ 23
#define DK 24
#define DA 25
#define S2 26
#define S3 27
#define S4 28
#define S5 29
#define S6 30
#define S7 31
#define S8 32
#define S9 33
#define S10 34
#define SJ 35
#define SQ 36
#define SK 37
#define SA 38
#define H2 39
#define H3 40
#define H4 41
#define H5 42
#define H6 43
#define H7 44
#define H8 45
#define H9 46
#define H10 47
#define HJ 48
#define HQ 49
#define HK 50
#define HA 51
#define CLB 0
#define DIM 1
#define SPD 2
#define HRT 3
#define N 0
#define E 1
#define P 2
#define W 3
#define NAME 75
#define LEFT 0
#define RIGHT 1
#define ACROSS 2
#define HOLD 3
#define RST "\e[m"
#define RED "\e[31m"
#define YLW "\e[33m"
#define LOAD 0
#define NEWGAME 1

void shuf(int*);
int draw(int*);
void init(int*,int*,int*,int*,int*,int*);
int start(int*,int*,int*,int*);
void out(char,int,char*,int);
void phud(int*);
void sort(int*);
int getchoice(int*,int,int,int*,int*);
void clrin();
int validtrick(int*,int,int,int);
void names();
void clrn(char*);
int compturn(int*,int*,int,int,char,int*,int*,int*,int*);
int playmin(int*,int,int,char,int*,int,int);
int playmax(int*,int,int,char,int*,int);
int playmaxavg(int*,char,int,int*,int,int*,int);
int trickmax(int*,int);
int ptsintrick(int*);
void hud(int*,int *,int *,int *);
void hassuit(int*,int*,int,int);
int suitsleft(int*,int,int);
int score(int*,int*,int*,int*,int*,int);
int won(int*,int*,int*,int*);
void passcards(int*,int*,int*,int*,int);
int pointscannotbetaken(int*,int,int*,int*,int*,int*);
void cmax(int*,int*);
void ppas(int*,int*,int);
void give(int*,int*);
void compwait();
void cdb();
void qdb();
void sdb();
void ldb(int);  // print last and next play at left -- requires trick[3]
void tdb(int*);  // prints trick info at top -- requires trick
void clrscr();
void gotoxy(int,int);
int debuggingoptions();
int gameoptions();
void printplayers();
int game();

double seed = 0;
int tsuit = 4;  // first trick = 4, 0-3 otherwise
int lastplay;  // who played last
  // options
int debug = 0,quickdebug = 0,colourblind = 1,cplay = 0,
qdbtoggle = 1,sdbtoggle = 1,cdbtoggle = 1,ldbtoggle = 1,tdbtoggle = 1;
  // global player hands for debugging
int *pdb,*ndb,*edb,*wdb;

