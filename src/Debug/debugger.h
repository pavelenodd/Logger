#pragma once
#include <iostream>
#include <map>
#include <string>
namespace debugger {
enum Type { INFO = 0 };
std::map<Type, std::string> TYPE_MESSAGE_MAP = {{INFO, "Information"}};

}  // namespace debugger

using namespace debugger;
class Debugger {
 private:
  const std::string object_name_;  // имя обекта откуда ведутся логи
  Type type_;

 private:
  void PrintLog(const std::string& L_msg, const Type L_type) const {
    std::cout << std::boolalpha;

    std::cout << "\t" << "Object" << "\t" << "\033[4m" << object_name_ << "\t"
              << TYPE_MESSAGE_MAP[L_type] << "\033[0m" << ": " << L_msg
              << std::endl;
  }

 public:
  Debugger(const std::string& L_object_name) : object_name_(L_object_name) {}
  ~Debugger() {}
  void Info(const std::string& mesg = "") const { PrintLog(mesg, Type::INFO); }
};