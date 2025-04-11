#pragma once

#include <cstdint>

#include <stm32rcos/core.hpp>

#include "port_handler.h"

namespace stm32rcos_dynamixel {

template <class UART_> class PortHandler : public dynamixel::PortHandler {
public:
  PortHandler(UART_ &uart) : uart_{uart} { is_using_ = false; }

  virtual ~PortHandler() { closePort(); }

  bool openPort() {
    return false; // not implemented
  }

  void closePort() {
    // not implemented
  }

  void clearPort() { uart_.flush(); }

  void setPortName(const char *) {
    // not implemented
  }

  char *getPortName() {
    return nullptr; // not implemented
  }

  bool setBaudRate(const int baudrate) {
    baud_rate_ = baudrate;
    return true;
  }

  int getBaudRate() { return baud_rate_; }

  int getBytesAvailable() { return uart_.available(); }

  int readPort(uint8_t *packet, int length) {
    if (!uart_.receive(packet, length, timeout_)) {
      is_timeout_ = true;
      return 0;
    }
    return length;
  }

  int writePort(uint8_t *packet, int length) {
    if (!uart_.transmit(packet, length, osWaitForever)) {
      return 0;
    }
    return length;
  }

  void setPacketTimeout(uint16_t packet_length) {
    timeout_ = 1000.0f / baud_rate_ * packet_length * 10 + 10;
  }

  void setPacketTimeout(double msec) { timeout_ = msec; }

  bool isPacketTimeout() {
    if (is_timeout_) {
      is_timeout_ = false;
      return true;
    }
    return false;
  }

private:
  UART_ &uart_;
  uint32_t baud_rate_ = 0;
  uint32_t timeout_ = 0;
  bool is_timeout_ = false;
};

} // namespace stm32rcos_dynamixel
