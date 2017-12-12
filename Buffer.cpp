//
// Created by abrzozowski on 12.12.17.
//

#include "Buffer.h"

void Buffer::produceA() {
    logger.info("Producer A tries to produce");
    produce('A');
    logger.info("Producer A successfully produced");
}

void Buffer::produceB() {
    logger.info("Producer B tries to produce");
    produce('B');
    logger.info("Producer B successfully produced");
}

char Buffer::consumeA() {
    logger.info("Consumer A tries to consume");
    const char c = consume('A');
    logger.info("Consumer A successfully consumed");
    return c;
}

char Buffer::consumeB() {
    logger.info("Consumer B tries to consume");
    const char c = consume('B');
    logger.info("Consumer B successfully consumed");
    return c;
}

bool Buffer::canConsume(char c) const {
    return position > MIN_CONSUME_SIZE - 1 && buffer[position - 1] == c;
}

bool Buffer::isFull() const {
    return position == SIZE;
}

void Buffer::produce(char c) {
    std::unique_lock<std::mutex> lock(mutex);
    cond.wait(lock, [this]() { return !isFull(); });

    buffer[position] = c;
    ++position;

    lock.unlock();
    cond.notify_all();
}

char Buffer::consume(char c) {
    std::unique_lock<std::mutex> lock(mutex);

    cond.wait(lock, [this, c]() -> bool { return canConsume(c); });

    --position;

    lock.unlock();
    cond.notify_all();
    return c;
}
