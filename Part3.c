#include "Part1.h"
#include "Part3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CSGList *selection_CSG(CSGList *CSGHash, int id) {
    CSGList *newList = new_CSGList();
    for (int i = 0; i < tableSize; i++) {
        CSG *viewCSG = CSGHash->lists[i];
        while (viewCSG != NULL) {
            if (viewCSG->StudentId == id) {
                insert_CSG(newList, viewCSG->Course, viewCSG->StudentId, viewCSG->Grade);
            }
            viewCSG = viewCSG->nextCSG;
        }
    }
    return newList;
}

void projection_CSG(CSGList *CSGHash, char *type) {
    int bucketCount = 0;
    for (int i = 0; i < tableSize; i++) {
        CSG *view = CSGHash->lists[i];
        while (view != NULL) {
            bucketCount ++;
            view = view->nextCSG;
        }
    }
    char **stringList = (char **) malloc(sizeof(char *) * bucketCount);
    int *intList = (int *) malloc(sizeof(int) * bucketCount);
    int index = 0;
    for (int i = 0; i < tableSize; i++) {
        CSG *viewCSG = CSGHash->lists[i];
        while (viewCSG != NULL) {
            if (strcmp(type, "Course") == 0) {
                stringList[index] = (char *) malloc(strlen(viewCSG->Course) + 1);
                strcpy(stringList[index], viewCSG->Course);
                index++;
            } else if (strcmp(type, "StudentId") == 0) {
                intList[index] = viewCSG->StudentId;
                index++;
            } else if (strcmp(type, "Grade") == 0) {
                stringList[index] = (char *) malloc(strlen(viewCSG->Course) + 1);
                strcpy(stringList[index], viewCSG->Grade);
                index++;
            }
            viewCSG = viewCSG->nextCSG;
        }
    }

    //print string
    if (strcmp(type, "Grade") == 0 || strcmp(type, "Course") == 0) {
        for (int i = 0; i < bucketCount; i++) {
            printf("%s\n", stringList[i]);
        }
        for (int i = 0; i < bucketCount; i++) {
            free(stringList[i]);
        }
    } else { //print int
        printf("student ID\n");
        for (int i = 0; i < bucketCount; i++) {
            printf("%d\n", intList[i]);
        }
    }
    free(stringList);
    free(intList);
}

CRDHList *newCRDHList() {
    CRDHList *Hashtable = (CRDHList *) malloc(sizeof(CRDHList));
    Hashtable->lists = (CRDH **) malloc(sizeof(CRDH) * tableSize);
    for (int i = 0; i < tableSize; i++) {
        Hashtable->lists[i] = NULL;
    }
    return Hashtable;
}

CRDH *newCRDH(char *Course, char *Room, char *Day, char *Hour) {
    CRDH *output = (CRDH *) malloc(sizeof(CRDH));
    output->Course = (char *) malloc(strlen(Course) + 1);
    output->Room = (char *) malloc(strlen(Room) + 1);
    output->Day = (char *) malloc(strlen(Day) + 1);
    output->Hour = (char *) malloc(strlen(Hour) + 1);

    output->Course = Course;
    output->Room = Room;
    output->Day = Day;
    output->Hour = Hour;
    output->nextCRDH = NULL;
    return output;
}

void insert_CRDH(CRDHList *CRDHHash, char *Course, char *room, char *Day, char *Hour) {
    int hash = hashString(Course);
    CRDH *viewCRDH = CRDHHash->lists[hash];
    if (viewCRDH == NULL) {
        CRDHHash->lists[hash] = newCRDH(Course, room, Day, Hour);
        return;
    }
    CRDH *previous = viewCRDH;
    while (viewCRDH != NULL) {
        previous = viewCRDH;
        viewCRDH = viewCRDH->nextCRDH;
    }
    previous->nextCRDH = newCRDH(Course, room, Day, Hour);
}

void printCRDH(CRDHList *table) {
    printf("COURSE\tROOM\t\t\tDAY\tHOUR\n");
    for (int i = 0; i < tableSize; i++) {
        if (table->lists[i] != NULL) {
            CRDH *viewCRDH = table->lists[i];
            while (viewCRDH != NULL) {
                if (strcmp(viewCRDH->Room, "Bausch & Lomb 109") == 0 || strcmp(viewCRDH->Room, "Hutchison Hall 141") == 0) {
                    printf("%s\t%s\t%s\t%s\n", viewCRDH->Course, viewCRDH->Room, viewCRDH->Day, viewCRDH->Hour);
                } else {
                    printf("%s\t%s\t\t%s\t%s\n", viewCRDH->Course, viewCRDH->Room, viewCRDH->Day, viewCRDH->Hour);
                }
                viewCRDH = viewCRDH->nextCRDH;
            }
        }
    }
}

CRDHList *joinCRDH(CRList *CRHash, CDHList *CDHHash) {
    CRDHList *output = newCRDHList();
    for (int i = 0; i < tableSize; i++) {
        CDH *viewCDH = CDHHash->lists[i];
        while (viewCDH != NULL) {
            int index = hashString(viewCDH->Course);
            CR *viewCR = CRHash->lists[index];
            while (viewCR != NULL) {
                insert_CRDH(output, viewCR->Course, viewCR->Room, viewCDH->Day, viewCDH->Hour);
                viewCR = viewCR->nextCR;
            }
            viewCDH = viewCDH->nextCDH;
        }
    }
    return output;
}

void projection_CRDH(CRDHList *CRDHHash, char *type1, char *type2) {
    int buckedSize = 0;
    for (int i = 0; i < tableSize; i++) {
        CRDH *currentCRDH = CRDHHash->lists[i];
        while (currentCRDH != NULL) {
            buckedSize += 1;
            currentCRDH = currentCRDH->nextCRDH;
        }
    }

    char **stringList1 = (char **) malloc(sizeof(char *) * buckedSize);
    char **stringList2 = (char **) malloc(sizeof(char *) * buckedSize);

    //check type1
    int index = 0;
    for (int i = 0; i < tableSize; i++) {
        CRDH *currentCRDH = CRDHHash->lists[i];
        while (currentCRDH != NULL) {
            if (strcmp(type1, "Course") == 0) {
                stringList1[index] = (char *) malloc(strlen(currentCRDH->Course) + 1);
                strcpy(stringList1[index], currentCRDH->Course);
                index++;
            } else if (strcmp(type1, "Room") == 0) {
                stringList1[index] = (char *) malloc(strlen(currentCRDH->Room) + 1);
                strcpy(stringList1[index], currentCRDH->Room);
                index++;
            } else if (strcmp(type1, "Day") == 0) {
                stringList1[index] = (char *) malloc(strlen(currentCRDH->Day) + 1);
                strcpy(stringList1[index], currentCRDH->Day);
                index++;
            } else if (strcmp(type1, "Hour") == 0) {
                stringList1[index] = (char *) malloc(strlen(currentCRDH->Hour) + 1);
                strcpy(stringList1[index], currentCRDH->Hour);
                index++;
            }
            currentCRDH = currentCRDH->nextCRDH;
        }
    }

    //check type2 (the same)
    int index2 = 0;
    for (int i = 0; i < tableSize; i++) {
        CRDH *currentCRDH = CRDHHash->lists[i];
        while (currentCRDH != NULL) {
            if (strcmp(type2, "Course") == 0) {
                stringList2[index2] = (char *) malloc(strlen(currentCRDH->Course) + 1);
                //charList2[index] = curr2->Course;
                strcpy(stringList2[index2], currentCRDH->Course);
                index2++;
            } else if (strcmp(type2, "Room") == 0) {
                stringList2[index2] = (char *) malloc(strlen(currentCRDH->Room) + 1);
                //charList2[index] = curr2->Room;
                strcpy(stringList2[index2], currentCRDH->Room);
                index2++;
            } else if (strcmp(type2, "Day") == 0) {
                stringList2[index2] = (char *) malloc(strlen(currentCRDH->Day) + 1);
                //charList2[index] = curr2->Day;
                strcpy(stringList2[index2], currentCRDH->Day);
                index2++;
            } else if (strcmp(type2, "Hour") == 0) {
                stringList2[index2] = (char *) malloc(strlen(currentCRDH->Hour) + 1);
                //charList2[index] = curr2->Hour;
                strcpy(stringList2[index2], currentCRDH->Hour);
                index2++;
            }
            currentCRDH = currentCRDH->nextCRDH;
        }
    }
    printf("Day\tHour\n");
    for (int j = 0; j < buckedSize; j++) {
        printf("%s\t%s\n", stringList1[j], stringList2[j]);
        free(stringList1[j]);
        free(stringList2[j]);
    }
    free(stringList1);
    free(stringList2);
}

CRDHList *selection_CRDH(CRDHList *CRDHHash, char *Room) {
    CRDHList *newList = newCRDHList();
    for (int i = 0; i < tableSize; i++) {
        CRDH *viewCRDH = CRDHHash->lists[i];
        while (viewCRDH != NULL) {
            if (strcmp(viewCRDH->Room, Room) == 0) {
                insert_CRDH(newList, viewCRDH->Course, viewCRDH->Room, viewCRDH->Day, viewCRDH->Hour);
            }
            viewCRDH = viewCRDH->nextCRDH;
        }
    }
    return newList;
}

void allOperation(CRList *CRHash, CDHList *CDHHash, char *Room, char *type1, char *type2) {
    CRDHList *CRDHHash = joinCRDH(CRHash, CDHHash);
    CRDHList *newCRDH = selection_CRDH(CRDHHash, Room);
    projection_CRDH(newCRDH, type1, type2);

    //free space used
    for (int i = 0; i < tableSize; i++) {
        if (CRDHHash->lists[i] != NULL) {
            freeCRDH(CRDHHash->lists[i]);
        } else {
            free(CRDHHash->lists[i]);
        }
        if (newCRDH->lists[i] != NULL) {
            freeCRDH(newCRDH->lists[i]);
        } else {
            free(newCRDH->lists[i]);
        }
    }
    free(CRDHHash);
    free(newCRDH);
}

void freeCRDH(CRDH *crdh) {
    if (crdh->nextCRDH == NULL) {
        free(crdh);
        return;
    } else {
        freeCRDH(crdh->nextCRDH);
        crdh->nextCRDH = NULL;
        free(crdh);
    }
}


