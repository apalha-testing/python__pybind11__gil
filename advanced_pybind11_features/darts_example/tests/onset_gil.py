import engines

# Setup the evaluator
class custom_evaluator_python(engines.operator_set_evaluator_iface):
    def __init__(self):
        super().__init__()
        print('Initialize my_custom_evaluator_python', flush=True)

    def evaluate(self, state, values):
        # mass accumulation
        values[0] = 1.0
        # mass flux
        values[1] = 2.0
        # fluid internal energy = water_enthalpy + steam_enthalpy - work
        # (in the following expression, 100 denotes the conversion factor from bars to kJ/m3)
        values[2] = 3.0
        # rock internal energy
        values[3] = 4.0
        # energy flux
        values[4] = 5.0
        # fluid conduction
        values[5] = 6.0
        # rock conduction
        values[6] = 7.0
        # temperature
        values[7] = 8.0

        return 0

my_custom_evaluator = custom_evaluator_python()


# Setup the multilinear interpolator
n_vars = 2
n_points = 64
min_p = 0.1
min_e = 0.2
max_p = 10.0
max_e = 20.0
n_axes_points = engines.index_vector([n_points] * n_vars)
n_axes_min = engines.value_vector([min_p, min_e])
n_axes_max = engines.value_vector([max_p, max_e])
my_interpolator = engines.multilinear_adaptive_cpu_interpolator_i_d_2_8(
        my_custom_evaluator, n_axes_points, n_axes_min, n_axes_max
        )

my_interpolator.init()  # it needs to be explicitly initialized

state = engines.value_vector([0.5, 0.8])
block_idx = engines.index_vector([1])
values = engines.value_vector([0., 0., 0., 0., 0., 0., 0., 0.])
derivatives = engines.value_vector([0., 0., 0., 0., 0., 0., 0., 0.])


# Evaluate the interpolator (deadlock)
my_interpolator.get_point_data(1)
