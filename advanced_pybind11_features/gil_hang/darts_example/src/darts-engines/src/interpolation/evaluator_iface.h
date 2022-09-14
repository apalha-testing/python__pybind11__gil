//*************************************************************************
//    Copyright (c) 2018
//            Mark Khait         M.Khait@tudelft.nl
//            Denis Voskov    D.V.Voskov@tudelft.nl
//    Delft University of Technology, the Netherlands
//
//    This file is part of the Delft Advanced Research Terra Simulator (DARTS)
//
//    DARTS is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as
//    published by the Free Software Foundation, either version 3 of the
//    License, or (at your option) any later version.
//
//    DARTS is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public
//    License along with DARTS. If not, see <http://www.gnu.org/licenses/>.
// *************************************************************************

#ifndef B7CB6645_948A_4B50_A7D5_980BEFD16090
#define B7CB6645_948A_4B50_A7D5_980BEFD16090

#include <vector>
#include "globals.h"

class timer_node;

/**
 * @brief Virtual interface class for evaluation of physical properties values
 *        Implemented mainly by different C++ physical kernels from darts.physics
 *        However, pure Python implementation is also possible through inheritance
 *
 */
class property_evaluator_iface
{
public:
   property_evaluator_iface(){};

   /**
   * @brief Compute property values for specified state
   *
   * @param state Coordinates in parameter space, where operators to be evaluated
   * @return double property value
   */
   virtual double evaluate(const std::vector<double> &state) = 0;

   /**
   * @brief Compute property values for all specified states
   *        A surrogate for vectorized evaluate function
   *
   * @param[in] states array of states
   * @param[in] n_blocks the number of states
   * @param[out] values  evaluated property values
   * @return int
   */
   int evaluate(const std::vector<double> &states, int n_blocks, std::vector<double> &values)
   {
      size_t state_len = states.size() / n_blocks;
      std::vector<double> state(state_len);
      values.resize(n_blocks);
      for (int i = 0; i < n_blocks; i++)
      {
         std::copy(states.begin() + i * state_len, states.begin() + (i + 1) * state_len, state.begin());
         values[i] = evaluate(state);
      }
      return 0;
   }
};

/**
 * @brief Virtual interface class for evaluation of operators values
 *        Implemented mainly by different C++ physical kernels from darts.physics
 *        However, pure Python implementation is also possible through inheritance
 *
 */
class operator_set_evaluator_iface
{
public:
   /**
   * @brief Construct a new operator set evaluator iface object
   *
   */
   operator_set_evaluator_iface() { timer = 0; };

   /**
   * @brief Initialize timer node to provide timing for operator set evaluation
   *
   * @param[in] timer_ Timer node of global timer.
   */
   void init_timer_node(timer_node *timer_) { timer = timer_; };

   /**
   * @brief Compute operators values for specified state
   *
   * @param state Coordinates in parameter space, where operators to be evaluated
   * @param values Evaluated operators values
   * @return int 0 if evaluation is successful
   */
   virtual int evaluate(const std::vector<double> &state, std::vector<double> &values) = 0;

   timer_node *timer;
};

/**
 * @brief Virtual interface class for evaluation of operators values and their gradients
 *        Mainly implemented by a variety of interpolators following OBL method
 *        But also can be derived by, for instance, AD-compatible physics kernel
 *        For GPU-compatible compilation, the interface provides two options: for computations on host and on device.
 *
 *
 */
class operator_set_gradient_evaluator_iface : public operator_set_evaluator_iface
{
public:
   /**
     * @brief Initialize evaluator, default empty implementation
     * Adds a possibility to initialize the object using properties assigned after construction
     *
     * @return int 0 if successful
     */
   virtual int init() { return 0; };

   /**
     * @brief Get the number of supporting points for the given axis, default empty implementation
     *
     * @param axis index of axis in question
     */
   virtual int get_axis_n_points(int axis) { return 0; };
   /**
     * @brief Get the minimum value for given axis, default empty implementation
     *
     * @param axis index of axis in question
     */
   virtual double get_axis_min(int axis) { return 0; };

   /**
     * @brief Get the maximum value for given axis, default empty implementation
     *
     * @param axis index of axis in question
     */
   virtual double get_axis_max(int axis) { return 0; };

   /**
     * @brief Get the number of interpolations that took place, default empty implementation
     *
     */
   virtual uint64_t get_n_interpolations() { return 0; };

   /**
     * @brief Get the number of supporting points used, default empty implementation
     *
     * @return the number of supporting points used
     */
   virtual uint64_t get_n_points_used() { return 0; };

   /**
     * @brief Get the total number of supporting points in parameter space, default empty implementation
     *
     * @return the total number of supporting points
     */
   virtual uint64_t get_n_points_total() { return 0; };

   /**
     * @brief Compute operators values and their gradients for every specified state
     *
     * @param[in]   states        Array of coordinates in parameter space, where operators to be evaluated
     * @param[in]   states_idxs   Indexes of states in the input array which are marked for evaluation
     * @param[out]  values        Evaluated operators values
     * @param[out]  derivatives   Evaluated operators gradients
     * @return 0 if evaluation is successful
     */
   virtual int evaluate_with_derivatives(const std::vector<double> &states, const std::vector<int> &states_idxs,
                                         std::vector<double> &values, std::vector<double> &derivatives) = 0;

#ifdef WITH_GPU
   /**
   * @brief Compute operators values for specified state on device
   *
   * @param state Coordinates in parameter space, where operators to be evaluated
   * @param values Evaluated operators values
   * @return int 0 if evaluation is successful
   */
   virtual int evaluate_d(double *state_d, double *values_d) = 0;
   /**
     * @brief Compute operators values and their gradients for every specified state on GPU device.
     *
     * @param[in]   n_states_idxs      Number of states marked for interpolation, the length of states_idxs_d array
     * @param[in]   state_d       Array of coordinates in parameter space, where operators to be evaluated, device pointer
     * @param[in]   states_idxs_d Indexes of states in the input array which are marked for evaluation, device pointer
     * @param[out]  values_d      Evaluated operators values, device pointer
     * @param[out]  derivatives_d Evaluated operators gradients, device pointer
     * @return 0 if evaluation is successful
     */
   virtual int evaluate_with_derivatives_d(int n_states_idxs, double *state_d, int *states_idxs_d,
                                           double *values_d, double *derivatives_d) = 0;
#endif
};

/**
 * @brief A class for evaluation of operators values and their gradients on host
 *        Provides straightforward device implementation by sending input data to host, calling the host function,
 *        and sending the output back to device
 *
 *
 */
class operator_set_gradient_evaluator_cpu : public operator_set_gradient_evaluator_iface
{
public:
#ifdef WITH_GPU

   /**
   * @brief Compute operators values for specified state on device
   *
   * @param state Coordinates in parameter space, where operators to be evaluated
   * @param values Evaluated operators values
   * @return int 0 if evaluation is successful
   */
   virtual int evaluate_d(double *state_d, double *values_d) final;

   /**
     * @brief Compute operators values and their gradients for every specified state on GPU device.
     *
     * @param[in]   n_states_idxs      Number of states marked for interpolation, the length of states_idxs_d array
     * @param[in]   state_d       Array of coordinates in parameter space, where operators to be evaluated, device pointer
     * @param[in]   states_idxs_d Indexes of states in the input array which are marked for evaluation, device pointer
     * @param[out]  values_d      Evaluated operators values, device pointer
     * @param[out]  derivatives_d Evaluated operators gradients, device pointer
     * @return 0 if evaluation is successful
     */
   virtual int evaluate_with_derivatives_d(int n_states_idxs, double *state_d, int *states_idxs_d,
                                           double *values_d, double *derivatives_d) final;
#endif
};

#ifdef WITH_GPU
/**
 * @brief A class for evaluation of operators values and their gradients on device
 *        Provides straightforward host implementation by sending input data to device, calling the device function,
 *        and sending the output back to host
 *
 */
class operator_set_gradient_evaluator_gpu : public operator_set_gradient_evaluator_iface
{
public:
   /**
   * @brief Compute operators values for specified state
   *
   * @param state Coordinates in parameter space, where operators to be evaluated
   * @param values Evaluated operators values
   * @return int 0 if evaluation is successful
   */
   virtual int evaluate(const std::vector<double> &state, std::vector<double> &values) final;
   /**
     * @brief Compute operators values and their gradients for every specified state
     *
     * @param[in]   states        Array of coordinates in parameter space, where operators to be evaluated
     * @param[in]   states_idxs   Indexes of states in the input array which are marked for evaluation
     * @param[out]  values        Evaluated operators values
     * @param[out]  derivatives   Evaluated operators gradients
     * @return 0 if evaluation is successful
     */
   virtual int evaluate_with_derivatives(const std::vector<double> &states, const std::vector<int> &states_idxs,
                                         std::vector<double> &values, std::vector<double> &derivatives) final;
};
#endif

#endif /* B7CB6645_948A_4B50_A7D5_980BEFD16090 */
