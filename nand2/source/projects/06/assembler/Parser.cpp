#include "Parser.h"

#include <fstream>
#include <string>

using std::ifstream;
using std::string;

Parser::Parser(ifstream& inputFileCtr) : inputFile(inputFileCtr)
{
   getline(inputFile, nextCommand);
   bool asdf = nextCommand.empty();
   bool asdf1 = inputFile.eof();
}

bool Parser::hasMoreCommands()
{
   return !(nextCommand.empty() || inputFile.eof());
}

void Parser::advance()
{
   currentCommand = nextCommand;
   getline(inputFile, nextCommand);
   // throw exception on inputFile.eof() ?
}

CommandType Parser::commandType()
{
   return CommandType::A_COMMAND;
}

string Parser::symbol()
{
   return "";
}

string Parser::dest()
{
   return "";
}

string Parser::comp()
{
   return "";
}

string Parser::jump()
{
   return "";
}