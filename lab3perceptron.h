#ifndef LAB3PERCEPTRON_H
#define LAB3PERCEPTRON_H
#include <array>
#include <vector>

class Perceptron {
  double bias = 1.0;
  double error = 1e-6;
  double accuracy = 0.0;
  std::array<double, 2> weights = {0.0, 0.0};
  double threshold;
  double learningRate;

public:
  Perceptron(double threshold, double learningRate)
      : threshold(threshold), learningRate(learningRate){};
  bool guess(std::array<double, 2> point) { return predict(point) > threshold; }
  double predict(std::array<double, 2> point) { return sum(point); }
  bool train(std::vector<std::array<double, 2>> points) {
    size_t i = 0;
    bool success = true;
    for (const auto &point : points)
      success &= adjustWeights(point, i++);
    return success;
  }
  double learn(std::vector<std::array<double, 2>> points,
               double deadline = 100.0) {
    while (true) {
      if (deadline / points.size() <= 0 || train(points))
        break;
      deadline--;
    }

    return accuracy;
  }
  bool adjustWeights(std::array<double, 2> point, double i) {
    auto delta = threshold - predict(point);
    if (abs(delta) < error || delta * pow(-1, i) < 0)
      return true;
    size_t n = 0;
    for (auto &w : weights)
      w = w + delta * point[n++] * learningRate;
    accuracy = 1 - delta;
    return false;
  }
  double sum(std::array<double, 2> point) {
    double res = bias;
    size_t i = 0;
    for (const auto &x : point)
      res += x * weights[i++];
    return res;
  }
};
#endif // LAB3PERCEPTRON_H
