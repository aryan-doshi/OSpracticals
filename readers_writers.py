import threading
import time

READERS_COUNT = 5
WRITERS_COUNT = 3

lock = threading.Lock()
cv_read = threading.Condition(lock)
cv_write = threading.Condition(lock)
read_count = 0
write_count = 0
data = 0

def reader(id):
    global read_count, data
    
    while True:
        # Enter reader critical section
        with lock:
            while write_count > 0:
                cv_read.wait()
            read_count += 1
        
        # Read data
        print(f"Reader {id} reads data {data}")
        time.sleep(0.5)
        
        # Exit reader critical section
        with lock:
            read_count -= 1
            if read_count == 0:
                cv_write.notify()
        
        # Sleep for some time
        time.sleep(0.5)

def writer(id):
    global write_count, data
    
    while True:
        # Enter writer critical section
        with lock:
            while write_count > 0 or read_count > 0:
                cv_write.wait()
            write_count += 1
        
        # Write data
        data += 1
        print(f"Writer {id} writes data {data}")
        time.sleep(0.5)
        
        # Exit writer critical section
        with lock:
            write_count -= 1
            if write_count == 0:
                cv_read.notify_all()
                cv_write.notify()
        
        # Sleep for some time
        time.sleep(0.5)

# Start reader threads
readers = []
for i in range(READERS_COUNT):
    readers.append(threading.Thread(target=reader, args=(i,)))
    readers[-1].start()

# Start writer threads
writers = []
for i in range(WRITERS_COUNT):
    writers.append(threading.Thread(target=writer, args=(i,)))
    writers[-1].start()

# Wait for all threads to finish
for r in readers:
    r.join()
for w in writers:
    w.join()
