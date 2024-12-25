/*
Login Details:
ID: MMS
Password: 123
*/
#include<fstream>
#include<iostream>
#include<string>
#include<iomanip>
#define A 2000
using namespace std;
class attend{
	public:
	string adate;
	string lunch;
	string dinner;
	string both;
	attend *link;
};

class node {
	public:
	string name ;
	string phoneno;
	string date;
	int t;
	int amount;
	int pamount;
	int lcount=0;
	int dcount=0;
	node *next;
	attend *a=NULL;

};
class mess{
	node *head;
	attend *ahead;
public:
	mess();
    void save();
	void insert();
	void display();
	void del();
	void dspattend(node *);
	void dsp(node *m);
	void getamount(node *temp);


};
mess::mess(){

	head=NULL;
	ahead=NULL;



}
void mess::insert(){
	int a=0,b=0;
	node *temp;
	temp=new node;
	cout<<endl;
	cout<<"                            Enter Customer Details \n"<<endl;
	cout<<"Enter name of Customer->";
	cin.ignore();
	getline(cin,temp->name);
	//cin>>temp->name;
	cout<<"Enter phone number->";
	cin>>temp->phoneno;

	do
	{
		if(a>0)
		{
			cout<<"Please re-enter your choice \n";
		}
	cout<<"Enter the timing (1.lunch 2.dinner 3.both)";
	cin>>temp->t;
	a++;
	}while(temp->t>3);

	cout<<"Enter Date of joining mess->";
	cin>>temp->date;


	do
	{
		if(b>0)
		{
			cout<<"Please pay the minimum amount"<<endl;
		}
		getamount(temp);
		b++;
	}while(temp->amount<500);

	temp->next=NULL;
	if(head==NULL){
		head=temp;
	}
	else{
		node *p;
		p=head;

		while(p->next!=NULL){
			p=p->next;
		}
		p->next=temp;
	}
}
void mess :: getamount(node *temp)
{

	cout<<"Enter Amount paid->";
		cin>>temp->amount;

}

void mess::save()
{

    ofstream data;
    data.open("Report.txt",ios::app);
    node* temp=head;
   
	
    data<<"                 Customer Details \n"<<endl;
    data<<"______________________________________________________________________________________________________________"<<endl;
    data<<left<<setw(15)<<"Customer name";
    data<<right<<setw(15)<<"Phone no";
    data<<right<<setw(15)<<"Date";
    data<<right<<setw(15)<<"Amount";
    data<<right<<setw(15)<<"Total lunch";
    data<<right<<setw(15)<<"Total dinner";
    data<<right<<setw(15)<<"Pending amount"<<endl;
    data<<"_______________________________________________________________________________________________________________"<<endl;
	
	
	
    while(temp!=NULL){
        data<<left<<setw(15)<<temp->name;
        data<<right<<setw(15)<<temp->phoneno;
        data<<right<<setw(15)<<temp->date;
        data<<right<<setw(15)<<temp->amount;
        data<<right<<setw(15)<<temp->lcount;
        data<<right<<setw(15)<<temp->dcount;
        switch(temp->t)
        {
        	case 1:
        		data<<right<<setw(15)<<((A/2)-temp->amount)<<endl;
        		break;
        	case 2:
				data<<right<<setw(15)<<((A/2)-temp->amount)<<endl;
				break;
			case 3:
			    data<<right<<setw(15)<<((A)-temp->amount)<<endl;	
        		break;
		}
        
        temp=temp->next;
    }
}




void mess::display(){
	node *p;
	char N;
	string mname;
	if(head==NULL)
	{
			cout<<"Customer list is Empty "<<endl;
			return;
	}

	else{

		cout<<"1:To display All customers details "<<endl;
		cout<<"2:To Display Particular customer Details "<<endl;
		cin>>N;
		switch(N){
			case '1':
			{
				p=head;
				cout<<endl;
				cout<<"                       Customer Details \n"<<endl;
				cout<<"______________________________________________________________________________"<<endl;
				cout<<left<<setw(15)<<"Customer name";
				cout<<right<<setw(15)<<"Phone no";
				cout<<right<<setw(15)<<"Joining Date";
				cout<<right<<setw(15)<<"Amount"<<endl;
				cout<<"______________________________________________________________________________"<<endl;

				while (p!=NULL)
				{

				dsp(p);
				//data << p->name << "  " << p->amount;
				cout<<endl<<"------------------------------------------------------------------------------"<<endl;
				p=p->next;

				}
				break;
			}
			case '2':
				{
				cout<<"Enter name to find Details ->";
				cin>>mname;
				p=head;
				while(p!=NULL)
				{
					if(p->name==mname)
					{
						cout<<endl;
						cout<<"                 Customer Details \n"<<endl;
						cout<<"______________________________________________________________________________"<<endl;
						cout<<left<<setw(15)<<"Customer name";
						cout<<right<<setw(15)<<"Phone no";
						cout<<right<<setw(15)<<"Date";
						cout<<right<<setw(15)<<"Amount"<<endl;
						cout<<"______________________________________________________________________________"<<endl;

						dsp(p);
						break;
					}
					p=p->next;
				}
				if(p==NULL)
				cout<<"Customer not found "<<endl;
				break;
				}
	}}
}
void mess::dsp(node *m){
	//cout<<endl;
	cout<<left<<setw(15)<<m->name;
	cout<<right<<setw(15)<<m->phoneno;
	cout<<right<<setw(15)<<m->date;
	cout<<right<<setw(15)<<m->amount+m->pamount;
	cout<<endl<<endl;
	//data << m->name << "  " << m->phoneno;
	//cout<<"______________________________________________________________________________"<<endl;
	cout<<left<<setw(15)<<"Date  ";
	switch(m->t)
	{
		case 1:
			cout<<right<<setw(15)<<"Lunch "<<endl;
			break;
		case 2:
			cout<<right<<setw(15)<<"Dinner "<<endl;
			break;
		case 3:
		cout<<right<<setw(15)<<"Lunch";
		cout<<right<<setw(15)<<"Dinner "<<endl;
		break;
		default :
			cout<<"Entered wrong choice"<<endl;
			break;



	}


	//cout<<"______________________________________________________________________________"<<endl;
	dspattend(m);

}

void mess::dspattend(node *m)
{
	node *p;

	p=m;
	if(p->a==NULL){
		return;
	}
	attend *s;
	s=p->a;
	cout<<endl;
	while(s!=NULL){
		cout<<left<<setw(15)<<s->adate;
		switch(p->t)
		{
		case 1:
		cout<<right<<setw(15)<<s->lunch<<endl;
		break;

		case 2:
	 	cout<<right<<setw(15)<<s->dinner<<endl;

	break;
	case 3:
		cout<<right<<setw(15)<<s->lunch;
		cout<<right<<setw(15)<<s->dinner<<endl;
		break;
	}

	s=s->link;}

}

void mess::del(){
	string name;
	node *p,*d,*s;
	p=head;
	if (head==NULL)
	{
			cout<<"Customer List is Empty"<<endl;
			return;
	}

	cout<<"Enter Name to delete customer info->";
	cin>>name;

	s=p;
	while(p!=NULL)
	{
		if(p->name==name)
		{
			if(p==head)
			{
				head=NULL;
				d=p;
				delete p;
				cout<<"Successfully Deleted Info of Customer "<<name<<endl;
				
				return;

			}
			s->next=p->next;
			d=p;
			delete d;
			cout<<"Successfully Deleted Info of Customer "<<name<<endl;
			return;
		}
		s=p;
		p=p->next;
	}
	if(p==NULL)
	cout<<"Customer Not found \n";

}


int main (){
	mess mk;
	char N;
    string aid,apassword;
	string id,password;
	int count=1;
	
	id="MMS";
	password="123";
	cout<<"                                          * MESS MANAGEMENT SYSTEM *     \n\n ";
		
	cout<<"Enter the login ID : ";
	cin>>aid;
	cout<<"Enter the password : ";
	cin>>apassword;
	if(aid==id && apassword==password)
		{
	while(count==1)
	{
		cout<<endl<<endl;
		cout<<"Enter your choice :\n";
		cout<<"1:To Add new Customer\n"<<"2:To display customer info"<<endl<<"3:To delete customer\n";
		cout<<"4:To stop\n";
		cin>>N;
		switch(N){
			case '1':
				{
					mk.insert();
					break;
				}
			case '2':
				{
					mk.display();
					break;
				}
			case '3':
				{
					mk.del();
					break;
				}
			case '4':
				{
					count++;
					break;
				}
			default:
			{
				cout<<"You entered wrong choice "<<endl;
				break;

			}
		}
	}
	}
	else 
  	{
		if(aid!=id)
		{
			cout<<"Invalid login credentials ";	
		
		}
			
	}	
	mk.save();
	return 0;
}