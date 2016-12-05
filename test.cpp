#include<iostream>
#include<set>
#include<vector>
#include<fstream>
#include<string>
#include<iterator>

using namespace std;

int main() {
  vector <vector<string>> h;
  vector<string> temp;
  temp.push_back("s");
  temp.push_back("r");
  h.push_back(temp);
  h.push_back(temp);
  h.push_back(temp);

  set<vector<string>> s(h.begin(), h.end());

  for(auto i = s.begin(); i != s.end(); ++i)
  for(auto ij = i->begin(); ij != i->end(); ++ij)
    cout<<*ij;

}
