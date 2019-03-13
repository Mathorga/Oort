#ifndef __SIMPLE_BRAIN__
#define __SIMPLE_BRAIN__

#include "Brain.h"

class SimpleBrain : public Brain {
public:
    SimpleBrain(uint16_t inputNum, uint16_t outputNum);
    SimpleBrain(Model *inputModel);

    void run();
    void correct();
    void setInput(double *input);
    void setExpectedOutput(double *expectedOutput);
    double *getOutput();

    uint16_t getInputNum();
    uint16_t getOutputNum();
    uint16_t getHiddenNum();
    uint16_t getNeuronsNum();
    uint16_t getSynapsesNum();
    Model* getModel();
    Model::_Neuron *getNeurons();
    Model::_Synapse *getSynapses();
    double calculateNeuronValue(uint16_t neuronNum);
    double activate(double input);
    double dActivate(double input);
    void randomlyAddSynapse();
    void randomlyAddNeuron();
    bool addSynapse(uint16_t inputNeuron, uint16_t outputNeuron);
    bool addNeuron(uint16_t inputNeuron, uint16_t outputNeuron);
    void describe();

protected:
    void computeError();
    void adjustWeights();

private:
    double baseWeight;
    double baseValue;
};

#endif