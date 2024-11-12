#include <iostream>
#include <thread>

using namespace std;

// 1. Use function pointer
// 2. Use lambda
// int main() {
//     // auto fun =;

//     std::thread t( [](int x) {
//         while (x-- > 0) {
//             cout << x << endl;
//         }
//     }, 10);
//     t.join();
//     return 0;
// }

//3. Use functor


// 4. Use Non static member function
// class Base {
//     public:
//         void run(int x) {
//             while (x-- > 0) {
//                 cout << x << endl;
//             }
//         }
// };

// int main() {
//     Base b;
//     std::thread t(&Base::run, &b, 10);
//     t.join();
//     return 0;
// }

// 5. Static member function
class Base {
    public:
        static void run(int x) {
            while (x-- > 0) {
                cout << x << endl;
            }
        }
};

int main() {
    Base b;
    std::thread t(&Base::run, 10);
    t.join();
    return 0;
}

