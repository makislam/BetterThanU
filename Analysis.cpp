#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;


string primeInstructions(char & letter)
{
    //switch case for prime instructions
    switch (letter) 
    {
        case 'F':
            return "F";
            break;
        case 'U':
            return "U";
            break;
        case 'D':
            return "D";
            break;
        case 'R':
            return "R";
            break;
        case 'L':
            return "L";
            break;
        case 'B':
            return "B";
            break;
    }
    return "invalid";
}

string Instructions(char & letter)
{
    //switch instructions for standard cube instructions
    switch (letter) 
    {
        case 'F':
            return "A";
            break;
        case 'U':
            return "C";
            break;
        case 'D':
            return "E";
            break;
        case 'R':
            return "G";
            break;
        case 'L':
            return "H";
            break;
        case 'B':
            return "I";
            break;
    }  
    return "invalid";
}
string reverse(string & input)
{ 
    string reversal = "";
    for(int index = input.length()-1; index >= 0 ; index --)
    {
        if(input.at(index) == 'p' || input.at(index) == '\'')
        {
            //valididty check
            if(primeInstructions(input.at(index-1)) == "invalid")
            {
                cout << "The instruction is invalid."<< endl;
                break;
            }
            reversal += primeInstructions(input.at(index-1));
            index--;
        }
        //valididty check
        else if(!(Instructions(input.at(index)) == "invalid"))
        {
            reversal += Instructions(input.at(index));
        }
        else
        {
            cout << "The instruction is invalid." << endl;
            break;
        }
    }
    return reversal; 
}

int main ()
{
    // Declare the solution and state strings
    string state = " ";
    int move_counter = 0;

    // Recieve input for the state
    cout << "What is the state of the cube? ";
    cin >> state;

    // Create & open new file to input the solution into
    ofstream fout("moves.txt");

    //prints out the new revered instructions
    fout << reverse(state);

    return EXIT_SUCCESS;
}