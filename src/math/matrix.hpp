#pragma once
#include "arithmetic.hpp"

namespace intern {
    // structs
    template<typename T, adress N, adress M = N>
    struct Matrix {
    public:
        Matrix() = default;
        Matrix(const std::initializer_list<T>& list) {
            if (list.size() == M) {
                for (adress n = 0; n < N; ++n) {
                    for (adress m = 0; m < M; ++m) {
                        at(n, m) = *(list.begin() + m);
                    }
                }
            }
        }
        Matrix(const std::initializer_list<std::initializer_list<T>>& list) {
            for (adress n = 0; n < N; ++n) {
                for (adress m = 0; m < M; ++m) {
                    at(n, m) = *(*(list.begin() + n) + m);
                }
            }
        }
        
        template<typename T2>
        Matrix(const Matrix<T2, N, M>& mat) {
            for (adress i = 0; i < N * M; ++i) {
                m_data[i] = (T)mat.m_data[i];
            }
        }

        T& at(adress index) {
            return m_data[index];
        }
        const T& at(adress index) const {
            return m_data[index];
        }
        T& at(adress n, adress m) {
            return m_data[M * n + m];
        }
        const T& at(adress n, adress m) const {
            return m_data[M * n + m];
        }

        T* data() {
            return m_data;
        }
        const T* data() const {
            return m_data;
        }
    private:
        T m_data[N * M];
    };
    template<typename T>
    struct Matrix<T, 2, 1> {
        Matrix() = default;
        Matrix(T val)
            : x(val), y(val) {}
        Matrix(T x, T y)
            : x(x), y(y) {}

        template<typename T2, adress N>
        Matrix(const Matrix<T2, N, 1>& vec)
            : x(vec.at(0)), y(vec.at(1)) {}

        T& at(adress index) {
            return index == 0 ? x : y;
        }
        const T& at(adress index) const {
            return index == 0 ? x : y;
        }
        T& at(adress n, adress m) {
            return at(n);
        }
        const T& at(adress n, adress m) const {
            return at(n);
        }

        T x, y;
    };
    template<typename T>
    struct Matrix<T, 3, 1> {
        Matrix() = default;
        Matrix(T val)
            : x(val), y(val), z(val) {}
        Matrix(T x, T y, T z)
            : x(x), y(y), z(z) {}
        Matrix(const Matrix<T, 2, 1>& xy, T z)
            : x(xy.x), y(xy.y), z(z) {}
        Matrix(T x, const Matrix<T, 2, 1>& yz)
            : x(x), y(yz.x), z(yz.y) {}

        template<typename T2, adress N>
        Matrix(const Matrix<T2, N, 1>& vec)
            : x(vec.at(0)), y(vec.at(1)), z(vec.at(2)) {}
        template<typename T2>
        Matrix(const Matrix<T2, 2, 1>& vec)
            : x(vec.at(0)), y(vec.at(1)), z(0) {}

        T& at(adress index) {
            return index == 0 ? x : index == 1 ? y : z;
        }
        const T& at(adress index) const {
            return index == 0 ? x : index == 1 ? y : z;
        }
        T& at(adress n, adress m) {
            return at(n);
        }
        const T& at(adress n, adress m) const {
            return at(n);
        }

        T x, y, z;
    };
    template<typename T>
    struct Matrix<T, 4, 1> {
        Matrix() = default;
        Matrix(T val)
            : x(val), y(val), z(val), w(val) {}
        Matrix(T x, T y, T z, T w)
            : x(x), y(y), z(z), w(w) {}
        Matrix(const Matrix<T, 2, 1>& xy, T z, T w)
            : x(xy.x), y(xy.y), z(z), w(w) {}
        Matrix(T x, const Matrix<T, 2, 1>& yz, T w)
            : x(x), y(yz.x), z(yz.y), w(w) {}
        Matrix(T x, T y, const Matrix<T, 2, 1>& zw)
            : x(x), y(y), z(zw.x), w(zw.y) {}
        Matrix(const Matrix<T, 3, 1>& xyz, T w)
            : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
        Matrix(T x, const Matrix<T, 3, 1>& yzw)
            : x(x), y(yzw.x), z(yzw.y), w(yzw.z) {}
        
        template<typename T2, adress N>
        Matrix(const Matrix<T2, N, 1>& vec)
            : x(vec.at(0)), y(vec.at(1)), z(vec.at(2)), w(vec.at(3)) {}
        template<typename T2>
        Matrix(const Matrix<T2, 2, 1>& vec)
            : x(vec.at(0)), y(vec.at(1)), z(0), w(0) {}
        template<typename T2, adress N>
        Matrix(const Matrix<T2, 3, 1>& vec)
            : x(vec.at(0)), y(vec.at(1)), z(vec.at(2)), w(0) {}

        T& at(adress index) {
            return index == 0 ? x : index == 1 ? y : index == 2 ? z : w;
        }
        const T& at(adress index) const {
            return index == 0 ? x : index == 1 ? y : index == 2 ? z : w;
        }
        T& at(adress n, adress m) {
            return at(n);
        }
        const T& at(adress n, adress m) const {
            return at(n);
        }

        T x, y, z, w;
    };

    // alias
    template<typename T, adress N, adress M = N>
    using Mat = Matrix<T, N, M>;

    template<typename T>
    using Mat2 = Mat<T, 2>;
    template<typename T>
    using Mat3 = Mat<T, 3>;
    template<typename T>
    using Mat4 = Mat<T, 4>;

    template<typename T>
    using Mat2x3 = Mat<T, 2, 3>;
    template<typename T>
    using Mat2x4 = Mat<T, 2, 4>;
    template<typename T>
    using Mat3x2 = Mat<T, 3, 2>;
    template<typename T>
    using Mat3x4 = Mat<T, 3, 4>;
    template<typename T>
    using Mat4x2 = Mat<T, 4, 2>;
    template<typename T>
    using Mat4x3 = Mat<T, 4, 3>;

    using Mat2f = Mat2<f32>;
    using Mat3f = Mat3<f32>;
    using Mat4f = Mat4<f32>;
    using Mat2x3f = Mat2x3<f32>;
    using Mat2x4f = Mat2x4<f32>;
    using Mat3x2f = Mat3x2<f32>;
    using Mat3x4f = Mat3x4<f32>;
    using Mat4x2f = Mat4x2<f32>;
    using Mat4x3f = Mat4x3<f32>;

    using Mat2d = Mat2<f64>;
    using Mat3d = Mat3<f64>;
    using Mat4d = Mat4<f64>;
    using Mat2x3d = Mat2x3<f64>;
    using Mat2x4d = Mat2x4<f64>;
    using Mat3x2d = Mat3x2<f64>;
    using Mat3x4d = Mat3x4<f64>;
    using Mat4x2d = Mat4x2<f64>;
    using Mat4x3d = Mat4x3<f64>;

    using Mat2i = Mat2<i32>;
    using Mat3i = Mat3<i32>;
    using Mat4i = Mat4<i32>;
    using Mat2x3i = Mat2x3<i32>;
    using Mat2x4i = Mat2x4<i32>;
    using Mat3x2i = Mat3x2<i32>;
    using Mat3x4i = Mat3x4<i32>;
    using Mat4x2i = Mat4x2<i32>;
    using Mat4x3i = Mat4x3<i32>;

    using Mat2u = Mat2<u32>;
    using Mat3u = Mat3<u32>;
    using Mat4u = Mat4<u32>;
    using Mat2x3u = Mat2x3<u32>;
    using Mat2x4u = Mat2x4<u32>;
    using Mat3x2u = Mat3x2<u32>;
    using Mat3x4u = Mat3x4<u32>;
    using Mat4x2u = Mat4x2<u32>;
    using Mat4x3u = Mat4x3<u32>;

    // matrix set funcs
    template<typename T, adress N, adress M = N>
    Mat<T, N, M>& zeros(Mat<T, N, M>& mat) {
        for (adress i = 0; i < N * M; ++i) {
            mat.at(i) = 0;
        }
        return mat;
    }
    template<typename T, adress N, adress M = N>
    Mat<T, N, M> zeros() {
        Mat<T, N, M> out;
        zeros(out);
        return out;
    }

    template<typename T, adress N>
    Mat<T, N>& identity(Mat<T, N>& mat) {
        zeros(mat);
        for (adress n = 0; n < N; ++n) {
            mat.at(n, n) = 1;
        }
        return mat;
    }
    template<typename T, adress N>
    Mat<T, N> identity() {
        Mat<T, N> out;
        identity(out);
        return out;
    }

    // operators
    template<typename T, adress N, adress M>
    Matrix<T, N, M> operator-(const Matrix<T, N, M>& mat) {
        Matrix<T, N, M> out;
        for (adress i = 0; i < N * M; ++i) {
            out.at(i) = -mat.at(i);
        }
        return out;
    }
    template<typename T, adress N, adress M>
    Matrix<T, N, M>& operator+=(Matrix<T, N, M>& mat, const Matrix<T, N, M>& other) {
        for (adress i = 0; i < N * M; ++i) {
            mat.at(i) += other.at(i);
        }
        return mat;
    }
    template<typename T, adress N, adress M>
    Matrix<T, N, M>& operator-=(Matrix<T, N, M>& mat, const Matrix<T, N, M>& other) {
        for (adress i = 0; i < N * M; ++i) {
            mat.at(i) -= other.at(i);
        }
        return mat;
    }
    template<typename T, adress N, adress M>
    Matrix<T, N, M>& operator*=(Matrix<T, N, M>& mat, T scalar) {
        for (adress i = 0; i < N * M; ++i) {
            mat.at(i) *= scalar;
        }
        return mat;
    }
    template<typename T, adress N, adress M>
    Matrix<T, N, M>& operator/=(Matrix<T, N, M>& mat, T scalar) {
        for (adress i = 0; i < N * M; ++i) {
            mat.at(i) /= scalar;
        }
        return mat;
    }
    template<typename T, adress N, adress M>
    Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat, const Matrix<T, N, M>& other) {
        Matrix<T, N, M> out(mat);
        out += other;
        return out;
    }
    template<typename T, adress N, adress M>
    Matrix<T, N, M> operator-(const Matrix<T, N, M>& mat, const Matrix<T, N, M>& other) {
        Matrix<T, N, M> out(mat);
        out -= other;
        return out;
    }
    template<typename T, adress N, adress M>
    Matrix<T, N, M> operator*(const Matrix<T, N, M>& mat, T scalar) {
        Matrix<T, N, M> out(mat);
        out *= scalar;
        return out;
    }
    template<typename T, adress N, adress M>
    Matrix<T, N, M> operator/(const Matrix<T, N, M>& mat, T scalar) {
        Matrix<T, N, M> out(mat);
        out /= scalar;
        return out;
    }

    template<typename T, adress N, adress M, adress L>
    Matrix<T, N, L> operator*(const Matrix<T, N, M>& mat1, const Matrix<T, M, L>& mat2) {
        Matrix<T, N, L> out = zeros<T, N, L>();
        for (adress n = 0; n < N; ++n) {
            for (adress l = 0; l < L; ++l) {
                for (adress m = 0; m < M; ++m) {
                    out.at(n, l) += mat1.at(n, m) * mat2.at(m, l);
                }
            }
        }
        return out;
    }
    template<typename T, adress N>
    Matrix<T, N>& operator*=(Matrix<T, N>& mat1, const Matrix<T, N>& mat2) {
        mat1 = mat1 * mat2;
        return mat1;
    }

    // length
    template<typename T, adress N, adress M>
    T frobenius_norm(const Mat<T, N, M>& mat) {
        T out = 0;
        for (adress i = 0; i < N * M; ++i) {
            out += mat.at(i) * mat.at(i);
        }
        return sqrt(out);
    }
    template<typename T, adress N, adress M>
    T length(const Mat<T, N, M>& mat) {
        return frobenius_norm(mat);
    }
    template<typename T, adress N, adress M>
    T dist(const Mat<T, N, M>& mat1, const Mat<T, N, M>& mat2) {
        return length(mat2 - mat1);
    }

    template<typename T, adress N, adress M>
    Mat<T, N, M>& normalize(Mat<T, N, M>& mat) {
        mat /= length(mat);
        return mat;
    }
    template<typename T, adress N, adress M>
    Mat<T, N, M> normalized(const Mat<T, N, M>& mat) {
        return normalize(Mat<T, N, M>(mat));
    }

    // transpose
    template<typename T, adress N, adress M>
    Mat<T, M, N> transposed(const Mat<T, N, M>& mat) {
        Matrix<T, M, N> out;
        for (adress n = 0; n < N; ++n) {
            for (adress m = 0; m < N; ++m) {
                out.at(N * m + n) = mat.at(M * n + m);
            }
        }
        return out;
    }
    template<typename T, adress N>
    Mat<T, N>& transpose(Mat<T, N>& mat) {
        mat = transposed(mat);
        return mat;
    }

    // insert / resize
    template<typename T, adress N1, adress M1, adress N2, adress M2>
    Mat<T, N1, M1>& insert(Mat<T, N1, M1>& dest, const Mat<T, N2, M2>& src, const Mat<u32, 2, 1>& where) {
        for (adress n = 0; n < min(N1 - where.x, N2); ++n) {
            for (adress m = 0; m < min(M1 - where.y, M2); ++m) {
                dest.at(where.x + n, where.y + m) = src.at(n, m);
            }
        }
        return dest;
    }
    template<typename T, adress N1, adress M1, adress N2, adress M2>
    Mat<T, N1, M1>& insert(Mat<T, N1, M1>& dest, const Mat<T, N2, M2>& src) {
        return insert(dest, src, Mat<u32, 2, 1>(0, 0));
    }
    template<typename T, adress N1, adress M1, adress N2, adress M2>
    Mat<T, N1, M1> resize(const Mat<T, N2, M2>& mat, const Mat<u32, 2, 1>& where) {
        Matrix<T, N1, M1> out = zeros<T, N1, M1>();
        insert(out, mat, where);
        return out;
    }
    template<typename T, adress N1, adress M1, adress N2, adress M2>
    Mat<T, N1, M1> resize(const Mat<T, N2, M2>& mat) {
        return resize<T,N1, M1>(mat, zeros<u32, 2, 1>());
    }
}