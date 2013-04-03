#pragma once

#include "MembershipFunction.h"

double positiveInfinity = 99999999999999999;
double negativeInfinity = -99999999999999999;

namespace functions {
    class TriangularMembershipFunction: public MembershipFunction {
        private:
            double a;
            double b;
            double c;

        public:
            TriangularMembershipFunction(double a, double b, double c);
            TriangularMembershipFunction(double a, double b);

            virtual double getValue(double input);
            virtual double getClippedValue(double input, double clip);
            virtual double getMax();
            virtual double getMin();
        private:
            void InitializeInstanceFields();
    };
}
