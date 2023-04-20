#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

const int READERS_COUNT = 5;
const int WRITERS_COUNT = 3;

mutex mtx;
condition_variable cv_read, cv_write;
int read_count = 0, write_count = 0, data = 0;

void reader(int id) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        while (write_count > 0) {
            cv_read.wait(lock);
        }
        ++read_count;
        lock.unlock();
        
        cout << "Reader " << id << " reads data " << data << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
        
        lock.lock();
        --read_count;
        if (read_count == 0) {
            cv_write.notify_one();
        }
        lock.unlock();
        
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void writer(int id) {
    while (true) {
        
        unique_lock<mutex> lock(mtx);
        while (write_count > 0 || read_count > 0) {
            cv_write.wait(lock);
        }
        ++write_count;
        lock.unlock();
        
        ++data;
        cout << "Writer " << id << " writes data " << data << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
        
        lock.lock();
        --write_count;
        if (write_count == 0) {
            cv_read.notify_all();
            cv_write.notify_one();
        }
        lock.unlock();
        
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main() {
    thread readers[READERS_COUNT];
    thread writers[WRITERS_COUNT];
    
    for (int i = 0; i < READERS_COUNT; ++i) {
        readers[i] = thread(reader, i);
    }
    
    for (int i = 0; i < WRITERS_COUNT; ++i) {
        writers[i] = thread(writer, i);
    }
    
    for (int i = 0; i < READERS_COUNT; ++i) {
        readers[i].join();
    }
    for (int i = 0; i < WRITERS_COUNT; ++i) {
        writers[i].join();
    }
    
    return 0;
}
