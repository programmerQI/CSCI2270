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



/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
    if(head == NULL){
      return true;
    }
    if(head -> next == NULL){
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
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName) {
    if(head == NULL){
      return;
    }
    Country *i = new Country();
    i -> next = head;
    while(i -> next != NULL){
      if(i -> next -> name == countryName){
        Country *tmp = i -> next;
        if(i -> next == head){
          head = tmp -> next;
        } else {
          i -> next = tmp -> next;
        }
        delete tmp;
        tmp = NULL;
        return;
      }
      i = i -> next;
    }
    std::cout << "Country does not exist." << std::endl;
    i = NULL;
    return;
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
 * @see insertCountry, deletecountry
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
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork() {
    if(head == NULL){
      return;
    }
    Country *i = head;
    while(i != NULL){
      std::cout << "deleting: " << i -> name << std::endl;
      Country *tmp = i;
      i = i -> next;
      delete tmp;
      tmp = NULL;
    }
    std::cout << "Deleted network" << std::endl;
    head = NULL;
}

/*
 * Purpose: Rotate the linked list i.e. move 'n' elements from
 * the back of the the linked to the front in the same order.
 * @param number elements to be moved from the end of the list to the beginning
 * @return none
 */
//  void CountryNetwork :: rotateNetwork(int n) {
//    if(head == NULL){
//      return;
//    }
//    reverseEntireNetwork();
//    int cnt = 1;
//    Country *tmp = head;
//    do{
//      cnt ++;
//      tmp = tmp -> next;
//    } while (cnt < n && tmp != NULL);
//    Country *mark = tmp;
//    while(tmp -> next != NULL){
//      tmp = tmp -> next;
//    }
//    tmp -> next = head;
//    head = mark -> next;
//    mark -> next = NULL;
//    reverseEntireNetwork();
//    tmp = NULL;
//    mark = NULL;
// }

  void CountryNetwork :: rotateNetwork(int n) {
    if(head == NULL){
      std::cout << "Linked List is Empty" << std::endl;
      return;
    }
    int cnt = 1;
    Country *tmp = head;
    while(cnt < n && tmp != NULL) {
      tmp = tmp -> next;
      cnt ++;
    }
    if(cnt != n){
      std::cout << "Rotate not possible" << std::endl;
      return;
    }
    Country *mt = tmp;
    while(tmp -> next != NULL) {
      tmp = tmp -> next;
    }
    tmp -> next = head;
    head = mt -> next;
    mt -> next = NULL;
    tmp = NULL;
    mt = NULL;
    std::cout << "Rotate Complete" << std::endl;
  }

/*
 * Purpose: reverse the entire network
 * @param ptr head of list
 */
void CountryNetwork::reverseEntireNetwork() {
  if(head == NULL){
    return;
  }
  Country *pre = head;
  Country *c = pre -> next;
  pre -> next = NULL;
  while(c != NULL){
    Country *nxt = c -> next;
    c -> next = pre;
    pre = c;
    c = nxt;
  }
  head = pre;
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
