//program to take in text string in command line and output the text in ascii art

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

//function to load ascii art from file (characters are separated by empty new lines)
//have char array and add every line of text file, including the newline character, to the array
//then when encountering an empty line, move on to the next index of the array and repeat
//return the char array
//example file:
/*
  ___       
 / _ \      
| | | |     
| |_| |     
 \___/      

 _
/ |         
| |         
| |         
|_|

_____ 
|___ \ 
  __) |
 / __/ 
|_____|
*/
string* load_ascii_art(string filename){
	ifstream file(filename);
	string* lines;
	string line;
	string txt="";
	int a=0;
	while(getline(file,line)){
		if(line.size()!=0){
			txt+=line+"\n";
		}
		else{
			lines[a]=txt;
		}
		a++;
	}
	return lines;
}

//function to take in character and return the ascii art of the character. numbers(0-9) are stored in "./#.txt"
//TODO: add spaces
string get_ascii_art(char c){
	string* num=load_ascii_art("./#.txt");
	if(c>='0' && c<='9'){
		return num[c-'0'];
	}
	else if(c>='a' && c<='z'){
		return load_ascii_art("./low.txt")[c-'a'];
	}
	else if(c>='A' && c<='Z'){
		return load_ascii_art("./cap.txt")[c-'A'];
	}
	else if(c>='!' && c<='/'){
		return load_ascii_art("./ascii.txt")[c-'!'];
	}
	else if(c>=':' && c<='@'){
		return load_ascii_art("./special.txt")[c-':'+7];
	}
	else if(c>='[' && c<='`'){
		return load_ascii_art("./special2.txt")[c-'['+14];
	}
	else if(c>='{' && c<='~'){
		return load_ascii_art("./special3.txt")[c-'{'+21];
	}
	else{
		return NULL;
	}
}

//function to take in a string and return the ascii art of the string
char** get_ascii_art(string s){
	char** ascii_art = new char*[5];
	for(int i=0;i<5;i++){
		ascii_art[i] = new char[s.size()*6];
	}
	for(int i=0;i<s.size();i++){
		string c = get_ascii_art(s[i]);
		if(c==""){
			continue;
		}
		for(int j=0;j<5;j++){
			for(int k=0;k<6;k++){
				ascii_art[j][i*6+k] = c[j*6+k];
			}
		}
	}
	return ascii_art;
}

int main(int argc,char** argv){
	if(argc!=2){
		cout<<"Usage: ./ascii_art <text>"<<endl;
		return 0;
	}
	cout<<load_ascii_art("./#.txt")[0]<<endl;
	char** ascii_art = get_ascii_art(argv[1]);
	cout<<ascii_art[0]<<endl;
	cout<<ascii_art[1]<<endl;
	cout<<ascii_art[2]<<endl;
	cout<<ascii_art[3]<<endl;
	cout<<endl;
	for(int i=0;i<strlen(argv[1]);i++){
		cout<<ascii_art[i];
	}
	cout<<endl;
	return 0;
}