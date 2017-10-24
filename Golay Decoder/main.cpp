#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;


int B[12][12] = {
    {0,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,0,1,1,1,0,0,0,1,0},
    {1,1,0,1,1,1,0,0,0,1,0,1},
    {1,0,1,1,1,0,0,0,1,0,1,1},
    {1,1,1,1,0,0,0,1,0,1,1,0},
    {1,1,1,0,0,0,1,0,1,1,0,1},
    {1,1,0,0,0,1,0,1,1,0,1,1},
    {1,0,0,0,1,0,1,1,0,1,1,1},
    {1,0,0,1,0,1,1,0,1,1,1,0},
    {1,0,1,0,1,1,0,1,1,1,0,0},
    {1,1,0,1,1,0,1,1,1,0,0,0},
    {1,0,1,1,0,1,1,1,0,0,0,1}
    };

int G[12][24] =  {
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,1,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,0,1,0,1},
    {0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,1,0,1,1},
    {0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,0,1,1,0},
    {0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,0,1,0,1,1,0,1},
    {0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,1,1},
    {0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,1,0,1,1,1},
    {0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,1,1,0,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,1,0,1,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,1,0,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,0,0,0,1}
    };


int weight( int vec[12] ) // Determines the weight of the input vector vec
{
    int vecWeight = 0;
    for (int i=0; i < 12; i = i + 1 )
    {
        if (vec[i] != 0)
        {
            vecWeight = vecWeight + 1;
        }
    };
    return vecWeight;
}

int decode( int receivedVec[24], int errorVec[24], int stepCounter )
{
    cout << "------------------SUCCESS AT STEP " << stepCounter << "-------------------\n\n";

    cout << "   Using the received word    r = [ ";
    for (int i = 0; i < 24; i = i + 1 )
    {
        cout << receivedVec[i] << " ";
    }
    cout << "]\n   and the error vector       e = [ ";

    for (int i = 0; i < 24; i = i + 1 )
    {
        cout << errorVec[i] << " ";
    }
    cout << "]\n\n   We decode r to     c = r - e = [ ";
    for (int i = 0; i < 24; i = i + 1 )
    {
        cout << (receivedVec[i] + errorVec[i]) % 2 << " ";
    }
    cout << "].";
}


int main()
{

    // Get the received word
    cout << "Enter a 24 bit word to decode: ";
    string initialInput;
    getline(cin, initialInput);

    if (initialInput.length() != 24)
    {
        cout << "\n\n\n   You must enter a 24 bit word!\n\n\n";
        return 0;
    }
    for (int i = 0; i < 24; i = i + 1)
    {
        if ( initialInput[i] != '0' && initialInput[i] != '1')
        {
            cout << "\n\n\n   You must enter only 0's and 1's!\n\n\n";
            return 0;
        }
    }

    // Convert the received word into an array of integers to work with
    int r[24];  // The array that the received word is stored in (interpreted as a row vector)
    int e[24];  // The error vector that will be used in decoding.
    int stepCounter = 0; // This counts which step we are on

    cout << "\n\nAssigning vector r as r = (";
    for (int i = 0; i < 24; i = i + 1)
    {
        r[i] = initialInput[i] - '0';
        if ( i != 23 )
            cout << r[i] << ",";
        else if ( i == 23 )
            cout << r[i];
    }
    cout << ").";


    // Step 1: Compute s = G*r^T

    int s[12] = {0,0,0,0,0,0,0,0,0,0,0,0};      // This will be G * r^T
    int j;    // This is a loop counter for taking dot products. Represents the column index

    // Compute s:
    for (int i=0; i <= 11; i = i + 1) // i is the row index
    {
        for ( j = 0; j < 24; j = j + 1)
        {
            s[i] = (s[i] + G[i][j] * r[j]) % 2;
        };
    };


    // Output s to the user
    cout << "\n\n------------------------Step 1------------------------\n   Computing vector s:\n\n";
    stepCounter = 1;


    for (int i=0; i <= 23; i = i + 1) // This loop counts the columns
    {
            if (i<6)
                cout << "                                                                     |" << r[i] << "|\n";
            if (6 <= i && i < 18)
                {
                    if (i != 12)
                        cout << "                 |";
                    else
                        cout << "   s = G * r^T = |";
                    for (int k = 0; k < 24; k = k + 1)
                    {
                        cout << G[i-6][k];
                        if (k != 23)
                            cout << " ";
                    }
                    cout << "|";
                    if (i == 12)
                        cout << " * ";
                    else
                        cout << "   ";
                    cout << "|" << r[i] << "|";

                    if (i == 12)
                    {
                        cout << " = |" << s[i-6] << "|";
                    }
                    else
                        cout << "   |" << s[i-6] << "|";
                    cout << "\n";
                }
                if (18 <= i)
                {
                    cout << "                                                                     |" << r[i] << "|\n";
                }

    };
    // Step 2: If w(s) <= 3, then set e = (s^T,0) and decode r to r-e

    cout << "\n   Proceeding to step 2...\n";

    cout << "\n\n------------------------Step 2------------------------\n   The weight of s is w(s) = " << weight(s) << ".";
    stepCounter = 2;

    // Check the weight. If it doesn't exceed 3, decode r
    if (weight(s) <= 3)
    {

        for( int i = 0; i < 12; i = i + 1)
        {
            e[i] = s[i];
        }
        for( int i = 0; i < 12; i = i + 1)
        {
            e[i + 12] = 0;
        }

        cout << "\n   Setting error vector as e = (s^T,0).";
        cout << "\n\n";
        decode( r, e, stepCounter);
        cout << "\n\n\n\n";
        return 0;
    }

    cout << "\n   The weight of s exceeds 3.\n   Proceeding to step 3...\n";


    // Step 3: If w(s + I_i) <= 2 for some I_i (column of B), then set e = ((s+I_i)^T, y^(i)) and decode r to r-e
    cout << "\n\n------------------------Step 3------------------------\n";
    stepCounter = 3;
    int sPlusI[12] = {0,0,0,0,0,0,0,0,0,0,0,0};     // This is the vector s + I_i that we are trying to find.
    int columnTracker = -1;                          // The index i for the column we are trying to find will be stored here.

    cout << "   Computing w(s+I_i) for columns I_i of B...\n";
    for (int i = 0; i < 12; i = i + 1)
    {
        for (int j = 0; j < 12; j = j + 1 )
        {
            sPlusI[j] = ( s[j] + B[j][i] ) % 2;

        }
        if (weight(sPlusI) <= 2)
            columnTracker = i;
            break;
    }


    if (columnTracker >= 0)      // If a column was found, do this stuff...
    {
        // Set the error vector:
        for (int i = 0; i < 24; i = i + 1 )
        {
            if (i<12)
                e[i] = ( s[i] + B[i][columnTracker] ) % 2;
            else if (i >= 12 && i-12 != columnTracker)
                e[i] = 0;
            else if (i >= 12 && i-12 == columnTracker)
                e[i] = 1;
        }
        cout << "\n   Column " << columnTracker + 1 << " works. Setting i = " << columnTracker + 1 << ".";
        cout << "\n   Setting error vector as e = ( (s+I_" << columnTracker + 1 << ")^T,y^(" << columnTracker + 1 << ") ).";
        cout << "\n\n\n";
        decode( r, e, stepCounter);
        cout << "\n\n\n\n";
        return 0;
    }

    cout << "   No columns I_i were found such that w(s+I_i) <= 2.\n   Proceeding to step 4...\n";


    // Step 4: Compute B^T*s
    cout << "\n\n------------------------Step 4------------------------\n   Computing vector B^T*s:\n\n";
    int Bs[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

    for (int i = 0; i < 12; i = i + 1)
    {
        for (int j = 0; j < 12; j = j + 1)
        {
            Bs[i] = ( Bs[i] + B[i][j]*s[j] ) % 2;
        }
    }

    // Output the computation to the user
    for (int i = 0; i < 12; i = i + 1)
    {
        if (i != 6)
            cout << "             ";
        else
            cout << "   B^T * s = ";

        cout << "|";
        for (int j = 0; j < 26; j = j + 1)
        {
            if (j < 11)
                cout << B[i][j] << " ";
            else if (j == 11)
                cout << B[i][j];
            else if (j == 13 )
                cout << "| ";
            else if (j == 15 && i == 6)
                cout << "* ";
            else if (j == 15 && i != 6)
                cout << "  ";
            else if (j == 17)
                cout << "|" << s[i] << "| ";
            else if (j == 21 && i == 6)
                cout << "= ";
            else if (j == 21 && i != 6)
                cout << "  ";
            else if (j == 23)
                cout << "|" << Bs[i] << "|\n";

        }
    }

    cout << "\n   Proceeding to step 5...\n";



    // Step 5: If w(B^T*s) <= 3, then set e = (0, (B^Ts)^T) and decode r to r-e
    cout << "\n\n------------------------Step 5------------------------\n   The weight of B^T*s is " << weight(Bs) << ".";
    stepCounter = 5;

    if (weight(Bs) <= 3)
    {

        for( int i = 0; i < 12; i = i + 1)
        {
            e[i] = 0;
        }
        for( int i = 0; i < 12; i = i + 1)
        {
            e[i + 12] = Bs[i];
        }

        cout << "\n   Setting error vector as e = (0,(B^T*s)^T).";
        cout << "\n\n";
        decode( r, e, stepCounter);
        cout << "\n\n\n\n";
        return 0;
    }

    cout << "\n   The weight of B^T*s exceeds 3.\n   Proceeding to step 6...\n";

    // Step 6: If w(B^T*s + r_i^T) <= 2 for some r_i (row of B), then set e = (x^(i), (B^T*s)^T + r_i) and decode r to r-e
    cout << "\n\n------------------------Step 6------------------------\n";
    stepCounter = 6;
    int BsPlusR[12]; // Stores the vector B^T*s + r_i^T
    columnTracker = -1;

    cout << "   Computing w(B^T*s+r_i^T) for rows r_i of B...\n";
    for (int i = 0; i < 12; i = i + 1)
    {
        for (int j = 0; j < 12; j = j + 1 )
        {
            BsPlusR[j] = ( Bs[j] + B[i][j] ) % 2;
        }
        if (weight(BsPlusR) <= 2)
            {
                columnTracker = i;
                break;
            }
    }


    if (columnTracker >= 0)      // If a column was found, do this stuff...
    {
        // Set the error vector:
        for (int i = 0; i < 24; i = i + 1 )
        {
            if ( i < 12 && i == columnTracker )
                e[i] = 1;
            else if (i < 12 && i != columnTracker)
                e[i] = 0;
            else if (i >= 12)
                e[i] = BsPlusR[i - 12];
        }
        cout << "\n   Row " << columnTracker + 1 << " gives a vector B^T * s + r_i^T of weight <= 2. Setting i = " << columnTracker + 1 << ".";
        cout << "\n   Setting error vector as e = ( x^(" << columnTracker + 1 << "), (B^T*s)^T + r_" << columnTracker + 1 << " ).";
        cout << "\n\n\n";
        decode( r, e, stepCounter);
        cout << "\n\n\n\n";
        return 0;
    }

    cout << "   No rows r_i were found such that w(B^T*s + r_i^T) <= 2.\n";



    // Step 7: At least 4 errors have occurred. Retransmit and restart.
    cout << "\n\n------------------------FAILURE------------------------\n";
    stepCounter = 7;

    cout << "\n   At least 4 errors have occurred in transmission. Retransmit and try again.\n\n\n";

    return 0;
}
