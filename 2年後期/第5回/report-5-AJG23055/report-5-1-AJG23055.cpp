//AJG23055 牧野唯希

#include "assignment5.h"
#include <iostream>
#include <string>

using namespace std;

class apple : public base {
public:
    apple() : base("apple", 1000) {}

    double get_price(double weight) override {
        return unit_price * weight;
    }
};

class yogurt : public base {
private:
    const double container_price = 50;

public:
    yogurt() : base("yogurt", 350) {}

    double get_price(double weight) override {
        return unit_price * weight + container_price;
    }
};

int main() {
    base* product;
    string name;
    double weight;

    while (true) {
        cout << "Enter 'name' (apple or yogurt). ";
        cin >> name;

        cout << "Enter 'weight' (kg). ";
        cin >> weight;

        if (name == "apple") {
            product = new apple();
        } else if (name == "yogurt") {
            product = new yogurt();
        } else {
            cout << "Invalid product name. Please enter 'apple' or 'yogurt'." << endl;
            continue;
        }

        double price = product->get_price(weight);
        cout << "The price of " << product->get_name() << " is " << price << " yen" << endl;

        delete product;
    }

    return 0;
}