#include "s21_matrix.h"

s21::Matrix::Matrix() : rows_(0), collumns_(0), size_(0), data_(nullptr) { ; }

s21::Matrix::Matrix(const int n, const int m)
    : rows_(n), collumns_(m), size_(n * m) {
  createMatrix(data_);
}

s21::Matrix::Matrix(const int n) : Matrix(1, n) { ; }

s21::Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_), collumns_(other.collumns_), size_(other.size_) {
  createMatrix(data_);
  copyData(data_, other.data_);
}

s21::Matrix::Matrix(Matrix&& other)
    : rows_(other.rows_),
      collumns_(other.collumns_),
      size_(other.size_),
      data_(std::move(other.data_)) {}

s21::Matrix::Matrix(const int n, const int m,
                    const std::initializer_list<int>& list)
    : Matrix(n, m) {
  if (size_ == list.size()) {
    int j = 0;
    for (auto i : list) {
      data_[j++] = i;
    }
  }
}

const s21::Matrix& s21::Matrix::operator=(const Matrix& other) {
  if (size_) removeMatrix(data_);
  rows_ = other.rows_;
  collumns_ = other.collumns_;
  size_ = other.size_;
  createMatrix(data_);
  copyData(data_, other.data_);
  return *this;
}

const s21::Matrix& s21::Matrix::operator=(Matrix&& other) {
  if (size_) removeMatrix(data_);
  rows_ = other.rows_;
  collumns_ = other.collumns_;
  size_ = other.size_;
  data_ = other.data_;
  other.data_ = nullptr;
  return *this;
}

s21::Matrix::~Matrix() {
  rows_ = collumns_ = size_ = 0;
  removeMatrix(data_);
}

bool s21::Matrix::operator==(const Matrix& other) {
  bool result = rows_ == other.rows_ && collumns_ == other.collumns_;
  for (int i = 0; i < size_ && result; ++i) {
    result = data_[i] == other.data_[i];
  }
  return result;
}

void s21::Matrix::pushBack(const int value) {
  if (!size_) {
    rows_ = collumns_ = size_ = 1;
    createMatrix(data_);
    data_[0] = value;
  } else if (rows_ == 1) {
    collumns_ = size_ += 1;
    int* tempData = data_;
    data_ = nullptr;
    createMatrix(data_);
    for (int i = 0; i < size_ - 1; ++i) data_[i] = tempData[i];
    data_[size_ - 1] = value;
    removeMatrix(tempData);
  }
}

void s21::Matrix::pushBack(const Matrix& other) {
  if (!size_) {
    rows_ = other.rows_;
    collumns_ = other.collumns_;
    size_ = other.size_;
    createMatrix(data_);
    copyData(data_, other.data_);
  } else {
    collumns_ += other.collumns_;
    size_ += other.size_;
    data_type temp = data_;
    data_ = nullptr;
    createMatrix(data_);
    int i = 0;
    for (int j = 0; j < size_ - other.size_; data_[i++] = temp[j++]) {
    }
    for (int j = 0; j < other.size_; data_[i++] = other.data_[j++]) {
    }
    removeMatrix(temp);
  }
}

typename s21::Matrix::Matrix s21::Matrix::slice(int start, int end) {
  if (start > end) {
    int tmp = start;
    start = end;
    end = tmp;
  }
  if (!end) end = size_;
  Matrix result(end - start);
  for (int i = 0; start < end; ++i, ++start) {
    result.data_[i] = data_[start];
  }
  return result;
}

int s21::Matrix::front() const { return data_[0]; }

int s21::Matrix::back() const { return data_[size_ - 1]; }

int& s21::Matrix::operator()(const int n, const int m) {
  return data_[indexEs(n, m, collumns_)];
}

int s21::Matrix::operator()(const int n, const int m) const {
  return data_[indexEs(n, m, collumns_)];
}

int& s21::Matrix::operator[](int n) {
  if (n < 0) n += size_;
  return data_[n];
}

int s21::Matrix::operator[](int n) const {
  if (n < 0) n += size_;
  return data_[n];
}

void s21::Matrix::operator()(const int n, const Matrix& other) {
  if (size_ && collumns_ == other.collumns_ && other.rows_ == 1 && n < rows_) {
    for (int i = 0; i < collumns_; ++i)
      data_[indexEs(n, i, collumns_)] = other.data_[i];
  }
}

int s21::Matrix::getRows() const { return rows_; }

int s21::Matrix::getColls() const { return collumns_; }

int s21::Matrix::getSize() const { return size_; }

bool s21::Matrix::empty() const { return size_ ? 0 : 1; }

bool s21::Matrix::contain(const int value) const {
  bool result = false;
  for (int i = 0; i < size_ && !result; ++i) result = data_[i] == value;
  return result;
}

void s21::Matrix::operator+=(const int value) {
  for (int i = 0; i < size_; data_[i++] += value) {
  }
}

void s21::Matrix::reverseSet() {
  data_type tmp = data_;
  data_ = nullptr;
  createMatrix(data_);
  for (int i = 0, j = size_ - 1; i < size_; data_[j--] = tmp[i++]) {
  }
  removeMatrix(tmp);
}

typename s21::Matrix::Matrix s21::Matrix::reverse() {
  Matrix result(*this);
  result.reverseSet();
  return result;
}

void s21::Matrix::resize(const int n, const int m) {
  if (size_) removeMatrix(data_);
  rows_ = n;
  collumns_ = m;
  size_ = n * m;
  createMatrix(data_);
}

void s21::Matrix::setMaxValue() {
  for (int i = 0; i < size_; ++i) data_[i] = INT_MAX;
}

void s21::Matrix::clear() {
  removeMatrix(data_);
  rows_ = collumns_ = size_ = 0;
}

void s21::Matrix::createMatrix(data_type& data) {
  data_ = new int[size_];
  for (int i = 0; i < size_; data_[i++] = 0)
    ;
}

void s21::Matrix::removeMatrix(data_type& data) {
  if (data != nullptr) delete[] data;
  data = nullptr;
}

void s21::Matrix::copyData(data_type& data, const data_type& other) {
  for (int i = 0; i < size_; ++i) data[i] = other[i];
}

int s21::Matrix::indexEs(const int row, const int coll, const int colls) const {
  return (row * colls) + coll;
}
