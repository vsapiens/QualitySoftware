#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
//.b=205
class InputReader
{
private:
    bool isBlank(string line);
    bool isComment(string line);
    bool isMultiComment(string line);

public:
    vector<int> counter;
    ifstream file;
    string fileName;
    char type;
    InputReader();
    InputReader(const InputReader &ir);
    InputReader(vector<int> count, string name, char typ);
    void handleInput();
    bool openFile();
    void countLines();
    void determineType();
};
InputReader::InputReader() : counter(vector<int>(7, 0)), fileName(""), type('E'){};
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
        else if (line.find("//.d=") != string::npos)
        {
            counter[3] += stoi(line.substr(line.find("//.d=") + 5));
        }
        else if (line.find("//.b=") != string::npos)
        {
            counter[2] += stoi(line.substr(line.find("//.b=") + 5));
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
class OutputHandler
{
private:
    //Determines the amount of hyphens
    const static int iHyphens = 44;
    //Stores the files read
    vector<InputReader> input;
    //Determines in order the values T=xx, I=xx, B=xx, D=xx, M=xx, A=xx
    string types;
    //File to be saved
    ofstream out;
    //The total counter of lines of code
    int globalCounter;
    //Formats each file according to the type
    void handlecheckCounterBASE(vector<int> counter);
    //Formats each file according to the type
    void handlecheckCounterNEW(vector<int> counter);
    //Formats each file according to the type
    void handlecheckCounterREUSE(vector<int> counter);

public:
    /*
    Inline Function: OutputHandler::OutputHandler(vector<InputReader> temp)
        Copies the input constructor, the types in the string, the file to be saved
        and the global counter of lines of code.
    Parameters: (vector<InputReader>) Vector of all the 
    Return: -
    */
    OutputHandler(vector<InputReader> temp) : input(temp), types("TIBDMA"), out("ConteoLDC.txt"), globalCounter(0){};
    //Formatted display
    void display();
};
/*
Function: handlecheckCounterBASE(vector<int> counter)
    Gives format to the display according to the BASE type
Parameters: (vector<int> counter) Where all the counters are stored
Return: -
*/
void OutputHandler::handlecheckCounterBASE(vector<int> counter)
{
    for (int i = 0; i < 6; i++)
    {
        if (counter[i] != -1)
        {
            cout << types[i] << "=" << counter[i];
            out << types[i] << "=" << counter[i];
            if (i != 5)
            {
                cout << ", ";
                out << ", ";
            }
        }
    }
    cout << endl;
    out << endl;
}
/*
Function: handlecheckCounterNEW(vector<int> counter)
    Gives format to the display according to the NEW type
Parameters: (vector<int> counter) Where all the counters are stored
Return: -
*/
void OutputHandler::handlecheckCounterNEW(vector<int> counter)
{
    for (int i = 0; i < 2; i++)
    {
        if (counter[i] != -1)
        {
            cout << types[i] << "=" << counter[i];
            out << types[i] << "=" << counter[i];
            if (i != 1)
            {
                cout << ", ";
                out << ", ";
            }
        }
    }
    cout << endl;
    out << endl;
}
/*
Function: handlecheckCounterREUSE(vector<int> counter)
    Gives format to the display according to the REUSE type
Parameters: (vector<int> counter) Where all the counters are stored
Return: -
*/
void OutputHandler::handlecheckCounterREUSE(vector<int> counter)
{
    for (int i = 0; i < 3; i++)
    {
        if (counter[i] != -1)
        {
            cout << types[i] << "=" << counter[i];
            out << types[i] << "=" << counter[i];
            if (i != 2)
            {
                cout << ", ";
                out << ", ";
            }
        }
    }
    cout << endl;
    out << endl;
}
/*
Function: OutputHandler::display()
    Initializes the vector of counters in 0 and the fileName as an empty string.
Parameters: -
Return: -
*/
void OutputHandler::display()
{
    cout << "PARTES BASE:" << endl;
    out << "PARTES BASE:" << endl;

    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].type == 'B')
        {
            cout << "   " << input[i].fileName.substr(0, input[i].fileName.find(".")) << " ";
            out << "   " << input[i].fileName.substr(0, input[i].fileName.find(".")) << " ";
            handlecheckCounterBASE(input[i].counter);
        }
        globalCounter += input[i].counter[0];
    }
    for (int i = 0; i < iHyphens; i++)
    {
        cout << "-";
        out << "-";
    }
    cout << endl;
    out << endl;

    cout << "PARTES NUEVAS:" << endl;
    out << "PARTES NUEVAS:" << endl;

    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].type == 'N')
        {
            cout << "   " << input[i].fileName.substr(0, input[i].fileName.find(".")) << " ";
            out << "   " << input[i].fileName.substr(0, input[i].fileName.find(".")) << " ";
            handlecheckCounterNEW(input[i].counter);
        }
    }
    for (int i = 0; i < iHyphens; i++)
    {
        cout << "-";
        out << "-";
    }
    cout << endl;
    out << endl;

    cout << "PARTES REUSADAS:" << endl;
    out << "PARTES REUSADAS:" << endl;

    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].type == 'R')
        {
            cout << "   " << input[i].fileName.substr(0, input[i].fileName.find(".")) << " ";
            out << "   " << input[i].fileName.substr(0, input[i].fileName.find(".")) << " ";
            handlecheckCounterREUSE(input[i].counter);
        }
    }
    for (int i = 0; i < iHyphens; i++)
    {
        cout << "-";
        out << "-";
    }
    cout << endl;
    out << endl;
    cout << "Total de LDC=" << globalCounter << endl;
    out << "Total de LDC=" << globalCounter << endl;
    out.close();
}
