#include "lab3.h"
#include "lab3diophantus.h"
#include "lab3fermat.h"
#include "lab3perceptron.h"
#include "ui_lab3.h"
#include <QMessageBox>
#define measure(obj, method, unit)\
  [obj]() {\
    auto start = std::chrono::high_resolution_clock::now();\
    obj.method();\
    return std::chrono::duration_cast<std::chrono::unit>(\
    std::chrono::high_resolution_clock::now() - start).count();\
  }()
std::random_device rd;
Lab3::Lab3(QWidget *parent) : QWidget(parent), ui(new Ui::Lab3) {
  ui->setupUi(this);
  ui->aSpinBox->setValue(std::uniform_int_distribution(1, 5)(rd));
  ui->bSpinBox->setValue(std::uniform_int_distribution(1, 5)(rd));
  ui->cSpinBox->setValue(std::uniform_int_distribution(1, 5)(rd));
  ui->dSpinBox->setValue(std::uniform_int_distribution(1, 5)(rd));
  ui->eqSpinBox->setValue(std::uniform_int_distribution(20, 50)(rd));
  connect(ui->fermatPushButton, &QPushButton::pressed, [this]() {
    auto input = ui->fermatInput->value();
    auto res = fermatFactorize(input);
    auto message = new QMessageBox(this);
    message->setText(QString::number(res.first) + " x " +
                     QString::number(res.second) + " = " +
                     QString::number(input));
    message->show();
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
    Diophantus medium({ui->aSpinBox->value(), ui->bSpinBox->value(),
                       ui->cSpinBox->value(), ui->dSpinBox->value()},
                       ui->eqSpinBox->value());
    Diophantus large({ui->aSpinBox->value(), ui->bSpinBox->value(),
                      ui->cSpinBox->value(), ui->dSpinBox->value()},
                      ui->eqSpinBox->value(), 5);
    auto start = std::chrono::high_resolution_clock::now();
    medium.solve();
    auto mediumTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    start = std::chrono::high_resolution_clock::now();
    large.solve();
    auto largeTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    auto message = new QMessageBox(this);
    message->setText("Time with normal population: " + QString::number(mediumTime) +
                     " ms\nTime with bigger population: " + QString::number(largeTime)
                     + " ms\nIncrease is " + (largeTime < mediumTime ? "positive" : "negative"));
    message->show();
  });
}

Lab3::~Lab3() { delete ui; }
