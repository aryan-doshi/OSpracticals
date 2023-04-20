import queue
import threading
import time

BUFFER_SIZE = 5

buffer = queue.Queue(BUFFER_SIZE) # bounded buffer

def producer():
    for i in range(1, 11):
        buffer.put(i) # add item to buffer
        print("Produced item", i)
        time.sleep(0.5) # sleep for some time

def consumer():
    for i in range(1, 11):
        item = buffer.get() # get item from buffer
        print("Consumed item", item)
        time.sleep(0.5) # sleep for some time

if __name__ == "__main__":
    producerThread = threading.Thread(target=producer)
    consumerThread = threading.Thread(target=consumer)
    
    producerThread.start()
    consumerThread.start()
    
    producerThread.join()
    consumerThread.join()
