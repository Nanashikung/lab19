#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstring>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string f, vector<string> &n, vector<int> &s, vector<char> &g){
    ifstream x(f);
    string l;
    do {
        getline(x, l);
        if (!l.length()) break;
        char name[30] = {};
        int scores[3] = {}, sum = 0;
        sscanf(l.c_str(), "%[^:]", name);
        sscanf(l.c_str()+strlen(name)+2, "%d %d %d", scores, scores+1, scores+2);
        for (int i = 0;i < 3; ++i) sum += scores[i];
        n.push_back(string(name));
        s.push_back(sum);
        g.push_back(score2grade(sum));
    } while(l.length());
    x.close();
}

void getCommand(string &c, string &k){
    string cmd;
    cout << "Please input your command: ";
    getline(cin, cmd);
    unsigned int j = 0;
    for (unsigned int i = 0; i < cmd.length(); ++i) {
        if (cmd[i] == ' ') {
            cmd[i] = '\0';
            j = i + 1;
            break;
        }
    }
    c = string(&cmd[0]);
    if (j) k = string(&cmd[j]);
}

void searchName(const vector<string> &n, const vector<int> &s, const vector<char> &g, const string k){
    cout << "---------------------------------\n";
    int size=n.size();
    bool checkname=false;
    for (int i = 0; i < size; ++i) {
        if (toUpperStr(n[i]) == k) {
            cout << n[i] << "'s score = " << s[i] << endl;
            cout << n[i] << "'s grade = " << g[i] << endl;
            checkname=true;
        }
        
        }

    if (!checkname) cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
}

void searchGrade(const vector<string> &n, const vector<int> &s, const vector<char> &g, const string k){
    cout << "---------------------------------\n";
    int size=g.size();
    for (int i = 0; i < size; ++i) {
        if (g[i] == k[0]) {
            cout << n[i] << " (" << s[i] << ")\n";
        }
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
