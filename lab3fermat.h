#ifndef LAB3FERMAT_H
#define LAB3FERMAT_H
#include <QtMath>
template <typename T> std::pair<T, T> fermatFactorize(T n) {
  T x = ceil(sqrt(n));
  if (x * x == n)
    return std::make_pair(x, x);
  while (true) {
    T k = floor(sqrt(x * x - n));
    if (k * k == x * x - n)
      return std::make_pair(x - k, x + k);
    ++x;
  }
}
#endif // LAB3FERMAT_H
