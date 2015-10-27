#ifndef MONTECARLO 
#define MONTECARLO

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <math.h>  
#include <set>

using namespace std;

class MonteCarlo
{

public:
  
  MonteCarlo();

  int select(vector<int> input);
  
  int selectK(vector<int> input, int k);

private:

  vector<int> sampleSet(const vector<int>& input);

};

#endif
