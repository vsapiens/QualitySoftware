/*
OutputHandler.cpp
    The header handles all the output phases of the program.
    In this case the output is given a format which is stated
    down below.

Erick Francisco Gonzalez Martinez A01039589
Version: 2.0 last modified 29/08/2019
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;
/*
Class: OutputHandler
    Handles the output format of the files
*/
class OutputHandler
{

private:
    //Stores the name of the file
    string fileName;
    //Stores the lines of code of each type
    vector<int> counter;
    //Determines the amount of hyphens
    const static int iHyphens = 44;

public:
    /*
    Inline Function: OutputHandler::OutputHandler(string name, const vector<int> &count)
        Initializes the filename with the name given and copies the vector.
    Parameters: (string) The name of th file, (vector<int>&) The vector with the amount of lines of code.
    Return: -
*/
    OutputHandler(string name, const vector<int> &count) : fileName(name), counter(count){};
    //Formatted display
    void display();
};

/*
Function: OutputHandler::display()
    Initializes the vector of counters in 0 and the fileName as an empty string.
Parameters: -
Return: -
*/
void OutputHandler::display()
{

    cout << "Nombre del archivo: " << fileName << endl;

    for (int i = 0; i < iHyphens; i++)
        cout << "-";
    cout << endl;

    cout << "Cantidad de líneas en blanco: " << counter[0] << endl;
    cout << "Cantidad de líneas con comentarios: " << counter[1] << endl;
    cout << "Cantidad de líneas con código: " << counter[2] << endl;
    for (int i = 0; i < iHyphens; i++)
        cout << "-";
    cout << endl;
    cout << "Cantidad total de líneas: " << counter[0] + counter[1] + counter[2] << endl;
}
