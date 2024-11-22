#include<chrono>
#include<iostream>
#include<semaphore>
#include<thread>

// Global binary semaphore instances
// Object counts are set to zero
// Objects are in non-signal state
std::binary_semaphore 
    smphSignalMainToThread{0},
    smphSignalThreadToMain{0};

void threadTask() {
    // Wait for a signal from the main process.
    // by attemping to decrement the semaphore.
    smphSignalMainToThread.acquire();

    // This call blocks until the semaphore's count
    // is increased from the main process.
    std::cout << "[Thread] got the signal\n";

    using namespace std::literals;
    std::this_thread::sleep_for(3s);

    // Signal the main process
    smphSignalThreadToMain.release();
    std::cout << "[Thread] send the signal\n";
}

int main (){ 
    // Create a workder thread, the thread runs immediately.
    std::thread worker(threadTask);
    std::cout << "[Main] send the singal\n";

    // Signal the worker thread to start working
    // by increaseing the semaphore's count.
    smphSignalMainToThread.release();

    // Wait until the worker thread is done doing the work
    // by attempting to decrement the semaphore's count
    smphSignalThreadToMain.acquire();

    std::cout << "[Main] got the signal\n";
    worker.join();
}