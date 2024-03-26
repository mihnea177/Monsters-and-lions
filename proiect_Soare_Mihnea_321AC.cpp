
// PROIECT POO --- Soare Mihnea Stefan

#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <regex>
#include <sstream>
using namespace std;

//class for every cast member to store information about name, role, type of make-up, type of diet
class Member{
    private:
        string name;
        string job;
        int monster_class;
        int diet;
    public:
        //setters
        void setData(string ImportedName,string ImportedJob){
            //importing name and job from CSV
            name = ImportedName;
            job = ImportedJob;

            //setting type of make-up for actors and extras
            regex pat1("actor");
            regex pat2("extra");
            monster_class = 0;
            if (regex_match(job, pat1) || regex_match(job, pat2))
                monster_class = rand() % (6-1)+1;

            //setting type of diet
            diet = rand() % (3-1)+1;
        }

        //getters
        string getName(){
            return name; 
        }
        string getJob(){
            return job; 
        }
        int getMonsterClass(){
            return monster_class;
        }
        int getDiet(){
            return diet;
        }
};

//randomizing name for extras
string randomName() {

    string fName[] = {"Ionescu", "Popescu", "Vlad", "Pascu", "Botescu", "Moraru", "Desliu", "Banica", "Schianu", "Capeleanu", "Bohiltea", "Dorobantu", "Mihaescu", "Nanu", "Bucur"};
    string lName[] = {"Catalin", "Alexandru", "Andrei", "Mihai", "Adrian", "Ion", "Raluca", "Georgeta", "Cristina", "Mihaela", "Ana", "Maria", "Ioana", "Lavinia", "Monica"};

    string name = "";

    name = name + fName[rand() % 15];
    name = name + ' ';
    name = name + lName[rand() % 15];

    return name;  
}

//code for importing data from CSV
void ImportData(Member member[], int &n){

    //import data from CSV
    ifstream f;
    f.open("wednesdayCast.csv");
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

        //getting name from line
        if((pos = line.find(delimiter)) != string::npos){
            inputName = line.substr(0,pos);
            line.erase(0, pos+delimiter.length());
        }

        //getting job from line
        inputJob = line.substr(0,line.length()-1);
        member[n].setData(inputName, inputJob);
        n++;

    }

    //creating extras
    for(i = 0; i < 132; i++){
        member[n+i].setData(randomName(), "extra");
    }

    n = n + i;
    f.close();
}

//class for creating a random menu; parent class for output
class Menu{
    public:
        void menu(){

            //types of soup for each type of diet
            string supa_t1[] = {"Ciorba de perisoare", "Ciorba de vacuta", "Ciorba de burta", "Supa cu taieti", "Supa crema de ciuperci", "Supa de rosii"};
            string supa_t2[] = {"Ciorba de legume", "Ciorba de varza", "Supa crema de ciuperci", "Supa de rosii"};
            string supa_t3[] = {"Ciorba de legume", "Bors de peste", "Supa crema de ciuperci", "Supa de rosii"};

            //types of main course for each type of diet
            string felprincipal_t1[] = {"Snitel cu cartofi", "Sarmale", "Chiftele", "Orez cu carne de porc"};
            string felprincipal_t2[] = {"Spanac", "Orez", "Salata", "Ciuperci"};
            string felprincipal_t3[] = {"Spanac cu peste", "Orez cu peste", "Salata", "Ciuperci"};

            //types of deserts for each type of diet
            string desert_t1[] = {"Savarina", "Papanasi", "Eclere", "Clatite", "Gogosi"};
            string desert_t2_t3[] = {"Salata de fructe", "Placinta cu mere", "Placinta cu dovleac", "Placinta cu visine"};

            //writing the randomized menu in a CSV file
            ofstream f;
            f.open("wednesdayFoodMenu.csv", ios::app);
            int i;
            for(i = 0; i < 3; i++){
                f << "Meniul pentru ziua: " << i+1 << " / Menu for day " << i+1 << ": \n\n";
                f << "--Meniu pentru persoanele care mananca orice / Menu for people able to eat anything: \n";
                f << "> Supa / Soup: " << supa_t1[rand()%6] << "\n"; \
                f << "> Fel principal / Main course: " << felprincipal_t1[rand()%4] << "\n"; 
                f << "> Desert: " << desert_t1[rand()%5] << "\n\n"; 

                f << "--Meniu pentru persoanele vegetarieni / Menu for vegetarians: \n";
                f << "> Supa / Soup: " << supa_t2[rand()%6] << "\n"; \
                f << "> Fel principal / Main course: " << felprincipal_t2[rand()%4] << "\n"; 
                f << "> Desert: " << desert_t2_t3[rand()%5] << "\n\n";

                f << "--Meniu pentru persoanele flexitarieni / Menu for flexitarians: \n";
                f << "> Supa / Soup: " << supa_t3[rand()%6] << "\n"; \
                f << "> Fel principal / Main course: " << felprincipal_t3[rand()%4] << "\n"; 
                f << "> Desert: " << desert_t2_t3[rand()%5] << "\n\n";
            }
            f.close();

        }
};

//class for calculating costs for each type of expenses
class Costs{
    private:
        double total_costs;
        double separate_costs;
    public:
        void cost(Member member[], int memberCount, int days){
            
            total_costs = 0;

            //writing costs for different number of days, for each expense, both in ENG and RO
            fstream f;
            f.open("wednesdayCosts.csv", ios::app);
            f << "Costurile pentru o perioada de " << days << " zile / " << "Costs for a period of " << days << " days \n\n";

            //transportation costs
            separate_costs = 0;
            int BusCount = memberCount/50 + ( memberCount % 50 != 0 );
            separate_costs = separate_costs + (BusCount * 5680) * 2;
            separate_costs = separate_costs/4.65;
            f << "--Costuri pentru transport / Transportation costs:  " << fixed << separate_costs << "$ \n";
            total_costs = total_costs + separate_costs;

            //accommodation costs
            separate_costs = 0;
            int DoubleRoom;
            int TripleRoom;
            TripleRoom = 132/3;
            DoubleRoom = (memberCount-132)/2 + ( (memberCount-132)%2 != 0 );
            separate_costs = separate_costs + (DoubleRoom*350 + TripleRoom*420) * days;
            separate_costs = separate_costs/4.65;
            f << "--Costuri pentru cazare / Accommodation costs:  " << fixed << separate_costs << "$ \n";
            total_costs = total_costs + separate_costs;

            //make-up costs
            separate_costs = 0;
            int i;
            for(i = 0; i < memberCount; i++){
                if(member[i].getMonsterClass() == 1) separate_costs = separate_costs + 230;
                if(member[i].getMonsterClass() == 2) separate_costs = separate_costs + 555;
                if(member[i].getMonsterClass() == 3) separate_costs = separate_costs + 345;
                if(member[i].getMonsterClass() == 4) separate_costs = separate_costs + 157;
                if(member[i].getMonsterClass() == 5) separate_costs = separate_costs + 55;
            }
            separate_costs = separate_costs * days;
            separate_costs = separate_costs/4.65;
            f << "--Costuri pentru machiaj / Make-up costs:  " << fixed << separate_costs << "$ \n";
            total_costs = total_costs + separate_costs;

            //food costs
            separate_costs = 0;
            for(i = 0; i < memberCount; i++){
                if(member[i].getDiet() == 1) separate_costs = separate_costs + 40;
                if(member[i].getDiet() == 2) separate_costs = separate_costs + 33;
                if(member[i].getDiet() == 3) separate_costs = separate_costs + 46;
            }
            separate_costs = separate_costs * days;
            separate_costs = separate_costs/4.65;
            f << "--Costuri pentru mancare / Food costs:  " << fixed << separate_costs << "$ \n";
            total_costs = total_costs + separate_costs;

            //drinks costs
            separate_costs = 0;
            float w_qty, c_qty, j_qty;
            w_qty = memberCount;
            c_qty = memberCount * 0.5;
            j_qty = memberCount * 0.8;
            w_qty = w_qty/2;
            if ((w_qty/2 - (int)w_qty/2) != 0)
                w_qty = (int)w_qty + 2;
            separate_costs = separate_costs + (w_qty * 6);
            if((c_qty - (int)c_qty) != 0)
                c_qty = (int)c_qty + 1;
            separate_costs = separate_costs + (c_qty * 30);
            j_qty = j_qty/2;
            if ((j_qty/2 - (int)j_qty/2) != 0)
                j_qty = (int)j_qty + 2;
            separate_costs = separate_costs + (j_qty * 8);
            separate_costs = separate_costs/4.65;
            f << "--Costuri pentru bautura / Drinks costs:  " << fixed << separate_costs << "$ \n";
            total_costs = total_costs + separate_costs;

            //renting costs
            separate_costs = 0;
            separate_costs = ( (days/10) * ((10*10000) * 0.98) ) + (days%10 * 10000);
            separate_costs = separate_costs/4.65;
            f << "--Costuri pentru inchirierea castelului / Castle renting costs:  " << fixed << separate_costs << "$ \n";
            total_costs = total_costs + separate_costs;

            f << "\n TOTAL: " << fixed << total_costs << "$\n\n\n\n";
            f.close();

        }
};

//class for writing the full cast in ENG and RO
class Output : public Costs, public Menu{
    public:

        //writing in ENG
        void cast(Member member[], int memberCount){
            ofstream f;
            f.open("/Users/mihnea/Documents/VSCODE/wednesdayFullCastENG.csv");
            int i;
            for(i = 0; i < memberCount; i++)
                f << member[i].getName() << ',' << member[i].getJob()  << "\n";
            f.close();
        }

        //writing in RO
        void cast(Member member[], int memberCount, string x){
            ofstream f;
            f.open("/Users/mihnea/Documents/VSCODE/wednesdayFullCastRO.csv");
            int i;
            for(i = 0; i < memberCount; i++)
                if(i >= 3 && i <= 7)
                    f << member[i].getName() << ',' << "scriitor" << "\n";
                else
                    if(i >= 8 && i <= 60)
                        f << member[i].getName() << ',' << member[i].getJob() << "\n";
                    else
                        if(i >= 61 && i <= 732)
                            f << member[i].getName() << ',' << "productie" << "\n";
                        else
                            if(i >= 733)
                                f << member[i].getName() << ',' << "figurant" << "\n";
                            else 
                                f << member[i].getName() << ',' << member[i].getJob() << "\n";
            f.close();
            }
};

int main(){
    
    //object of Member class for all cast members
    Member member[900];
    int memberCount = 0;

    //importing data
    ImportData(member, memberCount);

    //output data using Output class
    Output output;
    output.cast(member, memberCount);
    output.cast(member, memberCount, "RO");
    output.cost(member,memberCount, 30);
    output.cost(member,memberCount, 45);
    output.cost(member,memberCount, 60);
    output.cost(member,memberCount, 100);
    output.menu();
    
    return 0;
}
