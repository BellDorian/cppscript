#pragma once
#include <iostream>
#include <cstdlib>

#define ASSERT_CPPS(condition, message)                                   \
    do {                                                                  \
        if (!(condition)) {                                               \
            std::cerr << "Assertion failed: (" << #condition << ")\n"     \
                      << "Message: " << message << "\n"                   \
                      << "Function: " << __func__ << "\n"                 \
                      << "File: " << __FILE__ << ", Line: " << __LINE__   \
                      << std::endl;                                       \
            std::abort();                                                 \
        }                                                                 \
    } while (0)


#define WARN_CPPS(message) \
do { std::cerr << "\033[1;33m" << message << "\033[0m" << std::endl; } while(0)