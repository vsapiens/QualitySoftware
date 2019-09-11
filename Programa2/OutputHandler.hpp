/*
OutputHandler.cpp
    The header handles all the output phases of the program.
    In this case the output is given a format which is stated
    down below.

Erick Francisco Gonzalez Martinez A01039589
Version: 3.0 last modified 09/09/2019
*/
#include "InputReader.hpp"
/*
Class: OutputHandler
    Handles the output format of the files
*/
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
            cout << input[i].fileName.substr(0, input[i].fileName.find(".")) << " ";
            out << input[i].fileName.substr(0, input[i].fileName.find(".")) << " ";
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
            cout << input[i].fileName.substr(0, input[i].fileName.find(".")) << " ";
            out << input[i].fileName.substr(0, input[i].fileName.find(".")) << " ";
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
            cout << input[i].fileName.substr(0, input[i].fileName.find(".")) << " ";
            out << input[i].fileName.substr(0, input[i].fileName.find(".")) << " ";
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
