#include "QuickselectRandPivot.hpp"

QuickselectRandPivot::QuickselectRandPivot() {}

int QuickselectRandPivot::pivotSelection(vector<int>& input, int l, int r)
{
  // Random device better than rand() (web en marcadores con explicacion)
  random_device rd;
  mt19937 mt(rd());
  uniform_real_distribution<double> rand(l, r);
  return input[rand(mt)];  
}
