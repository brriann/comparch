#pragma once

#ifndef Parser_h
#define Parser_h

#include <fstream>
#include <string>

using std::ifstream;
using std::string;

enum class CommandType { A_COMMAND, C_COMMAND, L_COMMAND };

class Parser
{
public:
   Parser(ifstream&);
   bool hasMoreCommands();
   void advance();
   CommandType commandType();
   string symbol();
   string dest();
   string comp();
   string jump();
private:
   string currentCommand;
   string nextCommand;
   ifstream& inputFile;
};

#endif // Parser_h