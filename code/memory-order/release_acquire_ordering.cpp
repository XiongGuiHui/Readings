/**
 * What if 
 */
#include <thread>
#include <atomic>
#include <cassert>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

 
/**
 * all memory writes (non-atomic and relaxed atomic) that
 * happened-before the atomic store from the point of view
 * of thread A, become visible side-effects in thread B
 */
std::atomic<std::string*> ptr;
int d;

void producer(){
    std::string* p  = new std::string("Hello");
    d = 42;
    ptr.store(p, std::memory_order_release);
}
 
void consumer(){
    std::string* p2;
    while (!(p2 = ptr.load(std::memory_order_acquire))){
        cout << "-";
    }
    assert(*p2 == "Hello"); // never fires
    assert(d == 42); // never fires
}

void go(){
    // what a desperate thing, even loop for 10 billion times, we can not find the fire
    for (int i = 0; i < 1000; i++) {
        std::thread t2(consumer);
        std::thread t1(producer);
        t1.join();
        t2.join();
    }
}


/**
 * The following example demonstrates transitive release-acquire ordering across three threads 
 */
std::vector<int> data;
std::atomic<int> flag = {0};
 
void thread_1(){
    data.push_back(42);
    flag.store(1, std::memory_order_release);
}
 
void thread_2(){
    int expected=1;
    while (!flag.compare_exchange_strong(expected, 2, std::memory_order_acq_rel)) {
        expected = 1;
    }
}
 
void thread_3(){
    while (flag.load(std::memory_order_acquire) < 2);
    assert(data.at(0) == 42); // will never fire
}
 
void go2(){
    std::thread a(thread_1);
    std::thread b(thread_2);
    std::thread c(thread_3);
    a.join(); b.join(); c.join();
}
 
int main(){
    go();
}
