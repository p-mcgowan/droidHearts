
typedef struct Stream {
  int i;
  char c;
  int ia[1024];
  char ca[1024];
  char f[1024];

  void log(Stream s = {.i = -1, .c = -1, .ia = {-1}, .ca = {-1}, .f = {-1}}) {
  }

} Stream;
