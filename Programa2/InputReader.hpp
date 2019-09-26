/*
InputReader.cpp
    The header handles all the input phases of the program
    from the name of the file to the input of the file.
    It also includes the line counter according to the standard
    which is the main purpose of this program.

Erick Francisco Gonzalez Martinez A01039589
Version: 3.0 last modified 09/09/2019
*/
//.b =80
//.d=20
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
    //Returns if the input line is blank
    bool isBlank(string line);
    //Returns if the input line is a comment
    bool isComment(string line);
    //Returns if the input line is a comment
    bool isMultiComment(string line);

public:
    //Counters of the lines of code
    vector<int> counter;
    //Stores the file input
    ifstream file;
    //Stores the name of the file
    string fileName;
    //Stores the type of the char
    char type;

    //Empty Initialization
    InputReader();
    //Copy Constructor
    InputReader(const InputReader &ir);
    //Initialization with variables
    InputReader(vector<int> count, string name, char typ);
    //Handles the input of the name of the file
    void handleInput();
    //Tries to open the file
    bool openFile();
    //Counts the lines of code
    void countLines();
    //Determines the type of the block of code.
    void determineType();
};
/*
Function: InputReader::InputReader()
    Initializes the vector of counters in 0 and the fileName as an empty string.
Parameters: -
Return: -
*/
InputReader::InputReader() : counter(vector<int>(7, 0)), fileName(""), type('E'){};

/*
Function: InputReader::InputReader(const InputReader &ir)
    Copies the vector, the name of the file and the type.
Parameters: const InputReader &ir which is from where it will copy.
Return: -
*/
InputReader::InputReader(const InputReader &ir)
{
    counter = ir.counter;
    fileName = ir.fileName;
    type = ir.type;
};
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
    The function determines if the string is in blank
    or doesn't count for the LOC according to the 
    contabilization standards.  
Parameters: (string) The line to be analyzed.
Return: (bool) Returns whether the string is blank.
*/
bool InputReader::isBlank(string line)
{
    bool bfound = false;

    for (int i = 0; i < line.length(); i++)
    {
        if (!isspace((char)line[i]))
        {
            if (line[i] == '{' && !bfound)
            {
                bfound = true;
            }
            else if (line[i] == '}' && !bfound)
            {
                if (line[i + 1] == ';')
                {
                    bfound = true;
                    i++;
                }
                bfound = true;
            }
            else
                return false;
        }
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
    if (line.find("//") != -1)
    {
        if (line.find("//") == line.find("//."))
            return false;

        if (line.find("http") != -1)
            return false;

        return true;
    }

    return false;
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
        };

        return true;
    }

    return false;
}
/*
Function: InputReader::determineType()
    The function determines the type of code according to the 
    total LOC, base, reused and/or added.
Parameters: -
Return: -
*/
void InputReader::determineType()
{
    //"TIBDMA"
    if (counter[2] > 0 && (counter[3] > 0 || counter[4] > 0 || counter[5] > 0))
    {
        type = 'B';
    }
    else if (counter[2] == 0 && counter[3] == 0 && counter[4] == 0 && counter[5] > 0)
    {
        type = 'N';
    }
    else if (counter[2] > 0 && counter[3] == 0 && counter[4] == 0 && counter[5] == 0)
    {
        type = 'R';
    }
    else
    {
        type = 'E';
    }
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

        if (isComment(line) || isMultiComment(line) || isBlank(line))
        {
            counter[6]++;
        }
        else if (line.find("//.i") != string::npos)
        {
            counter[1]++;
        }
        else if (line.find("//.m") != string::npos)
        {
            counter[4]++;
        }
        else if (line.find("//.d=") != string::npos && line[line.find("=") + 1] != '\"')
        {
            counter[3] += stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("//.b =") != string::npos && line[line.find("=") + 1] != '\"')
        {
            counter[2] += stoi(line.substr(line.find("=") + 1));
        }
        else
        {
            counter[0]++;
        }
    }
    file.close();

    counter[0] += counter[4];
    //Calculates the added LOC
    counter[5] = counter[0] - counter[2] + counter[3];

    determineType();
}
