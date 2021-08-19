#include "Code.cpp"
#include "Parser.h"
#include "SymbolTable.h"

#include <iostream>
#include <string>
#include <fstream>
#include <exception>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::size_t;
using std::to_string;
using std::exception;


const char FILE_EXTENSION_DELIMITER = '.';
const string MACHINE_FILE_EXTENSION = "hack";
const int MACHINE_INSTRUCTION_SIZE = 16;

string getMachineFilePath(string assemblyFilePath) {
   size_t dotPos = assemblyFilePath.find_last_of(FILE_EXTENSION_DELIMITER);
   string dir = assemblyFilePath.substr(0, dotPos);
   return dir + FILE_EXTENSION_DELIMITER + MACHINE_FILE_EXTENSION;
}

bool tryParseStringToInt(string s)
{
   int i;
   try
   {
      i = stoi(s);
      return true;
   }
   catch (exception e)
   {
      return false;
   }
}

int main(int argc, char* argv[])
{
   string inputFilePath = argv[1];
   ifstream inputFileStream(inputFilePath);
   if (inputFileStream.bad() || inputFileStream.fail())
   {
      return 1;
   }

   ofstream outFileStream;
   outFileStream.open(getMachineFilePath(inputFilePath));

   Parser parser = Parser(inputFileStream);

   SymbolTable symbolTable = SymbolTable();

   // FIRST PASS - BUILD SYMBOL TABLE AND STORE FILE IN MEMORY
   while (parser.hasMoreCommands())
   {
      parser.advance();
      string symbol;
      switch (parser.commandType())
      {
         case CommandType::A_COMMAND:
            parser.incrementCommandCount();
            break;
         case CommandType::C_COMMAND:
            parser.incrementCommandCount();
            break;
         case CommandType::L_COMMAND:
            symbol = parser.symbol();
            if (symbolTable.contains(symbol))
            {
               // invalid use of label symbols
               return 2;
            }
            // label next line of code
            symbolTable.addEntry(symbol, parser.getCommandCount());
            break;
      }
   }

   parser.closeInputFile();

   // SECOND PASS - TRANSLATE IN-MEMORY VERSION USING SYMBOL TABLE
   for(auto it = parser.commandListBegin(); it != parser.commandListEnd(); ++it)
   {
      string currentCommand = *it;
      string symbol, symbolAddress, dest, comp, jump, codeDest, codeComp, codeJump, toFile;
      switch (parser.commandType(currentCommand))
      {
         case CommandType::A_COMMAND:
            symbol = parser.symbol(currentCommand);
            if (tryParseStringToInt(symbol))
            {
               toFile = symbol;
            }
            else
            {
               if (symbolTable.contains(symbol))
               {
                  symbolAddress = to_string(symbolTable.getAddress(symbol));
               }
               else
               {
                  int nextMemoryAddress = parser.getNextMemoryAddress();
                  symbolTable.addEntry(symbol, nextMemoryAddress);
                  symbolAddress = to_string(nextMemoryAddress);

                  parser.incrementNextMemoryAddress();
               }
               toFile = symbolAddress;
            }
            outFileStream << Code::fullInstrA(toFile) << endl;
            break;
         case CommandType::C_COMMAND:
            dest = parser.dest(currentCommand);
            comp = parser.comp(currentCommand);
            jump = parser.jump(currentCommand);
            codeDest = Code::dest(dest);
            codeComp = Code::comp(comp);
            codeJump = Code::jump(jump);
            outFileStream << Code::fullInstrC(codeDest, codeComp, codeJump) << endl;
            break;
         case CommandType::L_COMMAND:
            // skip (label)'s since they're already in symbol table.
            // TODO, should labels even be stored in memory as file is parsed?
            break;
      }
   }

   outFileStream.close();
   return 0;
}