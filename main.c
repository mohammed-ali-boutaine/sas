
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// STRUCTURE Date
typedef struct {
    int year;
    int month;
    int day;
} Date;

// STRUCTURE Reservation
typedef struct {
    int id;
    char nom[25];
    char prenom[25];
    char tel[25];
    int age;
    char statut[25];
    Date date;
} Reservation;

Reservation reservations[10000];

// Function declarations
void addReservation();
void updateReservation();
void deleteReservation();
void showReservations();

// Sorting functions
void sortReservationByName();
void sortReservationByStatut();

// Search functions
void searchById();
void searchByNom();

// statisics
void moyenneAge();
void statistquesAge();
void statistiques();

// sub functions
void getNewElement(char elementName[], char element[]);
int generateID();
void showReservation(Reservation r);
int findIndexByID(int idToFind);


// menu
void menu() {
    // colors
    const char *colorReset = "\033[0m";
    const char *colorPurple = "\033[35m";
    const char *colorGreen = "\033[32m";
    const char *colorYellow = "\033[33m";
    const char *colorBlue = "\033[34m";
    const char *colorRed = "\033[31m";
    const char *colorCyan = "\033[36m";

    printf("%sMenu:%s\n", colorCyan, colorReset);
    printf("%s1.  Ajouter un Contact%s\n", colorPurple, colorReset);
    printf("%s2.  Modifier un Contact%s\n", colorYellow, colorReset);
    printf("%s3.  Supprimer un Contact%s\n", colorYellow, colorReset);
    printf("%s4.  Afficher Tous les Contacts%s\n", colorBlue, colorReset);

    printf("%s5.  Tri des reservations par nom%s\n", colorGreen, colorReset);
    printf("%s6.  Tri des reservations par statut%s\n", colorGreen, colorReset);

    printf("%s7.  Recherche des reservation par ID%s\n", colorYellow, colorReset);
    printf("%s8.  Recherche des reservation par nom%s\n", colorYellow, colorReset);

    // printf("%s9. Recherche des reservation par date%s\n", colorYellow, colorReset);
    printf("%s9. La moyenne d'age des patient%s\n", colorBlue, colorReset);
    printf("%s10. Afficher le nombre de patients par tranche d'age%s\n", colorBlue, colorReset);
    printf("%s11. Generer des statistiques pour connaitre le nombre total de reservations par statut%s\n", colorBlue, colorReset);

    printf("%s0. Quit%s\n", colorRed, colorReset);
}


// Variables
int choice;
char input[100];
int length = 0;
int globalID = 0;
char sortedBy[10] = "id";


const char *statut[] = {
    "valide",
    "reporte",
    "annule",
    "traite" 
};
int statutSize = sizeof(statut) / sizeof(statut[0]);



int main(){
        system("cls");// clear terminal


    // array of reservation
    Reservation reservationsDefaut[10] = {
        {0, "bou", "mohammed", "0624240219", 19, "annule", {2022, 2, 22}},
        {1, "bou", "mohammed", "0624240219", 11, "valide", {2022, 2, 22}},
        {2, "azo", "mohammed", "0624240219", 45, "valide", {2022, 2, 22}},
        {3, "bo4", "mohammed", "0624240219", 20, "annule", {2022, 2, 22}},
        {4, "bo5", "mohammed", "0624240219", 70, "valide", {2022, 2, 22}},
        {5, "bo6", "mohammed", "0624240219", 20, "valide", {2022, 2, 22}},
        {6, "bou7", "mohammed", "0624240219", 24, "annule", {2022, 2, 22}},
        {7, "azo", "mohammed", "0624240219", 22, "reporte", {2022, 2, 22}},
        {8, "bo9", "mohammed", "0624240219", 20, "traite", {2022, 2, 22}},
        {9, "b0", "mohammed", "0624240219", 30, "traite", {2022, 2, 22}}
    };

    for(int i = 0; i < 10; i++) {
        reservations[i] = reservationsDefaut[i];
        length++;
        globalID++;
    }


    do{
        // menu
        menu();
        printf("Votre option: ");
        scanf("%s", input); 

        char *endptr;
        choice = strtol(input, &endptr, 10);

        if (*endptr != '\0' || endptr == input) {
            printf("Entrée invalide, veuillez entrer un nombre.\n");
            continue;
        }
        system("cls");

        // Handle user choice
        switch (choice) {
            case 1:
                addReservation();
                break;
            case 2:
                updateReservation();
                break;
            case 3:
                deleteReservation();
                break;
            case 4:
                showReservations();
                break;
            case 5:
                sortReservationByName();
                showReservations();
                break;
            case 6:
                sortReservationByStatut();
                showReservations();
                break;
            case 7:
                searchById();
                break;
            case 8:
                searchByNom();
                break;
            case 9:
                moyenneAge();
                break;
            case 10:
                statistquesAge();
                break;
            case 11:
                statistiques();
                break;
            case 0:
                printf("Quitter le programme...\n");
                return 0;
            default:
                printf("Option invalide, veuillez réessayer.\n");
                break;
        }

    } while (1);

    return 0;
}




// functions intializations:
void addReservation(){ // id , nom , prenom, telephone , age , statut , date
    Reservation newReservation;

    newReservation.id = generateID(); // Generate ID


    getchar();

    printf("Enter Nom: ");
    fgets(newReservation.nom, sizeof(newReservation.nom), stdin);
    newReservation.nom[strcspn(newReservation.nom, "\n")] = 0; // Remove newline

    printf("Enter Prenom: ");
    fgets(newReservation.prenom, sizeof(newReservation.prenom), stdin);
    newReservation.prenom[strcspn(newReservation.prenom, "\n")] = 0; 

    printf("Enter Telephone: ");
    fgets(newReservation.tel, sizeof(newReservation.tel), stdin);
    newReservation.tel[strcspn(newReservation.tel, "\n")] = 0; 

    printf("Enter Age : ");
    scanf("%d",&newReservation.age );
    getchar(); 

    //---------------------------

    // Select status
    printf("Choose a statut:\n");
    for (int i = 0; i < statutSize; i++) {
        printf("%d. %s\n", i + 1, statut[i]);
    }
    int statutChoice;
    printf("Enter your choice (1-%d): ", statutSize);
    scanf("%d", &statutChoice);
    getchar(); 

    if (statutChoice >= 1 && statutChoice <= statutSize) {
        strcpy(newReservation.statut, statut[statutChoice - 1]);
    } else {
        printf("Invalid choice, defaulting to 'Unknown'.\n");
        strcpy(newReservation.statut, "Unknown");
    }

    //  date
    printf("Enter Date (YYYY MM DD): ");
    scanf("%d %d %d", &newReservation.date.year, &newReservation.date.month, &newReservation.date.day);
    getchar();

    reservations[length] = newReservation;
    length++;
    printf("Reservation added successfully!\n");
}

void updateReservation() {  

    int idToUpdate;
    printf("Enter the reservation ID to update: ");
    scanf("%d", &idToUpdate);

    int index = findIndexByID(idToUpdate);  // Use the findIndexByID function

    if (index == -1) {
        printf("Reservation with ID %d not found.\n", idToUpdate);
        return;
    }

    Reservation resToUpdate = reservations[index];  

    printf("Updating Reservation ID: %d\n", resToUpdate.id);

    getchar();  
    // nom
    getNewElement("Nom", resToUpdate.nom);

    // prenom
    getNewElement("Prenom", resToUpdate.prenom);

    // tel
    getNewElement("Telephone", resToUpdate.tel);

    // age
    printf("Enter Age (or press Enter to keep current): ");
    char input[50];
    fgets(input, sizeof(input), stdin);
    if (input[0] != '\n') {
        resToUpdate.age = atoi(input); // search about atoi 
    }

    // status
    printf("Choose a new statut:\n");
    for (int i = 0; i < statutSize; i++) {
        printf("%d. %s\n", i + 1, statut[i]);
    }
    int statutChoice;
    printf("Enter your choice (1-%d): ", statutSize);
    scanf("%d", &statutChoice);
    getchar();  
    if (statutChoice >= 1 && statutChoice <= statutSize) {
        strcpy(resToUpdate.statut, statut[statutChoice - 1]);
    } else {
        printf("Invalid choice, keeping current status.\n");
    }

    // date (not finished)
    int year, month, day;
    printf("Enter new year (or press Enter to keep current): ");
    fgets(input, sizeof(input), stdin);
    if (input[0] != '\n') {
        sscanf(input, "%d", &year);
        resToUpdate.date.year = year;
    }

    printf("Enter new month (or press Enter to keep current): ");
    fgets(input, sizeof(input), stdin);
    if (input[0] != '\n') {
        sscanf(input, "%d", &month);
        resToUpdate.date.month = month;
    }

    printf("Enter new day (or press Enter to keep current): ");
    fgets(input, sizeof(input), stdin);
    if (input[0] != '\n') {
        sscanf(input, "%d", &day);
        resToUpdate.date.day = day;
    }

    printf("Reservation updated successfully!\n");
}



void deleteReservation(){

    if (length == 0) {
        printf("No reservations to delete.\n");
        return;
    }
    
        int idToDelete;
        printf("Enter the reservation ID to delete: ");
        scanf("%d", &idToDelete);

        int index = findIndexByID(idToDelete);

        if(index != -1 ){

             printf("Reservation Details:\n");
             showReservation(reservations[index]);

    char confirm[4];  
    printf("Are you sure you want to delete this reservation? (yes/no): ");
    getchar();
    fgets(confirm, sizeof(confirm), stdin);
    
    if (strcmp(confirm, "yes") != 0) { 
        printf("Deletion cancelled.\n");
        return;
    }


            for(int j = index ; j < length-1 ; j++){
                reservations[j]=reservations[j+1] ;
            }

            length--;

        printf("Reservation with ID %d has been deleted successfully.\n", idToDelete);
            return;

        }

        printf("Reservation with ID %d not found.\n", idToDelete);

};

void showReservations(){

    printf("%d\n",length);

    if (length == 0) {
        printf("No reservation to display.\n");
        return;
    }

    printf("%12s  | %-10s | %-15s | %-15s | %-12s | %-10s | %-12s\n", "ID", "Nom", "Prenom", "Telephone", "statut", "Age", "Date");    
    printf("--------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < length; i++) {
        showReservation(reservations[i]);
    }

    printf("--------------------------------------------------------------------------------------------------------\n");


};



void showReservation(Reservation r){
    // printf("------------------------------------------------------------------------------------------------------------\n");
    printf("%12d | %-10s | %-15s | %-15s | %-12s | %-10d | %04d-%02d-%02d\n",
               r.id,
               r.nom,
               r.prenom,
               r.tel,
               r.statut,
               r.age,
               r.date.year,
               r.date.month,
               r.date.day
            );
}

void getNewElement(char elementName[],char element[] ){
    printf("Enter new %s (or press Enter to keep current): ",elementName);

    char newElement[25];

    fgets(newElement, sizeof(newElement), stdin);

    if (strlen(newElement) > 1) {
        newElement[strcspn(newElement, "\n")] = 0; // Remove newline
        strcpy(element, newElement);
    }

}

int generateID() {
    int unicId = globalID;
    globalID++;
    return unicId;
}


int findIndexByID(int x){// binary search for id

    int low = 0;
    int high = length-1;
    int mid;
    // binary search
    if(strcmp(sortedBy,"id")  == 0){
        while (low <= high) {
        int mid = low + (high - low) / 2;

        if (reservations[mid].id == x){
            return mid;
        }
        if (reservations[mid].id < x){
            low = mid + 1;
        }else{
            high = mid - 1;

        }
        }
    }else{//linear search
        for (int i = 0; i < length; i++) {
            if (reservations[i].id == x) {
                return i; // Found the reservation, return the index
            }
        }
    }

    return -1;// not found
}


// sort
void sortReservationByName(){

    strcpy(sortedBy,"nom");

    // insertion sort
    for(int i=1 ; i< length ; i++){

        Reservation holder=reservations[i];
        int j= i-1 ;

        while(j>=0 & strcmp(reservations[j].nom,holder.nom) > 0  ){
            reservations[j+1]=reservations[j];
            j--;
        }
        reservations[j+1] = holder;
    }
}

void sortReservationByStatut(){

    strcpy(sortedBy,"statut");
    printf("status\n");

    // insertion sort
    for(int i=1 ; i< length ; i++){

        Reservation holder=reservations[i];
        int j= i-1 ;

        while(j>=0 & strcmp(reservations[j].statut,holder.statut) > 0  ){
            reservations[j+1]=reservations[j];
            j--;
        }
        reservations[j+1] = holder;
    }
}


void sortReservationByDate(){

}


// search 

void searchById(){

    int id;
    printf("entre id our search: ");
    scanf("%d", &id);

    int index = findIndexByID(id);  
    if (index == -1) {
        printf("Reservation with ID %d not found.\n", id);
        return;
    }

    showReservation(reservations[index]);



}
void searchByNom() {
    int namesIndex[1000];
    int index = 0;

    char nom[50];

    getchar();

    printf("Entrez le nom a rechercher : ");
    fgets(nom, sizeof(nom), stdin);

    int len = strlen(nom);
    if (len > 0 && nom[len - 1] == '\n') {
        nom[len - 1] = '\0';
    }

    // Binary search
    if (strcmp(sortedBy, "nom") == 0) {
        int low = 0;
        int high = length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Compare the names
            int cmp = strcmp(reservations[mid].nom, nom);
            if (cmp == 0) {
                namesIndex[index] = mid;
                index++;
                // Look for other occurrences (to handle duplicates)
                int left = mid - 1;
                while (left >= 0 && strcmp(reservations[left].nom, nom) == 0) {
                    namesIndex[index] = left;
                    index++;
                    left--;
                }
                int right = mid + 1;
                while (right < length && strcmp(reservations[right].nom, nom) == 0) {
                    namesIndex[index] = right;
                    index++;
                    right++;
                }
                break; // Exit the loop once found
            }
            if (cmp < 0) {
                low = mid + 1; 
            } else {
                high = mid - 1; 
            }
        }
    } else { // Linear search
        for (int i = 0; i < length; i++) {
            if (strcmp(reservations[i].nom, nom) == 0) {
                namesIndex[index] = i; 
                index++;
            }
        }
    }

    // Print found names
    if (index > 0) {
        printf("\nReservations trouvees :\n");
        for (int i = 0; i < index; i++) {
            showReservation(reservations[namesIndex[i]]);
        }
    } else {
        printf("\nAucune reservation trouvee avec ce nom.\n");
    }
}





// statistiq 
void moyenneAge() {
    if (length == 0) {
        printf("\nAucune reservation trouvee.\n");
        return;
    }

    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += reservations[i].age;
    }

    printf("\nMoyenne d'age : %.2f\n", (float)sum / length);
}


void statistquesAge(){

    // 1: 0=>18 , 2: 19=>35 , 3: 36 => +  
    int tranche1 = 0, tranche2 = 0, tranche3 = 0;

    for (int i = 0; i < length; i++) {

        if(reservations[i].age > 0){
            if (reservations[i].age <= 18){
            tranche1++;
        }
        else if (reservations[i].age <= 35 ){
            tranche2++;
        }
        else{
            tranche3++;
        }

        }
        
    }

    printf("0-18 ans  : %d\n", tranche1);
    printf("19-35 ans : %d\n", tranche2);
    printf("36+ ans   : %d\n", tranche3);


}

void statistiques() {
    int valide = 0, reporte = 0, annule = 0, traite = 0;

    for (int i = 0; i < length; i++) {
        if (strcmp(reservations[i].statut, "valide") == 0)
            valide++;
        else if (strcmp(reservations[i].statut, "reporte") == 0)
            reporte++;
        else if (strcmp(reservations[i].statut, "annule") == 0)
            annule++;
        else if (strcmp(reservations[i].statut, "traite") == 0)
            traite++;
    }

    printf("\n");
    printf("Validees : %d\n", valide);
    printf("Reportees : %d\n", reporte);
    printf("Annulees : %d\n", annule);
    printf("Traitees : %d\n", traite);
}
