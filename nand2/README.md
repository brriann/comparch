# nand2
Repo for working through "The Elements of Computing Systems" (Nisan/Shocken), nand2tetris.org

# devNotes

# start hardware simulator
nand2tetris/tools/HardwareSimulator.sh


# Tool | Command
Hardware Simulator	HardwareSimulator.sh
CPU Emulator	CPUEmulator.sh
Assembler	Assembler.sh
VM Emulator	VMEmulator.sh
Jack Compiler	JackCompiler.sh


# Ch 9 .jack compiler notes
Unlike the simulators, which feature an interactive user interface, the Jack Compiler is a terminal-oriented application. In order to run it, you must supply the name of the file or folder that you wish to compile. For example, suppose you wish to compile all .jack files stored in the folder projects/09/Square (that's a folder called Square, located in the 09 folder, which is located in the projects folder). To do so, open a Terminal window and type:

JackCompiler.sh ~/Desktop/nand2tetris/projects/09/Square

This results in either a successful compilation of the .jack files in Square, or some compilation errors.
