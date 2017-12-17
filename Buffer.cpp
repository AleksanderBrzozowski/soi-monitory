//
// Created by abrzozowski on 12.12.17.
//

#include <sstream>
#include <iostream>
#include "Buffer.h"

void Buffer::produceA() {
    produce('A');
}

void Buffer::produceB() {
    produce('B');
}

char Buffer::consumeA() {
    const char c = consume('A');
    return c;
}

char Buffer::consumeB() {
    const char c = consume('B');
    return c;
}

bool Buffer::isLastElement(char c) const {
    return buffer[position - 1] == c;
}

bool Buffer::isMoreThan3Elements() const {
    return position > MIN_CONSUME_SIZE;
}

void Buffer::printBuffer() {
    printf("Buffer: [");
    for (int i = 0; i < position - 1; ++i) {
        printf("%c, ", buffer[i]);
    }
    printf("%c]\n", buffer[position - 1]);
}

bool Buffer::isFull() const {
    return position == SIZE;
}

void Buffer::produce(char c) {
    std::unique_lock<std::mutex> lock(mutex);

    if (isFull()) {
        printf("Producer %c waits (%s)\n", c, FULL_CONDITION);

        cond.wait(lock, [this]() { return !isFull(); });

        printf("Producer %c produces element after waiting (%s)\n", c, FULL_CONDITION);
    } else {
        printf("Producer %c produces element\n", c);
    }

    buffer[position] = c;
    ++position;
    printBuffer();

    lock.unlock();
    cond.notify_all();
}

char Buffer::consume(char c) {
    std::unique_lock<std::mutex> lock(mutex);

    const bool lessThan3Elements = !isMoreThan3Elements();
    const bool lastElementOther = !isLastElement(c);
    if (lessThan3Elements || lastElementOther) {
        const char *const condition = lessThan3Elements ? LESS_THAN_3_ELEMENTS : LAST_ELEMENT_IS_OTHER;
        printf("Consumer %c waits (%s)\n", c, condition);

        cond.wait(lock, [this, c]() -> bool { return isMoreThan3Elements() && isLastElement(c); });

        printf("Consumer %c consumes after waiting (%s)\n", c, condition);
    } else {
        printf("Consumer %c consumes\n", c);
    }

    --position;
    printBuffer();

    lock.unlock();
    cond.notify_all();
    return c;
}
