// !macro_gen
// ALL CALENDAR_ALL

#include "misc/calendar_macros.h"

using namespace std;

namespace misc {

#ifdef CALENDAR_DAYS_PER_MONTH // ^
const int DAYS[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
#endif

#ifdef CALENDAR_IS_LEAP_YEAR // ^
inline bool isLeapYear(int y) {
  return (!(y & 3) && y % 100) || !(y % 400);
}
#endif

} // namespace misc
