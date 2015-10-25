#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;


void printVector(vector<int> input) {
  for ( int i = 0; i < input.size(); i++ )
    cout << input[i] << " ";
  cout << endl;
}

// Returns the median of an unsorted vector
int median(vector<int> input) {
  sort(input.begin(),input.end());
  int n = input.size() / 2;
  return input[n];
}

int medianOfMedians(const vector<int>& input, int l, int r) {
  // 1. Divide the vector in groups of 5
  // 2. Compute the median of each group
  // 3. Return the median of all medians
  vector<int> medians;
  for(int i = l; i < r; i+=5) {
    vector<int> group;
    for(int j = i; j < i+5; j++) {
      group.push_back(input[j]);
    }
    int m = median(group);
    cout << endl << "Median " << i/5 + 1 << " : " << m << endl;
    medians.push_back(m);
  }
  return median(medians);
}

int partition(vector<int> input, int l, int r) {
  // Random device better than rand() (web en marcadores con explicacion)
  /*random_device rd;
  mt19937 mt(rd());
  uniform_real_distribution<double> rand(l, r);
  int pivot = input[rand(mt)];*/
  int pivot = medianOfMedians(input,l,r);
  while (l < r) {
    while (input[l] < pivot)
      l++;
    while (input[r] > pivot)
      r--;
    if (input[l] == input[r])
      l++;
    else if (l < r) {
      int tmp = input[l];
      input[l] = input[r];
      input[r] = tmp;
    }
  }
  return r;
}

int quick_select(vector<int> input, int l, int r, int k)
{
  if (l == r) return input[l];
  int p = partition(input,l,r);
  int length = p - l + 1;
  if (length == k) return input[p];
  else if (k < length) return quick_select(input,l,p-1,k);
  else return quick_select(input,p+1,r,k-length);
}

int main()
{
  vector<int> v(10,0);
  vector<int> pending(10);
  int i = 0;
  // Initialization of pending vector (all numbers in 0..9)
  for(int i = 0; i < pending.size(); i++) 
    pending[i] = i;
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
  cout << endl << "--- Sample vector ---" << endl;
  printVector(v);
  for(int k = 1; k <= 10; k++) {
    if(k == 1) cout << "1st element : ";
    else if(k == 2) cout << "2nd element : ";
    else if(k == 3) cout << "3rd element : ";
    else cout << k << "th element : ";
    cout << quick_select(v,0,v.size()-1,k) << endl;
  }
  cout << "Median = " << median(v) << endl;
  cout << "Median of medians = " << medianOfMedians(v,0,v.size()-1) << endl;
}
