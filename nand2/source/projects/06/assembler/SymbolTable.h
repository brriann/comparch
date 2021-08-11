#pragma once

#ifndef SymbolTable_h
#define SymbolTable_h

#include <string>

using std::string;

class SymbolTable
{
public:
   SymbolTable();
   void addEntry(string, int);
   bool contains(string);
   int getAddress(string);
private:
   int myPrivateInt; // placeholder
};

#endif // SymbolTable_h