#pragma once

#include "modifier/FzSet.h"
#include "controller/BasicFuzzyController.h"
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace modifier;

using controller::BasicFuzzyController;
using controller::FuzzyOp;
using deffuzifyer::CentroidMethod;
using variables::LinguisticVariable;

class FuzzyLogicEngine {

    public:
        std::ofstream myfile;
        double positiveInfini;
        std::map<std::string, FzSet*> lingVars;
        BasicFuzzyController *bfc;
        FuzzyLogicEngine *fle;

        virtual void doRow(std::vector<std::string> row);
        virtual void readFail();
        virtual bool testFuzzy(int bandwidth, int cpu, int connections);
        virtual ~FuzzyLogicEngine();
        virtual double stringToDouble(const std::string& s);
        virtual std::vector<std::string> split(const std::string &s, char delim);
        virtual std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems);
        virtual double dump_map(const std::map<std::wstring, double>& map);
};
