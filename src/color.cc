#include "color.hpp"

#include <stdexcept>

Color::Color(int r, const int kG, int b): red_(r), green_(kG), blue_(b) {
  // need to ensure valid color has been constructed...
  const int kMagic = 255;
  if (r < 0 || r > kMagic) {
    throw std::invalid_argument("invalid range");
  }
  if (kG < 0 || kG > kMagic) {
    throw std::invalid_argument("invalid range");
  }
  if (b < 0 || b > kMagic) {
    throw std::invalid_argument("invalid range");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}