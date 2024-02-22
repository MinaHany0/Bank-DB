#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>

#define OPEN__ACCOUNT       1
#define BALANCE_INQUIRY     2
#define DEPOSIT             3
#define WOTHDRAW            4
#define CLOSE_ACCOUNT       5
#define SHOW_ALL_ACCOUNTS   6
#define QUIT                7

class Bank{
    
    private:
        Bank(){};
        class Account{
            private:
                std::string firstname;
                std::string lastName;
                int balance;
                int accountNumber;
            public:
                Account(std::string fn = "N/A", std::string ln= "N/A", int accNo = -1, int bal = 0)
                        : firstname(fn), lastName(ln), balance(bal), accountNumber(accNo){}
                std::string getFirstName(void){ return firstname; }
                std::string getLastName(void){ return lastName; }
                int getBalance(void){return balance; }
                int getAccountNumber(void){return accountNumber; }
                void deposit(int money){balance += money; }
                void withdraw(int money)                    
                {
                    if(balance >= money) balance -= money;
                    else std::cout << "Balance not Enough!\n";
                }
                void printBalance(void) {std::cout << getFirstName() << " " << getLastName() << " has " << getBalance() << std::endl;}
        };
    public: 
        static std::vector<Account> accounts_vec;
        static int EnrolledAccount;
        static Bank& getInst(void){ static Bank _b; return _b; }
        friend std::ostream &operator<<(std::ostream &os, Account &acc);
        friend std::ofstream &operator<<(std::ofstream &os, Account &acc);
        friend std::ifstream &operator>>(std::ifstream &os, Bank &bank);
        
        void readAccountsData(void);
        void openAccount(void);
        void balanceInquiry(void);
        void DepositinAccount(void);
        void WithdrawFromAccount(void);
        void closeAccount(void);
        void showall(void);
        void Quit(void);
};

std::vector<Bank::Account> Bank::accounts_vec;
int Bank::EnrolledAccount = 0;

std::ostream &operator<<(std::ostream &os, Bank::Account &acc)
{
    os << "Name : " << acc.getFirstName() << " " << acc.getLastName() << std::endl;
    os << "Account Number : " << acc.getAccountNumber() << std::endl;
    os << "Balance : " << acc.getBalance() << std::endl;
    return os;
}

std::ofstream &operator<<(std::ofstream &os, Bank::Account &acc)
{
    os << acc.getFirstName() << std::endl;
    os << acc.getLastName() << std::endl;
    os << acc.getBalance() << std::endl;
    os << acc.getAccountNumber() << std::endl;
    return os;
}

std::ifstream &operator>>(std::ifstream &os, Bank &bank)
{
    std::string firstName, LastName;
    int accNo, balance;
    os >> firstName;
    os >> LastName;
    os >> balance;
    os >> accNo;
    Bank::accounts_vec.push_back(Bank::Account(firstName, LastName, accNo, balance));
    Bank::EnrolledAccount = accNo+1;
    return os;
}

void Bank::readAccountsData()
{
    std::ifstream ifs("BankData.txt");
    if(!ifs)
    {
        std::cout << "No Data! Welcome to the new Bank"<< std::endl;
    }
    else
    {
        
        std::cout << "Retrieving Data\n\n";
        while(ifs.eof() == false)
        {
            ifs >> Bank::getInst();
        }
        std::vector<Bank::Account>::iterator itr = accounts_vec.begin();
        Bank::accounts_vec.erase(itr + accounts_vec.size());
        Bank::EnrolledAccount = accounts_vec[accounts_vec.size()-1].getAccountNumber() +1;
    }

}

void Bank::openAccount(void){

    std::string firstName, LastName;
    int accNo = EnrolledAccount++;
    int balance;
    std::cout << "Please Enter your First Name: ";;
    std::cin >> firstName;
    std::cin.ignore();
    std::cout << "Please Enter your Last Name: ";
    std::cin >> LastName;
    std::cin.ignore();
    std::cout << "Please Enter Initial Balance: ";
    std::cin >> balance;
    std::cin.ignore();
    accounts_vec.push_back(Account(firstName, LastName, accNo, balance));
    std::cout << "\n\nCongrats Account is Created\n";
    std::cout << std::setw(18) << std::left << "Account Name :" << firstName << " " << LastName << std::endl;
    std::cout << std::setw(18) << std::left << "Account Number:" << accNo << std::endl;
    std::cout << std::setw(18) << std::left << "Balance:" << balance << "\n\n\n";


}

void Bank::balanceInquiry(void)
{
    int num;
    std::cout << "Please enter account number : ";
    std::cin >>num; std::cin.ignore();
    std::vector<Bank::Account>::iterator itr = accounts_vec.begin();
    for(; itr < accounts_vec.end(); itr++)
    {
        if(itr->getAccountNumber() == num)
        {
            itr->printBalance();
            std::cout << "\n\n";
            return;
        }

    }
    std::cout << "Account doesn't exist\n\n";
    return;
}

void Bank::DepositinAccount(void)
{
    int num;
    std::cout << "Please enter account number : ";
    std::cin >>num; std::cin.ignore();
    auto itr = Bank::accounts_vec.begin();
    for(; itr < Bank::accounts_vec.end(); itr++)
    {
        if(itr->getAccountNumber() == num)
        {
            int money;
            std::cout << "Enter amount of money : ";
            std::cin >> money; std::cin.ignore();   
            Bank::accounts_vec[num].deposit(money);
            std::cout << "Balance of " << Bank::accounts_vec[num].getFirstName() << " "
            <<  Bank::accounts_vec[num].getLastName()<< " is " << Bank::accounts_vec[num].getBalance() << "\n\n"; 
            return;
        }
    }
    std::cout << "Account doesn't exist\n\n";
    return;    
}

void Bank::WithdrawFromAccount(void)
{
    int num;
    std::cout << "Please enter account number : ";
    std::cin >>num; std::cin.ignore();
    auto itr = Bank::accounts_vec.begin();
    for(; itr < Bank::accounts_vec.end(); itr++)
    {
        if(itr->getAccountNumber() == num)
        {
            int money;
            std::cout << "Enter amount of money : ";
            std::cin >> money; std::cin.ignore();   
            Bank::accounts_vec[num].withdraw(money);
            std::cout << "Balance of " << Bank::accounts_vec[num].getFirstName() 
            <<  Bank::accounts_vec[num].getLastName()<< " is " << Bank::accounts_vec[num].getBalance() << "\n\n"; 
            return;
        }
    }
    std::cout << "Account doesn't exist\n\n";
    return;    
}

void Bank::closeAccount(void)
{
    std::cout << "Please Enter account Number to Close: ";
    int closeAccNo;
    std::cin >> closeAccNo;
    std::cin.ignore();
    std::vector<Bank::Account>::iterator itr = accounts_vec.begin();
    for(int i = 0; i < accounts_vec.size(); i++)
    {
        if(accounts_vec[i].getAccountNumber() == closeAccNo)
        {
            accounts_vec.erase(itr+i);
            std::cout <<"Account Closed Successfully\n\n";
            return;
        }
    }
    std::cout << "Account doesn't exist\n\n";

}

void Bank::showall(void)
{
    for( std::vector<Bank::Account>::iterator it = accounts_vec.begin(); it < accounts_vec.end(); it++)
        std::cout << (*it) << std::endl;
}

void Bank::Quit(void)
{
    std::ofstream ofs("BankData.txt", std::ios::trunc);
    for( std::vector<Bank::Account>::iterator it = accounts_vec.begin(); it < accounts_vec.end(); it++)
        ofs << (*it) ;

}

int main()
{
    Bank::getInst().readAccountsData();
    int choice = 0;
    while(1)
    {

        std::cout << "\t\tSelect one option below" <<std::endl;
        std::cout << "\t\t1 Open an Account " << std::endl;
        std::cout << "\t\t2 Balance Inquiry " << std::endl;
        std::cout << "\t\t3 Deposit " << std::endl;
        std::cout << "\t\t4 Withdrawal " << std::endl;
        std::cout << "\t\t5 Close an Account " << std::endl;
        std::cout << "\t\t6 Show all Accounts " << std::endl;
        std::cout << "\t\t7 Quit " << std::endl;

        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case OPEN__ACCOUNT:
            Bank::getInst().openAccount();
            break;
        
        case BALANCE_INQUIRY:
            Bank::getInst().balanceInquiry();
            break;
        
        case DEPOSIT:
            Bank::getInst().DepositinAccount();
            break;
        
        case WOTHDRAW:
            Bank::getInst().WithdrawFromAccount();
            break;
        
        case CLOSE_ACCOUNT:
            Bank::getInst().closeAccount();
            break;
        
        case SHOW_ALL_ACCOUNTS:
            Bank::getInst().showall();
            break;
        
        case QUIT:
            Bank::getInst().Quit();
            exit(0);
            break;
        
        default:
            break;
        }
        
    }
}
