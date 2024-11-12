// JOIN NOTES
// 0. Once a thread is started we wait for this thread to finish by calling join() function on thread object.
// 1. Double join will result into program termination.
// 2. If needed we should check thread is joinable before joining. ( using joinable() function)

// DETACH NOTES
// 0. This is used to detach newly created thread from the parent thread.
// 1. Always check before detaching a thread that it is joinable otherwise we may end up double detaching and 
//    double detach() will result into program termination.
// 2. If we have detached thread and main function is returning then the detached thread execution is suspended.

// Either join() or detach() should be called on thread object, otherwise during thread object's destructor it will 
// terminate the program. Because inside destructor it checks if thread is still joinable? if yes then it terminates the program.

// In C++, when you create a std::thread object, it starts a new thread of execution. However, once a thread is created, you need to either:

// Join the thread using .join().
// Detach the thread using .detach().
// If you do neither, the program will terminate when the std::thread object's destructor is called, because the destructor checks whether the thread is still "joinable."

// Why Does the Program Terminate?
// When a std::thread object is destroyed (goes out of scope), its destructor calls the std::terminate() function if the thread is still joinable. This behavior is intentional to prevent the following potential issues:

// Resource Leak: If a thread is not joined or detached, it remains in a joinable state, causing a resource leak.
// Undefined Behavior: If the thread finishes execution but is not joined, accessing it later can lead to undefined behavior.
// What Does "Joinable" Mean?
// A thread is joinable if it represents a valid running thread that has not been joined or detached.

// Joinable: A thread that is either still running or has completed execution but has not been joined.
// Not Joinable: A thread that has been either joined, detached, or never started.


#include <iostream>
#include <thread>
#include <chrono>
using namespace std;


void run(int count) {
    while(count-- > 0) {
        cout << count << " Wu kongs" << endl;
    }
    std::this_thread::sleep_for(chrono::seconds(5));
    cout << "thread finished" << endl;
}

int main() {
    std::thread t1(run, 10);
    cout << "main" << endl;

    t1.join();
    if (t1.joinable())
        t1.join();
    // t1.detach();
    cout << "main after" << endl;
    return 0;
}