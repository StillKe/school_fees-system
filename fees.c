to check if a string is numeric
int isNumeric(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0; // Not numeric
        }
    }
    return 1; // Numeric
}

// Function to load people data from a file
int loadPeople(struct Person people[], int *numPeople) {
    FILE* file = fopen("people.txt", "r");
    if (file == NULL) {
        printf("No saved data found.\n");
        return 0;
    }

    *numPeople = 0;
    char line[100];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "%49[^,],%49[^,],%49[^,],%d,%d,%d,%19[^\n]",
            people[*numPeople].firstName,
            people[*numPeople].middleName,
            people[*numPeople].lastName,
            &people[*numPeople].basicFees,
            &people[*numPeople].meals,
            &people[*numPeople].transport,
            people[*numPeople].grade) == 7) {
            (*numPeople)++;
        } else {
            printf("Invalid data format in file.\n");
        }
    }

    fclose(file);
    printf("Data loaded successfully.\n");
    return 1;
}

// Function to save people data to a file
void savePeople(struct Person people[], int numPeople) {
    FILE* file = fopen("people.txt", "w");
    if (file == NULL) {
        printf("Error opening the file for writing.\n");
        return;
    }

    for (int i = 0; i < numPeople; i++) {
        if (fprintf(file, "%s,%s,%s,%d,%d,%d,%s\n",
            people[i].firstName, people[i].middleName, people[i].lastName,
            people[i].basicFees, people[i].meals, people[i].transport,
            people[i].grade) < 0) {
            printf("Error writing data to the file.\n");
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("Data saved successfully.\n");
}

// Function to add a new person
void addPerson(struct Person people[], int *numPeople) {
    struct Person p;

    printf("Enter First Name: ");
    fgets(p.firstName, sizeof(p.firstName), stdin);
    p.firstName[strcspn(p.firstName, "\n")] = '\0';

    printf("Enter Middle Name: ");
    fgets(p.middleName, sizeof(p.middleName), stdin);
    p.middleName[strcspn(p.middleName, "\n")] = '\0';

    printf("Enter Last Name: ");
    fgets(p.lastName, sizeof(p.lastName), stdin);
    p.lastName[strcspn(p.lastName, "\n")] = '\0';

    printf("Enter grade:\n");
    printf("0. Baby Class\n");
    printf("1. Pp1\n");
    printf("2. Pp2\n");
    printf("3. Grade1\n");
    printf("4. Grade2\n");
    printf("5. Grade3\n");
    printf("6. Grade4\n");
    printf("7. Grade5\n");
    printf("8. Grade6\n");
    printf("9. Grade7\n");

    int grade;
    do {
        printf("Enter grade: ");
        char gradeStr[10];
        fgets(gradeStr, sizeof(gradeStr), stdin);
        gradeStr[strcspn(gradeStr, "\n")] = '\0'; // Remove trailing newline

        if (isNumeric(gradeStr)) {
            grade = atoi(gradeStr);
            if (grade >= 0 && grade <= 9) {
                break;
            }
        }
        printf("Invalid grade entered. Please enter a valid grade number.\n");
    } while (1);

    char gradeName[20];
    int basicFees;

    switch (grade) {
        case 0:
            strcpy(gradeName, "Baby Class");
            basicFees = 3000;
            break;
        case 1:
            strcpy(gradeName, "Pp1");
            basicFees = 3500;
            break;
        case 2:
            strcpy(gradeName, "Pp2");
            basicFees = 3500;
            break;
        case 3:
            strcpy(gradeName, "Grade1");
            basicFees = 4000;
            break;
        case 4:
            strcpy(gradeName, "Grade2");
            basicFees = 4000;
            break;
        case 5:
            strcpy(gradeName, "Grade3");
            basicFees = 4500;
            break;
        case 6:
            strcpy(gradeName, "Grade4");
            basicFees = 4500;
            break;
        case 7:
            strcpy(gradeName, "Grade5");
            basicFees = 4500;
            break;
        case 8:
            strcpy(gradeName, "Grade6");
            basicFees = 7000;
            break;
        case 9:
            strcpy(gradeName, "Grade7");
            basicFees = 7000;
            break;
    }

    printf("Enter meals:\n");
    printf("0. None\n");
    printf("1. 10 o'clock tea only\n");
    printf("2. Lunch only\n");
    printf("3. Both\n");

    int meals;
    do {
        printf("Enter meals: ");
        char mealsStr[10];
        fgets(mealsStr, sizeof(mealsStr), stdin);
        mealsStr[strcspn(mealsStr, "\n")] = '\0'; // Remove trailing newline

        if (isNumeric(mealsStr)) {
            meals = atoi(mealsStr);
            if (meals >= 0 && meals <= 3) {
                break;
            }
        }
        printf("Invalid input. Please enter a valid option.\n");
    } while (1);

    int mealsFees;
    switch (meals) {
        case 0:
            mealsFees = 0;
            break;
        case 1:
            mealsFees = 1500;
            break;
        case 2:
            mealsFees = 3000;
            break;
        case 3:
            mealsFees = 4500;
            break;
    }

    printf("Enter transport:\n");
    printf("0. None\n");
    printf("1. Included\n");

    int transport;
    do {
        printf("Enter transport: ");
        char transportStr[10];
        fgets(transportStr, sizeof(transportStr), stdin);
        transportStr[strcspn(transportStr, "\n")] = '\0'; // Remove trailing newline

        if (isNumeric(transportStr)) {
            transport = atoi(transportStr);
            if (transport >= 0 && transport <= 1) {
                break;
            }
        }
        printf("Invalid input. Please enter a valid option.\n");
    } while (1);

    int transportFees;
    switch (transport) {
        case 0:
            transportFees = 0;
            break;
        case 1:
            transportFees = 2000;
            break;
    }

    int totalFees = basicFees + mealsFees + transportFees;

    printf("Entered Details:\n");
    printf("Name: %s %s %s\n", p.firstName, p.middleName, p.lastName);
    printf("Grade: %s\n", gradeName);
    printf("Basic Fees: %d\n", basicFees);
    printf("Meals Fees: %d\n", mealsFees);
    printf("Transport Fees: %d\n", transportFees);
    printf("Total Fees: %d\n", totalFees);

    printf("Do you want to confirm the entered details (y/n)? ");
    char confirm;
    scanf(" %c", &confirm);
    getchar(); // Consume newline character

    if (confirm == 'y' || confirm == 'Y') {
        strcpy(p.grade, gradeName);
        p.basicFees = basicFees;
        p.meals = mealsFees;
        p.transport = transportFees;

        people[*numPeople] = p;
        (*numPeople)++;

        savePeople(people, *numPeople);
        printf("Details added successfully.\n");
    }
}

// Function to view people in a specific grade
void viewPeople(struct Person people[], int numPeople) {
    printf("Enter the grade to view people:\n");
    printf("0. Baby Class\n");
    printf("1. Pp1\n");
    printf("2. Pp2\n");
    printf("3. Grade1\n");
    printf("4. Grade2\n");
    printf("5. Grade3\n");
    printf("6. Grade4\n");
    printf("7. Grade5\n");
    printf("8. Grade6\n");
    printf("9. Grade7\n");

    int grade;
    do {
        printf("Enter grade: ");
        char gradeStr[10];
        fgets(gradeStr, sizeof(gradeStr), stdin);
        gradeStr[strcspn(gradeStr, "\n")] = '\0'; // Remove trailing newline

        if (isNumeric(gradeStr)) {
            grade = atoi(gradeStr);
            if (grade >= 0 && grade <= 9) {
                break;
            }
        }
        printf("Invalid grade entered. Please enter a valid grade number.\n");
    } while (1);

    char gradeName[20];
    switch (grade) {
        case 0:
            strcpy(gradeName, "Baby Class");
            break;
        case 1:
            strcpy(gradeName, "Pp1");
            break;
        case 2:
            strcpy(gradeName, "Pp2");
            break;
        case 3:
            strcpy(gradeName, "Grade1");
            break;
        case 4:
            strcpy(gradeName, "Grade2");
            break;
        case 5:
            strcpy(gradeName, "Grade3");
            break;
        case 6:
            strcpy(gradeName, "Grade4");
            break;
        case 7:
            strcpy(gradeName, "Grade5");
            break;
        case 8:
            strcpy(gradeName, "Grade6");
            break;
        case 9:
            strcpy(gradeName, "Grade7");
            break;
    }

    printf("List of People in Grade %s:\n", gradeName);
    int found = 0;

    for (int i = 0; i < numPeople; i++) {
        if (strcmp(people[i].grade, gradeName) == 0) {
            printf("%d. Name: %s %s %s\n", found + 1, people[i].firstName, people[i].middleName, people[i].lastName);
            printf("   Basic Fees: %d\n", people[i].basicFees);
            printf("   Meals Fees: %d\n", people[i].meals);
            printf("   Transport Fees: %d\n", people[i].transport);
            printf("   Total Fees: %d\n", people[i].basicFees + people[i].meals + people[i].transport);
            found++;
        }
    }

    if (found == 0) {
        printf("No people found in Grade %s.\n", gradeName);
    }
}

int main() {
    struct Person people[1000];
    int numPeople = 0;

    int loadSuccess = loadPeople(people, &numPeople);

    if (loadSuccess) {
        char response;
        do {
            printf("Do you want to add new people (a), view people (v), or exit (e)? ");
            scanf(" %c", &response);
            getchar(); // Consume newline character

            if (response == 'a' || response == 'A') {
                int numToAdd;
                do {
                    printf("How many people do you want to add? ");
                    char numStr[10];
                    fgets(numStr, sizeof(numStr), stdin);
                    numStr[strcspn(numStr, "\n")] = '\0';

                    if (isNumeric(numStr)) {
                        numToAdd = atoi(numStr);
                        break;
                    }
                    printf("Invalid input. Please enter a valid number.\n");
                } while (1);

                for (int i = 0; i < numToAdd; i++) {
                    addPerson(people, &numPeople);
                }
            } else if (response == 'v' || response == 'V') {
                viewPeople(people, numPeople);
            }
        } while (response != 'e' && response != 'E');
    }

    return 0;
}
