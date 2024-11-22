#include<semaphore>
#include<iostream>
#include<chrono>
#include<thread>

std::binary_semaphore signalToProducer{1}, signalToConsumer{0};
using namespace std;

# define buffSize 5
int buff[buffSize];

void producer() {
    while(1) {
        signalToProducer.acquire();
        cout << "Produced = ";
        for(int i =0; i<buffSize; i++) {
            buff[i] = i * i; // simulate work
            cout << buff[i] << " " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        cout << endl;
        signalToConsumer.release();
    }
}

void consumer() {
    while(1) {
        signalToConsumer.acquire();
        cout << "Consumed = ";
        for(int i =buffSize - 1; i>= 0; i--) {
            cout << buff[i] << " " << std::flush;
            buff[i] = 0;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        cout << endl;
        cout << endl;
        signalToProducer.release();
    }
}

int main(){
    std::thread t1(producer);
    std::thread t2(consumer);

    cout << "Main process started.\n";
    t1.join();
    t2.join();
}