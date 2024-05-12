#ifndef SMARTCALC_VIEW_GRAPHVIEW_H
#define SMARTCALC_VIEW_GRAPHVIEW_H

#include <QDialog>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "./qcustomplot.h"
#include "controller/controllerGraph.h"

namespace Ui {
class GraphView;
}

namespace s21 {

class GraphView : public QDialog {
  Q_OBJECT

 public:
  explicit GraphView(std::string &lexeme, QWidget *parent = nullptr);
  ~GraphView();

 private slots:

  void on_button_count_clicked();

 private:
  const uint32_t kPointsQuantity = 10000.;

  // void SetValidators();

  void InitCalc();

  void PrintGraph();

  Ui::GraphView *ui;
  std::vector<std::pair<double, double>> result;
  std::string lexeme_;
  double xMin_ = -10., xMax_ = 10., yMin_ = -10., yMax_ = 10.;
  s21::ControllerGraph contGraph_;

  std::unique_ptr<QRegularExpressionValidator> validateDouble_;
};

}  // namespace s21

#endif  // SMARTCALC_VIEW_GRAPHVIEW_H
