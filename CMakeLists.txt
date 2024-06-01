cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0074 NEW)
cmake_policy(SET CMP0144 NEW)
project(GCD)

# 当然啦，这里要修改成你的 VERILATOR_ROOT, 通常是 /usr/local/share/verilator
set(VERILATOR_ROOT /usr/local/Cellar/verilator/5.024/share/verilator)

find_package(verilator HINTS ${VERILATOR_ROOT})
if (NOT verilator_FOUND)
  message(FATAL_ERROR "Verilator was not found. Either install it, or set the VERILATOR_ROOT environment variable")
endif()

add_executable(${PROJECT_NAME} "src/test/cxx/GCD.cxx")
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# Add the Verilated circuit to the target
# COVERAGE 覆盖率统计
verilate(${PROJECT_NAME} COVERAGE TRACE
  INCLUDE_DIRS "./src/test/cxx"
  VERILATOR_ARGS -Wall -Wno-UNUSEDSIGNAL
  SOURCES "GCD.sv")