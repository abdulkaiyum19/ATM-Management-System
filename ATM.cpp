#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void createAccount();
bool login(int& id, int& pin);
void atmMenu(int id, string name, int age, int pin, float& balance);
void continueFunction(float initialDeposit);
void updatePin(int id, int& pin);

void createAccount() {
    string name;
    int age, id, pin;
    float initialDeposit;

    ofstream file;
    file.open("AccountsList.txt", ios::out | ios::app);

    cout << "Enter Your Name: ";
    cin >> name;
    cout << "Create your Account Number: ";
    cin >> id;
    cout << "Enter Your Age: ";
    cin >> age;
    cout << "Create a PIN: ";
    cin >> pin;
    cout << "Enter initial deposit amount: BDT ";
    cin >> initialDeposit;

    file << id << " " << name << " " << age << " " << pin << " " << initialDeposit << endl;
    file.close();
    cout << "Account created successfully! Your initial balance is BDT " << initialDeposit << " TK" << endl;

    continueFunction(initialDeposit);
}

bool login(int& id, int& pin) {
    bool loggedIn = false;

    cout << "Enter Your Account Number: ";
    cin >> id;
    cout << "Enter Your PIN: ";
    cin >> pin;

    ifstream readFile("AccountsList.txt");
    int accountId;
    string name;
    int age;
    int accountPin;
    float initialDeposit;

    while (readFile >> accountId >> name >> age >> accountPin >> initialDeposit) {
        if (accountId == id && accountPin == pin) {
            cout << "Login successful!" << endl;
            readFile.close();
            return true;
        }
    }
    readFile.close();

    cout << "Login failed. Incorrect ID or PIN." << endl;
    return false;
}

void atmMenu(int id, string name, int age, int pin, float& balance) {
    int option;

    cout << "Welcome, " << name << " to Our ATM Service!!!\n";
    cout << "************************************\n";

    do {
        cout << "\nATM Menu:\n";
        cout << "1. View Balance\n";
        cout << "2. Withdraw Cash\n";
        cout << "3. Deposit Funds\n";
        cout << "4. Change PIN\n";
        cout << "5. Exit\n";
        cout << "Enter option: ";
        cin >> option;

        switch (option) {
            case 1:
                cout << "Your Balance Is: " << balance << " TK" << endl;
                break;

            case 2:
                float withdrawAmount;
                cout << "Enter amount to withdraw: ";
                cin >> withdrawAmount;
                if (withdrawAmount <= balance) {
                    balance -= withdrawAmount;
                    cout << "You withdrew " << withdrawAmount << " TK" << endl;
                    cout << "Your remaining balance is " << balance << " TK" << endl;
                } else {
                    cout << "Insufficient balance!\n";
                }
                break;

            case 3:
                float depositAmount;
                cout << "Enter amount to deposit: ";
                cin >> depositAmount;
                balance += depositAmount;
                cout << "You deposited BDT " << depositAmount << " TK" << endl;
                cout << "Your new balance is BDT " << balance << " TK" << endl;
                break;

            case 4:
                updatePin(id, pin);
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid option. Please enter a valid option.\n";
                break;
        }
    } while (option != 5);
}

void updatePin(int id, int& pin) {
    int oldPin;
    cout << "Enter your old PIN: ";
    cin >> oldPin;

    if (oldPin == pin) {
        int newPin;
        cout << "Enter your new PIN: ";
        cin >> newPin;
        pin = newPin;
        cout << "PIN Changed Successfully.\n";


        ifstream readFile("AccountsList.txt");
        ofstream tempFile("temp.txt");

        int accountId;
        string name;
        int age;
        int accountPin;
        float initialDeposit;

        while (readFile >> accountId >> name >> age >> accountPin >> initialDeposit) {
            if (accountId == id) {
                tempFile << accountId << " " << name << " " << age << " " << newPin << " " << initialDeposit << endl;
            } else {
                tempFile << accountId << " " << name << " " << age << " " << accountPin << " " << initialDeposit << endl;
            }
        }

        readFile.close();
        tempFile.close();

        remove("AccountsList.txt");
        rename("temp.txt", "AccountsList.txt");
    } else {
        cout << "Incorrect old PIN. PIN change failed.\n";
    }
}

void continueFunction(float initialDeposit) {
    int choice;
    cout << "\nContinue to:\n";
    cout << "1. Login\n";
    cout << "2. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            {
                int id, pin;
                float balance = initialDeposit;
                if (login(id, pin)) {
                    atmMenu(id, "User", 25, pin, balance);
                }
            }
            break;

        case 2:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice. Exiting...\n";
            break;
    }
}

int main() {
    int choice;

    cout << "Welcome to the ATM Service\n";
    cout << "***************************\n";

    do {
        cout << "Choose an option:\n";
        cout << "1. Create An Account\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;

            case 2:
                {
                    int id, pin;
                    float balance = 0.0;
                    if (login(id, pin)) {
                        atmMenu(id, "User", 25, pin, balance);
                    }
                }
                break;

            case 3:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice. Try again...\n";
                break;
        }
    } while (true);

    return 0;
}
