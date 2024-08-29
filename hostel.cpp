#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Client {
public:
    int regNo;
    string name;
    string cnic;   // New CNIC field
    int roomNumber;

    Client(int rNo, string n, string c, int rNum) : regNo(rNo), name(n), cnic(c), roomNumber(rNum) {}
};

class Hotel {
public:
    vector<Client> clients;  // Vector to store Client objects
    int roomPrices[35];
    bool rooms[35];  // To track occupied rooms

    Hotel() {
        // Initialize room prices and availability
        for (int i = 0; i < 10; i++) {
            roomPrices[i] = 25000;  // First 10 rooms
            rooms[i] = false;
        }
        for (int i = 10; i < 20; i++) {
            roomPrices[i] = 15000;  // Second 10 rooms
            rooms[i] = false;
        }
        for (int i = 20; i < 35; i++) {
            roomPrices[i] = 10000;  // Last 15 rooms
            rooms[i] = false;
        }
    }

    void showAvailableRooms() {
        cout << "Available Rooms: ";
        bool found = false;
        for (int i = 0; i < 35; i++) {
            if (!rooms[i]) {
                cout << (i + 1) << " ";
                found = true;
            }
        }
        if (!found) {
            cout << "None (All rooms are occupied)";
        }
        cout << endl;
    }

    void addClient(int regNo, string name, string cnic) {
        showAvailableRooms();  // Show available rooms before asking for room number

        int roomNumber;
        cout << "Enter Room Number (1-35): ";
        cin >> roomNumber;

        if (roomNumber < 1 || roomNumber > 35 || rooms[roomNumber - 1]) {
            cout << "Invalid room number or room already occupied." << endl;
            return;
        }

        clients.push_back(Client(regNo, name, cnic, roomNumber));
        rooms[roomNumber - 1] = true;
        cout << "Client added successfully." << endl;
    }

    void deleteClient(int regNo) {
        for (size_t i = 0; i < clients.size(); i++) {
            if (clients[i].regNo == regNo) {
                rooms[clients[i].roomNumber - 1] = false;  // Free the room
                clients.erase(clients.begin() + i);
                cout << "Client deleted successfully." << endl;
                return;
            }
        }
        cout << "Client not found." << endl;
    }

    void searchClient(int regNo) {
        for (size_t i = 0; i < clients.size(); i++) {
            if (clients[i].regNo == regNo) {
                cout << "Client found: " << clients[i].name << ", CNIC: " << clients[i].cnic << ", Room Number: " << clients[i].roomNumber << endl;
                return;
            }
        }
        cout << "Client not found." << endl;
    }

    void searchClient(string name) {
        for (size_t i = 0; i < clients.size(); i++) {
            if (clients[i].name == name) {
                cout << "Client found: Reg No: " << clients[i].regNo << ", CNIC: " << clients[i].cnic << ", Room Number: " << clients[i].roomNumber << endl;
                return;
            }
        }
        cout << "Client not found." << endl;
    }

    void showAllClients() {
        if (clients.empty()) {
            cout << "No clients currently in the hotel." << endl;
            return;
        }
        for (size_t i = 0; i < clients.size(); i++) {
            cout << "Reg No: " << clients[i].regNo << ", Name: " << clients[i].name << ", CNIC: " << clients[i].cnic << ", Room Number: " << clients[i].roomNumber << endl;
        }
    }

    void showRoomFeatures(int roomNumber) {
        if (roomNumber < 1 || roomNumber > 35) {
            cout << "Invalid room number." << endl;
            return;
        }
        cout << "Room Number: " << roomNumber << ", Price: " << roomPrices[roomNumber - 1] << endl;
        cout << "Room Features: " << (roomNumber <= 10 ? "Luxury Suite" : roomNumber <= 20 ? "Deluxe Room" : "Standard Room") << endl;
    }
};

int main() {
    Hotel hotel;
    int choice;
    while (true) {
        cout << "1. Add Client\n2. Delete Client\n3. Search Client by Reg No\n4. Search Client by Name\n5. Show All Clients\n6. Show Room Features\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        if (choice == 1) {
            int regNo;
            string name, cnic;
            cout << "Enter Reg No: ";
            cin >> regNo;
            cout << "Enter Name: ";
            cin.ignore();  // To handle the newline character left in the buffer
            getline(cin, name);
            cout << "Enter CNIC: ";
            getline(cin, cnic);
            hotel.addClient(regNo, name, cnic);
        } else if (choice == 2) {
            int regNo;
            cout << "Enter Reg No: ";
            cin >> regNo;
            hotel.deleteClient(regNo);
        } else if (choice == 3) {
            int regNo;
            cout << "Enter Reg No: ";
            cin >> regNo;
            hotel.searchClient(regNo);
        } else if (choice == 4) {
            string name;
            cout << "Enter Name: ";
            cin.ignore();  // To handle the newline character left in the buffer
            getline(cin, name);
            hotel.searchClient(name);
        } else if (choice == 5) {
            hotel.showAllClients();
        } else if (choice == 6) {
            int roomNumber;
            cout << "Enter Room Number (1-35): ";
            cin >> roomNumber;
            hotel.showRoomFeatures(roomNumber);
        } else if (choice == 7) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

