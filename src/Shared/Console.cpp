#include <iostream>

#include "Console.h"

namespace Console
{
  void pressEnterToContinue()
  {
    std::cout << std::endl << "please press enter to continue..." << std::endl;
    std::getchar();
  }

  void showMessage(const std::string& message)
  {
    std::cout << message << std::endl;
  }

  void showWarning(const std::string& warning)
  {
    std::cout << "WARNING: " << warning << std::endl;
  }

  void showInfo(const std::string& information)
  {
    std::cout << "INFO:    " << information << std::endl;
  }

  void showSuccess(const std::string& information)
  {
    std::cout << "SUCCESS: " << information << std::endl;
  }

  void showError(const std::string& error)
  {
    std::cout << "ERROR:   " << error << std::endl;
  }
}
