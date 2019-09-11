/*
main.cpp
    This program is the main that handles the input reader and the output reader
    to count the lines in the file given through the classification of
    a comment, multiline comment, blank spaces and lines of code.

Erick Francisco Gonzalez Martinez A01039589
Version: 2.0 last modified 29/08/2019
*/
#include "InputReader.hpp"
#include "OutputHandler.hpp"
/*
Function: Main
It handles the input, process of counting the archives and the output for the programs.
Parameters: -
Return: Int, describing the correct compilation of the program
*/
int main()
{
    //Input Reader initialization
    InputReader input;
    //Input management
    input.handleInput();

    //If the archive doesn't open the counters are already initialized to 0
    if (input.openFile())
        input.countLines();

    //Output Handler constructor with the name of the file and the counters
    OutputHandler output(input.getFileName(), input.getCounter());
    //Displays in the required format
    output.display();

    return 0;
}