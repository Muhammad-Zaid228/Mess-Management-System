This is a simple Mess Management System implemented in C++ using DSA's approaches to manage customer data, meal orders, and payments for a mess. It allows users to sign up, log in, add customers, manage their meal payments, and save data to a file.

**Features**

**User Management**

Sign up: Register a new user with a username and password.

Login: Authenticate an existing user before accessing the mess management system.

**Customer Management**

Add new customers with details such as name, phone number, meal type, joining date, and amount paid.

Display all customer details or specific customer details.

Delete customer information.

**Meal Management**

Show menu with item prices.

Deduct the cost of meals from the customer's account balance.

**Data Persistence**

Save customer data to a file (Report.txt).

**File Descriptions**

users.txt: Stores user credentials (username and password).

Report.txt: Stores customer details for persistence.
Usage Instructions

**1. Sign Up or Login**

At the start, the system will prompt for either signing up or logging in.

Sign up to create a new account or log in with existing credentials.

**2. Main Menu**

After successful login, the following options are available:

Add New Customer

Input customer details including name, phone number, meal type, joining date, and initial amount paid.

Display Customer Info

Choose to display all customer information or search for a specific customer by name.

Delete Customer

Remove a customer's details by specifying their name.

Show Menu and Deduct Amount

Show a list of available menu items with prices.

Deduct the cost of the selected item from the customer's balance.

Save and Exit

Save all customer data to Report.txt and exit the application.

**Constraints**

Minimum initial amount for a customer is 500.

Meal types:

1: Lunch

2: Dinner

3: Both

Example Menu

1. Chicken Biryani - Rs.150
2. Paneer Butter Masala - Rs.120
3. Gulab Jamun - Rs.50

**Dependencies**

C++ Standard Library

Filesystem for saving and reading data

**Author**

This program was created as a simple project for learning and managing basic customer and file operations in C++.

Feel free to contribute or suggest improvements!
