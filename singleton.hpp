#pragma once

#include <mutex>
#include <memory>

class Singleton {
public: 
    static Singleton& create_obj();
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    
    void printThreadId();
private:
    static std::unique_ptr<Singleton> obj;
 
    static std::mutex mtx;
    
    Singleton() = default;
};