
#include "logger.h"

int main() {
  BaseLogger* logger = TCP_IP_Logger::Get_Instance(5000);
  logger->StartConected();
  return 0;
}
