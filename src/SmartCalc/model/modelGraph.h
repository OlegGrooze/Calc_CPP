#ifndef SMARTCALC_MODEL_MODELGRAPH_H_
#define SMARTCALC_MODEL_MODELGRAPH_H_

#include <utility>
#include <vector>

#include "model/modelCalc.h"

namespace s21 {

class GraphCalc : public SmartCalc {
 public:
  void SetPointsQuantity(uint32_t q) noexcept;
  void SetXMin(double x) noexcept;
  void SetXMax(double x) noexcept;
  void CreateGraph(std::vector<std::pair<double, double>>& result);
  void CountPoints(std::vector<std::pair<double, double>>& result);

 private:
  double xMin_ = -10.;
  double xMax_ = 10.;
  uint32_t pointsQuantity_ = 10000;
};

}  // namespace s21

#endif  // SMARTCALC_MODEL_MODELGRAPH_H_
