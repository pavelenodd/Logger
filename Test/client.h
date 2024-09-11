#include <boost/asio.hpp>
#include <iostream>

#define PORT 8080  // Порт, к которому клиент будет подключаться
#define SERVER_IP "127.0.0.1"  // IP-адрес сервера

using boost::asio::ip::tcp;  // Используем пространство имен для TCP

/*int main() {
  try {
    // Создаем контекст для управления асинхронными операциями
    boost::asio::io_context io_context;

    // Создаем объект для разрешения IP-адреса и порта сервера
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
        resolver.resolve(SERVER_IP, std::to_string(PORT));

    // Создаем и подключаем сокет к серверу
    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    // Отправляем сообщение серверу
    std::string message = "Привет, сервер!\n";
    boost::asio::write(socket, boost::asio::buffer(message));

    // Читаем ответ от сервера
    boost::asio::streambuf buffer;
    boost::asio::read_until(socket, buffer, "\n");
    std::istream is(&buffer);
    std::string response;
    std::getline(is, response);
    std::cout << "Ответ сервера: " << response << std::endl;

    // Закрываем соединение с сервером
    socket.shutdown(tcp::socket::shutdown_both);
    socket.close();
  } catch (std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
  }

  return 0;
}*/