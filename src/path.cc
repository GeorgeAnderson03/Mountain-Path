#include "path.hpp"
Path::Path(size_t length, size_t starting_row) {
  std::vector<size_t> path(length);
  path_ = path;
  length_ = length;
  starting_row_ = starting_row;
}
void Path::IncEleChange(unsigned int value) {
  if (value >= 0) {
    ele_change_ += value;
  }
}
void Path::SetLoc(size_t col, size_t row) { path_.at(col) = row; }