#include <QApplication>
#include <QLocale>

#include "view/view.h"

int main(int argc, char *argv[]) {
  QLocale::setDefault(QLocale::c());
  QApplication a(argc, argv);
  s21::View w(nullptr);
  w.show();
  return a.exec();
}
