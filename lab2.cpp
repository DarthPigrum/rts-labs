#include "lab2.h"
#include "common.h"
#include "qcustomplot/qcustomplot.h"
#include "ui_lab2.h"
#include <cmath>
#include <complex>
#include <valarray>
#define PI 3.1415926

QVector<double> dft(const QVector<double> &signal) {
  size_t N = signal.length();
  QVector<std::complex<double>> spectrum(N);
  for (size_t p = 0; p < N; ++p)
    for (size_t k = 0; k < N; ++k)
      spectrum[p] += std::complex<double>(cos(2.0 * PI / N * p * k),
                                          -sin(2.0 * PI / N * p * k)) *
                     signal[k];
  QVector<double> result;
  for (auto &ref : spectrum)
    result.push_back(abs(ref));
  return result;
}

void fftInPlace(std::valarray<std::complex<double>> &signal) {
  size_t N = signal.size();
  if (N <= 1)
    return;
  std::valarray<std::complex<double>> even = signal[std::slice(0, N / 2, 2)];
  std::valarray<std::complex<double>> odd = signal[std::slice(1, N / 2, 2)];
  fftInPlace(even);
  fftInPlace(odd);
  for (size_t k = 0; k < N / 2; ++k) {
    auto t = std::polar(1.0, -2 * PI * k / N) * odd[k];
    signal[k] = even[k] + t;
    signal[k + N / 2] = even[k] - t;
  }
}

QVector<double> fft(const QVector<double> &signal) {
  std::valarray<std::complex<double>> spectrum(signal.length());
  size_t i = 0;
  for (const auto &ref : signal)
    spectrum[i++] = ref;
  fftInPlace(spectrum);
  QVector<double> result;
  for (const auto &ref : spectrum)
    result.push_back(abs(ref));
  return result;
}

Lab2::Lab2(QWidget *parent) : QWidget(parent), ui(new Ui::Lab2) {
  ui->setupUi(this);
  connect(ui->pushButton, &QPushButton::clicked, [this]() {
    auto signal = generate(ui->harmonics->value(), ui->frequency->value(),
                           ui->nInput->value());
    QVector<double> keys(signal.size());
    for (int i = 0; i < signal.size(); ++i)
      keys[i] = i;
    auto plot = new QCustomPlot(this);
    plot->addGraph();
    plot->graph(0)->addData(keys, signal);
    plot->xAxis->setRange(0, signal.size());
    plot->yAxis->setRange(-5, 5);
    plot->replot();
    ui->signal->layout()->addWidget(plot);
    auto dftPlot = new QCustomPlot(this);
    dftPlot->addGraph();
    dftPlot->graph(0)->addData(keys, dft(signal));
    dftPlot->xAxis->setRange(0, keys.size() / 4);
    dftPlot->yAxis->setRange(0, 400);
    dftPlot->replot();
    ui->dft->layout()->addWidget(dftPlot);
    auto fftPlot = new QCustomPlot(this);
    fftPlot->addGraph();
    fftPlot->graph(0)->addData(keys, fft(signal));
    fftPlot->xAxis->setRange(0, keys.size() / 4);
    fftPlot->yAxis->setRange(0, 400);
    fftPlot->replot();
    ui->fft->layout()->addWidget(fftPlot);
  });
}

Lab2::~Lab2() { delete ui; }
