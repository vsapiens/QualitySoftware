/*
main.cpp
    This program is the main that handles the input reader and the output reader
    to count the lines in the file given through the classification of
    a comment, multiline comment, blank spaces and lines of code.

Erick Francisco Gonzalez Martinez A01039589
Version: 3.0 last modified 10/09/2019
*/
#include "OutputHandler.hpp"

/*
Function: Main
It handles the input, process of counting the archives and the output for the programs.
Parameters: -
Return: Int, describing the correct compilation of the program
*/
int main()
{
    //determines the quantity of files
    int iFileQuantity;
    //the files are stored in a vector
    vector<InputReader> files;
    //reads the file
    cin >> iFileQuantity;
    cin.ignore();

    for (int i = 0; i < iFileQuantity; i++)
    {
        //Input Reader initialization
        InputReader input;
        //Input management
        input.handleInput();

        //If the archive doesn't open the counters are already initialized to 0
        if (input.openFile())
            input.countLines();

        if (i != 0)
        {
            //verifies if the file exists
            if (files[i - 1].fileName.substr(0, files[i - 1].fileName.find(".")) == files[i].fileName.substr(0, files[i].fileName.find(".")))
            {
                //adds the counter
                files[i - 1].counter[0] += files[i].counter[0];
                files[i - 1].counter[1] += files[i].counter[1];
                files[i - 1].counter[2] += files[i].counter[2];
                files[i - 1].counter[3] += files[i].counter[3];
                files[i - 1].counter[4] += files[i].counter[4];
                files[i - 1].counter[5] += files[i].counter[5];
                files[i - 1].counter[6] += files[i].counter[6];
            }
            else
            {
                files.push_back(input);
            }
        }
        else
        {
            files.push_back(input);
        }
    }
    //Handles the output files
    OutputHandler output(files);
    //Displays in the required format and saves the file
    output.display();

    return 0;
}