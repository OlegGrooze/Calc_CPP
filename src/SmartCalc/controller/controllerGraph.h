/*!
\file
\brief Header file with realisation of Graph Controller
*/
#ifndef SRC_CONTROLLER_CONTROLLERGRAPH_H_
#define SRC_CONTROLLER_CONTROLLERGRAPH_H_

#include <string>
#include <utility>
#include <vector>

#include "model/modelGraph.h"

namespace s21 {
/*!
\brief Class of controller for Graph calculator
\author wilmerno
\version 1.0
\date 11/2023
*/
class ControllerGraph {
 public:
  void SetLexeme(std::string& l) { calc_.SetLexeme(l); }

  void SetArg(double a) { calc_.SetArg(a); }

  void SetXMin(double x) { calc_.SetXMin(x); }

  void SetXMax(double x) { calc_.SetXMax(x); }

  void SetPointsQuantity(uint32_t q) { calc_.SetPointsQuantity(q); }

  void CountGraph(std::vector<std::pair<double, double>>& result) {
    calc_.CreateGraph(result);
  }

  void ChangeScale(std::vector<std::pair<double, double>>& result) {
    calc_.CountPoints(result);
  }

 private:
  GraphCalc calc_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLERGRAPH_H_
