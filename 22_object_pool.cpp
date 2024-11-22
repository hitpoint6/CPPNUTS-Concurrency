#include<iostream>
#include<vector>
#include<queue>
#include<thread>
#include<functional>
#include<sstream>
#include<mutex>
#include<condition_variable>

std::string get_thread_id() {
    auto myid = std::this_thread::get_id();
    std::stringstream ss;
    ss << myid;
    std::string mystr = ss.str();
    return mystr;
}


class Object {
public:
    int _num;
    Object(int num): _num {num} {}
    void doSomething() {std::cout << "Object doing something." << std::endl;}
};

class ObjectPool {
public:
    std::queue<std::shared_ptr<Object>> pool;
    int poolSize;
    std::mutex mutex_;

    ObjectPool(int size) : poolSize(size) {
        std::cout << "Object pool constructured" << std::endl;
        for(int i = 0; i < poolSize; ++i) {
            std::cout << "Object " << i << std::endl;
            pool.push(std::make_shared<Object>(Object(i))); 
        }
    }

    std::shared_ptr<Object> acquireObject() {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!pool.empty()) {
            auto obj = pool.front();
            printf("Thread %s acquired object: %d\n", get_thread_id().c_str(), obj->_num);
            pool.pop();
            return obj;
        }
        return nullptr; // No available objects in the pool
    }

    void releaseObject(std::shared_ptr<Object> obj) {
        std::unique_lock<std::mutex> lock(mutex_);
        printf("Thread %s release object: %d\n", get_thread_id().c_str(), obj->_num);
        pool.push(obj);
    }
};

void worker(ObjectPool& pool) {
    // Each worker just acquire and release the object.
    for (int i = 0; i < 15; ++i) {
        auto obj = pool.acquireObject();
        if (obj) {
            // Simulate some work
            int worked_for = rand() % 1000;
            std::this_thread::sleep_for(std::chrono::milliseconds(worked_for));
            pool.releaseObject(obj);
        } else {
            printf("Thread %s failed to acquire object \n", get_thread_id().c_str());
        }
    }
}

int main() {
    // A pool of 3 objects
    // 2 workers to aquire and release objects
    ObjectPool pool(3);
    std::vector<std::thread> workers;
    int workers_count = 2;

    for(int i=0; i<workers_count; i++) {
        workers.emplace_back(worker, std::ref(pool));
    }

    for(int i = 0; i < workers_count; i++) {
        workers[i].join();
    }

    return 0;
}