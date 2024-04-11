#ifndef S21_GRAPH_H
#define S21_GRAPH_H

#include <climits>
#include <fstream>
#include <sstream>
#include <string>

#include "containers/s21_matrix.h"

namespace s21 {

class Graph {
 public:
  Graph();
  Graph(const Graph& other);
  Graph(Graph&& other);
  Graph(const std::string& filename);
  const Graph& operator=(const Graph& other);
  const Graph& operator=(Graph&& other);
  ~Graph();

  int size() const;
  bool empty() const;
  int& operator()(const int n, const int m);
  int operator()(const int n, const int m) const;

  void loadGraphFromFile(const std::string& filename);

  void exportGraphToDot(const std::string& filename) const;

  friend std::ostream& operator<<(std::ostream& out, const Graph& other) {
    out << other.data_;
    return out;
  }

 private:
  Matrix data_;

  int parsNum(size_t& it, const std::string& line, bool& error);
};
};  // namespace s21

#endif  // S21_GRAPH_H