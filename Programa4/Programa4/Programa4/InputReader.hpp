/*
InputReader.cpp
    The header handles all the input phases of the program
    from the name of the file to the input of the file.
    It also includes the procedure to calculate the regression
    according to the probe method.

Erick Francisco Gonzalez Martinez A01039589
Version: 4.0 last modified 24/09/2019
*/
//.b =79
//.d=40
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
//Stores the maximum Error accepted by the iteration in Simspon
double maxError = 0.0000001;
//Stores the value of pi
double pi = 3.14159265359;
//.i
class InputReader
{
private:
    //Stores the x value
    double x; //.m
    //Stores the degrees of freedom from the user
    double dof; //.m
    //Stores the data from the file
    vector<double> data; //.m
    //Stores the iteration of simspon
    double p1, p2;
    //Stores the number of segments
    double num_seg;

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
    double calculateTDistribution(double num);
    //Calculates all the values
    void calculateIntegralSimpson();
};
/*
Function: InputReader::InputReader()
    Initializes the vector of results in 0 and the fileName as an empty string.
Parameters: -
Return: -
*/
//.i
InputReader::InputReader() : results(vector<double>(3, 0)), fileName(""), num_seg(10), p1(0), p2(0) //.m
                             {};

/*
Function: InputReader::InputReader(const InputReader &ir)
    Copies the vector and the name of the file.
Parameters: const InputReader &ir which is from where it will copy.
Return: -
*/
//.i
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
//.i
void InputReader::handleInput()
{
    cin >> x >> dof;
}
/*
Function: InputReader::openFile()
    Tries to open the file and returns whether its successful.
Parameters: -
Return: (bool) Determines if the file is opened correctly, exists or if it is empty.
*/
//.i
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
 Function: getDistributionGamma(double num)
    Calculates the gamma distribution of the num
 Parameters: -
 Return: num
 */
//.i
double getDistributionGamma(double num)
{
    if (num == 1)
        return 1;

    if (num == 0.5)
        return 1.77245385091;

    return (num - 1) * getDistributionGamma(num - 1);
}
/*
 Function: getDistributionT(double x, double dof)
    Calculates the distribution T with x value and dof degrees of freedom
 Parameters: (double)x is the value to be calculated, (double) dof degrees of freedom of the function
 Return: (double)(pow((1 + (pow(x, 2) / dof)), (-(dof + 1) / 2)))*(getDistributionGamma((dof + 1) / 2) / (pow(dof * pi, 0.5) * getDistributionGamma(dof / 2)))
 */
//.i
double getDistributionT(double x, double dof)
{

    return (double)(pow((1 + (pow(x, 2) / dof)), (-(dof + 1) / 2))) *
           (getDistributionGamma((dof + 1) / 2) / (pow(dof * pi, 0.5) * getDistributionGamma(dof / 2)));
}
/*
 Function: calculateIteration(double x, double dof, double num_seg)
    Calculates the distribution T with x value and dof degrees of freedum
 Parameters: (double)x is the value to be calculated, (double) dof degrees of freedom of the function, (double) num_seg in which the simpson approximation is calculated
 Return: (double) p
 */
//.i
double calculateIteration(double x, double dof, double num_seg)
{
    if (x <= 0 && dof <= 0)
        return 0;

    double width = x / num_seg;
    double p = 0;
    double it_num_seg = 0;
    double it_width = 0;
    double it_constant = (double)width / 3;

    while (it_num_seg <= num_seg)
    {
        if (it_num_seg == num_seg)
        {
            p += it_constant * getDistributionT(it_width, dof);
        }
        else if (it_num_seg == 0)
        {
            p += it_constant * getDistributionT(0, dof);
        }
        else if ((int)it_num_seg % 2 == 0)
        {
            p += (double)2 * it_constant * getDistributionT(it_width, dof);
        }
        else
        {
            p += (double)4 * it_constant * getDistributionT(it_width, dof);
        }

        it_width += width;
        ++it_num_seg;
    };

    return p;
}

/*
 Function: InputReader::storeValues()
    Stores the values of the file into the data types in the class
 Parameters: -
 Return: -
 */
//.i
void InputReader::storeValues()
{
    p1 = calculateIteration(x, dof, num_seg);

    num_seg *= 2;

    p2 = calculateIteration(x, dof, num_seg);
    while (abs(p1 - p2) >= maxError)
    {
        p2 = p1;
        num_seg *= 2;
        p1 = calculateIteration(x, dof, num_seg);
    }
    results[0] = x;
    results[1] = dof;
    results[2] = p2;
}
