
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
int player = 1;
using namespace std;
class body;
class ma;
string bl = "]-[";
string pas = " . ";
string point = "<#>";
string vishnya = " # ";
string enem = ">X<";
int k = 16;
double road(double xx1, double yy1, double xx2, double yy2) {
  return sqrt((xx1 - xx2) * (xx1 - xx2) + (yy2 - yy1) * (yy2 - yy1));
}
int better(int x1, int y1, int x2, int y2) {
  double xx1 = x1;
  double yy1 = y1;
  double xx2 = x2;
  double yy2 = y2;

  double r1 = road(xx1 + 1, yy1, xx2, yy2);
  double r2 = road(xx1, yy1 + 1, xx2, yy2);
  double r3 = road(xx1 - 1, yy1, xx2, yy2);
  double r4 = road(xx1, yy1 - 1, xx2, yy2);
  double minof = min(r1, min(r2, min(r3, r4)));
  if (minof == r1)
    return 2;
  if (minof == r2)
    return 4;
  if (minof == r3)
    return 1;
  if (minof == r4)
    return 3;

}
class poin {
  int x, y;
  int l;

 public:
  bool isa = false;
  poin() {
    x = 0;
    y = 0;
    l = 0;
  }
  int getx() {
    return x;
  }
  int gety() {
    return y;
  }
  int getl() {
    return l;
  }
  void sy(int y) {
    this->y = y;
  }
  void sx(int x) {
    this->x = x;
  }
  friend body;
};
class body {
 public:
  poin a[100][100];
  int x = 25, y = 25;

  body(poin& p) {
    a[50][50].x = p.x;
    a[50][50].y = p.y;
    a[50][50].isa = true;
  }
  bool po(int i, int j) {
    return a[i][j].isa;
  }

  void change(int i, int j, int u, int d) {
    a[i][j].x += d;
    a[i][j].y += u;
  }
  void del(ma& m, body& b, int i, int j) {
    b.a[i][j].isa = false;
  }
  void chek(ma& mi, body& b, int i, int j);

  friend ma;
};
class ma {

 public:
  string m[100][100];
  int h, w;
  ma(int h, int w) {
    this->h = h;
    this->w = w;
    for (int i = 0; i < h; i++)
      for (int j = 0; j < w; j++) {
        m[i][j] = pas;
      }
    for (int i = 0; i < max(w, h); i++) {
      m[i][0] = bl;
      m[0][min(i, w - 1)] = bl;
      m[h - 1][min(i, w - 1)] = bl;
      m[i][w - 1] = bl;
    }
  }
  void co() {
    system("cls");
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        cout << m[i][j];
      }
      cout << endl;
    }
  }
  void refact(ma& m, body& b, int u, int d) {
    ///������������
    for (int i = 0; i < 100; i++)
      for (int j = 0; j < 100; j++) {
        if (b.po(i, j)) {
          if (i < 0 && j < 0) {
            b.a[i][j].isa = false;
          } else {

            m.m[b.a[i][j].gety()][b.a[i][j].getx()] = pas;
            b.change(i, j, u, d);
          }
        }
      }
    ///����������
    for (int i = 0; i < 100; i++)
      for (int j = 0; j < 100; j++) {
        if (b.po(i, j)) {
          b.chek(m, b, i, j);
        }
      }

    ///���������
    for (int i = 0; i < 100; i++)
      for (int j = 0; j < 100; j++) {
        if (b.po(i, j)) {
          m.m[b.a[i][j].gety()][b.a[i][j].getx()] = point;
        }

      }
  }

  void vis(int x, int y, int* k) {
    if (m[y][x] == pas) {
      (*k)--;
      m[y][x] = vishnya;
    }
  }
  friend body;
};
void body::chek(ma& mi, body& b, int i, int j) {
  int x = b.a[i][j].x;
  int y = b.a[i][j].y;
  if (mi.m[y][x] == bl) {
    b.del(mi, b, i, j);
  } else if (mi.m[y][x] == enem) {
    b.del(mi, b, i, j);
    mi.m[y][x] = bl;
  } else {
    int zega = 0;
    for (int n = -1; n < 2; n++)
      for (int e = -1; e < 2; e++) {
        if (mi.m[y + n][x + e] == vishnya && (abs(n) != abs(e))) {
          b.a[i + n][j + e].isa = true;
          b.a[i + n][j + e].sx(x + e);
          b.a[i + n][j + e].sy(y + n);
          k++;
        }

      }

  }
}

class badboy {
 public:

  int x;
  int y;
  bool isl = false;
  badboy() {
    x = -1;
    y = -1;
    isl = false;
  }
  void isa(int x, int y) {
    isl = true;
    int w = x;
    int h = y;
    srand(time(NULL));
    int a = rand() % 4;
    if (a == 0) {
      this->x = 1;
      this->y = 1;
    }
    if (a == 1) {
      this->x = w - 2;
      this->y = 1;
    }
    if (a == 2) {
      this->x = 1;
      this->y = h - 2;
    }
    if (a == 3) {
      this->x = w - 2;
      this->y = h - 2;
    }

  }
  void recoll(ma& m, body& B) {
    int dd = y;
    int de = x;
    if (m.m[y][x] == bl) {
      isl = false;
    } else {
      m.m[y][x] = pas;
      bool vlad = false;
      for (int i = 1; i < m.h - 1; i++) {
        for (int j = 1; j < m.w - 1; j++) {
          if (m.m[i][j] == point) {

            if (better(y, x, i, j) == 1) {
              this->y -= 1;

            }
            if (better(y, x, i, j) == 2) {
              this->y += 1;
            }
            if (better(y, x, i, j) == 3) {
              this->x -= 1;
            }
            if (better(y, x, i, j) == 4) {
              this->x += 1;
            }
            vlad = true;
            break;
          }

        }
        if (vlad)
          break;
      }
      if (m.m[y][x] == enem) {
        isl = false;
        m.m[y][x] = enem;
      }
      if (m.m[y][x] == point) {
        for (int qi = 0; qi < 100; qi++)
          for (int qj = 0; qj < 100; qj++) {
            if (B.po(qi, qj)) {
              if (B.a[qi][qj].gety() == y && B.a[qi][qj].getx() == x) {
                B.del(m, B, qi, qj);
                isl = false;
                m.m[y][x] = bl;
              }
            }
          }

      }

      if (m.m[y][x] == bl) {
        isl = false;
      }

      if (m.m[y][x] == pas) {
        m.m[y][x] = enem;
      }
      if (m.m[y][x] == vishnya) {
        k++;
        m.m[y][x] = enem;
      }

    }
  }
};
int countp(body& b) {
  int x = 0;
  for (int qi = 0; qi < 100; qi++)
    for (int qj = 0; qj < 100; qj++) {
      if (b.po(qi, qj)) {
        x++;
      }

    }
  return x;
}
int main() {

  poin p;
  int x, y;
  bool f = true;
  cout << "razmer karti 2x(10-60) or -1 -1 for Settings\n";
  while (f) {
    cin >> x >> y;
    if (x * y < 2500)
      f = false;
    else {
      cout << "Vi eban? Menshe sdelay durak";
    }
  }
  if (x == -1 && y == -1) {
    cout << "block \n pusto \n body \n visnya \n enem \n";
    cin >> bl >> pas >> point >> vishnya >> enem;
    cin >> x >> y;
  }
  int h = x;
  int w = y;
  p.sx(y / 2);
  p.sy(x / 2);
  ma m(x, y);
  body B(p);
  m.vis(rand() % h, rand() % w, &k);
  m.refact(m, B, 0, 0);
  m.co();
  badboy badas[1000];
  char c;
  int s = 0;
  badas[0].isa(w, h);
  int l = 1;
  int botis = 1;
  while (true) {
    player = countp(B);
    s += player;
    if (player == 0) {
      system("cls");
      cout << " LOSE  LOSE  LOSE  LOSE  LOSE  LOSE  LOSE  LOSE  LOSE  LOSE "
           << endl;
      cout << "                        SCROE : " << l << endl;
      cout << " LOSE  LOSE  LOSE  LOSE  LOSE  LOSE  LOSE  LOSE  LOSE  LOSE "
           << endl;
      cout << "                        SCORE : " << l << endl;
      cout << " LOSE  LOSE  LOSE  LOSE  LOSE  LOSE  LOSE  LOSE  LOSE  LOSE "
           << endl;
      cout << "                        SCORE : " << l << endl;
      cout << " LOSE  LOSE  LOSE  LOSE  LOSE  LOSE  LOSE  LOSE  LOSE  LOSE "
           << endl;
      cin >> s;
      cin >> s;
      cin >> s;
      cin >> s;
      cin >> s;
      return 0;
    }
    cin >> c;

    srand(time(NULL));

    if (k)
      m.vis(rand() % h, rand() % w, &k);
    if (c == 'w') {
      m.refact(m, B, -1, 0);
    }

    if (c == 's') {
      m.refact(m, B, 1, 0);
    }
    if (c == 'd') {
      m.refact(m, B, 0, 1);
    }
    if (c == 'a') {
      m.refact(m, B, 0, -1);
    }

    if (l % 5 == 0) {
      botis++;

    }
    if (l % 2 == 0) {
      for (int i = 0; i < botis; i++) {
        if (badas[i].isl == false)
          badas[i].isa(w, h);
        badas[i].recoll(m, B);
      }
      l++;
    } else {
      l++;
    }
    m.co();
    cout << endl << "round : " << l << endl;
  }
  return 0;
}
