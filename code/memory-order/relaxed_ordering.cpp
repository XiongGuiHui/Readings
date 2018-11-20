#include <vector>
#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

 
/**
 * they do not impose an order among concurrent memory accesses.
 * They only guarantee atomicity and modification order consistency. 
 *
 * Typical use for relaxed memory ordering is incrementing counters,
 * such as the reference counters of std::shared_ptr, since this only
 * requires atomicity, but not ordering or synchronization 
 */
std::atomic<int> cnt = {0};
void f(){
    for (int n = 0; n < 1000; ++n) {
        cnt.fetch_add(1, std::memory_order_relaxed);
    }
}
void g(){
    std::vector<std::thread> v;
    for (int n = 0; n < 10; ++n) {
        v.emplace_back(f);
    }
    for (auto& t : v) {
        t.join();
    }
    std::cout << "Final counter value is " << cnt << '\n';
}


std::atomic<int> x = {0};
std::atomic<int> y = {0};

volatile int flag = 0;

void t1(){
    auto r1 = y.load(std::memory_order_relaxed); // A
    x.store(r1, std::memory_order_relaxed); // B
    cout << "r1: "<< r1 << "\t";
    if(r1 == 42){
        flag ++;
    }
}

void t2(){
    // Thread 2:
    auto r2 = x.load(std::memory_order_relaxed); // C 
    y.store(42, std::memory_order_relaxed); // D
    std::cout << "r2: " <<  r2 << "\t";
    if(r2 == 42){
        flag ++;
    }
}

void g2(){
    // we can find the expected wired situation where D finished before C
    for (int i = 0; i < 10000000; i++) {
        y.store(0, std::memory_order_relaxed);
        x.store(0, std::memory_order_relaxed);

        cout << "epoch : " << i << "\t";
        thread b(t2);
        thread a(t1); 

        a.join();
        b.join();
        cout << "x: " << x << "\ty: " << y << "\n";

        if(flag == 2){
            cout << "cheers" << endl;
            break;
        }else{

            flag = 0;
        }
    }
    
}
 
int main(){
    g2();
}
