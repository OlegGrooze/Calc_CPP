#include "view/view.h"

#include <QMessageBox>
#include <string>

#include "./ui_view.h"
#include "controller/controllerCalc.h"
#include "controller/controllerGraph.h"

s21::View::View(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::View),
      validateDouble_(std::make_unique<QRegularExpressionValidator>(
          QRegularExpression("^[+-]?[0-9]+([.][0-9]+)?$"), this)),
      validatePositiveDouble_(std::make_unique<QRegularExpressionValidator>(
          QRegularExpression("^[0-9]+([.][0-9]+)?$"), this)),
      validateInteger_(std::make_unique<QRegularExpressionValidator>(
          QRegularExpression("^[0-9]+$"), this)) {
  ui->setupUi(this);
  ui->line_sumdepo->hide();
  ui->line_sumwithdrawal->hide();
  ui->label_25->hide();
  ui->label_26->hide();
  SetValidators();
  SetSlots();
  AddShortcutForEq();
}

s21::View::~View() { delete ui; }

void s21::View::SetValidators() {
  ui->line_x->setValidator(validateDouble_.get());
  ui->line_sumdepo->setValidator(validatePositiveDouble_.get());
  ui->line_sumwithdrawal->setValidator(validatePositiveDouble_.get());
}

void s21::View::SetSlots() {
  for (auto el : {ui->button_openbracket, ui->button_closebracket,
                  ui->button_point,       ui->button_0,
                  ui->button_1,           ui->button_2,
                  ui->button_3,           ui->button_4,
                  ui->button_5,           ui->button_6,
                  ui->button_7,           ui->button_8,
                  ui->button_9,           ui->button_div,
                  ui->button_sum,         ui->button_sub,
                  ui->button_mul,         ui->button_mod,
                  ui->button_x,           ui->button_e}) {
    connect(el, SIGNAL(clicked()), this, SLOT(PressCalc()));
  }

  for (auto el :
       {ui->button_sqrt, ui->button_log, ui->button_ln, ui->button_sin,
        ui->button_cos, ui->button_tan, ui->button_asin, ui->button_acos,
        ui->button_atan, ui->button_pow}) {
    connect(el, SIGNAL(clicked()), this, SLOT(PressFunc()));
  }
}

void s21::View::AddShortcutForEq() {
  auto eqShortcut = new QAction(this);
  eqShortcut->setShortcuts({Qt::Key_Equal, Qt::Key_Return, Qt::Key_Enter});
  this->addAction(eqShortcut);
  auto f = [&]() { ui->button_eq->animateClick(); };
  connect(eqShortcut, &QAction::triggered, f);
}

void s21::View::PressCalc() {
  QPushButton *button = reinterpret_cast<QPushButton *>(sender());
  QString line;

  line = (ui->line_lexeme->text() + button->text());
  ui->line_lexeme->setText(line);
}

void s21::View::PressFunc() {
  QPushButton *button = reinterpret_cast<QPushButton *>(sender());
  QString line;

  line = (ui->line_lexeme->text() + button->text() + '(');
  ui->line_lexeme->setText(line);
}

void s21::View::on_button_eq_clicked() {
  QString xLine = ui->line_x->text();
  QString lexeme = ui->line_lexeme->text();

  if (lexeme.contains('x') && xLine.size() == 0) {
    QMessageBox::warning(this, "Ошибка", "Требуется аргумент");
    return;
  }

  if (lexeme.size() == 0) {
    QMessageBox::information(this, "Пустой ввод", "Введите значение!");
    return;
  }

  double xArg = xLine.toDouble();
  contCalc_.SetArg(xArg);
  std::string str = lexeme.toStdString();
  contCalc_.SetLexeme(str);
  try {
    double result = contCalc_.Count();
    ui->line_lexeme->setText(QString::number(result, 'g', 16));
  } catch (s21::Exception &e) {
    QMessageBox::warning(this, "Ошибка",
                         QString::fromStdString(e.GetMessage()));
  }
}

void s21::View::on_button_ac_clicked() { ui->line_lexeme->clear(); }

void s21::View::on_button_backspace_clicked() {
  QString str = ui->line_lexeme->text();
  if (!str.isEmpty()) {
    str.chop(1);
    ui->line_lexeme->setText(str);
  }
}

void s21::View::on_button_graph_clicked() {
  QString lexeme = ui->line_lexeme->text();
  if (lexeme.isEmpty()) {
    QMessageBox::information(this, "Пустой ввод", "Введите значение!");
    return;
  }
  std::string str = lexeme.toStdString();
  contCalc_.SetLexeme(str);
  try {
    contCalc_.Count();
    graph_ = new GraphView(str, nullptr);
    graph_->show();
  } catch (s21::Exception &e) {
    QMessageBox::warning(this, "Ошибка",
                         QString::fromStdString(e.GetMessage()));
  }
}

void s21::View::on_button_calculate_clicked() {
  if (ui->line_amount->text().isEmpty() ||
      ui->line_duration->text().isEmpty() || ui->line_rate->text().isEmpty()) {
    QMessageBox::information(
        this, "Какая-то графа пустая",
        "Недостаточно параметров!\nПожалуйста введите данные!");
    return;
  }

  contCredit_.SetAmount(ui->line_amount->text().toDouble());
  contCredit_.SetDuration(ui->line_duration->text().toUInt());
  contCredit_.SetRate(ui->line_rate->text().toDouble());

  double interestCharges, totalPayment;
  if (ui->radio_annuity->isChecked()) {
    double monthlyPayment;
    contCredit_.CountAnnuityCredit(monthlyPayment, interestCharges,
                                   totalPayment);
    ui->line_mpayment->setText(QString::number(monthlyPayment, 'f', 2));
  } else {
    double firstPayment, lastPayment;
    contCredit_.CountDiffCredit(firstPayment, lastPayment, interestCharges,
                                totalPayment);
    QString toPrint = (QString::number(firstPayment, 'f', 2) + " ... " +
                       QString::number(lastPayment, 'f', 2));
    ui->line_mpayment->setText(toPrint);
  }
  ui->line_charges->setText(QString::number(interestCharges, 'f', 2));
  ui->line_tpayment->setText(QString::number(totalPayment, 'f', 2));
}

void s21::View::on_button_calculate_depo_clicked() {
  if (!CheckInputDeposit()) {
    return;
  }

  contDebit_.SetAmount(ui->line_depamount->text().toDouble());
  contDebit_.SetDuration(ui->line_depperiod->text().toUInt());
  contDebit_.SetRate(ui->line_deprate->text().toDouble());
  contDebit_.SetTaxRate(ui->line_deptax->text().toDouble());
  contDebit_.SetReplanishment(
      SetPeriodicity(ui->combo_deposit->currentIndex()));
  contDebit_.SetReplanishmentAmount(ui->line_sumdepo->text().toDouble());
  contDebit_.SetWithdrawal(
      SetPeriodicity(ui->combo_withdrawal->currentIndex()));
  contDebit_.SetWithdrawalAmount(ui->line_sumwithdrawal->text().toDouble());
  contDebit_.SetCapitalization(ui->checkBox_capital->isChecked());
  contDebit_.SetPaymentPeriod(SetPeriodicity(ui->combo_period->currentIndex()));

  double interestCharges, taxAmount, depAmount;
  contDebit_.CountDebit(interestCharges, taxAmount, depAmount);

  ui->line_depcharges->setText(QString::number(interestCharges, 'f', 2));
  ui->line_deptaxamount->setText(QString::number(taxAmount, 'f', 2));
  ui->line_depamountsum->setText(QString::number(depAmount, 'f', 2));
}

bool s21::View::CheckInputDeposit() {
  bool result = true;
  bool rate = true;

  if (ui->line_depamount->text().isEmpty()) {
    result = false;
  }
  if (ui->line_depperiod->text().isEmpty()) {
    result = false;
  }
  if (ui->line_deprate->text().isEmpty()) {
    result = false;
  } else if (ui->line_deprate->text().toDouble() >= 100) {
    rate = false;
  }
  if (ui->line_deptax->text().isEmpty()) {
    result = false;
  } else if (ui->line_deptax->text().toDouble() >= 100) {
    rate = false;
  }

  if (!result) {
    QMessageBox::information(
        this, "Какая-то графа пустая",
        "Недостаточно параметров!\nПожалуйста введите данные!");
  } else if (!rate) {
    QMessageBox::information(this, "Какая-то графа пустая",
                             "Некорректное значение процентов.\n"
                             "Нужный диапазон от 0 до 100");
  }
  return result;
}

uint32_t s21::View::SetPeriodicity(int index) {
  unsigned value = 0;
  switch (index) {
    case 2:
      value = Periodicity::kQuarter;
      break;
    case 3:
      value = Periodicity::kHalf;
      break;
    case 4:
      value = Periodicity::kYear;
      break;
    default:
      value = index;
      break;
  }
  return value;
}

void s21::View::on_combo_deposit_currentIndexChanged(int index) {
  if (index != 0) {
    ui->line_sumdepo->show();
    ui->label_25->show();
    ui->line_sumdepo->setFocus();
  } else {
    ui->line_sumdepo->hide();
    ui->line_sumdepo->setText("");
    ui->label_25->hide();
  }
}

void s21::View::on_combo_withdrawal_currentIndexChanged(int index) {
  if (index != 0) {
    ui->line_sumwithdrawal->show();
    ui->label_26->show();
    ui->line_sumwithdrawal->setFocus();
  } else {
    ui->line_sumwithdrawal->hide();
    ui->line_sumwithdrawal->setText("");
    ui->label_26->hide();
  }
}
