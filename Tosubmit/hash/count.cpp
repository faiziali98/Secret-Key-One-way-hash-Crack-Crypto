#include <iostream>
#include <string>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream input("h1.txt");
    string k;string f;
    getline(input,k);
    input.close();
    input.open("h2.txt");
    getline(input,f);

    int count = 0;
    for (int n=0; n<k.length(); n++){
        if (f[n]==k[n]) count++;
    }
    cout<<count<<endl;
}
