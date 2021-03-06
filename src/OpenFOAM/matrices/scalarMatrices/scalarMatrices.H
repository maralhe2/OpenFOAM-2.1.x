/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    scalarMatrices

Description
    Scalar matrices

SourceFiles
    scalarMatrices.C
    scalarMatricesTemplates.C

\*---------------------------------------------------------------------------*/

#ifndef scalarMatrices_H
#define scalarMatrices_H

#include "RectangularMatrix.H"
#include "SquareMatrix.H"
#include "DiagonalMatrix.H"
#include "scalarField.H"
#include "labelList.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

typedef RectangularMatrix<scalar> scalarRectangularMatrix;
typedef SquareMatrix<scalar> scalarSquareMatrix;
typedef DiagonalMatrix<scalar> scalarDiagonalMatrix;

//- Solve the matrix using Gaussian elimination with pivoting,
//  returning the solution in the source
template<class Type>
void solve(scalarSquareMatrix& matrix, Field<Type>& source);

//- Solve the matrix using Gaussian elimination with pivoting
//  and return the solution
template<class Type>
void solve
(
    Field<Type>& psi,
    const scalarSquareMatrix& matrix,
    const Field<Type>& source
);

//- LU decompose the matrix with pivoting
void LUDecompose
(
    scalarSquareMatrix& matrix,
    labelList& pivotIndices
);

//- LU back-substitution with given source, returning the solution
//  in the source
template<class Type>
void LUBacksubstitute
(
    const scalarSquareMatrix& luMmatrix,
    const labelList& pivotIndices,
    Field<Type>& source
);

//- Solve the matrix using LU decomposition with pivoting
//  returning the LU form of the matrix and the solution in the source
template<class Type>
void LUsolve(scalarSquareMatrix& matrix, Field<Type>& source);

void multiply
(
    scalarRectangularMatrix& answer,         // value changed in return
    const scalarRectangularMatrix& A,
    const scalarRectangularMatrix& B
);

void multiply
(
    scalarRectangularMatrix& answer,         // value changed in return
    const scalarRectangularMatrix& A,
    const scalarRectangularMatrix& B,
    const scalarRectangularMatrix& C
);

void multiply
(
    scalarRectangularMatrix& answer,         // value changed in return
    const scalarRectangularMatrix& A,
    const DiagonalMatrix<scalar>& B,
    const scalarRectangularMatrix& C
);

//- Return the inverse of matrix A using SVD
scalarRectangularMatrix SVDinv
(
    const scalarRectangularMatrix& A,
    scalar minCondition = 0
);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "scalarMatricesTemplates.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
