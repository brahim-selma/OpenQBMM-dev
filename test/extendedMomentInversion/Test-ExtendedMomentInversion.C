/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2014-2015 Alberto Passalacqua
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is derivative work of OpenFOAM.

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

Application
    Test-ExtendedMomentInversion.C

Description
    Test the extendedMomentInversion class and its subclasses.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "IFstream.H"
#include "OFstream.H"
#include "scalarMatrices.H"
#include "univariateMomentSet.H"
#include "extendedMomentInversion.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "createFields.H"

    Info << "Testing extendedMomentInversion\n" << endl;

    label nMoments = 5;
    univariateMomentSet moments(nMoments, 0.0);

//  Valid moment set
   moments[0] = 1.0;
   moments[1] = 2.708217669;
   moments[2] = 8.951330468;
   moments[3] = 35.95258119;
   moments[4] = 174.4370267;
    
//  Unrealizable moment star
//     moments[0] = 0.567128698550116;
//     moments[1] = 0.659798044636756;
//     moments[2] = 0.796168501018439;
//     moments[3] = 1.0;
//     moments[4] = 1.3103698092;

//  Set of moment with sigma = 0 as root
//     moments[0] = 1.0;
//     moments[1] = 1.6487212707;
//     moments[2] = 2.7182818285;
//     moments[3] = 4.4816890703;
//     moments[4] = 7.3890560989;

// Set of moments with multiple roots not bracketed by sigmaMax
//     moments[0] = 1.0;
//     moments[1] = 1.055795897;
//     moments[2] = 1.247672408;
//     moments[3] = 1.670093417;
//     moments[4] = 2.578636894;
//     moments[5] = 4.688985807;
//     moments[6] = 10.22526492;
//     moments[7] = 27.0370458224;
//     moments[8] = 86.9534420717;
    
    autoPtr<extendedMomentInversion> EQMOM
    (
        extendedMomentInversion::New
        (
            quadratureProperties, 
            moments
        )
    );

    Info << "\nInverting moments.\n" << endl;

    EQMOM->invert();

    Info << "Sigma = " << EQMOM->sigma() << endl;

    Info << "\nExtracting secondary quadrature." << endl;

    EQMOM->secondaryQuadrature();

    Info << "\nRecovering secondary weights and abscissae." << endl;

    scalarDiagonalMatrix pWeights(EQMOM->primaryWeights());
    scalarDiagonalMatrix pAbscissae(EQMOM->primaryAbscissae());

    scalarRectangularMatrix sWeights(EQMOM->secondaryWeights());
    scalarRectangularMatrix sAbscissae(EQMOM->secondaryAbscissae());

    Info << "\nStoring quadrature." << endl;
    
    OFstream outputFile("./secondaryQuadrature");

    label nPrimaryNodes = EQMOM->nPrimaryNodes();
    label nSecondaryNodes = EQMOM->nSecondaryNodes();
    
    for (label pNodeI = 0; pNodeI < nPrimaryNodes; pNodeI++)
    {
        outputFile << "Primary node " << pNodeI
            << "\nPrimary weight = " << pWeights[pNodeI]
            << "\nPrimary abscissa = " << pAbscissae[pNodeI] << endl;

        outputFile << "\nSecondary nodes" << endl;

        for (label sNodeI = 0; sNodeI < nSecondaryNodes; sNodeI++)
        {
            outputFile << sWeights[pNodeI][sNodeI] << ", " 
                << sAbscissae[pNodeI][sNodeI] << endl;
        }

        outputFile << "\n\n";
    }

    Info << "\nEnd\n" << endl;

    return 0;
}


// ************************************************************************* //