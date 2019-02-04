#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <limits>
#include <tuple>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <string>
#include <fstream>

using namespace std;
typedef long long ll;
typedef unsigned int uint;
using vi = vector<int>;
using vii = vector<vector<int>>;
using pii = pair<int,int>;
template <class T>
void print(vector<T> v){ bool first=true; for(T x : v) { if(!first) cout << " "; first = false; cout << x; } cout << endl;}

template <class T>
void print2(vector<T>& v, T w){ bool first=true; for(T x : v) { if(!first) cout << " "; first = false; cout << x; } cout << " (" << w << ")"; cout << endl;}
vii getNeighbors(vi& curr, vi& weights, vi& I, vi& num){
  vii ans;
  int S=0;
  for(int i=0; i<curr.size(); i++){
    S += curr[i]*weights[i];
  }
  for(int i=0; i<curr.size(); i++){
    if(curr[i] > 0 && S-weights[i] >= I[0]){
      vi nxt(curr);
      nxt[i]--;
      ans.push_back(nxt);
    }
    if(num[i]-curr[i] > 0 && S+weights[i] <= I[1]){
      vi nxt(curr);
      nxt[i]++;
      ans.push_back(nxt);
    } 
  }
  return ans;
}
int k=17;
// vi num = {2*k-1, 2*k, 2*k, 0};
// vi weight = {2*k-1, 2*k,2,250};
// vi I = {(2*k-1)*(2*k), 4*k*k};
// vi start={2*k,0,0,0};
// vi goal = {0,2*k-1,0,0};
// vi num = {5*k, 5*k-1, 5*k-2, 0};
// vi weight = {3*k, 3*k-1, 3*k-2, 3};
// vi I = {(3*k-2)*(3*k), (3*k-1)*(3*k)};
// vi start={3*k-2,0,0,0};
// vi goal = {0,0,3*k,0};
vi num = {(3*k)/2+10, (3*k)/2+10, 2*k+20, 2*k+20};
vi weight = {(3*k)/2+1, (3*k)/2+2, k-1, k+1};
vi start={weight[1],0,weight[3],0};
vi goal = {0,weight[0],0,weight[2]};
vi I = {weight[1]*weight[0]+weight[2]*weight[3], weight[1]*weight[0]+weight[2]*weight[3]+weight[1]};
map<ll,bool> visited;
int totalNum = num[0]+num[1]+num[2]+num[3];
map<ll,ll> parent;
ll makeNumeric(vector<int>& curr){
  ll b=1;
  ll ans=0;
  for(int i=0; i<curr.size(); i++){
    ans += ll(curr[i])*b;
    b *= totalNum;
  }
  return ans;
}
bool isVisited(vi& curr){
  ll p = makeNumeric(curr);
  return visited.find(p) != visited.end() && visited[p];
  //return visited[curr[0]][curr[1]][curr[2]][curr[3]];
}
void visit(vi& curr){
  ll p = makeNumeric(curr);
  visited[p] = true;
}


vector<int> restore(int l, ll n){
  vi ans(l,0);
  for(int i=0; i<l; i++){
    int m = (n % totalNum);
    ans[i] = m;
    n = (n-ll(m))/ll(totalNum);
  }
  return ans;
}

void assignParent(vi& v, vi& w){
  parent[makeNumeric(v)] = makeNumeric(w);
}
int getWeight(vi& curr){
  int S=0;
  for(int i=0; i<curr.size(); i++){
    S += curr[i]*weight[i];
  }
  return S;
}

int shortestPath(){
  queue<pair<vi,int>> q;
  q.push(make_pair(start,0));
  visit(start);
  while(!q.empty()){
    auto wn = q.front();
    auto w = wn.first;
    auto n = wn.second;
    q.pop(); 
    if(w == goal){
      return n;
    }
    for(auto v : getNeighbors(w, weight, I, num)){
      if(!isVisited(v)){
        visit(v);
        assignParent(v,w);
        q.push(make_pair(v, n+1));
      }
    }
  }
  return -1;
}

int n_max = 50;
int getRand(){
  return rand() % n_max;
}

void randShortest(){
  int N=1000000;
  srand(time(NULL));
  for(int w=0; w<N; w++){
    if(w % 100 == 0)
      cout << "Test " << w <<"(" << totalNum << ")"<< endl;
    visited = map<ll, bool>();
    num = {getRand()+1, getRand()+1, getRand()+1, getRand()+1};
    weight = {getRand()+1, getRand()+1, getRand()+1, getRand()+1};
    start={getRand() % num[0],getRand() % num[1],getRand() % num[2],getRand() % num[3]};
    goal={getRand() % num[0],getRand() % num[1],getRand() % num[2],getRand() % num[3]};
    int startWeight = start[0]*weight[0]+start[1]*weight[1]+start[2]*weight[2]+start[3]*weight[3];
    int endWeight = goal[0]*weight[0]+goal[1]*weight[1]+goal[2]*weight[2]+goal[3]*weight[3];
    while(abs(endWeight-startWeight) > 30){
      goal={getRand() % num[0],getRand() % num[1],getRand() % num[2],getRand() % num[3]};
      startWeight = start[0]*weight[0]+start[1]*weight[1]+start[2]*weight[2]+start[3]*weight[3];
      endWeight = goal[0]*weight[0]+goal[1]*weight[1]+goal[2]*weight[2]+goal[3]*weight[3];
    }
    I = {min(startWeight,endWeight)-(getRand()) % (startWeight+1) , max(startWeight, endWeight)+(getRand() % (endWeight+1))};
    totalNum = num[0]+num[1]+num[2]+num[3];
    int m = shortestPath();
    //cout << m << endl;
    if(m != -1 && m > 4*totalNum){
      cout << m << "(" << totalNum << ")" << endl;
      print(num);
      print(weight);
      print(start);
      print(goal);
      print(I);
      cout<<"-------"<<endl;
      vector<int> path;
      int curr = makeNumeric(goal);
      path.push_back(curr);
      while(curr != makeNumeric(start)){
        curr = parent[curr];
        path.push_back(curr);
      }
      reverse(path.begin(), path.end());
      for(auto v : path){
        print(restore(4,v));
      }
    }
  }
}

void detShortest(){
  int m = shortestPath();
  cout << m << endl;
    
  vector<int> path;
  int curr = makeNumeric(goal);
  path.push_back(curr);
  while(curr != makeNumeric(start)){
    curr = parent[curr];
    path.push_back(curr);
  }
  reverse(path.begin(), path.end());
  for(auto v : path){
    auto c=restore(start.size(),v);
    print2(c, getWeight(c));
  }
}

void play(){
  cout << "weights: ";
  cin >> weight[0] >> weight[1] >> weight[2] >> weight[3];
  cout << "start: ";
  cin >> start[0] >> start[1] >> start[2] >> start[3];
  cout << "num: ";
  cin >> num[0] >> num[1] >> num[2] >> num[3];
  cout << "I: ";
  cin >> I[0] >> I[1];
  while(true){
    int t,m;
    int W = getWeight(start);
    print2(start, W);
    cout << "Move: ";
    cin >> t >> m;
    if(t == 0 && start[m] > 0 && W-weight[m] >= I[0]){
      start[m]--;
    }else if(t == 1 && num[m]-start[m] > 0 && W+weight[m] <= I[1]){
      start[m]++;
    } else{
      cout << "Invalid move" << endl;
    }
  }
}

int main(int argc, char** argv){
  if(argc > 1 && strcmp(argv[1],"-rand") == 0){
    randShortest();
  }else if(argc > 1 && strcmp(argv[1],"-play") == 0){
    play();
  }
  else{
    if(argc > 1 && strcmp(argv[1],"-input") == 0){
      int n_bins;
      cout << "n_bins: ";
      cin >> n_bins;
      cout << "weights: ";
      weight = vector<int>(n_bins);
      start = vector<int>(n_bins);
      goal = vector<int>(n_bins);
      num = vector<int>(n_bins);
      for(int i=0; i<n_bins;i++)
        cin >> weight[i];
      cout << "start: ";
      for(int i=0; i<n_bins;i++)
        cin >> start[i];
      cout << "goal: ";
      for(int i=0; i<n_bins;i++)
        cin >> goal[i];
      cout << "num: ";
      for(int i=0; i<n_bins;i++)
        cin >> num[i];
      cout << "I: ";
      cin >> I[0] >> I[1];
      cout << endl;
      totalNum = 0;
      for(int i=0; i<num.size(); i++)
        totalNum += num[i];
    }
    detShortest();
  }
  return 0;
}
