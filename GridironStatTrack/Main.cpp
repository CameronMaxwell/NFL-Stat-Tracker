/**
 * @file Main.cpp
 * @author Cameron Maxwell
 * @brief This is the main file that creates the GridironApplication environment.
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Wt/WApplication.h>
#include "GridironApplication.h"

int main(int argc, char **argv)
{
  return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
    return std::make_unique<GridironApplication>(env);
  });
}
