#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include "../Debug/debugger.h"
using boost::asio::ip::tcp;  // Используем пространство имен для TCP

class TCP_Server {
 private:
  tcp::acceptor acceptor_;  // Объект, который принимает входящие подключения
  const int port_;  // Порт, на котором сервер будет ожидать подключения
  Debugger* debugger_;  // Дебаггер для вывода отладки в консоль

 public:
  void StartAccept() {
    // Создаем новый сокет, используя executor напрямую
    tcp::socket socket(acceptor_.get_executor());
    debugger_->Info("Waiting for a connection...");
    debugger_->Info("port: " + std::to_string(port_));
    // Асинхронно принимаем соединение с клиентом
    acceptor_.async_accept(socket, [this,
                                    &socket](boost::system::error_code ec) {
      // Эта лямбда-функция будет вызвана после успешного подключения клиента
      if (!ec) {
        debugger_->Info("Client connected");
        debugger_->Info("Client connected from " +
                        socket.remote_endpoint().address().to_string() + ":" +
                        std::to_string(socket.remote_endpoint().port()));

        // Читаем данные от клиента
        boost::asio::streambuf buffer;  // Буфер для хранения данных
        boost::asio::read_until(socket, buffer,
                                "\n");  // Чтение данных до символа новой строки

        // Преобразуем данные в строку для удобства
        std::istream is(&buffer);
        std::string message;
        std::getline(is, message);

        debugger_->Info("Received message: " + message);

        // Отправляем ответ клиенту
        std::string response = "Привет, клиент!\n";
        boost::asio::write(socket, boost::asio::buffer(response));

        // После отправки ответа, закрываем соединение с клиентом
        socket.shutdown(tcp::socket::shutdown_both);
        socket.close();
      }

      // Продолжаем принимать следующие подключения
      StartAccept();
    });
  }

 public:
  TCP_Server(boost::asio::io_context& io_context, int L_port)
      : port_(L_port),  //
        acceptor_(io_context, tcp::endpoint(tcp::v4(), port_)) {
    debugger_ = new Debugger("Server");
  }
};
