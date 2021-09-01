#pragma once

#include <iostream>

#define LOG_INFO(X) std::cout << "INFO: " << X << std::endl
#define LOG_ERROR(X) std::cerr << "ERROR: " << X << std::endl

#if defined(_MSC_VER) && defined(_DEBUG)
#define LOG_DEBUG(X) std::cout << "DEBUG: " << X << std::endl
#else
#define LOG_DEBUG(X)
#endif