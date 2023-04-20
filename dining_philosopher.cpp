#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <semaphore.h>

using namespace std;

const int NUM_PHILOSOPHERS = 5;

sem_t chopsticks[NUM_PHILOSOPHERS];
vector<thread> philosophers;

void philosopher(int id) {
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;

    while (true) {
        cout << "Philosopher " << id << " is thinking" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));

        cout << "Philosopher " << id << " is hungry" << endl;

        sem_wait(&chopsticks[left_chopstick]);

        sem_wait(&chopsticks[right_chopstick]);

        cout << "Philosopher " << id << " is eating" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));

        sem_post(&chopsticks[left_chopstick]);

        sem_post(&chopsticks[right_chopstick]);
    }
}

int main() {
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers.emplace_back(philosopher, i);
    }

    for (auto& p : philosophers) {
        p.join();
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}
