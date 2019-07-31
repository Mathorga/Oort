#include "Nerve.h"
#include "SparsePerceptronNetwork.h"
#include "SparsePerceptronModelParser.h"
#include "LayeredPerceptronModel.h"
#include "KnowledgeParser.h"

using namespace Oort;

int main(int argc, char const *argv[]) {
    uint16_t inputNum = 1;
    uint16_t outputNum = 1;
    char* modelFileName = nullptr;
    float* expectedOutput;
    neuron_value_t* newExpectedOut;

    double startTime = 0;
    double endTime = 0;
    double execTime = 0;

    // Input check.
    if (argc > 2 || argc <= 1) {
        printf("Usage: %s [modelFile]\n", argv[0]);
        return -1;
    }
    if (argc > 1) {
        modelFileName = (char*) argv[1];
    }

    SparsePerceptronModelParser* parser = new SparsePerceptronModelParser();
    parser->readFile(modelFileName);
    SparsePerceptronNetwork* brain = new SparsePerceptronNetwork(parser->getModel());

    LayeredPerceptronModel* layeredModel = new LayeredPerceptronModel();
    layeredModel->print();
    // SparsePerceptronNetwork* brain = new SparsePerceptronNetwork(5184, 3);
    // parser->setModel(brain->getModel());
    // parser->writeFile(modelFileName);


    // Set expected output for the current input.
    newExpectedOut = (neuron_value_t*) malloc(outputNum * sizeof(vector_size_t));
    newExpectedOut[0] = 0.6;
    brain->setExpectedOutput(newExpectedOut);
    // brain->print();










    KnowledgeParser* kp = new KnowledgeParser();
    kp->readFile((char*) "./res/knl/testBin.knl");
    kp->getKnowledge()->print();
    KnowledgeParser* kp2 = new KnowledgeParser();
    kp2->setKnowledge(kp->getKnowledge());
    kp2->setDepth(2);
    kp2->writeFile((char*) "./res/knl/test2.knl");
















    // Main loop of the program.
    for (uint16_t i = 0;; i ++) {
        startTime = getTime();
        brain->run();
        brain->correct();
        // brain->describe();
        // brain->run();
        endTime = getTime();
        execTime = endTime - startTime;
        usleep(10000);
        // printf("Time: %f s\n", execTime);
        printf("Output: %.7f\n", brain->getOutput()[0]);
    }

    return 0;
}
