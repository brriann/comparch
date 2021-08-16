#include "Code.cpp"
#include "Parser.h"

#include <iostream>
#include <string>
#include <fstream>

using std::cout;
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

int main()
{
   // todo, arg1
   string inputFilePath = "assembly.asm";
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

      string debug1, debug2, debug3;
      bitset<3> debug4;
      switch (parser.commandType())
      {
         case CommandType::A_COMMAND:
            break;
         case CommandType::C_COMMAND:
            debug4 = Code::dest(parser.dest());
         case CommandType::L_COMMAND:
            break;
      }
   }


   outFileStream.close();
   cout << "assembler time";
   return 0;
}