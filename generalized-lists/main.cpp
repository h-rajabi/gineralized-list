#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

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
        void setTag(int t){this->tag=t;}
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

struct ge
{
    node* head;
    int size;
};

class generalizedList
{
    private:
        int size;
        node *first;
        void sub_print_list(node* head);
        void clear_list(node* head);
        int sub_dept_list(node* head);
        node* sub_find_node(node* head, int c, int e, char v);
        node* sub_find_before_node(node* head, int c, int e, char v);
        void sub_multiplication(node *head,int c);
        int sub_amount_list(node* head, vector<int>& v, int d);
    public:
        generalizedList(){
            this->first=NULL;
            this->size=0;
        };
        ~generalizedList(){
            clear_list(first);
        }
        void setSize(int s){this->size =s; };
        void setFirst(node* f){this->first=f;};
        int getSize(){return this->size;};
        node* getFirst(){return this->first;};
        void add_head(char v);
        void add_poly(int e);
        void add_h(float c,int e);
        void print_list(){
            sub_print_list(this->first);
        };
        int dept_list(){
            return sub_dept_list(this->getFirst());
        }
        node* find_node(int c,int e,char v){
            return sub_find_node(this->first, c, e, v);
        }
        void multiplication(int c){
            sub_multiplication(this->first,c);
        }
        void delete_node(int c, int e, char v);
        void amount_list();
};

ge read_from_file(string f);
void sort_array();
bool compare_row(const vector<int>& row1, const vector<int>& row2){
    return row1.back() > row2.back();
};
void create_list(vector<vector<int>>& a,node* head,int r,int c);
node* find_current_node(node* first,int e);
node* create_current_row(node* first, int e);
void create_current_row3(node* first,int c,int e);
void equal_list(node* head1,node* head2);

vector<char> varray={'x','y','z','i','e','f','g','h'};

int main()
{
    generalizedList* obj1=new generalizedList();
    ge result=read_from_file("in.txt");
    obj1->setFirst(result.head);
    obj1->setSize(result.size);
    cout<<"-----------------------\n";
    obj1->print_list();
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

int generalizedList::sub_dept_list(node* head){
    int dept =0;
    while (head)
    {
        if (head->getTag()==2)
        {
            int dp=sub_dept_list(head->getDlink());
            dept = max(dept,dp);
        }
        head=head->getLink();
    }
    return dept;
}

/*
void generalizedList::sub_multiplication(node* head,int c){
    if (!head) return; 

    if (head->getTag() == 3) {
        head->setCoef(head->getCoef() * c);
    }
    sub_multiplication(head->getDlink(), c);

    sub_multiplication(head->getLink(), c);
}
*/

void generalizedList::sub_multiplication(node* head, int c) {
    while (head) {
        if (head->getTag() == 2) {
            if (head->getDlink()) {
                sub_multiplication(head->getDlink(), c);
            }
        }
        else if (head->getTag() == 3) {
            head->setCoef(head->getCoef() * c);
        }
        head = head->getLink();
    }
}

node* generalizedList::sub_find_node(node* head, int c, int e, char v) {
    char x = head->getVariable();
    while (head) {
        if (x==v)
        {
            if (c==0)
            {
                if (head->getTag()==2)
                {
                    if (head->getExp() == e) return head;
                }
            }else
            {
                if (head->getTag()==3)
                {
                    if (head->getCoef()==c && head->getExp()==e) return head;
                }
            }
        }else
        {
            if (head->getTag()==2)
            {
                return sub_find_node(head->getDlink(),c,e,v);
            }
        }
        head = head->getLink();
    }
    return nullptr; 
}

void generalizedList::delete_node(int c, int e, char v){
    node *t=sub_find_before_node(this->getFirst(),c,e,v);
    if (t) {
        node* temp=t->getLink();
        t->setLink(temp->getLink());
        clear_list(temp->getDlink());
        delete temp;
        cout<<"done"<<endl;
    }
    else cout<< "not find"<<endl;
}

node* generalizedList::sub_find_before_node(node* head, int c, int e, char v) {
    char x = head->getVariable();
    while (head->getLink()) {
        if (x==v)
        {
            if (c==0)
            {
                if (head->getLink()->getTag()==2)
                {
                    if (head->getLink()->getExp() == e) return head;
                }
            }else
            {
                if (head->getLink()->getTag()==3)
                {
                    if (head->getLink()->getCoef()==c && head->getLink()->getExp()==e) return head;
                }
            }
        }else
        {
            if (head->getLink()->getTag()==2)
            {
                return sub_find_node(head->getLink()->getDlink(),c,e,v);
            }
        }
        head = head->getLink();
    }
    return nullptr; 
}

void generalizedList::amount_list(){
    int s=this->getSize();
    vector<int> narray(s);
    for (int i = 0; i < s ; i++)
    {
        cout<<"enter "<<varray[i]<<":";
        cin>>narray[i];
    }
    int sum =sub_amount_list(this->getFirst(),narray,s);
    cout<<"amount list for ";
    for (int i = 0; i < s; i++)
    {
        cout<<varray[i]<<":"<<narray[i]<<" ";
    }
    cout<<" is: "<<sum<<endl;
}

int generalizedList::sub_amount_list(node* head, vector<int>& v, int d){
    int a =v[d-1];
    int sum=0;
    while (head)
    {
        if (head->getTag()==2)
        {
            sum=sum+(pow(a,head->getExp()) * sub_amount_list(head->getDlink(),v,d-1));
        }else if (head->getTag()==3)
        {
            sum=sum+(pow(a,head->getExp())*head->getCoef());
        }
        head=head->getLink();
    }
    return sum;
}

ge read_from_file(string f){
    ifstream InFile(f);
    if(!InFile) {cout<<"error! :can not open file partner\n";}
    ge m;
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
    // sort(farray.begin(),farray.end(),compare_row);
    node *head=new node(varray[numC-1]);
    
    create_list(farray, head, numR, numC);
    m.head=head;
    m.size=numC;
    return m;
}

node* find_current_node(node* first,int e){
    if (first->getExp() == e)
    {
        return first;
    }
    
    while (first->getLink())
    {
        if (first->getExp() == e)
        {   
            return first;
        }
        first = first->getLink();
    }
    if (first->getExp() == e)
    {
        return first;
    }
    first->setLink(new node(e));
    return first->getLink();
}

node* create_current_row(node* first, int e){
    if (first->getLink())
    {   
        return find_current_node(first->getLink(),e);

    }else
    {   
        first->setLink(new node(e));
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

void create_list(vector<vector<int>>& a, node* head, int r, int c){
    node* temp=nullptr;
    node* tail=nullptr;
    for (int i = 0; i < r; i++)
    {
        tail=head;
        for (int j = c; j >= 1; j--)
        {
            if (j>1)
            {                   
                if (tail->getVariable() == varray[j-1])
                {   
                    
                    temp = create_current_row(tail,a[i][j]);
                    
                }else
                {
                    if (temp->getDlink())
                    {
                        tail=temp->getDlink();
                    }else
                    {
                        temp->setDlink(new node(varray[j-1]));
                        tail=temp->getDlink();
                    }
                    temp=create_current_row(tail,a[i][j]);
                }
                // برای برسی اینکه ایا باید تگ ۳ شود یا خیر 
                // تنها زمانی اتفاق میافتد که گره ما زیر مجموعه نداشته باشد 
                if (!temp->getDlink())
                {
                    bool t=false;
                    for (int k = j-1; k >= 1; k--)
                    {
                        if (a[i][k] != 0)
                        {
                            t= true;
                            break;
                        }
                    }
                    if (!t)
                    {
                        temp->setTag(3);
                        temp->setCoef(a[i][0]);
                    }
                    
                }
                
            }else
            {
                if (temp->getDlink())
                {
                    tail=temp->getDlink();
                }else
                {
                    temp->setDlink(new node(varray[j-1]));
                    tail=temp->getDlink();
                }
                create_current_row3(tail,a[i][j-1],a[i][j]);                
            }
        }
    }
}

bool equal_list(node* head1,node* head2){
    if (!head1 || !head2) return false;
    bool temp=true;
    while (head1 && head2)
    {   
        if(head1->getTag()!=head2->getTag()) return false;
        else if (head1->getTag()==1 && head2->getTag()==1)
            if (head1->getVariable() != head2->getVariable()) return false;
        else if (head1->getTag()==2 && head2->getTag() == 2)
        {
            if(head1->getExp != head2->getExp()) return false;
            temp = equal_list(head1->getDlink(),head2->getDlink());
        }else if (head1->getTag()==3 && head2->getTag()==3)
        {
            if(head1->getCoef() != head2->getCoef() || head1->getExp()!=head2->getExp()) return false;
        }
        if (!temp) return false;
        head1=head1->getLink();
        head2=head2->getLink();
    }

    if (!head1 && !head2) return true;
    return false;
}