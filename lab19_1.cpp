#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

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

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source(filename);
    string textline;
    int a,b,c;
    while(getline(source,textline))
    {
        if(textline.find(':'))
        {
            names.push_back(textline.substr(0,textline.find(':')));
            sscanf(textline.substr(textline.find(':')+2).c_str(),"%d %d %d",&a,&b,&c);
            scores.push_back(a+b+c);
            grades.push_back(score2grade(a+b+c));
        }
    }
}

void getCommand(string & command,string & key){
    string x;
    cout << "Please input your command: ";
    getline(cin,x);
    if(x.find(' '))
    {
        command = x.substr(0,x.find(' '));
        key = x.substr(x.find(' ')+1);

    }
    else command = x;
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int count=0;
    cout << "---------------------------------\n";
    for(unsigned int i=0 ; i<names.size() ; i++)
    {
        if(toUpperStr(names[i]) == key)
        {
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            count++;
        }
    }
    if(count == 0) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int count=0;
    string x;
    cout << "---------------------------------\n";
    for(unsigned int i=0 ; i<grades.size() ; i++)
    {
        x = grades[i];
        if(x==key)
        {
            cout << names[i] << " (" << scores[i] << ")\n";
            count++;
        }
    }
    if(count == 0) cout << "Cannot found.\n";
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