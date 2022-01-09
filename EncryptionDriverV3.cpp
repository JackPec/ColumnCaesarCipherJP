#include <iostream>
#include <string>
#include "templateInput3.h"
#include <fstream>
#include <cctype>
#include <climits>
#include<cstdlib>
#include<ctime>
#include <vector>
#include <iomanip>


//using namespace std;


std::string keyToUser = "";
std::string usersKey = "";

//void encrypt();

/////////////////////////////
class LineOfText
{
private:
    std::string line = "                                                  t"; //51 spaces
public:
    // getters and setters
    std::string GetLine();
    void SetLine(std::string input);
    void SetLine(char input, int index);

};

std::string LineOfText::GetLine()
{
    return line;
}

void LineOfText::SetLine(std::string input)
{
    line = input;
}

void LineOfText::SetLine(char input, int index)
{
    line[index] = input;
}
//////////////////

void encrypt(std::vector<LineOfText>& list)
{
    int seed;

    seed = ReadValue<int>("Input Seed integer here between INT_MAX and INT_MIN of current system:  ");

    std::cin.clear(); // clears cin after seed gets a value

    srand(time(0)+seed); //srand can take any amount of an int value


    std::string inFileName;
    std::ifstream inFile;

    std::string outFileName;
    std::ofstream outFile;

    std::ofstream keyFile;

    outFile.clear();


    std::string line;

    double value;
    double outputValue;
    int istreamErrors = 0;


    std::cout << "Enter input/write file name: "<< std::endl;
    std::cin >> inFileName;

    std::cout << "Enter output file name: "<< std::endl;

    std::cin >> outFileName;

    try
    {
        inFile.open(inFileName,std::ios::in);
        if (inFile.is_open()==1)
        {
            while (inFile.eof()==0)
            {
                //inFile >> setw(2); //
                getline(inFile,line);


                if(inFile.fail() == 1)
                {
                    istreamErrors++;

                    inFile.clear();
                    std::string dummy;
                    inFile >> dummy;


                    continue;
                }
                LineOfText t;

                ///////////////////////////////
                std::string addingspace = " ";

                while(line.size()<100)    /////////input should be formatted to be 100 chars long each line
                {
                    line += addingspace;

                }
                //////////////////////////

                t.SetLine(line);

                list.push_back(t);


            }


            inFile.close();
        }

        /////////////

        int longestLength = 0;
        for(int i = 0; i < list.size(); i++)
        {
            if(list[i].GetLine().size()> longestLength )
            {
                longestLength = list[i].GetLine().size();

            }


        }

        std::cout << longestLength << std::endl;


        for(int i = 0; i < longestLength; i++)
        {

            int key = rand() % 9 +1;

            for(int j = 0; j <  list.size(); j++)
            {
                // int key = rand() % 9 +1;



                // list[i].GetLine()[j] += key;
                char temp = list[j].GetLine()[i];

                // int wrap = temp + key; //assumes compiler does the wrap, will work on later
                if(!isspace(temp))
                {
                    temp += key;

                }


                list[j].SetLine(temp,i);

                //    keyToUser += to_string(key);

            }

            keyToUser += std::to_string(key);


        }

        std::cout<< keyToUser << std::endl;


        keyFile.open("Key",std::ios::out);
        if (keyFile.is_open()==1)
        {

            //    for(int i = 0; i < list.size();i++){
            keyFile << keyToUser << std::endl;
            //      cout << list[i].GetLine() << endl;

            //   }




        }

        keyFile.close();

//////////////////////////
        outFile.open(outFileName,std::ios::out);
        if (outFile.is_open()==1)
        {

            for(int i = 0; i < list.size(); i++)
            {
                outFile << list[i].GetLine() << std::endl;
                std::cout << list[i].GetLine() << std::endl;

            }




        }

        outFile.close();







    }
    catch (std::exception& ex)
    {
        throw;
    }













}

void decrypt(std::vector<LineOfText>& list)
{

    std::string inFileName;
    std::ifstream inFile;

    std::string outFileName;
    std::ofstream outFile;

    std::string keyFileName;
    std::ifstream keyFile;



    outFile.clear();


    std::string line;

    double value;
    double outputValue;
    int istreamErrors = 0;


    std::cout << "Enter input/write file name: "<< std::endl;
    std::cin >> inFileName;

    std::cout << "Enter output file name: "<< std::endl;

    std::cin >> outFileName;

    // cout << "Enter Key file name: "<< endl;

    // cin >> keyFileName;

    try
    {
        inFile.open(inFileName,std::ios::in);
        if (inFile.is_open()==1)
        {
            while (inFile.eof()==0)
            {
                //inFile >> setw(2); //
                getline(inFile,line);


                if(inFile.fail() == 1)  // checks errors when reading in data
                {
                    istreamErrors++;

                    inFile.clear();
                    std::string dummy;
                    inFile >> dummy;


                    continue;
                }
                LineOfText t;
                ///////////////////////////////
                std::string addingspace = " ";

                while(line.size()<100)    /////////input should be formatted to be 100 chars long each line
                {
                    line += addingspace;

                }
                //////////////////////////

                t.SetLine(line);

                list.push_back(t);


            }


            inFile.close();
        }

//////////////////////////////////////////////////////
        std::vector<int> keyVector;

        std::string keyLine = "";


        keyFile.open("Key",std::ios::in);
        if (keyFile.is_open()==1)
        {
            //  while (keyFile.eof()==0 && keyFile.fail()==0 ){
            //  int temp;
            //  keyFile >> temp;
            getline(keyFile,keyLine);
            //  keyVector.push_back(temp);
            //  cout << keyLine << endl ; //



            //   }

            keyFile.close();
        }
        /////////////////////////////////////////

        std::cout << keyLine << std::endl;
        for(int i = 0; i < keyLine.size(); i++)
        {
            char temp1 = keyLine[i];
            int temp2 = temp1 - '0'; // ascii value of temp1 - ascii value of 0 = actual value
            keyVector.push_back(temp2);
            std::cout << keyVector[i] << std::endl;

        }




////////////////////////////////

        for(int i = 0; i < 100; i++)
        {
            // int key = 1;
            int key = keyVector[i];

            for(int j = 0; j <  list.size(); j++)
            {
                // int key = rand() % 9 +1;



                // list[i].GetLine()[j] += key;
                char temp = list[j].GetLine()[i];

                // int wrap = temp + key; //assumes compiler does the wrap, will work on later
                if(!isspace(temp))
                {
                    temp -= key;

                }


                list[j].SetLine(temp,i);

                //    keyToUser += to_string(key);

            }


        }

        outFile.open(outFileName,std::ios::out);
        if (outFile.is_open()==1)
        {

            for(int i = 0; i < list.size(); i++)
            {
                outFile << list[i].GetLine() << std::endl;
                std::cout << list[i].GetLine() << std::endl;

            }
        }

        outFile.close();
    }
    catch (std::exception& ex)
    {
        throw;
    }


}
////////////////////////////////////////////////////////////////////////////


//selection options constants
const int ENCRYPT=1;
const int DECRYPT=2;
const int QUIT=3;



int main()
{
    int returnValue=0;

    std::vector<LineOfText> listEncrypt;
    std::vector<LineOfText> listDecrypt;



    try
    {



std::cout << "Column Caesar Cipher \n" << std::endl;
int menuChoice = 0;
	while (menuChoice != QUIT) {
        menuChoice = ReadValue<int>("\n1. Encrypt File\n2. Decrypt File\n3. Quit",1,3);

        if(menuChoice == ENCRYPT){
        encrypt(listEncrypt);
        }

        if(menuChoice == DECRYPT){
        decrypt(listDecrypt);
        }



    }











    }
    catch (std::exception& ex)
    {
        std::cerr<< ex.what() << std::endl;
        returnValue=1;
    }











    return returnValue;
}
