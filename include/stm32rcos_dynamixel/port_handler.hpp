#pragma once

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
    baudrate_ = baudrate;
    tx_time_per_byte = (1000.0 / (double)baudrate) * 10.0;
    return true;
  }

  int getBaudRate() { return baudrate_; }

  int getBytesAvailable() { return uart_.available(); }

  int readPort(uint8_t *packet, int length) {
    if (!uart_.receive(packet, length, packet_timeout_)) {
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
    packet_timeout_ = (tx_time_per_byte * (double)packet_length) +
                      (LATENCY_TIMER * 2.0) + 2.0;
  }

  void setPacketTimeout(double msec) { packet_timeout_ = msec; }

  bool isPacketTimeout() {
    if (is_timeout_) {
      is_timeout_ = false;
      return true;
    }
    return false;
  }

private:
  static constexpr int LATENCY_TIMER = 4;

  UART_ &uart_;
  int baudrate_ = 0;
  double packet_timeout_ = 0.0;
  double tx_time_per_byte = 0.0;
  bool is_timeout_ = false;
};

} // namespace stm32rcos_dynamixel
