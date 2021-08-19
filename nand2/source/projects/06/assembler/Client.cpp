#include "Code.cpp"
#include "Parser.h"

#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::size_t;


const char FILE_EXTENSION_DELIMITER = '.';
const string MACHINE_FILE_EXTENSION = "hack";
const int MACHINE_INSTRUCTION_SIZE = 16;

string getMachineFilePath(string assemblyFilePath) {
   size_t dotPos = assemblyFilePath.find_last_of(FILE_EXTENSION_DELIMITER);
   string dir = assemblyFilePath.substr(0, dotPos);
   return dir + FILE_EXTENSION_DELIMITER + MACHINE_FILE_EXTENSION;
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

   while (parser.hasMoreCommands())
   {
      parser.advance();
      string symbol, dest, comp, jump, codeDest, codeComp, codeJump;
      switch (parser.commandType())
      {
         case CommandType::A_COMMAND:
            symbol = parser.symbol();
            outFileStream << Code::fullInstrA(symbol) << endl;
            break;
         case CommandType::C_COMMAND:
            dest = parser.dest();
            comp = parser.comp();
            jump = parser.jump();
            codeDest = Code::dest(dest);
            codeComp = Code::comp(comp);
            codeJump = Code::jump(jump);
            outFileStream << Code::fullInstrC(codeDest, codeComp, codeJump) << endl;
            break;
         case CommandType::L_COMMAND:
            break;
      }
   }

   outFileStream.close();
   return 0;
}