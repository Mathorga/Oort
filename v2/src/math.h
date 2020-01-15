#include <math.h>
// Fixed size int types definitions.
#include <stdint.h>

// Translates bidimensional indexes to a monodimensional one.
// |i| is the row index.
// |j| is the column index.
// |n| is the number of columns (length of the rows).
#define IDX2D(i, j, n) ((i * n) + j)
// Translates tridimensional indexes to a monodimensional one.
// |i| is the index in the first dimension.
// |j| is the index in the second dimension.
// |k| is the index in the third dimension.
// |m| is the size of the first dimension.
// |n| is the size of the second dimension.
#define IDX3D(i, j, k, m, n) (((i * m) + j) + (m * n * k))

namespace oort {
    // Types definitions.
    template <typename T>
    struct tensor {
        uint32_t dimNum;
        uint32_t* dimSizes;
        T* values;
    };
    template <typename T>
    struct tensor1d {
        uint32_t width;
        T* values;
    };
    template <typename T>
    struct tensor2d {
        uint32_t width;
        uint32_t height;
        T* values;
    };
    template <typename T>
    struct tensor3d {
        uint32_t width;
        uint32_t height;
        uint32_t depth;
        T* values;
    };
    struct dtensor {
        uint32_t dimNum;
        uint32_t* dimSizes;
        double* values;
    };
    struct dtensor1d {
        uint32_t width;
        double* values;
    };
    struct dtensor2d {
        uint32_t width;
        uint32_t height;
        double* values;
    };
    struct dtensor3d {
        uint32_t width;
        uint32_t height;
        uint32_t depth;
        double* values;
    };

    struct str {};

    // Functors definitions.
    class UnaryFunction {
    public:
        virtual ~UnaryFunction() {};
        virtual double operator() (const double value) = 0;
    };
    class Sigmoid : public UnaryFunction {
    public:
        Sigmoid() {};
        ~Sigmoid() {};
        double operator() (const double value);
    };
    class FastSigmoid : public UnaryFunction {
    public:
        FastSigmoid() {};
        ~FastSigmoid() {};
        double operator() (const double value);
    };

    // Functions definitions.
    // Calculates the sigmoid of the given value.
    double sigmoid(const double value);
    // Calculates the fast sigmoid of the given value.
    double fsigmoid(const double value);
    // Calculates the derivative sigmoid of the given value.
    double dsigmoid(const double value);
    // Calculates the derivative fast sigmoid of the given value.
    double dfsigmoid(const double value);
    // Matrices functions.
    void mul(double* result,
             double* firstMatrix, uint32_t firstRowsNum, uint32_t firstColsNum,
             double* secondMatrix, uint32_t secondRowsNum, uint32_t secondColsNum);
    // Performs the dot product between 2D tensors <t1> and <t2>.
    void mul(const dtensor2d result, const dtensor2d t1, const dtensor2d t2);
    void hmul(uint32_t* result, uint32_t* firstMatrix, uint32_t* secondMatrix, uint32_t matrixSize);
    void hmul(double* result, double* firstMatrix, double* secondMatrix, uint32_t matrixSize);
    // Performs the Hadamard product between 2D tensors <t1> and <t2>.
    void hmul(const dtensor2d result, const dtensor2d t1, const dtensor2d t2);
    void smul(uint32_t* result, uint32_t value, uint32_t* matrix, uint32_t matrixSize);
    void smul(double* result, double value, double* matrix, uint32_t matrixSize);
    // Performs the scalar product between scalar <value> and 2D tensor <t>.
    void smul(const dtensor2d result, const double value, const dtensor2d t);
    void sigmoid(double* result, double* matrix, uint32_t matrixSize);
    // Calculates the sigmoid of every value of 2D tensor <t> and puts them in
    // <result>.
    void sigmoid(const dtensor2d result, const dtensor2d t);

    // Calculates the derivative of the given function in x = <value>.
    // Default epsilon is 0.01.
    double der(const double value, UnaryFunction* function);
    // Calculates the derivative of the given function in x = <value>, using the
    // given epsilon.
    double der(const double value, UnaryFunction* function, const double epsilon);
    // Calculates the given function in x = <value>.
    double prim(const double value, UnaryFunction* function);
}
