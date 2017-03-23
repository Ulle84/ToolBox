// created on 2017-03-23 by Ulrich Belitz

#include <iostream>

#include "Console.h"

int main(int argc, char* argv[])
{
  for (int i = 0; i < argc; ++i)
  {
    std::cout << i << " " << argv[i] << std::endl;
  }

  Console::pressEnterToContinue();
}
