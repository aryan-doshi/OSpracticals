import threading
import time

NUM_PHILOSOPHERS = 5

class Philosopher(threading.Thread):
    def __init__(self, id, left_chopstick, right_chopstick):
        super().__init__()
        self.id = id
        self.left_chopstick = left_chopstick
        self.right_chopstick = right_chopstick

    def run(self):
        while True:
            print(f"Philosopher {self.id} is thinking")
            time.sleep(1)

            print(f"Philosopher {self.id} is hungry")
            self.left_chopstick.acquire()
            self.right_chopstick.acquire()

            print(f"Philosopher {self.id} is eating")
            time.sleep(1)

            self.right_chopstick.release()
            self.left_chopstick.release()

if __name__ == "__main__":
    chopsticks = [threading.Semaphore(1) for _ in range(NUM_PHILOSOPHERS)]
    philosophers = []

    for i in range(NUM_PHILOSOPHERS):
        left_chopstick = chopsticks[i]
        right_chopstick = chopsticks[(i + 1) % NUM_PHILOSOPHERS]
        philosophers.append(Philosopher(i, left_chopstick, right_chopstick))

    for philosopher in philosophers:
        philosopher.start()

    for philosopher in philosophers:
        philosopher.join()
