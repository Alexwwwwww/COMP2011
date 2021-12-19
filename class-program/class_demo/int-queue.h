#include <iostream>     /* File: int-queue.h */
#include <cstdlib>
using namespace std;
const int BUFFER_SIZE = 5;

class int_queue // Circular queue
{
  private:
    int data[BUFFER_SIZE]; // Use an array to store data
    int num_items;         // Number of items on the queue
    int first;             // Index of the first item; start from 0

  public:
    int_queue() { first = 0; num_items = 0; } 

    // Check if the int_queue is empty
    bool empty() const { return (num_items == 0); }

    // Check if the int_queue is full
    bool full() const { return (num_items == BUFFER_SIZE); }

    // Give the number of data currently stored
    int size() const { return num_items; }

    int frontIndex() const { return first;}

    int getData(int pos) const { return data[pos];}

    int getCapacity() const {return BUFFER_SIZE;}
        
    // Retrieve the value of the front item
    int front() const
    {
        if (!empty())
            return data[first];

        cerr << "Warning: Queue is empty; can't retrieve any data!" << endl;
        exit(-1);
    }

    void enqueue(int x)  // Add a new item to the back of the queue
    {
        if (!full())
        {
            cout<<"Enqueueing: "<<x<<endl;
            data[(first+num_items) % BUFFER_SIZE] = x;
            ++num_items;
            cout<<"The first item is stored at position: "<<first<<endl;
            cout<<"The queue contains "<<num_items<<" items"<<endl;
            cout<<"The next item will be stored at location: "<<(first+num_items) % BUFFER_SIZE<<endl;
        } else {
            cerr << "Error: Queue is full; can't add (" << x << ")!" << endl;
            exit(-1);
        }
        
    }

    void dequeue()       // Remove the front item from the queue
    {
        if (!empty())
        {
            cout<<"Dequeueing: "<<data[first]<<endl;
            first = (first+1) % BUFFER_SIZE;
            --num_items;
            cout<<"The first item is stored at position: "<<first<<endl;
            cout<<"The queue contains "<<num_items<<" items"<<endl;
            cout<<"The next item will be stored at location: "<<(first+num_items) % BUFFER_SIZE<<endl;
        } else {
            cerr << "Error: Queue is empty; can't remove any data!" << endl;
            exit(-1);
        }
    }


};
