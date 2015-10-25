#ifndef QUICKSELECT 
#define QUICKSELECT

#include <vector>
#include <iostream>

using namespace std;

class Quickselect
{

public:
  
  Quickselect();
  
  int quickselect(vector<int> input, int l, int r, int k);
  
private:
  
  int partition(vector<int> input, int l, int r);

  virtual int pivotSelection(vector<int> input, int l, int r) = 0;

};

#endif
