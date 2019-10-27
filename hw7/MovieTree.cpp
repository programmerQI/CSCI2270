#include "MovieTree.hpp"
#include <iostream>

MovieTree::MovieTree()
{
    root = NULL;
}

MovieTree::~MovieTree()
{

}

void printList(LLMovieNode *node)
{
    do{
      std::cout << "" << std::endl;
      node = node -> next;
    } while (node != NULL);
}

void preOrderTravers(TreeNode *node)
{
    if(node -> leftChild != NULL) {
      preOrderTravers(node -> leftChild);
    }
    if(node -> head != NULL) {
      std::cout << "" << std::endl;
      printList(node -> head);
    }
    if(node -> rightChild != NULL) {
      preOrderTravers(node -> rightChild);
    }
}

void MovieTree::printMovieInventory()
{
    if(root == NULL){
      std::cout << "" << std::endl;
      return;
    }
    preOrderTravers(root);
}

void addLLNode(TreeNode *tnode, LLMovieNode *movie)
{
    if(tnode -> head == NULL){
      tnode -> head = movie;
    } else {
      LLMovieNode *n = tnode -> head;
      while(n -> next != NULL){
        n = n -> next;
      }
      n -> next = movie;
    }
}

void addTreeNode(TreeNode *node, char c, LLMovieNode *movie)
{
  char tc = node -> titleChar;
  if(tc == c){
    addLLNode(node, movie);
  } else if (tc < c && node -> leftChild != NULL) {
    addTreeNode(node -> leftChild, c, movie);
  } else if (tc > c && node -> rightChild != NULL) {
    addTreeNode(node -> rightChild, c, movie);
  }

  TreeNode *newTNode = new TreeNode();
  newTNode -> head = NULL;
  newTNode -> titleChar = c;
  newTNode -> parent = node;
  newTNode -> leftChild = NULL;
  newTNode -> rightChild = NULL;

  if(tc < c){
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

int main()
{
    return 0;
}
