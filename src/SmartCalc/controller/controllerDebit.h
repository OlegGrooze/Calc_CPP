#ifndef SRC_CONTROLLER_CONTROLLERDEBIT_H_
#define SRC_CONTROLLER_CONTROLLERDEBIT_H_

#include "../model/modelDebit.h"

namespace s21 {

class ControllerDebit {
 public:
  void SetAmount(double a) noexcept { calc_.SetAmount(a); }

  void SetDuration(uint32_t d) noexcept { calc_.SetDuration(d); }

  void SetRate(double r) noexcept { calc_.SetRate(r); }

  void SetTaxRate(double t) noexcept { calc_.SetTaxRate(t); }

  void SetReplanishment(uint32_t r) noexcept { calc_.SetReplanishment(r); }

  void SetReplanishmentAmount(double r) noexcept {
    calc_.SetReplanishmentAmount(r);
  }

  void SetWithdrawal(uint32_t w) noexcept { calc_.SetWithdrawal(w); }

  void SetWithdrawalAmount(double w) noexcept { calc_.SetWithdrawalAmount(w); }

  void SetCapitalization(bool c) noexcept { calc_.SetCapitalization(c); }

  void SetPaymentPeriod(uint32_t p) noexcept { calc_.SetPaymentPeriod(p); }

  void CountDebit(double& interestCharges, double& taxAmount,
                  double& depAmount) noexcept {
    return calc_.CountDebit(interestCharges, taxAmount, depAmount);
  }

 private:
  DebitCalc calc_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLERDEBIT_H_
