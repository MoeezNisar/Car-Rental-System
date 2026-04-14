#include <iostream>
#include <windows.h>
using namespace std;

const int MAX = 100;

int car_count = 0;
int customer_count = 0;

// ======== CAR CLASS =========
class Car {
public:
    string car_type[MAX];
    string car_model[MAX];
    double car_price[MAX];

    void add_car(int index) {
        cout << "Enter Car Name: ";
        cin >> car_type[index];
        cout << "Enter Car Model: ";
        cin >> car_model[index];
        cout << "Enter Car Price: ";
        cin >> car_price[index];
    }

    void view_cars() {
        if (car_count == 0) {
            cout << "No cars available!\n";
            return;
        }
        for (int i = 0; i < car_count; i++) {
            cout << "Car " << i + 1 << ":\n";
            cout << "Name: " << car_type[i]
                 << "\nModel: " << car_model[i]
                 << "\nPrice: $" << car_price[i] << "\n\n";
        }
    }
};

// ======== CUSTOMER CLASS =========
class Customer {
public:
    string cust_name[MAX];
    string cust_gender[MAX];
    string cust_location[MAX];
    string cust_contact[MAX];

    void add_customer(int index) {
        cout << "Enter Customer Name: ";
        cin >> cust_name[index];
        cout << "Enter Gender: ";
        cin >> cust_gender[index];
        cout << "Enter Location: ";
        cin >> cust_location[index];
        cout << "Enter Contact Number: ";
        cin >> cust_contact[index];
    }

    void view_customers() {
        if (customer_count == 0) {
            cout << "No customers found.\n";
            return;
        }
        for (int i = 0; i < customer_count; i++) {
            cout << "Customer " << i + 1 << ":\n";
            cout << "Name: " << cust_name[i]
                 << "\nGender: " << cust_gender[i]
                 << "\nLocation: " << cust_location[i]
                 << "\nContact: " << cust_contact[i] << "\n\n";
        }
    }

    void delete_customer() {
        if (customer_count == 0) {
            cout << "No customers to delete.\n";
            return;
        }
        for (int i = 0; i < customer_count; i++) {
            cout << i + 1 << ". " << cust_name[i] << " - " << cust_contact[i] << endl;
        }
        int del;
        cout << "Enter customer number to delete: ";
        cin >> del;
        if (del >= 1 && del <= customer_count) {
            for (int i = del - 1; i < customer_count - 1; i++) {
                cust_name[i] = cust_name[i + 1];
                cust_gender[i] = cust_gender[i + 1];
                cust_location[i] = cust_location[i + 1];
                cust_contact[i] = cust_contact[i + 1];
            }
            customer_count--;
            cout << "Customer deleted successfully.\n";
        } else {
            cout << "Invalid choice.\n";
        }
    }
};

// ======== RECEIPT CLASS =========
class Receipt {
    string customer_name;
    string customer_contact;
    string car_name;
    string car_model;
    double price_per_day;
    int rental_days;

public:
    void set_data(string cname, string contact,
                  string car, string model,
                  double price, int days) {
        customer_name = cname;
        customer_contact = contact;
        car_name = car;
        car_model = model;
        price_per_day = price;
        rental_days = days;
    }

    void show_receipt() const {
        if (customer_name.empty()) {
            cout << "\nNo receipt generated yet.\n";
            Sleep(1500);
            return;
        }
        cout << "\n=========== RENTAL RECEIPT ===========\n";
        cout << "Customer Name : " << customer_name << "\n";
        cout << "Contact       : " << customer_contact << "\n";
        cout << "Car Name      : " << car_name << "\n";
        cout << "Car Model     : " << car_model << "\n";
        cout << "Price/Day     : $" << price_per_day << "\n";
        cout << "Days Rented   : " << rental_days << "\n";
        cout << "--------------------------------------\n";
        cout << "Total Price   : $" << (price_per_day * rental_days) << "\n";
        cout << "======================================\n";
        Sleep(4000);
    }
};

// ======== BOOKING CLASS =========
class Booking {
    int bookings[MAX];
    int booking_count = 0;

public:
    void add_booking(Car& cars, Customer& custs, Receipt& receipt) {
        int car_index, cust_index, days;
        cout << "Enter Car Number (0 to " << car_count - 1 << "): ";
        cin >> car_index;
        cout << "Enter Customer Number (0 to " << customer_count - 1 << "): ";
        cin >> cust_index;

        if (car_index >= 0 && car_index < car_count &&
            cust_index >= 0 && cust_index < customer_count &&
            !cars.car_type[car_index].empty() &&
            !custs.cust_name[cust_index].empty()) {

            cout << "Enter number of rental days: ";
            cin >> days;

            bookings[booking_count++] = car_index;

            receipt.set_data(
                custs.cust_name[cust_index],
                custs.cust_contact[cust_index],
                cars.car_type[car_index],
                cars.car_model[car_index],
                cars.car_price[car_index],
                days
            );

            cout << "Booking successful!\n";
            Sleep(1000);

        } else {
            cout << "Invalid car or customer selection!\n";
            Sleep(2000);
        }
    }

    void delete_booking(Car& cars) {
        if (booking_count == 0) {
            cout << "No bookings to delete.\n";
            Sleep(1500);
            return;
        }
        for (int i = 0; i < booking_count; i++) {
            int idx = bookings[i];
            cout << i + 1 << ". Car: " << cars.car_type[idx] << " - " << cars.car_model[idx] << endl;
        }
        int del;
        cout << "Enter booking number to delete: ";
        cin >> del;
        if (del >= 1 && del <= booking_count) {
            for (int i = del - 1; i < booking_count - 1; i++) {
                bookings[i] = bookings[i + 1];
            }
            booking_count--;
            cout << "Booking deleted.\n";
        } else {
            cout << "Invalid selection.\n";
        }
        Sleep(2000);
    }

    void show_menu(Car& cars, Customer& custs, Receipt& receipt) {
        int ch;
        do {
            system("cls");
            cout << "====== BOOKING MENU ======\n";
            cout << "1. New Booking\n2. Delete Booking\n0. Back\nChoice: ";
            cin >> ch;
            switch (ch) {
                case 1: add_booking(cars, custs, receipt); break;
                case 2: delete_booking(cars); break;
                case 0: break;
                default: cout << "Invalid option.\n"; Sleep(1500);
            }
        } while (ch != 0);
    }
};

// ======== MENUS =========
void car_menu(Car& cars) {
    int ch;
    system("cls");
    cout << "====== CAR MENU ======\n";
    cout << "1. Add Car\n2. View Cars\nChoice: ";
    cin >> ch;
    switch (ch) {
        case 1: {
            int n;
            cout << "How many cars to add? ";
            cin >> n;
            for (int i = car_count; i < car_count + n && i < MAX; i++) {
                system("cls");
                cars.add_car(i);
            }
            car_count += n;
            break;
        }
        case 2: cars.view_cars(); Sleep(3000); break;
        default: cout << "Invalid option!\n"; Sleep(1500);
    }
}

void customer_menu(Customer& custs) {
    int ch;
    do {
        system("cls");
        cout << "====== CUSTOMER MENU ======\n";
        cout << "1. Add Customer\n2. View Customers\n3. Delete Customer\n0. Back\nChoice: ";
        cin >> ch;
        switch (ch) {
            case 1: {
                int n;
                cout << "How many customers to add? ";
                cin >> n;
                for (int i = customer_count; i < customer_count + n && i < MAX; i++) {
                    system("cls");
                    custs.add_customer(i);
                }
                customer_count += n;
                break;
            }
            case 2: custs.view_customers(); Sleep(3000); break;
            case 3: custs.delete_customer(); Sleep(2000); break;
            case 0: break;
            default: cout << "Invalid option!\n"; Sleep(1500);
        }
    } while (ch != 0);
}

int main() {
    Car cars;
    Customer custs;
    Booking bookings;
    Receipt receipt;

    int ch;
    do {
        system("cls");
        cout << "=== CAR RENTAL SYSTEM ===\n";
        cout << "1. Car Menu\n";
        cout << "2. Customer Menu\n";
        cout << "3. Booking Menu\n";
        cout << "4. View Receipt\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> ch;

        switch (ch) {
            case 1: car_menu(cars); break;
            case 2: customer_menu(custs); break;
            case 3: bookings.show_menu(cars, custs, receipt); break;
            case 4: receipt.show_receipt(); break;
            case 0:
                cout << "Thanks for using the system!\n";
                break;
            default:
                cout << "Invalid option!\n";
                Sleep(1500);
        }
    } while (ch != 0);

    return 0;
}

