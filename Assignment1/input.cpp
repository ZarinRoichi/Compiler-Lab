#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
using namespace std;

void removeCommentsAndWhiteSpace(ifstream &input, ofstream &output)
{
    char ch, next;
    bool isWhiteSpace = false;

    while (input.get(ch))
    {
        if (ch == '/')
        {
            input.get(next);
            if (next == '/')
            {
                // Single-line comment: skip until end of line
                while (input.get(ch) && ch != '\n')
                    ;
            }
            else if (next == '*')
            {
                // Multi-line comment: skip until closing '*/'
                while (input.get(ch))
                {
                    if (ch == '*')
                    {
                        input.get(next);
                        if (next == '/')
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                // Not a comment, output the '/' and the next character
                output.put(ch);
                output.put(next);
            }
        }
        else if (isspace(ch))
        {
            // Handle excessive white space
            if (!isWhiteSpace)
            {
                output.put(' '); // Add a single space
                isWhiteSpace = true;
            }
        }
        else
        {
            // Regular character, reset white space flag
            output.put(ch);
            isWhiteSpace = false;
        }
    }
}

int main()
{
    ifstream input("input.cpp");
    ofstream output("output.txt");

    if (!input.is_open())
    {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }
    if (!output.is_open())
    {
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }

    // Display input file
    cout << "Input File:" << endl;
    string line;
    while (getline(input, line))
    {
        cout << line << endl;
    }
    input.clear();
    input.seekg(0, ios::beg);

    // Process and remove comments and white space
    removeCommentsAndWhiteSpace(input, output);

    input.close();
    output.close();

    // Display output file
    cout << "\n\nOutput File:" << endl;
    ifstream outFile("output.txt");
    if (!outFile.is_open())
    {
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }
    while (getline(outFile, line))
    {
        cout << line << endl;
    }
    outFile.close();

    return 0;
}
