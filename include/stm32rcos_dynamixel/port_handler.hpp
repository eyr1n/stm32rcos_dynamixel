#pragma once

#include <cstdint>

#include <stm32rcos/core.hpp>
#include <stm32rcos/peripheral/uart.hpp>

#include "port_handler.h"

namespace stm32rcos_dynamixel {

class PortHandler : public dynamixel::PortHandler {
public:
  PortHandler(stm32rcos::peripheral::UARTBase &uart) : uart_{uart} {
    is_using_ = false;
  }

  ~PortHandler() override { closePort(); }

  bool openPort() override {
    return false; // not implemented
  }

  void closePort() override {
    // not implemented
  }

  void clearPort() override { uart_.flush(); }

  void setPortName(const char *) override {
    // not implemented
  }

  char *getPortName() override {
    return nullptr; // not implemented
  }

  bool setBaudRate(const int baudrate) override {
    baud_rate_ = baudrate;
    return true;
  }

  int getBaudRate() override { return baud_rate_; }

  int getBytesAvailable() override { return uart_.available(); }

  int readPort(uint8_t *packet, int length) override {
    if (!uart_.receive(packet, length, timeout_)) {
      is_timeout_ = true;
      return 0;
    }
    return length;
  }

  int writePort(uint8_t *packet, int length) override {
    if (!uart_.transmit(packet, length, osWaitForever)) {
      return 0;
    }
    return length;
  }

  void setPacketTimeout(uint16_t packet_length) override {
    timeout_ = 1000.0f / baud_rate_ * packet_length * 10 + 10;
  }

  void setPacketTimeout(double msec) override { timeout_ = msec; }

  bool isPacketTimeout() override {
    if (is_timeout_) {
      is_timeout_ = false;
      return true;
    }
    return false;
  }

private:
  stm32rcos::peripheral::UARTBase &uart_;
  uint32_t baud_rate_ = 0;
  uint32_t timeout_ = 0;
  bool is_timeout_ = false;
};

} // namespace stm32rcos_dynamixel
