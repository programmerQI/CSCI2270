#include <iostream>
#include <iomanip>
#include <fstream>
#define ARRAYSIZE_IGNOREWORDS 50
#define STARTSIZE_UNIQUEWORDS 100
int arraysize_uniquewords = STARTSIZE_UNIQUEWORDS;
int dtimes = 0;
struct WordItem{
    std::string word;
    int count;
    WordItem() : word(""), count(0) {}
};
WordItem* doubleArray(WordItem ori[])
{
    dtimes ++;
    int size_newarray = 2 * arraysize_uniquewords;
    WordItem* newArray = new WordItem[size_newarray];
    for(int i = 0; i < arraysize_uniquewords; i ++){
      newArray[i] = ori[i];
    }
    arraysize_uniquewords = size_newarray;
    delete [] ori;
    ori = NULL;
    return newArray;
}
int getStopWords(std::string filename, std::string ignorewords[], int size)
{
    std::ifstream in(filename);
    if(! in.is_open()){
      return -1;
    }
    int cnt = 0;
    std::string line;
    while(std::getline(in, line)){
      if(cnt >= size){
        break;
      }
      ignorewords[cnt ++] = line;
    }
    in.close();
    return cnt;
}
bool isStopWord(std::string word, std::string ignorewords[], int l)
{
    for(int i = 0; i < l; i ++){
      if(word == ignorewords[i]){
        return true;
      }
    }
    return false;
}
int isUniqueWord(std::string word, WordItem uniquewords[], int l)
{
    for(int i = 0; i < l; i ++){
      if(word == uniquewords[i].word){
        //std::cout << "221" << std::endl;
        return i;
      }
    }
    return -1;
}
int readText(std::string filename, WordItem **uniquewords, int *numuqwords, std::string ignorewords[], int numigwords)
{
    std::ifstream in(filename);
    if(! in.is_open()){
      return -1;
    }
    int total = 0;
    std::string line = "";
    while(getline(in, line)){
      std::string word = "";
      line.append(" ");
      for(int i = 0; i < line.length(); i ++){
        char c = line[i];
        if(c == ' ' && ! word.empty()){
          if(!isStopWord(word, ignorewords, numigwords)){
            int index_uqword = isUniqueWord(word, *uniquewords, *numuqwords);
            if(index_uqword != -1){
              (*uniquewords)[index_uqword].count ++;
            } else {
              if((*numuqwords) >= arraysize_uniquewords){
                *uniquewords = doubleArray(*uniquewords);
              }
              (*uniquewords)[(*numuqwords)].word = word;
              (*uniquewords)[(*numuqwords)].count ++;
              (*numuqwords) ++;
            }
            total ++;
          }
          word = "";
        } else {
          word = word + c;
        }
      }
    }
    in.close();
    return total;
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
      }
      while(i < j && uniqueWords[i].count >= pvt.count){
        i ++;
      }
      if(i < j){
        uniqueWords[j] = uniqueWords[i];
      }
    }
    uniqueWords[i] = pvt;
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
      float f = 1.0 * uniqueWords[i + N].count / total;
      std::cout << f  << " - " << uniqueWords[i + N].word << std::endl;
    }
}
int main(int argc, char *argv[])
{
    std::string n(argv[1]);
    std::string igwordsfilename(argv[3]);
    std::string txtfilename(argv[2]);

    std::string ignorewords[ARRAYSIZE_IGNOREWORDS];
    int numigwords = getStopWords(igwordsfilename, ignorewords, ARRAYSIZE_IGNOREWORDS);
    //std::cout << numigwords << std::endl;

    int total, numuqwords;
    numuqwords = 0;
    WordItem *uniquewords = new WordItem[arraysize_uniquewords];
    total = readText(txtfilename, &uniquewords, &numuqwords, ignorewords, numigwords);

    arraySort(uniquewords, numuqwords);

    std::cout << "Array doubled: " << dtimes << std::endl;
    std::cout << "#" << std::endl;
    std::cout << "Unique non-common words: " << numuqwords << std::endl;
    std::cout << "#" << std::endl;
    std::cout << "Total non-common words: " << total << std::endl;
    std::cout << "#" << std::endl;
    std::cout << "Probability of next 10 words from rank " << std::stoi(n) << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    printNext10(uniquewords, std::stoi(n), total);

    delete [] uniquewords;
    uniquewords = NULL;
    return 0;
}
