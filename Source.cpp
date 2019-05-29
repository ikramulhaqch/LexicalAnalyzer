#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>

using namespace std;

int** ArrayFromFile(int &count) {
	ifstream in("input.txt");
	string s;
	getline(in, s);
	count++;
	while (!in.eof()) {
		getline(in, s);
		if(s.length()>0)
		count++;
	}
	in.close();
	count--;
	int **arr = new int*[count];
	for (int i = 0; i < count; i++)
		arr[i] = new int[129];
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < 129; j++) {
			arr[i][j] = -1;
		}
	}
	string set;
	ifstream in1("input.txt");
	getline(in1, set);
	set += ' ';
	//changing AASCI of character set to ints.
	vector<int> charSet;
	int a = 0;
	s = "";
	for (int i = 0; i < set.length(); i++) {
		if (set[i] != ' ') {
			s += set[i];
		}
		else if (set[i] == ' ' && s!="") {
			a = stoi(s);
			if (a > 127)
				a = 128;
			charSet.push_back(a);
			s = "";
		}
	}
	string line;
	int k = 0;
	for (int i = 0; i < count; i++) {
		getline(in1, line);
		line += ' ';
		s = "";
		a=0,k=0;
		for (int j = 0; j < line.length(); j++) {
			if (line[j] != ' ') {
				s += line[j];
			}
			else if (line[j] == ' ' && s!="") {
				a = stoi(s);
				arr[i][charSet[k]] = a;
				k++;
				s = "";
			}
		}
	}
	in.close();
	return arr;
}

vector<vector<int> > Compressing(int **arr,int count,int map[]) {
	int inserted = 0;
	vector<vector<int> > trans;
	for (int i = 0; i < count; i++) {
		trans.push_back(vector<int>());
	}
	for (int i = 0; i < 129; i++) {
		bool same = false;
		int sameint = 0;
		for (int k = 0; k < inserted; k++) {
			for (int j = 0; j < count; j++) {
				if (arr[j][i] == trans[j][k]) {
					same = true;
					sameint = k;
				}
				else {
					same = false;
					sameint = -1;
					break;
				}
			}
			if (same) {
				break;
			}
		}
		if (!same) {
			int l = inserted;
			for (int j = 0; j < count; j++) {
				trans[j].push_back(arr[j][i]);
			}
			map[i] = inserted;
			inserted++;
		}
		else {
			int a = i;
			map[i] = sameint;
		}
	}
	return trans;
}

void transitionFunctionInFile(vector<vector<int> > trans,int map[]) {
	ofstream out("output.txt");
	for (int i = 0; i < trans.size(); i++) {
		for (int j = 0; j < trans[i].size(); j++) {
			out << setw(4) << trans[i][j];
		}
		out << endl;
	}
	for (int i = 0; i < trans[0].size(); i++) {
		out << i << " column is for: ";
		for (int j = 0; j < 129; j++) {
			if(map[j]==i)
				out << setw(4) << j;
		}
		out << endl;
	}
	out.close();

}

string readInputStream() {
	ifstream in("input_string.txt");
	string s;
	getline(in, s, (char)in.eof());
	in.close();
	return s;
}

void printLexeme(string token,int lsfs, int map[],vector<vector<int> > trans) {
	cout << "<F.S. " << trans[lsfs][map[128]] << ", ";
	for (int i = 0; i < token.length(); i++) {
		if (token[i] == '\n')
			cout << "\\n";
		else if (token[i] == '\r')
			cout << "\\r";
		else if (token[i] == '\t')
			cout << "\\t";
		else if (token[i] == '\b')
			cout << "\\b";
		else if (token[i] == '\f')
			cout << "\\f";
		else if (token[i] == '\v')
			cout << "\\v";
		else cout << token[i];
	}
	cout << " >\n";
}

void LexicalAnalyzer(vector <vector<int> > trans,int map[]) {
	int cur = 0,lsfs=-1,ls=0,rem=-1,forwd=0,line=0;
	string s = readInputStream();
	while (ls < s.length()) {
		int ind=0;
		bool escape = false;
		if (s[forwd] == 92) {
			escape = true;
			if (s[forwd + 1] == 'n') {
				ind = (int)'\n';
				line++;
			}
			else if (s[forwd + 1] == 'r')
				ind = (int)'\r';
			else if (s[forwd + 1] == 't')
				ind = (int)'\t';
			else if (s[forwd + 1] == 'b')
				ind = (int)'\b';
			else if (s[forwd + 1] == 'f')
				ind = (int)'\f';
			else if (s[forwd + 1] == 'v')
				ind = (int)'\v';
			else escape = false;
			forwd++;
		}
		else ind = (int)s[forwd];
		int mappedInd = map[ind];
		cur = trans[cur][mappedInd];
		forwd++;
		if (cur!=-1 && trans[cur][map[128]] != -1) {
			if (s[forwd-1] == '\n')
				line++;
			lsfs = cur;
			rem = forwd - 1;
		}
		else if (cur == -1) {
			if (lsfs != -1) {
				string token = "";
				//lexeme Generation.
				for (int i = ls; i <= rem; i++) {
					token += s[i];
				}
				printLexeme(token,lsfs,map,trans);
				ls = rem + 1;
				forwd = rem + 1;
				cur = 0;
				lsfs = -1;
			}
			else {
				if (escape) {

					cout << "error " << s[ls]<<s[ls+1] << " line no " << line << endl;
					ls++;
					forwd = ls;
				}
				else cout << "error " << s[ls] << " line no " << line << endl;
				ls++;
				forwd = ls;
				cur = 0;
			}
		}
	}
}

int main() {
	int **x,count=0;
	x = ArrayFromFile(count);
	int map[129];
	vector<vector<int> > transitionFunction=Compressing(x, count,map);
	transitionFunctionInFile(transitionFunction, map);
	LexicalAnalyzer(transitionFunction,map);
	return 0;
}