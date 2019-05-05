#ifndef __PERCEPTRON_SYNAPSE__
#define __PERCEPTRON_SYNAPSE__

#include "Synapse.h"
#include "Perceptron.h"

class Perceptron;

class PerceptronSynapse : public Synapse {
public:
    // Constructors.
    PerceptronSynapse();
    PerceptronSynapse(synapse_weight_t weight);
    PerceptronSynapse(Perceptron* inputNeuron);
    PerceptronSynapse(Perceptron* inputNeuron, synapse_weight_t weight);

    // Getters.
    Perceptron* getInputNeuron();

private:
    Perceptron* inputNeuron;
};

#endif
