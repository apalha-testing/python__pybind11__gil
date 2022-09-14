cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(vector_error)

include_directories("${CMAKE_SOURCE_DIR}/src")
include_directories("${CMAKE_SOURCE_DIR}/src/pybind11")

file (GLOB SOURCE_FILES "src/*.cpp"  "src/*.h")
file (GLOB PYBIND_FILES "src/pybind11/*.cpp")

# Set up such that XCode organizes the files
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES} ${PYBIND_FILES} )

find_package(pybind11 REQUIRED)
pybind11_add_module(vector_error
	${SOURCE_FILES}
	${PYBIND_FILES}
)

install(TARGETS vector_error
  COMPONENT python
  LIBRARY DESTINATION "${PYTHON_LIBRARY_DIR}"
  )
