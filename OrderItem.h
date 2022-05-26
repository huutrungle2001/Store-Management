#ifndef ORDER_ITEM_H
#define ORDER_ITEM_H

#include <iostream>
#include "Product.h"

using namespace std;

class OrderItem:Product {
   private:
    int orderItemID;

   public:

    OrderItem(int orderItemID, Product p) {
        this->orderItemID = orderItemID;
        this->productID = p.GetProductID();
        this->productName = p.GetProductName();
        this->productRate = p.GetProductRate();
    }

    int GetOrderItemID() const {
        return orderItemID;
    }

    string GetProductName() const {
        return productName;
    }

    void SetOrderItemID(int orderItemID) {
        this -> orderItemID = orderItemID;
    }

    int GetProductID() const {
        return productID;
    }

    void SetProductID(int productID) {
        this -> productID = productID;
    }
};

#endif