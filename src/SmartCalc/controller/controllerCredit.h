#ifndef SRC_CONTROLLER_CONTROLLERCREDIT_H_
#define SRC_CONTROLLER_CONTROLLERCREDIT_H_

#include "../model/modelCredit.h"

namespace s21 {

class ControllerCredit {
 public:
  void SetAmount(double a) noexcept { calc_.SetAmount(a); }

  void SetDuration(uint32_t d) noexcept { calc_.SetDuration(d); }

  void SetRate(double r) noexcept { calc_.SetRate(r); }

  void CountAnnuityCredit(double& monthlyPayment, double& interestCharges,
                          double& totalPayment) noexcept {
    calc_.AnnuityCredit(monthlyPayment, interestCharges, totalPayment);
  }

  void CountDiffCredit(double& firstPayment, double& lastPayment,
                       double& interestCharges, double& totalPayment) noexcept {
    calc_.DiffCredit(firstPayment, lastPayment, interestCharges, totalPayment);
  }

 private:
  CreditCalc calc_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLERCREDIT_H_
