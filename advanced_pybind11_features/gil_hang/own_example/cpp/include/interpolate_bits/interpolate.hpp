#include <string>
#include <memory>
#include <omp.h>
#include <unistd.h>
#include <iostream>

#define THREAD_NUM 4

#ifndef INTERPOLATE_H
#define INTERPOLATE_H

namespace interpolate {


class operator_set_evaluator {

public:

    operator_set_evaluator() {};

    virtual double evaluate(double value) = 0;
};


class multilinear_adaptive_cpu_interpolator {

public:
    operator_set_evaluator *supporting_point_evaluator;

    multilinear_adaptive_cpu_interpolator(operator_set_evaluator *supporting_point_evaluator_input);

    double get_point_data(double value);
};

}

#endif
