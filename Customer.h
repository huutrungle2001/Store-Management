#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
using namespace std;

class Customer {
   private:
    int customerID;
    string customerName;
    string customerAddress;
    string customerContact;

   public:
    Customer() {}

    Customer(int customerID, string customerName, string customerAddress, string customerContact) {
        this->customerID = customerID;
        this->customerName = customerName;
        this->customerAddress = customerAddress;
        this->customerContact = customerContact;
    }

    int GetCustomerID() const {
        return customerID;
    }

    void SetCustomerID(int customerID) {
        customerID = customerID;
    }

    string GetCustomerName() const {
        return customerName;
    }

    void SetCustomerName(string customerName) {
        customerName = customerName;
    }

    string GetCustomerAddress() const {
        return customerAddress;
    }

    void SetCustomerAddress(string customerAddress) {
        customerAddress = customerAddress;
    }

    string GetCustomerContact() const {
        return customerContact;
    }

    void SetCustomerContact(string customerContact) {
        customerContact = customerContact;
    }
};

#endif