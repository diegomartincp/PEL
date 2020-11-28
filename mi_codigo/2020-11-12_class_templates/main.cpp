#include <iostream>
  template<typename T> // el parámetro T de la plantilla es un tipo...
      //requires std::floating_point<T> // ...sometido a una ligadura (C++20)
   class Complex {
      T re_,
        im_;
   public:
      constexpr Complex(T const& re = T{}, T const& im = T{}) noexcept
         : re_{re}, im_{im} { }

      // acceso:
      constexpr auto real() const noexcept -> T const& { return re_; }
      constexpr auto imag() const noexcept -> T const& { return im_; }
      constexpr void real(T const& re) noexcept { re_ = re; }
      constexpr void imag(T const& im) noexcept { im_ = im; }

      // norma al cuadrado, complejo conjugado y argumento:
      constexpr auto norm() const noexcept -> T       { return re_*re_ + im_*im_; }
      constexpr auto conj() const noexcept -> Complex { return {re_, -im_}; }
                //auto arg()  const noexcept -> T       { return std::atan2(im_, re_); }
                auto arg()  const noexcept -> T       { return {re_, -im_}; }
   };

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto a_1 = Complex<float>{3.0f, 4.0f};  // a_1 = (3,4) de tipo Complex<float>
    auto a_2 = Complex{3.0f, 4.0f};         // ídem
    auto n_a = a_1.norm();                  // n_a = 25.0f es de tipo float

    auto b_1 = Complex<double>{8.0, -3.0};  // b_1 = (8,-3) de tipo Complex<double>
    auto b_2 = Complex{8.0, -3.0};          // ídem
    auto n_b = b_1.norm();                  // n_b = 73.0 es de tipo double

    auto c_1 = Complex<long double>{-6.0L}; // c_1 = (-6,0) de tipo Complex<long double>
    auto c_2 = Complex{-6.0L};              // ídem
    auto n_c = c_1.norm();                  // n_c = 36.0L es de tipo long double

    return 0;
}
