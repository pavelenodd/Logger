#include <boost/asio.hpp>
#include <iostream>

#define PORT 8080  // Порт, на котором сервер будет ожидать подключения

using boost::asio::ip::tcp;  // Используем пространство имен для TCP

class MyServer {
 public:
  MyServer(boost::asio::io_context& io_context)
      : acceptor_(io_context, tcp::endpoint(tcp::v4(), PORT)) {
    // Конструктор класса MyServer
    // Инициализируем объект acceptor, который будет ожидать входящих соединений
    StartAccept();  // Начинаем принимать подключения
  }

 private:
  void StartAccept() {
    // Создаем новый сокет, используя executor напрямую
    tcp::socket socket(acceptor_.get_executor());

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

  tcp::acceptor acceptor_;  // Объект, который принимает входящие подключения
};
