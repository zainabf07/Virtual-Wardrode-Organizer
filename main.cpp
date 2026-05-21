#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

const int MAX_CLOTHES = 100;
const int MAX_OUTFITS = 50;

// ================= BASE CLASS =================
class ClothingItem {
protected:
    string category, name, color, brand, season, style;

public:
    ClothingItem() {}

    ClothingItem(string cat, string n, string col,
                 string br, string seas, string st)
        : category(cat), name(n), color(col),
          brand(br), season(seas), style(st) {}

    virtual ~ClothingItem() {}

    virtual void displayDetails(int index = -1) const {
        if (index >= 0)
            cout << left << setw(5) << index;

        cout << setw(12) << category
             << setw(18) << name
             << setw(12) << color
             << setw(15) << brand
             << setw(12) << season
             << setw(15) << style << endl;
    }

    // Getters
    string getCategory() const { return category; }
    string getName() const { return name; }
    string getColor() const { return color; }
    string getBrand() const { return brand; }
    string getSeason() const { return season; }
    string getStyle() const { return style; }

    // Setters
    void setName(string n) { name = n; }
    void setColor(string c) { color = c; }
    void setBrand(string b) { brand = b; }
    void setSeason(string s) { season = s; }
    void setStyle(string st) { style = st; }

    string toFileString() const {
        return category + "|" + name + "|" + color + "|" +
               brand + "|" + season + "|" + style;
    }
};

// ================= DERIVED CLASSES =================
class Top : public ClothingItem {
public:
    Top(string n, string col, string br, string seas, string st)
        : ClothingItem("top", n, col, br, seas, st) {}
};

class Bottom : public ClothingItem {
public:
    Bottom(string n, string col, string br, string seas, string st)
        : ClothingItem("bottom", n, col, br, seas, st) {}
};

class Shoes : public ClothingItem {
public:
    Shoes(string n, string col, string br, string seas, string st)
        : ClothingItem("shoes", n, col, br, seas, st) {}
};

class Accessory : public ClothingItem {
public:
    Accessory(string n, string col, string br, string seas, string st)
        : ClothingItem("accessory", n, col, br, seas, st) {}
};

// ================= OUTFIT CLASS =================
class Outfit {
private:
    ClothingItem top, bottom, shoes, accessory;
    bool hasOutfit;

public:
    Outfit() : hasOutfit(false) {}

    Outfit(const ClothingItem& t,
           const ClothingItem& b,
           const ClothingItem& s,
           const ClothingItem& a)
        : top(t), bottom(b), shoes(s), accessory(a), hasOutfit(true) {}

    void displayOutfit() const {
        if (!hasOutfit) {
            cout << "No outfit data.\n";
            return;
        }

        cout << "\n---------------- OUTFIT ----------------\n";

        cout << left
             << setw(12) << "Category"
             << setw(18) << "Name"
             << setw(12) << "Color"
             << setw(15) << "Brand"
             << setw(12) << "Season"
             << setw(15) << "Style" << endl;

        cout << string(84, '-') << endl;

        top.displayDetails();
        bottom.displayDetails();
        shoes.displayDetails();
        accessory.displayDetails();
    }

    string toFileString() const {
        return top.toFileString() + "\n" +
               bottom.toFileString() + "\n" +
               shoes.toFileString() + "\n" +
               accessory.toFileString() + "\n---";
    }
};

// ================= USER WARDROBE =================
class UserWardrobe {
private:
    ClothingItem clothingItems[MAX_CLOTHES];
    int clothingCount = 0;

    Outfit savedOutfits[MAX_OUTFITS];
    int outfitCount = 0;

    ClothingItem createItemFromFile(string cat,
                                    string name,
                                    string col,
                                    string br,
                                    string seas,
                                    string st) {

        if (cat == "top")
            return Top(name, col, br, seas, st);

        if (cat == "bottom")
            return Bottom(name, col, br, seas, st);

        if (cat == "shoes")
            return Shoes(name, col, br, seas, st);

        if (cat == "accessory")
            return Accessory(name, col, br, seas, st);

        return ClothingItem(cat, name, col, br, seas, st);
    }

    void saveAllClothesToFile() {
        ofstream outFile("clothes.txt");

        for (int i = 0; i < clothingCount; i++) {
            outFile << clothingItems[i].toFileString() << endl;
        }

        outFile.close();
    }

    void loadClothesFromFile() {
        ifstream inFile("clothes.txt");

        if (!inFile)
            return;

        string line;

        while (getline(inFile, line) && clothingCount < MAX_CLOTHES) {
            stringstream ss(line);

            string cat, name, col, br, seas, st;

            getline(ss, cat, '|');
            getline(ss, name, '|');
            getline(ss, col, '|');
            getline(ss, br, '|');
            getline(ss, seas, '|');
            getline(ss, st, '|');

            clothingItems[clothingCount++] =
                createItemFromFile(cat, name, col, br, seas, st);
        }

        inFile.close();
    }

    void saveOutfitsToFile() {
        ofstream outFile("outfits.txt");

        for (int i = 0; i < outfitCount; i++) {
            outFile << savedOutfits[i].toFileString() << endl;
        }

        outFile.close();
    }

    void loadOutfitsFromFile() {
        ifstream inFile("outfits.txt");

        if (!inFile)
            return;

        string line;
        ClothingItem items[4];
        int itemIndex = 0;

        while (getline(inFile, line)) {

            if (line == "---") {

                if (itemIndex == 4 && outfitCount < MAX_OUTFITS) {
                    savedOutfits[outfitCount++] =
                        Outfit(items[0], items[1], items[2], items[3]);
                }

                itemIndex = 0;
                continue;
            }

            stringstream ss(line);

            string cat, name, col, br, seas, st;

            getline(ss, cat, '|');
            getline(ss, name, '|');
            getline(ss, col, '|');
            getline(ss, br, '|');
            getline(ss, seas, '|');
            getline(ss, st, '|');

            if (itemIndex < 4) {
                items[itemIndex++] =
                    createItemFromFile(cat, name, col, br, seas, st);
            }
        }

        inFile.close();
    }

    void printHeader() const {
        cout << left
             << setw(5) << "Idx"
             << setw(12) << "Category"
             << setw(18) << "Name"
             << setw(12) << "Color"
             << setw(15) << "Brand"
             << setw(12) << "Season"
             << setw(15) << "Style" << endl;

        cout << string(84, '-') << endl;
    }

public:
    UserWardrobe() {
        loadClothesFromFile();
        loadOutfitsFromFile();
    }

    void addClothingItem(const ClothingItem& item) {

        if (clothingCount >= MAX_CLOTHES) {
            cout << "Wardrobe is full.\n";
            return;
        }

        clothingItems[clothingCount++] = item;

        saveAllClothesToFile();

        cout << "Clothing item added successfully.\n";
    }

    void viewAllClothes() const {

        if (clothingCount == 0) {
            cout << "No clothing items available.\n";
            return;
        }

        cout << "\n---------------- WARDROBE ITEMS ----------------\n";

        printHeader();

        for (int i = 0; i < clothingCount; i++) {
            clothingItems[i].displayDetails(i);
        }
    }

    void removeClothingItem(int index) {

        if (index < 0 || index >= clothingCount) {
            cout << "Invalid index.\n";
            return;
        }

        for (int i = index; i < clothingCount - 1; i++) {
            clothingItems[i] = clothingItems[i + 1];
        }

        clothingCount--;

        saveAllClothesToFile();

        cout << "Clothing item removed successfully.\n";
    }

    void viewClothesByCategory(const string& category) const {

        bool found = false;

        cout << "\nAvailable " << category << " items:\n";

        printHeader();

        for (int i = 0; i < clothingCount; i++) {

            if (clothingItems[i].getCategory() == category) {
                clothingItems[i].displayDetails(i);
                found = true;
            }
        }

        if (!found)
            cout << "No items found.\n";
    }

    void createOutfit() {

        if (outfitCount >= MAX_OUTFITS) {
            cout << "Outfit storage is full.\n";
            return;
        }

        int tIdx, bIdx, sIdx, aIdx;

        while (true) {
            viewClothesByCategory("top");

            cout << "\nEnter index for Top: ";

            if (!(cin >> tIdx)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input.\n";
                continue;
            }

            if (tIdx >= 0 && tIdx < clothingCount &&
                clothingItems[tIdx].getCategory() == "top")
                break;

            cout << "Invalid selection.\n";
        }

        while (true) {
            viewClothesByCategory("bottom");

            cout << "Enter index for Bottom: ";

            if (!(cin >> bIdx)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input.\n";
                continue;
            }

            if (bIdx >= 0 && bIdx < clothingCount &&
                clothingItems[bIdx].getCategory() == "bottom")
                break;

            cout << "Invalid selection.\n";
        }

        while (true) {
            viewClothesByCategory("shoes");

            cout << "Enter index for Shoes: ";

            if (!(cin >> sIdx)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input.\n";
                continue;
            }

            if (sIdx >= 0 && sIdx < clothingCount &&
                clothingItems[sIdx].getCategory() == "shoes")
                break;

            cout << "Invalid selection.\n";
        }

        while (true) {
            viewClothesByCategory("accessory");

            cout << "Enter index for Accessory: ";

            if (!(cin >> aIdx)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input.\n";
                continue;
            }

            if (aIdx >= 0 && aIdx < clothingCount &&
                clothingItems[aIdx].getCategory() == "accessory")
                break;

            cout << "Invalid selection.\n";
        }

        savedOutfits[outfitCount++] =
            Outfit(clothingItems[tIdx],
                   clothingItems[bIdx],
                   clothingItems[sIdx],
                   clothingItems[aIdx]);

        saveOutfitsToFile();

        cout << "Outfit created successfully.\n";
    }

    void viewSavedOutfits() const {

        if (outfitCount == 0) {
            cout << "No outfits saved.\n";
            return;
        }

        for (int i = 0; i < outfitCount; i++) {
            cout << "\n[Outfit " << i + 1 << "]\n";
            savedOutfits[i].displayOutfit();
        }
    }

    void filterByCategory(const string& category) const {

        bool found = false;

        printHeader();

        for (int i = 0; i < clothingCount; i++) {

            if (clothingItems[i].getCategory() == category) {
                clothingItems[i].displayDetails(i);
                found = true;
            }
        }

        if (!found)
            cout << "No items found.\n";
    }

    void filterByColor(const string& color) const {

        bool found = false;

        printHeader();

        for (int i = 0; i < clothingCount; i++) {

            if (clothingItems[i].getColor() == color) {
                clothingItems[i].displayDetails(i);
                found = true;
            }
        }

        if (!found)
            cout << "No items found.\n";
    }

    void filterBySeason(const string& season) const {

        bool found = false;

        printHeader();

        for (int i = 0; i < clothingCount; i++) {

            if (clothingItems[i].getSeason() == season) {
                clothingItems[i].displayDetails(i);
                found = true;
            }
        }

        if (!found)
            cout << "No items found.\n";
    }

    void removeOutfit(int index) {

        if (index < 0 || index >= outfitCount) {
            cout << "Invalid outfit index.\n";
            return;
        }

        for (int i = index; i < outfitCount - 1; i++) {
            savedOutfits[i] = savedOutfits[i + 1];
        }

        outfitCount--;

        saveOutfitsToFile();

        cout << "Outfit removed successfully.\n";
    }

    void editClothingItem() {

        if (clothingCount == 0) {
            cout << "No clothing items available.\n";
            return;
        }

        viewAllClothes();

        int idx;

        cout << "Enter item index to edit: ";

        if (!(cin >> idx)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input.\n";
            return;
        }

        cin.ignore();

        if (idx < 0 || idx >= clothingCount) {
            cout << "Invalid index.\n";
            return;
        }

        string name, color, brand, season, style;

        cout << "Enter new name (leave empty to keep current): ";
        getline(cin, name);

        if (!name.empty())
            clothingItems[idx].setName(name);

        cout << "Enter new color (leave empty to keep current): ";
        getline(cin, color);

        if (!color.empty())
            clothingItems[idx].setColor(color);

        cout << "Enter new brand (leave empty to keep current): ";
        getline(cin, brand);

        if (!brand.empty())
            clothingItems[idx].setBrand(brand);

        cout << "Enter new season (leave empty to keep current): ";
        getline(cin, season);

        if (!season.empty())
            clothingItems[idx].setSeason(season);

        cout << "Enter new style (leave empty to keep current): ";
        getline(cin, style);

        if (!style.empty())
            clothingItems[idx].setStyle(style);

        saveAllClothesToFile();

        cout << "Clothing item updated successfully.\n";
    }
};

// ================= MAIN FUNCTION =================
int main() {

    UserWardrobe uw;

    int choice;

    do {

        cout << "\n========== VIRTUAL WARDROBE MENU ==========\n";

        cout << "1. Add Clothing Item\n";
        cout << "2. View All Clothes\n";
        cout << "3. Remove Clothing Item\n";
        cout << "4. Create Outfit\n";
        cout << "5. View Saved Outfits\n";
        cout << "6. Filter Clothes\n";
        cout << "7. Remove Outfit\n";
        cout << "8. Edit Clothing Item\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input.\n";
            continue;
        }

        cin.ignore();

        if (choice == 1) {

            string cat, name, col, br, seas, st;

            cout << "Enter category (top/bottom/shoes/accessory): ";
            getline(cin, cat);

            transform(cat.begin(), cat.end(), cat.begin(), ::tolower);

            cout << "Enter name: ";
            getline(cin, name);

            cout << "Enter color: ";
            getline(cin, col);

            cout << "Enter brand: ";
            getline(cin, br);

            cout << "Enter season: ";
            getline(cin, seas);

            cout << "Enter style: ";
            getline(cin, st);

            if (cat == "top")
                uw.addClothingItem(Top(name, col, br, seas, st));

            else if (cat == "bottom")
                uw.addClothingItem(Bottom(name, col, br, seas, st));

            else if (cat == "shoes")
                uw.addClothingItem(Shoes(name, col, br, seas, st));

            else if (cat == "accessory")
                uw.addClothingItem(Accessory(name, col, br, seas, st));

            else
                cout << "Invalid category.\n";
        }

        else if (choice == 2) {
            uw.viewAllClothes();
        }

        else if (choice == 3) {

            uw.viewAllClothes();

            int index;

            cout << "Enter item index to remove: ";
            cin >> index;

            uw.removeClothingItem(index);
        }

        else if (choice == 4) {
            uw.createOutfit();
        }

        else if (choice == 5) {
            uw.viewSavedOutfits();
        }

        else if (choice == 6) {

            int filterChoice;
            string value;

            cout << "\n1. Filter by Category\n";
            cout << "2. Filter by Color\n";
            cout << "3. Filter by Season\n";
            cout << "Enter choice: ";

            cin >> filterChoice;
            cin.ignore();

            cout << "Enter value: ";
            getline(cin, value);

            if (filterChoice == 1)
                uw.filterByCategory(value);

            else if (filterChoice == 2)
                uw.filterByColor(value);

            else if (filterChoice == 3)
                uw.filterBySeason(value);

            else
                cout << "Invalid option.\n";
        }

        else if (choice == 7) {

            uw.viewSavedOutfits();

            int index;

            cout << "Enter outfit number to remove: ";
            cin >> index;

            uw.removeOutfit(index - 1);
        }

        else if (choice == 8) {
            uw.editClothingItem();
        }

        else if (choice != 0) {
            cout << "Invalid option.\n";
        }

    } while (choice != 0);

    cout << "Thank you for using Virtual Wardrobe System.\n";

    return 0;
}
