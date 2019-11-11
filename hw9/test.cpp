#include "Graph.hpp"
vertex* Graph::DijkstraAlgorithm(std::string start, std::string end)
{
    class Pqueue{

      struct Node{
        vertex* v;
        struct Node* next;
        Node() : v(NULL), next(NULL) {}
        Node(vertex *ver) : v(ver), next(NULL) {}
      };

      Node *root;

      Pqueue(){
        root = NULL;
      }

      bool isEmpty(){
        if(root == NULL){
          return true;
        }
        return false;
      }

      void add(vertex* n){
        if(isEmpty()){
          root = new Node(n);
          return;
        }
        Node *i = root;
        while(i -> next != NULL){
          if(i -> next -> v -> distance <= n -> distance){
            i = i -> next;
          } else {
            break;
          }
        }
        Node *newNode = new Node(n);
        newNode -> next = i -> next;
        i -> next = newNode;
      }

      void dequeue(){
        if(root == NULL){
          return;
        }
        Node* tmp = root;
        root = root -> next;
        delete tmp;
      }

      vertex* front(){
        if(root == NULL){
          return NULL;
        }
        return root -> v;
      }

      void update(){
        if(root == NULL){
          return;
        }
        Node *i = root;
        while(i -> next != NULL){
          Node *j = i;
          while(j -> next != NULL){
            int dis_cur = j -> v -> distance;
            int dis_nex = j -> next -> v -> distance;
            if(dis_nex < dis_cur) {
              vertex* tmp = j -> next -> v;
              j -> next -> v = j -> v;
              j -> v = tmp;
            }
            j = j -> next;
          }
        }
      }
    };
    return NULL;
}
int main()
{
  return 0;
}
