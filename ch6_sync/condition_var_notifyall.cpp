#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>
 
std::condition_variable cv;
std::mutex cv_m; // This mutex is used for three purposes:
                 // 1) to synchronize accesses to i
                 // 2) to synchronize accesses to std::cerr
                 // 3) for the condition variable cv
int i = 0;
 
void waits(int _thread_id)
{
    int thread_id = _thread_id;
    std::unique_lock<std::mutex> lk(cv_m);
    std::cerr << "Waiting... \n";
    while(i == 0){
        cv.wait(lk);
    }
    i++;
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cerr << "thread: "<< thread_id<< "...finished waiting. i == "<<i<<"\n";
}
 
void signals()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lk(cv_m); // scoped lock 
        std::cerr << "Notifying...\n";
    }
    cv.notify_all();
 
    std::this_thread::sleep_for(std::chrono::seconds(1));
 
    {
        std::lock_guard<std::mutex> lk(cv_m);
        i = 1;
        std::cerr << "Notifying again...\n";
    }
    cv.notify_all();
}
 
int main()
{
    int id = 1;
    std::thread t1(waits,id++), t2(waits, id++), t3(waits, id++), t4(signals);
    t1.join(); 
    t2.join(); 
    t3.join();
    t4.join();
}