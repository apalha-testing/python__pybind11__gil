#include "../include/interpolate_bits/interpolate.hpp"

#include <iostream>

namespace interpolate {

  multilinear_adaptive_cpu_interpolator::multilinear_adaptive_cpu_interpolator(operator_set_evaluator *supporting_point_evaluator_input){
    this->supporting_point_evaluator = supporting_point_evaluator_input;
  };

  double multilinear_adaptive_cpu_interpolator::point_data_t(double value){
    omp_set_num_threads(THREAD_NUM);
    #pragma omp parallel
    {
      usleep(5000 * omp_get_num_threads()); // do this to avoid race condition while printing
      std::cout << "Number of available threads: " << omp_get_num_threads() << std::endl;
      // each thread can also get its own number
      std::cout << "Current thread number: " << omp_get_thread_num() << std::endl;
      std::cout << "Hello, World! " << this->supporting_point_evaluator->evaluate(value) + this->supporting_point_evaluator->evaluate(value) << "\n"<< std::endl;
    }
    return 1.0;
  };

}
