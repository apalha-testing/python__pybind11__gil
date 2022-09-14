# Advanced pybind11 features

This project is a stripped down version of DARTS, only containing the parts that generate the error.

## Requirements
No additional requirements than the files provided.

## Setup with Make
The build system is based on a Makefile.

The idea here is:
1. In `src/darts-engines` copy the configuration make file into `conf_gcc.mk`, for example for linux

```
  cp conf_gcc_linux.mk conf_gcc.mk
```

2. Run make
```
  make mt
```

3. This should generate `engines.so` file inside `tests`.

## Run the example
To run the example just move into the folder `tests` and run the python example `onset_gil.py`

```
cd tests
python onset_gil.py
```
