#include "GradientDescender.h"

namespace oort {
    void GradientDescender::run() {
        double error = 0.0;
        math::dtensor1d vals;
        math::itensor1d deps;
        math::dtensor1d dIn;
        math::dtensor1d** dOuts;
        math::dtensor1d dWeight;

        dOuts = (math::dtensor1d**) malloc(this->model->getMemLoopsNum() * sizeof(math::dtensor1d*));
        for (uint32_t i = 0; i < this->model->getMemLoopsNum(); i++) {
            dOuts[i] = (math::dtensor1d*) malloc(this->model->getLayersNum() * sizeof(math::dtensor1d));
            for (uint32_t j = 0; j < this->model->getLayersNum(); j++) {
                math::alloc(&(dOuts[i][j]), this->model->getLayerSize(j));
                math::zero(dOuts[i][j]);
            }
        }

        // Loop for specified epochs number.
        for (uint32_t i = 0; i < this->epochsNum; i++) {
            // Loop through knowledge data.
            for (uint32_t j = 0; j < this->knowledge.getExperiencesNum(); j++) {
                // Feed inputs to the model.
                this->model->feed(this->knowledge.getExperience(j).getInputs());

                // Run the model.
                this->model->compute();

                // Get the predicted output from the model.
                vals = this->model->getOutput();

                // Calculate the error of the model.
                error = math::prim(vals, this->knowledge.getExperience(j).getOutputs(), this->costFunction);
                // printf("\nERROR %f\n", error);

                // Calculate the error detivative to the output layer of the network.
                math::der(dOuts[0][this->model->getLayersNum() - 1], vals, this->knowledge.getExperience(j).getOutputs(), this->costFunction);
                // printf("\nSTART");
                // print(dOuts[0][this->model->getLayersNum() - 1]);
                // print(vals);
                // print(this->knowledge.getExperience(j).getOutputs());
                // printf("END\n");

                // Backpropagate the error.
                for (int32_t l = this->model->getLayersNum() - 1; l >= 0; l--) {
                    // Allocate derived values.
                    math::alloc(&dIn, this->model->getLayerSize(l));
                    // Allocate delta weights.
                    math::alloc(&dWeight, this->model->getLayerSize(l));

                    // Get layer dependencies.
                    deps = this->model->getLayerDeps(l);

                    // Compute input derivative for the current layer.
                    math::hmul(dIn, this->model->getLayerComposedVals(l), dOuts[0][l]);
                    // printf("\nDIn, %d", l);
                    // print(dIn);
                    // printf("\nDOuts, %d", l);
                    // print(dOuts[0][l]);
                    // printf("\nCompVals, %d", l);
                    // print(this->model->getLayerComposedVals(l));

                    // Add up to all dOuts.
                    for (uint32_t d = 0; d < deps.width; d++) {
                        // printf("\nAdding %d %d\n", d, deps.values[d]);
                        math::cadd(dOuts[0][deps.values[d]], dIn);
                        // printf("\nDIn, %d", l);
                        // print(dIn);
                        // printf("\nDOuts, %d", l);
                        // print(dOuts[0][deps.values[d]]);
                    }

                    // Compute weight delta and apply it.
                    math::hmul(dWeight, this->model->getLayerActivatedVals(l), dOuts[0][l]);
                    // printf("\nDWeight");
                    // print(dWeight);
                    // printf("\nActivVals");
                    // print(this->model->getLayerActivatedVals(l));
                    // printf("\nDOuts, %d", l);
                    // print(dOuts[0][l]);

                    // Reset vals for the next layer.
                    // math::copy(vals, dOut);

                    math::dealloc(dIn);
                    math::dealloc(dWeight);
                }
            //
            //     // Check if batch size or knowledge size is reached. If so
            //     // update weights and biases.
            //     if (j % this->batchSize == 0 || j == this->knowledge.getExperiencesNum() - 1) {
            //         // Update weights and biases.
                // }
            }
        }

        for (uint32_t i = 0; i < this->model->getMemLoopsNum(); i++) {
            for (uint32_t j = 0; j < this->model->getLayersNum(); j++) {
                math::dealloc(dOuts[i][j]);
            }
            delete dOuts[i];
        }
        delete dOuts;

        return;
    }

    // Getters.
    double GradientDescender::getLearningRate() {
        return this->learningRate;
    }
    uint32_t GradientDescender::getBatchSize() {
        return this->batchSize;
    }
    uint32_t GradientDescender::getEpochsNum() {
        return this->epochsNum;
    }

    // Setters.
    void GradientDescender::setLearningRate(double learningRate) {
        this->learningRate = learningRate;
    }
    void GradientDescender::setBatchSize(uint32_t batchSize) {
        this->batchSize = batchSize;
    }
    void GradientDescender::setEpochsNum(uint32_t epochsNum) {
        this->epochsNum = epochsNum;
    }
    void GradientDescender::setKnowledge(Knowledge knowledge) {
        this->knowledge = knowledge;
    }
    void GradientDescender::setCostFunction(math::DT1DBinFunc* costFunction) {
        this->costFunction = costFunction;
    }
}
