#ifndef SMARTCALC_MODEL_MODELCALC_H_
#define SMARTCALC_MODEL_MODELCALC_H_

#include <string>
#include <utility>
#include <vector>

#include "model/exception.h"
#include "model/stringTokenizer.h"
#include "model/token.h"

namespace s21 {

class SmartCalc {
 public:
  SmartCalc() = default;
  explicit SmartCalc(const std::string& l, double arg);

  void SetLexeme(const std::string& l) noexcept;
  void SetArg(const double arg) noexcept;
  double CountLexeme();

 protected:
  void PostfixNotation();
  double CountNotation();
  void ClearStructures() noexcept;

  std::string lexeme_;
  double arg_ = 0;
  std::vector<Token> tokens_;
  std::vector<Token> notation_;
  uint32_t pointsQuantity = 100000.;
};

}  // namespace s21

#endif  // SMARTCALC_MODEL_MODELCALC_H_
