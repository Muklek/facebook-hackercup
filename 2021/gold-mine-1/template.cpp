#include<iostream>
#include<string>
#include<string_view>
#include<array>
#include<vector>
#include<deque>
#include<list>
#include<unordered_map>
#include<map>
#include<unordered_set>
#include<set>
#include<algorithm>
#include<functional>
#include<memory>
#include<fstream>
#include<iterator>
#include<sstream>

using si =   std::size_t;
using i16 =  std::int16_t;  using i32 =  std::int32_t;  using i64 =  std::int64_t;
using ui16 = std::uint16_t; using ui32 = std::uint32_t; using ui64 = std::uint64_t;
using fl =   float;         using du =   double;
using ch =   char;          using st =   std::string;

template<typename T1, typename T2>  using pa = std::pair<T1,T2>;
template<typename T, std::size_t S> using ar = std::array<T,S>;
template<typename T>                using ve = std::vector<T>;
template<typename T>                using de = std::deque<T>;
template<typename T>                using li = std::list<T>;
template<typename K, typename V>    using um = std::unordered_map<K,V>;
template<typename K, typename V>    using om = std::map<K,V>;
template<typename T>                using us = std::unordered_set<T>;
template<typename T>                using os = std::set<T>;

#define pb push_back;
#define eb emplace_back;
#define br '\n';

#define p1d(x)  for(auto y : x) std::cout<<y<<' ';
#define p2d(x)  for(auto y : x) std::cout<<'\n', for(auto z : y) std::cout<<z<< ' ';
#define pm(x)   for(auto y : x) std::cout<<y.first<<'  '<<y.second<<'\n';
//#define sort(x) std::sort(x.begin(), x.end());
//////////////////////////////////////////////////////////////////////////////////////

__attribute__((always_inline)) inline
si gc(um<si, ve<si>> m, ve<si> g)
{
  ve<ve<si>> t{{0,1,1}};

  for(si i{0}, v{0}; i<t.size(); i++)
  {
    v = t[i][t[i].size()-1];
    if(m.find(v) != m.end())
    {
      for(si ch : m.at(v))
      {
        auto s{std::find(t[i].begin()+2, t[i].end(), ch)};
        if(s == std::end(t[i]))
        {
          ve<si> temp{0,1};
          temp[0] += t[i][0];
          temp[0] += g[ch-1];

          std::copy(t[i].begin()+2, t[i].end(),
                    std::back_inserter(temp));
          temp.emplace_back(ch);
          t.push_back(temp);
        }
      }
    }
  }


  std::sort(t.begin(), t.end(),
      [&](auto& va, auto& vb){return va[0] < vb[0];});

  si gold{0}, e{0};
  um<si, si> rp;
  for(si i{t.size()-1}; i > 1; i--)
  {
    for(si j{2}; j<t[i].size()-1; j++)
      rp.insert({t[i][j], t[i][j+1]});

    for(si k{t.size()-1}; k > 1; k--)
    {
      for(si l{2}; l<t[k].size()-1; l++)
      {
        if(rp.find(t[k][l]) != rp.end() &&
           rp.at(t[k][l]) == t[k][l+1])
          break;

        if(l == t[k].size()-2 && (t[i][0] + t[k][0]) > e)
          e = t[i][0] + t[k][0];
      }
    }
    rp.clear();
  }

  if(e == 0 && t.size() > 1) gold = g[0] + t[t.size()-1][0];
  else if(e != 0) gold = g[0] + e;
  else gold = g[0];

  return gold;
}



int main()
{
  std::ios::sync_with_stdio(0), std::cin.tie(0);

  std::fstream iFile;
  std::fstream oFile;
  iFile.open("./input.txt");
  oFile.open("./output.txt");

  std::string line{""};
  std::string set{""};
  si lineCount{0}, comboCount{0};

  std::getline(iFile, line);

  lineCount = std::stoi(line);

  um<si, ve<si>> map;
  ve<si> gmap;
  for(si i{1}; i<=lineCount; i++)
  {
    std::getline(iFile, line);
    comboCount = std::stoi(line);
    for(si j{1}; j<=comboCount; j++)
    {
      std::getline(iFile, line);
      std::istringstream ss(line);

      if(j == 1)
      {
        while(std::getline(ss, set, ' '))
          gmap.emplace_back(std::stoi(set));
      }
      else
      {
        si p{0}, c{0}, count{1};

        while(std::getline(ss, set, ' '))
        {
          if(count==1) p = std::stoi(set), ++count;
          else c = std::stoi(set);
        }
        
        if(map.find(p) != map.end()) map.at(p).emplace_back(c);
        else map.insert({p, {c}});

        if(map.find(c) != map.end()) map.at(c).emplace_back(p);
        else map.insert({c, {p}});
      }
    }
    auto x{gc(map, gmap)};
    oFile<<"Case #"<<i<<": "<<x<<'\n';

    map.clear();
    gmap.clear();
  }

  iFile.close();
  oFile.close();
}

