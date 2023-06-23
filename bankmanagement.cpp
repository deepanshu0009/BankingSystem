// #include<iostream>
// #include<fstream>
// #include<cctype>
// #include<iomanip>
#include <bits/stdc++.h>
using namespace std;



class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
	char adhar_num[20];
public:
	void create_account();
	void giveloan();
	void repayloan();
	void show_account() const;
	void modify();
	void dep(int);
	void draw(int);
	void report() const;
	int retacno() const;
	int retdeposit() const;
	char rettype() const;
};

struct Loan {
    int acc_num;
    int adhar_num;
    float amount;
    float loan_left;
    int repay_time;
};

void account::create_account()
{
	system("CLS");
	cout<<"\n\t\t\tEnter the Account No. : ";
	cin>>acno;
	cout<<"\n\n\t\t\tEnter the Name of the Account holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\t\t\tEnter Type of the Account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\t\t\tEnter The Initial amount : ";
	cin>>deposit;
	cout<<"\n\n\t\t\tAccount Created..";
}

void account::show_account() const
{
	cout<<"\n\t\t\tAccount No. : "<<acno;
	cout<<"\n\t\t\tAccount Holder Name : ";
	cout<<name;
	cout<<"\n\t\t\tType of Account : "<<type;
	cout<<"\n\t\t\tBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\n\t\t\tAccount No. : "<<acno;
	cout<<"\n\t\t\tModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\t\t\tModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\t\t\tModify Balance amount : ";
	cin>>deposit;
}


void account::dep(int x)
{
	deposit+=x;
}

void account::draw(int x)
{
	deposit-=x;
}

void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}




void account::giveloan() {
	system("CLS");
    int acc_num;
    cout << "Enter Account Number: ";
    cin >> acc_num;

    account acc;
    ifstream infile("ACCOUNT.dat", ios::binary);

    bool found = false;
    while (infile.read((char*)&acc, sizeof(acc))) {
        if (acc.acno == acc_num) {
            found = true;
            break;
        }
    }
    infile.close();

    if (!found) {
        cout << "Account not found!\n";
        return;
    }

    int adhar_num;
    cout << "Enter Adhar Number: ";
    cin>>adhar_num;

    float amount;
    cout << "Enter Amount to be loaned: ";
    cin >> amount;

    int repay_time;
    cout << "Enter Repayment Time (in months): ";
    cin >> repay_time;

    float loan_left = amount * 1.12; // 12% interest rate
    Loan loan = { acc_num, adhar_num, amount, loan_left, repay_time };

    ofstream outfile("LOAN.txt", ios::app);
    outfile.write((char*)&loan, sizeof(loan));
    outfile.close();

    cout << "Loan Granted Successfully!\n";
}

void account::repayloan() {
	system("CLS");
    int acc_num;
    cout << "Enter Account Number: ";
    cin >> acc_num;

    account acc;
    ifstream infile("ACCOUNT.dat", ios::binary);

    bool found = false;
    while (infile.read((char*)&acc, sizeof(acc))) {
        if (acc.acno == acc_num) {
            found = true;
            break;
        }
    }
    infile.close();

    if (!found) {
        cout << "Account not found!\n";
        return;
    }

    int adhar_num;
    cout << "Enter Adhar Number: ";
    cin>>adhar_num;

    Loan loan;
    ifstream loanfile("LOAN.txt", ios::binary);

    found = false;
    while (loanfile.read((char*)&loan, sizeof(loan))) {
        if (loan.acc_num == acc_num && loan.adhar_num== adhar_num) {
            found = true;
            break;
        }
    }
    loanfile.close();

    if (!found) {
        cout << "Loan not found for this account and adhar number!\n";
        return;
    }

    float repay_amount;
    cout << "Enter Amount to be Repaid: ";
    cin >> repay_amount;

    if (repay_amount > loan.loan_left) {
        cout << "Cannot repay more than the loan left!\n";
        return;
    }

    loan.loan_left -= repay_amount;
    ofstream outfile("LOAN.txt", ios::out | ios::app);
    outfile.seekp(-sizeof(Loan), ios::cur);
    outfile.write((char*)&loan, sizeof(Loan));
    outfile.close();

    cout << "Repayment Successfull!\n";
}






void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void helper(char x);

int main()
{
	char ch;
	int num;
	do
	{
	system("CLS");
	cout<<"\n\n\t\t\t\t======================\n";
	cout<<"\t\t\t\tBANK MANAGEMENT SYSTEM";
	cout<<"\n\t\t\t\t======================\n";

		cout<<"\t\t\t\t    ::MAIN MENU::\n";
		cout<<"\n\t\t\t\t0. EXIT";
		cout<<"\n\t\t\t\t1. NEW ACCOUNT";
		cout<<"\n\t\t\t\t2. DEPOSIT AMOUNT";
		cout<<"\n\t\t\t\t3. WITHDRAW AMOUNT";
		cout<<"\n\t\t\t\t4. BALANCE ENQUIRY";
		cout<<"\n\t\t\t\t5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\t\t\t\t6. CLOSE AN ACCOUNT";
		cout<<"\n\t\t\t\t7. MODIFY AN ACCOUNT";
		cout<<"\n\t\t\t\t8. ISSUE A LOAN";
		cout<<"\n\t\t\t\t9. PAYMENT OF A LOAN";
		cout<<"\n\n\t\t\t\tSelect Your Option (0-9): ";
		cin>>ch;

		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		case '7':
		 	system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		case '8':
			system("CLS");
			helper('8');
			break;
		case '9':
			system("CLS");
			helper('9');
			break;
		case '0':
		 	system("CLS");
			cout<<"\n\n\t\t\t****************************";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!='0');
	return 0;
}

void helper(char x)
{
    account obj;
    if(x == '8')
        obj.giveloan();
    if(x == '9')
        obj.repayloan();
    
}


void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\t\t\tBALANCE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\n\t\t\tAccount number does not exist";
}



void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\n\t\t\tEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur); //fncallat1353
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		    cout<<"\n\n\t\t\tRecord Updated";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found ";
}



void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\nRecord Deleted ..";
}


void display_all()
{
	system("CLS");
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}


void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\t\t\tTO DEPOSITSS AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be deposited: ";
				cin>>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				cout<<"\n\n\t\t\tTO WITHDRAW AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be withdraw: ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if(bal<0)
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);//fn1353
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t\t\tRecord Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found ";
}

