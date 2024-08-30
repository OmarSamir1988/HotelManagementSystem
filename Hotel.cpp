#include <iostream>
#include <string>

#define MAX_ROOMS 100

using namespace std;

// Class for Client Information
class Client
{
public:
    string firstName;
    string city;
    string contactNumber;
    string checkInDate;
    string checkOutDate;
    float advancePayment;
    int bookingId;
};

// Room Class Definition
class Room
{
public:
    char roomType;
    char bedType;
    char airConditioned;
    int roomId;
    int roomRate;
    int occupancyStatus;

    Client clientInfo;
    Room createRoom(int);
    void findRoom(int);
    void removeRoom(int);
    void showRoomDetails(Room);
};

// Global Declarations
Room roomList[MAX_ROOMS];
int roomCount = 0;

// Function to Create and Add a Room
Room Room::createRoom(int roomNum)
{
    Room newRoom;
    newRoom.roomId = roomNum;
    cout << "\nEnter AC Type (A for AC / N for Non-AC): ";
    cin >> newRoom.airConditioned;
    cout << "\nEnter Comfort Level (S for Standard / N for Normal): ";
    cin >> newRoom.roomType;
    cout << "\nEnter Bed Size (B for Big / S for Small): ";
    cin >> newRoom.bedType;
    cout << "\nEnter Daily Rent: ";
    cin >> newRoom.roomRate;
    newRoom.occupancyStatus = 0;

    cout << "\nRoom successfully created!";
    return newRoom;
}

// Function to Search for a Room
void Room::findRoom(int roomNum)
{
    int i;
    bool isFound = false;
    for (i = 0; i < roomCount; i++)
    {
        if (roomList[i].roomId == roomNum)
        {
            isFound = true;
            break;
        }
    }
    if (isFound)
    {
        cout << "\nRoom Details:\n";
        if (roomList[i].occupancyStatus == 1)
        {
            cout << "\nThe room is currently occupied.";
        }
        else
        {
            cout << "\nThe room is available.";
        }
        showRoomDetails(roomList[i]);
    }
    else
    {
        cout << "\nRoom not found!";
    }
}

// Function to Display Room Details
void Room::showRoomDetails(Room roomObj)
{
    cout << "\nRoom ID: \t" << roomObj.roomId;
    cout << "\nAC Type (A for AC / N for Non-AC): " << roomObj.airConditioned;
    cout << "\nComfort Level (S for Standard / N for Normal): " << roomObj.roomType;
    cout << "\nBed Size (B for Big / S for Small): " << roomObj.bedType;
    cout << "\nDaily Rent: " << roomObj.roomRate;
}

// Hotel Management Class Definition
class HotelManagement : protected Room
{
public:
    void processCheckIn();
    void displayAvailableRooms();
    void findClientByName(string);
    void processCheckOut(int);
    void showGuestSummary();
};

// Function to Show Guest Summary
void HotelManagement::showGuestSummary()
{
    if (roomCount == 0)
    {
        cout << "\nNo guests are currently staying in the hotel.";
    }
    else
    {
        for (int i = 0; i < roomCount; i++)
        {
            if (roomList[i].occupancyStatus == 1)
            {
                cout << "\nGuest Name: " << roomList[i].clientInfo.firstName;
                cout << "\nRoom ID: " << roomList[i].roomId;
                cout << "\nCity: " << roomList[i].clientInfo.city;
                cout << "\nContact Number: " << roomList[i].clientInfo.contactNumber;
                cout << "\n---------------------------------------";
            }
        }
    }
}

// Function for Room Check-In Process
void HotelManagement::processCheckIn()
{
    int roomNum;
    bool isFound = false;

    cout << "\nEnter Room ID for Check-In: ";
    cin >> roomNum;
    for (int i = 0; i < roomCount; i++)
    {
        if (roomList[i].roomId == roomNum)
        {
            isFound = true;
            if (roomList[i].occupancyStatus == 1)
            {
                cout << "\nThe room is already booked.";
                return;
            }

            cout << "\nEnter Booking ID: ";
            cin >> roomList[i].clientInfo.bookingId;

            cout << "\nEnter Client's First Name: ";
            cin >> roomList[i].clientInfo.firstName;

            cout << "\nEnter City: ";
            cin >> roomList[i].clientInfo.city;

            cout << "\nEnter Contact Number: ";
            cin >> roomList[i].clientInfo.contactNumber;

            cout << "\nEnter Check-In Date (dd/mm/yyyy): ";
            cin >> roomList[i].clientInfo.checkInDate;

            cout << "\nEnter Check-Out Date (dd/mm/yyyy): ";
            cin >> roomList[i].clientInfo.checkOutDate;

            cout << "\nEnter Advance Payment: ";
            cin >> roomList[i].clientInfo.advancePayment;

            roomList[i].occupancyStatus = 1;

            cout << "\nClient checked in successfully.";
            break;
        }
    }
    if (!isFound)
    {
        cout << "\nRoom ID not found!";
    }
}

// Function to Display Available Rooms
void HotelManagement::displayAvailableRooms()
{
    bool available = false;
    for (int i = 0; i < roomCount; i++)
    {
        if (roomList[i].occupancyStatus == 0)
        {
            showRoomDetails(roomList[i]);
            cout << "\n\nPress enter to see the next available room";
            available = true;
        }
    }
    if (!available)
    {
        cout << "\nAll rooms are occupied.";
    }
}

// Function to Find Client by Name
void HotelManagement::findClientByName(string clientName)
{
    bool isFound = false;
    for (int i = 0; i < roomCount; i++)
    {
        if (roomList[i].occupancyStatus == 1 && roomList[i].clientInfo.firstName == clientName)
        {
            cout << "\nClient Name: " << roomList[i].clientInfo.firstName;
            cout << "\nRoom ID: " << roomList[i].roomId;
            cout << "\n\nPress enter to see the next record\n";
            isFound = true;
        }
    }
    if (!isFound)
    {
        cout << "\nNo client found with the given name.\n";
    }
}

// Function to Process Check-Out and Generate Bill
void HotelManagement::processCheckOut(int roomNum)
{
    bool isFound = false;
    int stayDuration;
    float totalAmountDue = 0;

    for (int i = 0; i < roomCount; i++)
    {
        if (roomList[i].occupancyStatus == 1 && roomList[i].roomId == roomNum)
        {
            isFound = true;

            cout << "\nEnter the number of days the client stayed: ";
            cin >> stayDuration;
            totalAmountDue = stayDuration * roomList[i].roomRate;

            cout << "\n\t######## Check-Out Details ########\n";
            cout << "\nClient Name : " << roomList[i].clientInfo.firstName;
            cout << "\nRoom ID : " << roomList[i].roomId;
            cout << "\nCity : " << roomList[i].clientInfo.city;
            cout << "\nContact Number : " << roomList[i].clientInfo.contactNumber;
            cout << "\nTotal Amount Due : " << totalAmountDue << " /";
            cout << "\nAdvance Payment: " << roomList[i].clientInfo.advancePayment << " /";
            cout << "\n*** Total Payable: " << totalAmountDue - roomList[i].clientInfo.advancePayment << " / only";

            roomList[i].occupancyStatus = 0;
            break;
        }
    }
    if (!isFound)
    {
        cout << "\nRoom ID not found or the room is not occupied!";
    }
}

// Function to Manage Rooms (Adding and Searching)
void manageRoomInventory()
{
    Room roomObj;
    int choice, roomId;
    bool roomExists = false;

    do
    {
        cout << "\n### Room Management ###";
        cout << "\n1. Add a Room";
        cout << "\n2. Search for a Room";
        cout << "\n3. Back to Main Menu";
        cout << "\n\nChoose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nEnter Room ID to add: ";
            cin >> roomId;
            for (int i = 0; i < roomCount; i++)
            {
                if (roomList[i].roomId == roomId)
                {
                    roomExists = true;
                }
            }
            if (roomExists)
            {
                cout << "\nRoom ID already exists. Please enter a unique ID.";
                roomExists = false;
            }
            else
            {
                roomList[roomCount] = roomObj.createRoom(roomId);
                roomCount++;
            }
            break;
        case 2:
            cout << "\nEnter Room ID to search: ";
            cin >> roomId;
            roomObj.findRoom(roomId);
            break;
        case 3:
            // Return to Main Menu
            break;
        default:
            cout << "\nInvalid option, please try again.";
            break;
        }
    } while (choice != 3);
}

int main()
{
    HotelManagement hotel;
    int choice, roomId;
    string clientName;

    do
    {
        cout << "######## Hotel Management System #########\n";
        cout << "\n1. Manage Rooms";
        cout << "\n2. Check-In Room";
        cout << "\n3. Display Available Rooms";
        cout << "\n4. Search Client by Name";
        cout << "\n5. Check-Out Room";
        cout << "\n6. Guest Summary Report";
        cout << "\n7. Exit";
        cout << "\n\nChoose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            manageRoomInventory();
            break;
        case 2:
            if (roomCount == 0)
            {
                cout << "\nNo room data available.\nPlease add rooms first.";
            }
            else
            {
                hotel.processCheckIn();
            }
            break;
        case 3:
            if (roomCount == 0)
            {
                cout << "\nNo room data available.\nPlease add rooms first.";
            }
            else
            {
                hotel.displayAvailableRooms();
            }
            break;
        case 4:
            if (roomCount == 0)
            {
                cout << "\nNo rooms available.\nPlease add rooms first.";
            }
            else
            {
                cout << "Enter Client's First Name: ";
                cin >> clientName;
                hotel.findClientByName(clientName);
            }
            break;
        case 5:
            if (roomCount == 0)
            {
                cout << "\nNo rooms available.\nPlease add rooms first.";
            }
            else
            {
                cout << "Enter Room ID: ";
                cin >> roomId;
                hotel.processCheckOut(roomId);
            }
            break;
        case 6:
            hotel.showGuestSummary();
            break;
        case 7:
            cout << "\nThank you for using our Hotel Management System!";
            break;
        default:
            cout << "\nInvalid option, please try again.";
            break;
        }
    } while (choice != 7);

    return 0;
}
