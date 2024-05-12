#ifndef SMARTCALC_MODEL_EXCEPTION_H_
#define SMARTCALC_MODEL_EXCEPTION_H_

#include <string>

namespace s21 {

class Exception {
 public:
  explicit Exception(const std::string& msg) : msg_(msg) {}

  std::string GetMessage() const { return (msg_); }

 private:
  std::string msg_;
};
}  // namespace s21

#endif  //  SMARTCALC_MODEL_EXCEPTION_H_
