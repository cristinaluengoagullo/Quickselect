#include <iostream>
#include <random>
#include <string.h>
#include <time.h>
#include <chrono>
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
  cout << endl << "Usage: " << arg0 << "[-v] ( -rep | -norep ) ( -det | -rand | -mom | -monte ) <number_elements> <i-th element>" << endl << endl;
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
  vector<int> pending(2*n);
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

set<int> sampleKs(int n) 
{
  set<int> ks;
  int nSqrt = sqrt(n);
  ks.insert(n/2);
  int i = nSqrt;
  while(i < (n-nSqrt)) {
    ks.insert(i);
    i += (float(1)/10*(n-2*nSqrt));
  }
  return ks;
}

int main(int argc, char **argv)
{
  if(argc < 5 or argc > 6) return showUsageMessage(argv[0]);
  int start = 0;
  bool verbose = false;
  if(argc == 6 and not strcmp(argv[1],"-v")) {
    verbose = true; 
    start = 1;
  }
  // Number of elements in the vector
  int n = stoi(argv[start+3]);
  // k-th element we want to select
  int k = stoi(argv[start+4]);
  if(k > n) {
    cout << "k must be smaller than the number of elements!" << endl;
    return 3;
  }    
  vector<int> v;
  set<int> ks;
  if(not strcmp(argv[start+1],"-rep")) v = sampleVectorRepeatedValues(n);
  else if(not strcmp(argv[start+1],"-norep")) v =  sampleVectorDistinctValues(n);
  ks = sampleKs(v.size());
  if(verbose) {
    cout << endl << "* Sample vector *" << endl << endl;
    printVector(v);
    cout << endl << "* Sorted sample vector *" << endl << endl;
    sort(v.begin(),v.end());
    printVector(v);
    cout << endl;
    cout << "* Sample Ks *" << endl;
    for(auto k : ks) cout << k << " ";
    cout << endl;
    if(k == 1) cout << endl << "1st element : ";
    else if(k == 2) cout << endl << "2nd element : ";
    else if(k == 3) cout << endl << "3rd element : ";
    else cout << endl << k << "th element : ";
  }
  int result;
  if(not strcmp(argv[start+2],"-det")) {
    QuickselectDetPivot qs;
    auto begin = std::chrono::high_resolution_clock::now();
    result = qs.quickselect(v,0,v.size()-1,k);
    if(verbose) cout << result  << endl << endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end-begin).count();
    cout << std::fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() * pow(10,-6)) << endl;
  }
  else if(not strcmp(argv[start+2],"-rand")) {
    QuickselectDetPivot qs;
    auto begin = std::chrono::high_resolution_clock::now();
    result = qs.quickselect(v,0,v.size()-1,k);
    if(verbose) cout << result << endl << endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end-begin).count();
    cout << std::fixed << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << endl;
  }
  else if(not strcmp(argv[start+2],"-mom")) {
    QuickselectMOMPivot qs;
    auto begin = std::chrono::high_resolution_clock::now();
    result = qs.quickselect(v,0,v.size()-1,k);
    if(verbose) cout << result << endl << endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end-begin).count();
    cout << std::fixed << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << endl;
  }
  else if(not strcmp(argv[start+2],"-monte")) {
    MonteCarlo mc;
    auto begin = std::chrono::high_resolution_clock::now();
    result = mc.selectK(v,k);
    if(result == -1) cout << "FAILED" << endl; 
    if(verbose) cout << result << endl << endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end-begin).count();
    cout << std::fixed << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << endl;
  }
}
