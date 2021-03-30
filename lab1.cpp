#include "lab1.h"
#include "common.h"
#include "qcustomplot/qcustomplot.h"
#include "ui_lab1.h"

template <typename T>
using QVectorView =
    std::pair<QVector<double>::const_iterator, QVector<double>::const_iterator>;

double average(QVectorView<double> signal) {
  int n = 0;
  double sum = 0.0;
  for (auto value = signal.first; value < signal.second; ++value, ++n)
    sum += *value;
  return sum / n;
}
double dispersion(QVectorView<double> signal) {
  int n = 0;
  double sum = 0.0;
  double avg = average(signal);
  for (auto value = signal.first; value < signal.second; ++value, ++n)
    sum += pow(avg - *value, 2);
  return sum / n;
}
double correlation(QVectorView<double> signal1, QVectorView<double> signal2) {
  int n = 0;
  double sum = 0.0;
  double m1 = average(signal1);
  double m2 = average(signal2);
  auto s2 = signal2.first;
  for (auto s1 = signal1.first; s1 < signal1.second; ++s1, ++s2, ++n)
    sum += (*s1 - m1) * (*s2 - m2);
  return sum / n;
}

QVector<double> autocorrelation(const QVector<double> &signal) {
  int l = signal.length() / 2;
  QVector<double> res;
  for (int i = 0; i < l; ++i)
    res.push_back(correlation(
        std::make_pair(signal.begin(), signal.begin() + l),
        std::make_pair(signal.begin() + i, signal.begin() + i + l)));
  return res;
}
QVector<double> crosscorrelation(const QVector<double> &signal1,
                                 const QVector<double> &signal2) {
  QVector<double> res;
  int l = signal1.size() / 2;
  for (int i = 0; i < l; ++i)
    res.push_back(correlation(
        std::make_pair(signal1.begin(), signal1.begin() + l),
        std::make_pair(signal2.begin() + i, signal2.begin() + i + l)));
  return res;
}

Lab1::Lab1(QWidget *parent) : QWidget(parent), ui(new Ui::Lab1) {
  ui->setupUi(this);
  connect(ui->pushButton, &QPushButton::clicked, [this]() {
    auto signal = generate(ui->harmonics->value(), ui->frequency->value(),
                           ui->nInput->value());
    ui->average->setText(
        QString::number(average(std::make_pair(signal.begin(), signal.end()))));
    ui->dispersion->setText(QString::number(
        dispersion(std::make_pair(signal.begin(), signal.end()))));
    QVector<double> keys(signal.size());
    for (int i = 0; i < signal.size(); ++i)
      keys[i] = i;
    auto halfkeys =
        QVector<double>(keys.begin(), keys.begin() + (signal.size() / 2));
    auto plot = new QCustomPlot(this);
    plot->addGraph();
    plot->graph(0)->addData(keys, signal);
    plot->xAxis->setRange(0, signal.size());
    plot->yAxis->setRange(-5, 5);
    plot->replot();
    ui->signal->layout()->addWidget(plot);
    auto autocorrelationPlot = new QCustomPlot(this);
    autocorrelationPlot->addGraph();
    autocorrelationPlot->graph(0)->addData(halfkeys, autocorrelation(signal));
    autocorrelationPlot->xAxis->setRange(0, halfkeys.size());
    autocorrelationPlot->yAxis->setRange(-1, 1);
    autocorrelationPlot->replot();
    ui->autocorrelation->layout()->addWidget(autocorrelationPlot);
    auto crosscorrelationPlot = new QCustomPlot(this);
    crosscorrelationPlot->addGraph();
    crosscorrelationPlot->graph(0)->addData(
        halfkeys, crosscorrelation(signal, generate(ui->harmonics->value(),
                                                    ui->frequency->value(),
                                                    ui->nInput->value())));
    crosscorrelationPlot->xAxis->setRange(0, halfkeys.size());
    crosscorrelationPlot->yAxis->setRange(-1, 1);
    crosscorrelationPlot->replot();
    ui->crosscorrelation->layout()->addWidget(crosscorrelationPlot);
  });
}

Lab1::~Lab1() { delete ui; }
