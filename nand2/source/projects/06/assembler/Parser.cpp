#include "Parser.h"

#include <fstream>
#include <string>

using std::ifstream;
using std::string;

Parser::Parser(ifstream& inputFile)
{

}

bool Parser::hasMoreCommands()
{
   return true;
}

void Parser::advance()
{

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