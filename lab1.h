#ifndef LAB1_H
#define LAB1_H

#include <QWidget>

namespace Ui {
class Lab1;
}

class Lab1 : public QWidget
{
    Q_OBJECT
public:
    explicit Lab1(QWidget *parent = nullptr);
    ~Lab1();

private:
    Ui::Lab1 *ui;
};

#endif // LAB1_H
