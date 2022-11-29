#include "Part1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int tableSize = 50;

//hashTable methods
int hashInt(int key) {
    return key % tableSize;
}

int hashString(char *key) {
    int temp = 0;
    for (int i = 0; i < strlen(key); i++) {
        temp = (temp * 33 ^ (int) key[i]) % tableSize;
    }
    return temp % tableSize;
}

//SNAP (StudentId-Name-Address-Phone)
void printSNAP(SNAPList *hashTable) {
    printf("StudentId\tName\t\t\tAddress\t\t\t\tPhone\n");
    for (int i = 0; i < tableSize; i++) {
        if (hashTable->lists[i] != NULL) {
            SNAP *SNAPtobePrinted = hashTable->lists[i];
            while (SNAPtobePrinted != NULL) {
                if (strcmp(SNAPtobePrinted->Address, "2700 B-H Townline Rd") == 0) {
                    printf("%d\t\t%s\t\t%s\t\t%s\n", SNAPtobePrinted->StudentId, SNAPtobePrinted->Name,
                           SNAPtobePrinted->Address, SNAPtobePrinted->Phone);
                } else {
                    printf("%d\t\t%s\t\t%s\t\t\t%s\n", SNAPtobePrinted->StudentId, SNAPtobePrinted->Name,
                           SNAPtobePrinted->Address, SNAPtobePrinted->Phone);
                }
                SNAPtobePrinted = SNAPtobePrinted->nextSNAP;
            }
        }
    }
    printf("\n");
}

void printSNAP2(SNAPList *hashTable) {
    printf("StudentId\tName\t\tAddress\t\tPhone\n");
    for (int i = 0; i < tableSize; i++) {
        if (hashTable->lists[i] != NULL) {
            SNAP *SNAPtobePrinted = hashTable->lists[i];
            while (SNAPtobePrinted != NULL) {
                printf("%d\t\t%s\t\t%s\t\t%s\t\t", SNAPtobePrinted->StudentId, SNAPtobePrinted->Name,
                       SNAPtobePrinted->Address, SNAPtobePrinted->Phone);
                SNAPtobePrinted = SNAPtobePrinted->nextSNAP;
            }
            printf("\n");
        }
    }
    printf("\n");
}

SNAPList *new_SNAPList() {
    SNAPList *hashTable = (SNAPList *) malloc(sizeof(SNAPList));
    hashTable->lists = (SNAP **) malloc(sizeof(SNAP *) * tableSize);
    for (int i = 0; i < tableSize; i++) {
        hashTable->lists[i] = NULL;
    }
    return hashTable;
}

SNAP *newSNAP(int StudentId, char *Name, char *Address, char *Phone) {
    SNAP *SNAPnew = (SNAP *) malloc(sizeof(SNAP));
    SNAPnew->Address = (char *) malloc(strlen(Address) + 1);
    SNAPnew->Name = (char *) malloc(strlen(Name) + 1);
    SNAPnew->Phone = (char *) malloc(strlen(Phone) + 1);

    SNAPnew->Address = Address;
    SNAPnew->Name = Name;
    SNAPnew->Phone = Phone;

    SNAPnew->StudentId = StudentId;
    SNAPnew->nextSNAP = NULL;
    return SNAPnew;
}

void insert_SNAP(SNAPList *hashTable, int StudentId, char *Name, char *Address, char *Phone) {
    int hash = hashInt(StudentId);
    SNAP *currentSNAP = hashTable->lists[hash];
    if (currentSNAP == NULL) { //if not already in hashtable, create new
        hashTable->lists[hash] = newSNAP(StudentId, Name, Address, Phone);
        return;
    }

    //move through linkedlist
    SNAP *previousSNAP = currentSNAP;
    while (currentSNAP != NULL) {
        if (strcmp(currentSNAP->Name, Name) == 0 && strcmp(currentSNAP->Address, Address) == 0 &&
            strcmp(currentSNAP->Phone, Phone) == 0) {
            return;
        } else {
            previousSNAP = currentSNAP;
            currentSNAP = currentSNAP->nextSNAP;
        }
    }
    previousSNAP->nextSNAP = newSNAP(StudentId, Name, Address, Phone);
}

void lookup_SNAP(SNAPList *hashTable, int StudentId, char *Name, char *Address, char *Phone) {
    int hash = hashInt(StudentId);
    SNAP *currentSNAP = hashTable->lists[hash];

    while (currentSNAP != NULL) {
        if (strcmp(Name, "*") == 0) {
            if (strcmp(Address, "*") == 0) {
                if (strcmp(currentSNAP->Phone, Phone) == 0) {
                    printf("Name: %s, Address: %s\n", currentSNAP->Name, currentSNAP->Address);
                }
            } else if (strcmp(Phone, "*") == 0) {
                if (strcmp(currentSNAP->Address, Address) == 0) {
                    printf("Name: %s, Phone: %s\n", currentSNAP->Name, currentSNAP->Phone);
                }
            } else {
                if (strcmp(currentSNAP->Address, Address) == 0 && strcmp(currentSNAP->Phone, Phone) == 0) {
                    printf("Name: %s\n", currentSNAP->Name);
                }
            }
        } else if (strcmp(Address, "*") == 0) {
            if (strcmp(Phone, "*") == 0) {
                if (strcmp(currentSNAP->Name, Name) == 0) {
                    printf("Phone: %s, Address: %s\n", currentSNAP->Phone, currentSNAP->Name);
                }
            } else {
                if (strcmp(currentSNAP->Name, Name) == 0 || strcmp(currentSNAP->Phone, Phone) == 0) {
                    printf("Address: %s\n", currentSNAP->Address);
                }
            }
        }
        currentSNAP = currentSNAP->nextSNAP;
    }
}

void delete_SNAP(SNAPList *hashTable, int StudentId, char *Name, char *Address, char *Phone) {
    int hash = hashInt(StudentId);
    SNAP *currentSNAP = hashTable->lists[hash];

    if (currentSNAP == NULL) {
        return;
    }
    SNAP *previousSNAP = currentSNAP;
    int bucketIndex = 0;
    while (currentSNAP != NULL) {
        if (strcmp(currentSNAP->Name, Name) == 0 && strcmp(currentSNAP->Address, Address) == 0 &&
            strcmp(currentSNAP->Phone, Phone) == 0) {
            if (currentSNAP->nextSNAP == NULL && bucketIndex == 0) {
                hashTable->lists[hash] = NULL;
            }
            if (currentSNAP->nextSNAP != NULL && bucketIndex == 0) {
                hashTable->lists[hash] = previousSNAP->nextSNAP;
            }
            if (currentSNAP->nextSNAP == NULL && bucketIndex != 0) {
                previousSNAP->nextSNAP = NULL;
            }
            if (currentSNAP->nextSNAP != NULL && bucketIndex != 0) {
                previousSNAP->nextSNAP = previousSNAP->nextSNAP;
            }
        }
        previousSNAP = currentSNAP;
        currentSNAP = previousSNAP->nextSNAP;
        bucketIndex++;
    }
}

void freeSNAP(SNAP *snap) {
    if (snap->nextSNAP == NULL) {
        free(snap);
        return;
    } else {
        freeSNAP(snap->nextSNAP);
        snap->nextSNAP = NULL;
        free(snap);
    }
}

//CSG (Course-StudentId-Grade)
void printCSG(CSGList *hashTable) {
    printf("StudentId\tCourse\tGrade\n");
    for (int i = 0; i < tableSize; i++) {
        if (hashTable->lists[i] != NULL) {
            CSG *CSGtobePrinted = hashTable->lists[i];
            while (CSGtobePrinted != NULL) {
                printf("%d\t\t%s\t%s\n", CSGtobePrinted->StudentId, CSGtobePrinted->Course, CSGtobePrinted->Grade);
                CSGtobePrinted = CSGtobePrinted->nextCSG;
            }
        }
    }
    printf("\n");
}

void printCSG2(CSGList *hashTable) {
    printf("StudentId\tCourse\tGrade\n");
    for (int i = 0; i < tableSize; i++) {
        if (hashTable->lists[i] != NULL) {
            CSG *CSGtobePrinted = hashTable->lists[i];
            while (CSGtobePrinted != NULL) {
                printf("%d\t\t%s\t%s\t\t", CSGtobePrinted->StudentId, CSGtobePrinted->Course, CSGtobePrinted->Grade);
                CSGtobePrinted = CSGtobePrinted->nextCSG;
            }
            printf("\n");
        }
    }
    printf("\n");
}

CSGList *new_CSGList() {
    CSGList *hashTable = (CSGList *) malloc(sizeof(CSGList));
    hashTable->lists = (CSG **) malloc(sizeof(CSG *) * tableSize);
    for (int i = 0; i < tableSize; i++) {
        hashTable->lists[i] = NULL;
    }
    return hashTable;
}

CSG *newCSG(int StudentId, char *Course, char *Grade) {
    CSG *CSGnew = (CSG *) malloc(sizeof(CSG));
    CSGnew->Course = (char *) malloc(strlen(Course) + 1);
    CSGnew->Grade = (char *) malloc(strlen(Grade) + 1);

    CSGnew->Course = Course;
    CSGnew->Grade = Grade;

    CSGnew->StudentId = StudentId;
    CSGnew->nextCSG = NULL;
    return CSGnew;
}

void insert_CSG(CSGList *hashTable, char *Course, int StudentId, char *Grade) {
    int hash = hashInt(StudentId);
    CSG *currentCSG = hashTable->lists[hash];
    if (currentCSG == NULL) {
        hashTable->lists[hash] = newCSG(StudentId, Course, Grade);
        return;
    }

    CSG *previousCSG = currentCSG;
    while (currentCSG != NULL) {
        if (strcmp(currentCSG->Grade, Grade) == 0 && strcmp(currentCSG->Course, Course) == 0) {
            return;
        } else {
            previousCSG = currentCSG;
            currentCSG = currentCSG->nextCSG;
        }
    }
    previousCSG->nextCSG = newCSG(StudentId, Course, Grade);
}

void lookup_CSG(CSGList *hashTable, char *Course, int StudentId, char *Grade) {
    int hash = hashInt(StudentId);
    CSG *currentCSG = hashTable->lists[hash];

    while (currentCSG != NULL) {
        if (strcmp(Course, "*") == 0) {
            if (strcmp(Grade, "*") == 0) {
                printf("(%s, %d, %s)\n", currentCSG->Course, StudentId, currentCSG->Grade);
            } else {
                if (strcmp(currentCSG->Grade, Grade) == 0) {
                    printf("(%s, %s, %d)\n", currentCSG->Course, Grade, StudentId);
                }
            }
        } else {
            if (strcmp(currentCSG->Course, Course) == 0) {
                printf("(%s, %d, %s)\n", Course, StudentId, currentCSG->Grade);
            }
        }
        currentCSG = currentCSG->nextCSG;
    }
}

void delete_CSG(CSGList *hashTable, char *Course, int StudentId, char *Grade) {
    int hash = hashInt(StudentId);
    CSG *currentCSG = hashTable->lists[hash];
    if (currentCSG == NULL) {
        return;
    }

    CSG *previousCSG = currentCSG;
    int bucketIndex = 0;
    while (currentCSG != NULL) {
        if ((strcmp(currentCSG->Course, Course) == 0 && strcmp(currentCSG->Grade, Grade) == 0)
            || (strcmp(currentCSG->Course, Course) == 0 && strcmp(Grade, "*") == 0)
            || (strcmp(currentCSG->Grade, Grade) == 0 && strcmp(Course, "*") == 0)
            || (strcmp(Course, "*") == 0 && strcmp(Grade, "*") == 0)) {
            if (currentCSG->nextCSG == NULL && bucketIndex == 0) {
                hashTable->lists[hash] = NULL;
            }
            if (currentCSG->nextCSG != NULL && bucketIndex == 0) {
                hashTable->lists[hash] = currentCSG->nextCSG;
            }
            if (currentCSG->nextCSG == NULL && bucketIndex != 0) {
                previousCSG->nextCSG = NULL;
            }
            if (currentCSG->nextCSG != NULL && bucketIndex != 0) {
                previousCSG->nextCSG = currentCSG->nextCSG;
            }
        }
        previousCSG = currentCSG;
        currentCSG = previousCSG->nextCSG;
        bucketIndex++;
    }
}

void freeCSG(CSG *csg) {
    if (csg->nextCSG == NULL) {
        free(csg);
        return;
    } else {
        freeCSG(csg->nextCSG);
        csg->nextCSG = NULL;
        free(csg);
    }
}


//CP(Course-Prerequisite)
void printCP(CPList *hashTable) {
    printf("Course\tPrerequisite\n");
    for (int i = 0; i < tableSize; i++) {
        if (hashTable->lists[i] != NULL) {
            CP *CPtobePrinted = hashTable->lists[i];
            while (CPtobePrinted != NULL) {
                printf("%s\t%s\n", CPtobePrinted->Course, CPtobePrinted->Prerequisite);
                CPtobePrinted = CPtobePrinted->nextCP;
            }
        }
    }
    printf("\n");
}

void printCP2(CPList *hashTable) {
    printf("Course\tPrerequisite\n");
    for (int i = 0; i < tableSize; i++) {
        if (hashTable->lists[i] != NULL) {
            CP *CPtobePrinted = hashTable->lists[i];
            while (CPtobePrinted != NULL) {
                printf("%s\t%s\t\t", CPtobePrinted->Course, CPtobePrinted->Prerequisite);
                CPtobePrinted = CPtobePrinted->nextCP;
            }
            printf("\n");
        }
    }
    printf("\n");
}

CPList *new_CPList() {
    CPList *hashTable = (CPList *) malloc(sizeof(CPList));
    hashTable->lists = (CP **) malloc(sizeof(CP *) * tableSize);
    for (int i = 0; i < tableSize; i++) {
        hashTable->lists[i] = NULL;
    }
    return hashTable;
}

CP *newCP(char *Course, char *Prerequisite) {
    CP *CPnew = (CP *) malloc(sizeof(CP));
    CPnew->Course = (char *) malloc(strlen(Course) + 1);
    CPnew->Prerequisite = (char *) malloc(strlen(Prerequisite) + 1);

    CPnew->Course = Course;
    CPnew->Prerequisite = Prerequisite;
    CPnew->nextCP = NULL;
    return CPnew;
}

void insert_CP(CPList *hashTable, char *Course, char *Prerequisite) {
    int hash = hashString(Course);
    CP *currentCP = hashTable->lists[hash];
    if (currentCP == NULL) {
        hashTable->lists[hash] = newCP(Course, Prerequisite);
        return;
    }

    CP *prev = currentCP;
    while (currentCP != NULL) {
        if (strcmp(currentCP->Course, Course) == 0 &&
        strcmp(currentCP->Prerequisite, Prerequisite) == 0) {
            return;
        } else {
            prev = currentCP;
            currentCP = currentCP->nextCP;
        }
    }
    prev->nextCP = newCP(Course, Prerequisite);
}

void lookup_CP(CPList *hashTable, char *Course, char *Prerequisite) {
    int hash = hashString(Course);
    CP *CPCurr = hashTable->lists[hash];

    while (CPCurr != NULL) {
        if (strcmp(Prerequisite, "*") == 0) {
            printf("(%s, %s)\n", CPCurr->Course, CPCurr->Prerequisite);
        } else {
            if (strcmp(CPCurr->Prerequisite, Prerequisite) == 0) {
                printf("(%s, %s)\n", CPCurr->Course, CPCurr->Prerequisite);
            }
        }
        CPCurr = CPCurr->nextCP;
    }
}

void delete_CP(CPList *hashTable, char *Course, char *Prerequisite) {
    int hash = hashString(Course);
    CP *CPCurr = hashTable->lists[hash];

    if (CPCurr == NULL) {
        return;
    }
    CP *CPRev = CPCurr;
    int bucketIndex = 0;
    while (CPCurr != NULL) {
        if (strcmp(CPCurr->Prerequisite, Prerequisite) || strcmp(Prerequisite, "*")) {
            if (CPCurr->nextCP == NULL && bucketIndex == 0) {
                hashTable->lists[hash] = NULL;
            }
            if (CPCurr->nextCP != NULL && bucketIndex == 0) {
                hashTable->lists[hash] = CPRev->nextCP;
            }
            if (CPCurr->nextCP == NULL && bucketIndex != 0) {
                CPRev->nextCP = NULL;
            }
            if (CPCurr->nextCP != NULL && bucketIndex != 0) {
                CPRev->nextCP = CPRev->nextCP;
            }
        }
        CPRev = CPCurr;
        CPCurr = CPRev->nextCP;
        bucketIndex++;
    }
}

void freeCP(CP *cp) {
    if (cp->nextCP == NULL) {
        free(cp);
        return;
    } else {
        freeCP(cp->nextCP);
        cp->nextCP = NULL;
        free(cp);
    }
}

//CDH (Course-Day-Hour)
void printCDH(CDHList *hashTable) {
    printf("Course\tDay\tHour\n");
    for (int i = 0; i < tableSize; i++) {
        if (hashTable->lists[i] != NULL) {
            CDH *CDHtobePrinted = hashTable->lists[i];
            while (CDHtobePrinted != NULL) {
                printf("%s\t%s\t%s\n", CDHtobePrinted->Course, CDHtobePrinted->Day, CDHtobePrinted->Hour);
                CDHtobePrinted = CDHtobePrinted->nextCDH;
            }
        }
    }
    printf("\n");
}

void printCDH2(CDHList *hashTable) {
    printf("Course\tDay\tHour\n");
    for (int i = 0; i < tableSize; i++) {
        if (hashTable->lists[i] != NULL) {
            CDH *CDHtobePrinted = hashTable->lists[i];
            while (CDHtobePrinted != NULL) {
                printf("%s\t%s\t%s\t\t", CDHtobePrinted->Course, CDHtobePrinted->Day, CDHtobePrinted->Hour);
                CDHtobePrinted = CDHtobePrinted->nextCDH;
            }
            printf("\n");
        }
    }
    printf("\n");
}

CDHList *new_CDHList() {
    CDHList *hashTable = (CDHList *) malloc(sizeof(CDHList));
    hashTable->lists = (CDH **) malloc(sizeof(CP *) * tableSize);
    for (int i = 0; i < tableSize; i++) {
        hashTable->lists[i] = NULL;
    }
    return hashTable;
}

CDH *newCDH(char *Course, char *Day, char *Hour) {
    CDH *CDHnew = (CDH *) malloc(sizeof(CDH));
    CDHnew->Course = (char *) malloc(strlen(Course) + 1);
    CDHnew->Day = (char *) malloc(strlen(Day) + 1);
    CDHnew->Hour = (char *) malloc(strlen(Hour) + 1);

    CDHnew->Course = Course;
    CDHnew->Day = Day;
    CDHnew->Hour = Hour;
    CDHnew->nextCDH = NULL;
    return CDHnew;
}

void insert_CDH(CDHList *hashTable, char *Course, char *Day, char *Hour) {
    int hash = hashString(Course);
    CDH *currentCDH = hashTable->lists[hash];
    if (currentCDH == NULL) {
        hashTable->lists[hash] = newCDH(Course, Day, Hour);
        return;
    }

    CDH *prev = currentCDH;
    while (currentCDH != NULL) {
        prev = currentCDH;
        currentCDH = currentCDH->nextCDH;
    }
    prev->nextCDH = newCDH(Course, Day, Hour);
}

void lookup_CDH(CDHList *hashTable, char *Course, char *Day, char *Hour) {
    int hash = hashString(Course);
    CDH *currentCDH = hashTable->lists[hash];

    while (currentCDH != NULL) {
        if (strcmp(Day, "*") == 0) {
            if (strcmp(Hour, "*") == 0) {
                printf("Day: %s, Hour: %s\n", Day, Hour);
            } else {
                if (strcmp(currentCDH->Hour, Hour) == 0) {
                    printf("Day: %s\n", Day);
                }
            }
        } else {
            if (strcmp(currentCDH->Day, Day) == 0) {
                printf("Hour: %s", Hour);
            }
        }
        currentCDH = currentCDH->nextCDH;
    }
}

void delete_CDH(CDHList *hashTable, char *Course, char *Day, char *Hour) {
    int hash = hashString(Course);
    CDH *currentCDH = hashTable->lists[hash];
    if (currentCDH == NULL) {
        return;
    }
    
    CDH *previousCDH = currentCDH;
    int bucketIndex = 0;
    while (currentCDH != NULL) {
        if ((strcmp(currentCDH->Day, Day) == 0 && strcmp(currentCDH->Hour, Hour) == 0)
            || (strcmp(currentCDH->Day, Day) == 0 && strcmp(Hour, "*") == 0)
            || (strcmp(currentCDH->Hour, Hour) == 0 && strcmp(Day, "*") == 0)
            || (strcmp(Day, "*") == 0 && strcmp(Hour, "*") == 0)) {
            if (currentCDH->nextCDH == NULL && bucketIndex == 0) {
                hashTable->lists[hash] = NULL;
            }
            if (currentCDH->nextCDH != NULL && bucketIndex == 0) {
                hashTable->lists[hash] = previousCDH->nextCDH;
            }
            if (currentCDH->nextCDH == NULL && bucketIndex != 0) {
                previousCDH->nextCDH = NULL;
                hashTable->lists[hash] = NULL;
            }
            if (currentCDH->nextCDH != NULL && bucketIndex != 0) {
                previousCDH->nextCDH = previousCDH->nextCDH;
            }
        }
        previousCDH = currentCDH;
        currentCDH = previousCDH->nextCDH;
        bucketIndex++;
    }
}

void freeCDH(CDH *cdh) {
    if (cdh->nextCDH == NULL) {
        free(cdh);
        return;
    } else {
        freeCDH(cdh->nextCDH);
        cdh->nextCDH = NULL;
        free(cdh);
    }
}


//CR (Course-Room)
void printCR(CRList *hashTable) {
    printf("Course\tRoom\n");
    for (int i = 0; i < tableSize; i++) {
        if (hashTable->lists[i] != NULL) {
            CR *COut = hashTable->lists[i];
            while (COut != NULL) {
                printf("%s\t%s\n", COut->Course, COut->Room);
                COut = COut->nextCR;
            }
        }
    }
    printf("\n");
}

void printCR2(CRList *hashTable) {
    printf("Course\tRoom\n");
    for (int i = 0; i < tableSize; i++) {
        if (hashTable->lists[i] != NULL) {
            CR *COut = hashTable->lists[i];
            while (COut != NULL) {
                printf("%s\t%s\t\t", COut->Course, COut->Room);
                COut = COut->nextCR;
            }
            printf("\n");
        }
    }
    printf("\n");
}

CRList *new_CRList() {
    CRList *hashTable = (CRList *) malloc(sizeof(CRList));
    hashTable->lists = (CR **) malloc(sizeof(CR *) * tableSize);
    for (int i = 0; i < tableSize; i++) {
        hashTable->lists[i] = NULL;
    }
    return hashTable;
}

CR *newCR(char *Course, char *Room) {
    CR *CRnew = (CR *) malloc(sizeof(CR));
    CRnew->Course = (char *) malloc(strlen(Course) + 1);
    CRnew->Room = (char *) malloc(strlen(Course) + 1);

    CRnew->Course = Course;
    CRnew->Room = Room;
    CRnew->nextCR = NULL;
    return CRnew;
}

void insert_CR(CRList *hashTable, char *Course, char *Room) {
    int hash = hashString(Course);
    CR *currentCR = hashTable->lists[hash];
    if (currentCR == NULL) {
        hashTable->lists[hash] = newCR(Course, Room);
        return;
    }

    CR *prev = currentCR;
    while (currentCR != NULL) {
        prev = currentCR;
        currentCR = currentCR->nextCR;
    }
    prev->nextCR = newCR(Course, Room);
}

void lookup_CR(CRList *hashTable, char *Course, char *Room) {
    int hash = hashString(Course);
    CR *currentCR = hashTable->lists[hash];

    while (currentCR != NULL) {
        if (strcmp(Room, "*") == 0) {
            printf("%s\n", currentCR->Room);
        } else {
            if (strcmp(currentCR->Room, Room) == 0) {
                printf("%s\n", currentCR->Room);
            }
        }
        currentCR = currentCR->nextCR;
    }
}

void delete_CR(CRList *hashTable, char *Course, char *Room) {
    int hash = hashString(Course);
    CR *currentCR = hashTable->lists[hash];
    if (currentCR == NULL) {
        return;
    }
    
    CR *previousCR = currentCR;
    int bucketIndex = 0;
    while (currentCR != NULL) {
        if (strcmp(currentCR->Room, Room) || strcmp(Room, "*")) {
            if (currentCR->nextCR == NULL && bucketIndex == 0) {
                hashTable->lists[hash] = NULL;
            }
            if (currentCR->nextCR != NULL && bucketIndex == 0) {
                hashTable->lists[hash] = previousCR->nextCR;
            }
            if (currentCR->nextCR == NULL && bucketIndex != 0) {
                previousCR->nextCR = NULL;
            }
            if (currentCR->nextCR != NULL && bucketIndex != 0) {
                previousCR->nextCR = previousCR->nextCR;
            }
        }
        previousCR = currentCR;
        currentCR = previousCR->nextCR;
        bucketIndex++;
    }
}

void freeCR(CR *cr) {
    if (cr->nextCR == NULL) {
        free(cr);
        return;
    } else {
        freeCR(cr->nextCR);
        cr->nextCR = NULL;
        free(cr);
    }
}