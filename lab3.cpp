#include "lab3.h"
#include "lab3diophantus.h"
#include "lab3fermat.h"
#include "lab3perceptron.h"
#include "ui_lab3.h"

Lab3::Lab3(QWidget *parent) : QWidget(parent), ui(new Ui::Lab3) {
  ui->setupUi(this);
  connect(ui->fermatPushButton, &QPushButton::pressed, [this]() {
    auto input = ui->fermatInput->value();
    auto res = fermatFactorize(input);
    ui->fermatMult->setDigitCount(log10(input) + 1);
    ui->fermatMult->display(input);
    ui->fermatFact1->setDigitCount(log10(res.first) + 1);
    ui->fermatFact1->display(res.first);
    ui->fermatFact2->setDigitCount(log10(res.second) + 1);
    ui->fermatFact2->display(res.second);
  });
  connect(ui->pPushButton, &QPushButton::pressed, [this]() {
    Perceptron p(ui->pThreshold->value(), ui->pLearningRate->value());
    auto res = QString::number(
        p.learn({{0, 6}, {3, 3}, {1, 5}, {2, 4}}, ui->pDeadline->value()));
    ui->pAccuracy->setDigitCount(res.length());
    ui->pAccuracy->display(res);
  });
  connect(ui->dPushButton, &QPushButton::pressed, [this]() {
    auto res = Diophantus({ui->aSpinBox->value(), ui->bSpinBox->value(),
                           ui->cSpinBox->value(), ui->dSpinBox->value()},
                          ui->eqSpinBox->value())
                   .solve();
    ui->aLcdNumber->display(res[0]);
    ui->bLcdNumber->display(res[1]);
    ui->cLcdNumber->display(res[2]);
    ui->dLcdNumber->display(res[3]);
  });
}

Lab3::~Lab3() { delete ui; }
