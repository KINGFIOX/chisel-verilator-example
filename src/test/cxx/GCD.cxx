#include "VGCD.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <cstdlib>
#include <iostream>
#include <memory>

/**
 * @brief 一个正确的 gcd 实现
 *
 * @param a
 * @param b
 * @return int
 */
int gcd(uint16_t a, uint16_t b) {
  while (b != 0) {
    int remainder = a % b;
    a = b;
    b = remainder;
  }
  return a;
}

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true); // 启用波形跟踪

  size_t fail_cnt = 0;
  size_t success_cnt = 0;

  auto dut = std::make_unique<VGCD>();
  VerilatedVcdC *vcd = new VerilatedVcdC();
  dut->trace(vcd, 99);  // 设定跟踪级别
  vcd->open("gcd.vcd"); // 打开VCD文件

  // 重置设备
  dut->reset = 1;
  dut->clock = 0;
  for (int i = 0; i < 5; i++) {
    dut->clock = !dut->clock;
    dut->eval();
    vcd->dump(10 * i); // 记录时间点
  }
  dut->reset = 0;

  srand(time(NULL));
  uint16_t x = rand();
  uint16_t y = rand();

  // 主仿真循环
  for (int cycle = 0; cycle < 400; cycle++) {
    dut->io_loadingValues = (cycle == 5);
    dut->io_value1 = x;
    dut->io_value2 = y;

    dut->clock = 1;
    dut->eval();
    vcd->dump(10 * cycle + 5);

    dut->clock = 0;
    dut->eval();
    vcd->dump(10 * cycle + 10);

    dut->io_loadingValues = 0;
  }

  // 收集结果和清理
  uint16_t top_z = dut->io_outputGCD;

  dut->final();
  vcd->close(); // 关闭VCD文件

  if (uint16_t z = gcd(x, y); z == top_z) {
    std::cout << "success" << std::endl;
  } else {
    std::cout << "fail" << std::endl;
    std::cout << "x: " << (int)x << std::endl;
    std::cout << "y: " << (int)y << std::endl;
    std::cout << "gcd(x, y): " << (int)z << std::endl;
    std::cout << "dut(x, y): " << (int)top_z << std::endl;
  }

  return 0;
}
