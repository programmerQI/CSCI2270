#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <vector>

using namespace std;

// MovieNode: node struct that will be stored in the MovieTree BST

MovieTree::MovieTree() {
  root = NULL;
}

void deleteNode(MovieNode *node)
{
    if(node -> left != NULL){
      deleteNode(node -> left);
      node -> left = NULL;
    }
    if(node -> right != NULL){
      deleteNode(node -> right);
      node -> right = NULL;
    }
    delete node;
}

MovieTree::~MovieTree() {
    deleteNode(root);
    root = NULL;
}

void getMovieList(MovieNode *node, std::vector<MovieNode*>& list, int& cnt)
{
    if(cnt >= 100){
      return;
    }
    if(node -> left != NULL){
      getMovieList(node -> left, list, cnt);
    }
    list.push_back(node);
    cnt ++;
    if(node -> right != NULL){
      getMovieList(node -> right, list, cnt);
    }
}

void MovieTree::printMovieInventory() {
  if(root == NULL){
    std::cout << "Tree is Empty. Cannot print" << std::endl;
    return;
  }
  std::vector<MovieNode*> inv;
  int cnt = 0;
  getMovieList(root, inv, cnt);
  if(cnt == 0){
    std::cout << "Tree is Empty. Cannot print" << std::endl;
  }
  for(int i = 0; i < cnt; i ++){
    MovieNode m = *inv[i];
    std::cout << "Movie: " << m.title << " " << m.rating << std::endl;
  }
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {
  if(root == NULL){
    root = new MovieNode(ranking, title, year, rating);
    return;
  }
  MovieNode *node = root;
  while(true){
    int res = title.compare(node -> title);
    if(res < 0 && node -> left != NULL){
      node = node -> left;
    } else if (res < 0) {
      node -> left = new MovieNode(ranking, title, year, rating);
      break;
    } else if (res > 0 && node -> right != NULL){
      node = node -> right;
    } else if (res > 0) {
      node -> right = new MovieNode(ranking, title, year, rating);
      break;
    } else if (res == 0){
      break;
    }
  }
  node = NULL;
}

void MovieTree::findMovie(string title) {
  if(root == NULL){
    return;
  }
  MovieNode *node = root;
  int res;
  do{
    res = title.compare(node -> title);
    if(res < 0 && node -> left != NULL){
      node = node -> left;
    } else if (res > 0 && node -> right != NULL){
      node = node -> right;
    } else if (res != 0) {
      std::cout << "Movie not found." << std::endl;
      node = NULL;
      return;
    }
  } while (res != 0);
  std::cout << "Movie Info:" << std::endl;
  std::cout << "==================" << std::endl;
  std::cout << "Ranking:" << node->ranking << std::endl;
  std::cout << "Title :" << node->title << std::endl;
  std::cout << "Year :" << node->year << std::endl;
  std::cout << "rating :" << node->rating << std::endl;
}

void query(MovieNode *node, float rating, int year)
{
  if(node -> rating > rating && node -> year > year){
    std::cout << node -> title << "(" << node -> year << ") " << node -> rating << std::endl;
  }
  if(node -> left != NULL){
    query(node -> left, rating, year);
  }
  if (node -> right != NULL) {
    query(node -> right, rating, year);
  }
}

void MovieTree::queryMovies(float rating, int year) {
  std::cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << std::endl;
  query(root, rating, year);
}

void sumRating(MovieNode *node, float& sum, int& cnt)
{
    sum = sum + node -> rating;
    cnt = cnt + 1;
    if(node -> left != NULL){
      sumRating(node -> left, sum, cnt);
    }
    if(node -> right != NULL){
      sumRating(node -> right, sum, cnt);
    }
}

void MovieTree::averageRating() {
  if(root == NULL){
    std::cout << "Average rating:0.0" << std::endl;
    return;
  }
  float sum = 0.0;
  int cnt = 0;
  sumRating(root, sum, cnt);
  float ave = sum / cnt;
  std::cout << "Average rating:" << ave << std::endl;
}

void showMenu()
{
    std::cout << "======Main Menu======" << std::endl;
    std::cout << "1. Find a movie" << std::endl;
    std::cout << "2. Query movies" << std::endl;
    std::cout << "3. Print the inventory" << std::endl;
    std::cout << "4. Average Rating of movies" << std::endl;
    std::cout << "5. Quit" << std::endl;
}

int split(std::string line, char spliter, std::string strs[], int size)
{
    line = line + spliter;
    int len = line.length();
    std::string word = "";
    int cnt = 0;
    for(int i = 0; i < len; i ++){
      char c = line[i];
      if(c == spliter){
        strs[cnt ++] = word;
        word = "";
        if(cnt >= size){
          return size;
        }
      } else {
        word = word + c;
      }
    }
    return cnt;
}

int readFile(std::string filename, MovieTree& t)
{
    std::ifstream in(filename);
    if(!in.is_open()){
      return -1;
    }
    std::string line;
    while(getline(in, line)){
      std::string strs[5];
      split(line, ',', strs, 5);
      t.addMovieNode(std::stoi(strs[0]), strs[1], std::stoi(strs[2]), std::stof(strs[3]));
    }
    in.close();
    return 0;
}

int main(int argc, char* args[])
{
    if(argc != 2){
      std::cout << "Not enough argument!" << std::endl;
      return 0;
    }
    MovieTree mt;
    std::string file(args[1]);
    readFile(file, mt);
    std::string in;
    while(true){
      showMenu();
      std::getline(std::cin, in);
      if(in == "1") {
        std::cout << "Enter title:" << std::endl;
        std::string t;
        std::getline(std::cin, t);
        mt.findMovie(t);
      } else if (in == "2") {
        std::cout << "Enter minimum rating:" << std::endl;
        std::string r;
        std::getline(std::cin, r);
        std::cout << "Enter minimum year:" << std::endl;
        std::string y;
        std::getline(std::cin, y);
        mt.queryMovies(std::stof(r), std::stoi(y));
      } else if (in == "3") {
        mt.printMovieInventory();
      } else if (in == "4") {
        mt.averageRating();
      } else if (in == "5") {
        std::cout << "Goodbye!" << std::endl;
        break;
      }
    }
    return 0;
}
