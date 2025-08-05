#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUSES 5
#define ROWS 5
#define COLS 4

typedef struct {
    char name[50];
    char busNumber[10];
    int seats[ROWS][COLS]; // 0 = available, 1 = booked
} Driver;

Driver buses[MAX_BUSES];
int busCount = 0;

void addBus() {
    if (busCount >= MAX_BUSES) {
        printf("Bus limit reached!\n");
        return;
    }
    printf("Enter driver name: ");
    scanf(" %s", buses[busCount].name);

    printf("Enter bus number: ");
    scanf(" %s", buses[busCount].busNumber);

    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            buses[busCount].seats[i][j] = 0;
        }
    }

    printf("Bus added successfully!\n");
    busCount++;
}

void listBuses() {
    if (busCount == 0) {
        printf("No buses available.\n");
        return;
    }
    printf("\nAvailable Buses:\n");
    for (int i = 0; i < busCount; i++) {
        printf("Bus %d: %s (Driver: %s)\n", i + 1, buses[i].busNumber, buses[i].name);
    }
}

void viewSeats(int busIndex) {
    printf("Seat layout (0=Available, 1=Booked):\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", buses[busIndex].seats[i][j]);
        }
        printf("\n");
    }
}
void bookSeat(int busIndex) {
    int row, col;
    viewSeats(busIndex);

    printf("Enter seat to book (row and column): ");
    scanf("%d %d", &row, &col);

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        if (buses[busIndex].seats[row][col] == 0) {
            buses[busIndex].seats[row][col] = 1;
            printf("Seat booked successfully!\n");
        } else {
            printf("Seat already booked!\n");
        }
    } else {
        printf("Invalid seat coordinates.\n");
    }
}

void cancelBooking(int busIndex) {
    int row, col;
    viewSeats(busIndex);

    printf("Enter seat to cancel (row and column): ");
    scanf("%d %d", &row, &col);

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        if (buses[busIndex].seats[row][col] == 1) {
            buses[busIndex].seats[row][col] = 0;
            printf("Booking canceled.\n");
        } else {
            printf("Seat was not booked.\n");
        }
    } else {
        printf("Invalid seat coordinates.\n");
    }
}

int findBusIndex(char *busNumber) {
    for (int i = 0; i < busCount; i++) {
        if (strcmp(buses[i].busNumber, busNumber) == 0) {
            return i;
        }
    }
    return -1;
}
void deleteBus() {
    char busNumber[10];
    printf("Enter bus number to delete: ");
    scanf(" %s", busNumber);

    int index = findBusIndex(busNumber);
    if (index == -1) {
        printf("Bus not found.\n");
        return;
    }

    for (int i = index; i < busCount - 1; i++) {
        buses[i] = buses[i + 1];
    }

    busCount--;
    printf("Bus deleted successfully.\n");
}
int main() {
    int choice;
    char searchBus[10];


    do {
        printf("\n--- Bus Booking System Menu ---\n");
        printf("1. Add Bus\n");
        printf("2. List all Bus\n");
        printf("3. Book Seat\n");
        printf("4. View Seats\n");
        printf("5. Cancel Booking\n");
        printf("6. Delete Bus\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBus();
                break;
            case 2:
                listBuses();
                break;
            case 3:
                printf("Enter bus number to book: ");
                scanf(" %s", searchBus);
                {
                    int idx = findBusIndex(searchBus);
                    if (idx != -1) {
                        bookSeat(idx);
                    }
                    else {
                        printf("Bus not found.\n");
                    }
                }
                break;
            case 4:
                printf("Enter bus number to view: ");
                scanf(" %s", searchBus);
                {
                    int idx = findBusIndex(searchBus);
                    if (idx != -1) {
                        viewSeats(idx);
                    } else {
                        printf("Bus not found.\n");
                    }
                }
                break;
            case 5:
                printf("Enter bus number to cancel booking: ");
                scanf(" %s", searchBus);
                {
                    int idx = findBusIndex(searchBus);
                    if (idx != -1) {
                        cancelBooking(idx);
                    }
                    else {
                        printf("Bus not found.\n");
                    }
                }
                break;
            case 6:
                deleteBus();
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}
