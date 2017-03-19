#include <iostream>
#include <string>

#include "ConsoleHelper.h"

ConsoleHelper::ConsoleHelper()
{
}

ConsoleHelper::~ConsoleHelper()
{
}

void ConsoleHelper::waitForUserInput()
{
  // TODO enter does not return - another key must be pressed
  std::cout << "press enter to continue";

  std::string input;
  std::cin >> input;
}
