#include <iostream>
#include <random>
#include <string.h>
#include <set>

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
  cout << endl << "Usage: " << arg0 << " [-v] ( -rep | -norep ) ( -det | -rand | -mom | -monte ) <number_elements> [<i-th element>]" << endl << endl;
  cout << "      -v: Outputs information" << endl;
  cout << "      -rep: Creates a sample vector which can have repeated elements" << endl;
  cout << "      -norep: Creates a sample vector of distinct elements" << endl;
  cout << "      -det: Deterministic pivot for quickselect" << endl;
  cout << "      -rand: Random pivot for quickselect" << endl;
  cout << "      -mom: Median of medians pivot for quickselect" << endl;
  cout << "      -monte: Monte Carlo algorithm for quickselect" << endl;
  cout << endl;
  return 3;
}

// Generates a sample vector of n distinct elements
vector<int> sampleVectorDistinctValues(int n) 
{
  // Sample vector: vector of n distinct elements
  vector<int> v(n);
  // Vector of pending numbers to appear in v - For now there can appear 
  // numbers in the interval 0..2*n-1
  vector<int> pending(n);
  int i = 0;
  // Initialization of pending vector 
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
  return v;
}

// Generates a sample vector of n elements (there can be repetitions)
vector<int> sampleVectorRepeatedValues(int n) 
{
  // Sample vector: vector of n elements
  vector<int> v(n);
  int i = 0;
  // Assignment of random values to v
  while(i < v.size()) {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> rand(0,v.size()-1);   
    int r = rand(mt);
    v[i] = r;
    i++;
  }
  return v;
}

int main(int argc, char **argv)
{
  int start = 0;
  bool verbose = false;
  if(argc == 6 and not strcmp(argv[1],"-v")) {
    verbose = true; 
    start = 1;
  }
  if(strcmp(argv[start+2],"-monte") and start+4 == argc) {
    cout << "It is mandatory to specify a k for algorithms different than Monte Carlo!" << endl;
    return 3;
  }
  // k is optional for Monte Carlo, since if there is not k specified it will compute
  // the median
  int k = -1;
  if(start+4 < argc) k = stoi(argv[start+4]);
  // Number of elements in the vector
  int n = stoi(argv[start+3]);
  // k-th element we want to select
  if(k > n) {
    cout << "k must be smaller than the number of elements!" << endl;
    return 3;
  }    
  vector<int> v;
  if(not strcmp(argv[start+1],"-rep")) v = sampleVectorRepeatedValues(n);
  else if(not strcmp(argv[start+1],"-norep")) v =  sampleVectorDistinctValues(n);
  if(verbose) {
    cout << endl << "* Sample vector *" << endl << endl;
    printVector(v);
    cout << endl << "* Sorted sample vector *" << endl << endl;
    vector<int> sorted(v);
    sort(sorted.begin(),sorted.end());
    printVector(sorted);
    cout << endl;
    if(k == 1) cout << endl << "1st element : ";
    else if(k == 2) cout << endl << "2nd element : ";
    else if(k == 3) cout << endl << "3rd element : ";
    else cout << endl << k << "th element : ";
  }
  if(not strcmp(argv[start+2],"-det")) {
    QuickselectDetPivot qs;
    int result = qs.quickselect(v,0,v.size()-1,k);
    cout << result << endl << endl;
  }
  else if(not strcmp(argv[start+2],"-rand")) {
    QuickselectRandPivot qs;
    int result = qs.quickselect(v,0,v.size()-1,k);
    cout << result << endl << endl;
  }
  else if(not strcmp(argv[start+2],"-mom")) {
    QuickselectMOMPivot qs;
    int result = qs.quickselect(v,0,v.size()-1,k);
    cout << result << endl << endl;
  }
  else if(not strcmp(argv[start+2],"-monte")) {
    MonteCarlo mc;
    int result;
    if(k == -1) result = mc.selectMedian(v);
    else result = mc.selectK(v,k);
    if(result == -1) cout << "FAILED" << endl; 
    cout << result << endl << endl;
  }
}
