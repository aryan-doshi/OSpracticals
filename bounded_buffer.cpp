#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>
#include<queue>
#include<semaphore.h>
using namespace std;

const int BUFFER_SIZE = 5;

sem_t empty;
sem_t full;
sem_t globalEmpty;
sem_t localEmpty;
mutex mtx;
condition_variable bufferNotFull;
condition_variable bufferNotEmpty;

queue<int> buffer;

void producer() {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&empty);
        unique_lock<mutex> lock(mtx);
        buffer.push(i);
        cout << "Produced item " << i << endl;
        lock.unlock();
        sem_post(&full);
        bufferNotFull.notify_one();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void consumer() {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&full);
        unique_lock<mutex> lock(mtx);
        int item = buffer.front();
        buffer.pop();
        cout << "Consumed item " << item << endl;
        lock.unlock();
        sem_post(&empty);
        bufferNotEmpty.notify_one();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main() {
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    
    thread producerThread(producer);
    thread consumerThread(consumer);
    
    producerThread.join();
    consumerThread.join();
    
    sem_destroy(&empty);
    sem_destroy(&full);
    
    return 0;
}
