//
//  NSGA.hpp
//  TiMO_Projekt
//
//  Created by Michal on 08/03/2020.
//  Copyright © 2020 Michal_Nowak & Kacper_Stenka. All rights reserved.
//

#ifndef NSGA_hpp
#define NSGA_hpp

#include <stdio.h>
#include "allele.hpp"

using namespace std;

// --------------------------------------------------------------------

class NSGA {

private:

    vector<Allele> NSGA_Populations_List;

    Allele NSGA_P0;
    Allele NSGA_Pt;

    double NSGA_Split_Function(double alpha, double q_share, Individual ii, Individual jj);
    void NSGA_Fitness_Scharing(Allele *p, double Fd);
    Allele NSGA_NonDominated_Sorting(Allele P);

    double Niche_Radius;

protected:

public:

    NSGA();
    ~NSGA();

    void initPopulation(Allele P0, double);

    void NSGA_Algorithm();

    vector<Allele> NSGA_Get_Population_List();
    Allele NSGA_Get_Actual_Population();
    Allele NSGA_Get_NonDom();
    Allele NSGA_Get_Dom();
};

// --------------------------------------------------------------------


#endif /* NSGA_hpp */
