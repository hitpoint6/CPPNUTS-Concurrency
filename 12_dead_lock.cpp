#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

std::mutex m1;
std::mutex m2;

void thread1() {
    m1.lock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    m2.lock();
    cout << "Critical section of thread one\n";
    m1.unlock();
    m2.unlock();
}

void thread2() {
    m2.lock(); // Dead lock: t1 acquired m1, and t2 acquired m2, then t2 tries to acquire m1, which is held by t1, t2 waits for m1. However t1 also tries to acquired m2, which is held by t2, t1 waits for m2. Both are waiting infinitely.
    std::this_thread::sleep_for(std::chrono::seconds(1));
    m1.lock(); // To resolve deadlock, make sure that thread2 acquires locks in the same sequence: m1.lock() then m2.lock(). In this situation, t1 acquires m1. If t2 tries to acquire m1, it will wait. Later t1 acquire m2, finishes everything then releases m1, t2 can then acquire m1 and continue the process.

    cout << "Critical section of thread two\n";
    m2.unlock();
    m1.unlock();
}

int main() {
    thread t1(thread1);
    thread t2(thread2);
    t1.join();
    t2.join();

    return 0;
}