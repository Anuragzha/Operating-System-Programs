4)write a program to implement process synchronization using reader writer problem.
#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>
#include <chrono>
 
using namespace std;
 
mutex mtx;              // Mutex for reader count update
sem_t wrt;             // Semaphore for writer access
int read_count = 0;    // Number of active readers
 
// Reader Function
void reader(int id) {
   while (true) {
       this_thread::sleep_for(chrono::milliseconds(500)); // Simulate random read time
 
       // Entry Section
       mtx.lock();
       read_count++;
       if (read_count == 1) {
           sem_wait(&wrt); // First reader locks the writer
       }
       mtx.unlock();
 
       // Reading section
       cout << "Reader " << id << " is reading..." << endl;
       this_thread::sleep_for(chrono::milliseconds(1000)); // Simulating read time
 
       // Exit Section
       mtx.lock();
       read_count--;
       if (read_count == 0) {
           sem_post(&wrt); // Last reader unlocks the writer
       }
       mtx.unlock();
   }
}
 
// Writer Function
void writer(int id) {
   while (true) {
       this_thread::sleep_for(chrono::milliseconds(2000)); // Simulate random write time
 
       // Entry Section
       sem_wait(&wrt); // Writer acquires lock
       cout << "Writer " << id << " is writing..." << endl;
       this_thread::sleep_for(chrono::milliseconds(2000)); // Simulating write time
 
       // Exit Section
       sem_post(&wrt); // Writer releases lock
   }
}
 
int main() {
   sem_init(&wrt, 0, 1); // Initialize writer semaphore
 
   // Creating multiple reader and writer threads
   thread readers[5], writers[2];
 
   for (int i = 0; i < 5; i++) {
       readers[i] = thread(reader, i + 1);
   }
 
   for (int i = 0; i < 2; i++) {
       writers[i] = thread(writer, i + 1);
   }
 
   // Joining threads (never actually reached in an infinite loop setup)
   for (int i = 0; i < 5; i++) {
       readers[i].join();
   }
 
   for (int i = 0; i < 2; i++) {
       writers[i].join();
   }
 
   sem_destroy(&wrt); // Cleanup semaphore
 
   return 0;
}