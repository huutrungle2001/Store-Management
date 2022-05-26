#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <map>

#include "OrderItem.h"
using namespace std;

class Order {
   private:
    int orderID;
    int customerID;
    int numProducts;
    map<int, OrderItem*> orderItems;

   public:
    Order() {}

    Order(int orderID, int customerID) {
        this->orderID = orderID;
        this->customerID = customerID;
        this->numProducts = 0;
    }

    int getSize(){
        return orderItems.size();
    }

    void placeOrder() {
    }

    int GetOrderID() const {
        return orderID;
    }

    void SetOrderID(int orderID) {
        this -> orderID = orderID;
    }

    int GetCustomerID() const {
        return customerID;
    }

    void SetCustomerID(int customerID) {
        this -> customerID = customerID;
    }

    int GetNumProducts() const {
        return numProducts;
    }

    void SetNumProducts(int numProducts) {
        this -> numProducts = numProducts;
    }

    void addOrderItem(OrderItem* i){
        if (orderItems.find(i -> GetOrderItemID()) != orderItems.end()){
            return;
        }
        orderItems[i -> GetOrderItemID()] = i;
    }

    void viewOrder(){
        for (auto it = orderItems.begin(); it != orderItems.end(); it++){
            OrderItem* item = it -> second;
            cout << item -> GetOrderItemID() << ": " << item -> GetProductName();
            cout << endl;
        }
    }
};

class OrderList{
private:
    map<int, Order*> list;

public:
    OrderList(){}

    void printBill(Order* o){
        addOrder(o);
        o -> viewOrder();
    }

    void addOrder(Order* o){
        o -> SetOrderID(list.size());
        list[o -> GetOrderID()] = o;
    }

    void removeOrder(int ID){
        list.erase(ID);
    }

    void findOrder(){
        int ID;
        cout << "Enter the order ID: "; cin >> ID;

        findOrder(ID);
    }

    void findOrder(int ID){
        if (list.find(ID) == list.end()){
            cout << "Order doesn't exist!";
            return;
        }
        else{
            list[ID] -> viewOrder();
        }

    }

};

#endif