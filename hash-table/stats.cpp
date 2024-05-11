#include "stats.h"

#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

#include "hashtable.h"

double compute_mean(const vector<int> &v) {
  double sum = 0;
  for (auto &n : v) sum += n;
  return sum / v.size();
}

double compute_stddev(const vector<int> &v) {
  double sum_squares = 0;
  double mean = compute_mean(v);
  double len = v.size();
  for (auto n : v) {
    double diff = n - mean;
    sum_squares += diff * diff;
  }
  return sqrt(sum_squares / len);
}
Stats::Stats(string name, const vector<int> &chain_lengths)
    : name(name), chain_lengths(chain_lengths) {
  for (int num : chain_lengths) {
    entries += num;
  }
  chains = chain_lengths.size();
  load_factor = static_cast<double>(entries) / chains;
  min = *min_element(chain_lengths.begin(), chain_lengths.end());
  max = *max_element(chain_lengths.begin(), chain_lengths.end());
  span = max - min;

  mean = compute_mean(chain_lengths);
  stddev = compute_stddev(chain_lengths);

  for (int len : chain_lengths) {
    histogram[len]++;
  }
}
