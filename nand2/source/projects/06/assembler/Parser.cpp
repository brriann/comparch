#include "Parser.h"

#include <fstream>
#include <string>

using std::ifstream;
using std::string;

const char EQUALS_CHAR = '=';
const char SEMICOLON_CHAR = ';';

const string NULL_STRING = "null";

Parser::Parser(ifstream& inputFileCtr) : inputFile(inputFileCtr)
{
   getline(inputFile, currentCommand);
}

bool Parser::hasMoreCommands()
{
   // todo, account for last line
   return !inputFile.eof();
}

void Parser::advance()
{
   // TODO, handle comments
   getline(inputFile, currentCommand);
}

CommandType Parser::commandType()
{
   CommandType commandType;
   char firstCharOfLine = currentCommand.at(0);

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
   currentCommandType = commandType;
   return commandType;
}

string Parser::symbol()
{
   string symbol;
   switch (currentCommandType)
   {
      // @xxx
      case CommandType::A_COMMAND:
         symbol = currentCommand.substr(1, string::npos);
         break;
      // (xxx)
      case CommandType::L_COMMAND:
         symbol = currentCommand.substr(1, currentCommand.length() - 2);
         break;
      // invalid case - debug statement
      default:
         symbol = "invalidSymbolReturn";
         break;
   }
   return symbol;
}

string Parser::dest()
{
   // comp;jump
   if (currentCommand.find(EQUALS_CHAR) == string::npos)
   {
      return NULL_STRING;
   }
   return currentCommand.substr(0, currentCommand.find(EQUALS_CHAR));
}

string Parser::comp()
{
   if (currentCommand.find(EQUALS_CHAR) == string::npos)
   {
      return currentCommand.substr(0, currentCommand.find(SEMICOLON_CHAR));
   }
   else
   {
      if (currentCommand.find(SEMICOLON_CHAR) == string::npos)
      {
         return currentCommand.substr(currentCommand.find(EQUALS_CHAR) + 1, 
            string::npos);
      }
      else
      {
         return currentCommand.substr(currentCommand.find(EQUALS_CHAR) + 1, 
            currentCommand.find(SEMICOLON_CHAR) - (currentCommand.find(EQUALS_CHAR) + 1));
      }
   }
}

string Parser::jump()
{
   if (currentCommand.find(SEMICOLON_CHAR) == string::npos)
   {
      return NULL_STRING;
   }
   return currentCommand.substr(currentCommand.find(SEMICOLON_CHAR) + 1, string::npos);
}