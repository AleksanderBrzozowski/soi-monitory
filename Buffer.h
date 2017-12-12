//
// Created by abrzozowski on 12.12.17.
//

#ifndef MONITORY_SOI_BUFFER_H
#define MONITORY_SOI_BUFFER_H

#include <condition_variable>
#include "Logger.h"

class Buffer {
private:
    static const int SIZE = 9;
    static const int MIN_CONSUME_SIZE = 3;

    std::condition_variable cond;
    std::mutex mutex;
    Logger logger{};
    int position = 0;
    char buffer[SIZE]{};

    bool isFull() const;

    bool canConsume(char c) const;

    void produce(char);

    char consume(char);
public:
    Buffer() = default;

    virtual ~Buffer() = default;

    void produceA();

    void produceB();

    char consumeA();

    char consumeB();
};

#endif //MONITORY_SOI_BUFFER_H
