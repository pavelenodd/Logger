

#include "../Test/client.h"
#include "logger_manager.h"

int main() {
  BaseLogger* logger = TCP_IP_Logger::Get_Instance(5050);
  logger->StartConected();
  return 0;
}
