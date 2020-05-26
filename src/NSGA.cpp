//
//  NSGA.cpp
//  TiMO_Projekt
//
//  Created by Michal_Nowak & Kacper_Stenka on 08/03/2020.
//  Copyright © 2020 Michal_Nowak & Kacper_Stenka. All rights reserved.
//

#include "NSGA.hpp"

// --------------------------------------------------------------------

NSGA::NSGA() {

}

// --------------------------------------------------------------------

NSGA::~NSGA() {

}

// --------------------------------------------------------------------

void NSGA::initPopulation(Allele P0, double niche) {

    this->Niche_Radius = niche;
    P0.Population_Adaptation_Update();

    NSGA_P0.Population_Clear();
    NSGA_Pt.Population_Clear();

    NSGA_P0 = P0;
    NSGA_Pt = P0;

    NSGA_Populations_List.clear();
    NSGA_Populations_List.push_back( P0 );
}

// --------------------------------------------------------------------

double NSGA::NSGA_Split_Function(double alpha, double q_share, Individual ii, Individual jj) {

    double d_ij = 0;
    double sd_ij = 0;

    // Step 1:
    for(int i = 0; i < ii.Goals_Size; ++i) {

        d_ij += pow( ( jj.Goals[i] - ii.Goals[i] ), 2);
    }

    d_ij = sqrt( d_ij );

    // Step 2:
    if( d_ij < q_share ) {

        sd_ij = 1 - pow( (d_ij / q_share), alpha);
    }
    else {

        sd_ij = 0;
    }

    return sd_ij;
}

// --------------------------------------------------------------------

void NSGA::NSGA_Fitness_Scharing(Allele *p, double Fd) {

    for(int i = 0; i < p->Population_Get_Size(); ++i) {

        Individual I_Temp = p->Population_Get_Individual(i);

        double Distance_Sum = 0;

        for(int j = 0; j < p->Population_Get_Size(); ++j) {

            Individual J_Temp = p->Population_Get_Individual(j);

            if( i != j ) {

                Distance_Sum += NSGA_Split_Function(1, Niche_Radius, I_Temp, J_Temp);
            }
        }

        double Fitness = Distance_Sum != 0 ? (Fd / Distance_Sum) : Fd;

        p->Population_Set_Fitness(Fitness, i);
    }
}

// --------------------------------------------------------------------

Allele NSGA::NSGA_NonDominated_Sorting(Allele P) {

    Allele P_sorted = P;
    P_sorted.Population_Clear();

    Allele P_remain = P;
    Allele P_nondom = P;
    double Fd = P.Population_Get_Size();

    P_remain.Population_Adaptation_Update();

    while( P_remain.Population_Get_Size() != 0 ) {

        P_nondom = P_remain.Population_Delete_Return_NonDom();

        if( P_nondom.Population_Get_Size() == 0 ) {

            P_nondom = P_remain;
            P_remain.Population_Clear();
        }

        NSGA_Fitness_Scharing(&P_nondom, Fd);

        Fd = 0.9 * P_nondom.Population_Get_Min_Fitness();

        for(int i = 0; i < P_nondom.Population_Get_Size(); ++i) {

            P_sorted.Population_Set_Individual( P_nondom.Population_Get_Individual(i) );
        }

    }
    return P_sorted;
}

// --------------------------------------------------------------------

void NSGA::NSGA_Algorithm() {

    // Step 1: Crossing and Mutation
    NSGA_Pt = NSGA_Pt.Population_Recombination();

    // Step 2: Adaptation
    NSGA_Pt = NSGA_NonDominated_Sorting(NSGA_Pt);

    // Step 3: Selection
    NSGA_Pt = NSGA_Pt.Selection(5);

    NSGA_Populations_List.push_back( NSGA_Pt );
}

// --------------------------------------------------------------------

vector<Allele> NSGA::NSGA_Get_Population_List() {

    return NSGA_Populations_List;
}

// --------------------------------------------------------------------

Allele NSGA::NSGA_Get_Actual_Population() {

    return NSGA_Pt;
}

// --------------------------------------------------------------------

Allele NSGA::NSGA_Get_NonDom() {

    Allele P_Temp1 = NSGA_Pt;

    P_Temp1.Population_Adaptation_Update();

    Allele P_Temp2 = P_Temp1.Population_Delete_Return_NonDom();

    return P_Temp2;
}

// --------------------------------------------------------------------

Allele NSGA::NSGA_Get_Dom() {

    Allele P_Temp = NSGA_Pt;

    P_Temp.Population_Adaptation_Update();

    P_Temp.Population_Delete_Return_NonDom();

    return P_Temp;
}

// --------------------------------------------------------------------
