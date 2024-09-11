#pragma once
#include "Server/server.h"

#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using boost_tcp = boost::asio::ip::tcp;

/**
 * Базовый класс логгера (интерфейс)
 * \fn StartConected-для инициализации логгера
 * \fn Connected - для обработки подключения
 * \fn Reconected - для обработки переподключения
 * \fn Disconnected - для обработки отключения
 * \fn HanleMessage - для обработки полученного сообщения
 */
class BaseLogger {
 protected:
  BaseLogger() {}

  virtual ~BaseLogger() {};

 public:
  virtual void StartConected() = 0;
  virtual void Connected() = 0;
  virtual void Reconected() = 0;
  virtual void Disconnected() = 0;
  virtual void HanleMessage(std::string message) = 0;
};

class TCP_IP_Logger : public BaseLogger {
 private:
  boost::asio::io_context io_context_;
  int port_;
  static TCP_IP_Logger* instance_;
  TCP_IP_Logger* logger_;

 protected:
 public:
 private:
  // Приватный конструктор для предотвращения создания объектов извне
  TCP_IP_Logger(int L_port) : port_(L_port) {
    static MyServer server(io_context_);
  }
  ~TCP_IP_Logger() = default;

 public:
  /**
   * Метод для инициализации TCP/IP логгера
   */
  void StartConected() override {
    std::cout << "TCP/IP Logger initialized on port " << port_ << std::endl;
  }

  // Метод для получения единственного экземпляра класса (Singleton)
  static TCP_IP_Logger* Get_Instance(int L_port) {
    if (instance_ == nullptr) {
      instance_ = new TCP_IP_Logger(L_port);
    }
    return instance_;
  }

  void Connected() override {
    std::cout << "Connected to TCP/IP server on port " << port_ << std::endl;
  }
  void Reconected() override {
    std::cout << "Reconnected to TCP/IP server on port " << port_ << std::endl;
  }
  void Disconnected() override {
    std::cout << "Disconnected from TCP/IP server" << std::endl;
  }
  void HanleMessage(std::string message) override {
    std::cout << "Received message: " << message << std::endl;
  }
};
TCP_IP_Logger* TCP_IP_Logger::instance_ = nullptr;  // TODO перенести в cpp
