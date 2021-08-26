// constructing priority queues
#include <iostream>       // std::cout
#include <string>          // std::priority_queue
#include <map>         // std::vector
#include <functional>     // std::greater

class mycomparison
{
  bool reverse;
public:
  mycomparison(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const int& lhs, const int&rhs) const
  {
    if (reverse) return (lhs>rhs);
    else return (lhs<rhs);
  }
};

template<typename T>
void printf_queue(T value){
	auto iter = value.begin();
	
}

int main ()
{
  std::map<int, int> first;
  first[0x1] = 0x1;
  first[0x4] = 0x4;
  first[0x3] = 0x3;
  first[0x6] = 0x6;
  first[0x5] = 0x5;
  first[0x11] = 0x11;
  first[0x13] = 0x13;
  first[0x14] = 0x14;
  for(auto item = first.begin(); item != first.end() ; ++item){
	std::cout<< item->first << ":" << item->second << std::endl;
  }
  
  std::cout << std::endl << "reversed:" << std::endl << std::endl;
  for(auto item = first.rbegin(); item != first.rend() ; ++item){
	std::cout<< item->first << ":" << item->second << std::endl;
  }
  
  return 0;
}