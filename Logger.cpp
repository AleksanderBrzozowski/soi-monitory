//
// Created by abrzozowski on 12.12.17.
//

#include <iostream>
#include <sys/time.h>
#include <cstring>
#include "Logger.h"

void Logger::info(const std::string s) const {
    std::unique_lock<std::mutex> lock(mutex);
    std::cout << "\x1B[34m" << getActualTime() << "\x1B[0m" << ": " << s << std::endl;
}

std::string Logger::getActualTime() const {
    struct timeval tm_now{};
    struct tm *tm;
    char buf[26], usec_buf[6];
    gettimeofday(&tm_now, nullptr);
    tm = localtime(&tm_now.tv_sec);
    strftime(buf, 26, "%H:%M:%S", tm);
    strcat(buf, ".");
    sprintf(usec_buf, "%d", (int) tm_now.tv_usec);
    strcat(buf, usec_buf);

    return std::string(buf);
}
