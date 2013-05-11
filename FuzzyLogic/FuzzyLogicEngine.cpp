#include "FuzzyLogicEngine.h"
#include "deffuzifyer/CentroidMethod.h"
#include "variables/LinguisticVariable.h"
#include "functions/TrapezoidalMembershipFunction.h"
#include "controller/FuzzyOp.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

using namespace controller;
using namespace variables;
using namespace std;

using controller::BasicFuzzyController;
using controller::FuzzyOp;
using deffuzifyer::CentroidMethod;
using functions::TrapezoidalMembershipFunction;
using modifier::FzSet;
using variables::LinguisticVariable;
using std::cout;

ofstream myfile;



double positiveInfini = std::numeric_limits<double>::infinity();
map<string, FzSet*> lingVars;
BasicFuzzyController *bfc;
FuzzyLogicEngine *fle;

double stringToDouble(const std::string& s) {
    std::istringstream i(s);
    double x;
    if (!(i >> x))
        return 0;
    return x;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void FuzzyLogicEngine::doRow(vector<string> row) {

    if (row.at(0) == "rule") {
        vector<string> elements = split(row.at(1), ',');
        if (elements.at(0) == "and") {
            FzSet* fzset1 = lingVars.find(elements.at(1))->second;
            FzSet* fzset2 = lingVars.find(elements.at(2))->second;
            FzSet* fzset3 = lingVars.find(elements.at(3))->second;
            bfc->addRule(FuzzyOp::fuzzyAnd(fzset1, fzset2), fzset3);
            myfile << "uus rule:" << elements.at(1) << "--" << elements.at(2) << "--" << elements.at(3) << "\n";
        }
    } else {
        string sName = row.at(0);
        wstring name;
        name.assign(sName.begin(), sName.end());
        LinguisticVariable *mv = new LinguisticVariable(name);

        for (int i = 1; (unsigned) i < row.size(); i++) {
            string line = row.at(i);
            vector<string> elements = split(line, ',');
            //label
            string sLabel = elements.at(1);
            wstring label;
            label.assign(sLabel.begin(), sLabel.end());
            double d1 = (elements.at(2) == "inf") ? positiveInfini : stringToDouble(elements.at(2));
            double d2 = (elements.at(3) == "inf") ? positiveInfini : stringToDouble(elements.at(3));
            double d3 = (elements.at(4) == "inf") ? positiveInfini : stringToDouble(elements.at(4));
            double d4 = (elements.at(5) == "inf") ? positiveInfini : stringToDouble(elements.at(5));
            FzSet* fzSet = mv->addSet(label, new TrapezoidalMembershipFunction(d1, d2, d3, d4));
            lingVars.insert(make_pair(elements.at(0), fzSet));
            myfile << "uus lingvar:" << elements.at(0) << "->" << d1 << "--" << d2 << "--" << d3 << "--" << "d4" << "\n";
        }
        bfc->addVariable(mv);
    }
}

void FuzzyLogicEngine::readFail() {
    string line;
    ifstream myfile("testData");
    if (myfile.is_open()) {
        while (myfile.good()) {
            getline(myfile, line);
            vector<string> row = split(line, ':');
            doRow(row);
        }
        myfile.close();
    }
}

double dump_map(const std::map<std::wstring, double>& map) {
    for (std::map<std::wstring, double>::const_iterator it = map.begin(); it != map.end(); it++) {
        //wcout << "Key: " << it->first << endl;
        //myfile.precision(15);
        myfile << "Value: " << it->second << endl;
        return it->second;
    }
    return 0;
}
/*
int main(int argc, char **argv) {
    FuzzyLogicEngine *fle = new FuzzyLogicEngine();
    fle->testFuzzy(100, 20, 150);
}*/

bool FuzzyLogicEngine::testFuzzy(int bandwidth, int cpu, int connections) {
    if (fle == 0) {
        fle = new FuzzyLogicEngine();
        myfile.open("testOutput");
        bfc = new BasicFuzzyController();
        fle->readFail();
    }

    bfc->fuzzify(L"BANDWIDTH", double(bandwidth));
    bfc->fuzzify(L"CPULOAD", double(cpu));
    bfc->fuzzify(L"CONNECTIONS", double(connections));

    CentroidMethod *cm = new CentroidMethod();
    cm->setSamplesPoints(10);
    bfc->setDefuzzifyerMethod(cm);

    //cout << L"Delegate with a grade of truth to2: ";
    double result = dump_map(bfc->defuzzify(L"OFFLOAD"));
    myfile.close();
    if (result > 60) {
        return true;
    } else {
        return false;
    }
}
