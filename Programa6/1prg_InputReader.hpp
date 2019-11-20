/*
InputReader.cpp
    The header handles all the input phases of the program
    from the name of the file to the input of the file.
    It also includes the procedure to calculate the regression
    according to the probe method.

Erick Francisco Gonzalez Martinez A01039589
Version: 6.0 last modified 06/11/2019
*/
//.b =88
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
//Stores the maximum Error accepted by the iteration in Simspon
double maxError = 0.00000001;
//Stores the value of pi
double pi = 3.14159265359;
/*
Class InputReader
    Manages the input of the files and calculates the values
*/
//.i
class InputReader
{
private:
    //Stores the N value
    int N;
    //Stores the xK real value
    double xK;
    //Stores the x value
    double x;
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
    vector<pair<double, double> > data;
    //Stores the degrees of freedom from the user
    double dof;
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
    //Calculates all the values
    void calculateValues();
};
/*
Function: InputReader::InputReader()
    Initializes the vector of results in 0 and the fileName as an empty string.
Parameters: -
Return: -
*/
//.i
InputReader::InputReader() : results(vector<double>(11, 0)), fileName(""), num_seg(100000), p1(0), p2(0) //.m
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
    getline(cin, fileName);
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
 Function: InputReader::calculateValues()
    Calculates all the values of the given set
 Parameters: -
 Return: -
 */
//.i
void InputReader::calculateValues()
{
    
    results[0] = N;
    results[1] = xK;
    results[2] = (double)((dSumXY - N * dAvgY * dAvgX) / (dSumX2 - N * pow(dAvgX, 2)));
    results[3] = (double)(dAvgY - results[2] * dAvgX);
    results[4] = ((double)N * (dSumXY)-dSumX * dSumY) / sqrt((double)(N * (dSumX2)-pow(dSumX, 2)) * ((double)N * (dSumY2)-pow(dSumY, 2)));
    results[5] = pow(results[4], 2);
    results[6] = results[3] + results[2] * xK;

    dof = (double)N-2.0;
    x = (abs(results[4])*sqrt(dof))/(sqrt(1.0-results[5]));
    p1 = calculateIteration(x, dof, num_seg);
    results[7] = 1.0-2.0*p1;

    //Calculate Results 8
    double sum(0),sum2(0),sigma(0);

    for (int i = 0; i < N; i++)
    {
        sum += pow(data[i].second- results[3]-results[2]*data[i].first,2);
        sum2 += pow(data[i].first - dAvgX,2);
    }
    sigma = sqrt((1/dof)*sum);

    bool bRight = false;
    x = 1.0;
    double delta = x / 2.0;
    p1 = calculateIteration(x, dof, num_seg);

    if (p1 < 0.35)
    {
        x += delta;
        bRight = true;
    }
    else
        x -= delta;

    p2 = calculateIteration(x, dof, num_seg);
    delta /= 2;
    while (abs(p1 - p2) >= maxError)
    {
        if (p1 < 0.35)
        {
            x += delta;
            if (!bRight)
            {
                delta /= 2;
            }
            bRight = true;
        }
        else
        {
            x -= delta;
            if (bRight)
            {
                delta /= 2;
            }
            bRight = false;
        }
        p2 = p1;
        p1 = calculateIteration(x, dof, 10000);
    }

    results[8] = (double)(x*sigma*sqrt( 1.0 + (double)1.0/N + ((double)(pow((double)xK-dAvgX,2))/sum2)));
    results[9] = results[6]+results[8];
    results[10] = results[6]-results[8] <= 0 ? 0: results[6]-results[8];
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
