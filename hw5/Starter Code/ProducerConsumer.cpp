#include "ProducerConsumer.hpp"
#include <iostream>

ProducerConsumer :: ProducerConsumer()
{
    queueFront = queueEnd = counter = 0;
}

bool ProducerConsumer :: isEmpty()
{
    if(counter == 0){
      return true;
    }
    return false;
}

bool ProducerConsumer :: isFull()
{
    if(counter == SIZE){
      return true;
    }
    return false;
}

void ProducerConsumer :: enqueue(std::string item)
{
    if(isFull()){
      std::cout << "Queue full, cannot add new item" << std::endl;
      return;
    }
    queue[queueEnd] = item;
    queueEnd = (queueEnd + 1) % SIZE;
    counter ++;
}

void ProducerConsumer :: dequeue()
{
    if(isEmpty()){
      std::cout << "Queue empty, cannot dequeue an item" << std::endl;
      return;
    }
    queueFront = (queueFront + 1) % SIZE;
    counter --;
}

int ProducerConsumer :: queueSize()
{
    return counter;
}

std::string ProducerConsumer :: peek()
{
    if(isEmpty()){
      std::cout << "Queue empty, cannot peek" << std::endl;
    }
    return queue[queueFront];
}
