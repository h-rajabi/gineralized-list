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
        int size;
        node *first;
        void sub_print_list(node* head);
        void clear_list(node* head);
    public:
        generalizedList(){
            this->first=NULL;
            this->size=0;
        };
        ~generalizedList(){
            clear_list(first);
        }
        void setSize(){this->size = this->size+1; };
        void setFirst(node* f){this->first=f;};
        int getSize(){return this->size;};
        node* getFirst(){return this->first;};
        void add_head(char v);
        void add_poly(int e);
        void add_h(float c,int e);
        void par_print_list();
        void print_list(){
            sub_print_list(this->first);
        };

};

void read_from_file();
void sort_array();
bool compare_row(const vector<int>& row1, const vector<int>& row2){
    return row1.back() > row2.back();
};


int main()
{
    // read_from_file();
    // generalizedList testl;
    // node *x=new node(4,2);
    // node *y=new node(5,1);
    // node *z=new node(8,0);

    // testl.add_head('x');
    // node *f= testl.getFirst();
    // f->setLink(x);
    // x->setLink(y);
    // y->setLink(z);
    // testl.print_list();
    return 0;
}

void generalizedList::sub_print_list(node* head){
    
    char v = head->getVariable();
    while (head)
    {
        if(head->getTag() == 2){
            cout<<"(";
            sub_print_list(head->getDlink());
            cout << ")"<<v<<"^"<<head->getExp()<<"+";
        }
        else if (head->getTag() != 1){
            cout<<"+"<<head->getCoef()<<v<<"^"<<head->getExp();
        }
        head=head->getLink();
    }
    
}

void generalizedList::clear_list(node* head){
    while (head)
    {
        node* next=head->getLink();
        if (head->getTag() == 2)
        {
            clear_list(head->getDlink());
        }
        delete head;
        head=next;
    }
}

void generalizedList::add_head(char v){
    node* newNode=new node(v);
    if (!this->first)
    {
        this->first=newNode;
    }
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


