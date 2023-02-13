# Generating documentation C++ - pybind11 - python code

In this example is shown how to generate sphinx documentation from docstrings:

* in python (as usual).
* in pybind11 exposure of C++ classes and functions.

## How to test

* Requirements in [`docs/requirements_docs.txt`](requirements_docs.txt) must be installed in your environment.
* Follow installing instructions of main example.
* `source full_build_and_test.sh` will build and test the code, and additionally generate the docs.
  If you want only to generate de docs:

  ``` bash
  cd docs
  make clean
  make html # html is the format, others can be chosen.
  ```

Folder *_build* will be generated. Open `build/html/index.html` in your browser to check the documentation. 

## Things to pay attention to

### Docstrings

Use syntax of [sphinx (rst)](https://sublime-and-sphinx-guide.readthedocs.io/en/latest/packages.html). 

#### In pybind11

In [`src/pybind11/pybind_module.cpp`](../src/pybind11/pybind_module.cpp) we can add docstrings to:

* **Module:** Line 17. 
* **Class:** Line 53.
* **Method or function:** Line 59.

Keep your docstring in between `R"pbdoc(` and `)pbdoc"`, otherwise you'll get compilation errors.
In other functions such as `get_sum` and `get_diff` you can see how to name your arguments in two different ways. Other wise it will name then arg0, arg1 ...

#### In python

Create docstrings as usual (in python), see some examples in [`model_outside.py`](../model_outside.py) and/or [`python/model.py`](../python/model.py).

#### In C++

Nothing to do, use some in-line comments.

### Sphinx configuration and deployment

I kept the same structure, packages and syntax used in darts-package/darts/docs.

* In [api.rst](api.rst) are the commands to auto-generate the documentation from the docstrings.
* Other sections in the docs like [about.md](about.md) should be created in separated files (.md and .rst formats are supported).
* Then, the sections and auto-generated docs should be added to [index.rst](index.rst).

## Not done here

Link to readthedocs.com. Contact Luisa if you have questions about this procedure.

## Side notes

* [model_outside.py](../model_outside.py) had to be created to be able to import vector_error.so (generated pybind11 module). Thus, the python docstrings are taken from this file and not from python/model.py.
