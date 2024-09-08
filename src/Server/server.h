/*#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <vector>

using boost::asio::ip::tcp;  // Используем пространство имен для TCP

struct ClientInfo {
  const std::string ip_address_;
  const int port_;

  ClientInfo() = delete;
  ClientInfo(std::string L_ip_address, int L_port, tcp::socket L_socket)
      : ip_address_(L_ip_address), port_(L_port) {}
};

#define PORT 8080  // Порт, на котором сервер будет ожидать подключения

class TCP_Server {
 private:
  tcp::acceptor acceptor_;  // Объект, который принимает входящие подключения
  const int port_;  // Порт, на котором сервер будет ожидать подключения
 private:
  void StartAccept() {
    // Создаем новый сокет для входящего соединения
    tcp::socket socket(acceptor_.get_executor().context());

    // Асинхронно принимаем соединение с клиентом
    acceptor_.async_accept(socket, [this,
                                    &socket](boost::system::error_code ec) {
      // Эта лямбда-функция будет вызвана после успешного подключения клиента
      if (!ec) {
        std::cout << "Новое подключение: " << socket.remote_endpoint()
                  << std::endl;

        // Читаем данные от клиента
        boost::asio::streambuf buffer;  // Буфер для хранения данных
        boost::asio::read_until(socket, buffer,
                                "\n");  // Чтение данных до символа новой строки

        // Преобразуем данные в строку для удобства
        std::istream is(&buffer);
        std::string message;
        std::getline(is, message);
        std::cout << "Получено сообщение от клиента: " << message << std::endl;

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
  TCP_Server(boost::asio::io_context& L_io_context, const int L_port)
      : port_(L_port),
        acceptor_(L_io_context, tcp::endpoint(tcp::v4(), port_)) {
    // Конструктор класса TCP_Server
    // Инициализируем объект acceptor, который будет ожидать входящих соединений
    StartAccept();  // Начинаем принимать подключения
  }
};

/*int main() {
  try {
    // Создаем контекст для управления асинхронными операциями
    boost::asio::io_context io_context;

    // Создаем объект сервера, который начинает ожидание подключений
    TCP_Server server(io_context, PORT);

    // Запускаем главный цикл обработки событий
    io_context.run();
  } catch (std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
  }

  return 0;
}*/