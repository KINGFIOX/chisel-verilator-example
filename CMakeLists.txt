cmake_minimum_required(VERSION 3.12)
project(GCD)

set(VERILATOR_ROOT /usr/share/verilator)

find_package(verilator HINTS ${VERILATOR_ROOT})
if (NOT verilator_FOUND)
  message(FATAL_ERROR "Verilator was not found. Either install it, or set the VERILATOR_ROOT environment variable")
endif()

add_executable(${PROJECT_NAME} "src/test/cxx/GCD.cxx")
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# Add the Verilated circuit to the target
# COVERAGE 覆盖率统计
verilate(${PROJECT_NAME} COVERAGE TRACE
  VERILATOR_ARGS -Wall
  SOURCES "generated/GCD.sv")