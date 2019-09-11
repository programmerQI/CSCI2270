#include<iostream>
#include<iomanip>
#include<fstream>
#include<stdlib.h>
#define ARRAYSIZE_IGNOREWORDS 50
#define STARTSIZE_UNIQUEWORDS 100
int arraysize_uniquewords = STARTSIZE_UNIQUEWORDS;
int doubleTimes = 0;
typedef struct DcNode{
    struct DcNode* next[26];
    bool isWord;
    int index;
}DcNode, *DcLink;
struct WordItem{
    std::string word;
    int count;
    DcLink link;
    WordItem() : word(""), count(0), link(NULL) {}
    ~WordItem(){
      free(link);
      link = NULL;
    }
};
DcLink initNode()
{
    DcLink node = (DcLink)malloc(sizeof(DcNode));
    for(int i = 0; i < 26; i ++){
      node -> next[i] = NULL;
    }
    node -> isWord = false;
    node -> index = -1;
    return node;
}
void clearDc(DcLink root)
{
    if(root == NULL){
      return;
    }
    for(int i = 0; i < 26; i ++){
      if(root -> next[i] != NULL){
        clearDc(root -> next[i]);
      }
    }
    free(root);
    root = NULL;
}
void setIndex(WordItem *wordItem, int index)
{
    DcLink dcLink = (*wordItem).link;
    dcLink -> index = index;
}
WordItem* doubleWordsArray(WordItem *array)
{
    doubleTimes ++;
    int newArraySize = arraysize_uniquewords * 2;
    WordItem *newArray = new WordItem[newArraySize];
    for(int i = 0; i < arraysize_uniquewords; i ++){
      newArray[i] = array[i];
    }
    delete(array);
    array = NULL;
    arraysize_uniquewords = newArraySize;
    return newArray;
}
void getStopWords(const char *ignoreWordFileName, std::string ignoreWords[], DcLink root)
{
    std::string filename(ignoreWordFileName);
    std::ifstream in(filename);
    if(!in.is_open()){
      std::cout << "Fail to open " << filename << std::endl;
    }
    std::string line = "";
    int cnt = 0;
    DcLink tmp = root;
    while(getline(in, line)){
      ignoreWords[cnt ++] = line;
      for(int i = 0; i < line.length(); i ++){
        if(tmp -> next[i] == NULL){
          tmp -> next[i] = initNode();
        }
        tmp = tmp -> next[i];
      }
      tmp -> isWord = true;
    }
    in.close();
}
// bool isStopWord(std::string word, std::string ignoreWords[])
// {
//     for(int i = 0; i < 50; i ++){
//       if(word == ignoreWords[i]){
//         return true;
//       }
//     }
//     return false;
// }
bool isStopWord(std::string word, DcLink root)
{
    DcLink tmp = root;
    for(int i = 0; i < word.length(); i ++){
      if(tmp -> next[i] == NULL){
        return false;
      }
      tmp = tmp -> next[i];
    }
    if(tmp -> isWord){
      return true;
    } else {
      return false;
    }
}
int getTotalNumberNonStopWords(WordItem uniqueWords[], int length){
    int count = 0;
    for(int i = 0; i < length; i ++){
        count = count + uniqueWords[i].count;
    }
    return count;
}
int readText(const char *textfilename, WordItem uniquewords[], int numUqWords, DcLink root, int total)
{
    int cnt = total;
    std::string filename(textfilename);
    std::ifstream in(filename);
    if(! in.is_open()){
      return -1;
    }
    std::string line;
    while(getline(in, line)){

    }
    in.close();
    return cnt;
}
int optLine(std::string line,WordItem uniquewords[], int numUqWords, char spliter, DcLink root)
{
    int cnt = 0;
    DcLink tmp = root;
    line.append(" ");
    std::string word = "";
    for(int i = 0; i < line.length(); i ++){
      char c = line[i];
      if(c == spliter && ! word.empty()){
        if(tmp -> isWord){
          int index = tmp -> index;
          uniquewords[index].count ++;
        } else {
          
        }
        word = "";
        tmp = root;
        cnt ++;
      } else {
        if(tmp -> next[i] == NULL){
          tmp -> next[i] = initNode();
        }
        tmp = tmp -> next[i];
        word = word + c;
      }
    }
    return cnt;
}
void qSort(WordItem uniqueWords[], int begin, int end)
{
    if(begin >= end){
      return;
    }
    WordItem pvt = uniqueWords[begin];
    int i = begin;
    int j = end;
    while(i < j){
      while(i < j && uniqueWords[j].count < pvt.count){
        j --;
      }
      if(i < j){
        uniqueWords[i] = uniqueWords[j];
        setIndex(&(uniqueWords[i]), i);
      }
      while(i < j && uniqueWords[i].count >= pvt.count){
        i ++;
      }
      if(i < j){
        uniqueWords[j] = uniqueWords[i];
        setIndex(&(uniqueWords[j]), j);
      }
    }
    uniqueWords[i] = pvt;
    setIndex(&(uniqueWords[i]), i);
    qSort(uniqueWords, begin, i - 1);
    qSort(uniqueWords, i + 1, end);
}
void arraySort(WordItem uniqueWords[], int length)
{
    qSort(uniqueWords, 0, length - 1);
}
void printNext10(WordItem uniqueWords[], int N, int totalNumWords){
    for(int i = 0; i < 10; i ++){
      std::cout << std::fixed;
      std::cout << std::setprecision(4);
      std::cout << 1.0 * uniqueWords[i + N].count / totalNumWords << " - " << uniqueWords[i + N].word << std::endl;
    }
}
void printStringArray(std::string array[], int size){
    for(int i = 0; i < size; i ++){
      std::cout << array[i] << std::endl;
    }
}
void printWordItemArray(WordItem array[], int size){
    for(int i = 0; i < size; i ++){
      std::cout << array[i].word << std::endl;
    }
}
int main(int argc, char* argv[])
{
    if(argv[1] == NULL || argv[2] == NULL && argv[3] == NULL){
      std::cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" << std::endl;
      return -1;
    }
    std::string ignoreWords[ARRAYSIZE_IGNOREWORDS];
    DcLink igroot = initNode();
    getStopWords(argv[2], ignoreWords, igroot);
    printStringArray(ignoreWords, ARRAYSIZE_IGNOREWORDS);

    // std::cout << "211" << std::endl;
    WordItem *uniquewords = new WordItem[arraysize_uniquewords];
    DcLink uqroot = initNode();

    clearDc(igroot);
    igroot = NULL;
    clearDc(uqroot);
    uqroot = NULL;
    return 0;
}
