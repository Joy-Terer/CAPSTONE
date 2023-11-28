#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SEATS 10
#define MAX_EMPLOYEES 2


struct Employee{
	char username[50];
    char password[50];
}

struct Employee employees[2] = {
    {"employee1", "password1"},
    {"employee2", "password2"},
};

struct user {
    char name[50];
    char password[20];
    char Email[50];
    int seatNumber;
};

struct user reservations[MAX_SEATS];
int numReservations = 0;

void saveDataToFile() {
    FILE* file = fopen("reservations.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing\n");
        return;
    }

    for (int i = 0; i < MAX_SEATS; ++i) {
        fprintf(file, "%s %s %s %d\n", reservations[i].name, reservations[i].Email, reservations[i].password, reservations[i].seatNumber);
    }

    fclose(file);
}

void loadDataFromFile() {
    FILE* file = fopen("reservations.txt", "r");
    if (file == NULL) {
        printf("No existing reservations data found\n");
        return;
    }

    while (fscanf(file, "%s %s %s %d", reservations[numReservations].name, reservations[numReservations].Email, reservations[numReservations].password, &reservations[numReservations].seatNumber) == 4) {
        ++numReservations;
    }

    fclose(file);
}


int employee(const char *username, const char *password) {
    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        if (strcmp(username, Employee[i].username) == 0 && strcmp(password, Employee[i].password) == 0)
		 { 
		 	printf("Employee login successful");
            return 0; 
        }
    }
    return 1; 
}

void login() {
    printf("============BUS RESERVATION AND BOOKING SYSTEM==============\n");
    printf("\t\t\t EMPLOYEE LOGIN CREDENTIALS\n\n");

    char name[50];
    char password[50];

    printf("Enter your Name: ");
    scanf("%s", name);

    printf("Enter your password: ");
    scanf("%s", password);

    int userType = employee(name, password);

    if (userType == 0) {
        loadDataFromFile();
        printf("Employee login successful\n");
    } else if (userType == 1) {
        printf("User login successful\n");
    } else {
        printf("Invalid login credentials\n");
        exit(0);
    }

    printf("Continue with booking (1 = yes, 0 = No): ");
    int opt;
    scanf("%d", &opt);

    switch (opt) {
        case 1:
            break;
        case 0:
            printf("Thank you for choosing our system\n");
            exit(0);
        default:
            printf("Invalid choice.\n");
            exit(0);  
    }
}

void displayMenu() {
    printf("\n-----Bus Reservation System -----\n");
    printf("1. View Available Seats\n");
    printf("2. Make a Reservation\n");
    printf("3. Cancel a Reservation\n");
    printf("4. View Reservations\n");
    printf("5. Make payment\n");
    printf("6. Generate ticket\n");
    printf("7. Exit\n");
}

void viewAvailableSeats() {
    printf("\nAvailable Seats:\n");
    for (int i = 0; i < MAX_SEATS; i++) {
        if (reservations[i].seatNumber == 0) {
            printf("Seat %d is available\n", i + 1);
        }
    }
}

void makeReservation() {
    int seatNumber;
    char name[50];
    char password[20];
    char Email[50];

    printf("Enter your name: ");
    scanf("%s", name);

    printf("Enter your password:");
    scanf("%s", password);

    printf("Enter your email:");
    scanf("%s", Email);

    viewAvailableSeats();
    printf("Enter the seat number you want to reserve: ");
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > MAX_SEATS) {
        printf("Invalid seat number. Please try again.\n");
        return;
    }

    if (reservations[seatNumber - 1].seatNumber != 0) {
        printf("Sorry, seat %d is already reserved. Please choose another seat.\n", seatNumber);
        return;
    }

    struct user newReservation;
    strcpy(newReservation.name, name);
    strcpy(newReservation.password, password);
    strcpy(newReservation.Email, Email);
    newReservation.seatNumber = seatNumber;

    reservations[seatNumber - 1] = newReservation;
    numReservations++;

    printf("Reservation successful!\n");
}

void cancelReservation() {
    int seatNumber;

    viewAvailableSeats();
    printf("Enter the seat number you want to cancel: ");
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > MAX_SEATS) {
        printf("Invalid seat number. Please try again.\n");
        return;
    }

    if (reservations[seatNumber - 1].seatNumber == 0) {
        printf("Seat %d is not reserved.\n", seatNumber);
        return;
    }

    reservations[seatNumber - 1].seatNumber = 0;
    numReservations--;

    printf("Reservation for seat %d canceled successfully.\n", seatNumber);
}

void viewReservations() {
    printf("\nCurrent Reservations:\n");
    for (int i = 0; i < MAX_SEATS; i++) {
        if (reservations[i].seatNumber != 0) {
            printf("Seat %d: %s\n", i + 1, reservations[i].name);
        }
    }
}


void makepayment() {
    int seatNumber;

    printf("Enter the seat number for payment: ");
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > MAX_SEATS) {
        printf("Invalid seat number. Please try again.\n");
        return;
    }

    if (reservations[seatNumber - 1].seatNumber == 0) {
        printf("Seat %d is not reserved.\n", seatNumber);
        return;
    }

    printf("Select payment mode:\n");
    printf("1. Credit card\n");
    printf("2. M-pesa\n");
    printf("3. Cash\n");

    int paymentmode;
    printf("Enter your choice: ");
    scanf("%d", &paymentmode);

    switch (paymentmode) {
        case 1:
            printf("Processing credit card payment for seat %d...\n", seatNumber);
            break;
        case 2:
            printf("Processing M-pesa payment for seat %d...\n", seatNumber);
            break;
        case 3:
            printf("Please pay cash at the counter for seat %d\n", seatNumber);
            break;
        default:
            printf("Invalid payment mode!\n");
            return;
    }
}

void generateTicket() {
    int seatNumber;

    printf("Enter the seat number to generate a ticket: ");
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > MAX_SEATS) {
        printf("Invalid seat number. Please try again.\n");
        return;
    }

    if (reservations[seatNumber - 1].seatNumber == 0) {
        printf("Seat %d is not reserved.\n", seatNumber);
        return;
    }

    printf("\n------ TICKET ------\n");
    printf("Name: %s\n", reservations[seatNumber - 1].name);
    printf("Email: %s\n", reservations[seatNumber - 1].Email);
    printf("Seat Number: %d\n", reservations[seatNumber - 1].seatNumber);
    printf("------ Enjoy your journey! ------\n");
}

int main() {
    int choice;

    do {
        login();
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewAvailableSeats();
                break;
            case 2:
                makeReservation();
                break;
            case 3:
                cancelReservation();
                break;
            case 4:
                viewReservations();
                break;
            case 5:
                makepayment();
                break;
            case 6:
                generateTicket();
                break;
            case 7:
                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
