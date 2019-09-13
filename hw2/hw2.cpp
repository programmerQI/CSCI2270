#include<iostream>
#include<iomanip>
#include<fstream>
#include<stdlib.h>
#define ARRAYSIZE_IGNOREWORDS 50
#define STARTSIZE_UNIQUEWORDS 100
const static char SPLITER = ' ';
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
      link = NULL;
    }
};
DcLink initNode()
{
    // std::cout << "466" << std::endl;
    DcLink node = (DcLink)malloc(sizeof(DcNode));
    for(int i = 0; i < 26; i ++){
      node -> next[i] = NULL;
    }
    node -> isWord = false;
    node -> index = -1;
    // std::cout << "467" << std::endl;
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
    //std::cout << "990" << std::endl;
    for(int i = 0; i < arraysize_uniquewords; i ++){
      newArray[i] = array[i];
      //std::cout << newArray[i].word << "-" << newArray[i].count << " ";
    }
    //std::cout << std::endl << "-----------------" << std::endl;
    //std::cout << std::endl;
    //std::cout << (array == NULL ? "NULL" : "NOT NULL") << std::endl;
    //std::cout << "991" << std::endl;
    //std::cout << (array == NULL ? "NULL" : "NOT NULL") << std::endl;
    delete[] array;
    //std::cout << "992" << std::endl;
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
        char c = line[i];
        int ci = c - 'a';
        if(tmp -> next[ci] == NULL){
          tmp -> next[ci] = initNode();
        }
        tmp = tmp -> next[ci];
      }
      tmp -> isWord = true;
      tmp = root;
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
inline void insertWord(std::string word, WordItem **uniquewords, int *numUqWords, DcLink link)
{
    if(*numUqWords >= arraysize_uniquewords){
      //std::cout << "333" << std::endl;
      (*uniquewords) = doubleWordsArray(*uniquewords);
      //std::cout << "334" << std::endl;
    }
    //std::cout << "131" << std::endl;
    WordItem* newItem = (*uniquewords) + (*numUqWords);
    newItem -> word = word;
    newItem -> link = link;
    newItem -> count = 0;
    link -> isWord = true;
    link -> index = *numUqWords;
    (*numUqWords) ++;
    //std::cout << "132" << std::endl;
}
int optLine(std::string line, WordItem **uniquewords, int *numUqWords, char spliter, DcLink igroot, DcLink uqroot)
{
    int cnt = 0;
    DcLink igtmp = igroot;
    DcLink uqtmp = uqroot;
    line.append(" ");
    std::string word = "";
    bool isIgWord = true;;
    //std::cout << "121" << std::endl;
    for(int i = 0; i < line.length(); i ++){
      char c = line[i];
      int ci = c - 'a';
      if(c == spliter && ! word.empty()){
        if(!(isIgWord && igtmp -> isWord)){
          if(uqtmp -> isWord){
            int index = uqtmp -> index;
            (*uniquewords)[index].count ++;
          } else {
            insertWord(word, uniquewords, numUqWords, uqtmp);
          }
          cnt ++;
        }
        word = "";
        isIgWord = true;
        igtmp = igroot;
        uqtmp = uqroot;
      } else {
        if(igtmp -> next[ci] == NULL){
          isIgWord = false;
        }
        if(isIgWord){
          igtmp = igtmp -> next[ci];
        }
        if(uqtmp -> next[ci] == NULL){
          uqtmp -> next[ci] = initNode();
        }
        uqtmp = uqtmp -> next[ci];
        word = word + c;
      }
    }
    //std::cout << "122" << std::endl;
    return cnt;
}
int readText(const char *textfilename, WordItem **uniquewords, int *numUqWords, DcLink igroot, DcLink uqroot, int total)
{
    int cnt = total;
    std::string filename(textfilename);
    std::ifstream in(filename);
    if(! in.is_open()){
      return -1;
    }
    //std::cout << "117" << std::endl;
    std::string line;
    while(getline(in, line)){
      cnt = cnt + optLine(line, uniquewords, numUqWords, SPLITER, igroot, uqroot);
    }
    //std::cout << "118" << std::endl;
    in.close();
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
void printNext10(WordItem uniqueWords[], int N, int total){
    for(int i = 0; i < 10 && (i + N) < total; i ++){
      std::cout << std::fixed;
      std::cout << std::setprecision(4);
      std::cout << 1.0 * uniqueWords[i + N].count / total << " - " << uniqueWords[i + N].word << std::endl;
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
    if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL){
      std::cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" << std::endl;
      return -1;
    }
    std::string ignoreWords[ARRAYSIZE_IGNOREWORDS];
    DcLink igroot = initNode();
    getStopWords(argv[2], ignoreWords, igroot);
    // printStringArray(ignoreWords, ARRAYSIZE_IGNOREWORDS);

    //std::cout << "211" << std::endl;
    WordItem *uniquewords = new WordItem[arraysize_uniquewords];
    int totalwords, numuqwords;
    totalwords = numuqwords = 0;
    DcLink uqroot = initNode();
    totalwords = readText(argv[3], &uniquewords, &numuqwords, igroot ,uqroot, totalwords);
    //std::cout << totalwords << " : " << numuqwords << std::endl;
    //std::cout << "111" << std::endl;
    //printWordItemArray(uniquewords, numuqwords);
    arraySort(uniquewords, numuqwords);

    std::cout << "Array doubled: " << doubleTimes << std::endl;
    std::cout << "#" << std::endl;
    std::cout << "Unique non-common words: " << numuqwords << std::endl;
    std::cout << "#" << std::endl;
    std::cout << "Total non-common words: " << totalwords << std::endl;
    std::cout << "#" << std::endl;
    std::cout << "Probability of next 10 words from rank 25" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    std::string n(argv[1]);
    printNext10(uniquewords, std::stoi(n), totalwords);

    clearDc(igroot);
    igroot = NULL;
    clearDc(uqroot);
    uqroot = NULL;
    delete[] uniquewords;
    uniquewords = NULL;
    return 0;
}
