#include "Part2.h"
#include "Part1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getGradeByStudentCourse(SNAPList *SNAPHash, CSGList *CSGHash, char *studentName, char *course) {
    //(1) for each tuple t in StudentId-Name-Address-Phone do
    for (int i = 0; i < tableSize; i++){
        if (SNAPHash->lists[i] != NULL){
            SNAP *viewSNAP = SNAPHash->lists[i];
            while (viewSNAP != NULL){
                //(2) if t has “C. Brown” in its Name component then begin
                if (strcmp(viewSNAP->Name, studentName) == 0){
                    //(3) let i be the StudentId component of tuple t;
                    int viewId = viewSNAP->StudentId;

                    //(4) for each tuple s in Course-StudentId-Grade do
                    for(int j = 0; j < tableSize; j++){
                        if(CSGHash->lists[j] != NULL){
                            CSG *viewCSG = CSGHash->lists[j];
                            while (viewCSG != NULL){
                                //(5) if s has Course component “CS101” and StudentId component i then
                                if (strcmp(viewCSG->Course, course) == 0 && viewCSG->StudentId == viewId) {
                                    //(6) print the Grade component of tuple s;
                                    printf("Grade is: %s\n", viewCSG->Grade);
                                    break;
                                }
                                viewCSG = viewCSG->nextCSG;
                            }
                        }
                    }
                }
                viewSNAP = viewSNAP->nextSNAP;
            }
        }
    }
}

void getRoomByStudentHourDay(SNAPList *SNAPHash, CSGList *CSGHash, CDHList *CDHHash, CRList *CRHash, char *studentName, char *day, char *hour) {
    //Traverse SNAP Hashtable
    for (int i = 0; i < tableSize; i++) {
        if (SNAPHash->lists[i] != NULL) {
            SNAP *viewSNAP = SNAPHash->lists[i];
            while (viewSNAP != NULL) {
                //Found the name! So found the StudentId
                if (strcmp(viewSNAP->Name, studentName) == 0) {
                    int viewId = viewSNAP->StudentId;

                    //Traverse CSG Hashtable
                    for (int j = 0; j < tableSize; j++) {
                        if (CSGHash->lists[j] != NULL) {
                            CSG *viewCSG = CSGHash->lists[j];
                            while (viewCSG != NULL) {
                                if(viewCSG->StudentId == viewId){
                                    char *courseName = viewCSG->Course;

                                    //Traverse CDH Hashtable
                                    for (int k = 0; k < tableSize; k++) {
                                        if(CDHHash->lists[k] != NULL){
                                            CDH *viewCDH = CDHHash->lists[k];
                                            while (viewCDH != NULL) {
                                                //We have found the one matches all the course, day, & hour!
                                                if (strcmp(viewCDH->Course, courseName) == 0 &&
                                                    strcmp(viewCDH->Day, day) == 0 && strcmp(viewCDH->Hour, hour) == 0) {
                                                    lookup_CR(CRHash, courseName, "*");
                                                    //break;
                                                }
                                                viewCDH = viewCDH->nextCDH;
                                            }
                                        }
                                    }
                                }
                                viewCSG = viewCSG->nextCSG;
                            }
                        }
                    }
                }
                viewSNAP = viewSNAP->nextSNAP;
            }
        }
    }
}