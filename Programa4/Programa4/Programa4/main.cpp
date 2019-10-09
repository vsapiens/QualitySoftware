/*
main.cpp
This program is the main that handles the input reader and the output reader
    to calculate regressions as in the PROBE method suggests in the PSP

Erick Francisco Gonzalez Martinez A01039589
Version: 4.0 last modified 24/09/2019
*/
//.b =9
//.d=1
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
    input.storeValues(); //.m

    //Handles the output files
    OutputHandler output(input.results); //.m

    //Displays in the required format and saves the file
    output.display();

    return 0;
}
