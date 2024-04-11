#ifndef CONTAINERS_S21_MATRIX_H
#define CONTAINERS_S21_MATRIX_H

#include <climits>
#include <initializer_list>
#include <iostream>

namespace s21 {
class Matrix {
 public:
  using data_type = int*;
  Matrix();
  Matrix(const int n, const int m);
  Matrix(const int n);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  Matrix(const int n, const int m, const std::initializer_list<int>& list);
  const Matrix& operator=(const Matrix& other);
  const Matrix& operator=(Matrix&& other);
  ~Matrix();
  bool operator==(const Matrix& other);

  void pushBack(const int value);
  void pushBack(const Matrix& other);
  Matrix slice(int start = 0, int end = 0);

  int front() const;
  int back() const;
  int& operator()(const int n, const int m);
  int operator()(const int n, const int m) const;
  int& operator[](int n);
  int operator[](int n) const;
  void operator()(const int n, const Matrix& other);
  int getRows() const;
  int getColls() const;
  int getSize() const;
  bool empty() const;
  bool contain(const int value) const;

  void operator+=(const int value);
  void reverseSet();
  Matrix reverse();

  void resize(const int n, const int m);
  void setMaxValue();
  void clear();

  friend std::ostream& operator<<(std::ostream& out, const Matrix other) {
    if (other.size_) {
      out << other.rows_ << ", " << other.collumns_ << std::endl;
      for (int i = 0; i < other.rows_; ++i) {
        for (int j = 0; j < other.collumns_; ++j) {
          out << other.data_[other.indexEs(i, j, other.collumns_)];
          if (j != other.collumns_ - 1) out << ", ";
        }
        out << std::endl;
      }
    }
    return out;
  }

 private:
  int rows_;
  int collumns_;
  int size_;
  data_type data_;

  void createMatrix(data_type& data);
  void removeMatrix(data_type& data);
  void copyData(data_type& data, const data_type& other);

  int indexEs(const int row, const int coll, const int colls) const;
};
};  // namespace s21

#endif  // CONTAINERS_S21_MATRIX_H