#include "lab2.h"
#include "common.h"
#include "qcustomplot/qcustomplot.h"
#include "ui_lab2.h"
#include <cmath>
#include <complex>
#include <valarray>
#define PI 3.1415926

#define measure(fn, arg, unit)\
  [arg]() {\
    auto start = std::chrono::high_resolution_clock::now();\
    fn(arg);\
    return std::chrono::duration_cast<std::chrono::unit>(\
    std::chrono::high_resolution_clock::now() - start).count();\
  }()

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
    auto dftTimePlot = new QCustomPlot(this);
    auto fftTimePlot = new QCustomPlot(this);
    QVector<double> nKeys;
    QVector<double> dftTime;
    QVector<double> fftTime;
    for(int n = 5;n <= 12;++n) {
        nKeys.push_back(1 << n);
        auto signal = generate(ui->harmonics->value(), ui->frequency->value(),1 << n);
        dftTime.push_back(measure(dft, signal, microseconds));
        fftTime.push_back(measure(fft, signal, microseconds));
    }
    dftTimePlot->addGraph();
    dftTimePlot->graph(0)->addData(nKeys, dftTime);
    dftTimePlot->xAxis->setRange(1 << 5, 1 << 12);
    dftTimePlot->xAxis->setLabel("DFT(N)");
    dftTimePlot->yAxis->setRange(0, 2e6);
    dftTimePlot->yAxis->setLabel("t(μs)");
    dftTimePlot->replot();
    fftTimePlot->addGraph();
    fftTimePlot->graph(0)->addData(nKeys, fftTime);
    fftTimePlot->xAxis->setRange(1 << 5, 1 << 12);
    fftTimePlot->xAxis->setLabel("FFT(N)");
    fftTimePlot->yAxis->setRange(0, 3000);
    fftTimePlot->yAxis->setLabel("t(μs)");
    fftTimePlot->replot();
    ui->compare->layout()->addWidget(dftTimePlot);
    ui->compare->layout()->addWidget(fftTimePlot);
  });
}

Lab2::~Lab2() { delete ui; }
