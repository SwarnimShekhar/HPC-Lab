#Producer-Consumer Problem

import threading
import time
import queue

q = queue.Queue(maxsize=10)


def producer():
    while True:
        item = time.time()
        q.put(item)
        print(f'Produced {item}')
        time.sleep(1)

def consumer():
    while True:
        item = q.get()
        print(f'Consumed {item}')
        q.task_done()
        time.sleep(2)

producer_thread = threading.Thread(target=producer)
consumer_thread = threading.Thread(target=consumer)

producer_thread.start()
consumer_thread.start()

q.join()

#Dining-Philosophers Problem

import threading
import time

num_philosophers = 5

forks = [threading.Semaphore(1) for _ in range(num_philosophers)]

limit = threading.Semaphore(num_philosophers - 1)

def philosopher(id):
    while True:
        time.sleep(1)  # Thinking
        print(f'Philosopher {id} is thinking.')
        limit.acquire()
        forks[id].acquire()
        forks[(id + 1) % num_philosophers].acquire()
        print(f'Philosopher {id} is eating.')
        time.sleep(1)  # Eating
        forks[id].release()
        forks[(id + 1) % num_philosophers].release()
        limit.release()

philosophers = [threading.Thread(target=philosopher, args=(i,)) for i in range(num_philosophers)]

for p in philosophers:
    p.start()

#Readers and Writers Problem

import threading
import time

resource = 0
readers = 0
resource_access = threading.Semaphore(1)
read_count_access = threading.Semaphore(1)


def reader(id):
    global readers
    while True:
        read_count_access.acquire()
        readers += 1
        if readers == 1:
            resource_access.acquire()
        read_count_access.release()

        print(f'Reader {id} is reading resource: {resource}')
        time.sleep(1)  # Reading

        read_count_access.acquire()
        readers -= 1
        if readers == 0:
            resource_access.release()
        read_count_access.release()
        time.sleep(1)


def writer(id):
    global resource
    while True:
        resource_access.acquire()
        resource += 1
        print(f'Writer {id} is writing to resource: {resource}')
        time.sleep(1)  # Writing
        resource_access.release()
        time.sleep(1)


reader_threads = [threading.Thread(target=reader, args=(i,)) for i in range(3)]
writer_threads = [threading.Thread(target=writer, args=(i,)) for i in range(2)]

for t in reader_threads + writer_threads:
    t.start()

#Sleeping Barber Problem

import threading
import time
import random

waiting_chairs = threading.Semaphore(3)
barber_chair = threading.Semaphore(1)
barber_sleeping = threading.Semaphore(0)

def barber():
    while True:
        print('Barber is waiting for a customer.')
        barber_sleeping.acquire()
        barber_chair.acquire()
        print('Barber is cutting hair.')
        time.sleep(2)  # Cutting hair
        barber_chair.release()

def customer(id):
    while True:
        time.sleep(random.randint(1, 5))
        if waiting_chairs.acquire(blocking=False):
            print(f'Customer {id} is waiting.')
            barber_sleeping.release()
            barber_chair.acquire()
            print(f'Customer {id} is getting a haircut.')
            barber_chair.release()
            waiting_chairs.release()
        else:
            print(f'Customer {id} left (no available chair).')

barber_thread = threading.Thread(target=barber)
customer_threads = [threading.Thread(target=customer, args=(i,)) for i in range(10)]

barber_thread.start()
for t in customer_threads:
    t.start()
