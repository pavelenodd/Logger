#pragma once
#include "Server/server.h"

#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Debug/debugger.h"

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
  Debugger* debugger_;

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
/*
работы по подключению TCP/IP сервера к проекту
 */

class TCP_IP_Logger : public BaseLogger {
 private:
  boost::asio::io_context io_context_;
  static TCP_IP_Logger* instance_;
  int port_;
  TCP_Server* tcp_server_;

 protected:
 public:
 private:
  // Приватный конструктор для предотвращения создания объектов извне
  TCP_IP_Logger(int L_port) : port_(L_port) {
    tcp_server_ = new TCP_Server(io_context_, port_);
    debugger_ = new Debugger("TCP/IP Logger");
  }
  ~TCP_IP_Logger() { delete tcp_server_; }

 public:
  /**
   * Метод для инициализации TCP/IP логгера
   */
  void StartConected() override {
    debugger_->Info("Starting TCP/IP Logger on port " + std::to_string(port_));
    tcp_server_->StartAccept();
  }

  // Метод для получения единственного экземпляра класса (Singleton)
  static TCP_IP_Logger* Get_Instance(int L_port) {
    if (instance_ == nullptr) {
      instance_ = new TCP_IP_Logger(L_port);
    }
    return instance_;
  }

  void Connected() override {
    debugger_->Info("Connected to TCP/IP server on port " +
                    std::to_string(port_));
  }
  void Reconected() override {
    debugger_->Info("Reconnected to TCP/IP server on port " +
                    std::to_string(port_));
  }
  void Disconnected() override {
    debugger_->Info("Disconnected from TCP/IP server");
  }
  void HanleMessage(std::string message) override {
    debugger_->Info("Received message: " + message);
  }
};
TCP_IP_Logger* TCP_IP_Logger::instance_ = nullptr;  // TODO перенести в cpp
