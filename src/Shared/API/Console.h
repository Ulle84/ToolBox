// created on 2016-12-09

#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>

#include "SharedAPI.h"

namespace Console
{
  void SHARED_API pressEnterToContinue();

  void SHARED_API showMessage(std::string message);
  void SHARED_API showWarning(std::string warning);
  void SHARED_API showInfo(std::string information);
  void SHARED_API showError(std::string error);
  void SHARED_API showSuccess(std::string error);

  template<typename T>
  void showValue(std::string description, T value)
  {
    std::cout << description << ": " << value << std::endl;
  }

  template<typename T>
  void showNumberOf(std::string description, T value)
  {
    std::cout << "number of " << description << ": " << value << std::endl;
  }
}

#endif