#ifndef RGB_MATRIX_H
#define RGB_MATRIX_H

#include "matrix.h"
#include "bw_matrix.h"

class RGBMatrix : public Matrix
{
public:
    RGBMatrix();
    RGBMatrix(const RGBMatrix& mat);
    RGBMatrix(size_t rows, size_t cols);
    RGBMatrix(size_t rows, size_t cols, int initVal);

    void print() const override;
    void fromOpenCV(const cv::Mat& mat) override;
    cv::Mat toOpenCV() const override;
    bool readImage(const std::string& path) override;

    BWMatrix toBW() const;

    RGBMatrix add(int val) const;
    RGBMatrix multiply(int val) const;
    RGBMatrix subtract(int val) const;

    RGBMatrix operator+(int val) const;
    RGBMatrix operator-(int val) const;
    RGBMatrix operator*(int val) const;
    RGBMatrix& operator=(const RGBMatrix& mat);
    friend std::ostream& operator<<(std::ostream& out, const RGBMatrix& mat);
};

#endif // RGB_MATRIX_H