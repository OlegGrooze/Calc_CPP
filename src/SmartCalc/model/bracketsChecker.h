#ifndef SMARTCALC_MODEL_BRACKETSCHECKER_H_
#define SMARTCALC_MODEL_BRACKETSCHECKER_H_

#include <stack>
#include <string>

#include "model/exception.h"

namespace s21 {

class BracketsChecker {
 public:
  explicit BracketsChecker(const std::string& s) : str_(s) {}

  void Check() const {
    std::stack<char> br;
    for (uint32_t i = 0; i < str_.size(); ++i) {
      if (str_[i] == '(') {
        br.push(str_[i]);
      }
      if (str_[i] == ')') {
        if (br.empty()) {
          throw(s21::Exception("Неправильная расстановка скобок"));
        } else {
          br.pop();
        }
      }
      if (i > 0 && str_[i] == '(' && str_[i - 1] == ')') {
        throw(s21::Exception("Неправильная расстановка скобок"));
      }
      if (i > 0 && str_[i] == ')' && str_[i - 1] == '(') {
        throw(s21::Exception("Неправильная расстановка скобок"));
      }
    }
    if (!br.empty()) {
      throw(s21::Exception("Неправильная расстановка скобок"));
    }
  }

 private:
  std::string str_;
};
}  // namespace s21

#endif  // SMARTCALC_MODEL_BRACKETSCHECKER_H_
