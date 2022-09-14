import interpolate

class fancy_evaluator(interpolate.operator_set_evaluator):

    def __init__(self):
        super().__init__()

    def evaluate(self, double):
        return 2.0*double

my_evaluator = fancy_evaluator()

my_interpolator = interpolate.multilinear_adaptive_cpu_interpolator(my_evaluator)

my_interpolator.get_point_data(2.0)
