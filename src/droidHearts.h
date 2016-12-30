#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <conio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include "conOut.h"
#include "getch.h"


// deprecated?
#define RND 13
#define SCR 14
#define TOT 15
#define N 0
#define E 1
#define P 2
#define S 2
#define W 3

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
#define N_CARDS 52
#define N_SUITS 4

#define CLB 0
#define DIM 1
#define SPD 2
#define HRT 3

#define NORTH 0
#define EAST 1
#define PLAYER 2
#define SOUTH 2
#define WEST 3

#define N_HAND 13
#define N_STRAT 16
#define N_TRICK 5
#define NAME 75
#define PLAYERS 4
#define TRICK_SUIT 4
#define STRAT_NO_SUIT 4
#define NAME_LENGTH 10

#define HOLD 0
#define LEFT 1
#define RIGHT 2
#define ACROSS 3

#define LOAD 0
#define NEWGAME 1
#define NO_PRINT 0
#define PRINT 1
#define NO_SUITS 0
#define HAS_SUITS 1

// Drawing
#define HORIZ 'h'
#define VERT 'v'
#define CARD_WIDTH 5
#define CARD_HEIGHT 3
#define CELL_PLAYERS 0
#define CELL_CARDS 1
#define CELL_SCORE 2
#define CELL_OUTPUT 3

#define RST "\e[m"
#define RED "\e[31m"
#define YLW "\e[33m"

double seed = 0;
//int tsuit = 4;  // first trick = 4, 0-3 otherwise
//int lastplay;  // who played last

// External librariea
#include "extern.h"
#include "classes.h"
#include "debug.h"
#include "drawable.h"
#include "game.h"
#include "logic.h"
#include "ai.h"

