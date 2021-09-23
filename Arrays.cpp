/* Arrays By Ryan Jarl
   Created on: Mar 26, 2021
   This program accepts an input file (mp5input.txt)
   that contains data that consists of a keyword, and
   several lines of random phrases that are decrypted 
   and encrypted, with a letter that tells the program
   whether to decrypt or encrypt the statement. Doing
   so by utilizing arrays and strings, the results are 
   then printed to an output file (mp5output.txt).*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void cryption(ifstream&, ofstream&, string);
void printColSep(ofstream&);

int main()
{
	string keyword = "";
	ifstream input;
	ofstream output;
	input.open("mp5input.txt");
	output.open("mp5output.txt");
	input >> keyword;
	cryption(input, output, keyword);
	input.close();
	output.close();
}
void cryption(ifstream& input, ofstream& output, string keyword){
	int i;
	int j;
	int index;
	string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXY";
	string keyalph;
	string encstr;
	string decstr;
	char special = 'z';
	char crypttype;
	const int row = 5;
	const int column = 5;
	char table[row][column];
	output << "Keyword Is: " << keyword << endl;
	for (i = 0; i < keyword.length(); i++){
		for (j = 0; j < i; j++){
			if (keyword[i] == keyword[j]){
				keyword.erase(j, 1);
			}
		}
	}
	for (i = 0; i < keyword.size(); i++){
		for (j = 0; j < alphabet.length(); j++){
			if (keyword[i] == alphabet[j]){
				alphabet.erase(j, 1);
			}
		}
	}
	keyalph = keyword.append(alphabet);
	index = 0;
	output << endl;
	for (i = 0; i < row; i++){
		output << i << " ";
		for (j = 0; j < column; j++){
			table[i][j] = keyalph[index];
			index++;
		}
	}
	output << endl;
	printColSep(output);
	for (i = 0; i < 5; i++){
		output << i << " ";
		for (j = 0; j < 5; j++){
			output << "| " << table[i][j] << ' ';
		}
		output << endl;
		printColSep(output);
	}
	output << "**************************************************************************************" << endl;
	while (!input.eof()){
		input >> crypttype;
		if (crypttype == 'D'){
			getline(input, decstr);
			decstr = decstr.substr(1, decstr.size());
			output << decstr << endl;
			for (i = 0; i < 5; i++){
				for (j = 0; j < 5; j++){
					for (index = 0; index < decstr.length(); index++){
						if (decstr[index] == table[i][j]){
							decstr[index] = tolower(table[j][i]);
						}
					}
				}
			}
			output << "Decrypts To: " << endl << decstr << endl;
			output << "**************************************************************************************" << endl;
		}
		else if (crypttype == 'E'){
			getline(input, encstr);
			encstr = encstr.substr(1, encstr.size());
			output << encstr << endl;
			for (i = 0; i < 5; i++){
				for (j = 0; j < 5; j++){
					for (index = 0; index < encstr.length(); index++){
						if (encstr[index] == tolower(table[i][j])){
							encstr[index] = (table[j][i]);
						}
		else if (encstr[index] == tolower(special)){
			encstr[index] = toupper(special);
						}
					}
				}
			}
			output << "Encrypts To: " << endl << encstr << endl;
			output << "**************************************************************************************" << endl;
		}
	}
}
void printColSep(ofstream& output){
	for (int i = 0; i < 21; i++){
		output << "-";
	}
	output << endl;
}
