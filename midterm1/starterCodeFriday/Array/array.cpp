#include<iostream>
#include<string>
using namespace std;

/*
// Split 'arr' into 'even_arr' & 'odd_arr'
//  - 'arr': pointer to original array
//  - 'even_arr': pointer to even array
//  - 'odd_arr': pointer to odd array
*/
void split(int* &arr, int* &even_arr, int* &odd_arr, int size, int &even_size, int &odd_size)
{
	//Implement this function
  even_size = 0;
  odd_size = 0;
  for(int i = 0; i < size; i ++){
    if(arr[i] % 2 == 0){
      even_arr[even_size ++];
    } else {
      odd_arr[odd_size ++];
    }
  }
  if(even_size == 0){
    even_arr = NULL;
  }
  if(odd_size == 0){
    odd_arr = NULL;
  }
}

void printArray(int* arr, int size) {
    for(int i = 0; i<size; i++)
    {
        cout<< arr[i];
        if(i < size-1)
          cout << ", ";
    }
    cout<<endl;
}

int main(int argc, char* argv[])
{
    if(argc<2)
    {
      cout<<"usage: a.out <#>";
      return -1;
    }

	// Create input array:
    int size = stoi(argv[1]);
    int *arr = new int[size];

    cout<< "original array: ";
    for(int i = 0; i<size; i++)
    {
        arr[i] = rand()%100;
        cout<< arr[i];
        if(i < size-1)
          cout << ", ";
    }
    cout<<endl;

	// Call your function with new arrays:
	//split();
  int even[size], odd[size];
  int e, o;
  split(arr, even, odd, size, e, o);
	// Output
  cout<< "original array: ";
  for(int i = 0; i<e; i++)
  {
      even[i] = rand()%100;
      cout<< even[i];
      if(i < size-1)
        cout << ", ";
  }
  cout<<endl;
  cout<< "original array: ";
  for(int i = 0; i<o; i++)
  {
      odd[i] = rand()%100;
      cout<< odd[i];
      if(i < size-1)
        cout << ", ";
  }
  cout<<endl;
	// Clean up (delete)
  delete [] arr;
  delete [] even;
  delete [] odd;
    return 0;
}
