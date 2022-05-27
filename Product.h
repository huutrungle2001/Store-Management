#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

class Product {
   protected:
    int productID;
    string productName;

    double productRate;

    public:
    Product(){}

    Product(int productID, string productName, double productRate) {
        this->productID = productID;
        this->productName = productName;
        this->productRate = productRate;
    }

    int GetProductID() const {
        return productID;
    }

    void SetProductID(int productID) {
        this -> productID = productID;
    }

    string GetProductName() const {
        return productName;
    }

    void SetProductName(string productName) {
        this -> productName = productName;
    }

    double GetProductRate() const {
        return productRate;
    }

    void SetProductRate(double productRate) {
        this -> productRate = productRate;
    }

    void toFile(ofstream& file){
        file << productID << endl;
        file << productName << endl;
        file << productRate << endl;
    }
};

class ProductList{
private:
    map<int, Product*> list;
public:
    ProductList(){}

    void addProduct(){
        int productID;
        string productName; 
        double productRate;

        cout << "Enter product ID: "; cin >> productID;
        cout << "Enter product name: "; cin >> productName;
        cout << "Enter product rate: "; cin >> productRate;

        Product* p = new Product(productID, productName, productRate);

        addProduct(p);
    }

    void addProduct(int productID,
                    string productName,
                    double productRate){
        Product* p = new Product(productID, productName, productRate);
        addProduct(p);
    }

    void addProduct(Product* p){
        int ID = p -> GetProductID();
        list[ID] = p;
    }

    void deleteProduct(){
        int ID;
        cout << "Enter the delete product ID: "; cin >> ID;
        deleteProduct(ID);
    }

    void deleteProduct(int ID){
        list.erase(ID);
    }

    void printProduct(Product* p){
        if (p != nullptr)
            cout << p -> GetProductID() << ": " << p -> GetProductName() << endl;
        else
            cout << "Product doesn't exist!" << endl;

    }

    void findProduct(){
        string name;
        cout << "Enter the product name: "; cin >> name;
        Product* p = findProduct(name);
        printProduct(p);
    }

    Product* findProduct(string name){
        for (auto it = list.begin(); it != list.end(); it++){
            if (it -> second -> GetProductName() == name){
                return it -> second;
            }
        }
        return nullptr;
    }

    Product* findProduct(int ID){
        if (list.find(ID) != list.end())
            return list[ID];
        return nullptr;
    }

    
    void showList(){
        for (auto it = list.begin(); it != list.end(); it++){
            Product* p = it -> second;
            cout << p -> GetProductID() << ": ";       
            cout << p -> GetProductName() << ": ";       
            cout << p -> GetProductRate() << endl;       
        }
    }

    void toFile(){
        ofstream file;
        file.open("Product.txt");

        if (file.is_open()){
            file << list.size() << endl;
            for (auto it = list.begin(); it != list.end(); it++){
                it -> second -> toFile(file);
            }
        }
    }

    void readFile(){
        ifstream file;
        file.open("Product.txt");
        if (file.is_open()){
            int n;
            file >> n;
            for (int i = 0; i < n; i++){
                int productID;
                string productName; 
                double productRate;
                file >> productID;
                file >> productName;
                file >> productRate;
                addProduct(productID, productName, productRate);
            }
        }
    }
};

#endif