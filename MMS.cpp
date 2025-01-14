#include <wx/wx.h>
#include <wx/textdlg.h>
#include <wx/numdlg.h>
#include <fstream>
#include <vector>
#include <limits>
#include <string>

using namespace std;

const int BASE_COST = 2000;

class Node {
public:
    string name;
    string phone;
    string joinDate;
    int type = 0; // 1: Lunch, 2: Dinner, 3: Both
    int amountPaid = 0;
    Node* next = nullptr;
};

class Mess {
    Node* head = nullptr;

public:
    Mess() { loadFromFile(); }
    ~Mess();

    void insertCustomer();
    void displayCustomers();
    void displayCustomerDetails();
    void deleteCustomer();
    void saveToFile();
    void loadFromFile(); // New function to load data from a file
    void showMenuAndDeductAmount();

private:
    Node* findCustomerByName(const string& name);
    string hashPhoneNumber(const string& phone); // New hashing function
};

Mess::~Mess() {
    saveToFile();
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void Mess::insertCustomer() {
    Node* newCustomer = new Node;

    // Customer Name
    wxTextEntryDialog nameDialog(nullptr, "Enter Customer Name:", "Add Customer");
    if (nameDialog.ShowModal() != wxID_OK) return; // Allow cancellation
    newCustomer->name = nameDialog.GetValue().ToStdString();

    // Phone Number
    wxTextEntryDialog phoneDialog(nullptr, "Enter Phone Number:", "Add Customer");
    if (phoneDialog.ShowModal() != wxID_OK) return; // Allow cancellation
    newCustomer->phone = phoneDialog.GetValue().ToStdString();

    // Meal Type
    wxNumberEntryDialog typeDialog(nullptr, "Enter Meal Type (1: Lunch, 2: Dinner, 3: Both):", "Meal Type", "Add Customer", 1, 1, 3);
    if (typeDialog.ShowModal() != wxID_OK) return; // Allow cancellation
    newCustomer->type = typeDialog.GetValue();

    // Joining Date
    wxTextEntryDialog dateDialog(nullptr, "Enter Joining Date (DD/MM/YYYY):", "Add Customer");
    if (dateDialog.ShowModal() != wxID_OK) return; // Allow cancellation
    newCustomer->joinDate = dateDialog.GetValue().ToStdString();

    // Amount Paid
    wxNumberEntryDialog amountDialog(nullptr, "Enter Amount Paid (Minimum 500):", "Amount Paid", "Add Customer", 500, 500, 100000);
    if (amountDialog.ShowModal() != wxID_OK) return; // Allow cancellation
    newCustomer->amountPaid = amountDialog.GetValue();

    // Insert into linked list
    if (!head) {
        head = newCustomer;
    }
    else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newCustomer;
    }

    wxMessageBox("Customer added successfully!", "Success", wxOK | wxICON_INFORMATION);
}

Node* Mess::findCustomerByName(const string& name) {
    Node* temp = head;
    while (temp) {
        if (temp->name == name) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Hashing function to replace phone number with 'xxxxxxxxxxx'
string Mess::hashPhoneNumber(const string& phone) {
    return "xxxxxxxxxxx";
}

void Mess::displayCustomers() {
    if (!head) {
        wxMessageBox("No customers to display.", "Information", wxOK | wxICON_INFORMATION);
        return;
    }

    wxString message;
    Node* temp = head;
    while (temp) {
        message += wxString::Format("Name: %s\nPhone: %s\nJoining Date: %s\nAmount Paid: %d\nMeal Type: %s\n------------------------\n",
            temp->name, hashPhoneNumber(temp->phone), temp->joinDate, temp->amountPaid,
            temp->type == 1 ? "Lunch" : (temp->type == 2 ? "Dinner" : "Both"));
        temp = temp->next;
    }

    wxMessageBox(message, "Customer List", wxOK | wxICON_INFORMATION);
}

void Mess::displayCustomerDetails() {
    wxTextEntryDialog nameDialog(nullptr, "Enter Customer Name to View Details:", "Customer Details");
    if (nameDialog.ShowModal() != wxID_OK) return;

    string name = nameDialog.GetValue().ToStdString();
    Node* customer = findCustomerByName(name);

    if (!customer) {
        wxMessageBox("Customer not found.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    wxString message = wxString::Format("Name: %s\nPhone: %s\nJoining Date: %s\nAmount Paid: %d\nMeal Type: %s\n",
        customer->name, hashPhoneNumber(customer->phone), customer->joinDate, customer->amountPaid,
        customer->type == 1 ? "Lunch" : (customer->type == 2 ? "Dinner" : "Both"));

    wxMessageBox(message, "Customer Details", wxOK | wxICON_INFORMATION);
}

void Mess::deleteCustomer() {
    wxTextEntryDialog nameDialog(nullptr, "Enter Customer Name to Delete:", "Delete Customer");
    if (nameDialog.ShowModal() != wxID_OK) return;

    string name = nameDialog.GetValue().ToStdString();
    Node* temp = head, * prev = nullptr;

    while (temp) {
        if (temp->name == name) {
            if (prev) {
                prev->next = temp->next;
            }
            else {
                head = temp->next;
            }
            delete temp;
            wxMessageBox("Customer deleted successfully!", "Success", wxOK | wxICON_INFORMATION);
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    wxMessageBox("Customer not found.", "Error", wxOK | wxICON_ERROR);
}

void Mess::saveToFile() {
    ofstream file("customers.txt");
    if (!file) {
        wxMessageBox("Failed to open file for writing.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    Node* temp = head;
    while (temp) {
        file << temp->name << "," << temp->phone << "," << temp->joinDate << "," << temp->type << "," << temp->amountPaid << "\n";
        temp = temp->next;
    }
}

void Mess::loadFromFile() {
    ifstream file("customers.txt");
    if (!file) return;

    string line;
    while (getline(file, line)) {
        Node* newCustomer = new Node;
        size_t pos = 0;

        pos = line.find(",");
        newCustomer->name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(",");
        newCustomer->phone = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(",");
        newCustomer->joinDate = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(",");
        newCustomer->type = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        newCustomer->amountPaid = stoi(line);

        if (!head) {
            head = newCustomer;
        }
        else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newCustomer;
        }
    }
}

void Mess::showMenuAndDeductAmount() {
    wxTextEntryDialog nameDialog(nullptr, "Enter Customer Name:", "Order Menu");
    if (nameDialog.ShowModal() != wxID_OK) return;
    string name = nameDialog.GetValue().ToStdString();

    Node* customer = findCustomerByName(name);
    if (!customer) {
        wxMessageBox("Customer not found.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    const int MENU_SIZE = 3;
    vector<string> menuItems = { "Chicken Biryani", "Paneer Butter Masala", "Gulab Jamun" };
    vector<int> menuPrices = { 150, 120, 50 };

    wxString menuMessage = "Menu:\n";
    for (int i = 0; i < MENU_SIZE; ++i) {
        menuMessage += wxString::Format("%d. %s - Rs.%d\n", i + 1, menuItems[i], menuPrices[i]);
    }

    wxNumberEntryDialog menuDialog(nullptr, menuMessage, "Select Menu Item", "Order Menu", 1, 1, MENU_SIZE);
    if (menuDialog.ShowModal() != wxID_OK) return;

    int itemNumber = menuDialog.GetValue();
    int price = menuPrices[itemNumber - 1];

    if (customer->amountPaid < price) {
        wxMessageBox("Insufficient balance. Please add more funds.", "Error", wxOK | wxICON_ERROR);
    }
    else {
        customer->amountPaid -= price;
        wxMessageBox(wxString::Format("Order successful! Rs.%d deducted. Remaining balance: Rs.%d", price, customer->amountPaid),
            "Success", wxOK | wxICON_INFORMATION);
    }
}

class MessApp : public wxApp {
public:
    virtual bool OnInit();
};

class MainFrame : public wxFrame {
    Mess mess;

public:
    MainFrame();

private:
    void OnAddCustomer(wxCommandEvent&);
    void OnDisplayCustomers(wxCommandEvent&);
    void OnDisplayCustomerDetails(wxCommandEvent&);
    void OnDeleteCustomer(wxCommandEvent&);
    void OnShowMenu(wxCommandEvent&);
    void OnExit(wxCommandEvent&);
};

enum {
    ID_ADD_CUSTOMER = 1,
    ID_DISPLAY_CUSTOMERS,
    ID_DISPLAY_CUSTOMER_DETAILS,
    ID_DELETE_CUSTOMER,
    ID_SHOW_MENU,
    ID_EXIT
};

bool MessApp::OnInit() {
    MainFrame* frame = new MainFrame();
    frame->Show(true);
    return true;
}

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "Mess Management System", wxDefaultPosition, wxSize(600, 400)) {
    wxMenuBar* menuBar = new wxMenuBar;

    wxMenu* menu = new wxMenu;
    menu->Append(ID_ADD_CUSTOMER, "Add Customer");
    menu->Append(ID_DISPLAY_CUSTOMERS, "Display Customers");
    menu->Append(ID_DISPLAY_CUSTOMER_DETAILS, "Display Customer Details");
    menu->Append(ID_DELETE_CUSTOMER, "Delete Customer");
    menu->Append(ID_SHOW_MENU, "Show Menu and Deduct Amount");
    menu->AppendSeparator();
    menu->Append(ID_EXIT, "Exit");

    menuBar->Append(menu, "Options");
    SetMenuBar(menuBar);

    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxStaticText* welcomeText = new wxStaticText(panel, wxID_ANY, "Welcome to MMS", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE);
    wxFont font = welcomeText->GetFont();
    font.SetPointSize(14);
    font.SetWeight(wxFONTWEIGHT_BOLD);
    welcomeText->SetFont(font);

    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    panelSizer->AddStretchSpacer();
    panelSizer->Add(welcomeText, 0, wxALIGN_CENTER_HORIZONTAL);
    panelSizer->AddStretchSpacer();
    panel->SetSizer(panelSizer);

    Bind(wxEVT_MENU, &MainFrame::OnAddCustomer, this, ID_ADD_CUSTOMER);
    Bind(wxEVT_MENU, &MainFrame::OnDisplayCustomers, this, ID_DISPLAY_CUSTOMERS);
    Bind(wxEVT_MENU, &MainFrame::OnDisplayCustomerDetails, this, ID_DISPLAY_CUSTOMER_DETAILS);
    Bind(wxEVT_MENU, &MainFrame::OnDeleteCustomer, this, ID_DELETE_CUSTOMER);
    Bind(wxEVT_MENU, &MainFrame::OnShowMenu, this, ID_SHOW_MENU);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, ID_EXIT);
}

void MainFrame::OnAddCustomer(wxCommandEvent&) {
    mess.insertCustomer();
}

void MainFrame::OnDisplayCustomers(wxCommandEvent&) {
    mess.displayCustomers();
}

void MainFrame::OnDisplayCustomerDetails(wxCommandEvent&) {
    mess.displayCustomerDetails();
}

void MainFrame::OnDeleteCustomer(wxCommandEvent&) {
    mess.deleteCustomer();
}

void MainFrame::OnShowMenu(wxCommandEvent&) {
    mess.showMenuAndDeductAmount();
}

void MainFrame::OnExit(wxCommandEvent&) {
    Close(true);
}

wxIMPLEMENT_APP(MessApp);
