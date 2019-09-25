/*
InputReader.cpp
    The header handles all the input phases of the program
    from the name of the file to the input of the file.
    It also includes the procedure to calculate the regression
    according to the probe method.

Erick Francisco Gonzalez Martinez A01039589
Version: 4.0 last modified 24/09/2019
*/
//.b =80
//.d=#
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
/*
Class InputReader
    Manages the input of the files and calculates the values
*/
class InputReader
{
private:
    //Stores the N value
    int N;
    //Stores the xK real value
    int xK;
    //Stores the sum of the multiplication of the pairs
    double dSumXY;
    //Stores the sum of x values
    double dSumX;
    //Stores the sum of y values
    double dSumY;
    //Stores the sum of y^2 values
    double dSumY2;
    //Stores the sum of x^2 values
    double dSumX2;
    //Stores the average of x
    double dAvgX;
    //Stores the average of y
    double dAvgY;
    //Stores the data
    vector<pair<double, double>> data;

public:
    //Stores the results of the saved data
    vector<double> results;
    //Stores the file input
    ifstream file;
    //Stores the name of the file
    string fileName;

    //Empty Initialization
    InputReader();
    //Copy Constructor
    InputReader(const InputReader &ir);
    //Initialization with variables
    InputReader(vector<double> results);
    //Handles the input of the name of the file
    void handleInput();
    //Tries to open the file
    bool openFile();
    //Stores the values in the file
    void storeValues();
    //Calculates all the values
    void calculateValues();
};
/*
Function: InputReader::InputReader()
    Initializes the vector of results in 0 and the fileName as an empty string.
Parameters: -
Return: -
*/
InputReader::InputReader() : results(vector<double>(7, 0)), fileName("")
{
    dSumXY = 0;
    dSumX = 0;
    dSumY = 0;
    dSumY2 = 0;
    dSumX2 = 0;
    dAvgX = 0;
    dAvgY = 0;
};

/*
Function: InputReader::InputReader(const InputReader &ir)
    Copies the vector, the name of the file and the type.
Parameters: const InputReader &ir which is from where it will copy.
Return: -
*/
InputReader::InputReader(const InputReader &ir)
{
    results = ir.results;
    fileName = ir.fileName;
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
 Function: InputReader::calculateValues()
    Calculates all the values of the given set
 Parameters: -
 Return: -
 */
void InputReader::calculateValues()
{

    results[0] = N;
    results[1] = xK;

    results[2] = (dSumXY - N * dAvgY * dAvgX) / (dSumX2 - N * pow(dAvgX, 2));
    results[3] = dAvgY - results[2] * dAvgX;

    results[4] = (N * (dSumXY)-dSumX * dSumY) / sqrt((N * (dSumX2)-pow(dSumX, 2)) * (N * (dSumY2)-pow(dSumY, 2)));
    results[5] = pow(results[4], 2);

    results[6] = results[3] + results[2] * xK;
}
/*
 Function: InputReader::storeValues()
    Stores the values of the file into the data types in the class
 Parameters: -
 Return: -
 */
void InputReader::storeValues()
{
    double x, y;
    string line;
    getline(file, line);

    if (line.length() != 0)
        xK = stoi(line);

    while (!file.eof())
    {
        getline(file, line);
        x = stod(line.substr(0, line.find(",")));
        y = stod(line.substr(line.find(",") + 1));
        if (x != 0 && y != 0)
            data.push_back(make_pair(x, y));
    }

    N = (int)data.size();

    if (N != 0)
    {
        for (int i = 0; i < N; i++)
        {
            dSumXY += data[i].first * data[i].second;
            dSumX += data[i].first;
            dSumY += data[i].second;
            dSumY2 += pow(data[i].second, 2);
            dSumX2 += pow(data[i].first, 2);
        }

        dAvgX = dSumX / ((double)N);
        dAvgY = dSumY / ((double)N);

        calculateValues();
    }
}
