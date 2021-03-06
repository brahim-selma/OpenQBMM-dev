/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2015 Alberto Passalacqua
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

Class
    Foam::populationBalanceModels::diffusionModels::noDiffusion

Description
    Standard turbulent diffusion model. This model should be default for
    problems without size-dependent diffusion.

SourceFiles
    noDiffusion.C

\*---------------------------------------------------------------------------*/

#ifndef noDiffusion_H
#define noDiffusion_H

#include "diffusionModel.H"
#include "fvm.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace populationBalanceSubModels
{
namespace diffusionModels
{

/*---------------------------------------------------------------------------*\
                    Class noDiffusion Declaration
\*---------------------------------------------------------------------------*/

class noDiffusion
:
    public diffusionModel
{      
public:

        //- Runtime type information
        TypeName("none");


    // Constructors

        //- Construct from components
        noDiffusion(const dictionary& dict);


    //- Destructor
    virtual ~noDiffusion();


    // Member Functions

        //- Moments of the daughter distribution
        virtual tmp<fvScalarMatrix> momentDiff
        (
            const volScalarField& moment
        ) const;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace diffusionModels
} // End namespace populationBalanceSubModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
