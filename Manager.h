#ifndef MANAGER_H
#define MANAGER_H

#include "Product.h"
#include "Order.h"
#include <map>

class Manager{
private:
	ProductList prodList;
	OrderList ordList;

	int ID;
	string password;

	map<int, string> accounts;

public:
	Manager(){}

	Manager(ProductList& prodList, OrderList& ordList){
		this -> prodList = prodList;
		this -> ordList = ordList;
	}

	void setProductList(ProductList& prodList){
		this -> prodList = prodList;
	}

	void setOrderList(OrderList& ordList){
		this -> ordList = ordList;
	}

	void addProduct(int productID, string productName, double productRate){
		Product* p = new Product(productID, productName, productRate);

		prodList.addProduct(p);
	}

	void deleteProduct(int productID){
		prodList.deleteProduct(productID);
	}

	void manageAccount(){
		int ID; 
		string password;
		cout << "Enter the manager ID: "; cin >> ID;
		cout << "Enter the manager pw: "; cin >> password;

		accounts[ID] = password;
		return;
	}

	void deleteAccount(){
		int ID;
		string password;
		cout << "Enter the account ID: "; cin >> ID;
		cout << "Enter the account pw: "; cin >> password;
		deleteAccount(ID, password);
	}

	void deleteAccount(int ID, string password){
		if (login(ID, password))
			accounts.erase(ID);
	}

	bool login(int ID, string password){
		if (accounts.find(ID) == accounts.end())
			return false;
		return accounts[ID] == password;
	}

	void toFile(){
		ofstream file;
		file.open("Manager.txt");

		file << accounts.size() << endl;

		for (auto it = accounts.begin(); it != accounts.end(); it++){
			file << it -> first << " " << it -> second << endl;
		}
	}

	void readFile(){
		ifstream file;
		file.open("Manager.txt");

		int n;
		file >> n;

		for (int i = 0; i < n; i++){
			int ID;
			string password;
			file >> ID >> password;
			accounts[ID] = password;
		}

		file.close();
	}

};

#endif