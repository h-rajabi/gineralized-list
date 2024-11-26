#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


class node
{
    private:
        char variable;
        int coef;
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
        void setExp(int e){ this->exp=e; }
        void setLink(node *l){ this->link=l; }
        void setDlink(node *dl){ this->dlink=dl; }
        char getVariable(){return this->variable;}
        int getCoef(){return this->coef;}
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
        void print_list(){
            sub_print_list(this->first);
        };

};

node* read_from_file();
void sort_array();
bool compare_row(const vector<int>& row1, const vector<int>& row2){
    return row1.back() > row2.back();
};
void create_list(vector<vector<int>>& a,vector<char>& v,node* head,int r,int c);
node* find_current_node(node* first,int e);
node* create_current_row(node* first, int e);
void create_current_row3(node* first,int c,int e);
int main()
{
    generalizedList* obj1=new generalizedList();
    obj1->setFirst(read_from_file());
    cout<<"-----------------------\n";
    obj1->print_list();
    // node* head=obj1->getFirst();
    // cout<<head->getVariable()<<"^"<<head->getLink()->getExp()<<"(";
    // head=head->getLink()->getDlink();
    // cout<<head->getVariable()<<"^"<<head->getLink()->getExp()<<"(";
    // head=head->getLink()->getDlink();
    // cout<<head->getVariable()<<"^"<<head->getLink()->getExp()<<"("<<head->getLink()->getCoef()<<")";

    cout<<endl;
    return 0;
}

void generalizedList::sub_print_list(node* head){
    
    char v = head->getVariable();
    while (head) {
        if (head->getTag() == 2) {
            cout << "(";
            if (head->getDlink())
            {
            sub_print_list(head->getDlink());
            }else cout<<"error here";
            cout << ")"<<v << "^" << head->getExp();
        } else if (head->getTag() == 3) {
            cout << "+" << head->getCoef() << v<<"^" << head->getExp();
        }
        head = head->getLink();
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

node* read_from_file(){
    ifstream InFile("in.txt");
    if(!InFile) {cout<<"error! :can not open file partner\n";}
    int numC,numR;
    InFile >> numC >> numR;
    vector<vector<int>> farray(numR,vector<int>(numC+1));
    for (int i = 0; i < numR; i++)
    {
        for (int j = 0; j < numC+1; j++)
        {
            InFile>>farray[i][j];
        }
    }
    
    InFile.close();    
    sort(farray.begin(),farray.end(),compare_row);
    vector<char> varray={'x','y','z','i','e','f','g','h'};
    node *head=new node(varray[numC-1]);
    create_list(farray,varray,head,numR,numC);
    return head;
}

/*
void create_list(vector<vector<int>>& a,vector<char>& v,node* head,int r,int c){
    node *current=head;
    node *tail=nullptr;
    for (int i = 0; i < r; i++)
    {
        if (current->getTag() == 1)
        {
            current->setLink(new node(a[i][c]));
            current=current->getLink();
        }else if(current->getExp() != a[i][c])
        {
            current->setLink(new node(a[i][c]));
            current=current->getLink();
        }
        
        node *temp=nullptr;
        for (int j = c-1; j >= 1; j--)
        {   

            if (current->getDlink())
            {
                temp=current->getDlink();
            }else
            {
                temp = new node(v[j-1]);
                current->setDlink(temp);
            }
            
            if (temp->getLink())
            {   
                temp = temp->getLink();
                if (j>1)
                {   
                    if (temp->getExp() != a[i][j])
                    {
                        temp->setLink(new node(a[i][j]));  
                    }
                }else
                {   
                    if (temp->getDlink())
                    {
                        temp=temp->getDlink();
                        node* tail=temp->getLink();
                        while (tail->getLink())
                        {
                            if (tail->getExp() == a[i][j])
                            {   
                                tail->setCoef(tail->getCoef()+a[i][j-1]);
                                break;
                            }
                            else
                            {
                                tail=tail->getLink();
                            }
                        }
                        if (!tail->getLink())
                        {
                            tail->setLink(new node(a[i][j-1],a[i][j]));
                        }
                        
                    }else
                    {
                        temp->setDlink(new node(v[j-1]));
                        temp=temp->getDlink();
                        temp->setLink(new node(a[i][j-1],a[i][j]));
                    }
                }
            }else
            {
                if (j>1)
                {
                    temp->setLink(new node(a[i][j]));
                    temp=temp->getLink();   
                }else
                {   temp->setDlink(new node(v[j-1]));
                    temp=temp->getDlink();
                    temp->setLink(new node(a[i][j-1],a[i][j]));
                }
            }
        }
    }
}
*/

node* find_current_node(node* first,int e){
    if (first->getExp()== e)
    {
        return first;
    }
    
    while (first->getLink())
    {
        if (first->getExp() == e)
        {   
            // cout<<"find:" <<first<<endl;

            return first;
        }
        first = first->getLink();
    }

    first->setLink(new node(e));
    // cout<<"not find:"<<first<<endl;
    return first->getLink();
}
node* create_current_row(node* first, int e){
    if (first->getLink())
    {   
        // cout<<find_current_node(first->getLink(),e);
        return find_current_node(first->getLink(),e);

    }else
    {   
        first->setLink(new node(e));
        // cout<<"first is :"<<first->getVariable()<<"ad :"<<first->getLink()<<endl;
        return first->getLink();
    }
}
void create_current_row3(node* first,int c,int e){
    if (first->getLink())
    {   
        first=first->getLink();
        while (first->getLink())
        {
            if (first->getExp() == e)
            {   
                first->setCoef(first->getCoef()+c);
                return ;
            }
            first=first->getLink();                        
        }
        if (!first->getLink())
        {
            first->setLink(new node(c,e));
        }
    }else
    {
        first->setLink(new node(c,e));
    }
}

void create_list(vector<vector<int>>& a,vector<char>& v,node* head,int r,int c){
    node* temp=nullptr;
    node* tail=nullptr;
    // cout<<"ad head :"<<head<<endl;
    for (int i = 0; i < r; i++)
    {
        tail=head;
        for (int j = c; j >= 1; j--)
        {
            if (j>1)
            {
                if (tail->getVariable() == v[j-1])
                {   
                    
                    temp = create_current_row(tail,a[i][j]);
                }else
                {
                    if (temp->getDlink())
                    {
                        tail=temp->getDlink();
                    }else
                    {
                        temp->setDlink(new node(v[j-1]));
                        tail=temp->getDlink();
                    }
                    temp=create_current_row(tail,a[i][j]);
                }
            }else
            {
                if (temp->getDlink())
                {
                    tail=temp->getDlink();
                }else
                {
                    temp->setDlink(new node(v[j-1]));
                    tail=temp->getDlink();
                }
                create_current_row3(tail,a[i][j-1],a[i][j]);                
            }
        }
    }
}