#pragma once

#include "math/gcd/ext_gcd.h"

namespace math {

// Number of integer solutions of ax+by=c,
//   where x_min<=x<=x_max and y_min<=y<=y_max
inline long long linearDiophantineSolutionCount(
    long long a,
    long long b,
    const long long& c,
    long long xmin,
    long long xmax,
    long long ymin,
    long long ymax) {
  if (xmin > xmax || ymin > ymax) {
    return 0;
  }
  long long xCount = xmax - xmin + 1;
  long long yCount = ymax - ymin + 1;
  if (!a && !b) {
    return c ? 0 : xCount * yCount;
  }
  if (!a) {
    if (c % b) {
      return 0;
    }
    long long y = c / b;
    return ymin <= y && y <= ymax ? xCount : 0;
  }
  if (!b) {
    if (c % a) {
      return 0;
    }
    long long x = c / a;
    return xmin <= x && x <= xmax ? yCount : 0;
  }
  bool negativeA = false;
  if (a < 0) {
    negativeA = true;
    a = -a;
  }
  bool negativeB = false;
  if (b < 0) {
    negativeB = true;
    b = -b;
  }
  long long x, y;
  long long gcd = math::extGcd(a, b, x, y);
  if (c % gcd) {
    return 0;
  }
  if (negativeA) {
    swap(xmin, xmax);
    xmin = -xmin;
    xmax = -xmax;
  }
  if (negativeB) {
    swap(ymin, ymax);
    ymin = -ymin;
    ymax = -ymax;
  }
  long long mul = c / gcd;
  x *= mul;
  y *= mul;
  long long dx = b / gcd, dy = a / gcd;
  auto shift = [&x, &y, &dx, &dy](const long long& delta) {
    x += delta * dx;
    y -= delta * dy;
  };
  if (x < xmin) {
    shift((xmin - x + dx - 1) / dx);
  } else {
    shift(-((x - xmin) / dx));
  }
  if (x > xmax || y < ymin) {
    return 0;
  }
  // shift Y down to maximum value in the range
  if (y > ymax) {
    shift((y - ymax + dy - 1) / dy);
  }
  if (xmax < x || y < ymin) {
    return 0;
  }
  return min((xmax - x) / dx, (y - ymin) / dy) + 1;
}

} // namespace math
