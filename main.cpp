//////////////////////////////////IMPORTING ALL NECESSARY HEADER FILES AND LIBRARIES\\\\\\\\\\\\\\\\\\\\\\

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <math.h>
#include <bits/stdc++.h>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

////////////////////////////// ALL NECESSARY FUNCTIONS,CLASS  AND GLOABL DECLARATIONS \\\\\\\\\\\\\\\\\\\\\\\\

string NAME, ACCOUNTNO;
char FOURDIGITPIN[5];
int ENTRYPIN, BALANCE, ENTRYCODE;

inline void line()
{
    cout << "\t\t\t_____________________________________________________________________________________"<<endl<<endl;
}
inline void starline()
{
    cout << "\t\t\t*************************************************************************************"<<endl<<endl;
}

// GLOBAL OBJECTS DECLARATIONS \\

fstream file("BankConfidential1.txt", ios::app | ios::in | ios::out);
fstream ExLE("ATMsecret.txt", ios::app | ios::in | ios::out);
time_t now = time(0);
char *dt = ctime(&now);

///// NECESSARY FUNCTIONS AND VARIABLES DECLARATIONS \\\\\\

const int n = 3;
void write_to_csv();
bool verif_entry_code(int);
int get_balance_from_file(int t);
bool get_ATMPIN_from_file(int t, string MPIN);
string adv_tokenizer(string s, char del);
string adv_tokenizer_forATMPIN(string s, char del);
class Bank;
class Info;
template <class BankType>
class ATM;
class ICICI;
class HDFC;
template <class disobj>
void display(disobj);
/////////////////////////////////////////////////////////////////////////
/*
                                        Funtion To Generate OTP
*/
bool OTP()
{

    file << "\t\t" << dt << "\t\t\tInitialized OTP Generation.\n";
    char otp[6], votp[6], c;
    int i;
correct:
    srand((unsigned)time(NULL));
    for (i = 0; i < 5; i++)
    {
        c = rand() % 10 + 48;
        otp[i] = c;
    }
    otp[i] = '\0';
    cout<<endl<<endl<<"\t\t\tOTP Generated\t\t: " << otp << endl;
    file << "\t\t" << dt << "\t\t\tOTP Generated Successfully..\n";

    cout << "\t\t\tVerify OTP\t\t: ";
    cin >> votp;
    try // try block
    {
        if (strcmp(otp, votp) == 0)
        {
            cout<<endl<<"\t\t\tYour OTP is Successfully Verified" << endl;
            file << "\t\t" << dt << "\t\t\tOTP Verified.\n";
            return true;
        }
        else
        {
            throw otp; // throw
            return false;
        }
    }
    catch (char otp[60]) // catch block
    {
        cout << endl<<"\t\t\tYou Entered Wrong OTP " << endl;
        cout << endl<<"\t\t\tPlease Enter The OTP Again." << endl;
        file << "\t\t" << dt << "\t\t\tClient Entered a Wrong OTP.\n";
        goto correct;
    }
}

/////////////////////////////////////////////////////////////////////////
/*
Funtion To Generate Random Account Number
*/
string generateaccount()
{
    char accno[12];
    int c;
    srand((unsigned)time(NULL));
    for (int i = 0; i < 12; i++)
    {
        c = rand() % 10 + 48;
        accno[i] = c;
    }
    file << "\t\t" << dt << "\t\t\t Account Number Of Client is " << accno << "\n";
    ACCOUNTNO = accno;
    return accno;
}

/////////////////////////////////////////////////////////////////////////
/*
                                Funtion To Generate Random ATM entry No
*/
int ATMentryNO()
{
    int generate = 0;
    for (int i = 0; i < 8; i++)
    {
        generate += ((rand() % 10) * pow(10, i));
    }
    return generate;
}

class Info
{
protected:
    string Pan;

public:
    string name;
    friend void ATMStart();
    template <class BankType>
    friend class ATM;
    friend class ICICI;
    friend class HDFC;
    void displaypan()
    {
        for (int i = 0; i < Pan.length(); i++)
        {
            if (i < Pan.length() - 5)
            {
                cout << "X";
            }
            else
            {
                cout << Pan[i];
            }
        }
        file << "\t\t" << dt << "\t\t\tPAN Displayed\n";
    }
    static int count;
    static void counter()
    {
        file << "For Client Number : " << ++count << "\n";
    }
    void setdata()
    {
        counter();
        cout << "\t\t\t//////////////////////////////// |||||||| ////////////////////////////////////" << endl;
        cout << "\t\t\t////////////////////////////////          ////////////////////////////////////" << endl;
        cout << "\t\t\t//////////////////////////////// WEL-COME ////////////////////////////////////" << endl;
        cout << "\t\t\t////////////////////////////////          ////////////////////////////////////" << endl;
        cout << "\t\t\t//////////////////////////////// |||||||| ////////////////////////////////////" << endl;
        file << dt << "\tCheck-in initiated\n";
        cout<<endl<<endl;
        cout << "\t\t\tEnter Your Name\t\t\t: ";
        cin >> name;
        NAME = name;
        file << "\t\t" << dt << "\t\t\tEntered Name :" << name << "\n";
        cout << "\t\t\tEnter Your PAN Number \t\t: ";
        cin >> Pan;
        file << "\t\t" << dt << "\t\t\tPAN Entered : " << Pan << "\n";
    }
};
int Info ::count = 0;

///////////////////////////****************Bank*****************////////////////////////////////
/*
                Bank class is major class of the program
                It consist of following Parameter:
                1.string account_no: To Store Account Number of User in string Format
                2.int balance: to track & maintain balance of user
                3. bool DebitCard : To see wheather user has opt to have DebitCard or Not
                4.int Loan Amount: This will tell loan amount on user
                5.Info Basic: here Basic is object of class Info which Consist of name,pan No of user
                6. int EntryNo: This will Provide Entry Number at ATM To user who has opt for Debitcard
                7. char MPIN[4]: This will Store 4 digit ATM Pin of ATM
                8. bool hasSet: This will tell us wheather Client has set his DebitCard Pin
                9.void setpin(): Funtion To set Pin of ATM
                10.bool CheckPin(): Funtion To Check the PIN
                11.void displayAccNo(): Function To Display Masked Account Number of User
                12.void setdata(): To set all the Data of User
*/
class Bank
{
protected:
    string account_no;
    bool DebitCard;
    int loanAmount;
    Info Basic;
    static int statcount;
    int EntryNo;
    bool hasSet;
    char MPIN[4];

public:
    int balance;
    void setpin();
    bool CheckPin();
    friend void ATMStart();
    friend void write_to_csv();
    void displayAccNo();
    void setdata()
    {
        Basic.setdata();
        line();
        account_no = generateaccount(); // Account Number is generated here
        cout << "\t\t\tEnter Your Initial Opening Balance : ";
        cin >> balance;
        BALANCE = balance;
        file << "\t\t" << dt << "\t\t\tWants to Open Account With " << balance << "Rupees as Balance.\n";
        int choice;
    correct1:
        line();
        cout<<endl<<endl;
        cout << "\t\t\tIf Want Debit Card Press 1 Else 0 : ";
        cin >> choice;
        if (choice == 1)
        {
            cout<<endl<<endl;
            cout << "\t\t\tYou Will Recieve Debiit Card Shortly" << endl;
            DebitCard = true;
            hasSet = false;
            EntryNo = ATMentryNO();
            cout<<endl;
            cout << "\t\t\tYour Entry Code OF ATM is : " << EntryNo << endl;
            cout<<endl<<"\t\t\t****************** KINDLY COPY IT ***********************"<<endl;
            ENTRYPIN = EntryNo;
            cout << "\t\t\tDo Not Share IT With Anyone" << endl;
            cout<<endl<<"\t\t\t\t\t\tPLEASE SET YOUR ATM PIN IMMEDIATELY"<<endl;
            getch();
            system("cls");
            statcount++;
            file << "\t\t" << dt << "\t\t\tApplied for Debit Card.\n";
        }
        else if (choice == 0)
        {
            cout << endl<<"\t\t\tYou Denyed To Debit Card" << endl;
            DebitCard = false;
            file << "\t\t" << dt << "\t\t\tDid Not Applied for Debit Card.\n";
        }
        else
        {
            cout << endl <<"\t\t\tSomething Went Wrong Try Again" << endl;
            file << "\t\t" << dt << "\t\t\tEntered Wrong Choice.\n";
            cout << endl<<"\t\t\tPress any key to continue" << endl;

            getch();
            goto correct1;
        }

        cout<<endl<<endl<<"\t\t\tEnter Loan Credit You Want From Bank (Enter 0 if Not Required): ";
        cin >> loanAmount;
        if (loanAmount == 0)
            file << "\t\t" << dt << "\t\t\tNot Applied For Loan.\n";
        else
            file << "\t\t" << dt << "\t\t\tApplied for Loan.\n";
        getch();
    }

    friend class ICICI;
    friend class HDFC;
    template <class disobj>
    friend void display(disobj);
    template <class BankType>
    friend class ATM;
};
int Bank::statcount = 0;

// void displayAccNo(): Function To Display Masked Account Number of User

void Bank ::displayAccNo()
{
    for (int i = 0; i < account_no.length(); i++)
    {
        if (i < account_no.length() - 5)
            cout << "X";
        else
            cout << account_no[i];
    }
    cout << endl;
    file << "\t\t" << dt << "\t\t\tAccount Number Displayed.\n";
}

// bool CheckPin(): Funtion To Check the PIN

bool Bank ::CheckPin()
{
    char ch;
    char IN[5];
    for (int i = 0; i < 4; i++)
    {
    nittak:
        ch = getch();
        if (ch < 48 || ch > 57)
            goto nittak;
        else
        {
            IN[i] = ch;
            ch = 'X';
            cout << ch;
        }
    }
    IN[4] = '\0';
    cout << endl;
    int arr[4];

    // if(get_ATMPIN_from_file(ENTRYCODE,MPIN)){
    //     return true ;
    // }
    if (strcmp(IN, FOURDIGITPIN) == 0)
    {
        return true;
    }
    else if (strcmp(IN, MPIN) == 0)
    {
        return true;
    }
    else{
        cout<<endl<<"\t\t\tPlease Enter The Correct Pin Next Time."<<endl;
        cout<<endl<<"\t\t\tExiting Now.  "<<endl;
        cout<<endl<<"\t\t\tPress Any Key To Continue.... "<<endl;
        getch();
        return false;}
}

// void setpin(): Funtion To set Pin of ATM

void Bank ::setpin()
{
    char PIN[5], VPIN[5];
    char ch;
    OTP();
ifwrong:
    cout<<endl<<endl<<"\t\t\tEnter Your Four Digit PIN : " << endl;
    cout<<"\t\t\t\t\t\t"<<endl;
    for (int i = 0; i < 4; i++)
    {
    nittak:
        ch = getch();
        if (ch < 48 || ch > 57)
            goto nittak;
        else
        {
            PIN[i] = ch;
            FOURDIGITPIN[i] = PIN[i];
            ch = 'X';
            cout << ch;
        }
    }
    PIN[4] = '\0';
    FOURDIGITPIN[4] = '\0';
    system("cls");
    cout << endl;

    cout<<endl<<endl<<"\t\t\tEnter PIN Once Again To Confirm : " << endl;
    for (int i = 0; i < 4; i++)
    {
    nit:
        ch = getch();
        if (ch < 48 || ch > 57)
            goto nit;
        else
        {
            VPIN[i] = ch;
            ch = 'X';
            cout << ch;
        }
    }
    VPIN[4] = '\0';
    cout << endl;
    if (strcmp(PIN, VPIN) == 0)
    {
        system("cls");
        cout<<endl<<endl<<"Your PIN is Successfully Verified" <<endl;
        getch();
        for (int i = 0; i < 4; i++)
        {
            MPIN[i] = PIN[i];
        }
        hasSet = true;
        write_to_csv();
    }
    else
    {
        cout<<endl<<endl<<"****************** PIN Mismatched *******************"
             << "\a" << endl;
             cout << endl<<"\t\t\tPress any key to continue" << endl;

    getch();
        goto ifwrong;
    }
}

///////////////////////////ICICI////////////////////////////////
/*
                            HDFC class Derived From class Info & class Bank
*/
class ICICI : public Info, public Bank
{
public:
    template <class disobj>
    friend void display(disobj);
    template <class BankType>
    friend class ATM;
    void setdata()
    {
        Bank::setdata();
    }
    friend void ATMStart();
};

///////////////////////////HDFC////////////////////////////////
/*
                            HDFC class Derived From class Info & class Bank
*/
class HDFC : public Info, public Bank
{
public:
    template <class disobj>
    friend void display(disobj);
    void setdata()
    {
        Bank::setdata();
    }
    template <class BankType>
    friend class ATM;
    friend void ATMStart();
};

// Initiating Array Of An Object
ICICI *I = new ICICI[n];
HDFC *H = new HDFC[n];

///////////////////////////ATM////////////////////////////////

template <class BankType>
class ATM
{
    BankType Obj;

public:
    void Operations(BankType &Obj);
    void Withdraw(BankType &Obj);
    void Deposit(BankType &Obj);
    void CheckBalance(BankType &Obj);
    friend void ATMStart();
    friend void get_balance_from_file();
};
/////////////////////////////////////////////////////////////////////////////////////////
/*
                            Withdraw() Function To Withdraw Amount From ATM
*/
template <class BankType>
void ATM<BankType>::Withdraw(BankType &Obj)
{
    int withdrawamt;
    cout << endl<<"\t\t\tEnter Amount To be Debited : ";
    cin >> withdrawamt;
    if (withdrawamt % 100 != 0)
    {
        cout << endl<<"\t\t\tEnter Amount in Multiple of 100" << endl;
        cout << endl<<"\t\t\tPress any key to continue" << endl;

    getch();
    }
    else if (withdrawamt > Obj.balance)
    {
        cout << endl<<"\t\t\tInsufficient Balance" << endl;
        cout << endl<<"\t\t\tPress any key to continue" << endl;

    getch();
    }
    else
    {
        Obj.balance = Obj.balance - withdrawamt;
        cout << endl<<"\t\t\tYour transaction is succesful..." << endl;
        cout << endl<<"\t\t\tPress any key to continue" << endl;

    getch();
    }
}
template <class BankType>
/////////////////////////////////////////////////////////////////////////////////////////
/*
                                Deposit Function To Deposit Cash in ATM
*/
void ATM<BankType>::Deposit(BankType &Obj)
{
    int deposit;
    cout <<endl<< "\t\t\tEnter Amount To be Credited : ";
    cin >> deposit;
    Obj.balance = Obj.balance + deposit;

    cout << endl<<"\t\t\tYour transaction is succesful..." << endl;
    cout << endl<<"\t\t\tPress any key to continue" << endl;

    getch();
}
/////////////////////////////////////////////////////////////////////////////////////////
/*
                        CheckBalance() Function To Check Balance In Account
*/
template <class BankType>
void ATM<BankType>::CheckBalance(BankType &Obj)
{
    cout << endl<<endl<<"\t\t\tCurrent balance in your account is ";
    if (Obj.balance < 0 || Obj.balance > 1000000)
    {
        Obj.balance = get_balance_from_file(ENTRYCODE);
    }

    cout << Obj.balance << endl;
    cout<<endl<<endl<<"\t\t\tPress Any Key To Continue..."<<endl;;
    getch();
}

/////////////////////////////////////////////////////////////////////////////////////////
/*
                        Operation Function To Initiate ATM Operations
*/
template <class BankType>
void ATM<BankType>::Operations(BankType &Obj)
{
    int choice;
    starline();
    cout <<endl<< "\t\t\tFor WithDraw Press 1" << endl;
    cout <<endl<< "\t\t\tFor Deposite Press 2" << endl;
    cout <<endl<< "\t\t\tFor Checking balance Press 3" << endl;
    starline();

    cout << endl<<"\t\t\tEnter Your Choice : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        system("cls");
        Withdraw(Obj);
        break;
    case 2:
        system("cls");
        Deposit(Obj);
        break;
    case 3:
        system("cls");
        CheckBalance(Obj);
        break;
    default:
        cout << "Enter Valid Choice " << endl;
        break;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
/*
                                    Function Template to Display Data
*/
template <class disobj>
void display(disobj obj)
{
    system("cls");
    line();
    cout << "Your Name is \t\t\t: " << obj.Basic.name << endl;
    file << "\t\t" << dt << "\t\t\tName Displayed.\n";
    cout << "Your PAN \t\t\t: ";
    obj.Basic.displaypan();
    // obj.Basic.displaypan();
    cout << "\nYour Account No   \t\t: ";
    obj.displayAccNo(); // Display Masked Account Number of Obj
    cout << "Your Balance     \t\t: " << obj.balance << endl;
    file << "\t\t" << dt << "\t\t\tAccount Balance Displayed.\n";
    line();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
        Function To Provide Banking Facility To Open Account & To Store Initial Information about Client
        Function Used :
        1. setdata() of Bank Class by object of derived class i.e Either ICICI or HDFC
        2. Display() : which is Function template & will display all information of User
*/
static void BankOperations()
{
    static int countICICI = 0;
    static int countHDFC = 0;
correct:
    int choice;
    cout << "\t\t\t###################################################################################" << endl;
    cout << "\t\t\t###################################################################################" << endl;
    cout << "\t\t\t####################                                            ###################" << endl;
    cout << "\t\t\t####################           AIML BANK MANAGEMENT             ###################" << endl;
    cout << "\t\t\t####################           Zindagi ke saath bhi             ###################" << endl;
    cout << "\t\t\t####################            Zindagi ke baad bhi             ###################" << endl;
    cout << "\t\t\t####################                                            ###################" << endl;
    cout << "\t\t\t###################################################################################" << endl;
    cout << "\t\t\t###################################################################################" << endl;
    cout << "\t\t\tFor ICICI Bank Press 1\n\n\t\t\tFor HDFC Bank Press 2\n\n\t\t\tEnter  : ";
    cin >> choice;
    system("cls");
    if (choice == 1)
    {
        I[countICICI].setdata();
        display(I[countICICI]);
        countICICI++;
        file << "\t" << dt << "\tCheck-Out Initated.\n\n\n\n\n";
    }
    else if (choice == 2)
    {
        H[countHDFC].setdata();
        display(H[countHDFC]);
        countHDFC++;
        file << "\t" << dt << "\tCheck-Out Initated.\n\n\n\n\n";
    }
    else
    {
        cout << "Something Went Wrong " << endl;
        goto correct;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
            functon ATMStart : friend function of all class i.e Bank,ICICI,HDFC,ATM etc
*/
template <class BankType>
ATM<BankType> User;
void ATMStart()
{
    int EntryCode;
    int Pin;
    cout<<endl<<endl<<endl<<"\t\t\tEnter Your Entry Code : ";
    cin >> EntryCode; // Here Entry Code is Taken From User
    ENTRYCODE = EntryCode;
    int flag = 0;
    for (int i = 0; i < 3; i++)
    {
        if (I[i].EntryNo == EntryCode || verif_entry_code(EntryCode)) // Entry Code is Checked For ICICI client array
        {
            flag = 1;
            if (get_ATMPIN_from_file(EntryCode, ""))
            {
                I[i].hasSet = true;
            }
            if (I[i].hasSet == false)
            {
                I[i].setpin(); // If User Havent set PIN yet First He has to set PIN
                break;
            }
            else
            {
                ICICI &obj = I[i];
                cout << endl<<"\t\t\tEnter Your ATM PIN : ";
                bool Pass = I[i].CheckPin(); // Here Pin will be checked using CheckPin() Function
                if (Pass)
                {
                    User<ICICI>.Operations(obj);
                    break;
                }
                else
                {
                    cout << endl<<"\t\t\tSomething Went Wrong!!!...." << endl;
                    break;
                }
            }
        }
        else if (H[i].EntryNo == EntryCode || verif_entry_code(EntryCode)) // Entry Code is Check For HDFC Client Array
        {
            flag = 1;
            if (get_ATMPIN_from_file(EntryCode, ""))
            {
                H[i].hasSet = true;
            }
            if (H[i].hasSet == false)
            {
                H[i].setpin();
                break;
            }
            else
            {
                HDFC &obj = H[i];
                cout << "Enter Your ATM PIN : ";
                bool Pass = H[i].CheckPin();
                if (Pass)
                {
                    User<HDFC>.Operations(obj);
                    break;
                }
                else
                {
                    cout << "Something Went Wrong!!!...." << endl;
                    break;
                }
            }
        }
        if (flag == 0)
        {
            cout << endl<<"\t\t\tEntered Entry CODE is Wrong" << endl;
            cout << endl<<"\t\t\tPress any key to continue" << endl;
            getch();
        }
    }
}
int main() // THE DRIVER PROGRAMME
{
    while (1)
    {
    cho:
        system("cls");
        cout << "\t\t\t###################################################################################" << endl;
        cout << "\t\t\t###################################################################################" << endl;
        cout << "\t\t\t####################                                            ###################" << endl;
        cout << "\t\t\t####################      WELCOME TO AIML BANK MANAGEMENT       ###################" << endl;
        cout << "\t\t\t####################                 SYSTEM                     ###################" << endl;
        cout << "\t\t\t#################### -founded by Pratham,Koustubh and Santrupti ###################" << endl;
        cout << "\t\t\t####################                                            ###################" << endl;
        cout << "\t\t\t###################################################################################" << endl;
        cout << "\t\t\t###################################################################################" << endl;
        int choice;
        cout << endl
             << endl;
        cout << "\t\t\tFor Banking Operation Press 1" << endl;
        cout << endl;
        cout << "\t\t\tFor ATM Operation Press 2" << endl;
        cout << endl;
        cout << "\t\t\tEnter : ";
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
            BankOperations(); // Function TO initiate Banking Operation
            goto cho;
            break;

        case 2:
            ATMStart(); // Function to initiate ATM Operation
            goto cho;
            break;
        default:
            break;
        }
    }

    return 0;
}

void write_to_csv() // File necessary hold the login details of the consumers into a file
{
    ExLE << ENTRYPIN << "," << BALANCE << "," << FOURDIGITPIN << "," << ACCOUNTNO << "," << NAME << "\n";
    ExLE.close();
}

bool verif_entry_code(int t)
{
    stringstream stream;
    stream << t;
    string no;
    stream >> no;
    ifstream file;
    string line;

    int flag, offset;
    file.open("ATMsecret.txt");
    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, line, ',');
            if ((offset = line.find(no, 0)) != string::npos)
            {
                flag = 1;

                break;
            }
            else
                flag = 0;
        }
    }
    else
        return false;

    if (flag)
        return true;
    else
        return false;
}

int get_balance_from_file(int t)
{
    stringstream stream;
    stream << t;
    string no;
    stream >> no;
    fstream file;
    string line, line2;
    int flag, offset;
    file.open("ATMsecret.txt", ios::app | ios::out | ios::in);
    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, line, ',');
            if ((offset = line.find(no, 0)) != string::npos)
            {
                getline(file, line2, '\n');
                break;
            }
        }
    }
    string newstring;
    newstring = adv_tokenizer(line2, ',');
    return stoi(newstring);
}

string adv_tokenizer(string s, char del)
{
    stringstream ss(s);
    string word;
    int i = 0;
    while (i < 1)
    {
        getline(ss, word, del);
        i++;
    }
    return word;
}

bool get_ATMPIN_from_file(int t, string MPIN)
{
    stringstream stream;
    stream << t;
    string no;
    stream >> no;
    fstream file;
    string line, line2;
    int flag, offset;
    file.open("ATMsecret.txt", ios::app | ios::out | ios::in);
    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, line, ',');
            if ((offset = line.find(no, 0)) != string::npos)
            {
                getline(file, line2, '\n');
                break;
            }
        }
    }
    else
        cout << "Something went wrong, while confirming the password." << endl;
    string newstring;
    newstring = adv_tokenizer_forATMPIN(line2, ',');
    for (int i = 0; i < 4; i++)
    {
        FOURDIGITPIN[i] = newstring[i];
    }
    FOURDIGITPIN[4] = '\0';

    if (MPIN == "" && newstring != "")
    {
        return true;
    }
    else if (newstring == MPIN)
    {
        return false;
    }
    else
        return false;
}

string adv_tokenizer_forATMPIN(string s, char del)
{
    stringstream ss(s);
    string word;
    int i = 0;
    while (i < 2)
    {
        getline(ss, word, del);
        i++;
    }
    return word;
}
