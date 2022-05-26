#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <map>
#include <fstream>

#include "OrderItem.h"
using namespace std;

class Order {
   private:
    int orderID;
    int customerID;
    int totalOrder;
    map<int, OrderItem*> orderItems;

   public:
    Order() {}

    Order(int orderID, int customerID) {
        this->orderID = orderID;
        this->customerID = customerID;
        this->totalOrder = 0;
    }

    int getSize(){
        return orderItems.size();
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

    int GetTotalOrder() const {
        return totalOrder;
    }

    void SetTotalOrder(int totalOrder) {
        this -> totalOrder = totalOrder;
    }

    void addOrderItem(OrderItem* i){
        if (orderItems.find(i -> GetOrderItemID()) != orderItems.end()){
            return;
        }
        orderItems[i -> GetOrderItemID()] = i;
    }

    int getTotalAmount(){
        int totalAmount = 0;
        for (auto it = orderItems.begin(); it != orderItems.end(); it++){
            OrderItem* item = it -> second;
            totalAmount += item -> GetProductQuantity();
        }

        return totalAmount;
    }

    void viewOrder(){
        cout << "Number of products in bill: " << getTotalAmount() << endl;
        for (auto it = orderItems.begin(); it != orderItems.end(); it++){
            OrderItem* item = it -> second;
            cout << item -> GetOrderItemID() << ": " << item -> GetProductName() << ": " << item -> GetProductQuantity();
            cout << endl;
        }
    }

    void toFile(){
        string filepath = to_string(orderID) + ".txt";
        ofstream file;
        file.open(filepath);

        file << orderID << endl;
        file << customerID << endl;
        file << orderItems.size() << endl; 

        for (auto it = orderItems.begin(); it != orderItems.end(); it++){
            OrderItem* item = it -> second;
            file << item -> GetOrderItemID() << endl;
            file << item -> GetProductName() << endl;
            file << item -> GetProductQuantity() << endl;
        }
    }

    void readFile(string filepath, ProductList* prodList){
        ifstream file;
        file.open(filepath);

        file >> orderID;
        file >> customerID;

        int n;
        file >> n;

        for (int i = 0; i < n; i++){
            int ItemID;
            string name;
            int quantity;

            file >> ItemID;
            file >> name;
            file >> quantity;

            OrderItem* oi = new OrderItem(ItemID, * prodList -> findProduct(name), quantity );
            addOrderItem(oi);
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

    void toFile(){
        ofstream file;
        file.open("orderID.txt");

        file << list.size() << endl;
        for (auto it = list.begin(); it != list.end(); it++){
            file << it -> first << endl;
            it -> second -> toFile();
        }
    }

    void readFile(ProductList* prodList){
        ifstream file;
        file.open("orderID.txt");

        int n;
        file >> n;

        for (int i = 0; i < n; i++){
            Order* o = new Order();
            int ID;
            file >> ID;
            string path = to_string(ID) + ".txt";
            o -> SetOrderID(ID);
            o -> readFile(path, prodList);

            addOrder(o);
        }
    }

};

#endif