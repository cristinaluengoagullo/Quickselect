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

int showUsageMessage(const char* arg0) {
  cout << endl << "Usage: " << arg0 << " [-wc] <number_elements>" << endl << endl;
  cout << "      -wc: Performs worst-case tests" << endl;
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

// Generates a sorted sample vector of n distinct elements
vector<int> sampleSortedVector(int n) {
  vector<int> v(n);
  for(int i = 0; i < n; i++)
    v[i] = i;
  return v;
}

// n 
int main(int argc, char **argv)
{
  const int NUM_ITERATIONS = 5;
  int start = 0;
  bool worstCase = false;
  if(argc > 3) showUsageMessage(argv[0]);
  if(argc == 3) {
    if(not strcmp(argv[1],"-wc")) worstCase = true;
    start++;
  } 
  // Number of elements in the vector
  int n = stoi(argv[start+1]);
  cout << endl << "************************************" << endl;
  cout << "********** Length = " << n << " **********" << endl;
  cout << "************************************" << endl << endl;
  // k we want to select
  int k = n/2;   
  vector<int> v;
  if(not worstCase) v = sampleVectorDistinctValues(n);
  else v = sampleSortedVector(n);
  float sumDet = 0, sumRand = 0, sumMOM = 0, sumMonte = 0;
  for(int i = 0; i < NUM_ITERATIONS; i++) {

    cout << "*** Quickselect deterministic pivot ***" << endl;
    QuickselectDetPivot qs1;
    vector<int> v1(v); 
    auto begin = std::chrono::high_resolution_clock::now();
    int result = qs1.quickselect(v1,0,v1.size()-1,k);
    cout << result << endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() * pow(10,-6));
    cout << std::fixed << duration << endl;
    sumDet += duration;

    if(not worstCase) {
      cout << endl << "*** Quickselect random pivot ***" << endl;
      QuickselectRandPivot qs2;
      vector<int> v2(v);
      begin = std::chrono::high_resolution_clock::now();
      result = qs2.quickselect(v2,0,v2.size()-1,k);
      cout << result << endl;
      end = std::chrono::high_resolution_clock::now();
      duration = (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() * pow(10,-6));
      cout << std::fixed << duration << endl;
      sumRand += duration;
    }

    cout << endl << "*** Quickselect MOM pivot ***" << endl;
    QuickselectMOMPivot qs3;
    vector<int> v3(v);
    begin = std::chrono::high_resolution_clock::now();
    result = qs3.quickselect(v3,0,v3.size()-1,k);
    cout << result << endl;
    end = std::chrono::high_resolution_clock::now();
    duration = (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() * pow(10,-6));
    cout << std::fixed << duration << endl;
    sumMOM += duration;

    cout << endl <<"*** Monte Carlo ***" << endl;
    MonteCarlo mc;
    vector<int> v4(v);
    begin = std::chrono::high_resolution_clock::now();
    result = mc.selectMedian(v4);
    if(result == -1) cout << "FAILED" << endl; 
    cout << result << endl;
    end = std::chrono::high_resolution_clock::now();
    duration = (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() * pow(10,-6));
    if(result != -1) cout << std::fixed << duration << endl << endl;
    sumMonte += duration;
  }
  cout << endl << "** Average running times **" << endl << endl;
  cout << float(sumDet)/NUM_ITERATIONS << endl;
  if(not worstCase) cout << float(sumRand)/NUM_ITERATIONS << endl;
  cout << float(sumMOM)/NUM_ITERATIONS << endl;
  cout << float(sumMonte)/NUM_ITERATIONS << endl << endl;
  cout << "******* END Length " << n << " *******" << endl;
}
