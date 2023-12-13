#include "elevation_dataset.hpp"

#include <fstream>

ElevationDataset::ElevationDataset(const std::string& filename,
                                   const size_t kWidth,
                                   size_t height) {
  std::fstream ifs(filename);
  width_ = kWidth;
  height_ = height;
  int min = INT32_MAX;
  int max = INT32_MIN;
  int value = 0;
  int temp = 0;
  if (ifs.is_open()) {
  } else {
    throw std::invalid_argument("a");
  }
  for (unsigned long i = 0; i < height_; i++) {
    std::vector<int> vector;
    for (unsigned long j = 0; j < width_; j++) {
      ifs >> value;
      if (!(ifs.fail())) {
        if (value < min) {
          min = value;
        }
        if (value > max) {
          max = value;
        }
        vector.push_back(value);
      } else {
        throw std::invalid_argument("incorrect numbers");
      }
    }
    data_.push_back(vector);
  }
  ifs >> temp;
  if (!(ifs.fail())) {
    throw std::invalid_argument("something at the end of the file");
  }
  max_ele_ = max;
  min_ele_ = min;
}
