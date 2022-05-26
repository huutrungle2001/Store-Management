#ifndef ORDER_ITEM_H
#define ORDER_ITEM_H
#include <iostream>
using namespace std;

class OrderItem {
   private:
    int orderItemID;
    int productID;

   public:
    OrderItem() {}

    OrderItem(int orderItemID, int productID) {
        this->orderItemID = orderItemID;
        this->productID = productID;
    }

    int GetOrderItemID() const {
        return orderItemID;
    }

    void SetOrderItemID(int orderItemID) {
        orderItemID = orderItemID;
    }

    int GetProductID() const {
        return productID;
    }

    void SetProductID(int productID) {
        productID = productID;
    }
};

#endif