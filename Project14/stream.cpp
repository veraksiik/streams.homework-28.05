#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>


using namespace std;

class FileManager {
private:
    string product_file;
    string quantity_file;
    string price_file;

public:
    FileManager() {}

    void setFiles(const string& productFile, const string& quantityFile, const string& priceFile) 
    {
        product_file = productFile;
        quantity_file = quantityFile;
        price_file = priceFile;
    }

    bool checkFiles() {
        ifstream product(product_file);
        ifstream quantity(quantity_file);
        ifstream price(price_file);

        if (product.good() && quantity.good() && price.good()) {
            char choice;
            cout << "Файлы уже существуют. Перезаписать данные? (y/n): ";
            cin >> choice;
            return (choice == 'y');
        }
        else {
            return true;
        }
    }

    void getData(string& product, int& quantity, float& price) {
        cout << "Введите название товара: ";
        cin.ignore(); 
        getline(cin, product);
        cout << "Введите количество: ";
        cin >> quantity;
        cout << "Введите цену: ";
        cin >> price;
    }

    void writeData(const string& product, int quantity, float price) {
        ofstream productFile(product_file, ios::app);
        ofstream quantityFile(quantity_file, ios::app);
        ofstream priceFile(price_file, ios::app);

        productFile << product << endl;
        quantityFile << quantity << endl;
        priceFile << price << endl;
    }

    void readData() {
        ifstream productFile(product_file);
        ifstream quantityFile(quantity_file);
        ifstream priceFile(price_file);

        string product;
        int quantity;
        float price;
        int id = 1;

        cout << "Id | Название | Кол-во | Цена" << endl;
        cout << "------------------------------" << endl;

        while (getline(productFile, product)) {
            quantityFile >> quantity;
            priceFile >> price;
            cout << id++ << ") " << product << " "
                << quantity << " " << price << endl;
        }
    }
};

int main() 
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    FileManager fileManager;

    fileManager.setFiles("товары.txt", "количество.txt", "цены.txt");

    if (fileManager.checkFiles()) {
        for (int i = 0; i < 3; ++i) {
            string product;
            int quantity;
            float price;
            fileManager.getData(product, quantity, price);
            fileManager.writeData(product, quantity, price);
        }
    }

    fileManager.readData();

    return 0;
}
