#ifndef LAB2_H
#define LAB2_H

#include <QWidget>

namespace Ui {
class Lab2;
}

class Lab2 : public QWidget
{
    Q_OBJECT
public:
    explicit Lab2(QWidget *parent = nullptr);
    ~Lab2();

private:
    Ui::Lab2 *ui;
};

#endif // LAB2_H
