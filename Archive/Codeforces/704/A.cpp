// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct Event {
  Event* nextSame;
  bool read;
};

const int MAXN = 300000;

Event events[MAXN];
Event* headApp[MAXN];
Event* lastApp[MAXN];
int res;

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  memset(headApp, 0, sizeof(Event*) * n);
  memset(lastApp, 0, sizeof(Event*) * n);
  res = 0;
  int eventPnt = 0, lastEventPnt = 0;
  FOR(_, 0, q) {
    int op, x;
    io::readInt(op);
    io::readInt(x);
    --x;
    if (op == 1) {
      auto& event = events[eventPnt];
      event.read = false;
      ++res;
      if (!lastApp[x]) {
        headApp[x] = lastApp[x] = &event;
      } else {
        lastApp[x]->nextSame = &event;
        lastApp[x] = &event;
      }
      ++eventPnt;
    } else if (op == 2) {
      for (; headApp[x]; headApp[x] = headApp[x]->nextSame) {
        if (!headApp[x]->read) {
          headApp[x]->read = true;
          --res;
        }
        if (!headApp[x]->nextSame) {
          break;
        }
      }
    } else {
      for (; lastEventPnt <= x; ++lastEventPnt) {
        if (!events[lastEventPnt].read) {
          events[lastEventPnt].read = true;
          --res;
        }
      }
    }
    io::writeInt(res);
    io::writeChar('\n');
  }
}
