#include "Parser.h"

#include <fstream>
#include <string>
#include <algorithm>

using std::ifstream;
using std::string;

const char EQUALS_CHAR = '=';
const char SEMICOLON_CHAR = ';';
const char COMMENT_LEADING_CHAR = '/';

const string NULL_STRING = "null";

const int FIRST_MEMORY_ADDRESS = 16;

// http://cplusplus.com/forum/beginner/251052/
std::string trim(const std::string& line)
{
   const char* WhiteSpace = " \t\v\r\n";
   std::size_t start = line.find_first_not_of(WhiteSpace);
   std::size_t end = line.find_last_not_of(WhiteSpace);
   return start == end ? std::string() : line.substr(start, end - start + 1);
}


Parser::Parser(ifstream& inputFileCtr) : inputFile(inputFileCtr)
{
   currentCommandType = CommandType::A_COMMAND;
   commandCount = 0;
   nextMemoryAddress = FIRST_MEMORY_ADDRESS;
}

bool Parser::hasMoreCommands()
{
   return getline(inputFile, currentCommand) || !inputFile.eof();
}

void Parser::advance()
{
   //TODO, handle comments
   while (currentCommand.empty() || currentCommand.at(0) == COMMENT_LEADING_CHAR)
   {
      getline(inputFile, currentCommand);
   }
   // trim trailing comment
   currentCommand = currentCommand.substr(0, currentCommand.find(COMMENT_LEADING_CHAR));
   // trim left+right whitespace
   currentCommand = trim(currentCommand);
   commandList.push_back(currentCommand);
}

CommandType commandTypeHelper(string command)
{
   CommandType commandType;
   char firstCharOfLine = command.at(0);

   switch (firstCharOfLine)
   {
      // (symbol)
      case '(':
         commandType = CommandType::L_COMMAND;
         break;
         // @symbol or @15
      case '@':
         commandType = CommandType::A_COMMAND;
         break;
         // dest=comp;jump
      default:
         commandType = CommandType::C_COMMAND;
         break;
   }
   return commandType;
}

CommandType Parser::commandType()
{
   CommandType commandType = commandTypeHelper(currentCommand);
   currentCommandType = commandType;
   return commandType;
}
CommandType Parser::commandType(string command)
{
   CommandType commandType = commandTypeHelper(command);
   currentCommandType = commandType;
   return commandType;
}

string symbolHelper(string command, CommandType commandType)
{
   string symbol;
   switch (commandType)
   {
      // @xxx
      case CommandType::A_COMMAND:
         symbol = command.substr(1, string::npos);
         break;
         // (xxx)
      case CommandType::L_COMMAND:
         symbol = command.substr(1, command.length() - 2);
         break;
         // invalid case - debug statement
      default:
         symbol = "invalidSymbolReturn";
         break;
   }
   return symbol;
}

string Parser::symbol()
{
   return symbolHelper(currentCommand, currentCommandType);
}

string Parser::symbol(string command)
{
   return symbolHelper(command, currentCommandType);
}

string destHelper(string command)
{
   // comp;jump
   if (command.find(EQUALS_CHAR) == string::npos)
   {
      return NULL_STRING;
   }
   return command.substr(0, command.find(EQUALS_CHAR));
}

string Parser::dest()
{
   return destHelper(currentCommand);
}

string Parser::dest(string command)
{
   return destHelper(command);
}

string compHelper(string command)
{
   if (command.find(EQUALS_CHAR) == string::npos)
   {
      return command.substr(0, command.find(SEMICOLON_CHAR));
   }
   else
   {
      if (command.find(SEMICOLON_CHAR) == string::npos)
      {
         return command.substr(command.find(EQUALS_CHAR) + 1,
            string::npos);
      }
      else
      {
         return command.substr(command.find(EQUALS_CHAR) + 1,
            command.find(SEMICOLON_CHAR) - (command.find(EQUALS_CHAR) + 1));
      }
   }
}

string Parser::comp()
{
   return compHelper(currentCommand);
}

string Parser::comp(string command)
{
   return compHelper(command);
}

string jumpHelper(string command)
{
   if (command.find(SEMICOLON_CHAR) == string::npos)
   {
      return NULL_STRING;
   }
   return command.substr(command.find(SEMICOLON_CHAR) + 1, string::npos);
}

string Parser::jump()
{
   return jumpHelper(currentCommand);
}

string Parser::jump(string command)
{
   return jumpHelper(command);
}

void Parser::incrementCommandCount()
{
   ++commandCount;
}

int Parser::getCommandCount()
{
   return commandCount;
}

void Parser::incrementNextMemoryAddress()
{
   ++nextMemoryAddress;
}

int Parser::getNextMemoryAddress()
{
   return nextMemoryAddress;
}

void Parser::closeInputFile()
{
   inputFile.close();
}

vector<string>::iterator Parser::commandListBegin()
{
   return commandList.begin();
}

vector<string>::iterator Parser::commandListEnd()
{
   return commandList.end();
}
