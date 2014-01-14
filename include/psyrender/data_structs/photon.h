
#ifndef _PSY_PHOTON_H
#define _PSY_PHOTON_H

typedef struct {
    Ray ray;
    Color color;
} Photon;

// Make PhotonList type
PTRLIST_MAKE_HEADER(PhotonList, Photon)

#endif
