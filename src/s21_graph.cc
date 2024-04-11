#include "s21_graph.h"

s21::Graph::Graph() { ; }

s21::Graph::Graph(const Graph& other) : data_(other.data_) { ; }

s21::Graph::Graph(Graph&& other) : data_(std::move(other.data_)) { ; }

s21::Graph::Graph(const std::string& filename) { loadGraphFromFile(filename); }

const typename s21::Graph::Graph& s21::Graph::operator=(const Graph& other) {
  data_ = other.data_;
  return *this;
}

const typename s21::Graph::Graph& s21::Graph::operator=(Graph&& other) {
  data_ = std::move(other.data_);
  return *this;
}

s21::Graph::~Graph() { ; }

int s21::Graph::size() const { return data_.getRows(); }

bool s21::Graph::empty() const { return data_.empty(); }

int& s21::Graph::operator()(const int n, const int m) { return data_(n, m); }

int s21::Graph::operator()(const int n, const int m) const {
  return data_(n, m);
}

void s21::Graph::loadGraphFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (file.is_open()) {
    bool error = false;
    std::string line;
    std::getline(file, line);
    int size = 0;
    try {
      size = std::stoi(line);
    } catch (const std::exception&) {
      error = true;
    }
    data_.resize(size, size);
    for (int i = 0; std::getline(file, line) && i < size && !error; ++i) {
      if (line.size() > 1) {
        for (size_t j = 0, it = 0; it < line.size() && j < size && !error;
             ++j) {
          data_(i, j) = parsNum(it, line, error);
        }
      }
    }
    if (error) data_.clear();
  }
  file.close();
}

void s21::Graph::exportGraphToDot(const std::string& filename) const {
  std::ofstream file(filename);
  if (file.is_open()) {
    std::ostringstream out;
    out << "Graph " + filename + " {" << std::endl;
    for (int i = 0; i < data_.getRows(); ++i) {
      for (int j = 0; j < data_.getColls(); ++j) {
        if (data_(i, j) != 0 || data_(j, i) != 0) {
          out << "  ";
          if (data_(i, j) == data_(j, i)) {
            out << std::to_string(i + 1) + " -- " + std::to_string(j + 1)
                << std::endl;
          } else {
            out << std::to_string(std::min(i, j) + 1) + " -> " +
                       std::to_string(std::max(i, j) + 1)
                << std::endl;
          }
        }
      }
    }
    out << "}" << std::endl;
    file << out.str();
  }
  file.close();
}

int s21::Graph::parsNum(size_t& it, const std::string& line, bool& error) {
  int result = 0;
  if (line[it] >= '0' && line[it] <= '9') {
    result = std::stoi(&(line[it]));
    for (; (line[it] >= '0' && line[it] <= '9') && it < line.size(); ++it) {
    }
    for (; (line[it] == ' ' || line[it] == ',') && it < line.size(); ++it) {
    }
  } else {
    error = true;
  }
  return result;
}