#pragma once

#ifndef SymbolTable_h
#define SymbolTable_h

#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;

class SymbolTable
{
public:
   SymbolTable();
   void addEntry(string, int);
   bool contains(string);
   int getAddress(string);
private:
   unordered_map<string, int> symbolTable;
};

#endif // SymbolTable_h