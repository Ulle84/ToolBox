// created on 2016-12-09

#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <iostream>

#include "SharedAPI.h"

namespace Console
{
  void SHARED_API pressEnterToContinue();

  void SHARED_API showMessage(const std::string& message);
  void SHARED_API showWarning(const std::string& warning);
  void SHARED_API showInfo(const std::string& information);
  void SHARED_API showError(const std::string& error);
  void SHARED_API showSuccess(const std::string& error);

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