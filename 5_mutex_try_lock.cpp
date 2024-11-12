

// In this video we will learn about std::mutex::try_lock() On Mutex In C++11 Threading.
// In C++, std::mutex::try_lock() is a non-blocking way to attempt locking a mutex. It tries to lock the mutex, but if the mutex is already locked by another thread, it does not block the current thread. Instead, it returns immediately, allowing the current thread to continue its execution without waiting.



// Few points to remember about the try_lock is as follows:
// 0. try_lock() Tries to lock the mutex. Returns immediately. On successful lock acquisition returns true otherwise returns false.
// 1. If try_lock() is not able to lock mutex, then it doesn't get blocked that's why it is called non-blocking.
// 2. If try_lock is called again by the same thread which owns the mutex, the behaviour is undefined.
//    It is a dead lock situation with undefined behaviour. (if you want to be able to lock the same mutex by same thread more than one time the go for recursive_mutex)

// There are so many try_lock function
// 1. std::try_lock
// 2. std::mutex::try_lock
// 3. std::shared_lock::try_lock
// 4. std::timed_mutex::try_lock
// 5. std::unique_lock::try_lock
// 6. std::shared_mutex::try_lock
// 7. std::recursive_mutex::try_lock
// 8. std::shared_timed_mutex::try_lock
// 9. std::recursive_timed_mutex::try_lock

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int counter = 0;
std::mutex mtx;

void increaseTheCounterFor100000Time() {
    for (int i=0; i<100000; ++i) {
        if(mtx.try_lock()) {
            ++counter;
            mtx.unlock();
        }
    }
};


int main() {
    std::thread t1(increaseTheCounterFor100000Time);
    std::thread t2(increaseTheCounterFor100000Time);

    t1.join();
    t2.join();

    cout << "Counter ends up at: " << counter << endl;

    return 0;
}