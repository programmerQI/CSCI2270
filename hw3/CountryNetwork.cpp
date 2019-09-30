/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
    head = NULL;
}

bool CountryNetwork :: isEmpty()
{
    if(head == NULL){
      return true;
    }
    return false;
}

/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName)
{
    Country *newCountry = new Country();
    newCountry -> name = countryName;
    newCountry -> message = "";
    newCountry -> numberMessages = 0;
    newCountry -> next = NULL;
    if(head == NULL){
      head = newCountry;
      std::cout << "adding: " << countryName << " (HEAD)" << std::endl;
    } else if (previous == NULL){
      newCountry -> next = head;
      head = newCountry;
      std::cout << "adding: " << countryName << " (HEAD)" << std::endl;
    } else {
      newCountry -> next = previous -> next;
      previous -> next = newCountry;
      std::cout << "adding: " << countryName << " (prev: " << previous -> name << ")" << std::endl;
    }
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
    if(head != NULL){
      return;
    }
    std::string names[] = {"United States", "Canada", "Brazil", "India", "China", "Australia"};
    Country *tmp = NULL;
    //std::cout << "adding: prev: [HEAD]" << std::endl;
    for(std::string i : names){
      insertCountry(tmp, i);
      tmp = head;
      while(tmp -> next != NULL){
        tmp = tmp -> next;
      }
    }
}

/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
    if(head == NULL){
      return NULL;
    }
    Country *country = head;
    while(country != NULL){
      if(country -> name == countryName){
        return country;
      }
      country = country -> next;
    }
    return NULL;
}

/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
    if(head == NULL){
      std::cout << "Empty list" << std::endl;
      return;
    }
    Country *tmp = head;
    if(searchNetwork(receiver) == NULL){
      std::cout << "Country not found" << std::endl;
      return;
    }
    while(tmp != NULL){
      tmp -> message = message;
      tmp -> numberMessages ++;
      std::cout << tmp -> name << " [# messages received: " << tmp -> numberMessages << "] received: " << tmp -> message << std::endl;
      if(tmp -> name == receiver){
        return;
      }
      tmp = tmp -> next;
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
    std::cout << "== CURRENT PATH ==" << std::endl;
    if(head == NULL){
      std::cout << "nothing in path" << std::endl;
      std::cout << "===" << std::endl;
      return;
    }
    Country *tmp = head;
    while(tmp != NULL){
      std::cout << tmp -> name << " -> ";
      tmp = tmp -> next;
    }
    std::cout << "NULL" << std::endl;
    std::cout << "===" << std::endl;
    return;
}

 // Clean the memory
 void CountryNetwork::cleanNetwork(){
   if(head == NULL){
     return;
   }
   Country *node = head;
   Country *tmp = NULL;
   while(node != NULL){
     //std::cout << "Delete..." << std::endl;
     tmp = node -> next;
     delete node;
     node = tmp;
   }
   head = NULL;
   return;
 }
