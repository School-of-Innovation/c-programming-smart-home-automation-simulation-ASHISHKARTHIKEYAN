#include <stdio.h>

#define MAX_ROOMS 5 // Maximum number of rooms allowed
#define AUTO_LOCK_THRESHOLD 5 // Auto-lock after 5 consecutive inputs without motion

// Function prototypes
void initializeSystem(int rooms, int lights[], int temps[], int motion[], int locks[]);
void displayMenu();
void controlLights(int rooms, int lights[], int *lightCounter);
void readTemperature(int rooms, int temps[]);
void detectMotion(int rooms, int motion[], int *motionCounter, int locks[]);
void securitySystem(int rooms, int locks[]);
void analyzeHouseStatus(int rooms, int lights[], int temps[], int motion[], int locks[]);
void checkEnergySaving(int rooms, int lights[]);

int main() {
    int rooms;
    printf("Enter number of rooms (1-%d): ", MAX_ROOMS);
    scanf("%d", &rooms);
    if (rooms < 1 || rooms > MAX_ROOMS) {
        printf("Invalid number of rooms. Exiting...\n");
        return 1;
    }

    int lights[rooms], temps[rooms], motion[rooms], locks[rooms];
    int motionCounter = 0, lightCounter = 0;
    initializeSystem(rooms, lights, temps, motion, locks);

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: controlLights(rooms, lights, &lightCounter); break;
            case 2: readTemperature(rooms, temps); break;
            case 3: detectMotion(rooms, motion, &motionCounter, locks); break;
            case 4: securitySystem(rooms, locks); break;
            case 5: analyzeHouseStatus(rooms, lights, temps, motion, locks); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice, please try again.\n");
        }
        
        checkEnergySaving(rooms, lights);
    } while (choice != 6);
    
    return 0;
}

void initializeSystem(int rooms, int lights[], int temps[], int motion[], int locks[]) {
    for (int i = 0; i < rooms; i++) {
        lights[i] = 0;      // All lights OFF
        temps[i] = 22;      // Default temperature (22°C)
        motion[i] = 0;      // No motion detected
        locks[i] = 1;       // Doors locked
    }
    printf("System initialized. All lights OFF, doors locked, no motion detected.\n");
}

void displayMenu() {
    printf("\n===== Smart Home Menu =====\n");
    printf("1. Toggle Light\n");
    printf("2. Read Temperature\n");
    printf("3. Check Motion Sensor\n");
    printf("4. Lock/Unlock Security System\n");
    printf("5. House Status Summary\n");
    printf("6. Exit\n");
}

void controlLights(int rooms, int lights[], int *lightCounter) {
    int room;
    printf("Enter room number to toggle light (1-%d): ", rooms);
    scanf("%d", &room);
    if (room < 1 || room > rooms) {
        printf("Invalid room number.\n");
        return;
    }
    lights[room - 1] = !lights[room - 1];
    printf("Light in Room %d is now %s.\n", room, lights[room - 1] ? "ON" : "OFF");
    (*lightCounter)++;
}

void readTemperature(int rooms, int temps[]) {
    int room;
    printf("Enter room number to read temperature (1-%d): ", rooms);
    scanf("%d", &room);
    if (room < 1 || room > rooms) {
        printf("Invalid room number.\n");
        return;
    }
    printf("Temperature in Room %d: %d°C\n", room, temps[room - 1]);
    if (temps[room - 1] > 30) {
        printf("Warning: High temperature detected in Room %d!\n", room);
    }
}

void detectMotion(int rooms, int motion[], int *motionCounter, int locks[]) {
    int detected = 0;
    for (int i = 0; i < rooms; i++) {
        if (motion[i]) {
            printf("Motion detected in Room %d!\n", i + 1);
            detected = 1;
        }
    }
    if (!detected) {
        printf("No motion detected in any room.\n");
        (*motionCounter)++;
    } else {
        *motionCounter = 0;
    }
    
    if (*motionCounter >= AUTO_LOCK_THRESHOLD) {
        for (int i = 0; i < rooms; i++) {
            locks[i] = 1;
        }
        printf("Auto-Lock activated: All doors are now locked due to inactivity.\n");
        *motionCounter = 0;
    }
}

void securitySystem(int rooms, int locks[]) {
    int room;
    printf("Enter room number to lock/unlock (1-%d): ", rooms);
    scanf("%d", &room);
    if (room < 1 || room > rooms) {
        printf("Invalid room number.\n");
        return;
    }
    locks[room - 1] = !locks[room - 1];
    printf("Room %d is now %s.\n", room, locks[room - 1] ? "Locked" : "Unlocked");
}

void analyzeHouseStatus(int rooms, int lights[], int temps[], int motion[], int locks[]) {
    printf("\nHouse Status:\n");
    for (int i = 0; i < rooms; i++) {
        printf("Room %d: Light %s, Temp %d°C, %s, %s\n", i + 1, 
               lights[i] ? "ON" : "OFF", temps[i],
               motion[i] ? "Motion Detected" : "No Motion", 
               locks[i] ? "Locked" : "Unlocked");
    }
}

void checkEnergySaving(int rooms, int lights[]) {
    int allLightsOn = 1;
    for (int i = 0; i < rooms; i++) {
        if (!lights[i]) {
            allLightsOn = 0;
            break;
        }
    }
    if (allLightsOn) {
        printf("Energy Saving Mode: All lights have been ON for a while. Consider turning them OFF.\n");
    }
    
    // Auto-Lock Feature
    static int motionCounter = 0;
    if (++motionCounter >= AUTO_LOCK_THRESHOLD) {
        printf("Auto-Lock activated: All doors are now locked due to inactivity.\n");
        motionCounter = 0;
    }
    
    // Temperature Alert Feature
    for (int i = 0; i < rooms; i++) {
        if (temps[i] > 30) {
            printf("Warning: High temperature detected in Room %d!\n", i + 1);
        }
    }
}
