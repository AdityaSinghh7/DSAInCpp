#include "sorter.h"
using namespace std;
#include <fstream>
#include <iostream>

void Sorter::fill(int count, string file_name) {
  vec.clear();
  ifstream file(file_name);
  string word;
  while (count-- && file >> word) {
    vec.push_back(word);
  }
  file.close();
}

void Sorter::print(ostream& out) {
  for (const auto& word : vec) {
    out << word << " ";
  }
}

bool Sorter::verify_sorted() { return is_sorted(vec.begin(), vec.end()); }

// insertion sort

void InsertionSorter::insertionsort(vector<string>& vec, int low, int high) {
  for (int i = low + 1; i <= high; i++) {
    string key = vec[i];
    int j = i - 1;
    while (j >= low && vec[j] > key) {
      vec[j + 1] = vec[j];
      j--;
    }
    vec[j + 1] = key;
  }
}

void InsertionSorter::sort() { insertionsort(vec, 0, vec.size() - 1); }

// Quick Sort

string QuickSorter::select_pivot(vector<string>& vec, int low, int high) {
  int mid = (low + high) / 2;
  if (vec[mid] < vec[low]) swap(vec[low], vec[mid]);
  if (vec[high] < vec[low]) swap(vec[low], vec[high]);
  if (vec[mid] < vec[high]) swap(vec[mid], vec[high]);
  return vec[high];
}

int QuickSorter::partition(vector<string>& vec, int low, int high) {
  string pivot = select_pivot(vec, low, high);
  int i = low - 1;
  for (int j = low; j <= high - 1; j++) {
    if (vec[j] < pivot) {
      i++;
      swap(vec[i], vec[j]);
    }
  }
  swap(vec[i + 1], vec[high]);
  return (i + 1);
}

void QuickSorter::quicksort(vector<string>& vec, int low, int high) {
  if (low < high) {
    int partitioner = partition(vec, low, high);
    quicksort(vec, low, partitioner - 1);
    quicksort(vec, partitioner + 1, high);
  }
}

void QuickSorter::sort() { quicksort(vec, 0, vec.size() - 1); }

// Heap Sort

void HeapSorter::heapify(vector<string>& vec, int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  if (left < n && vec[left] > vec[largest]) largest = left;
  if (right < n && vec[right] > vec[largest]) largest = right;
  if (largest != i) {
    swap(vec[i], vec[largest]);
    heapify(vec, n, largest);
  }
}

void HeapSorter::heapsort(vector<string>& vec, int low, int high) {
  int n = high - low + 1;
  for (int i = n / 2 - 1; i >= 0; i--) heapify(vec, n, i);
  for (int i = n - 1; i >= 0; i--) {
    swap(vec[0], vec[i]);
    heapify(vec, i, 0);
  }
}

void HeapSorter::sort() { heapsort(vec, 0, vec.size() - 1); }

// Intro Sort

void IntroSorter::introsort(vector<string>& arr, int low, int high) {
  if (high - low < 11) {
    InsertionSorter::insertionsort(arr, low, high);
    return;
  }
  int p = QuickSorter::partition(arr, low, high);
  introsort(arr, low, p - 1);
  introsort(arr, p + 1, high);
}

void IntroSorter::sort() { introsort(vec, 0, vec.size() - 1); }

// STLSorter

void STLSorter::sort() { std::sort(vec.begin(), vec.end()); }

// Stable Sort

void StableSorter::sort() { std::stable_sort(vec.begin(), vec.end()); }

// Shell Sorter

void ShellSorter::gapInsertionSort(vector<string>& avector, int start,
                                   int gap) {
  int i = avector.size();
  for (int j = start + gap; j < i; j += gap) {
    string curr = avector[j];
    int pos = j;
    while (pos >= gap && avector[pos - gap] > curr) {
      avector[pos] = avector[pos - gap];
      pos -= gap;
    }
    avector[pos] = curr;
  }
}

void ShellSorter::shellSort(vector<string>& avector) {
  int svc = avector.size() / 2;
  while (svc > 0) {
    for (int sp = 0; sp < svc; sp++) {
      ShellSorter::gapInsertionSort(avector, sp, svc);
      svc = svc / 2;
    }
  }
}

void ShellSorter::sort() { ShellSorter::shellSort(vec); }

ostream& operator<<(ostream& out, Sorter& L) {
  L.print(out);
  return out;
}

void error(string word, string msg) {
  cout << "Error: " << msg << ": " << word << endl;
}
