#include "Part2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*


 * */
void GradeStudentCourse(SNAPList *SNAPHash, CSGList *CSGHash, char *studentName, char *course) {
    //(1) for each tuple t in StudentId-Name-Address-Phone do
    for (int i = 0; i < 50; i++){
        if (SNAPHash->lists[i] != NULL){
            SNAP *viewSNAP = SNAPHash->lists[i];
            while (viewSNAP != NULL){
                //(2) if t has “C. Brown” in its Name component then begin
                if (strcmp(viewSNAP->Name, studentName) == 0){
                    //(3) let i be the StudentId component of tuple t;
                    int viewId = viewSNAP->StudentId;

                    //(4) for each tuple s in Course-StudentId-Grade do
                    for(int j = 0; j < 50; j++){
                        if(CSGHash->lists[j] != NULL){
                            CSG *viewCSG = CSGHash->lists[j];
                            while (viewCSG != NULL){
                                //(5) if s has Course component “CS101” and StudentId component i then
                                if (strcmp(viewCSG->Course, course) == 0 && viewCSG->StudentId == viewId) {
                                    //(6) print the Grade component of tuple s;
                                    printf("Grade is: %s\n", viewCSG->Grade);
                                    return;
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

void StudentHourDay(SNAPList *SNAPHash, CSGList *CSGHash, CDHList *CDHHash, CRList *CRHash, char *studentName, char *day, char *hour) {

}