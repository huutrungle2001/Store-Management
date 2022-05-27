#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <fstream>
#include <iostream>

#include "Order.h"

using namespace std;

class Customer {
   private:
    int customerID;
    string customerName;
    string customerAddress;
    string customerContact;
    string password;

    Order* cart;

   public:
    Customer() {
        cart = new Order();
    }

    Customer(int customerID, string customerName, string customerAddress, string customerContact, string password) {
        this->customerID = customerID;
        this->customerName = customerName;
        this->customerAddress = customerAddress;
        this->customerContact = customerContact;
        this->password = password;

        cart = new Order();
        cart->SetCustomerID(customerID);
    }

    int GetCustomerID() const {
        return customerID;
    }

    void SetCustomerID(int customerID) {
        this->customerID = customerID;
    }

    string GetCustomerName() const {
        return customerName;
    }

    void SetCustomerName(string customerName) {
        this->customerName = customerName;
    }

    string GetCustomerAddress() const {
        return customerAddress;
    }

    void SetCustomerAddress(string customerAddress) {
        this->customerAddress = customerAddress;
    }

    string GetCustomerContact() const {
        return customerContact;
    }

    void SetCustomerContact(string customerContact) {
        this->customerContact = customerContact;
    }

    string GetCustomerPassword() const {
        return password;
    }

    void SetCustomerPassword(string password) {
        this->password = password;
    }

    Order* printBill() {
        return cart;
    }

    void addItemToCart(ProductList prodList) {
        int ID;
        cout << "Enter the product ID: ";
        cin >> ID;
        if (prodList.findProduct(ID) == nullptr) {
            cout << "Product doesn't exist!" << endl;
            return;
        }
        int quantity;
        cout << "Enter the quantity: ";
        cin >> quantity;

        // Hash
        int orderID = customerID * 1000 + ID * 100 + quantity * 10;

        OrderItem* item = new OrderItem(orderID, *prodList.findProduct(ID), quantity);
        cart->addOrderItem(item);
    }

    void toFile(ofstream& file) {
        file << customerID << endl;
        file << customerName << endl;
        file << customerAddress << endl;
        file << customerContact << endl;
        file << password << endl;
    }
};

class CustomerList {
   private:
    // map chứa data của các customers
    map<int, Customer*> list;
    // map chứa password của các customers
    map<int, string> accounts;

   public:
    CustomerList() {}

    void addCustomer(Customer* c) {
        int ID = c->GetCustomerID();
        list[ID] = c;
        accounts[ID] = c->GetCustomerPassword();
    }

    Customer* findCustomer(int ID) {
        if (list.find(ID) != list.end())
            return list[ID];
        return nullptr;
    }

    void manageAccount() {
        int ID;
        string password;

        cout << "Enter the custormer ID: ";
        cin >> ID;
        cout << "Enter the custormer pw: ";
        cin >> password;
        if (findCustomer(ID) == nullptr) {
            string customerName;
            string customerAddress;
            string customerContact;
            cout << "Enter the custormer name: ";
            cin >> customerName;
            cout << "Enter the custormer address: ";
            cin >> customerAddress;
            cout << "Enter the custormer contact: ";
            cin >> customerContact;

            Customer* c = new Customer(ID, customerName, customerAddress, customerContact, password);
            addCustomer(c);
        }
        accounts[ID] = password;
    }

    // return:
    // -1: custormer doesn't exist
    //  0: wrong password
    //  1: success
    int login(int ID, string password) {
        if (findCustomer(ID) == nullptr) {
            return -1;
        }

        return (accounts[ID] == password);
    }

    void deleteAccount() {
        int ID;
        string password;
        cout << "Enter the account ID: ";
        cin >> ID;
        cout << "Enter the account pw: ";
        cin >> password;
        deleteAccount(ID, password);
    }

    void deleteAccount(int ID, string password) {
        if (login(ID, password))
            accounts.erase(ID);
    }

    void toFile() {
        ofstream file;
        file.open("Customer.txt");
        file << list.size() << endl;
        for (auto it = list.begin(); it != list.end(); it++) {
            it->second->toFile(file);
        }
    }

    void readFile() {
        ifstream file;
        file.open("Customer.txt");
        int n;
        file >> n;
        for (int i = 0; i < n; i++) {
            int customerID;
            string customerName;
            string customerAddress;
            string customerContact;
            string password;

            file >> customerID;
            file >> customerName;
            file >> customerAddress;
            file >> customerContact;
            file >> password;

            Customer* c = new Customer(customerID, customerName, customerAddress, customerContact, password);
            addCustomer(c);
        }
    }
};

#endif