#include <iostream>
#include <string>
#include <limits>

using namespace std;

//Node structure for Train Coach
struct CoachNode {
    int coachNumber;
    string coachType;
    int passengerCapacity;
    int currentPassengers;
    CoachNode* next;
    CoachNode* prev;

    CoachNode(int num, const string& type, int cap, int curr){
        coachNumber = num;
        coachType = type;
        passengerCapacity = cap;
        currentPassengers = curr; 
        next = nullptr;
        prev = nullptr;
        }
};

class TrainSystem {
private:
    CoachNode* current;

public:
    TrainSystem(){
        current = nullptr;

    }

    ~TrainSystem() {
        if (!current) return;
        CoachNode* temp = current;
        do {
            CoachNode* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != current);
        current = nullptr;
    }
    //1. Append coach at the end of list(circular train)
    void addCoach(int num, const string& type, int cap, int curr) {
        CoachNode* newNode = new CoachNode(num, type, cap, curr);
        if (!current) {
            newNode->next = newNode;
            newNode->prev = newNode;
            current = newNode;
        } else {
            CoachNode* tail = current->prev;
            newNode->next = current;
            newNode->prev = tail;
            tail->next = newNode;
            current->prev = newNode;
        }
        cout << "\nCoach (" << num << " - " << type << ") added to train.\n";
    }
    //2. Insert a coach after a specified coach number
    void insertCoach(int afterNum, int num, const string& type, int cap, int curr) {
        if (!current) {
            cout << "\nTrain is empty, adding as first coach.\n";
            addCoach(num, type, cap, curr);
            return;
        }
        CoachNode* temp = current;
        CoachNode* target = nullptr;

        do {
            if (temp->coachNumber == afterNum) {
                target = temp;
                break;
            }
            temp = temp->next;
        } while (temp != current);

        if (!target) {
            cout << "\nCoach " << afterNum << " not found, cannot insert.\n";
            return;
        }
        CoachNode* newNode = new CoachNode(num, type, cap, curr);
        CoachNode* nextNode = target->next;

        newNode->next = nextNode;
        newNode->prev = target;
        target->next = newNode;
        nextNode->prev = newNode;

        cout << "\nInserted Coach (" << num << ") after Coach (" << afterNum << ")\n";
    }
    //3. Remove Coach by Coach Number
    void removeCoach(int num) {
        if (!current) {
            cout << "\nTrain is empty.\n";
            return;
        }
        CoachNode* temp = current;
        CoachNode* target = nullptr;

        do {
            if (temp->coachNumber == num) {
                target = temp;
                break;
            }
            temp = temp->next;
        } while (temp != current);

        if (!target) {
            cout << "\noach Number " << num << " not found.\n";
            return;
        }
        if (target->next == target) { // Only one coach exists
            cout << "\nRemoved Coach (" << num << "), train is now empty.\n";
            delete target;
            current = nullptr;
            return;
        }
        CoachNode* prevNode = target->prev;
        CoachNode* nextNode = target->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        if (target == current) {
            current = nextNode; //Active coach advances to next valid coach
        }
        cout << "\nRemoved Coach (" << num << "), Active selection moved to Coach (" << current->coachNumber << ")\n";
        delete target;
    }
    //4. Move Forward in list
    void moveForward() {
        if (current) {
            current = current->next;
            cout << "\nMoved forward to Coach (" << current->coachNumber << ")\n";
        } else {
            cout << "\nTrain is empty\n";
        }
    }
    //5. Move Backward in List
    void moveBackward() {
        if (current) {
            current = current->prev;
            cout << "\nMoved backward to Coach (" << current->coachNumber << ")\n";
        } else {
            cout << "\nTrain is empty.\n";
        }
    }
    //6. Display Train Clockwise (Forward)
    void displayTrainClockwise() const {
        if (!current) {
            cout << "\nTrain is empty\n";
            return;
        }

        cout << "\n--- Displaying Train Clockwise ---\n";
        CoachNode* temp = current;
        do {
            cout << "Coach #" << temp->coachNumber 
                 << "Type: " << temp->coachType 
                 << "Capacity: " << temp->passengerCapacity 
                 << "Passengers: " << temp->currentPassengers;
            if (temp == current) cout << "  <-- (ACTIVE)";
            cout << "\n";
            temp = temp->next;
        } while (temp != current);
        cout << "----------------------------------\n";
    }
    //7. Display Train Anti-clockwise (Backward)
    void displayTrainAntiClockwise() const {
        if (!current) {
            cout << "\nTrain is empty.\n";
            return;
        }
        cout << "\n--- Displaying Train Anti-Clockwise ---\n";
        CoachNode* temp = current;
        do {
            cout << "Coach #" << temp->coachNumber 
                 << "Type: " << temp->coachType 
                 << "Capacity: " << temp->passengerCapacity 
                 << "Passengers: " << temp->currentPassengers;
            if (temp == current) cout << "  <-- (ACTIVE)";
            cout << "\n";
            temp = temp->prev;
        } while (temp != current);
        cout << "---------------------------------------\n";
    }
    //8. Search Coach by Number
    void searchCoach(int num) const {
        if (!current) {
            cout << "\nTrain is empty.\n";
            return;
        }
        CoachNode* temp = current;
        do {
            if (temp->coachNumber == num) {
                cout << "\n-----------------------------------\n";
                cout << "\tCOACH FOUND\n";
                cout << "Coach Number : " << temp->coachNumber << "\n";
                cout << "Coach Type   : " << temp->coachType << "\n";
                cout << "Capacity     : " << temp->passengerCapacity << "\n";
                cout << "Passengers   : " << temp->currentPassengers << "\n";
                cout << "Empty Seats  : " << (temp->passengerCapacity - temp->currentPassengers) << "\n";
                return;
            }
            temp = temp->next;
        } while (temp != current);

        cout << "\nCoach " << num << " not found.\n";
    }
    //9. Find Maximum Available Capacity
    void findMaxAvailableCapacity() const {
        if (!current) {
            cout << "\nTrain is empty.\n";
            return;
        }
        CoachNode* temp = current;
        CoachNode* maxCoach = current;
        int maxEmptySeats = current->passengerCapacity - current->currentPassengers;

        do {
            int emptySeats = temp->passengerCapacity - temp->currentPassengers;
            if (emptySeats > maxEmptySeats) {
                maxEmptySeats = emptySeats;
                maxCoach = temp;
            }
            temp = temp->next;
        } while (temp != current);

        cout << "\n-------------------------------------------------\n";
        cout << "\tCOACH WITH MAXIMUM AVAILABLE CAPACITY\n";
        cout << "Coach Number : " << maxCoach->coachNumber << "\n";
        cout << "Coach Type   : " << maxCoach->coachType << "\n";
        cout << "Empty Seats  : " << maxEmptySeats << " (" << maxCoach->currentPassengers << "/" << maxCoach->passengerCapacity << " occupied)\n";
    }

    //10. Display Current Coach
    void displayCurrentCoach() const {
        if (!current) {
            cout << "\nNo coach selected.\n";
            return;
        }
        cout << "\n-----------------------------------\n";
        cout << "      CURRENT SELECTED COACH       \n";
        cout << "Coach Number : " << current->coachNumber << "\n";
        cout << "Coach Type   : " << current->coachType << "\n";
        cout << "Capacity     : " << current->passengerCapacity << "\n";
        cout << "Passengers   : " << current->currentPassengers << "\n";
    }
    //11. Reverse Train Direction (In-place pointer manipulation)
    void reverseTrainDirection() {
        if (!current || current->next == current) {
            cout << "\nDirection reversed\n";
            return;
        }
        CoachNode* currNode = current;
        CoachNode* tempPrev = nullptr;

        do {
            //Swap next and prev pointers for each coach node
            tempPrev = currNode->prev;
            currNode->prev = currNode->next;
            currNode->next = tempPrev;

            //Advance to the original next node (which is in currNode->prev after swapping)
            currNode = currNode->prev;
        } while (currNode != current);

        cout << "\nTrain direction reversed in-place \n";
    }
};
int main() {
    TrainSystem train;

    int choice;
    do {
        cout << "\n-----------------------------------------\n";
        cout << "\tTRAIN COACH NAVIGATION MENU\n";
        cout << "1. Add Coach (At End)\n";
        cout << "2. Insert Coach (After specified Coach)\n";
        cout << "3. Remove Coach by Number\n";
        cout << "4. Move Forward\n";
        cout << "5. Move Backward\n";
        cout << "6. Display Train Clockwise\n";
        cout << "7. Display Train Anti-clockwise\n";
        cout << "8. Search Coach\n";
        cout << "9. Find Max Available Capacity Coach\n";
        cout << "10. Display Current Coach\n";
        cout << "11. Reverse Train Direction\n";
        cout << "12. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int num, cap, curr;
                string type;
                cout << "Enter Coach Number: ";
                cin >> num;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Coach Type: ";
                getline(cin, type);
                cout << "Enter Passenger Capacity: ";
                cin >> cap;
                cout << "Enter Current Passengers: ";
                cin >> curr;
                train.addCoach(num, type, cap, curr);
                break;
            }
            case 2: {
                int afterNum, num, cap, curr;
                string type;
                cout << "Enter Coach Number to insert after: ";
                cin >> afterNum;
                cout << "Enter New Coach Number: ";
                cin >> num;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Coach Type: ";
                getline(cin, type);
                cout << "Enter Passenger Capacity: ";
                cin >> cap;
                cout << "Enter Current Passengers: ";
                cin >> curr;
                train.insertCoach(afterNum, num, type, cap, curr);
                break;
            }
            case 3: {
                int num;
                cout << "Enter Coach Number to remove: ";
                cin >> num;
                train.removeCoach(num);
                break;
            }
            case 4:
                train.moveForward();
                break;
            case 5:
                train.moveBackward();
                break;
            case 6:
                train.displayTrainClockwise();
                break;
            case 7:
                train.displayTrainAntiClockwise();
                break;
            case 8: {
                int num;
                cout << "Enter Coach Number to search: ";
                cin >> num;
                train.searchCoach(num);
                break;
            }
            case 9:
                train.findMaxAvailableCapacity();
                break;
            case 10:
                train.displayCurrentCoach();
                break;
            case 11:
                train.reverseTrainDirection();
                break;
            case 12:
                cout << "\nExited Train Management System...\n";
                break;
            default:
                cout << "\noption not present.\n";
        }
    } while (choice != 12);

    return 0;
}