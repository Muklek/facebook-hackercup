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

#define p1d(x)  for(auto y : *x) std::cout<<y<<' ';
#define p2d(x)  for(auto& y : *x) std::cout<<'\n', for(auto z : y) std::cout<<z<< ' ';
#define pm(x)   for(auto& y : *x) std::cout<<y.first<<'  '<<y.second<<'\n';
#define sort(x) std::sort(x->begin(), x->end());
//////////////////////////////////////////////////////////////////////////////////////

__attribute__((always_inline)) inline
std::pair<si,si> gc(const ve<st>& b)
{
  si const mrow{b.size()};
  si const mcol{b[0].size()};

  os<si> row, col;
  for(si r{0}; r<mrow; r++)
  {
    for(si c{0}; c<mcol; c++)
    {
      if(b[r][c] == 'O' && row.find(r) == row.end())
        row.insert(r);
      if(b[r][c] == 'O' && col.find(c) == col.end())
        col.insert(c);
    }
  }

  um<si,si> xrow, xcol;
  for(si r{0}; r<mrow; r++)
  {
    for(si c{0}; c<mcol; c++)
    {
      if(b[r][c] == 'X')
      {
        if(xrow.find(r) == xrow.end()) xrow.insert({r, 1});
        else xrow.at(r) += 1;

        if(xcol.find(c) == xcol.end()) xcol.insert({c, 1});
        else xcol.at(c) += 1;
      }
    }
  }

  um<si, si> t;
  um<si,si> ut;
  for(si r{0}, c{0}, x{0}; r<mrow; r++, c=0)
  {
    if(row.find(r) == row.end())
    {
      if(xrow.find(r) != xrow.end()) x = mrow - xrow.at(r);
      else x = mrow;

      if(x == 1)
      {
        while(c < mcol && b[r][c] == 'X') ++c;
        ut.insert({r, c});
      }

      if(t.find(x) != t.end()) t.at(x) +=1;
      else t.insert({x, 1});
    }
  }
  for(si c{0}, r{0}, x{0}, inc{true}; c<mcol; c++, r=0, inc=true)
  {
    if(col.find(c) == col.end())
    {
      if(xcol.find(c) != xcol.end()) x = mcol - xcol.at(c);
      else x = mcol;

      if(x == 1)
      {
        while(r < mrow && b[r][c] == 'X') ++r;
        if(ut.find(r) != ut.end() && ut.at(r) == c) inc = false;
      }

      if(inc && t.find(x) != t.end()) t.at(x) += 1;
      else if(inc) t.insert({x, 1});
    }
  }

  si mcount{std::numeric_limits<si>::max()};
  si mpos{std::numeric_limits<si>::max()};
  if(t.size() == 0) return std::make_pair(mcount, mpos);
  for(auto& x : t) if(x.first < mcount) mcount = x.first, mpos = x.second;

  return std::make_pair(mcount, mpos);
}





int main()
{
  std::ios::sync_with_stdio(0), std::cin.tie(0);

  std::fstream iFile;
  std::fstream oFile;
  iFile.open("./input.txt");
  oFile.open("./output.txt");

  std::string line{""};
  int lineCount{0}, boardCount{0}, boardSize{0};

  std::getline(iFile, line);

  boardCount = std::stoi(line);

  ve<st> board;
  for(si i{1}; i<=boardCount; i++)
  {
    std::getline(iFile,line);
    boardSize = std::stoi(line);

    for(si j{1}; j<=boardSize; j++)
    {
      std::getline(iFile,line);
      board.emplace_back(line);
    }
    auto x{gc(board)};

    oFile<<"Case #"<<i<<":"<<" ";
    if(x.first == std::numeric_limits<si>::max()) oFile<<"Impossible"<<'\n';
    else oFile<<x.first<<" "<<x.second<<'\n';

    board.clear();
  }

  iFile.close();
  oFile.close();
}


