#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


class node
{
    private:
        char variable;
        float coef;
        int exp,tag;
        node *link;
        node *dlink;
    public:
        node(char v){
            this->variable=v;
            this->tag=1;
            this->link=NULL;
            this->dlink=NULL;
        }
        node(int e){
            this->exp=e;
            this->tag=2;
            this->link=NULL;
            this->dlink=NULL;
        }
        node(float c,int e){
            this->coef=c;
            this->tag=3;
            this->exp=e;
            this->link=NULL;
            this->dlink=NULL;
        }
        void setVariable(char v){ this->variable=v; }
        void setCoef(float c){ this->coef=c; }
        void setEcp(int e){ this->exp=e; }
        void setLink(node *l){ this->link=l; }
        void setDlink(node *dl){ this->dlink=dl; }
        char getVariable(){return this->variable;}
        float getCoef(){return this->coef;}
        int getExp(){return this->exp;}
        int getTag(){return this->tag;}
        node* getLink(){return this->link;}
        node* getDlink(){return this->dlink;}
};

class generalizedList
{
    private:
        int size=0;
        node *first=NULL;
    
    public:
        generalizedList();
        void par_print_list();
        void print_list();

};

void read_from_file();
void sort_array();
bool compare_row(const vector<int>& row1, const vector<int>& row2){
    return row1.back() > row2.back();
};


int main()
{
    read_from_file();
    return 0;
}

void read_from_file(){
    ifstream InFile("in.txt");
    if(!InFile) {cout<<"error! :can not open file partner\n";}
    int numC,numR;
    InFile >> numC >> numR;
    vector<vector<int>> farray(numR,vector<int>(numC+1));
    vector<char> variable={'x','y','z','i','e','f','g','h'};
    for (int i = 0; i < numR; i++)
    {
        for (int j = 0; j < numC+1; j++)
        {
            InFile>>farray[i][j];
        }
    }
    
    InFile.close();

    for (int i = 0; i < numR; i++)
    {
        for (int j = 0; j < numC+1; j++)
        {
            cout<<farray[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"--------------*-------------"<<endl;
    
    sort(farray.begin(),farray.end(),compare_row);
    
    for (int i = 0; i < numR; i++)
    {
        for (int j = 0; j < numC+1; j++)
        {
            cout<<farray[i][j]<<"\t";
        }
        cout<<endl;
    }

    

}


