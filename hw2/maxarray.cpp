#include<iostream>
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
int main()
{
    WordItem *ary = new WordItem[12800];
    return 0;
}
