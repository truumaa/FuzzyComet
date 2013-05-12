#pragma once

#include "modifier/FzSet.h"
#include "controller/BasicFuzzyController.h"
#include <string>
#include <vector>

using namespace modifier;

using controller::BasicFuzzyController;
using controller::FuzzyOp;
using deffuzifyer::CentroidMethod;
using variables::LinguisticVariable;

class FuzzyLogicEngine {

    public:
        virtual void doRow(std::vector<std::string> row);
        virtual void readFail();
        virtual bool testFuzzy(int bandwidth, int cpu, int connections);
        virtual ~FuzzyLogicEngine();
};
