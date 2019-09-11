/*
InputReader.cpp
    The header handles all the input phases of the program
    from the name of the file to the input of the file.
    It also includes the line counter which is the main purpose
    of this program.

Erick Francisco Gonzalez Martinez A01039589
Version: 2.0 last modified 29/08/2019
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
/*
Class InputReader
    Manages the input of the files and count the lines of code
*/
class InputReader
{

private:
    //Counters of the lines of code
    vector<int> counter;
    //Stores the file input
    ifstream file;
    //Stores the name of the file
    string fileName;
    //Returns if the input line is blank
    bool isBlank(string line);
    //Returns if the input line is a comment
    bool isComment(string line);
    //Returns if the input line is a comment
    bool isMultiComment(string line);

public:
    //Empty Initialization
    InputReader();
    //Handles the input of the name of the file
    void handleInput();
    //Tries to open the file
    bool openFile();
    //Counts the lines of code
    void countLines();
    /*
    Inline Function: getCounter()
        Gets the counter of the lines of code.
    Parameters: -
    Return: (vector<int>) returns the vector of the counter.
    */
    vector<int> getCounter() { return counter; };
    /*
    Inline Function: getFileName() 
        Gets the file of the name.
    Parameters: -
    Return: (string) The name of the file.
    */
    string getFileName() { return fileName; };
};
/*
Function: InputReader::InputReader()
    Initializes the vector of counters in 0 and the fileName as an empty string.
Parameters: -
Return: -
*/
InputReader::InputReader() : counter(vector<int>(3, 0)), fileName(""){};

/*
Function: InputReader::handleInput()
    Reads the line of the filename and stores its
Parameters: -
Return: -
*/
void InputReader::handleInput()
{
    getline(cin, fileName);
}
/*
Function: InputReader::openFile()
    Tries to open the file and returns whether its successful.
Parameters: -
Return: (bool) Determines if the file is opened correctly, exists or if it is empty.
*/
bool InputReader::openFile()
{
    file.open(fileName);

    if (file.fail() || file.eof())
    {
        file.close();

        return false;
    }

    return true;
}
/*
Function: InputReader::isBlank
    The function determines if the string is in blank. 
Parameters: (string) The line to be analyzed.
Return: (bool) Returns whether the string is blank.
*/
bool InputReader::isBlank(string line)
{
    for (int i = 0; i < line.length(); i++)
    {
        if (!isspace((char)line[i]))
            return false;
    }

    return true;
}
/*
Function: InputReader::isComment
    The function determines if the string is a single lined comment.
Parameters: (string) The line to be analyzed.
Return: (bool) Returns whether the string is a single lined comment.
*/
bool InputReader::isComment(string line)
{
    if (line.find("//") == -1)
        return false;

    return true;
}
/*
Function: InputReader::isMultiComment
    The function determines if the string is a multilined lined comment.
Parameters: (string) The line to be analyzed.
Return: (bool) Returns whether the string is multilined lined comment.
*/
bool InputReader::isMultiComment(string line)
{
    if (line.find("/*") != -1)
    {
        while (line.find("*/") == -1)
        {

            getline(file, line);

            counter[1]++;
        };

        return true;
    }

    return false;
}

/*
Function: InputReader::countLines()
    The function determines the amount of lines in the code.
Parameters: -
Return: -
*/
void InputReader::countLines()
{

    string line;

    while (!file.eof())
    {
        getline(file, line);

        if (isBlank(line))
        {
            counter[0]++;
        }
        else if (isComment(line))
        {
            counter[1]++;
        }
        else if (isMultiComment(line))
        {
            counter[1]++;
        }
        else
        {
            counter[2]++;
        }
    }
    file.close();
}
