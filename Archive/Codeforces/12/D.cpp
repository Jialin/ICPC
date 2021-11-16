// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define STAIR_CONTAINER_IS_FULLY_INSIDE
#define STAIR_CONTAINER_UPDATE
#include "ds/stair_container_macros.h"

#include "ds/stair_container.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct Person {
  int x, y, z;

  inline bool operator<(const Person& o) const {
    return x > o.x || (x == o.x && (y < o.y || (y == o.y && z < o.z)));
  }
};

const int MAXN = 500000;

int n;
Person persons[MAXN];

int main() {
  io::readInt(n);
  FOR(i, 0, n) {
    io::readInt(persons[i].x);
  }
  FOR(i, 0, n) {
    io::readInt(persons[i].y);
  }
  FOR(i, 0, n) {
    io::readInt(persons[i].z);
  }
  sort(persons, persons + n);
  ds::StairContainer<int> stairs;
  int res = 0;
  FOR(i, 0, n) {
    const auto& person = persons[i];
    if (stairs.isFullyInside(person.y, person.z)) {
      ++res;
    } else {
      stairs.update(person.y, person.z);
    }
  }
  io::writeInt(res);
  io::writeChar('\n');
}
