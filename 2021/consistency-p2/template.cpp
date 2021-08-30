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

using si =   std::size_t;
using i16 =  std::int16_t;  using i32 =  std::int32_t;  using i64 =  std::int64_t;
using ui16 = std::uint16_t; using ui32 = std::uint32_t; using ui64 = std::uint64_t;
using fl =   float;         using du =   double;
using ch =   char;          using st =   std::string;

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
#define sort(x) std::sort(x.begin(), x.end());
//////////////////////////////////////////////////////////////////////////////////////

__attribute__((always_inline)) inline
bool iv(char* l)
{
  switch(*l){
    case 'A': return true;
    case 'E': return true;
    case 'I': return true;
    case 'O': return true;
    case 'U': return true;
    default: return false;
  }
}


__attribute__((always_inline)) inline
bool s(st& l)
{
  sort(l);

  si c{0}, dc{0}, mc{0}, v{0}, dv{0}, mv{0};
  for(si i{0}, j{0}, z{1}, co{0}; i<l.size(); i++)
  {
    if(iv(&l[i])) z = 1;
    else z = 0;

    j = i;
    while(j < l.size() && l[j] == l[i]) ++j;
    --j;

    co = j - i + 1;
    if(z)
    {
      v += co; if(mv < co) mv = co;
    }
    else
    {
      c += co; if(mc < co) mc = co;
    }

    i = j;
  }

  dc = c - mc;
  dv = v - mv;

  if((v == 0 && dc == 0) || (c == 0 && dv == 0)) return true;
  return false;
}


__attribute__((always_inline)) inline
i32 gc(st& l, const um<ch,ve<ch>>& r)
{
  if(s(l)) return 0;

  ve<um<ch, si>> t;

  for(ch c : l)
  {
    um<ch, si> x;
    x.insert({c, 0});
    t.push_back(x);
  }

  for(si i{0}, ne{1}; i<t.size();)
  {
    for(auto& p : t[i])
    {
      if(r.find(p.first) != r.end())
      {
        for(ch c : r.at(p.first))
        {
          if(t[i].find(c) == t[i].end()) t[i].insert({c, p.second+1}), ne = 0;
          else if(t[i].at(c) > (p.second+1)) t[i].at(c) = p.second+1;
        }
      }
    }
    if(ne) ++i;
    else ne = 1;
  }

  i32 c{std::numeric_limits<i32>::max()};
  si lc{0}, max{t.size()};
  for(auto& p : t[0])
  {
    lc = p.second;
    for(si i{1}; i<max; i++)
    {
      if(t[i].find(p.first) != t[i].end()) lc += t[i].at(p.first);
      else break;

      if(i == (max-1)) c = std::min(c, static_cast<i32>(lc));
    }
  }

  if(c == std::numeric_limits<i32>::max()) return -1;
  return c;
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

  um<ch, ve<ch>> map;
  for(si i{1}; i<=lineCount; i++)
  {
    std::getline(iFile, line);
    set = line;
    
    std::getline(iFile, line);
    comboCount = std::stoi(line);

    for(si j{1}; j<=comboCount; j++)
    {
      std::getline(iFile, line);
      if(map.find(line[0]) != map.end()) map.at(line[0]).emplace_back(line[1]);
      else map.insert({line[0], {line[1]}});
    }

    auto x{gc(set, map)};
    oFile<<"Case #"<<i<<": "<<x<<'\n';
    map.clear();
  }

  iFile.close();
  oFile.close();
}

