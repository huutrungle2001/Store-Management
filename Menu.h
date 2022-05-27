#include "Product.h"
#include "Customer.h"
#include "OrderItem.h"
#include "Order.h"
#include "Manager.h"

class Menu{
private:
	ProductList prodList;
	CustomerList cusList;
	OrderList orderList;

	Manager mng;

	bool running;

	// 0: not logged in
	// 1: admin
	// 2: manager
	// 3: customer
	int role;

	// If logged in as a customer
	Customer* currentCus;

public:
	Menu(){
		role = 0;
		running = true;
		mng.setProductList(prodList);
		mng.setOrderList(orderList);
	}

	void Login(int ID, string password){
		// If exit
		if (ID == -1 && password == "x"){
			running = false;
			return;
		}

		// admin: ID: 0  || password: admin
		if (ID == 0){
			if (password == "admin")
				role = 1;
			return;
		}

		// If accounts belong to a manager
		if (mng.login(ID, password)){
			role = 2;
			return;
		}

		// If accounts belong to a customer
		if (cusList.login(ID, password) == 1){
			currentCus = cusList.findCustomer(ID);
			role = 3;
		}

		return;
	}

	int getRole(){

		return role;
	}

	void MainLoop(){
		prodList.readFile();
		mng.readFile();
		cusList.readFile();
		orderList.readFile(&prodList);

		while (running){
			if (role == 0)
				LoginMenu();
			if (role == 1)
				adminMenu();
			if (role == 2)
				managerMenu();
			if (role == 3)
				customerMenu();
		}

		prodList.toFile();
		cusList.toFile();
		orderList.toFile();
		mng.toFile();
	}

	void LoginMenu(){
		while (role == 0 && running){
			int ID;
			string password;
			cout << "Login to continue! (enter -1, x to exit)" << endl;
			cout << "Enter your ID: "; cin >> ID;
			cout << "Enter your pw: "; cin >> password;
			Login(ID, password);
		}
	}

	void printAdmin(){
		cout << " 1. Add/Edit a manager account." << endl;
		cout << " 2. Add/Edit a a customer account." << endl;
		cout << " 3. Delete a manager account." << endl;
		cout << " 4. Delete a customer account." << endl;
		cout << " 0. Log out." << endl;
		cout << "-1. Exit." << endl;
		cout << "Your choice: ";
	}

	void adminMenu(){
		int option;
		while (running && role == 1){
			printAdmin();
			cin >> option;
			switch(option){
				case 1:
					mng.manageAccount();
					break;
				case 2:
					cusList.manageAccount();
					break;
				case 3:
					mng.deleteAccount();
					break;
				case 4:
					cusList.deleteAccount();
					break;

				case 0:
					role = 0;
					break;
				case -1:
					running = false;
					break;
				default:
					cout << "Invalid option!" << endl;
					break;
			}
		}
	}

	void printManager(){
		cout << " 1. Add/Edit a product." << endl;
		cout << " 2. Delete a product." << endl;

		cout << " 0. Log out." << endl;
		cout << "-1. Exit." << endl;
		cout << "Your option: ";
	}

	void managerMenu(){
		while (running && role == 2){
			printManager();
			int option;
			cin >> option;

			switch(option){
				case 1:
					prodList.addProduct();
					break;
				case 2:
					prodList.deleteProduct();
					break;

				case 0:
					role = 0;
					break;

				case -1:
					running = false;
					break;
				default:
					cout << "Invalid option!" << endl;
					break;
			}
		}
	}

	void printCustomer(){
		cout << " 1. Search for a product." << endl;
		cout << " 2. Add product to the cart." << endl;
		cout << " 3. Print Bill." << endl;
		cout << " 4. Show products list." << endl;
		cout << " 0. Log out." << endl;
		cout << "-1. Exit." << endl;
		cout << "Your choice: ";
	}

	void customerMenu(){
		while (running && role == 3){
			printCustomer();
			int choice;
			cin >> choice;
			switch(choice){
				case 1:
					prodList.findProduct();
					break;
				case 2:
					currentCus -> addItemToCart(prodList);
					break;
				case 3:
					orderList.printBill(currentCus -> printBill());
					break;
				case 4:
					prodList.showList();
					break;

				case 0:
					role = 0;
					break;
				case -1:
					running = false;
					break;
				default:
					cout << "Invalid option!" << endl;
					break;
			}
		}
	}

};

