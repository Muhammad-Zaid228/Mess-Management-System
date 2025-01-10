#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int BASE_COST = 2000;

class Node {
public:
    string name;
    string phone;
    string joinDate;
    int type = 0; // 1: Lunch, 2: Dinner, 3: Both
    int amountPaid = 0;
    Node *next = nullptr;
};

class Mess {
    Node *head = nullptr;

public:
    Mess() = default;
    ~Mess();

    void insertCustomer();
    void displayCustomers();
    void deleteCustomer();
    void saveToFile();
    void displayCustomerDetails(Node *customer);
    void showMenuAndDeductAmount();

private:
    Node* findCustomerByName(const string &name);
};

Mess::~Mess() {
    while (head) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

void Mess::insertCustomer() {
    Node *newCustomer = new Node;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Customer Name: ";
    getline(cin, newCustomer->name);

    cout << "Enter Phone Number: ";
    cin >> newCustomer->phone;

    do {
        cout << "Enter Meal Type (1: Lunch, 2: Dinner, 3: Both): ";
        cin >> newCustomer->type;
    } while (newCustomer->type < 1 || newCustomer->type > 3);

    cout << "Enter Joining Date (DD/MM/YYYY): ";
    cin >> newCustomer->joinDate;

    do {
        cout << "Enter Amount Paid (Minimum 500): ";
        cin >> newCustomer->amountPaid;
    } while (newCustomer->amountPaid < 500);

    if (!head) {
        head = newCustomer;
    } else {
        Node *temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newCustomer;
    }

    cout << "Customer added successfully!\n";
}

Node* Mess::findCustomerByName(const string &name) {
    Node *temp = head;
    while (temp) {
        if (temp->name == name) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void Mess::displayCustomerDetails(Node *customer) {
    cout << "Name: " << customer->name << "\n";
    cout << "Phone: " << customer->phone << "\n";
    cout << "Joining Date: " << customer->joinDate << "\n";
    cout << "Amount Paid: " << customer->amountPaid << "\n";

    cout << "Meal Type: ";
    if (customer->type == 1) cout << "Lunch\n";
    else if (customer->type == 2) cout << "Dinner\n";
    else cout << "Both\n";
}

void Mess::displayCustomers() {
    if (!head) {
        cout << "No customers to display.\n";
        return;
    }

    cout << "1. Display All Customers\n";
    cout << "2. Display Specific Customer\n";

    int choice;
    cin >> choice;
    if (choice == 1) {
        Node *temp = head;
        while (temp) {
            displayCustomerDetails(temp);
            cout << "------------------------\n";
            temp = temp->next;
        }
    } else if (choice == 2) {
        cout << "Enter Customer Name: ";
        string name;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);

        Node *customer = findCustomerByName(name);
        if (customer) {
            displayCustomerDetails(customer);
        } else {
            cout << "Customer not found.\n";
        }
    } else {
        cout << "Invalid choice.\n";
    }
}

void Mess::deleteCustomer() {
    cout << "Enter Customer Name to Delete: ";
    string name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    Node *temp = head, *prev = nullptr;
    while (temp) {
        if (temp->name == name) {
            if (prev) {
                prev->next = temp->next;
            } else {
                head = temp->next;
            }
            delete temp;
            cout << "Customer deleted successfully.\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    cout << "Customer not found.\n";
}

void Mess::saveToFile() {
    ofstream file("Report.txt");
    if (!file) {
        cout << "Failed to open file for writing.\n";
        return;
    }

    Node *temp = head;
    while (temp) {
        file << "Name: " << temp->name << "\n";
        file << "Phone: " << temp->phone << "\n";
        file << "Joining Date: " << temp->joinDate << "\n";
        file << "Amount Paid: " << temp->amountPaid << "\n";
        file << "Meal Type: ";
        if (temp->type == 1) file << "Lunch\n";
        else if (temp->type == 2) file << "Dinner\n";
        else file << "Both\n";
        file << "------------------------\n";
        temp = temp->next;
    }

    cout << "Customer data saved to Report.txt\n";
}

void Mess::showMenuAndDeductAmount() {
    cout << "Enter Customer Name: ";
    string name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    Node *customer = findCustomerByName(name);
    if (!customer) {
        cout << "Customer not found.\n";
        return;
    }

    const int MENU_SIZE = 3;
    vector<string> menuItems = {"Chicken Biryani", "Paneer Butter Masala", "Gulab Jamun"};
    vector<int> menuPrices = {150, 120, 50};

    cout << "Menu:\n";
    for (int i = 0; i < MENU_SIZE; ++i) {
        cout << i + 1 << ". " << menuItems[i] << " - Rs." << menuPrices[i] << "\n";
    }

    cout << "Enter the item number to order: ";
    int itemNumber;
    cin >> itemNumber;

    if (itemNumber < 1 || itemNumber > MENU_SIZE) {
        cout << "Invalid item number.\n";
        return;
    }

    int price = menuPrices[itemNumber - 1];

    if (customer->amountPaid < price) {
        cout << "Insufficient balance. Please add more funds.\n";
    } else {
        customer->amountPaid -= price;
        cout << "Order successful! Rs." << price << " deducted. Remaining balance: Rs." << customer->amountPaid << "\n";
    }
}

void signUp() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ofstream userFile("users.txt", ios::app);
    userFile << username << " " << password << "\n";
    userFile.close();
    cout << "User registered successfully!\n";
}

bool login() {
    string username, password, fileUsername, filePassword;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream userFile("users.txt");
    while (userFile >> fileUsername >> filePassword) {
        if (fileUsername == username && filePassword == password) {
            userFile.close();
            return true; // Login successful
        }
    }
    userFile.close();
    cout << "Invalid credentials!\n";
    return false; // Login failed
}

int main() {
    Mess mess;
    char choice;

    cout << "Mess Management System\n";
    cout << "1. Sign Up\n2. Login\n";
    cin >> choice;

    if (choice == '1') {
        signUp();
    } else if (choice == '2') {
        if (!login()) {
            return 0; // Exit if login fails
        }
    } else {
        cout << "Invalid choice!\n";
        return 0;
    }

    while (true) {
        cout << "\nMess Management System\n";
        cout << "1. Add New Customer\n";
        cout << "2. Display Customer Info\n";
        cout << "3. Delete Customer\n";
        cout << "4. Show Menu and Deduct Amount\n";
        cout << "5. Save and Exit\n";
        cin >> choice;
        switch (choice) {
            case '1':
                mess.insertCustomer();
                break;
            case '2':
                mess.displayCustomers();
                break;
            case '3':
                mess.deleteCustomer();
                break;
            case '4':
                mess.showMenuAndDeductAmount();
                break;
            case '5':
                mess.saveToFile();
                return 0;
            default:
                cout << "Invalid choice!\n";
                break;
        }
    }
    return 0;
}
