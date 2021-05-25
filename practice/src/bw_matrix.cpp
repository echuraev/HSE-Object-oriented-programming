#include "bw_matrix.h"

#include <iomanip>
#include <iostream>

BWMatrix::BWMatrix()
    : Matrix(0, 0, 1)
{}

BWMatrix::BWMatrix(const BWMatrix& mat)
    : Matrix(mat)
{}

BWMatrix::BWMatrix(size_t rows, size_t cols)
    : Matrix(rows, cols, 1)
{}

BWMatrix::BWMatrix(size_t rows, size_t cols, int initVal)
    : Matrix(rows, cols, 1, initVal)
{}

BWMatrix BWMatrix::invert() const
{
    BWMatrix res = *this - 255;
    res = res * (-1);
    return res;
}

void BWMatrix::print() const
{
    std::cout << *this << std::endl;
}

void BWMatrix::fromOpenCV(const cv::Mat& mat)
{
if (mat.channels() != 1 || mat.depth() != CV_8U)
        return;
    m_rows = mat.rows;
    m_cols = mat.cols;
    m_data.resize(mat.total());
    for (int r = 0; r < m_rows; ++r) {
        for (int c = 0; c < m_cols; ++c) {
            at(r, c) = mat.at<uchar>(r, c);
        }
    }
}

cv::Mat BWMatrix::toOpenCV() const
{
    cv::Mat mat(m_rows, m_cols, CV_8UC1);
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < m_cols; ++c) {
            mat.at<uchar>(r, c) = at(r, c);
        }
    }
    return mat;
}

bool BWMatrix::readImage(const std::string& path) 
{
    cv::Mat bwImage = cv::imread(path, cv::IMREAD_GRAYSCALE);
    if (bwImage.empty())
        return false;
    fromOpenCV(bwImage);
    return true;
}

BWMatrix BWMatrix::add(int val) const
{
    BWMatrix res(m_rows, m_cols);
    Matrix::add(res, val);
    return res;
}

BWMatrix BWMatrix::multiply(int val) const
{
    BWMatrix res(m_rows, m_cols);
    Matrix::multiply(res, val);
    return res;
}

BWMatrix BWMatrix::subtract(int val) const
{
    BWMatrix res(m_rows, m_cols);
    Matrix::subtract(res, val);
    return res;
}

BWMatrix BWMatrix::operator+(int val) const
{
    return add(val);
}

BWMatrix BWMatrix::operator-(int val) const
{
    return subtract(val);
}

BWMatrix BWMatrix::operator*(int val) const
{
    return multiply(val);
}

BWMatrix& BWMatrix::operator=(const BWMatrix& mat)
{
    Matrix::operator=(mat);
    return *this;
}

std::ostream& operator<<(std::ostream& out, const BWMatrix& mat)
{
    for (size_t r = 0; r < mat.m_rows; ++r) {
        for (size_t c = 0; c < mat.m_rows; ++c) {
            out << (c > 0 ? " " : "") << std::setw(2);
            out << "[";
            out << mat.at(r, c);
            out << "]";
        }
        out << std::endl;
    }
    return out;
}
