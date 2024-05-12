#ifndef SMARTCALC_MODEL_MODELCREDIT_H_
#define SMARTCALC_MODEL_MODELCREDIT_H_

#include <cstdint>
#include <utility>

namespace s21 {

class CreditCalc {
 public:
  void SetAmount(double a) noexcept;
  void SetDuration(uint32_t d) noexcept;
  void SetRate(double r) noexcept;

  void AnnuityCredit(double& monthlyPayment, double& interestCharges,
                     double& totalPayment) const noexcept;
  void DiffCredit(double& firstPayment, double& lastPayment,
                  double& interestCharges, double& totalPayment) const noexcept;

 private:
  double amount_ = 0;
  uint32_t duration_ = 0;
  double rate_ = 0;
};

}  // namespace s21

#endif  // SMARTCALC_MODEL_MODELCREDIT_H_
