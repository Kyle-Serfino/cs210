#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

class ItemFrequencyTracker {
private:
    unordered_map<string, int> itemCounts;  

public:
    void read_data(const string& filename) {
        ifstream inputFile(filename);
        string food;
        while (getline(inputFile, food)) {
            increase_amount(food);  //change and update item
        }
        inputFile.close();
    }

    void increase_amount(const string& food) {
        itemCounts[food]++;  //add to item
    }

    int find_count(const string& food) const {
        auto it = itemCounts.find(food);
        if (it != itemCounts.end()) {
            return it->second;
        }
        return 0;
    }

    void display_amounts() const {
        for (const auto& entry : itemCounts) {
            cout << entry.first << ": " << entry.second << endl;  // Display item amounts saving item name and count
        }
    }

    void display_chart() const {
        for (const auto& entry : itemCounts) {
            cout << entry.first << " ";
            for (int i = 0; i < entry.second; i++) {
                cout << "!";  //display historgram with ! shape
            }
            cout << endl;
        }
    }

    void save_data(const string& filename) const {
        ofstream outputFile(filename);
        for (const auto& entry : itemCounts) {
            outputFile << entry.first << ":" << entry.second << endl;  // Save item counts to a file
        }
        outputFile.close();
    }
};

int main() {
    ItemFrequencyTracker tracker;
    tracker.read_data("CS210_Project_Three_Input_File.txt");// has all of the inforamtion from the txt file

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Search for a Food" << endl;
        cout << "2. Display Food counts" << endl;
        cout << "3. Display Food histogram" << endl;
        cout << "4. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // allows for there to be ab uffer clear

        if (choice == 1) {
            string food;
            cout << "Enter the item to search for: ";
            getline(cin, food);
            int count = tracker.find_count(food);
            cout <<  food <<" "<< count << endl;//search item and displayamount
        }else if (choice == 2) {
            tracker.display_amounts();// will show the numbers
        }else if (choice == 3) {
            tracker.display_chart();// will show the ! for the historgram if selected
        }else if (choice == 4) {
            tracker.save_data("frequency.dat");  // Save data to a file
            cout << "Data backup saved to 'frequency.dat' Exiting" << endl;
            break;
        }
        else {
            cout << "Please choose something else." << endl;  //This will make sure you cant break the code
        }
    }

    return 0;
}
