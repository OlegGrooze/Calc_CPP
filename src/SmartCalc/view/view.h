#ifndef SMARTCALC_VIEW_VIEW_H
#define SMARTCALC_VIEW_VIEW_H

#include <QMainWindow>
#include <memory>

#include "controller/controllerCalc.h"
#include "controller/controllerCredit.h"
#include "controller/controllerDebit.h"
#include "view/graphview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

typedef enum {
  kNone = 0,     ///> never or in the end
  kMonth = 1,    ///> every month
  kQuarter = 3,  ///> every quarter
  kHalf = 6,     ///> every half of the year
  kYear = 12     ///> every year
} Periodicity;

class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(QWidget *parent = nullptr);
  ~View();

 private slots:
  void PressCalc();
  void PressFunc();
  void on_button_ac_clicked();
  void on_button_backspace_clicked();
  void on_button_eq_clicked();
  void on_button_graph_clicked();
  void on_button_calculate_clicked();
  void on_button_calculate_depo_clicked();
  void on_combo_deposit_currentIndexChanged(int index);
  void on_combo_withdrawal_currentIndexChanged(int index);

 private:
  void SetValidators();
  void SetSlots();
  void AddShortcutForEq();
  bool CheckInputDeposit();
  uint32_t SetPeriodicity(int index);

  Ui::View *ui;
  GraphView *graph_;
  s21::ControllerCalc contCalc_;
  s21::ControllerCredit contCredit_;
  s21::ControllerDebit contDebit_;

  std::unique_ptr<QRegularExpressionValidator> validateDouble_;
  std::unique_ptr<QRegularExpressionValidator> validatePositiveDouble_;
  std::unique_ptr<QRegularExpressionValidator> validateInteger_;
};

}  // namespace s21
#endif  // SMARTCALC_VIEW_VIEW_H
