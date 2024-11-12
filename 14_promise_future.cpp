// In this video we will learn about how std::promise and std::future and how they work together to synchronise threads.
// Basically std::promise is sent to the called thread and once the value is ready we set that value in promise object, now at calling thread side we get that value using std::future object which was created using std::promise object before sending it to the called thread. And this is how we receive value from one thread to another in synchronisation.

// Notes:
// 1. std::promise (setter)
//     a. Used to set values or expections.
// 2. std::future (getter)
//     a. Used to get values from promises.
//     b. Ask promise if the value is available.
//     c. Wait for the promise.


#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <future>

using namespace std;
using namespace std::chrono;
typedef long int ull;

void findOdd(std::promise<ull>&& OddSumPromise, ull start, ull end) {
    ull OddSum = 0;
    for (ull i = start; i <= end; ++i) {
        if (i & 1) {
            OddSum += i;
        }
    }
    OddSumPromise.set_value(OddSum);
}

int main() {
    ull start = 0, end = 1900000000;
    std::promise<ull> OddSum;
    std::future<ull> OddFuture = OddSum.get_future();

    cout << "Thread Created!" << endl;

    std::thread t1(findOdd, std::move(OddSum), start, end);
    // from now on, the main thread and t1 are executing in parallel
     
    cout << "Waiting for Result!!" << endl;

    cout << "OddSum: " << OddFuture.get() << endl;

    cout << "Completed! " << endl;

    t1.join();
    return 0;
}





