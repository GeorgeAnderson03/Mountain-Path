#include "path_image.hpp"

#include <cmath>
#include <fstream>

Path Checks(size_t height,
            size_t width,
            const ElevationDataset& kDataset,
            unsigned int k) {
  unsigned int above = 0, next = 0, below = 0, sloweri = k;
  Path path = Path(width, k);
  path.SetLoc(0, k);
  for (unsigned int p = 0; p < width; ++p) {
    int currele = kDataset.DatumAt(sloweri, p);
    if (p + 1 < width) {
      next = abs(currele - kDataset.DatumAt(sloweri, p + 1));
      if (sloweri - 1 < height) {
        above = abs(currele - kDataset.DatumAt(sloweri - 1, p + 1));
      } else {
        above = INT32_MAX;
      }
      if (sloweri + 1 < height) {
        below = abs(currele - kDataset.DatumAt(sloweri + 1, p + 1));
      } else {
        below = INT32_MAX;
      }
      if (next < above && next < below) {
        path.IncEleChange(next);
        path.SetLoc(p + 1, sloweri);
      } else if (below < next && below < above) {
        sloweri++;
        path.IncEleChange(below);
        path.SetLoc(p + 1, sloweri);
      } else if (above < next && above < below) {
        sloweri--;
        path.IncEleChange(above);
        path.SetLoc(p + 1, sloweri);
      } else if ((next == above || next == below)) {
        path.IncEleChange(next);
        path.SetLoc(p + 1, sloweri);
      } else if (above == below && above < next) {
        sloweri++;
        path.IncEleChange(below);
        path.SetLoc(p + 1, sloweri);
      }
    }
  }
  return path;
}

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  width_ = image.Width();
  height_ = image.Height();
  for (unsigned long i = 0; i < height_; i++) {
    std::vector<Color> color;
    for (unsigned long j = 0; j < width_; j++) {
      color.push_back(image.ColorAt(i, j));
    }
    path_image_.push_back(color);
  }
  for (unsigned int i = 0; i < height_; i++) {
    paths_.push_back(Checks(height_, width_, dataset, i));
  }
  unsigned int first = paths_.at(0).EleChange();
  unsigned int bestpath = 0;
  for (unsigned int i = 0; i < height_; i++) {
    if (paths_.at(i).EleChange() <= first) {
      if (paths_.at(i).EleChange() != first) {
        first = paths_.at(i).EleChange();
        bestpath = i;
      }
    }
  }
  const Color kRed = Color(252, 25, 63);
  for (unsigned int i = 0; i < height_; i++) {
    for (unsigned int j = 0; j < width_; j++) {
      if (paths_.at(i).StartingRow() != bestpath) {
        path_image_.at(paths_.at(i).GetPath().at(j)).at(j) = kRed;
      }
    }
  }
  const Color kGreen = Color(31, 253, 13);
  for (unsigned int i = 0; i < height_; i++) {
    for (unsigned int j = 0; j < width_; j++) {
      if (paths_.at(i).StartingRow() == bestpath) {
        path_image_.at(paths_.at(i).GetPath().at(j)).at(j) = kGreen;
      }
    }
  }
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream out(name);
  if (out.is_open()) {
    out << "P3" << std::endl;
    out << width_ << " " << height_ << std::endl;
    out << kMaxColorValue << std::endl;
    for (unsigned long i = 0; i < height_; i++) {
      for (unsigned long j = 0; j < width_; j++) {
        out << path_image_.at(i).at(j).Red() << " "
            << path_image_.at(i).at(j).Green() << " "
            << path_image_.at(i).at(j).Blue() << std::endl;
      }
      out << '\n';
    }
  }
}
