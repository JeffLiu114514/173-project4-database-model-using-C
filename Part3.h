#ifndef INC_173_PROJ4_PART3_H
#define INC_173_PROJ4_PART3_H
typedef struct CRDH CRDH;
typedef struct CRDHList CRDHList;
struct CRDH {
    char *Course;
    char *Room;
    char *Day;
    char *Hour;
    CRDH *nextCRDH;
};

struct CRDHList {
    CRDH **lists;
};

CSGList *selection_CSG(CSGList *CSGHash, int id);

void projection_CSG(CSGList *CSGHash, char *type);

void printCRDH(CRDHList *table);

CRDHList *joinCRDH(CRList *CRHash, CDHList *CDHHash);

void projection_CRDH(CRDHList *CRDHHash, char *type, char *type2);

CRDHList *selection_CRDH(CRDHList *CRDHHash, char *Room);

#endif //INC_173_PROJ4_PART3_H
