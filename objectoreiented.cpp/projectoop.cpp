#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <ctime>
#include <stdexcept>
#include <limits>

class InsufficientFundsException : public std::runtime_error {
public:
    InsufficientFundsException() : std::runtime_error("Error: Insufficient Balance.") {}
};

class LimitExceededException : public std::runtime_error {
public:
    LimitExceededException() : std::runtime_error("Error: Withdrawal limit exceeded.") {}
};

class InvalidAmountException : public std::runtime_error {
public:
    InvalidAmountException() : std::runtime_error("Error: Invalid amount entered (must be positive).") {}
};

template <typename T>
T getValidInput(const std::string& prompt) {
    T value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            return value;
        } else {
            std::cout << "Invalid input. Please enter a valid value.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

class Transaction
{
private:
    float amount;
    std::string type;
    std::string date;

public:
    Transaction(float amt, const std::string &t, const std::string &d)
        : amount(amt), type(t), date(d)
    {
    }

    void showTransaction() const
    {
        std::cout << "[" << date << "] " << type << ": " << amount << std::endl;
    }
};

class adminAccount;
class managerAccount;

class Accounts
{
protected:
    float withdrawed = 0;
    std::string status;
    float withdrawLimit;
    std::vector<Transaction> transactions;
    std::string accountType;
    std::string accountName;
    std::string MPIN;
    float balance;
    
    Accounts(const Accounts &other)
    {
        accountName = other.accountName;
        MPIN = other.MPIN;
        balance = other.balance;
        withdrawLimit = other.withdrawLimit;
        status = other.status;
        transactions = other.transactions;
        accountType = other.accountType;
    }

public:
    Accounts() {}
    Accounts(std::string accountName, std::string MPIN)
    {
        this->accountName = accountName;
        this->MPIN = MPIN;
        balance = 0;
    }
    Accounts(std::string accountName, std::string MPIN, std::string accountType)
    {
        this->accountName = accountName;
        this->MPIN = MPIN;
        this->accountType = accountType;
        balance = 0;
    }

    void Deposit(float amount)
    {
        if (amount <= 0) {
            throw InvalidAmountException();
        }
        this->balance += amount;
        addTransaction(amount, "Deposit");
        std::cout << "Balance Deposited Successfully" << std::endl;
    }

    float getwithdrawlimit()
    {
        return withdrawLimit;
    }

    void Withdraw(float amount)
    {
        if (amount <= 0) {
            throw InvalidAmountException();
        }
        if (amount > this->balance) {
            throw InsufficientFundsException();
        }
        if (amount > this->getRemainingLimit()) {
            throw LimitExceededException();
        }

        addTransaction(amount, "Withdraw");
        this->balance -= amount;
        withdrawed += amount;
        std::cout << "Withdraw: " << amount << std::endl;
    }

    std::string getCurrentDate()
    {
        time_t t = time(nullptr);
        std::string date = ctime(&t);
        if (!date.empty()) date.pop_back();
        return date;
    }

    void addTransaction(float amount, const std::string &type)
    {
        transactions.emplace_back(amount, type, getCurrentDate());
    }

    void balanceInquiry()
    {
        std::cout << "Current Balance: " << this->balance << std::endl;
    }

    void ChangeMPIN()
    {
        while (true)
        {
            std::string tempMPIN;
            std::cout << "Enter your current MPIN: ";
            std::cin >> tempMPIN;

            if (tempMPIN == MPIN)
            {
                std::cout << "Enter new MPIN: ";
                std::cin >> tempMPIN;
                if (!isValidMPIN(tempMPIN)) {
                    std::cout << "New MPIN is invalid (must be 4 digits).\n";
                    continue;
                }
                MPIN = tempMPIN;
                std::cout << "MPIN changed successfully.\n";
                return;
            }
            else
            {
                int choice = getValidInput<int>("Incorrect MPIN\n1. Retry\n2. Exit\nChoice: ");
                if (choice != 1)
                    return;
            }
        }
    }

    bool checkUser(std::string user)
    {
        return this->accountName == user;
    }
    void setStatus(const std::string &s)
    {
        status = s;
    }
    void setWithdrawLimit(float w)
    {
        withdrawLimit = w;
    }
    void setAccountType(const std::string &type)
    {
        accountType = type;
    }

    bool isValidMPIN(const std::string &MPIN)
    {
        if (MPIN.size() != 4)
            return false;

        for (char c : MPIN)
            if (!isdigit(c))
                return false;

        return true;
    }
    float getRemainingLimit()
    {
        return withdrawLimit - withdrawed;
    }
    std::string getAccoutName()
    {
        return accountName;
    }
    std::string getMPIN()
    {
        return MPIN;
    }
    std::string getAccountType()
    {
        return accountType;
    }
    float getBalance()
    {
        return balance;
    }
    void removeBalance(float amount)
    {
        this->balance -= amount;
    }
    void addBalance(float amount)
    {
        this->balance += amount;
    }
    std::string getStatus()
    {
        return status;
    }
    std::vector<Transaction> &getTransactionsHistory()
    {
        return transactions;
    }

    virtual ~Accounts() {}
};

class userAccount : public Accounts
{
public:
    userAccount() {}
    userAccount(const std::string &name, const std::string &pin)
        : Accounts(name, pin)
    {
        accountType = "User";
        withdrawLimit = 50000;
        status = "Active";
    }
    userAccount(const Accounts &acc) : Accounts(acc)
    {
        accountType = "User";
        withdrawLimit = 50000;
        status = "Active";
    }

    void transfer(userAccount &u1, float amount)
    {
        if (amount <= 0) throw InvalidAmountException();
        if (amount > this->getBalance()) throw InsufficientFundsException();
        if (amount > this->getwithdrawlimit()) throw LimitExceededException();

        this->removeBalance(amount);
        u1.addBalance(amount);
        this->addTransaction(amount, "Transfer to " + u1.getAccoutName());
        u1.addTransaction(amount, "Transfer from " + getAccoutName());
        std::cout << "Transfer was Successful.\n";
    }
};

class adminAccount : public Accounts
{
public:
    adminAccount(const Accounts &acc) : Accounts(acc)
    {
        accountType = "Admin";
    }
    void freezeAccount(userAccount &u)
    {
        u.setStatus("Frozen");
        std::cout << u.getAccoutName() << " has been frozen.\n";
    }

    void terminateAccount(userAccount &u)
    {
        u.setStatus("Terminated");
        std::cout << u.getAccoutName() << " has been terminated." << std::endl;
    }

    void increaseLimit(userAccount &u, float amount)
    {
        if (amount <= 0) throw InvalidAmountException();
        u.setWithdrawLimit(u.getwithdrawlimit() + amount);
        std::cout << u.getAccoutName() << "'s withdraw limit increased by " << amount << std::endl;
    }

    void convertUserToAdmin(std::vector<Accounts *> &accounts, int index)
    {
        if(index < 0 || index >= accounts.size()) throw std::out_of_range("Invalid account index.");
        if (accounts[index]->getAccountType() != "User")
        {
            std::cout << "Account is not a User.\n";
            return;
        }

        adminAccount *admin = new adminAccount(*accounts[index]);

        delete accounts[index];
        accounts[index] = admin;

        std::cout << "User converted to admin successfully.\n";
    }
};

class managerAccount : public Accounts
{
public:
    managerAccount(const Accounts &acc) : Accounts(acc)
    {
        accountType = "Manager";
    }
    void convertAdminToUser(std::vector<Accounts *> &accounts, int index)
    {
        if(index < 0 || index >= accounts.size()) throw std::out_of_range("Invalid account index.");

        if (accounts[index]->getAccountType() != "Admin")
        {
            std::cout << "Account is not an Admin.\n";
            return;
        }

        userAccount *user = new userAccount(*accounts[index]);

        delete accounts[index];
        accounts[index] = user;

        std::cout << "Admin converted to User successfully.\n";
    }

    void increaseLimit(userAccount &u, float amount)
    {
        if(amount <= 0) throw InvalidAmountException();
        u.setWithdrawLimit(u.getwithdrawlimit() + amount);
        std::cout << u.getAccoutName() << "'s withdraw limit increased by " << amount << std::endl;
    }

    void convertUserToAdmin(std::vector<Accounts *> &accounts, int index)
    {
        if(index < 0 || index >= accounts.size()) throw std::out_of_range("Invalid account index.");

        if (accounts[index]->getAccountType() != "User")
        {
            std::cout << "Not a user account.\n";
            return;
        }

        adminAccount *admin = new adminAccount(*accounts[index]);

        delete accounts[index];
        accounts[index] = admin;

        std::cout << "User promoted to Admin successfully.\n";
    }

    void promoteAdminToManager(std::vector<Accounts *> &accounts, int index)
    {
        if(index < 0 || index >= accounts.size()) throw std::out_of_range("Invalid account index.");

        if (accounts[index]->getAccountType() != "Admin")
        {
            std::cout << "Account is not an Admin.\n";
            return;
        }

        managerAccount *manager = new managerAccount(*accounts[index]);

        delete accounts[index];
        accounts[index] = manager;

        std::cout << "Admin promoted to Manager successfully.\n";
    }
};

void userDashboard(std::vector<Accounts *> &, int);
void adminDashboard(std::vector<Accounts *> &, int);
void managerDashboard(std::vector<Accounts *> &, int);

void createAccount(std::vector<Accounts *> &accountData)
{
    std::string accountName;
    std::string MPIN;
    
    try {
        while (true)
        {
            int rts = 0;
            std::cout << "Enter User Name: ";
            std::cin >> accountName;
            
            for (int i = 0; i < accountData.size(); i++)
            {
                if (accountData[i]->checkUser(accountName))
                {
                    std::cout << "Username Already Registered\n";
                    std::cout << "Would you like to Try Again?\n";
                    int choice = getValidInput<int>("1.Yes\n2.No\nChoice: ");
                    
                    if (choice == 1) {
                        rts = 1;
                        break;
                    } else {
                        rts = 2;
                        break;
                    }
                }
            }
            if (rts == 1) continue;
            else if (rts == 2) return;
            break;
        }

        while (true)
        {
            int rts = 0;
            std::cout << "Enter MPIN (4 digits): ";
            std::cin >> MPIN;
            
            Accounts check;
            if (!check.isValidMPIN(MPIN))
            {
                std::cout << "Invalid MPIN format.\n";
                int choice = getValidInput<int>("Would you like to Try Again?\n1.Yes\n2.No\nChoice: ");
                
                if (choice == 1) continue;
                else return;
            }
            break;
        }
        
        accountData.push_back(new userAccount(accountName, MPIN));
        std::cout << "Account created successfully!\n";
       
    }
    catch (const std::exception& e) {
        std::cerr << "Error creating account: " << e.what() << std::endl;
    }
}

void Login(std::vector<Accounts *> &accountData)
{
    int choice;
    bool founduser = false;
    int userindex;
    std::string userName;
    std::string MPIN;

    while (true)
    {
        std::cout << "Enter User Name: ";
        std::cin >> userName;
        for (int i = 0; i < accountData.size(); i++)
        {
            if (accountData[i]->getAccoutName() == userName)
            {
                founduser = true;
                userindex = i;
                break;
            }
        }
        if (!founduser)
        {
            std::cout << "Couldn't find user\n";
            choice = getValidInput<int>("Would you like to Try Again?\n1.Yes\n2.No\nChoice: ");
            
            if (choice == 1) continue;
            else return;
        }
        break;
    }

    while (true)
    {
        std::cout << "Enter MPIN: ";
        std::cin >> MPIN;
        
        try {
            if (accountData.at(userindex)->getMPIN() != MPIN)
            {
                std::cout << "Incorrect MPIN\n";
                choice = getValidInput<int>("Would you like to Try Again?\n1.Yes\n2.No\nChoice: ");
                
                if (choice == 1) continue;
                else return;
            }
        } catch (const std::out_of_range& e) {
            std::cerr << "System Error: User index out of bounds." << std::endl;
            return;
        }
        break;
    }

    try {
        if (accountData[userindex]->getAccountType() == "User")
        {
            userDashboard(accountData, userindex);
        }
        else if (accountData[userindex]->getAccountType() == "Admin")
        {
            adminDashboard(accountData, userindex);
        }
        else
        {
            managerDashboard(accountData, userindex);
        }
    } catch (const std::exception& e) {
        std::cerr << "A runtime error occurred during session: " << e.what() << std::endl;
    }
}
 // here is mine

void userDashboard(std::vector<Accounts *> &accountData, int index)
{
    userAccount *user = dynamic_cast<userAccount *>(accountData[index]);
    if (!user) {
        std::cerr << "Error: Account type mismatch (Critical Error).\n";
        return;
    }

    int choice;
    while (true)
    {
        std::cout << "\n--- User Dashboard ---\n";
        std::cout << "1. Balance Inquiry\n";
        std::cout << "2. Deposit\n";
        std::cout << "3. Withdraw\n";
        std::cout << "4. Transfer\n";
        std::cout << "5. Change MPIN\n";
        std::cout << "6. Transaction History\n";
        std::cout << "7. Logout\n";
        
        choice = getValidInput<int>("Choice: "); // use here template function

        if (choice == 7) break;

        try {
            switch (choice)
            {
            case 1:
                user->balanceInquiry();
                break;
            case 2:
            {
                float amount = getValidInput<float>("Enter deposit amount: ");
                user->Deposit(amount);
                break;
            }
            case 3:
            {
                float amount = getValidInput<float>("Enter withdraw amount: ");
                user->Withdraw(amount);
                break;
            }
            case 4:
            {
                std::string targetUser;
                std::cout << "Enter recipient username: ";
                std::cin >> targetUser;
                float amount = getValidInput<float>("Enter amount: ");

                int foundIndex = -1;
                for (int i = 0; i < accountData.size(); i++)
                {
                    if (accountData[i]->getAccoutName() == targetUser)
                    {
                        foundIndex = i;
                        break; 
                    }
                }

                if (foundIndex != -1)
                {
                    userAccount *receiver = dynamic_cast<userAccount *>(accountData[foundIndex]);
                    if (receiver)
                        user->transfer(*receiver, amount); 
                    else
                        std::cout << "Recipient is not a user account.\n";
                }
                else
                {
                    std::cout << "Recipient not found.\n";
                }
                break;
            }
            case 5:
                user->ChangeMPIN();
                break;
            case 6:
            {
                std::cout << "--- Transaction History ---\n";
                for (auto &t : user->getTransactionsHistory())
                    t.showTransaction();
                break;
            }
            default:
                std::cout << "Invalid choice!\n";
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "Operation Failed: " << e.what() << std::endl;
        }
    }
}

void adminDashboard(std::vector<Accounts *> &accountData, int index)
{
    adminAccount *admin = dynamic_cast<adminAccount *>(accountData[index]);
    if (!admin) {
        std::cerr << "Error: Account mismatch.\n";
        return;
    }

    int choice;
    while (true)
    {
        std::cout << "\n--- Admin Dashboard ---\n";
        std::cout << "1. View Accounts (Summary)\n";
        std::cout << "2. Freeze Account\n";
        std::cout << "3. Terminate Account\n";
        std::cout << "4. Increase Withdraw Limit\n";
        std::cout << "5. Promote User->Admin\n";
        std::cout << "6. Logout\n";
        
        choice = getValidInput<int>("Choice: ");

        if (choice == 6) break;

        std::string targetUser;
        int foundIndex = -1;

        if (choice >= 2 && choice <= 5)
        {
            std::cout << "Enter target username: ";
            std::cin >> targetUser;
            for (int i = 0; i < accountData.size(); i++) 
            {
                if (accountData[i]->getAccoutName() == targetUser)
                {
                    foundIndex = i;
                    break;
                }
            }
            if (foundIndex == -1)
            {
                std::cout << "User not found!\n";
                continue;
            }
        }

        try {
            switch (choice)
            {
            case 1:
                std::cout << "\n--- System Accounts ---\n";
                for (auto const &acc : accountData)
                {
                    std::cout << "Name: " << acc->getAccoutName() << " | Type: " << acc->getAccountType()
                              << " | Status: " << acc->getStatus() << " | Balance: " << acc->getBalance() << std::endl;
                }
                break;
            case 2:
                if (userAccount *u = dynamic_cast<userAccount *>(accountData[foundIndex]))
                    admin->freezeAccount(*u);
                else
                    std::cout << "Can only freeze User accounts.\n";
                break;
            case 3:
                if (userAccount *u = dynamic_cast<userAccount *>(accountData[foundIndex]))
                    admin->terminateAccount(*u);
                else
                    std::cout << "Can only terminate User accounts.\n";
                break;
            case 4:
            {
                float amount = getValidInput<float>("Enter amount to add to limit: ");
                if (userAccount *u = dynamic_cast<userAccount *>(accountData[foundIndex]))
                    admin->increaseLimit(*u, amount);
                else
                    std::cout << "Target is not a User account.\n";
                break;
            }
            case 5:
                admin->convertUserToAdmin(accountData, foundIndex);
                break;
            default:
                std::cout << "Invalid choice!\n";
            }
        }
        catch (const std::exception& e) {
             std::cout << "Operation Failed: " << e.what() << std::endl;
        }
    }
} //here

void managerDashboard(std::vector<Accounts *> &accountData, int index)
{
    managerAccount *manager = dynamic_cast<managerAccount *>(accountData[index]);
    if (!manager) return;

    int choice;
    while (true)
    {
        std::cout << "\n--- Manager Dashboard ---\n";
        std::cout << "1. System Overview\n";
        std::cout << "2. Demote Admin to User\n";
        std::cout << "3. Promote Admin to Manager\n";
        std::cout << "4. Increase User Withdraw Limit\n";
        std::cout << "5. Promote User to Admin\n";
        std::cout << "6. Logout\n";
        
        choice = getValidInput<int>("Choice: ");

        if (choice == 6) break;

        std::string targetUser;
        int foundIndex = -1;

        if (choice >= 2 && choice <= 5)
        {
            std::cout << "Enter target username: ";
            std::cin >> targetUser;
            for (int i = 0; i < accountData.size(); i++)
            {
                if (accountData[i]->getAccoutName() == targetUser)
                {
                    foundIndex = i;
                    break;
                }
            }
            if (foundIndex == -1)
            {
                std::cout << "Account not found!\n";
                continue;
            }
        }

        try {
            switch (choice)
            {
            case 1:
                for (auto const &acc : accountData)
                {
                    std::cout << "User: " << acc->getAccoutName() << " [" << acc->getAccountType() << "] Balance: " << acc->getBalance() << std::endl;
                }
                break;
            case 2:
                manager->convertAdminToUser(accountData, foundIndex);
                break;
            case 3:
                manager->promoteAdminToManager(accountData, foundIndex);
                break;
            case 4:
            {
                float amount = getValidInput<float>("Enter amount: ");
                if (userAccount *u = dynamic_cast<userAccount *>(accountData[foundIndex]))
                    manager->increaseLimit(*u, amount);
                else
                    std::cout << "Target is not a User.\n";
                break;
            }
            case 5:
                manager->convertUserToAdmin(accountData, foundIndex);
                break;
            default:
                std::cout << "Invalid choice!\n";
            }
        } catch (const std::exception& e) {
             std::cout << "Operation Failed: " << e.what() << std::endl;
        }
    }
}

int main()
{
    std::vector<Accounts *> accountData;

    try {
        Accounts mgrBase("manager", "1234");
        managerAccount *manager = new managerAccount(mgrBase);
        accountData.push_back(manager);

        Accounts adminBase("admin", "1234");
        adminAccount *admin = new adminAccount(adminBase);
        accountData.push_back(admin);

        while (true)
        {
            int choice;
            std::cout << "\nWelcome to BOP Bank" << std::endl;
            std::cout << "1.Create Account" << std::endl;
            std::cout << "2.Login" << std::endl;
            std::cout << "3.Exit" << std::endl;
            
            choice = getValidInput<int>("Choice: ");

            switch (choice)
            {
            case 1:
                createAccount(accountData);
                break;
            case 2:
                Login(accountData);
                break;
            case 3:
                for (Accounts *acc : accountData)
                {
                    delete acc;
                }
                accountData.clear();
                return 0;
            default:
                std::cout << "Invalid Choice" << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Critical System Failure: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown Critical Failure." << std::endl;
    }

    for (Accounts *acc : accountData) delete acc;
    accountData.clear();

    return 0;
}