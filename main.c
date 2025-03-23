#include <stdio.h>
#include <stdlib.h>//I used rand function to assign values for the temperatures, Beacause nothing is mentioned in the instruction about, how the values are assigned for temp
#define MAX_ROOMS 5  //  max number of rooms

// Function prototypes
void initializeSystem();
void displayMenu();
void controlLights();
void readTemperature();
void detectMotion();
void securitySystem();
void analyzeHouseStatus();

int main() {
    
    int allon=1;//for checking all lights are ON
    int cycle[1]={0};// For counting iterations
    int rooms;
    printf("Enter number of rooms:");
    scanf("%d",&rooms);
    if(rooms<=0 || rooms>MAX_ROOMS){
        printf("Enter valid no of rooms");
        return 1;
    }
    int light[rooms],door[rooms],motion[rooms],temp[rooms];
    initializeSystem(light,door,motion,temp,rooms);

    int choice=0;
    do
    {
            displayMenu();
            printf("Enter your choice :");
            scanf("%d",&choice);
            if(choice<=0 || choice >6){
                printf("Enter valid choice\n");
                return 1;
            }
            switch (choice){
                case 1:
                controlLights(rooms,light,cycle,allon);
                break;
                case 2:
                readTemperature(rooms,temp);
                break;
                case 3:
                detectMotion(rooms,motion);
                break;
                case 4:
                securitySystem(rooms,door,motion,cycle);
                break;
                case 5:
                analyzeHouseStatus(rooms, light, temp, motion, door);
                break;
                default:
                case 6:
                printf("Exiting...\n");
                break;
                printf("\nEnter a valid choice\n");
            }
            
         ++cycle[0];
    } while (choice!=6);


    return 0;
}

 
void initializeSystem(int light[], int door[], int motion[],int temp[], int rooms) {
    printf("\nInitializing system...\n");
    int L=20,M=35; //For generating random values for temperature
    for (int i=0;i<rooms;i++){
        light[i]=0;
        door[i]=0;
        motion[i]=0;
        temp[i]=rand()%(M-L + 1)+L;
    } 
}

void displayMenu() {
    printf("\n===== Smart Home Menu ====\n\n1.Toggle Light\n2.Read Temperature\n3.Check Motion Sensor\n4.Lock/Unlock Security System\n5.House Status Summary\n6.Exit\n");
    
}
void controlLights(int rooms, int light[],int cycle[],int allon) {
        
    //For Additional Challenge
    for (int i=0;i<rooms;i++){
        allon = allon && light[i];
    }

    if(allon == 1 && cycle[0]>=5){
        printf("\n\nAll lights are ON for too long, consider turning them OFF\n\n");
        cycle[0]=0;
    }

    int room_no;
    printf("Enter room number to toggle light(%d-%d):",1,rooms);
    scanf("%d",&room_no);
    if(room_no<=0 || room_no>rooms){
        printf("Enter valid room number");
        return;
    }
    if(light[room_no-1] == 0){
        light[room_no-1]=1;}
    else{
        light[room_no-1]=0;
    }


    if(light[room_no-1]==1){
        printf("Light in Room %d is ON\n\n",room_no);}
    else{
        printf("Light in Room %d is OFF\n\n",room_no);
    }


}
void readTemperature(int rooms, int temp[]) {
    printf("Temperature status :\n\n");
    for(int i=0;i<rooms;i++){
        printf("Temperature in Room %d is %d°C\n",i+1,temp[i]);
        //For Additional challenge
        if(temp[i]>30){
            printf("(Warning temperature in room %d is above 30°C)\n\n",i+1);
        }
    }
}
void detectMotion(int rooms, int motion[]) {//The instruction says 'Check if any motion is detected' and not told the users to update it. Thats why i made the code like this(motion detection is 0 always)
    printf("Motion Sensors Status:\n");
    for(int i=0;i<rooms;i++){
        if(motion[i]==0){
            printf("No Motion Detected in Room %d\n",i+1);
        }
        else{
            printf("Motion Detected in Room \n%d",i+1);
        }
    }

}
void securitySystem(int rooms, int door[],int motion[],int cycle[]) {
    int doorno;
    int status;
    printf("\nEnter the Room number to lock or unlock the door(1-%d):",rooms);
    scanf("%d",&doorno);
    if(doorno<=0 || doorno>rooms){
        printf("\nEnter valid number");
        return;
    }
    printf("\nLock or Unlock the door (1/0) :");
    scanf("%d",&status);
    if(status!=1 && status!=0){
        printf("\nEnter valid number");
        return;
    }
    if(status==1){
        door[doorno-1]=1;
        printf("\nThe door of room %d is unlocked.\n",doorno);
    }
    else{
        door[doorno-1]=0;
        printf("\nThe door of room %d is locked.\n",doorno);
    }
    //Additional Challenge

    if(cycle[0]>=5){
        for(int i=0;i<rooms;i++){
            int nomotion=1;
            nomotion=nomotion && (motion[i]^1);
            if(nomotion==1){
                if(door[i]==1){
                    printf("\nSince, no motion is detected in room %d for 5 inputs the door is now locked automatically.\n",i+1);
                    door[i]=0;
                    cycle[0]=0;
                }

            }
        }
        
    }
}
void analyzeHouseStatus(int rooms, int light[], int temp[], int motion[], int door[]) {

printf("\nHouse Status:\n");
for(int i=0;i<rooms;i++){
    printf("Room %d : ",i+1);
    if(light[i]==0){
        printf("Light OFF,");
    }
    else if(light[i]==1){
        printf("Light ON,");
    }
    printf("Temp %d°C,",temp[i]);

    if(motion[i]==0){
        printf("No motion,");

    }
    else if(motion[i]==1){
        printf("Motion Detected,");
    }

    if(door[i]==0){
        printf("Locked\n");

    }
    else if(door[i]==1){
        printf("Unlocked\n");
    }
}

}

