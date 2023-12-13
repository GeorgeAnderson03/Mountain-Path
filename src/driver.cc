#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
int main() {
  ElevationDataset dataset = {
      "/home/vagrant/src/mp-mountain-paths-GeorgeAnderson2021/example-data/"
      "ex_input_data/all-tie-row1-2w-3h.dat",
      2,
      3};
  GrayscaleImage image = {dataset};
  image.ToPpm("name.ppm");
  return 0;
}