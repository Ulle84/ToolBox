// created on 2016-12-09

#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <iostream>

namespace Console
{
  void pressEnterToContinue();

  void showMessage(const std::string& message);
  void showWarning(const std::string& warning);
  void showInfo(const std::string& information);
  void showError(const std::string& error);
  void showSuccess(const std::string& error);

  template<typename T>
  void showValue(const std::string& description, T value)
  {
    std::cout << description << ": " << value << std::endl;
  }

  template<typename T>
  void showNumberOf(const std::string& description, T value)
  {
    std::cout << "number of " << description << ": " << value << std::endl;
  }
}

#endif