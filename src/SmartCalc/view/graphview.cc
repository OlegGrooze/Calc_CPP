#include "view/graphview.h"

#include <memory>
#include <utility>
#include <vector>

#include "./ui_graphview.h"

void ConvertStdToQ(const std::vector<std::pair<double, double>>& stdv,
                   QVector<double>& vX, QVector<double>& vY) {
  for (uint32_t i = 0; i < stdv.size(); ++i) {
    vX[i] = stdv[i].first;
    vY[i] = stdv[i].second;
  }
}

s21::GraphView::GraphView(std::string& lexeme, QWidget* parent)
    : QDialog(parent),
      ui(new Ui::GraphView),
      lexeme_(lexeme),
      validateDouble_(std::make_unique<QRegularExpressionValidator>(
          QRegularExpression("^[+-]?[0-9]+([.][0-9]+)?$"), this)) {
  ui->setupUi(this);
  result.resize(kPointsQuantity);
  InitCalc();
  PrintGraph();
}

s21::GraphView::~GraphView() { delete ui; }

void s21::GraphView::InitCalc() {
  contGraph_.SetLexeme(lexeme_);
  contGraph_.SetPointsQuantity(kPointsQuantity);
  contGraph_.SetXMin(xMin_);
  contGraph_.SetXMax(xMax_);
  contGraph_.CountGraph(result);
}

void s21::GraphView::PrintGraph() {
  QPen pen(Qt::red, 0, Qt::DotLine);
  QVector<double> vX(kPointsQuantity), vY(kPointsQuantity);
  ConvertStdToQ(result, vX, vY);

  ui->widget->clearGraphs();
  ui->widget->addGraph();
  ui->widget->graph(0)->setData(vX, vY);
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(
      QCPScatterStyle::ssCircle, QPen(Qt::darkCyan), QBrush(Qt::darkRed), 2));
  ui->widget->xAxis->setLabel("X");
  ui->widget->yAxis->setLabel("Y");
  ui->widget->xAxis->setLabelColor(Qt::darkMagenta);
  ui->widget->yAxis->setLabelColor(Qt::darkMagenta);
  ui->widget->xAxis->grid()->setPen(pen);
  ui->widget->yAxis->grid()->setPen(pen);
  ui->widget->xAxis->setRange(xMin_, xMax_);
  ui->widget->yAxis->setRange(yMin_, yMax_);
  ui->widget->replot();
  ui->widget->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag |
                              QCP::iSelectPlottables);
  ui->widget->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
  ui->widget->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
}

void s21::GraphView::on_button_count_clicked() {
  xMin_ = ui->line_xmin->text().toDouble();
  xMax_ = ui->line_xmax->text().toDouble();
  yMin_ = ui->line_ymin->text().toDouble();
  yMax_ = ui->line_ymax->text().toDouble();

  contGraph_.SetXMin(xMin_);
  contGraph_.SetXMax(xMax_);
  contGraph_.ChangeScale(result);
  PrintGraph();
}
