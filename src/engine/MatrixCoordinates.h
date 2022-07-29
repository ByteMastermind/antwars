//
// Created by michal on 26.5.22.
//

#ifndef BENESM41_MATRIXCOORDINATES_H
#define BENESM41_MATRIXCOORDINATES_H

/**
 * Coordinates of the matrix. Different than rendering coordinates (swapped and matrix coordinates are block)
 */
struct MatrixCoordinates {
    int row;                  /*!< row coordinate (of the block) */
    int col;                  /*!< column coordinate (of the block) */

    MatrixCoordinates(int row, int col) : row(row), col(col) {}

    bool operator==(const MatrixCoordinates &rhs) const {
        return row == rhs.row &&
               col == rhs.col;
    }

    bool operator!=(const MatrixCoordinates &rhs) const {
        return !(rhs == *this);
    }
};


#endif //BENESM41_MATRIXCOORDINATES_H
