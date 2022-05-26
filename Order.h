#ifndef ORDER_H
#define ORDER_H
#include <iostream>
#include <map>

#include "Product.h"
using namespace std;

class Order {
   private:
    int orderID;
    int customerID;
    int numProducts;

   public:
    Order() {}

    Order(int orderID, int customerID, int numProducts) {
        this->orderID = orderID;
        this->customerID = customerID;
        this->numProducts = numProducts;
    }

    void placeOrder() {
    }

    int GetOrderID() const {
        return orderID;
    }

    void SetOrderID(int orderID) {
        orderID = orderID;
    }

    int GetCustomerID() const {
        return customerID;
    }

    void SetCustomerID(int customerID) {
        customerID = customerID;
    }

    int GetNumProducts() const {
        return numProducts;
    }

    void SetNumProducts(int numProducts) {
        numProducts = numProducts;
    }
};

#endif