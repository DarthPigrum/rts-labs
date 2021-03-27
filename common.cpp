#include "common.h"

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0, 1.0);

QVector<double> generate(int harmonics, double frequency, int N) {
    QVector<double> signal(N);
    double W = frequency / harmonics;

    for (int i = 0; i < harmonics; ++i) {
        double amplitude = distribution(generator);
        double phase = distribution(generator);
        for (int t = 0; t < N; ++t)
            signal[t] += (amplitude * sin(W * t + phase));
        W += W;
    }
    return signal;
}
