#include <iostream>
#include <windows.h>
#include "EntryPoint.hpp"
#include "Application.hpp"

entry_point{

    Application app;
    app.run();

    std::cout << "Cal" << std::endl;
    return 0;
}
