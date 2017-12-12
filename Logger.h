//
// Created by abrzozowski on 12.12.17.
//

#ifndef MONITORY_SOI_LOGGER_H
#define MONITORY_SOI_LOGGER_H

#include <string>
#include <mutex>

class Logger {
public:
    void info(std::string s) const;
private:
    mutable std::mutex mutex;

    std::basic_string<char> getActualTime() const;
};

#endif //MONITORY_SOI_LOGGER_H
