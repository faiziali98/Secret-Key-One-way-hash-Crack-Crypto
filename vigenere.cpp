#include <iostream>
#include <string>
#include <fstream>
#include <vector> 
using namespace std;

float Count(string str, char c) {
    float n = 0;
    for (int i=0; i<str.length();i++) {
    	if (str[i] == c) n++;
    }
    return n;
}

void keyis(string k, int klen)
{
	float arr[26] = {8.2,1.5,2.8,4.3,12.7,2.2,2,6.1,7,0.2,0.8,4,2.4,6.7,7.5,1.9,0.1,6,6.3,9.1,2.8,1,2.4,0.2,2,0.1};
	float freq[26];
	string key = "";
	for (int i=0; i<klen; i++){
		string s = "";
		for (int n=i; n<k.length();){
			s = s + k[n];
			n += klen;
		}
		for (int n=0; n<26;n++){
			char c = 97+n;
			freq[n] = (Count(s, c)/s.length())*100;
		}
		float max=0; int mind = 0;
		for (int n=0; n<26; n++){
			float product = 0;
			for (int m=0; m<26; m++){
				product += arr[m]*freq[(m+n)%26];
			}
			if (n==0) max=product;
			else if (product>max){
				max = product;
				mind = n;
			}
		}
		char lm = 97+mind;
		key += lm;
	}
	cout<<"The key is..., wait for it \""<<key<<"\""<<endl;
}

int findKeyLength(string k){
	string s = k;
	int count = 0, len;
	cout<<"The collisions with possible lengths are \n"<<endl;
	cout<<"Length        "<<"Collisions"<<endl;
	for (int i=1;i<=100;i++){
		for (int n=0;n<k.length();n++){
			s[(n+i)%k.length()] = k[n];
		}
		count = 0;
		for (int n=0;n<k.length();n++){
			if (s[n]==k[n]) count++;
		}
		cout<<"   "<<i<<"             "<<count<<endl;	
	}
	cout<<"\nNow select the possible key length"<<endl; cin>>len;
	return len;
}

int main(){
	ifstream input("ciphertext.txt");
	string k;
	getline(input,k);
	keyis (k,findKeyLength(k));
}