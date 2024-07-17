#pragma once
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <iostream>

class Logger {
 private:
 private:
  Logger();

  ~Logger();

 protected:
 public:
  void static Connected();
  void static Disconnected();
};