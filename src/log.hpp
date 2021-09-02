#pragma once

#include <iostream>

#define LOG_INFO(X) std::cout << "INFO: " << X << std::endl
#define LOG_WARNING(X) std::cerr << "WARNING: " << X << std::endl
#define LOG_ERROR(X) std::cerr << "ERROR: " << X << std::endl

#if defined(_MSC_VER) && defined(_DEBUG) || defined(__GNUC__)
#define LOG_DEBUG(X) std::cout << "DEBUG: " << X << std::endl
#else
#define LOG_DEBUG(X)
#endif