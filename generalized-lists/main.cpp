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

class generalizedList
{
    private:
        int size;
        node *first;
        void sub_print_list(node* head);
        void clear_list(node* head);
        int sub_dept_list(node* head);
        node* sub_find_node(node* head, int c, int e, char v);
        void sub_multiplication(node *head,int c);
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
        int dept_list(){
            return sub_dept_list(this->getFirst());
        }
        node* find_node(int c,int e,char v){
            return sub_find_node(this->first, c, e, v);
        }
        void multiplication(int c){
            sub_multiplication(this->first,c);
        }
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
    cout<<endl;
    // node* term = obj1->find_node(1,9,'y');
    // if (term) {
    //     cout << "Found term with coefficient: " << endl;
    // } else {
    //     cout << "Term not found." << endl;
    // }
    // cout<<endl;
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
    while (head) {
        // اگر گره از نوع 1 (متغیر) است

        // // اگر گره از نوع 2 است (توان بدون ضریب)
        // if (head->getTag() == 2 && head->getExp() == e) {
        //     if (c==0) {
        //         return head; // اگر ضریب مهم نیست، گره پیدا شده است
        //     }
        //     // جستجو در زیرلیست گره
        //     if (head->getDlink()) {
        //         return sub_find_node(head->getDlink(), c, e, v);
        //     }
        // }

        // // اگر گره از نوع 3 است (توان و ضریب)
        // if (head->getTag() == 3 && head->getExp() == e) {
        //     if (c==0 || head->getCoef() == c) {
        //         return head; // گره با مشخصات پیدا شده است
        //     }
        // }

        // حرکت به گره بعدی
        if (head->getTag() == 1 && head->getVariable() == v) {
            // جستجو در زیرلیست
            return sub_find_node(head->getLink(), c, e, v);
        }
        
        if (head->getTag()==2)
        {
            
        }
        
        head = head->getLink();
    }
    return nullptr; // اگر گره پیدا نشد
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

void create_list(vector<vector<int>>& a,vector<char>& v,node* head,int r,int c){
    node* temp=nullptr;
    node* tail=nullptr;
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
                    temp->setDlink(new node(v[j-1]));
                    tail=temp->getDlink();
                }
                create_current_row3(tail,a[i][j-1],a[i][j]);                
            }
        }
    }
}