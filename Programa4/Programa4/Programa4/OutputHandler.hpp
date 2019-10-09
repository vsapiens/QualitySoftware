/*
OutputHandler.cpp
    The header handles all the output phases of the program.
    In this case the output is given a format which is stated
    down below.

Erick Francisco Gonzalez Martinez A01039589
Version: 5.0 last modified 24/09/2019
*/
//.b =26
//.d=4
#include "InputReader.hpp"
/*
Class: OutputHandler
    Handles the output format of the files
*/
//.i
class OutputHandler
{
private:
    // The results to be displayed
    vector<double> results;

public:
    /*
    Inline Function: OutputHandler::OutputHandler(vector<double> temp)
        Copies the results into the vector.
    Parameters: (vector<double> temp) Vector of all the results
    Return: -
    */
    OutputHandler(vector<double> temp) : results(temp){};

    //Formatted display
    void display();
};
/*
 Function: round
 Displays the results in the format
 Parameters: (double) number the number to be added
 Return: (double) value of the number rounded
 */
//.i
inline double round(double number)
{
    if (number < 0)
        return ceil(number - 0.5);
    return floor(number + 0.5);
}
/*
 Function: convert
 Displays the results in the format
 Parameters: (double) x is the number to be converted
 Return: String with the rounded double to 5 decimal places
 */
//.i
string convert(double x)
{
    string s = to_string(round(x * 100000.0) / 100000.0);
    int length;

    length = (int)s.find(".") + 6;
    while (s[s.length() - 1] == '0' && length < s.length())
    {
        s.pop_back();
    }

    return s;
}
/*
Function: OutputHandler::display()
    Displays the results in the format
Parameters: -
Return: -
*/
//.i
void OutputHandler::display()
{
    cout << "  x = " << convert(results[0]) << endl;//.m
    cout << "dof = " << results[1] << endl;//.m
    cout << "  p = " << convert(results[2]) << endl;//.m
}
