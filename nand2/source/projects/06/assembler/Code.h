#pragma once

#ifndef Code_h
#define Code_h

#include <string>
#include <bitset>
#include <map>

using std::string;
using std::bitset;
using std::map;

static class Code
{
public:
   static string dest(string);
   static string comp(string);
   static string jump(string);
   static bitset<16> fullInstrC(string, string, string);
   static bitset<16> fullInstrA(string);
private:
   static map<string, string> destMap;
   static map<string, string> compMap;
   static map<string, string> jumpMap;
};

#endif // Code_h