#ifndef SRC_CONTROLLER_CONTROLLERCALC_H_
#define SRC_CONTROLLER_CONTROLLERCALC_H_

#include <string>

#include "../model/modelCalc.h"

namespace s21 {

class ControllerCalc {
 public:
  void SetLexeme(std::string& l) { calc_.SetLexeme(l); }

  void SetArg(double a) { calc_.SetArg(a); }

  double Count() { return calc_.CountLexeme(); }

 private:
  SmartCalc calc_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLERCALC_H_
