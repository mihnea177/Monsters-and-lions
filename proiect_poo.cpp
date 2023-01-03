// PROIECT POO --- Soare Mihnea Stefan 321AC

#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <regex>
#include <sstream>
using namespace std;

class Member{
    private:
        string name;
        string job;
        int monster_class;
        int diet;
    public:
        void setData(string ImportedName,string ImportedJob){
            name = ImportedName;
            job = ImportedJob;
            regex pat1("actor");
            regex pat2("extra");
            monster_class = 0;
            if (regex_match(job, pat1) || regex_match(job, pat2))
                monster_class = rand() % (6-1)+1;
            diet = rand() % (3-1)+1;
        }
        string getName() { return name; }
        string getJob() { return job; }
        int getMonsterClass() { return monster_class; }
        int getDiet() { return diet; }
        ~Member();
};

string randomName() {

    string fName[] = {"Ionescu", "Popescu", "Vlad", "Pascu", "Botescu", "Moraru", "Desliu", "Banica", "Schianu", "Capeleanu", "Bohiltea", "Dorobantu", "Mihaescu", "Nanu", "Bucur"};
    string lName[] = {"Catalin", "Alexandru", "Andrei", "Mihai", "Adrian", "Ion", "Raluca", "Georgeta", "Cristina", "Mihaela", "Ana", "Maria", "Ioana", "Lavinia", "Monica"};

    string name = "";

    name = name + fName[rand() % 15];
    name = name + ' ';
    name = name + lName[rand() % 15];

    return name;  
}

void ImportData(Member member[], int &n){

    //import data from CSV
    ifstream f;
    f.open("/Users/mihnea/Documents/VSCODE/wednesdayCast.csv");
    try{
        if(!f)
            throw 99999;
    }
    catch(int err){
        cerr << "NU SE POATE ACCESA FISIERUL" << endl;
    }
    
    string line = "";
    string inputName, inputJob;
    int i = 0;
    string delimiter = ",";
    size_t pos = 0;

    //separating lines from CSV file
    while(getline(f,line)){

        if((pos = line.find(delimiter)) != string::npos){
            inputName = line.substr(0,pos);
            line.erase(0, pos+delimiter.length());
        }
        inputJob = line.substr(0,line.length()-1);
        member[n].setData(inputName, inputJob);
        n++;
    }

    for(i = 0; i < 132; i++){
        member[n+i].setData(randomName(), "extra");
    }
    
    n = n + i;

    f.close();
}

void ExportCastCSV(Member member[], int n){

    ofstream f;
    f.open("/Users/mihnea/Documents/VSCODE/wednesdayFullCast.csv");
    int i;
    for(i=0; i<n; i++)
        f << member[i].getName() << ',' << member[i].getJob() << ',' << member[i].getDiet() << "\n";
    f.close();
}

long TransportationCosts(int n){

    int BusCount = n/50 + ( n % 50 != 0 );
    return (BusCount * 5680) * 2;
}

long AccommodationCosts(int n, int days){

    int DoubleRoom;
    int TripleRoom;
    int rest;

    TripleRoom = 132/3;
    DoubleRoom = (n-132)/2 + ( (n-132)%2 != 0 );

    return (DoubleRoom*350 + TripleRoom*420) * days;
}

long MakeupCosts(Member member[], int n, int days){

    int i;
    long costs = 0;
    for(i=0; i<n; i++){
        if(member[i].getMonsterClass() == 1) costs = costs + 230;
        if(member[i].getMonsterClass() == 2) costs = costs + 555;
        if(member[i].getMonsterClass() == 3) costs = costs + 345;
        if(member[i].getMonsterClass() == 4) costs = costs + 157;
        if(member[i].getMonsterClass() == 5) costs = costs + 55;
    }
    return costs * days;
}

long FoodCosts(Member member[], int n, int days){

    int i;
    long costs = 0;
    for(i=0; i<n; i++){
        if(member[i].getDiet() == 1) costs = costs + 40;
        if(member[i].getDiet() == 2) costs = costs + 33;
        if(member[i].getDiet() == 3) costs = costs + 46;
    }
    return costs * days;
}

float DrinksCosts(int n, int days){

    float w_qty, c_qty, j_qty;
    w_qty = n;
    c_qty = n * 0.5;
    j_qty = n * 0.8;
    long costs = 0;

    w_qty = w_qty/2;
    if ((w_qty/2 - (int)w_qty/2) != 0)
        w_qty = (int)w_qty + 2;
    costs = costs + (w_qty * 6);

    if((c_qty - (int)c_qty) != 0)
        c_qty = (int)c_qty + 1;
    costs = costs + (c_qty * 30);

    j_qty = j_qty/2;
    if ((j_qty/2 - (int)j_qty/2) != 0)
        j_qty = (int)j_qty + 2;
    costs = costs + (j_qty * 8);

    return costs;
}

int main(){
    
    Member member[900];
    int memberCount = 0;
    ImportData(member, memberCount);
    ExportCastCSV(member, memberCount);

    int days = 10;

    cout << TransportationCosts(memberCount) << "\n";
    cout << AccommodationCosts(memberCount, days) << "\n";
    cout << MakeupCosts(member, memberCount, days) << "\n";
    cout << FoodCosts(member, memberCount, days) << "\n";
    cout << DrinksCosts(memberCount, days) << "\n";

    return 0;
}