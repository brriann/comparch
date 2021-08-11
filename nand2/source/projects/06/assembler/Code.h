#pragma once

#ifndef Code_h
#define Code_h

#include <string>
#include <bitset>

using std::string;
using std::bitset;

static class Code
{
public:
   static bitset<3> dest(string);
   static bitset<7> comp(string);
   static bitset<3> jump(string);
private:
   int myPrivateInt; // placeholder
};

#endif // Code_h