#pragma once

#include <iostream>     // std::cout
#include <algorithm>
#include <assert.h>

template <typename T, size_t R, size_t C>
class Matrix {
private:

    static constexpr size_t rows_ = R;
	static constexpr size_t cols_ = C;
    static constexpr size_t size_ = R * C;
    T data_[size_];

public:
    // ----- Base Methods -----
    
    constexpr Matrix(); // default constructor
    constexpr Matrix(const std::initializer_list<T>& list); // using initializer_list

    // template <typename... Args>
    // constexpr Matrix(Args&&... args); // using forward arguments

    ~Matrix() = default;
    Matrix(const Matrix<T, R, C>& M) = default; // by copy

    // ----- Operators -----
    
    // TODO with expression template
    constexpr Matrix<T, R, C>& operator=(const Matrix<T, R, C>& M); // TODO
    Matrix<T, R, C> operator+(const Matrix<T, R, C>& M) const; // TODO
    Matrix<T, R, C> operator+(const T& val) const; // TODO
    
    template <typename T_, size_t R_, size_t C_> // return false if type or size are different
    inline constexpr bool operator==(const Matrix<T_, R_, C_>& M) { return false; }

    constexpr bool operator==(const Matrix<T, R, C>& M);
        // return std::equal(begin(), end(), M.begin()); constexpr ?

    constexpr bool operator<(const Matrix<T, R, C>& M);
        // return lexicographical_compare(begin(), end(), M.begin(), M.end()); constexpr ?

    inline constexpr bool operator!= (const Matrix<T, R, C>& M) { return !(*this == M); }
    inline constexpr bool operator> (const Matrix<T, R, C>& M) { return R < *this; }
    inline constexpr bool operator<= (const Matrix<T, R, C>& M) { return !(M < *this); }
    inline constexpr bool operator>= (const Matrix<T, R, C>& M) { return !(*this < R); }


    // use other template parameters to be template as well for external class ostream to handle our class
    template <typename T_, size_t R_, size_t C_>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T_, R_, C_>& M);

    // ----- Getters ----
    static constexpr size_t id(const size_t& r, const size_t& c) { return r * cols_ + c;}; 
    static constexpr size_t rows() {return rows_;};
    static constexpr size_t cols() {return cols_;};
    static constexpr size_t size() {return size_;};
    // static constexpr std::pair<size_t, size_t> shape() {return std::make_pair(rows_, cols_);}; // dosn't work because of make_pair .. ? 

    // begin
    inline constexpr T* begin() { return data_; };
    inline constexpr const T* begin() const { return data_; };
     inline constexpr const T* cbegin() const { return data_; };

    // end
    inline constexpr T* end() { return data_ + size_; };
    inline constexpr const T* end() const { return data_ + size_; };
    inline constexpr const T* cend() const { return data_ + size_; };

    // //data
    // inline constexpr T* data() noexcept;
    // inline constexpr const T* data() const noexcept;

    // by rows & cols
    inline constexpr T& operator()(const size_t& r, const size_t& c) noexcept { return data_[id(r, c)]; } ;
    inline constexpr const T& operator()(const size_t& r, const size_t& c) const noexcept { return data_[id(r, c)]; };
    // with static_assert bounding check
    constexpr T& at(const size_t& r, const size_t& c);
    constexpr const T& at(const size_t& r, const size_t& c) const;

    // by index
    inline constexpr T& operator[](const size_t& id) noexcept { return data_[id]; }
    inline constexpr const T& operator[](const size_t& id) const noexcept { return data_[id]; }
    // with bounding check
    constexpr T& at(const size_t& id);
    constexpr const T& at(const size_t& id) const;

    // ----- useFull Method -----
    constexpr Matrix<T, R, C> fill(const T& val) const; // TODO
    constexpr T det() const; // TODO
    Matrix<T, C, R>& transpose() const;
    // TOTO inplace transpose (pb with template arguments)
    Matrix<T, 1, R * C>& flatten() const; // TODO

    // ----- static methods -----
    constexpr static Matrix<T, R, C> Identity(); // TODO how handle passing only one non-type template parameter ? (because Rows = Cols)
    static Matrix<T, R, C> Zeros();
    static Matrix<T, R, C> Ones();
};

// ----- Base Methods -----

template <typename T, size_t R, size_t C>
constexpr Matrix<T, R, C>::Matrix() : data_{} {
    static_assert(cols_ > 0 && rows_ > 0 , "size must be greter than 0");
}
// why " data_ must be initialized by mem-initializer on 'constexpr' constructor " error without ": data_{}"
template <typename T, size_t R, size_t C>
constexpr Matrix<T, R, C>::Matrix(const std::initializer_list<T>& list) {
    static_assert(list.size() ==  R * C );
    auto it = list.begin();
    for (T& i : data_) {
        i = *it;
        it++; // ++ is constexpr ? 
    }
}

// template <typename T, size_t R, size_t C>
// template <typename... Args>
// constexpr Matrix<T, R, C>::Matrix(Args&&... args) : data_{ std::forward<Args>(args)... } {
// }
    

// template <typename T, size_t R, size_t C>
// Matrix<T, R, C>::~Matrix() {
//     // nothing to do
// }

// ----- Operators -----

template <typename T, size_t R, size_t C>
constexpr Matrix<T, R, C>& Matrix<T, R, C>::operator=(const Matrix<T, R, C>& M) {
    if (this != &M) {
        // TODO
    }
    return *this;
}

template <typename T, size_t R, size_t C>
constexpr bool Matrix<T, R, C>::operator==(const Matrix<T, R, C>& M) {
    for (size_t i = 0; i < size(); i++) {
        if(data_[i] != M(i)) { return false;}
    }
    return true;
}

template <typename T, size_t R, size_t C>
constexpr bool Matrix<T, R, C>::operator<(const Matrix<T, R, C>& M) {
    for (size_t i = 0; i < size(); i++) {
        if(data_[i] >= M(i)) { return false;}
    }
    return true;
}

// ----- Getters ----
template <typename T, size_t R, size_t C>
constexpr T& Matrix<T, R, C>::at(const size_t& r, const size_t& c) { 
    static_assert(r >= 0 && c >= 0 && r < rows_ && c < cols_, "invalid range");
    return data_[id(r, c)]; 
};
template <typename T, size_t R, size_t C>    
constexpr const T& Matrix<T, R, C>::at(const size_t& r, const size_t& c) const { 
    static_assert(r >= 0 && c >= 0 && r < rows_ && c < cols_, "invalid range");
    return data_[id(r, c)]; 
};

template <typename T, size_t R, size_t C>
constexpr T& Matrix<T, R, C>::at(const size_t& id) { 
    static_assert(id >= 0 && id  < size_, "invalid range");
    return data_[id];
};
template <typename T, size_t R, size_t C>    
constexpr const T& Matrix<T, R, C>::at(const size_t& id) const { 
    static_assert(id >= 0 && id  < size_, "invalid range");
    return data_[id];
};

// ----- useFull Method -----
template <typename T, size_t R, size_t C>
constexpr Matrix<T, R, C> Matrix<T, R, C>::fill(const T& val) const {
    // use std::fill insted ? constexpr ?
    Matrix<T, R, C> M;
    for (T& m : M.data_) {
        m = val;
    }
    return M;
}

template <typename T, size_t R, size_t C>
Matrix<T, C, R>& Matrix<T, R, C>::transpose() const {
    Matrix<T, C, R> M;
    for (size_t i = 0; i < M.rows_; ++i) {
        for (size_t j = 0; j < M.cols_; ++j) {
            M.data_[M.id(i, j)] = data_[id(j, i)];
        }
    }
    return M;
}

template <typename T, size_t R, size_t C>
std::ostream& operator<<(std::ostream& os, const Matrix<T, R, C>& M) {
    os << "[";
    for (size_t j = 0; j < M.cols_ - 1; ++j) os << M(0, j) << ", ";
    os << M(0, M.cols_ - 1) << std::endl;

    for (size_t i = 1; i < M.rows_-1; ++i) {
        os << " ";
        for (size_t j = 0; j < M.cols_ - 1; ++j) os << M(i, j) << ", ";
        os << M(i, M.cols_ - 1) << std::endl;
    }
    os << " ";
    for (size_t j = 0; j < M.cols_ - 1; ++j) os << M( M.rows_-1, j) << ", ";
    os << M( M.rows_-1, M.cols_ - 1) <<  "]" << std::endl;

    return os;
}

// ----- static methods -----

template <typename T, size_t R, size_t C>
constexpr Matrix<T, R, C> Matrix<T, R, C>::Identity() {
    Matrix<T, R, C> M;
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            (i == j) ? M(i, j) = 1 : M(i, j) = 0;
        }
    }
    return M;
}

template <typename T, size_t R, size_t C>
Matrix<T, R, C> Matrix<T, R, C>::Zeros() {
    Matrix<T, R, R> M;
    return M.fill(0);
}

template <typename T, size_t R, size_t C>
Matrix<T, R, C> Matrix<T, R, C>::Ones() {
    Matrix<T, R, R> M;
    return M.fill(1);
}