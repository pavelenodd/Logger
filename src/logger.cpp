#include "logger.h"

Logger::Logger() {}

Logger::~Logger() {}

void Logger::Connected() {
  std::cout << "Connected" << std::endl;
  Logger();
}

void Logger::Disconnected() { std::cout << "Disconnected" << std::endl; }
