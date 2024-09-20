#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>

using namespace std;

class Expense
{
private:
    double amount;
    string date; // Format: YYYY-MM-DD
    string category;
    string description;

public:
    Expense(double amt, std::string dt, std::string cat, std::string desc)
        : amount(amt), date(dt), category(cat), description(desc) {}

    double getAmount() const { return amount; }
    std::string getDate() const { return date; }
    std::string getCategory() const { return category; }

    void displayExpense() const
    {
        std::cout << std::setw(12) << date << std::setw(10) << amount
                  << std::setw(15) << category << std::setw(20) << description << std::endl;
    }

    string toFileFormat() const
    {
        return to_string(amount) + "," + date + "," + category + "," + description;
    }
};

class User
{
private:
    int userID;
    string username;
    string password;
    vector<Expense> expenses;

public:
    User(int id, std::string uname, std::string pass)
        : userID(id), username(uname), password(pass) {}

    void addExpense();
    void viewExpenses();
    void generateReport();
    bool authenticate(std::string uname, std::string pass);
    void saveExpensesToFile(const std::string &filename);
    void loadExpensesFromFile(const std::string &filename);
};

void User::addExpense()
{
    double amount;
    string date, category, description;

    cout << "Enter amount: ";
    while (!(cin >> amount))
    {
        cout << "Invalid input. Please enter a numeric value for the amount: ";
        cin.clear();                                         // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
    }

    cout << "Enter date (YYYY-MM-DD): ";
    cin >> date;

    cout << "Enter category: ";
    cin >> category;

    cout << "Enter description: ";
    cin.ignore();
    getline(cin, description);

    Expense newExpense(amount, date, category, description);
    expenses.push_back(newExpense);
    cout << "Expense added successfully!\n";
}

void User::viewExpenses()
{
    string period;
    cout << "View expenses for (day/week/month): ";
    cin >> period;

    cout << "\n===== Expenses for the " << period << " =====\n";
    cout << std::setw(12) << "Date" << std::setw(10) << "Amount"
         << std::setw(15) << "Category" << std::setw(20) << "Description" << endl;
    cout << std::string(70, '-') << endl;

    // Use current date handling for better flexibility
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm *localTime = localtime(&currentTime);
    string currentDate = to_string(localTime->tm_year + 1900) + "-" +
                         to_string(localTime->tm_mon + 1) + "-" +
                         to_string(localTime->tm_mday);

    for (const auto &expense : expenses)
    {
        string date = expense.getDate();
        if (period == "day" && date == currentDate)
        {
            expense.displayExpense();
        }
        else if (period == "week")
        {
            // Implement week check (e.g., within the last 7 days)
            // Placeholder logic for demonstration
        }
        else if (period == "month" && date.substr(0, 7) == currentDate.substr(0, 7))
        {
            expense.displayExpense();
        }
    }
    cout << std::string(70, '-') << endl;
}

int main()
{
    User user(1, "john_doe", "password123");

    // Load expenses from a file at startup
    user.loadExpensesFromFile("expenses.txt");

    while (true)
    {
        cout << "\n ------Expense Tracker -------\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Generate Report\n";
        cout << "4. Save Expenses\n";
        cout << "5. Exit\n";
        cout << "Choose an option (1-5): ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            user.addExpense();
            break;
        case 2:
            user.viewExpenses();
            break;
        case 3:
            user.generateReport();
            break;
        case 4:
            user.saveExpensesToFile("expenses.txt");
            break;
        case 5:
            user.saveExpensesToFile("expenses.txt");
            cout << "Exiting... Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }
    }
}
