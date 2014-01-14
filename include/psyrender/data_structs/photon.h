
#ifndef _PSY_PHOTON_H
#define _PSY_PHOTON_H

typedef struct {
    Ray ray;
    Color color;
} Photon;

// Make PhotonArray type
PTRARRAY_MAKE_HEADER(PhotonArray, Photon)

#endif
