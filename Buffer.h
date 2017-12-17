//
// Created by abrzozowski on 12.12.17.
//

#ifndef MONITORY_SOI_BUFFER_H
#define MONITORY_SOI_BUFFER_H

static const char *const FULL_CONDITION = "Buffer is full";

static const char *const LESS_THAN_3_ELEMENTS = "Less than 3 elements";

static const char *const LAST_ELEMENT_IS_OTHER = "Last element is other";

#include <condition_variable>

class Buffer {
private:
    static const int SIZE = 9;
    static const int MIN_CONSUME_SIZE = 3;

    std::condition_variable cond;
    std::mutex mutex;
    int position = 0;
    char buffer[SIZE]{};

    bool isFull() const;

    bool isMoreThan3Elements() const;

    bool isLastElement(char c) const;

    void produce(char);

    char consume(char);
public:
    Buffer() = default;

    virtual ~Buffer() = default;

    void produceA();

    void produceB();

    char consumeA();

    char consumeB();

    void printBuffer();
};

#endif //MONITORY_SOI_BUFFER_H
