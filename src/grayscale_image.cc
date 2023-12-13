#include "grayscale_image.hpp"

#include <cmath>
#include <fstream>

#include "color.hpp"
#include "elevation_dataset.hpp"
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  width_ = dataset.Width();
  height_ = dataset.Height();
  double maxele = dataset.MaxEle();
  double minele = dataset.MinEle();
  int shade_of_gray = 0;
  for (unsigned long i = 0; i < dataset.Height(); i++) {
    std::vector<Color> colorvector;
    for (unsigned long j = 0; j < dataset.Width(); j++) {
      if (maxele == minele) {
        shade_of_gray = 0;
      } else {
        shade_of_gray = std::round((double((dataset.DatumAt(i, j) - minele)) /
                                    double((maxele - minele))) *
                                   double(kMaxColorValue));
      }
      Color color = Color(shade_of_gray, shade_of_gray, shade_of_gray);
      colorvector.push_back(color);
    }
    image_.push_back(colorvector);
  }
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height) {
  ElevationDataset dataset = ElevationDataset(filename, width, height);
  width_ = dataset.Width();
  height_ = dataset.Height();
  int maxele = dataset.MaxEle();
  int minele = dataset.MinEle();
  int shade_of_gray = 0;
  for (unsigned long i = 0; i < dataset.Height(); i++) {
    std::vector<Color> colorvector;
    for (unsigned long j = 0; j < dataset.Width(); j++) {
      if (maxele == minele) {
        shade_of_gray = 0;
      } else {
        shade_of_gray = std::round((double((dataset.DatumAt(i, j) - minele)) /
                                    double((maxele - minele))) *
                                   double(kMaxColorValue));
      }
      Color color = Color(shade_of_gray, shade_of_gray, shade_of_gray);
      colorvector.push_back(color);
    }
    image_.push_back(colorvector);
  }
}

const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_.at(row).at(col);
}
void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream out(name);
  if (out.is_open()) {
    out << "P3" << std::endl;
    out << width_ << " " << height_ << std::endl;
    out << kMaxColorValue << std::endl;
    for (unsigned long i = 0; i < height_; i++) {
      for (unsigned long j = 0; j < width_; j++) {
        out << image_.at(i).at(j).Red() << " " << image_.at(i).at(j).Green()
            << " " << image_.at(i).at(j).Blue() << std::endl;
      }
      out << '\n';
    }
  }
}
