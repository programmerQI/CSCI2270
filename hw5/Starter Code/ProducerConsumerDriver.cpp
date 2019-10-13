/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
  cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}

int main(int argc, char const *argv[])
{
		ProducerConsumer pc;
		std::string in;
		while(true){
			menu();
			std::cin >> in;
			if(in == "1"){
				std::cout << "Enter the number of items to be produced:" << std::endl;
				int n;
				std::cin >> n;
				for(int i = 1; i <= n; i ++){
					std::cout << "Item" << i << ":" << std::endl;
					std::string item;
					std::cin >> item;
					pc.enqueue(item);
					if(pc.isFull()){
						break;
					}
				}
			} else if (in == "2") {
				std::cout << "Enter the number of items to be consumed:" << std::endl;
				int n;
				std::cin >> n;
				for(int i = 0; i < n; i ++)
				{
					std::cout << "Consumed: " << pc.peek() << std::endl;
					pc.dequeue();
					if(pc.isEmpty()){
						std::cout << "No more items to consume from queue" << std::endl;
						break;
					}
				}
			} else if (in == "3") {
				std::cout << "Number of items in the queue:" << pc.queueSize() << std::endl;
				break;
			} else {

			}
		}
}
