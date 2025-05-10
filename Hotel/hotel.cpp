#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <ctime>

using namespace std;

// Class for individual items (food or rooms)
class Item {
private:
    string name;
    int price;
    int quantity;
    int sold;

public:
    // Constructor
    Item(string name, int price, int quantity = 0) : name(name), price(price), quantity(quantity), sold(0) {}

    // Getters and setters
    string getName() const { return name; }
    int getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    int getSold() const { return sold; }
    int getRemaining() const { return quantity - sold; }
    int getTotalSales() const { return sold * price; }

    void setQuantity(int qty) { quantity = qty; }
    
    // Function to process an order
    bool order(int qty) {
        if (getRemaining() >= qty) {
            sold += qty;
            return true;
        }
        return false;
    }
    
    // Reset sales data
    void resetSales() {
        sold = 0;
    }
};

// Class for handling the hotel inventory and operations
class Hotel {
private:
    vector<Item> inventory;
    string dataFile;
    string customerLogFile;

public:
    // Constructor
    Hotel(string fileName = "hotel_data.txt") : dataFile(fileName), customerLogFile("customer_log.txt") {
        // Initialize default inventory
        inventory.push_back(Item("Room", 1200));
        inventory.push_back(Item("Pasta", 250));
        inventory.push_back(Item("Burger", 120));
        inventory.push_back(Item("Noodles", 140));
        inventory.push_back(Item("Shake", 120));
        inventory.push_back(Item("Chicken Roll", 150));
        
        // Try to load data from file
        loadData();
    }

    // Initialize inventory quantities
    void initializeInventory() {
        cout << "\n\t Quantity of items we have\n";
        
        for (size_t i = 0; i < inventory.size(); i++) {
            int qty;
            cout << "\n" << inventory[i].getName() << " available: ";
            cin >> qty;
            inventory[i].setQuantity(qty);
        }
        
        // Save the updated inventory to file
        saveData();
    }

    // Display menu options
    void displayMenu() {
        cout << "\n\t\t\t Please select from the menu options ";
        
        for (size_t i = 0; i < inventory.size(); i++) {
            cout << "\n" << (i + 1) << ") " << inventory[i].getName();
        }
        
        cout << "\n" << (inventory.size() + 1) << ") Information regarding sales and collection ";
        cout << "\n" << (inventory.size() + 2) << ") Reset daily sales";
        cout << "\n" << (inventory.size() + 3) << ") Save and exit";
        cout << "\n\n Please Enter your choice: ";
    }

    // Process a customer order
    void processOrder(int choice) {
        if (choice < 1 || choice > static_cast<int>(inventory.size())) {
            cout << "\nInvalid choice!";
            return;
        }
        
        int index = choice - 1;
        int quant;
        cout << "\n\n Enter " << inventory[index].getName() << " quantity: ";
        cin >> quant;
        
        if (inventory[index].order(quant)) {
            cout << "\n\n\t\t" << quant << " " << inventory[index].getName();
            
            if (inventory[index].getName() == "Room") {
                cout << "(s) have been allotted to you";
            } else {
                cout << " is the order!";
            }
            
            // Log this transaction
            logTransaction(inventory[index].getName(), quant, inventory[index].getPrice());
            
            // Save after each successful order
            saveData();
            
            // Show bill for this item
            cout << "\n\n Bill details:";
            cout << "\n Item: " << inventory[index].getName();
            cout << "\n Quantity: " << quant; 
            cout << "\n Price per item: $" << inventory[index].getPrice();
            cout << "\n Total: $" << quant * inventory[index].getPrice() << endl;
        } else {
            cout << "\n\tOnly " << inventory[index].getRemaining() << " " 
                 << inventory[index].getName() << " remaining in hotel ";
        }
    }

    // Display sales information
    void displaySalesInfo() {
        cout << "\n\tDetails of sales and collection ";
        
        int totalCollection = 0;
        
        for (const Item& item : inventory) {
            cout << "\n\n Number of " << item.getName() << " we had: " << item.getQuantity();
            cout << "\n Number of " << item.getName() << " we sold: " << item.getSold();
            cout << "\n Remaining " << item.getName() << ": " << item.getRemaining();
            cout << "\n Total " << item.getName() << " collection for the day: $" << item.getTotalSales();
            
            totalCollection += item.getTotalSales();
        }
        
        cout << "\n\n\n Total collection for the day: $" << totalCollection;
    }

    // Save data to file
    void saveData() {
        ofstream outFile(dataFile);
        
        if (!outFile) {
            cout << "\nError: Unable to open file for writing!";
            return;
        }
        
        for (const Item& item : inventory) {
            outFile << item.getName() << "," 
                   << item.getPrice() << "," 
                   << item.getQuantity() << "," 
                   << item.getSold() << endl;
        }
        
        outFile.close();
    }

    // Load data from file
    void loadData() {
        ifstream inFile(dataFile);
        
        if (!inFile) {
            cout << "\nNo previous data found. Starting with empty inventory.";
            return;
        }
        
        string line;
        inventory.clear();
        
        while (getline(inFile, line)) {
            try {
                size_t pos = 0;
                vector<string> tokens;
                
                // Split the line by commas
                while ((pos = line.find(',')) != string::npos) {
                    tokens.push_back(line.substr(0, pos));
                    line.erase(0, pos + 1);
                }
                tokens.push_back(line);
                
                if (tokens.size() == 4) {
                    string name = tokens[0];
                    int price = stoi(tokens[1]);
                    int quantity = stoi(tokens[2]);
                    int sold = stoi(tokens[3]);
                    
                    Item item(name, price, quantity);
                    // Manually set sold items since we don't have a direct setter
                    for (int i = 0; i < sold; i++) {
                        item.order(1);
                    }
                    
                    inventory.push_back(item);
                }
            } catch (const exception& e) {
                cout << "\nError parsing file: " << e.what();
                inventory.clear();
                break;
            }
        }
        
        inFile.close();
        
        if (inventory.empty()) {
            cout << "\nInvalid data format. Starting with default inventory.";
            // Reinitialize with default inventory
            inventory.push_back(Item("Room", 1200));
            inventory.push_back(Item("Pasta", 80));
            inventory.push_back(Item("Burger", 120));
            inventory.push_back(Item("Noodles", 50));
            inventory.push_back(Item("Shake", 120));
            inventory.push_back(Item("Chicken Roll", 150));
        } else {
            cout << "\nPrevious data loaded successfully!";
        }
    }

    // Log transaction to customer log file
    void logTransaction(const string& itemName, int quantity, int price) {
        ofstream logFile(customerLogFile, ios::app);
        if (!logFile) {
            cout << "\nWarning: Unable to log transaction!";
            return;
        }
        
        // Get current time
        time_t now = time(0);
        tm* localTime = localtime(&now);
        char timeStr[80];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);
        
        logFile << timeStr << " - Item: " << itemName 
                << ", Quantity: " << quantity 
                << ", Price: $" << price 
                << ", Total: $" << (quantity * price) << endl;
        
        logFile.close();
    }
    
    // Reset sales data for a new day
    void resetDailySales() {
        char choice;
        cout << "\nDo you want to reset daily sales data? (y/n): ";
        cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            for (Item& item : inventory) {
                item.resetSales();
            }
            saveData();
            
            // Archive the customer log file
            archiveLogFile();
            
            cout << "\nSales data has been reset for a new day!";
        }
    }
    
    // Archive log file with date
    void archiveLogFile() {
        // Get current date for archive filename
        time_t now = time(0);
        tm* localTime = localtime(&now);
        char dateStr[20];
        strftime(dateStr, sizeof(dateStr), "%Y%m%d", localTime);
        
        string archiveFile = "customer_log_" + string(dateStr) + ".txt";
        
        ifstream src(customerLogFile);
        ofstream dst(archiveFile);
        
        if (src && dst) {
            dst << src.rdbuf();
            src.close();
            dst.close();
            
            // Clear the current log file
            ofstream clear(customerLogFile, ios::trunc);
            clear.close();
            
            cout << "\nCustomer log archived to " << archiveFile;
        } else {
            cout << "\nWarning: Unable to archive log file!";
        }
    }
    
    // Get number of items in inventory
    int getInventorySize() const {
        return inventory.size();
    }
    
    // Check if a menu choice is valid
    bool isValidMenuChoice(int choice) {
        return (choice >= 1 && choice <= static_cast<int>(inventory.size() + 3));
    }
    
    // Process menu choice
    bool processMenuChoice(int choice) {
        // Handle item purchases
        if (choice >= 1 && choice <= static_cast<int>(inventory.size())) {
            processOrder(choice);
            return false; // Don't exit
        }
        
        // Handle special options
        switch (choice) {
            case -1: // Invalid input
                cout << "\nPlease enter a valid number!";
                return false;
                
            default:
                if (choice == inventory.size() + 1) {
                    // Sales information
                    displaySalesInfo();
                } else if (choice == inventory.size() + 2) {
                    // Reset daily sales
                    resetDailySales();
                } else if (choice == inventory.size() + 3) {
                    // Save and exit
                    saveData();
                    cout << "\nData saved successfully. Exiting program...";
                    return true; // Exit
                } else {
                    cout << "\nPlease select a valid option!";
                }
                return false;
        }
    }
};

// Class for handling user authentication
class Authentication {
private:
    string usersFile;
    string currentUser;
    bool isLoggedIn;

public:
    Authentication(string fileName = "users.txt") : usersFile(fileName), isLoggedIn(false) {
        // Check if users file exists, if not, create an admin user
        ifstream file(usersFile);
        if (!file) {
            createDefaultAdmin();
        }
    }

    // Create default admin user if no users exist
    void createDefaultAdmin() {
        ofstream file(usersFile);
        if (file) {
            // Format: username,password,role
            file << "admin,admin123,admin" << endl;
            file.close();
            cout << "\nDefault admin user created (username: admin, password: admin123)";
        }
    }

    // Login function
    bool login() {
        string username, password;
        int attempts = 0;
        
        while (attempts < 3) {
            cout << "\n\n=== LOGIN ===";
            cout << "\nUsername: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            
            if (validateUser(username, password)) {
                currentUser = username;
                isLoggedIn = true;
                cout << "\nLogin successful! Welcome, " << username << "!";
                return true;
            } else {
                attempts++;
                cout << "\nInvalid username or password. Attempts remaining: " << (3 - attempts);
            }
        }
        
        cout << "\nToo many failed attempts. Exiting program...";
        return false;
    }

    // Validate user credentials
    bool validateUser(const string& username, const string& password) {
        ifstream file(usersFile);
        if (!file) {
            return false;
        }
        
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            if (pos != string::npos) {
                string storedUsername = line.substr(0, pos);
                line.erase(0, pos + 1);
                
                pos = line.find(',');
                if (pos != string::npos) {
                    string storedPassword = line.substr(0, pos);
                    
                    if (username == storedUsername && password == storedPassword) {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }

    // Check if user is logged in
    bool isUserLoggedIn() const {
        return isLoggedIn;
    }

    // Get current user
    string getCurrentUser() const {
        return currentUser;
    }
};

// Function to clear input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to display welcome message and header
void displayHeader() {
    cout << "\n\t\t\t=================================================";
    cout << "\n\t\t\t|        HOTEL MANAGEMENT SYSTEM                |";
    cout << "\n\t\t\t=================================================";
}

int main() {
    displayHeader();
    
    // Authentication system
    Authentication auth;
    if (!auth.login()) {
        return 1;  // Exit if login fails
    }
    
    Hotel hotel;
    int choice;
    bool firstRun = true;
    
    if (firstRun) {
        cout << "\nDo you want to initialize inventory? (1 for Yes, 0 for No): ";
        int initChoice;
        cin >> initChoice;
        
        if (initChoice == 1) {
            hotel.initializeInventory();
        }
        
        firstRun = false;
    }
    
    while (true) {
        hotel.displayMenu();
        
        // Get user choice with error handling
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;  // Invalid input
        }
        
        // Process the menu choice
        bool shouldExit = hotel.processMenuChoice(choice);
        if (shouldExit) {
            break;
        }
        
        cout << "\n\nPress Enter to continue...";
        clearInputBuffer();
        cin.get();
    }
    
    return 0;
}