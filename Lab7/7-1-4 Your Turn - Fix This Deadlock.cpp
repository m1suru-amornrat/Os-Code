#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex resourceA, resourceB, resourceC;

void process1() {
    std::scoped_lock lock(resourceA, resourceB);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    // Work...
}

void process2() {
    std::scoped_lock lock(resourceA, resourceB, resourceC);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    // Work...
}

void process3() {
    std::scoped_lock lock(resourceA, resourceC);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    // Work...
}

int main() {
    std::thread t1(process1);
    std::thread t2(process2);
    std::thread t3(process3);

    t1.join();
    t2.join();
    t3.join();
}
