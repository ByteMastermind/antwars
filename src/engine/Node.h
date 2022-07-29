//
// Created by michal on 26.5.22.
//

#ifndef BENESM41_NODE_H
#define BENESM41_NODE_H

#include "MatrixCoordinates.h"

/**
 * Used for BFS - hold current coordinates and previous coordinates
 */
struct Node {
    MatrixCoordinates previous;
    bool visited = false;

    explicit Node(const MatrixCoordinates &previous) : previous(previous) {}
};


#endif //BENESM41_NODE_H
