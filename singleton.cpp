#include <iostream>
#include <thread>
#include "singleton.hpp"

std::unique_ptr<Singleton> Singleton::obj = nullptr;

void Singleton::printThreadId() 
{
    std::cout << "thread " << std::this_thread::get_id() << std::endl;
}

void threadFunc()
{
    Singleton& s = Singleton::create_obj();
    Singleton::create_obj().printThreadId(); 
}

std::mutex Singleton::mtx;

Singleton& Singleton::create_obj() 
{
    std::lock_guard<std::mutex> lock(mtx);
    if (!obj) {
        obj.reset(new Singleton());
    }
    return *obj;
}

int main()
{
    Singleton& s1 = Singleton::create_obj();

	Singleton& s2 = Singleton::create_obj();

	std::cout << &s1 << " " << &s2 << std::endl;
	
    std::thread t1(threadFunc);
    std::thread t2(threadFunc);
    std::thread t3(threadFunc);
    
    t1.join();
    t2.join();
    t3.join();
    return 0;
}