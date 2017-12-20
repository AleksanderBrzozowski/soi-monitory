#include <iostream>
#include <thread>
#include "Buffer.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

static const int PRODUCER_A_SLEEP_IN_SECONDS = 1;
static const int PRODUCER_B_SLEEP_IN_SECONDS = 3;

static const int CONSUMER_A_SLEEP_IN_SECONDS = 2;
static const int CONSUMER_B_SLEEP_IN_SECONDS = 1;

void consumeA(Buffer &buffer, int sleepDurationInSeconds);

void consumeB(Buffer &buffer, int sleepDurationInSeconds);

void produceA(Buffer &buffer, int sleepDurationInSeconds);

void produceB(Buffer &buffer, int sleepDurationInSeconds);

int main() {
    Buffer buffer;

    auto producerAThread = std::thread(produceA, std::ref(buffer), PRODUCER_A_SLEEP_IN_SECONDS);
    auto producerBThread = std::thread(produceB, std::ref(buffer), PRODUCER_B_SLEEP_IN_SECONDS);
    auto consumeAThread = std::thread(consumeA, std::ref(buffer), CONSUMER_A_SLEEP_IN_SECONDS);
    auto consumeBThread = std::thread(consumeB, std::ref(buffer), CONSUMER_B_SLEEP_IN_SECONDS);

    producerAThread.join();
    producerBThread.join();
    consumeAThread.join();
    consumeBThread.join();
    return 0;
}

void consumeA(Buffer &buffer, int sleepDurationInSeconds) {
    while (true) {
        buffer.consumeA();
        std::this_thread::sleep_for(std::chrono::seconds(sleepDurationInSeconds));
    }
}

void consumeB(Buffer &buffer, int sleepDurationInSeconds) {
    while (true) {
        buffer.consumeB();
        std::this_thread::sleep_for(std::chrono::seconds(sleepDurationInSeconds));
    }
}

void produceA(Buffer &buffer, int sleepDurationInSeconds) {
    while(true) {
        buffer.produceA();
        std::this_thread::sleep_for(std::chrono::seconds(sleepDurationInSeconds));
    }
}

void produceB(Buffer &buffer, int sleepDurationInSeconds) {
    while(true) {
        buffer.produceB();
        std::this_thread::sleep_for(std::chrono::seconds(sleepDurationInSeconds));
    }
}

#pragma clang diagnostic pop