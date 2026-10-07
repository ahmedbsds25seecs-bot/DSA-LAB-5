#include <iostream>
#include <string>
#include <limits>

using namespace std;
//Node structure representing a single browser tab
struct TabNode {
    int tabID;
    string websiteTitle;
    string url;
    TabNode* next;
    TabNode* prev;

    TabNode(int id, string title, string u) 
    {
        tabID = id; 
        websiteTitle = title;
        url = u;
        next = nullptr;
        prev = nullptr;
    }
};
//Class managing the Circular Doubly Linked List of Browser Tabs
class BrowserTabManager {
private:
    TabNode* current;
public:
    BrowserTabManager() : current(nullptr) {}

    //Destructor to free all allocated memory
    ~BrowserTabManager() {
        if (!current) return;
        TabNode* temp = current;
        do {
            TabNode* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != current);
        current = nullptr;
    }
    //1 Inserts a new tab after the current tab
    void openNewTab(int id, const string& title, const string& url) {
        TabNode* newNode = new TabNode(id, title, url);

        if (!current) { //List is empty
            newNode->next = newNode;
            newNode->prev = newNode;
            current = newNode;
        } else { //Insert after current
            TabNode* nextNode = current->next;
            newNode->next = nextNode;
            newNode->prev = current;
            current->next = newNode;
            nextNode->prev = newNode;
            current = newNode; // Set newly opened tab as active
        }
        cout << "\nsuccessfully Opened Tab (" << id << "): " << title << "\n";
    }
    //2. Deletes current tab and advances current pointer
    void closeCurrentTab() {
        if (!current) {
            cout << "\nNo open tabs to close.\n";
            return;
        }
        if (current->next == current) { // Only one tab exists
            cout << "\nsuccessfully Closed Tab (" << current->tabID << "): " << current->websiteTitle << "\n";
            delete current;
            current = nullptr;
        } else {
            TabNode* toDelete = current;
            TabNode* prevNode = current->prev;
            TabNode* nextNode = current->next;

            //Re-link surrounding nodes
            prevNode->next = nextNode;
            nextNode->prev = prevNode;

            current = nextNode; //Move current pointer to the next tab

            cout << "\nsuccessfully Closed Tab (" << toDelete->tabID << "): " << toDelete->websiteTitle << "\n";
            delete toDelete;
        }
    }
    //3. Move to next node
    void moveNext() {
        if (!current) {
            cout << "\nNo tabs available\n";
            return;
        }
        current = current->next;
        cout << "\nActive Tab is now: " << current->tabID << ": " << current->websiteTitle << "\n";
    }
    //4. Move to previous
    void movePrevious() {
        if (!current) {
            cout << "\nWarning: No tabs available\n";
            return;
        }
        current = current->prev;
        cout << "\nActive Tab is now: " << current->tabID << ": " << current->websiteTitle << "\n";
    }
    //5. Display Current Tab
    void displayCurrentTab() const {
        if (!current) {
            cout << "\nNo active tab\n";
            return;
        }
        cout << "\n-----------------------------------\n";
        cout << "\tACTIVE TAB\n";
        cout << "Tab ID: " << current->tabID << "\n";
        cout << "Title : " << current->websiteTitle << "\n";
        cout << "URL   : " << current->url << "\n";
    }
    //6. Display all forward tabs 
    void displayAllTabsForward() const {
        if (!current) {
            cout << "\nNo tabs open.\n";
            return;
        }
        cout << "\n--- Displaying All Tabs Forward ---\n";
        TabNode* temp = current;
        do {
            cout << "ID: " << temp->tabID 
                 << "Title: " << temp->websiteTitle 
                 << "URL: " << temp->url;
            if (temp == current) cout << "  <-- ACTIVE";
            cout << "\n";
            temp = temp->next;
        } while (temp != current); 
        cout << "-----------------------------------\n";
    }
    //7. Display all backward tabs 
    void displayAllTabsBackward() const {
        if (!current) {
            cout << "\nNo tabs open.\n";
            return;
        }
        cout << "\n--- Displaying All Tabs Backward ---\n";
        TabNode* temp = current;
        do {
            cout << "ID: " << temp->tabID 
                 << "Title: " << temp->websiteTitle 
                 << "URL: " << temp->url;
            if (temp == current) cout << "  <-- ACTIVE";
            cout << "\n";
            temp = temp->prev;
        } while (temp != current); 
        cout << "------------------------------------\n";
    }
    //8. Search Tab by ID
    void searchTab(int id) const {
        if (!current) {
            cout << "\nBrowser has no tabs.\n";
            return;
        }
        TabNode* temp = current;
        do {
            if (temp->tabID == id) {
                cout << "\n-----------------------------------\n";
                cout << "\tTAB FOUND\n";
                cout << "Tab ID: " << temp->tabID << "\n";
                cout << "Title : " << temp->websiteTitle << "\n";
                cout << "URL   : " << temp->url << "\n";
                return;
            }
            temp = temp->next;
        } while (temp != current);

        cout << "\nNO Tab with ID " << id << "\n";
    }
};
int main() {
    BrowserTabManager browser;
    int choice;

    do {
        cout << "\n---------------------------------------\n";
        cout << "\tBROWSER TAB MANAGER MENU\n";
        cout << "1. Open New Tab\n";
        cout << "2. Close Current Tab\n";
        cout << "3. Move Next\n";
        cout << "4. Move Previous\n";
        cout << "5. Display Current Tab\n";
        cout << "6. Display All Tabs Forward\n";
        cout << "7. Display All Tabs Backward\n";
        cout << "8. Search Tab\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string title, url;
                cout << "Enter Tab ID: ";
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
                cout << "Enter Website Title: ";
                getline(cin, title);
                cout << "Enter URL: ";
                getline(cin, url);
                browser.openNewTab(id, title, url);
                break;
            }
            case 2:
                browser.closeCurrentTab();
                break;
            case 3:
                browser.moveNext();
                break;
            case 4:
                browser.movePrevious();
                break;
            case 5:
                browser.displayCurrentTab();
                break;
            case 6:
                browser.displayAllTabsForward();
                break;
            case 7:
                browser.displayAllTabsBackward();
                break;
            case 8: {
                int id;
                cout << "Enter Tab ID to search: ";
                cin >> id;
                browser.searchTab(id);
                break;
            }
            case 9:
                cout << "\nClosed Browser Tab Manager\n";
                break;
            default:
                cout << "\nChoseen option not present\n";
        }
    } while (choice != 9);

    return 0;
}