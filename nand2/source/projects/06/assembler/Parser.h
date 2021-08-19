#pragma once

#ifndef Parser_h
#define Parser_h

#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::string;
using std::vector;

enum class CommandType { A_COMMAND, C_COMMAND, L_COMMAND };

class Parser
{
public:
   Parser(ifstream&);
   bool hasMoreCommands();
   void advance();
   CommandType commandType();
   CommandType commandType(string);
   string symbol();
   string symbol(string);
   string dest();
   string dest(string);
   string comp();
   string comp(string);
   string jump();
   string jump(string);
   void incrementCommandCount();
   int getCommandCount();
   void incrementNextMemoryAddress();
   int getNextMemoryAddress();
   void closeInputFile();
   vector<string>::iterator commandListBegin();
   vector<string>::iterator commandListEnd();
private:
   int nextMemoryAddress;
   int commandCount;
   vector<string> commandList;
   string currentCommand;
   CommandType currentCommandType;
   ifstream& inputFile;
};

#endif // Parser_h