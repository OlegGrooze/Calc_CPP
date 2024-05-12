#ifndef SMARTCALC_MODEL_STRINGTOKENIZER_H_
#define SMARTCALC_MODEL_STRINGTOKENIZER_H_

#include <string>
#include <vector>

#include "model/exception.h"
#include "model/token.h"

namespace s21 {

class StringTokenizer {
 public:
  explicit StringTokenizer(std::string& l) : lexeme_(l) {}
  std::vector<Token> ParseLexeme();

 private:
  bool GetBrackets();
  bool GetFunction();
  bool GetNumber();
  bool GetOperator();
  bool GetVariable();

  std::string lexeme_;
  uint32_t lexIter_ = 0;
  std::vector<Token> tokens_;
};

}  // namespace s21

#endif  // SMARTCALC_MODEL_STRINGTOKENIZER_H_
