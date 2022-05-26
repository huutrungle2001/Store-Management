#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
using namespace std;

class Product {
   private:
    int productID;
    string productName;
    double productRate;

   public:
    Product(int productID, string productName, double productRate) {
        this->productID = productID;
        this->productName = productName;
        this->productRate = productRate;
    }

    int GetProductID() const {
        return productID;
    }

    void SetProductID(int productID) {
        productID = productID;
    }

    string GetProductName() const {
        return productName;
    }

    void SetProductName(string productName) {
        productName = productName;
    }

    double GetProductRate() const {
        return productRate;
    }

    void SetProductRate(double productRate) {
        productRate = productRate;
    }
};

#endif