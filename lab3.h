#ifndef LAB3_H
#define LAB3_H

#include <QWidget>

namespace Ui {
class Lab3;
}

class Lab3 : public QWidget {
  Q_OBJECT

public:
  explicit Lab3(QWidget *parent = nullptr);
  ~Lab3();

private:
  Ui::Lab3 *ui;
};

#endif // LAB3_H
