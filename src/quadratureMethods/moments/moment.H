/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2012 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
2015-03-09 Alberto Passalacqua: Templated class on the type of field used to
                                store the moment and on the type of quadrature
                                node.
2015-05-23 Alberto Passalacqua: Added IOobject::groupname for improved naming
                                of files associated to moments.
2015-05-24 Alberto Passalacqua: Generalized moment update function to deal with
                                standard and extended nodes.
2015-06-13 Alberto Passalacqua: Introduced autoPtr to the PtrList of nodes to
                                improve initialization of nodes.
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
    Foam::moment

Description
    Stores a moment of a distribution function with arbitrary dimensionality.

SourceFiles
    momentI.H
    moment.C

\*---------------------------------------------------------------------------*/

#ifndef moment_H
#define moment_H

#include "PtrList.H"
#include "quadratureNodes.H"
#include "volFields.H"
#include "labelList.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class moment Declaration
\*---------------------------------------------------------------------------*/

template <class fieldType, class nodeType> 
class moment
:
    public fieldType
{
    //- Reference to the quadrature nodes
    const autoPtr<PtrList<nodeType> >& nodes_;

    //- The order of each dimension of the moment
    const labelList cmptOrders_;

    //- The name of the moment
    const word name_;

    //- The number of dimensions of the distribution function
    const label nDimensions_;

    //- The overall order of the moment
    const label order_;


public:

    //- Convert a list of labels to a word. {1, 2, 3} -> 123
    static word listToWord(const labelList& lst);

    //- Convert a list of labels to a single label. {0, 2, 3} -> 23
    static label listToLabel(const labelList& lst);


    // Constructors

        //- Construct from a list of orders of each dimension of the moment
        //  and the quadrature nodes
        moment
        (
            const labelList& cmptOrders,
            const fvMesh& mesh,
            const autoPtr<PtrList<nodeType> >& nodes
        );
        
        //- Construct from name, orders, and quadrature nodes
        moment
        (
            const labelList& cmptOrders,
            const autoPtr<PtrList<nodeType> >& nodes,
            const fieldType& initMoment
        );

        //- Return clone
        autoPtr<moment> clone() const;


        //- Return a pointer to a new moment created on freestore
        //  from Istream
        class iNew
        {
            const fvMesh& mesh_;
            const autoPtr<PtrList<nodeType> >& nodes_;

        public:

            iNew
            (
                const fvMesh& mesh,
                const autoPtr<PtrList<nodeType> >& nodes
            )
            :
                mesh_(mesh),
                nodes_(nodes)
            {}

            autoPtr<moment<fieldType, nodeType> > operator()(Istream& is) const
            {
                labelList ent(is);
                return autoPtr<moment<fieldType, nodeType> >
                (
                    new moment<fieldType, nodeType> (ent, mesh_, nodes_)
                );
            }
        };


    //- Destructor
    ~moment();


    // Member Functions

        // Access

            //- Return the name of the moment
            inline const word& name() const;

            //- Return the name of the moment
            inline const word& keyword() const;

            //- Return the dimensionality of the distribution
            inline label nDimensions() const;

            //- Return the overall order of the moment
            inline label order() const;

            //- Return the order of each dimension
            inline const labelList& cmptOrders() const;


        // Edit

            //- Update the moment from the quadrature nodes
            void update();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "momentI.H"
#   include "moment.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
