#include "CountryNetwork.hpp"
#include <iostream>
void displayMenu()
{
    std::cout << "Select a numerical option:" << std::endl;
    std::cout << "+=====Main Menu=========+" << std::endl;
    std::cout << "1. Build Network " << std::endl;
    std::cout << "2. Print Network Path " << std::endl;
    std::cout << "3. Transmit Message " << std::endl;
    std::cout << "4. Add Country " << std::endl;
    std::cout << "5. Quit " << std::endl;
    std::cout << "+-----------------------+" << std::endl;
    std::cout << "#> ";
    return;
}
int main()
{
    CountryNetwork net;

    std::string in;
    displayMenu();
    while(std::getline(std::cin, in) && in != "5"){
      if(in == "1"){
        net.loadDefaultSetup();
        net.printPath();
      } else if (in == "2") {
        net.printPath();
      } else if (in == "3") {
        std::string c, m;
        std::cout << "Enter name of the country to receive the message: " << std::endl;
        std::getline(std::cin, c);
        std::cout << "Enter the message to send: " << std::endl;
        std::getline(std::cin, m);
        std::cout << std::endl;
        net.transmitMsg(c, m);
      } else if (in == "4") {
        Country *pre = NULL;
        std::string n, p;
        std::cout << "Enter a new country name: " << std::endl;
        std::getline(std::cin, n);
        std::cout << "Enter the previous country name (or First): " << std::endl;
        while(std::getline(std::cin, p)) {
          if(p == "First") {
            net.insertCountry(NULL, n);
            break;
          }
          pre = net.searchNetwork(p);
          if(pre != NULL){
            net.insertCountry(pre, n);
            break;
          }
          std::cout << "INVALID(previous country name)...Please enter a VALID previous country name!" << std::endl;
        }
        net.printPath();
      } else {
        std::cout << "Invalid Input" << std::endl;
      }
      displayMenu();
    }
    std::cout << "Quitting... Cleaning up path" << std::endl;
    net.printPath();
    net.cleanNetwork();
    std::cout << "Goodbye!" << endl;
    return 0;
}
