#include "inc/multithreded_logger.hpp"

#include <iostream>
#include <chrono>
#include <thread>

void thread1(void) {
    for(int i = 0; i < 5; i++) {
        std::cout << "log1\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        MTLogger::INFO("Thread 1");
    }
}

void thread2(void) {
    for(int i = 0; i < 5; i++) {
        std::cout << "log2\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        MTLogger::INFO("Thread 2");
    }
}

int main() {
    
    std::thread t1(thread1);
    std::thread t2(thread2);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    t1.join();
    t2.join();
}