// Badger
#include <iostream>
#include <regex>
#include <string>
#include <map>
#include <fstream>
#include "../rgb.h"

using namespace std;

map<string, rgb> regex_map = {
	//{"\\b(auto|double|int|struct|break|else|long|switch|case|enum|register|typedef|char|extern|return|union|const|float|short|unsigned|continue|for|signed|void|default|goto|sizeof|volatile|do|if|static|while|class)\\b", rgb(0, 0, 255)},
	{"\\b\\/\\/.*\\b", rgb(0, 100, 0)}, // Single line comments
	{"\\b\\/\\*.*\\*\\/\\b", rgb(0, 100, 0)}, // Multi line comments
	{"\\b(true|false)\\b", rgb(0, 0, 175)},			 // Boolean values
	{"\\b(\\d+)\\b", rgb(125, 125, 125)},			  // Numeric values
	{"\\b(if|else|while|for|do|switch)\\b", rgb(255, 0, 0)}, // Control flow keywords
	{"\\b(int|float|double|char|void)\\b", rgb(0, 150, 0)}, // Data type keywords
	{"\\b(return|break|continue|goto|const|constexpr)\\b", rgb(0, 100, 100)}, // Other keywords
	{"\\b(sizeof|static|extern|register)\\b", rgb(100, 50, 200)}, // Storage class specifiers
	{"\\b(inline|virtual|explicit|mutable|namespace)\\b", rgb(150, 100, 50)}, // Other specifiers
	{"\\b(this|new|delete|nullptr|operator)\\b", rgb(50, 150, 150)}, // Miscellaneous keywords
	{"\\b(const_cast|dynamic_cast|static_cast|reinterpret_cast)\\b", rgb(200, 100, 150)}, // Type cast operators
	{"\\b(asm|auto|bool|catch|char|class|const_cast|delete|double|dynamic_cast|explicit|export|extern|false|float|friend|inline|long|mutable|namespace|new|operator|private|protected|public|reinterpret_cast|short|signed|sizeof|static_cast|template|this|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|wchar_t)\\b", rgb(0, 0, 128)}, // C++ keywords
	{"\\b(alignas|alignof|and|and_eq|bitand|bitor|compl|concept|consteval|constexpr|constinit|co_await|co_return|co_yield|not|not_eq|or|or_eq|requires|xor|xor_eq)\\b", rgb(0, 0, 30)}, // C++20 keywords
	{"\\b(override|final|import|module|transaction|synchronized)\\b", rgb(0, 0, 10)}, // C++20 keywords
	{"\\b(export|module|import|requires|co_await|co_return|co_yield|concept|consteval|constinit)\\b", rgb(0, 0, 50)}, // C++20 keywords
	{"\\b(alignas|alignof|and|and_eq|asm|atomic_cancel|atomic_commit|atomic_noexcept|auto|bitand|bitor|bool|break|case|catch|char|char8_t|char16_t|char32_t|class|compl|concept|const|const_cast|consteval|constexpr|constinit|continue|co_await|co_return|co_yield|decltype|default|delete|do|double|dynamic_cast|else|enum|explicit|export|extern|false|float|for|friend|goto|if|inline|int|long|module|mutable|namespace|new|noexcept|not|not_eq|nullptr|operator|or|or_eq|private|protected|public|reflexpr|register|reinterpret_cast|requires|return|short|signed|sizeof|static|static_assert|static_cast|struct|switch|synchronized|template|this|thread_local|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|wchar_t|while|xor|xor_eq)\\b", rgb(0, 0, 75)}, // C++20 keywords
	{"\\b(#include|#define|#undef|#ifdef|#ifndef|#if|#else|#elif|#endif|#line|#error|#pragma)\\b", rgb(0, 0, 25)} // Preprocessor directives
};

void highlight(string str){
	for (auto it = regex_map.begin(); it != regex_map.end(); it++){
		regex reg(it->first);
		smatch matches;
		while (regex_search(str, matches, reg)){
			cout << matches.prefix().str();
			cout << (string)it->second << matches.str(1) << "\033[0m";
			str = matches.suffix().str();
		}
	}
	cout << str << endl;
}

string read_file(string filename){
	ifstream file(filename);
	string str;
	string file_contents;
	while (getline(file, str)){
		file_contents += str;
		file_contents.push_back('\n');
	}
	return file_contents;
}

int main(int argc,char** argv){
	if(argc>1){
		string file_contents = read_file(argv[1]);
		highlight(file_contents);
		return 0;
	}

	string str;
	while(cout<<(string)green+"> \033[0m"+(string)rgb(125,125,125)&&getline(cin,str)){
		cout<<"\033[0m";
		highlight(str);
	}
	return 0;
}
// FIXME: doesn't highlight most things in map