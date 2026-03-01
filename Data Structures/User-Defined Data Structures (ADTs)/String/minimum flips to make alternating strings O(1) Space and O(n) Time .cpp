#include <iostream>
#include <string>
#include <vector>
using namespace std;
int minOperations(string s) 
{
        int n = s.length();
        // flips_pattern1 corresponds to pattern: 010101...
        // flips_pattern2 corresponds to pattern: 101010...
        int flips_pattern1 = 0;
        int flips_pattern2 = 0;
        for (int i = 0; i < n; i++) 
        {
            // Even index
            if (i % 2 == 0) 
            {
                // Pattern 1 expects ’0’, Pattern 2 expects ’1’
                if (s[i] != '0') flips_pattern1++;
                if (s[i] != '1') flips_pattern2++;
            }
            // Odd index
            else 
            {
                // Pattern 1 expects ’1’, Pattern 2 expects ’0’
                if (s[i] != '1') flips_pattern1++;
                if (s[i] != '0') flips_pattern2++;
            }
        }
    
    return min(flips_pattern1, flips_pattern2);        
}
int main()
{
    string s;
    cout<<"Enter string : ";
    getline(cin,s);
    int x = minOperations(s);
    cout<<"Operations : "<<x<<endl;
    return 0;
}
