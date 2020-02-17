#pragma once

template <typename T, size_t R, size_t C>
class Matrix; // forward declaration

template <typename T, class L, class R>
class MatrixSum {
private:
    const L& left_;
    const R& right_;

public:
    // ----- Base Methods -----

    MatrixSum(const L& l, const R& r);
    ~MatrixSum() = default;

    // ----- Operators -----
    T operator()(const size_t& i, const size_t& j) const;
};

template <typename T, class L, class R>
MatrixSum<T, L, R>::MatrixSum(const L& l, const R& r) : left_(l), right_(r) {
}

template <typename T, class L, class R>
T MatrixSum<T, L, R>::operator()(const size_t& i, const size_t& j) const {
    return left_(i, j) + right_(i, j);
}
