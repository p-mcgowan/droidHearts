// Coordinate point object
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
  
  Frame(int w, int h, Coord start = {.x = 1, .y = 1}) {
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

    gotoxy(1,42);
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

  void clearCell(int cell, char dir = 'h') {
    fillCell(cell, ' ', dir);
  }

  void clearCells(char dir = 'h') {
    int i;
    for (i = 0; i <= hCells; i++) {
      fillCell(i, ' ', dir);
    }
  }

  // Get the coordinate of the upper left-most point in a cell
  Coord cellAnchor(int cell, char div = 'h') {
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
  Coord cellCorner(int cell, char div = 'h') {
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
  Coord cellCenter(int cell, char div = 'h') {
    Coord a = cellAnchor(cell, div);
    Coord c = cellCorner(cell, div);
    return Coord(a.x + (c.x - a.x) / 2, a.y + (c.y - a.y) / 2);
  }

} Frame;

