namespace math {

template<typename T = double>
class Complex {
public:
  inline Complex(const T& real = 0, const T& imag = 0) : real_(real), imag_(imag) {}

  inline Complex<T> operator*(const Complex<T>& o) {
    return Complex(
        real_ * o.real_ - imag_ * o.imag_,
        real_ * o.imag_ + imag_ * o.real_);
  }

  inline void operator+=(const Complex<T>& o) {
    real_ += o.real_;
    imag_ += o.imag_;
  }

  inline void operator/=(const T& scale) {
    real_ /= scale;
    imag_ /= scale;
  }

  inline void init(const T& real = 0, const T& imag = 0) {
    real_ = real;
    imag_ = imag;
  }

  inline void initPolar(const T& r, const T& theta) {
    real_ = r * cos(theta);
    imag_ = r * sin(theta);
  }

  inline void initMul(const Complex<T>& x, const Complex<T>& y) {
    real_ = x.real_ * y.real_ - x.imag_ * y.imag_;
    imag_ = x.real_ * y.imag_ + x.imag_ * y.real_;
  }

  inline void initSub(const Complex<T>& x, const Complex<T>& y) {
    real_ = x.real_ - y.real_;
    imag_ = x.imag_ - y.imag_;
  }

  inline T real() const { return real_; }
  inline T imag() const { return imag_; }
private:
  T real_;
  T imag_;
}; // class Complex
} // namespace math
