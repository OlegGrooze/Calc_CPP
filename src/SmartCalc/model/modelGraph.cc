#include "model/modelGraph.h"

#include <utility>
#include <vector>

void s21::GraphCalc::SetPointsQuantity(uint32_t q) noexcept {
  pointsQuantity_ = q;
}

void s21::GraphCalc::SetXMin(double x) noexcept { xMin_ = x; }

void s21::GraphCalc::SetXMax(double x) noexcept { xMax_ = x; }

void s21::GraphCalc::CreateGraph(
    std::vector<std::pair<double, double>>& result) {
  PostfixNotation();
  CountPoints(result);
}

void s21::GraphCalc::CountPoints(
    std::vector<std::pair<double, double>>& result) {
  double step = (xMax_ - xMin_) / (static_cast<double>(pointsQuantity_) - 1);

  for (uint32_t i = 0; i < pointsQuantity_; ++i) {
    arg_ = xMin_;
    result[i].first = xMin_;
    result[i].second = CountNotation();
    xMin_ += step;
  }
}
