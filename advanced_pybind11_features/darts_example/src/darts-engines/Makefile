include conf_gcc.mk

TARGET      = ../../tests/engines.so
IFLAGS      = -I./src -I./src/interpolation -I./src/pybind11
IFLAGS      += -I./lib/pybind11 $(shell python3-config --includes)

# solvers library, linked to engines, is build inside manylinux2010, where D_GLIBCXX_USE_CXX11_ABI is locked to 0
# Force the same value here for correct linking when engines are built elsewhere, and solvers are taken from manylinux2010
DFLAGS      = -DPYBIND11_ENABLED -D_GLIBCXX_USE_CXX11_ABI=0
LFLAGS_BASE	+= $(PYTHON_LFLAGS)
LFLAGS_MT  	= $(LFLAGS_BASE)
LFLAGS      = $(LFLAGS_BASE)

BUILD_DIR	= build

SUBDIRS     = interpolation pybind11
BUILD_DIRS  = $(BUILD_DIR) $(patsubst %,$(BUILD_DIR)/%,$(SUBDIRS))

#$(info    IFLAGS is $(IFLAGS))

OBJ_NVCC_DONT_LIKE = pybind11/py_main.o


OBJ =  interpolation/interpolator_base.o \
    globals.o \
		pybind11/py_globals.o \
    pybind11/py_evaluator_iface.o \
    pybind11/py_operator_set_interpolator_pz.o \
    pybind11/py_operator_set_interpolator_pz_cap_gra.o \
    pybind11/py_operator_set_interpolator_pz_cap_gra_dif.o \
    pybind11/py_operator_set_interpolator_pz_dif.o \
    pybind11/py_operator_set_interpolator_pz_kin.o \
    pybind11/py_operator_set_interpolator_pz_kin_phi.o \
    pybind11/py_operator_set_interpolator_pz_kin_dif.o \
    pybind11/py_operator_set_interpolator_pz_kin_dif_np.o \
    pybind11/py_operator_set_interpolator_pz_sol.o \
    pybind11/py_operator_set_interpolator_pze.o \
    pybind11/py_operator_set_interpolator_pze_dvelocity.o \
    pybind11/py_operator_set_interpolator_pze_gra.o \
    pybind11/py_operator_set_interpolator_pzt.o \
    pybind11/py_operator_set_interpolator_pzt_kin.o \
    pybind11/py_operator_set_interpolator_super.o \
    pybind11/py_operator_set_interpolator_rates.o \
    engines_build_info.o


OBJ_D = $(patsubst %,$(BUILD_DIR)/%,$(OBJ) $(OBJ_NVCC_DONT_LIKE))
OBJ_MT_D = $(patsubst %.o,$(BUILD_DIR)/%.mt.o,$(OBJ) $(OBJ_NVCC_DONT_LIKE))
OBJ_NVCC_DONT_LIKE_D = $(patsubst %.o,$(BUILD_DIR)/%.nonvcc.o,$(OBJ_NVCC_DONT_LIKE))

OBJ_DEBUG_D = $(patsubst %.o,$(BUILD_DIR)/%.od,$(OBJ) $(OBJ_NVCC_DONT_LIKE))
OBJ_MT_DEBUG_D = $(patsubst %.o,$(BUILD_DIR)/%.mt.od,$(OBJ) $(OBJ_NVCC_DONT_LIKE))
OBJ_NVCC_DONT_LIKE_DEBUG_D = $(patsubst %.o,$(BUILD_DIR)/%.nonvcc.od,$(OBJ_NVCC_DONT_LIKE))


OBJ_ITORS = $(filter $(BUILD_DIR)/pybind11/py_operator_set_interpolator%, $(OBJ_D) $(OBJ_GPU_D) $(OBJ_MT_D) $(OBJ_DEBUG_D) $(OBJ_GPU_DEBUG_D) $(OBJ_MT_DEBUG_D))
OBJ_ITORS += $(filter $(BUILD_DIR)/interpolation%, $(OBJ_D) $(OBJ_GPU_D) $(OBJ_MT_D) $(OBJ_DEBUG_D) $(OBJ_GPU_DEBUG_D) $(OBJ_MT_DEBUG_D))

BUILD_MACHINE := $(shell whoami)@$(shell hostname)
BUILD_DATE := $(shell TZ=Europe/Amsterdam date +"%d/%m/%Y, %H:%M:%S")
BUILD_GIT_HASH := $(shell git describe --always --dirty --match 'NOT A TAG')

dir_guard=@mkdir -p $(@D)


default: $(TARGET)


.PHONY: gpu mt clean clean_target build_dirs build_info

# Additional rule to force rebuild build_info.cpp file every time
src/engines_build_info.cpp: build_info
    $(shell echo "#include \"engines_build_info.h\""  > src/engines_build_info.cpp)
    $(shell echo "const char *ENGINES_BUILD_DATE = \"$(BUILD_DATE)\";"  >> src/engines_build_info.cpp)
    $(shell echo "const char *ENGINES_BUILD_MACHINE = \"$(BUILD_MACHINE)\";"  >> src/engines_build_info.cpp)
    $(shell echo "const char *ENGINES_BUILD_GIT_HASH = \"$(BUILD_GIT_HASH)\";"  >> src/engines_build_info.cpp)

.PHONY: gpu mt debug gpu_debug mt_debug clean clean_target build_dirs clean_itors

build_dirs: $(BUILD_DIRS)

$(BUILD_DIRS):
	mkdir -p $@


$(BUILD_DIR)/%.o:          src/%.cpp
	$(CXX) $(CXXFLAGS) $(IFLAGS) $(DFLAGS)  -c -o  $@ $<


# template class instantiation (for interpolators, for example) has been moved to expose functions
# in order to simplify and generalize the code. So *.cu do not exist anymore
# consequently, for GPU build those py_*.cpp files which expose gpu classes have to be compiled by nvcc
# the simpliest solution is to compile all cpp files by nvcc using --x=cu
$(BUILD_DIR)/%.mt.o:          src/%.cpp
	$(CXX) $(CXXFLAGS) $(OMP_FLAG) $(IFLAGS) $(DFLAGS)  -c -o  $@ $<

$(BUILD_DIR)/%.od:          src/%.cpp
	$(CXX) $(CXXFLAGS_DEBUG) $(IFLAGS) $(DFLAGS)  -c -o  $@ $<

# template class instantiation (for interpolators, for example) has been moved to expose functions
# in order to simplify and generalize the code. So *.cu do not exist anymore
# consequently, for GPU build those py_*.cpp files which expose gpu classes have to be compiled by nvcc
# the simpliest solution is to compile all cpp files by nvcc using --x=cu
$(BUILD_DIR)/%.mt.od:          src/%.cpp
	$(CXX) $(CXXFLAGS_DEBUG) $(OMP_FLAG) $(IFLAGS) $(DFLAGS)  -c -o  $@ $<



$(TARGET): build_dirs $(OBJ_D) $(LIN_LIB)
	$(CXX) -shared -o $(TARGET) $(OBJ_D) $(LFLAGS)

mt: build_dirs $(OBJ_MT_D) $(LIN_LIB)
	$(CXX) -undefined dynamic_lookup -shared -o $(TARGET) $(OBJ_MT_D) $(LFLAGS_MT) $(OMP_FLAG)

debug: build_dirs $(OBJ_DEBUG_D) $(LIN_LIB)
	$(CXX) -shared -o $(TARGET) $(OBJ_DEBUG_D) $(LFLAGS)

mt_debug: build_dirs $(OBJ_MT_DEBUG_D) $(LIN_LIB)
	$(CXX) -shared -o $(TARGET) $(OBJ_MT_DEBUG_D) $(LFLAGS_MT) $(OMP_FLAG)



clean:
	rm -rf $(TARGET) $(OBJ_D) $(OBJ_MT_D) $(OBJ_DEBUG_D) $(OBJ_MT_DEBUG_D) $(OBJ_NVCC_DONT_LIKE_D)

clean_target:
	rm -rf $(TARGET)

clean_itors:
	rm -rf $(OBJ_ITORS)
