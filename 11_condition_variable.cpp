// In this video we will learn how to use "Condition Variable In C++ Threading".
// Few important points to remember while using "condition variables" are as follows:
// 1. Condition variables allow us to synchronise threads via notifications.
//    a. notify_one();
//    b. notify_all();
// 2. You need mutex to use condition variable
// 3. Condition variable is used to synchronise two or more threads.
// 4. Best use case of condition variable is Producer/Consumer problem.
// 5. Condition variables can be used for two purposes:
//     a. Notify other threads
//     b. Wait for some condition

// Note:
// 1. Condition variables are used to synchronize two or more threads.
// 2. Best use case of cv is Producer/Consumer problem.

#include<iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

std::condition_variable cv;
std::mutex m;
long balance = 0;

void addMoney(int money) {
    std::lock_guard<mutex> lg(m);
    balance += money;
    cout << "Amount added current balance: " << balance << endl;
    cv.notify_one();
}

void withdrawMoney(int money) {
    std::unique_lock<mutex> ul(m);
    cv.wait(ul, []{return (balance != 0) ? true : false; }); 
    // This put the execution in wait until the condition is met. 
    // when the predicate does not satisfy, CV will put the thread into sleep and release the mutex m (key)
    // If the condition is true, it will keep the mutex and execute the code in the scope.
    // The following code is guarded by CV so withdrawMoney can not proceed before addMoney.

    if (balance >= money) {
        balance -= money;
        cout << "Amount Deducted: " << money << endl; 
    } else {
        cout << "Amount can't be deducted, current balance is less than " << money << endl;
    }
    cout << "Current balance is: " << balance << endl;
}

int main() {
    std::thread t1(withdrawMoney, 600);
    std::thread t2(addMoney, 500); // addMoney will always start first
    t1.join();
    t2.join();
    return 0;
}