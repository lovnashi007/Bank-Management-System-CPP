#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>

// Using the standard namespace to avoid writing std:: repeatedly
using namespace std;

// Class to represent a bank account
class bank_account {
    int account_number;
    char name[50];
    char type;
    int deposit;

public:
    void create_account();    // Function to get data from user
    void show_account() const; // Function to show data on screen
    void modify();            // Function to add new data
    void dep(int);            // Function to accept amount and add to balance
    void draw(int);           // Function to accept amount and subtract from balance
    void report() const;      // Function to show data in tabular format
    int retacno() const;      // Function to return account number
    int retdeposit() const;   // Function to return balance amount
    char rettype() const;     // Function to return type of account
};

// Member function definitions

void bank_account::create_account() {
    cout << "\nEnter The account No. :";
    cin >> account_number;
    cout << "\nEnter The Name of The account Holder : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nEnter Type of The account (C for Current / S for Savings) : ";
    cin >> type;
    type = toupper(type); // Convert to uppercase
    cout << "\nEnter The Initial amount (>=500 for Savings and >=1000 for Current ) : ";
    cin >> deposit;
    cout << "\n\nAccount Created Successfully..";
}

void bank_account::show_account() const {
    cout << "\nAccount No. : " << account_number;
    cout << "\nAccount Holder Name : " << name;
    cout << "\nType of Account : " << type;
    cout << "\nBalance amount : " << deposit;
}

void bank_account::modify() {
    cout << "\nAccount No. : " << account_number;
    cout << "\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nModify Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\nModify Balance amount : ";
    cin >> deposit;
}

void bank_account::dep(int x) {
    deposit += x;
}

void bank_account::draw(int x) {
    deposit -= x;
}

void bank_account::report() const {
    cout << account_number << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int bank_account::retacno() const {
    return account_number;
}

int bank_account::retdeposit() const {
    return deposit;
}

char bank_account::rettype() const {
    return type;
}


// Function declarations for file operations
void write_account();    // Function to write record in binary file
void display_sp(int);    // Function to display account details given by user
void modify_account(int);  // Function to modify record of file
void delete_account(int);  // Function to delete record of file
void display_all();      // Function to display all account details
void deposit_withdraw(int, int); // Function to deposit/withdraw amount for given account

// Main function of the program
int main() {
    char ch;
    int num;
    do {
        system("cls"); // Clears the screen
        cout << "\n\n\t\t\t\t==============================\n";
        cout << "\t\t\t\t   BANK MANAGEMENT SYSTEM";
        cout << "\n\t\t\t\t==============================\n";
        cout << "\n\t\t\t\t    ::MAIN MENU::\n";
        cout << "\n\t\t\t\t1. NEW ACCOUNT";
        cout << "\n\t\t\t\t2. DEPOSIT AMOUNT";
        cout << "\n\t\t\t\t3. WITHDRAW AMOUNT";
        cout << "\n\t\t\t\t4. BALANCE ENQUIRY";
        cout << "\n\t\t\t\t5. ALL ACCOUNT HOLDER LIST";
        cout << "\n\t\t\t\t6. CLOSE AN ACCOUNT";
        cout << "\n\t\t\t\t7. MODIFY AN ACCOUNT";
        cout << "\n\t\t\t\t8. EXIT";
        cout << "\n\n\t\t\t\tSelect Your Option (1-8): ";
        cin >> ch;

        switch (ch) {
        case '1':
            write_account();
            break;
        case '2':
            cout << "\n\n\t\t\t\tEnter The account No. : "; cin >> num;
            deposit_withdraw(num, 1); // 1 for deposit
            break;
        case '3':
            cout << "\n\n\t\t\t\tEnter The account No. : "; cin >> num;
            deposit_withdraw(num, 2); // 2 for withdrawal
            break;
        case '4':
            cout << "\n\n\t\t\t\tEnter The account No. : "; cin >> num;
            display_sp(num);
            break;
        case '5':
            display_all();
            break;
        case '6':
            cout << "\n\n\t\t\t\tEnter The account No. : "; cin >> num;
            delete_account(num);
            break;
        case '7':
            cout << "\n\n\t\t\t\tEnter The account No. : "; cin >> num;
            modify_account(num);
            break;
        case '8':
            cout << "\n\n\t\t\t\tThanks for using bank management system";
            break;
        default: cout << "\a";
        }
        cin.ignore();
        cin.get();
    } while (ch != '8');
    return 0;
}


// Function to write in file
void write_account() {
    bank_account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(bank_account));
    outFile.close();
}

// Function to read specific record from file
void display_sp(int n) {
    bank_account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\nBALANCE DETAILS\n";
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(bank_account))) {
        if (ac.retacno() == n) {
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nAccount number does not exist";
}


// Function to modify record of file
void modify_account(int n) {
    bool found = false;
    bank_account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char*>(&ac), sizeof(bank_account));
        if (ac.retacno() == n) {
            ac.show_account();
            cout << "\n\nEnter The New Details of account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(bank_account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&ac), sizeof(bank_account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}


// Function to delete record of file
void delete_account(int n) {
    bank_account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(bank_account))) {
        if (ac.retacno() != n) {
            outFile.write(reinterpret_cast<char*>(&ac), sizeof(bank_account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\n\tRecord Deleted ..";
}

// Function to display all records from file
void display_all() {
    bank_account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME           Type  Balance\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(bank_account))) {
        ac.report();
    }
    inFile.close();
}

// Function to deposit and withdraw amounts
void deposit_withdraw(int n, int option) {
    int amt;
    bool found = false;
    bank_account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char*>(&ac), sizeof(bank_account));
        if (ac.retacno() == n) {
            ac.show_account();
            if (option == 1) { // Deposit
                cout << "\n\n\t\t\tTO DEPOSIT AMOUNT ";
                cout << "\n\nEnter The amount to be deposited: ";
                cin >> amt;
                ac.dep(amt);
            }
            if (option == 2) { // Withdraw
                cout << "\n\n\t\t\tTO WITHDRAW AMOUNT ";
                cout << "\n\nEnter The amount to be withdrawn: ";
                cin >> amt;
                int bal = ac.retdeposit() - amt;
                if (bal < 500 && ac.rettype() == 'S' || bal < 1000 && ac.rettype() == 'C')
                    cout << "Insufficience balance";
                else
                    ac.draw(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(bank_account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&ac), sizeof(bank_account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}