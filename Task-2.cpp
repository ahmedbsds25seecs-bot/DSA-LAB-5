#include <iostream>
#include <string>
#include <limits>

using namespace std;

//Node representing a photo
struct PhotoNode {
    int photoID;
    string photoName;
    string dateTaken;
    string location;
    PhotoNode* next;
    PhotoNode* prev;

    PhotoNode(int id, const string& name, const string& date, const string& loc){
        photoID = id;
        photoName = name;
        dateTaken = date;
        location = loc;
        next = nullptr; 
        prev = nullptr; 
    }
};
class PhotoAlbum {
private:
    PhotoNode* current;

public:
    PhotoAlbum(){
        current = nullptr;
        }
    ~PhotoAlbum() {
        if (!current) return;
        PhotoNode* temp = current;
        do {
            PhotoNode* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != current);
        current = nullptr;
    }
    //1. Inserts photo(node) the end of cdll
    void addPhoto(int id, const string& name, const string& date, const string& loc) {
        PhotoNode* newNode = new PhotoNode(id, name, date, loc);
        
        if (!current) {
            newNode->next = newNode;
            newNode->prev = newNode;
            current = newNode;
        } else {
            PhotoNode* tail = current->prev; //Tail is current->prev in CDLL
            newNode->next = current;
            newNode->prev = tail;
            tail->next = newNode;
            current->prev = newNode;
        }
        cout << "\nsuccessfully added photo: " << name << " (ID: " << id << ")\n";
    }
    //2. Insert Photo After Current
    void insertPhotoAfterCurrent(int id, const string& name, const string& date, const string& loc) {
        if (!current) {
            addPhoto(id, name, date, loc);
            return;
        }
        PhotoNode* newNode = new PhotoNode(id, name, date, loc);
        PhotoNode* nextNode = current->next;

        newNode->next = nextNode;
        newNode->prev = current;
        current->next = newNode;
        nextNode->prev = newNode;

        cout << "\nsuccesfully inserted photo \"" << name << "\" after \"" << current->photoName << "\"\n";
    }
    //3. Remove Photo by Photo ID
    void removePhoto(int id) {
        if (!current) {
            cout << "\nAlbum is empty.\n";
            return;
        }
        PhotoNode* temp = current;
        PhotoNode* target = nullptr;

        do {
            if (temp->photoID == id) {
                target = temp;
                break;
            }
            temp = temp->next;
        } while (temp != current);

        if (!target) {
            cout << "\nPhoto with ID: " << id << " ,not found in album.\n";
            return;
        }
        if (target == current) {
            removeCurrentPhoto();
        } else {
            PhotoNode* prevNode = target->prev;
            PhotoNode* nextNode = target->next;
            prevNode->next = nextNode;
            nextNode->prev = prevNode;

            cout << "\nsuccesfully removed Photo ID: " << id << " (" << target->photoName << ")\n";
            delete target;
        }
    }
    //4. Remove Current Photo
    void removeCurrentPhoto() {
        if (!current) {
            cout << "\nAlbum is empty.\n";
            return;
        }
        if (current->next == current) {
            cout << "\nsuccessfully removed current photo: " << current->photoName << "\nAlbum is now empty.\n";
            delete current;
            current = nullptr;
        } else {
            PhotoNode* toDelete = current;
            PhotoNode* prevNode = current->prev;
            PhotoNode* nextNode = current->next;

            prevNode->next = nextNode;
            nextNode->prev = prevNode;
            current = nextNode; // Next photo becomes current

            cout << "\nsuccessfully removed photo: " << toDelete->photoName << "\nSelected photo is now: " << current->photoName << "\n";
            delete toDelete;
        }
    }
    //5. Move Next
    void moveNext() {
        if (current) {
            current = current->next;
            cout << "\nMoved to next photo: " << current->photoName << "\n";
        } else {
            cout << "\nAlbum is empty.\n";
        }
    }
    //6. Move Previous
    void movePrevious() {
        if (current) {
            current = current->prev;
            cout << "\nMoved to previous photo: " << current->photoName << "\n";
        } else {
            cout << "\nAlbum is empty.\n";
        }
    }
    //7. Display Album Forward
    void displayAlbumForward() const {
        if (!current) {
            cout << "\nAlbum is empty.\n";
            return;
        }
        cout << "\n--- Displaying Album Forward ---\n";
        PhotoNode* temp = current;
        do {
            cout << "ID: " << temp->photoID 
                 << "Name: " << temp->photoName 
                 << "Date: " << temp->dateTaken 
                 << "Location: " << temp->location;
            if (temp == current) cout << "  <-- (SELECTED)";
            cout << "\n";
            temp = temp->next;
        } while (temp != current);
        cout << "--------------------------------\n";
    }
    //8. Display Album Backward
    void displayAlbumBackward() const {
        if (!current) {
            cout << "\nAlbum is empty.\n";
            return;
        }
        cout << "\n--- Displaying Album Backward ---\n";
        PhotoNode* temp = current;
        do {
            cout << "ID: " << temp->photoID 
                 << "Name: " << temp->photoName 
                 << "Date: " << temp->dateTaken 
                 << "Location: " << temp->location;
            if (temp == current) cout << "  <-- (SELECTED)";
            cout << "\n";
            temp = temp->prev;
        } while (temp != current);
        cout << "---------------------------------\n";
    }
    //9. Search Photo by Photo ID
    void searchPhoto(int id) const {
        if (!current) {
            cout << "\nAlbum is empty.\n";
            return;
        }
        PhotoNode* temp = current;
        do {
            if (temp->photoID == id) {
                cout << "\n-----------------------------------\n";
                cout << "\tPHOTO FOUND\n";
                cout << "ID      : " << temp->photoID << "\n";
                cout << "Name    : " << temp->photoName << "\n";
                cout << "Date    : " << temp->dateTaken << "\n";
                cout << "Location: " << temp->location << "\n";
                return;
            }
            temp = temp->next;
        } while (temp != current);
        cout << "\nPhoto with ID " << id << " not found.\n";
    }
    //10. Count Photos
    void countPhotos() const {
        if (!current) {
            cout << "\nTotal Photos: 0\n";
            return;
        }
        int count = 0;
        PhotoNode* temp = current;
        do {
            count++;
            temp = temp->next;
        } while (temp != current);
        cout << "\nTotal Photos in Album: " << count << "\n";
    }
};
int main() {
    PhotoAlbum album;

    int choice;
    do {
        cout << "\n-------------------------------------------------\n";
        cout << "\tCIRCULAR PHOTO ALBUM MENU\n";
        cout << "1. Add Photo (At End)\n";
        cout << "2. Insert Photo After Current\n";
        cout << "3. Remove Photo by ID\n";
        cout << "4. Remove Current Photo\n";
        cout << "5. Move Next\n";
        cout << "6. Move Previous\n";
        cout << "7. Display Album Forward\n";
        cout << "8. Display Album Backward\n";
        cout << "9. Search Photo by ID\n";
        cout << "10. Count Photos\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string name, date, loc;
                cout << "Enter Photo ID: ";
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Photo Name: ";
                getline(cin, name);
                cout << "Enter Date Taken: ";
                getline(cin, date);
                cout << "Enter Location: ";
                getline(cin, loc);
                album.addPhoto(id, name, date, loc);
                break;
            }
            case 2: {
                int id;
                string name, date, loc;
                cout << "Enter Photo ID: ";
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Photo Name: ";
                getline(cin, name);
                cout << "Enter Date Taken: ";
                getline(cin, date);
                cout << "Enter Location: ";
                getline(cin, loc);
                album.insertPhotoAfterCurrent(id, name, date, loc);
                break;
            }
            case 3: {
                int id;
                cout << "Enter Photo ID to remove: ";
                cin >> id;
                album.removePhoto(id);
                break;
            }
            case 4:
                album.removeCurrentPhoto();
                break;
            case 5:
                album.moveNext();
                break;
            case 6:
                album.movePrevious();
                break;
            case 7:
                album.displayAlbumForward();
                break;
            case 8:
                album.displayAlbumBackward();
                break;
            case 9: {
                int id;
                cout << "Enter Photo ID to search: ";
                cin >> id;
                album.searchPhoto(id);
                break;
            }
            case 10:
                album.countPhotos();
                break;
            case 11:
                cout << "\nExiting Photo Album...\n";
                break;
            default:
                cout << "\nOption not present,try again.\n";
        }
    } while (choice != 11);

    return 0;
}