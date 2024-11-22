#include <iostream>
using namespace std;

int main()
{
    int x;
    cin>>x;
    cout << "Hello World!\n";
    return 0;
}


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
    generalizedList(){ size +=1; };
    
};

