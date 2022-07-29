//
// Created by michal on 27.5.22.
//

#ifndef BENESM41_USINGS_H
#define BENESM41_USINGS_H

#include <vector>
#include "MatrixCoordinates.h"

template<class T>
using Map = std::vector<std::vector<T>>;            /*!< Map n x n of type T */
using Path = std::vector<MatrixCoordinates>;        /*!< Sequence of coordinates showing shortest path from A to Be */

#endif //BENESM41_USINGS_H
