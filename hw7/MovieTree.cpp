#include "MovieTree.hpp"
#include <iostream>

MovieTree::MovieTree()
{
    root = NULL;
}

void deleteList(LLMovieNode *node)
{
  if(node -> next != NULL){
    deleteList(node -> next);
  }
  delete node;
  node = NULL;
}

void deleteTree(TreeNode *node)
{
  if(node -> leftChild != NULL){
    deleteTree(node -> leftChild);
  }
  if(node -> rightChild != NULL){
    deleteTree(node -> rightChild);
  }
  deleteList(node -> head);
  delete node;
  node = NULL;
}

MovieTree::~MovieTree()
{
  if(root != NULL){
    deleteTree(root);
  }
}

void printList(LLMovieNode *node)
{
    do{
      std::cout << " >> " << node -> title << " " << node -> rating << std::endl;
      node = node -> next;
    } while (node != NULL);
}

void preOrderTravers(TreeNode *node)
{
    if(node -> leftChild != NULL) {
      preOrderTravers(node -> leftChild);
    }
    if(node -> head != NULL) {
      std::cout << "Movies starting with letter: " << node -> titleChar << std::endl;
      printList(node -> head);
    }
    if(node -> rightChild != NULL) {
      preOrderTravers(node -> rightChild);
    }
}

void MovieTree::printMovieInventory()
{
    if(root == NULL){
      //std::cout << "" << std::endl;
      return;
    }
    preOrderTravers(root);
}

void addLLNode(TreeNode *tnode, LLMovieNode *movie)
{
    // if(tnode -> head == NULL){
    //   tnode -> head = movie;
    // } else {
    //   LLMovieNode *n = tnode -> head;
    //   while(n -> next != NULL){
    //     n = n -> next;
    //   }
    //   n -> next = movie;
    // }
    if(tnode -> head == NULL){
      tnode -> head = movie;
      return;
    }

    LLMovieNode *lnode = new LLMovieNode();
    lnode -> next = tnode -> head;
    std::string t = movie -> title;
    while(t.compare(lnode -> next -> title) >= 0){
      lnode = lnode -> next;
      if(lnode -> next == NULL){
        break;
      }
    }
    movie -> next = lnode -> next;
    if(lnode -> next == tnode -> head){
      tnode -> head = movie;
    } else {
      lnode -> next = movie;
    }
}

void addTreeNode(TreeNode *node, char c, LLMovieNode *movie)
{
  char tc = node -> titleChar;
  if(tc == c){
    addLLNode(node, movie);
    return;
  } else if (c < tc && node -> leftChild != NULL) {
    addTreeNode(node -> leftChild, c, movie);
    return;
  } else if (c > tc && node -> rightChild != NULL) {
    addTreeNode(node -> rightChild, c, movie);
    return;
  }

  TreeNode *newTNode = new TreeNode();
  newTNode -> head = NULL;
  newTNode -> titleChar = c;
  newTNode -> parent = node;
  newTNode -> leftChild = NULL;
  newTNode -> rightChild = NULL;

  if(c < tc){
    node -> leftChild = newTNode;
    addTreeNode(node -> leftChild, c, movie);
  } else {
    node -> rightChild = newTNode;
    addTreeNode(node -> rightChild, c, movie);
  }
}

void MovieTree::addMovie(int ranking, std::string title, int year, float rating)
{
    char c = title[0];
    if(root == NULL){
      root = new TreeNode();
      root -> head = NULL;
      root -> titleChar = c;
      root -> parent = NULL;
      root -> leftChild = NULL;
      root -> rightChild = NULL;
    }
    LLMovieNode *movie = new LLMovieNode(ranking, title, year, rating);
    addTreeNode(root, c, movie);
}

void MovieTree::deleteMovie(std::string title)
{
    if(root == NULL){
      std::cout << "Movie: " << title << " not found, cannot delete." << std::endl;
      return;
    }

    char c = title[0];
    TreeNode *n = root;
    int mark = 0;
    while(n -> titleChar != c){
      if(c < n -> titleChar && n -> leftChild != NULL){
        n = n -> leftChild;
        mark = 1;
      } else if (c > n -> titleChar && n -> rightChild != NULL){
        n = n -> rightChild;
        mark = 2;
      } else {
        break;
      }
    }

    if(n -> titleChar != c){
      //std::cout << "" << std::endl;
      std::cout << "Movie: " << title << " not found, cannot delete." << std::endl;
      return;
    }

    LLMovieNode *ln = new LLMovieNode();
    ln -> next = n -> head;
    while(ln -> next != NULL){
      if(ln -> next -> title == title){
        //Delete
        LLMovieNode *tmp = ln -> next;
        if(ln -> next == n -> head){
          n -> head = n -> head -> next;
        } else {
          ln -> next = ln -> next -> next;
        }
        delete tmp;
        tmp = NULL;
        ln = NULL;
        //std::cout << "" << std::endl;
        return;
      }
      ln = ln -> next;
    }

    //std::cout << "" << std::endl;
}

int main()
{
    return 0;
}
