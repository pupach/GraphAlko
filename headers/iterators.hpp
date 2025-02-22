//
// Created by catboy on 2/21/2025.
//

#ifndef GRAPHALKO_ITERATORS_HPP
#define GRAPHALKO_ITERATORS_HPP
#include "Edges.hpp"

template<typename CurEdges>
class GraphStorageMatrixNear;

template<typename T, bool is_const>
class NearTopIterator_TopEdges {
 protected:
  std::vector<T>::iterator iter_near_tops;
  bool orientation = false;

 public:
  using value_type = T;
  using reference = std::conditional_t<is_const, const T &, value_type &>;
  using pointer = std::conditional_t<is_const, const T *, value_type *>;
  using difference_type = ssize_t;
  using iterator_category = std::bidirectional_iterator_tag;

  explicit NearTopIterator_TopEdges(std::vector<T>::iterator iter_near_tops) : iter_near_tops(iter_near_tops) {}

  NearTopIterator_TopEdges<T, is_const> &operator--() {
    iter_near_tops--;
    return *this;
  }
  NearTopIterator_TopEdges<T, is_const> operator--(int) {
    auto copy = *this;
    --(*this);
    return copy;
  }
  NearTopIterator_TopEdges<T, is_const> &operator++() {
    iter_near_tops++;
    return *this;
  }
  NearTopIterator_TopEdges<T, is_const> operator++(int) {
    auto copy = *this;
    ++(*this);
    return copy;
  }
  reference operator*() {
    return *iter_near_tops;
  }
  bool operator==(const NearTopIterator_TopEdges &other) {
    return other.iter_near_tops == this->iter_near_tops;
  }
  bool operator!=(const NearTopIterator_TopEdges &other) {
    return this->iter_near_tops != other.iter_near_tops;
  }
};

template<typename T, bool is_const>
class NearTopIterator_NearMatrix {
 protected:
  friend GraphStorageMatrixNear<T>;
  std::vector<T>::iterator iter_near_tops;

 public:
  using value_type = T;
  using reference = std::conditional_t<is_const, const T &, value_type &>;
  using pointer = std::conditional_t<is_const, const T *, value_type *>;
  using difference_type = ssize_t;
  using iterator_category = std::bidirectional_iterator_tag;

  explicit NearTopIterator_NearMatrix(std::vector<T>::iterator iter_near_tops) : iter_near_tops(iter_near_tops) {

  }

  NearTopIterator_NearMatrix<T, is_const> &operator--() {
    iter_near_tops--;
    while (iter_near_tops->where == INT_MAXIMUS) {
      iter_near_tops--;
    }
    return *this;
  }
  NearTopIterator_NearMatrix<T, is_const> operator--(int) {
    auto copy = *this;
    --(*this);
    return copy;
  }
  NearTopIterator_NearMatrix<T, is_const> &operator++() {
    iter_near_tops++;
    while (iter_near_tops->where == -1) {
      iter_near_tops++;
    }
    return *this;
  }
  NearTopIterator_NearMatrix<T, is_const> operator++(int) {
    auto copy = *this;
    ++(*this);
    return copy;
  }
  reference operator*() {
    return *iter_near_tops;
  }
  bool operator==(const NearTopIterator_NearMatrix &other) {
    return other.iter_near_tops == this->iter_near_tops;
  }
  bool operator!=(const NearTopIterator_NearMatrix &other) {
    return this->iter_near_tops != other.iter_near_tops;
  }
};

#endif //GRAPHALKO_ITERATORS_HPP
