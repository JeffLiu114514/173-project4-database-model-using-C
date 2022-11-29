#include "Part1.h"
#include "Part3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CSGList *selection_CSG(CSGList *CSGHash, int id) {
    CSGList *newList = new_CSGList();
    for (int i = 0; i < 50; i++) {
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
    int hashCount = 0;
    for (int i = 0; i < 50; i++) {
        CSG *view = CSGHash->lists[i];
        while (view != NULL) {
            hashCount ++;
            view = view->nextCSG;
        }
    }
    char **charList = (char **) malloc(sizeof(char *) * hashCount);
    int *intList = (int *) malloc(sizeof(int) * hashCount);
    int index = 0;
    for (int i = 0; i < 50; i++) {
        CSG *viewCSG = CSGHash->lists[i];
        while (viewCSG != NULL) {
            if (strcmp(type, "Course") == 0) {
                charList[index] = (char *) malloc(strlen(viewCSG->Course) + 1);
                strcpy(charList[index], viewCSG->Course);
                index++;
            } else if (strcmp(type, "StudentId") == 0) {
                intList[index] = viewCSG->StudentId;
                index++;
            } else if (strcmp(type, "Grade") == 0) {
                charList[index] = (char *) malloc(strlen(viewCSG->Course) + 1);
                strcpy(charList[index], viewCSG->Grade);
                index++;
            }
            viewCSG = viewCSG->nextCSG;
        }
    }

    if (strcmp(type, "Grade") == 0 || strcmp(type, "Course") == 0) {
        for (int j = 0; j < hashCount; j++) {
            printf("%s\n", charList[j]);
        }
        for (int k = 0; k < hashCount; k++) {
            free(charList[k]);
        }
    } else {
        printf("student ID\n");
        for (int l = 0; l < hashCount; l++) {
            printf("%d\n", intList[l]);
        }
    }
    free(charList);
    free(intList);
}

CRDHList *newCRDHList() {
    struct CRDHList *Hashtable = (CRDHList *) malloc(sizeof(CRDHList));
    Hashtable->lists = (CRDH **) malloc(sizeof(CRDH) * 50);
    for (int i = 0; i < 50; i++) {
        Hashtable->lists[i] = NULL;
    }
    return Hashtable;
}

CRDH *newCRDH(char *Course, char *Room, char *Day, char *Hour) {
    struct CRDH *output = (CRDH *) malloc(sizeof(CRDH));
    output->Course = (char *) malloc(strlen(Course) + 1);
    output->Room = (char *) malloc(strlen(Room) + 1);
    output->Day = (char *) malloc(strlen(Day) + 1);
    output->Hour = (char *) malloc(strlen(Hour) + 1);

    output->Course = Course;
    output->Room = Room;
    output->Day = Day;
    output->Hour = Hour;

    /*strcpy(output->Course, Course);
    strcpy(output->Room, Room);
    strcpy(output->Day, Day);
    strcpy(output->Hour, Hour);*/

    output->nextCRDH = NULL;
    return output;
}

void insert_CRDH(CRDHList *CRDHHash, char *Course, char *room, char *Day, char *Hour) {
    int slot = hashString(Course);
    CRDH *CRDHCurr = CRDHHash->lists[slot];
    if (CRDHCurr == NULL) {
        CRDHHash->lists[slot] = newCRDH(Course, room, Day, Hour);
        return;
    }
    CRDH *prev = CRDHCurr;
    while (CRDHCurr != NULL) {
        prev = CRDHCurr;
        CRDHCurr = CRDHCurr->nextCRDH;
    }
    prev->nextCRDH = newCRDH(Course, room, Day, Hour);
}

void printCRDH(CRDHList *table) {
    printf("COURSE\tROOM\t\tDAY\tHOUR\n");
    for (int i = 0; i < 50; i++) {
        if (table->lists[i] != NULL) {
            CRDH *curr = table->lists[i];
            while (curr != NULL) {
                printf("%s\t%s\t%s\t%s\n", curr->Course, curr->Room, curr->Day, curr->Hour);
                curr = curr->nextCRDH;
            }
        }
    }
}

CRDHList *joinCRDH(CRList *CRHash, CDHList *CDHHash) {
    CRDHList *output = newCRDHList();
    for (int i = 0; i < 50; i++) {
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

void projection_CRDH(CRDHList *CRDHHash, char *type, char *type2) {
    int size1 = 0;
    for (int i = 0; i < 50; i++) {
        CRDH *curr = CRDHHash->lists[i];
        while (curr != NULL) {
            size1 += 1;
            curr = curr->nextCRDH;
        }
    }
    char **charList = (char **) malloc(sizeof(char *) * size1);
    char **charList2 = (char **) malloc(sizeof(char *) * size1);
    int index = 0;
    for (int k = 0; k < 50; k++) {
        CRDH *curr1 = CRDHHash->lists[k];
        while (curr1 != NULL) {
            if (strcmp(type, "Course") == 0) {
                charList[index] = (char *) malloc(strlen(curr1->Course) + 1);
                //charList[index] = curr1->Course;
                strcpy(charList[index], curr1->Course);
                index++;
            } else if (strcmp(type, "Room") == 0) {
                charList[index] = (char *) malloc(strlen(curr1->Room) + 1);
                //charList[index] = curr1->Room;
                strcpy(charList[index], curr1->Room);
                index++;
            } else if (strcmp(type, "Day") == 0) {
                charList[index] = (char *) malloc(strlen(curr1->Day) + 1);
                //charList[index] = curr1->Day;
                strcpy(charList[index], curr1->Day);
                index++;
            } else if (strcmp(type, "Hour") == 0) {
                charList[index] = (char *) malloc(strlen(curr1->Hour) + 1);
                //charList[index] = curr1->Hour;
                strcpy(charList[index], curr1->Hour);
                index++;
            }
            curr1 = curr1->nextCRDH;
        }
    }
    int index2 = 0;
    for (int k = 0; k < 50; k++) {
        CRDH *curr2 = CRDHHash->lists[k];
        while (curr2 != NULL) {
            if (strcmp(type2, "Course") == 0) {
                charList2[index2] = (char *) malloc(strlen(curr2->Course) + 1);
                //charList2[index] = curr2->Course;
                strcpy(charList2[index2], curr2->Course);
                index2++;
            } else if (strcmp(type2, "Room") == 0) {
                charList2[index2] = (char *) malloc(strlen(curr2->Room) + 1);
                //charList2[index] = curr2->Room;
                strcpy(charList2[index2], curr2->Room);
                index2++;
            } else if (strcmp(type2, "Day") == 0) {
                charList2[index2] = (char *) malloc(strlen(curr2->Day) + 1);
                //charList2[index] = curr2->Day;
                strcpy(charList2[index2], curr2->Day);
                index2++;
            } else if (strcmp(type2, "Hour") == 0) {
                charList2[index2] = (char *) malloc(strlen(curr2->Hour) + 1);
                //charList2[index] = curr2->Hour;
                strcpy(charList2[index2], curr2->Hour);
                index2++;
            }
            curr2 = curr2->nextCRDH;
        }
    }
    printf("Day\tHour\n");
    for (int j = 0; j < size1; j++) {
        printf("%s\t%s\n", charList[j], charList2[j]);
        free(charList[j]);
        free(charList2[j]);
    }

    free(charList);
    free(charList2);
}

CRDHList *selection_CRDH(CRDHList *CRDHHash, char *Room) {
    CRDHList *newList = newCRDHList();
    for (int i = 0; i < 50; i++) {
        CRDH *curr = CRDHHash->lists[i];
        while (curr != NULL) {
            if (strcmp(curr->Room, Room) == 0) {
                insert_CRDH(newList, curr->Course, curr->Room, curr->Day, curr->Hour);
            }
            curr = curr->nextCRDH;
        }
    }
    return newList;
}

void jointOperation(CRList *CRHash, CDHList *CDHHash, char *Room, char *type1, char *type2) {
    CRDHList *CRDHHash = joinCRDH(CRHash, CDHHash);
    CRDHList *CRDHNew = selection_CRDH(CRDHHash, Room);
    projection_CRDH(CRDHNew, type1, type2);

    for (int i = 0; i < 50; i++) {
        if (CRDHHash->lists[i] != NULL) {
            freeCRDH(CRDHHash->lists[i]);
        } else {
            free(CRDHHash->lists[i]);
        }

        if (CRDHNew->lists[i] != NULL) {
            freeCRDH(CRDHNew->lists[i]);
        } else {
            free(CRDHNew->lists[i]);
        }
    }
    free(CRDHHash);
    free(CRDHNew);
}

void freeCRDH(CRDH *CRDHi) {
    if (CRDHi->nextCRDH == NULL) {
        free(CRDHi);
        return;
    } else {
        freeCRDH(CRDHi->nextCRDH);
        CRDHi->nextCRDH = NULL;
        free(CRDHi);
    }
}

