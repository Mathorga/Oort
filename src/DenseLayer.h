/*
********************************************************************************
DenseLayer.h

TODO

Copyright (C) 2020  Luka Micheletti
********************************************************************************
*/

#ifndef __DENSE_LAYER__
#define __DENSE_LAYER__

#include "Layer.h"

namespace oort {
    class DenseLayer : public Layer {
    public:
        DenseLayer(const uint32_t inSize, const uint32_t outSize);
        void step(math::dtensor input);
    private:
        // Layer weight matrix.
        math::dtensor2d weight;

        // Layer bias array.
        math::dtensor1d bias;

        // Layer values before activation.
        math::dtensor1d composedValues;

        // Layer values after activation.
        math::dtensor1d activatedValues;

        // Layer activation function.
        math::DUnFunc* activationFunction;
    };
}

#endif
