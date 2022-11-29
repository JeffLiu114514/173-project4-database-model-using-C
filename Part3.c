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

    output->nextCRDH = NULL;
    return output;
}

void insert_CRDH(CRDHList *CRDHHash, char *Course, char *room, char *Day, char *Hour) {
    int index = hashString(Course);
    CRDH *viewCRDH = CRDHHash->lists[index];
    if (viewCRDH == NULL) {
        CRDHHash->lists[index] = newCRDH(Course, room, Day, Hour);
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
    printf("COURSE\tROOM\t\tDAY\tHOUR\n");
    for (int i = 0; i < 50; i++) {
        if (table->lists[i] != NULL) {
            CRDH *viewCRDH = table->lists[i];
            while (viewCRDH != NULL) {
                printf("%s\t%s\t%s\t%s\n", viewCRDH->Course, viewCRDH->Room, viewCRDH->Day, viewCRDH->Hour);
                viewCRDH = viewCRDH->nextCRDH;
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

}

CRDHList *selection_CRDH(CRDHList *CRDHHash, char *Room) {
    CRDHList *newList = newCRDHList();
    for (int i = 0; i < 50; i++) {
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


