#include "math.h"

namespace oort {
    namespace math {
        double sigmoid(const double value) {
            return (1 / (1 + (exp(-value))));
        }
        double fsigmoid(const double value) {
            return 0.5 * value / (1 + abs(value)) + 0.5;
        }
        double dsigmoid(const double value) {
            return sigmoid(value) * (1 - sigmoid(value));
        }
        double dfsigmoid(const double value) {
            return 1 / (2 * pow((1 + abs(value)), 2));
        }
        error mul(double* res,
                  double* firstMatrix, uint32_t firstRowsNum, uint32_t firstColsNum,
                  double* secondMatrix, uint32_t secondRowsNum, uint32_t secondColsNum) {
            error err = error::NO_ERROR;
            for (uint32_t i = 0; i < firstRowsNum; i++) {
                for (uint32_t j = 0; j < secondColsNum; j++) {
                    res[IDX2D(i, j, secondColsNum)] = 0.0;
                    for (uint32_t k = 0; k < firstColsNum; k++) {
                        res[IDX2D(i, j, secondColsNum)] += firstMatrix[IDX2D(i, k, firstColsNum)] * secondMatrix[IDX2D(k, j, secondColsNum)];
                    }
                }
            }
            return err;
        }
        error mul(const dtensor2d res, const dtensor2d t1, const dtensor2d t2) {
            error err = error::NO_ERROR;
            if (t1.width == t2.height &&
                res.height == t1.height &&
                res.width == t2.width) {
                for (uint32_t i = 0; i < t1.height; i++) {
                    for (uint32_t j = 0; j < t2.width; j++) {
                        res.values[IDX2D(i, j, t2.width)] = 0.0;
                        for (uint32_t k = 0; k < t1.width; k++) {
                            res.values[IDX2D(i, j, t2.width)] += t1.values[IDX2D(i, k, t1.width)] * t2.values[IDX2D(k, j, t2.width)];
                        }
                    }
                }
            } else {
                err = error::WRONG_SIZE;
            }
            return err;
        }
        error mul(const dtensor1d res, const dtensor2d t1, const dtensor1d t2) {
            error err = error::NO_ERROR;
            if (t1.width == t2.width &&
                res.width == t1.height) {
                for (uint32_t i = 0; i < t1.height; i++) {
                    res.values[i] = 0.0;
                    for (uint32_t j = 0; j < t2.width; j++) {
                        res.values[i] += t1.values[IDX2D(i, j, t1.width)] * t2.values[j];
                    }
                }
            } else {
                err = error::WRONG_SIZE;
            }
            return err;
        }
        error mul(const dtensor1d res, const dtensor1d t1, const dtensor2d t2) {
            error err = error::NO_ERROR;
            if (t1.width == t2.height &&
                res.width == t2.width) {
                for (uint32_t i = 0; i < t1.width; i++) {
                    for (uint32_t j = 0; j < t2.width; j++) {
                        res.values[IDX2D(i, j, t2.width)] = 0.0;
                        for (uint32_t k = 0; k < t1.width; k++) {
                            res.values[IDX2D(i, j, t2.width)] += t1.values[IDX2D(i, k, t1.width)] * t2.values[IDX2D(k, j, t2.width)];
                        }
                    }
                }
            } else {
                err = error::WRONG_SIZE;
            }
            return err;
        }
        error hmul(uint32_t* res, uint32_t* firstMatrix, uint32_t* secondMatrix, uint32_t matrixSize) {
            error err = error::NO_ERROR;
            for (uint32_t i = 0; i < matrixSize; i++) {
                res[i] = firstMatrix[i] * secondMatrix[i];
            }
            return err;
        }
        error hmul(double* res, double* firstMatrix, double* secondMatrix, uint32_t matrixSize) {
            error err = error::NO_ERROR;
            for (uint32_t i = 0; i < matrixSize; i++) {
                res[i] = firstMatrix[i] * secondMatrix[i];
            }
            return err;
        }
        error hmul(const dtensor2d res, const dtensor2d t1, const dtensor2d t2) {
            error err = error::NO_ERROR;
            if (t1.width == t2.width && res.width == t2.width &&
                t1.height == t2.height && res.height == t2.height) {
                for (uint32_t i = 0; i < res.width * res.height; i++) {
                    res.values[i] = t1.values[i] * t2.values[i];
                }
            }
            return err;
        }
        error smul(uint32_t* res, uint32_t value, uint32_t* matrix, uint32_t matrixSize) {
            error err = error::NO_ERROR;
            for (uint32_t i = 0; i < matrixSize; i++) {
                res[i] = value * matrix[i];
            }
            return err;
        }
        error smul(double* res, double value, double* matrix, uint32_t matrixSize) {
            error err = error::NO_ERROR;
            for (uint32_t i = 0; i < matrixSize; i++) {
                res[i] = value * matrix[i];
            }
            return err;
        }
        error smul(const dtensor2d res, const double value, const dtensor2d t) {
            error err = error::NO_ERROR;
            for (uint32_t i = 0; i < t.width * t.height; i++) {
                res.values[i] = value * t.values[i];
            }
            return err;
        }
        error sigmoid(double* res, double* matrix, uint32_t matrixSize) {
            error err = error::NO_ERROR;
            for (uint32_t i = 0; i < matrixSize; i++) {
                res[i] = sigmoid(matrix[i]);
            }
            return err;
        }
        error sigmoid(const dtensor2d res, const dtensor2d t) {
            error err = error::NO_ERROR;
            for (uint32_t i = 0; i < t.width * t.height; i++) {
                res.values[i] = sigmoid(t.values[i]);
            }
            return err;
        }

        double Sigmoid::operator() (const double value) {
            return 1 / (1 + exp(-value));
        }
        double FastSigmoid::operator() (const double value) {
            return 0.5 * value / (1 + abs(value)) + 0.5;
        }

        double der(const double value, UnaryFunction* function, const double epsilon) {
            return ((*function)(value + epsilon) - (*function)(value - epsilon)) / (2 * epsilon);
        }
        double der(const double value, UnaryFunction* function) {
            return ((*function)(value + 0.01) - (*function)(value - 0.01)) / 0.02;
        }
        double prim(const double value, UnaryFunction* function) {
            return (*function)(value);
        }
    }
}
