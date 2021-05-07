#ifndef LAB3DIOPHANTUS_H
#define LAB3DIOPHANTUS_H
#include <optional>
#include <random>
#include <vector>
class Chromosome {
  std::vector<int> task;
  int target;
  int calc() const {
    int res = 0;
    for (size_t i = 0; i < genes.size(); ++i)
      res += genes[i] * task[i];
    return res;
  }

public:
  std::vector<int> genes;
  Chromosome(const std::vector<int> &genes, const std::vector<int> &task,
             int target = 0)
      : task(task), target(target), genes(genes) {}

  Chromosome crossover(const Chromosome &partner) {
    auto child = *this;
    for (size_t i = child.genes.size() / 2; i < child.genes.size(); ++i)
      child.genes[i] = partner.genes[i];

    return child;
  }

  int fitness() const { return abs(target - calc()); }
};

class Diophantus {
  std::random_device rd;
  std::vector<Chromosome> population;

public:
  Diophantus(std::vector<int> task, int target, int sizePower = 4) {
    for (size_t i = 0; i < pow(task.size(), sizePower); ++i) {
      std::vector<int> genes(task.size());
      for (size_t n = 0; n < task.size(); ++n)
        genes[n] = std::uniform_int_distribution<int>(1, target / 2)(rd);
      population.push_back(Chromosome(genes, task, target));
    }
  }

  std::vector<int> solve() {
    while (true) {
      auto chromosome = crossover();
      if (chromosome)
        return chromosome->genes;
    }
  }

  std::optional<Chromosome> crossover() {
    std::vector<Chromosome> children;
    for (size_t i = 0; i < population.size(); ++i) {
      std::vector<std::pair<Chromosome, double>> parents;
      for (const auto &chromosome : population)
        parents.push_back(std::make_pair(
            chromosome, std::uniform_real_distribution(0.0, 1.0)(rd) *
                            chromosome.fitness()));
      std::sort(
          parents.begin(), parents.end(),
          [](std::pair<Chromosome, double> a, std::pair<Chromosome, double> b) {
            return a.second < b.second;
          });

      auto parent = parents[0].first;
      auto partner = parents[1].first;

      auto child = parent.crossover(partner);
      if (abs(child.fitness()) == 0)
        return std::optional<Chromosome>(child);

      children.push_back(child);
    }
    population = children;
    return std::nullopt;
  }
};
#endif // LAB3DIOPHANTUS_H
