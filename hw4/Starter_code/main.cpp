/****************************************************************/
/*                   Assignment 4 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
// you may include more libraries as needed

using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    CountryNetwork net;
    std::string in;
    displayMenu();
    while(std::getline(std::cin, in)){
      if(in == "1"){
        net.loadDefaultSetup();
        net.printPath();
      } else if (in == "2") {
        net.printPath();
      }
      //  else if (in == "3") {
      //   std::string c, m;
      //   std::cout << "Enter name of the country to receive the message: " << std::endl;
      //   std::getline(std::cin, c);
      //   std::cout << "Enter the message to send: " << std::endl;
      //   std::getline(std::cin, m);
      //   std::cout << std::endl;
      //   net.transmitMsg(c, m);
      // }
      else if (in == "3") {
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
      } else if (in == "4") {
        std::string n;
        std::cout << "Enter a country name: " << std::endl;
        std::getline(std::cin, n);
        net.deleteCountry(n);
        net.printPath();
      } else if (in == "5") {
        net.reverseEntireNetwork();
        net.printPath();
      } else if (in == "6") {
        std::string n, p;
        std::cout << "Enter the count of values to be rotated: " << std::endl;
        std::getline(std::cin, n);
        net.rotateNetwork(std::stoi(n));
        net.printPath();
      } else if (in == "7") {
        std::cout << "Network before deletion" << std::endl;
        net.printPath();
        net.deleteEntireNetwork();
        std::cout << "Network after deletion" << std::endl;
        net.printPath();
      } else if (in == "8") {
        std::cout << "Quitting... cleaning up path: " << std::endl;
        if(net.isEmpty()){
          net.printPath();
          std::cout << "Path cleaned" << std::endl;
          break;
        } else {
          //std::cout << "Error: Path NOT cleaned" << std::endl;
          net.printPath();
          net.deleteEntireNetwork();
          std::cout << "Path cleaned" << std::endl;
          break;
        }
      }else {
        std::cout << "Invalid Input" << std::endl;
      }
      displayMenu();
    }
    std::cout << "Goodbye!" << endl;
    return 0;
}

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Add Country " << endl;
    cout << " 4. Delete Country " << endl;
    cout << " 5. Reverse Network" << endl;
    cout << " 6. Rotate Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
