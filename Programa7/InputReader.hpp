/*
InputReader.cpp
    The header handles all the input phases of the program
    from the name of the file to the input of the file.

Erick Francisco Gonzalez Martinez A01039589
Version: 7.0 last modified 19/11/2019
*/
//.b =88
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;
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
    //Stores the values of xk, yk, wk
    double xk,yk,wk;
    //Stores the values of the sum of each variable
    double xi,yi,wi,zi;
    //Stores the values of the sum of each variable
    double w2i,wx,wy,wz;
    //Stores the values of the sum of each variable
    double x2i,xy,xz;
    //Stores the values of the sum of each variable
    double y2i,yz;
    //Stores the coefficients
    double b0,b1,b2,b3;
    //Stores the data
    vector<vector<double> > data;
    //Stores the matrix that will be reduced
    vector<vector<double> > mat;

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
    //Calculates the row reduced echolon form
    void rrf();
};
/*
Function: InputReader::InputReader()
    Initializes the vector of results in 0 and the fileName as an empty string.
Parameters: -
Return: -
*/
//.i
InputReader::InputReader() : results(vector<double>(9, 0)), fileName("") //.m
{
    b0 = 0;
    b1 = 0;
    b2 = 0;
    b3 = 0;
    wi = 0;     
    xi = 0;     
    yi = 0;     
    zi = 0;     
    w2i = 0;
    x2i = 0;
    y2i = 0;
    wx = 0;
    wy = 0;
    wz = 0;
    xy = 0;
    xz = 0;
    yz = 0;
    xk = 0;
    yk = 0;
    wk = 0;
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
Function: InputReader::rrf()
    This procedure reduces the matrix in a row reduced
    echolon form.
Parameters: -
Return: -
*/
//.i
void InputReader::rrf()
{
    double pivot = 1;

    for(int i =0 ; i< mat.size(); i++)
    {
        for(int k =0; k < mat.size();k++)
        {
            if(k != i)
            {
                for(int j =i+1; j < mat[i].size();j++)
                {
                    mat[k][j] = (mat[i][i]*mat[k][j] - mat[k][i]*mat[i][j])/pivot;
                }
            }
        }
        pivot = mat[i][i];
    }

    b0 = (mat[0][mat.size()])/pivot;
    b1 = (mat[1][mat.size()])/pivot;
    b2 = (mat[2][mat.size()])/pivot;
    b3 = (mat[3][mat.size()])/pivot;

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
    rrf();
    results[0] = N;//.m
    results[1] = wk;//.m
    results[2] = xk;//.m
    results[3] = yk;//.m
    results[4] = b0;//.m
    results[5] = b1;//.m
    results[6] = b2;//.m
    results[7] = b3;//.m
    results[8] = b0+wk*b1+xk*b2+yk*b3;//.m

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
    double x,y,z,w;
    vector<double> ks;
    vector<double> input;
    string line;
    stringstream ss;

    getline(file, line);

    if (line.length() != 0)
        xk = stoi(line);

    ss = (stringstream)line;

    for (double i; ss >> i;) {
        ks.push_back(i);    
        if (ss.peek() == ',')
            ss.ignore();
    }
    wk = ks[0];
    xk = ks[1];
    yk = ks[2];

    while (!file.eof())
    {
        getline(file, line);

        ss = (stringstream)line;

        for (double i; ss >> i;) {
            input.push_back(i);   
            if (ss.peek() == ',')
                ss.ignore();
        }

        data.push_back(input);
        input.clear();
    }

    N = (int)data.size();

    if (N != 0)
    {
        for (int i = 0; i < N; i++)
        {
            wi += data[i][0];
            xi += data[i][1];
            yi += data[i][2];
            zi += data[i][3];

            w2i += pow(data[i][0],2);
            x2i += pow(data[i][1],2);
            y2i += pow(data[i][2],2);

            wx += data[i][0]* data[i][1];
            wy += data[i][0]* data[i][2];
            wz += data[i][0]* data[i][3];

            xy += data[i][1]* data[i][2];
            xz += data[i][1]* data[i][3];

            yz += data[i][2]* data[i][3];
        }
        vector<double> r1 = { (double)N , wi , xi , yi , zi };
        vector<double> r2 = { wi , w2i , wx , wy , wz };
        vector<double> r3 = { xi , wx , x2i , xy , xz };
        vector<double> r4 = { yi , wy , xy , y2i , yz };

        mat.push_back(r1);
        mat.push_back(r2);
        mat.push_back(r3);
        mat.push_back(r4);

        calculateValues();
    }
}

