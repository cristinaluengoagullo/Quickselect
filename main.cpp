#include <iostream>
#include <random>
#include <string.h>

#include "QuickselectDetPivot.hpp"
#include "QuickselectRandPivot.hpp"
#include "QuickselectMOMPivot.hpp"
#include "MonteCarlo.hpp"

using namespace std;

void printVector(vector<int> input) {
  for ( int i = 0; i < input.size(); i++ )
    cout << input[i] << " ";
  cout << endl;
}

int showUsageMessage(const char* arg0) {
  cout << endl << "Usage: " << arg0 << "( -det | -rand | -mom | -monte ) <number_elements> <i-th element>" << endl << endl;
  cout << "      -det: Deterministic pivot" << endl;
  cout << "      -rand: Random pivot" << endl;
  cout << "      -mom: Median of medians pivot" << endl;
  cout << "      -monte: Monte Carlo algorithm" << endl;
  cout << endl;
  return 3;
}

int main(int argc, char **argv)
{
  if(argc < 4 or argc > 4) return showUsageMessage(argv[0]);
  // Number of elements in the vector
  int n = stoi(argv[2]);
  // k-th element we want to select
  int k = stoi(argv[3]);
  if(k > n) {
    cout << "k must be smaller than the number of elements!" << endl;
    return 3;
  }    
  // Sample vector: vector of n distinct elements
  vector<int> v(n);
  // Vector of pending numbers to appear in v
  vector<int> pending(2*n);
  int i = 0;
  // Initialization of pending vector (all numbers in 0..2*n-1)
  for(int i = 0; i < pending.size(); i++) 
    pending[i] = i;
  // Assignment of distinct random values to v
  while(i < v.size()) {
    int last = pending.size()-1;
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> rand(0,last);   
    int r = rand(mt);
    v[i] = pending[r];
    pending[r] = pending[last];
    pending.pop_back();
    i++;
  }
  cout << endl << "--- Sample vector ---" << endl << endl;
  printVector(v);
  cout << endl << "---------------------" << endl << endl;
  cout << endl << "--- Sorted sample vector ---" << endl << endl;
  sort(v.begin(),v.end());
  printVector(v);
  cout << endl << "---------------------" << endl << endl;
  if(k == 1) cout << "1st element : ";
  else if(k == 2) cout << "2nd element : ";
  else if(k == 3) cout << "3rd element : ";
  else cout << k << "th element : ";
  if(not strcmp(argv[1],"-det")) {
    QuickselectDetPivot qs;
    cout << qs.quickselect(v,0,v.size()-1,k) << endl << endl;
  }
  else if(not strcmp(argv[1],"-rand")) {
    QuickselectDetPivot qs;
    cout << qs.quickselect(v,0,v.size()-1,k) << endl << endl;
  }
  else if(not strcmp(argv[1],"-mom")) {
    QuickselectMOMPivot qs;
    cout << qs.quickselect(v,0,v.size()-1,k) << endl << endl;
  }
  else if(not strcmp(argv[1],"-monte")) {
    MonteCarlo mc;
    cout << mc.selectK(v,k) << endl << endl;
  }
}
