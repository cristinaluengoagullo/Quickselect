#include "MonteCarlo.hpp"

MonteCarlo::MonteCarlo() {}

int MonteCarlo::selectMedian(vector<int> input)
{
  vector<int> sample = sampleSet(input);
  #ifdef DEBUG
  cout << endl << endl << "Sample: " << endl;
  for(auto s : sample) cout << s << " ";
  cout << endl;
  #endif
  sort(sample.begin(),sample.end());
  #ifdef DEBUG
  cout << endl << "Sorted sample: " << endl;
  for(auto s : sample) cout << s << " ";
  cout << endl << endl;
  #endif
  int n = input.size();
  int index = floor(0.5*pow(n,0.75) - sqrt(n));
  #ifdef DEBUG
  cout << "index d = " << index << endl;
  #endif
  if(index > 0) index--;
  else index = 0;
  int d = sample[index];
  index = ceil(0.5*pow(n,0.75) + sqrt(n)) - 1;
  if(index > sample.size()) index = sample.size()-1;
  #ifdef DEBUG
  cout << "index u = " << index << endl;
  #endif
  int u = sample[index];
  set<int> c;
  int ld = 0, lu = 0;
  for(int i = 0; i < n; i++) {
    if(input[i] >= d and input[i] <= u) c.insert(input[i]);
    if(input[i] < d) ld++;
    if(input[i] > u) lu++;
  }
  #ifdef DEBUG
  cout << "d = " << d << ", u = " << u << endl;
  cout << "ld = " << ld << ", lu = " << lu << endl;
  cout << endl << "C set: " << endl;
  for(auto s : c) cout << s << " ";
  cout << endl;
  #endif
  if(ld > float(n/2) or lu > float(n/2)) {
    #ifdef DEBUG
    cout << "Entra fail1" << endl; 
    #endif
    return -1;
  }
  if(c.size() <= 4*pow(n,0.75)) {
    set<int>::iterator it = c.begin();
    advance(it,floor(float(n/2))-ld);
    return *it;
  }
  #ifdef DEBUG
  cout << "Entra fail2" << endl;
  #endif
  return -1;
}

int MonteCarlo::selectK(vector<int> input, int k)
{
  vector<int> sample = sampleSet(input);
  #ifdef DEBUG
  cout << endl << endl << "Sample: " << endl;
  for(auto s : sample) cout << s << " ";
  cout << endl;
  #endif
  sort(sample.begin(),sample.end());
  #ifdef DEBUG
  cout << endl << "Sorted sample: " << endl;
  for(auto s : sample) cout << s << " ";
  cout << endl << endl;
  #endif
  int n = input.size();
  int index = floor(float(k/n)*pow(n,0.75) - sqrt(n));
  if(index > 0) index--;
  else index = 0;
  #ifdef DEBUG
  cout << "n = " << n << endl;
  cout << "index d = " << index << endl;
  #endif
  int d = sample[index];
  index = ceil((float(n-k)/n)*pow(n,0.75) + sqrt(n)) - 1;
  if(index > sample.size()) index = sample.size()-1;
  #ifdef DEBUG
  cout << "index u = " << index << endl;
  #endif
  int u = sample[index];
  set<int> c;
  int ld = 0, lu = 0;
  for(int i = 0; i < n; i++) {
    if(input[i] >= d and input[i] <= u) c.insert(input[i]);
    else if(input[i] < d) ld++;
    else if(input[i] > u) lu++;
  }
  #ifdef DEBUG
  cout << "d = " << d << ", u = " << u << endl;
  cout << "ld = " << ld << ", lu = " << lu << endl;
  cout << endl << "C set: " << endl;
  for(auto s : c) cout << s << " ";
  cout << endl;
  #endif
  if(ld >= k or lu > n-k) {
    #ifdef DEBUG
    cout << "Entra fail1" << endl; 
    #endif
    return -1;}
  if(c.size() <= 4*pow(n,0.75)) {
    set<int>::iterator it = c.begin();
    int index = k - ld;
    #ifdef DEBUG
    cout << endl << "k = " << k << endl;
    cout << "index c = " << index << endl;
    cout << (index == k) << endl;
    #endif
    if(index <= 0) index = k - 1;
    else index--;
    #ifdef DEBUG
    cout << "new index = " << index << endl;
    #endif
    advance(it,index);
    return *it;
  }
  #ifdef DEBUG
  cout << "Entra fail2" << endl;
  #endif
  return -1;
}

vector<int> MonteCarlo::sampleSet(const vector<int>& input) 
{
  vector<int> sample;
  int n = ceil(pow(input.size(),0.75));  
  while(sample.size() < n) {
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> rand(0,input.size()-1);
    sample.push_back(input[rand(mt)]);  
  }
  return sample;
}
