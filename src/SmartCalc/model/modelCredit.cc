#include "model/modelCredit.h"

#include <cmath>

void s21::CreditCalc::SetAmount(double a) noexcept { amount_ = a; }

void s21::CreditCalc::SetDuration(uint32_t d) noexcept { duration_ = d; }

void s21::CreditCalc::SetRate(double r) noexcept { rate_ = r; }

void s21::CreditCalc::AnnuityCredit(double& monthlyPayment,
                                    double& interestCharges,
                                    double& totalPayment) const noexcept {
  double mRate = rate_ / 1200.;

  monthlyPayment = (mRate * std::pow(1 + mRate, duration_)) /
                   (std::pow(1 + mRate, duration_) - 1) * amount_;
  totalPayment = monthlyPayment * duration_;
  interestCharges = totalPayment - amount_;
}

void s21::CreditCalc::DiffCredit(double& firstPayment, double& lastPayment,
                                 double& interestCharges,
                                 double& totalPayment) const noexcept {
  double mainPayment = amount_ / duration_;
  totalPayment = 0;

  for (uint32_t i = 0; i < duration_; ++i) {
    double remainder = amount_ - mainPayment * i;
    double ratePayment = remainder * rate_ / 1200.;
    interestCharges += ratePayment;
    if (i == 0) {
      firstPayment = mainPayment + ratePayment;
    }
    if (i == duration_ - 1) {
      lastPayment = mainPayment + ratePayment;
    }
  }
  totalPayment = amount_ + interestCharges;
}
