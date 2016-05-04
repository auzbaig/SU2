/*!
 * transport_model.cpp
 * \brief Source of the main transport properties subroutines of the SU2 solvers.
 * \author S. Vitale, M. Pini, G. Gori, A. Guardone, P. Colonna
 * \version 4.1.2 "Cardinal"
 *
 * SU2 Lead Developers: Dr. Francisco Palacios (Francisco.D.Palacios@boeing.com).
 *                      Dr. Thomas D. Economon (economon@stanford.edu).
 *
 * SU2 Developers: Prof. Juan J. Alonso's group at Stanford University.
 *                 Prof. Piero Colonna's group at Delft University of Technology.
 *                 Prof. Nicolas R. Gauger's group at Kaiserslautern University of Technology.
 *                 Prof. Alberto Guardone's group at Polytechnic University of Milan.
 *                 Prof. Rafael Palacios' group at Imperial College London.
 *
 * Copyright (C) 2012-2016 SU2, the open-source CFD code.
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#include "../include/transport_model.hpp"

#ifdef HAVE_FluidProp
#include "fluidprop.h"
#endif

/*-------------------------------------------------*/
/*----------- Dynamic Viscosity Models ------------*/
/*-------------------------------------------------*/

CViscosityModel::CViscosityModel(void) {

  /*--- Attributes initialization ---*/

	Mu = 0.0;
	dmudrho_T = 0.0;
	dmudT_rho = 0.0;

}

CViscosityModel::~CViscosityModel(void) { }


CConstantViscosity::CConstantViscosity(void) : CViscosityModel() { }

CConstantViscosity::CConstantViscosity(su2double mu_const) : CViscosityModel() {

  /*--- Attributes initialization ---*/

	Mu = mu_const;
	dmudrho_T = 0.0;
	dmudT_rho = 0.0;

}

CConstantViscosity::~CConstantViscosity(void) { }




CSutherland::CSutherland(void) : CViscosityModel() {
	Mu_ref = 0.0;
	T_ref = 0.0;
	S = 0.0;

}

CSutherland::CSutherland(su2double mu_ref, su2double t_ref, su2double s) : CViscosityModel() {

	Mu_ref = mu_ref;
	T_ref = t_ref;
	S = s;
}

CSutherland::~CSutherland(void) { }


void CSutherland::SetViscosity(su2double T, su2double rho) {

	Mu = Mu_ref*pow((T/T_ref),(3.0/2.0))*((T_ref + S)/(T + S));

}

void CSutherland::SetDerViscosity(su2double T, su2double rho) {

	dmudrho_T = 0.0;
	dmudT_rho = Mu_ref*( (3.0/2.0)*pow( (T/T_ref),(1.0/2.0) )*( (T_ref + S)/(T + S) )
			    -pow( (T/T_ref),(3.0/2.0) )*(T_ref + S)/(T + S)/(T + S) );

}



CFluidPropViscosity::CFluidPropViscosity(void) : CViscosityModel() {

}

CFluidPropViscosity::~CFluidPropViscosity(void) { }


void CFluidPropViscosity::SetViscosity(su2double T, su2double rho) {

        su2double deta_dT, deta_drho, lambda, dlambda_dT, dlambda_drho, sigma; 
        fluidprop_alltransprops( "Td", T, rho, &Mu, &deta_dT, &deta_drho, &lambda, &dlambda_dT, &dlambda_drho, &sigma); 

        if (strcmp( fluidprop_geterror(), "No errors")) {
           printf( "FluidProp error message: %s\n", fluidprop_geterror());
	   printf( "T = %f, rho = %f, mu = %f\n", T, rho, Mu);
        }
}

void CFluidPropViscosity::SetDerViscosity(su2double T, su2double rho)  {

        su2double eta, lambda, dlambda_dT, dlambda_drho, sigma; 
        fluidprop_alltransprops( "Td", T, rho, &eta, &dmudT_rho, &dmudrho_T, &lambda, &dlambda_dT, &dlambda_drho, &sigma); 

        if (strcmp( fluidprop_geterror(), "No errors")) {
           printf( "FluidProp error message: %s\n", fluidprop_geterror());
	   printf( "T = %f, rho = %f, dmudT_rho = %f, dmudrho_dT = %f\n", T, rho, dmudT_rho, dmudT_rho);
        }
}
/*-------------------------------------------------*/
/*---------- Thermal Conductivity Models ----------*/
/*-------------------------------------------------*/

CConductivityModel::CConductivityModel(void) {

  /*--- Attributes initialization ---*/

	Kt = 0.0;
	dktdrho_T = 0.0;
	dktdT_rho = 0.0;

}

CConductivityModel::~CConductivityModel(void) { }


CConstantConductivity::CConstantConductivity(void) : CConductivityModel() { }

CConstantConductivity::CConstantConductivity(su2double kt_const) : CConductivityModel() {

  /*--- Attributes initialization ---*/

	Kt = kt_const;
	dktdrho_T = 0.0;
	dktdT_rho = 0.0;

}

CConstantConductivity::~CConstantConductivity(void) { }


CConstantPrandtl::CConstantPrandtl(void) : CConductivityModel() { }

CConstantPrandtl::CConstantPrandtl(su2double pr_const) : CConductivityModel() {

  /*--- Attributes initialization ---*/

	Pr_const = pr_const;

}

void CConstantPrandtl::SetConductivity(su2double T, su2double rho, su2double mu, su2double cp) {

	Kt = mu*cp/Pr_const;

}

void CConstantPrandtl::SetDerConductivity(su2double T, su2double rho, su2double dmudrho_T, su2double dmudT_rho, su2double cp) {

	dktdrho_T = dmudrho_T*cp/Pr_const;
	dktdT_rho = dmudT_rho*cp/Pr_const;

}

CConstantPrandtl::~CConstantPrandtl(void) { }




CFluidPropConductivity::CFluidPropConductivity(void) : CConductivityModel() { }

CFluidPropConductivity::CFluidPropConductivity(su2double pr_const) : CConductivityModel() {

  /*--- Attributes initialization ---*/

	Pr_const = pr_const;

}

void CFluidPropConductivity::SetConductivity(su2double T, su2double rho, su2double mu, su2double cp) {

        su2double eta, deta_dT, deta_drho, dlambda_dT, dlambda_drho, sigma; 
        fluidprop_alltransprops( "Td", T, rho, &eta, &deta_dT, &deta_drho, &Kt, &dlambda_dT, &dlambda_drho, &sigma); 

        if (strcmp( fluidprop_geterror(), "No errors")) {
           printf( "FluidProp error message: %s\n", fluidprop_geterror());
	   printf( "T = %f, rho = %f, Kt = %f\n", T, rho, Kt);
        }
}

void CFluidPropConductivity::SetDerConductivity(su2double T, su2double rho, su2double dmudrho_T, su2double dmudT_rho, su2double cp) {

        su2double eta, deta_dT, deta_drho, lambda, sigma; 
        fluidprop_alltransprops( "Td", T, rho, &eta, &deta_dT, &deta_drho, &lambda, &dktdT_rho, &dktdrho_T, &sigma); 

        if (strcmp( fluidprop_geterror(), "No errors")) {
           printf( "FluidProp error message: %s\n", fluidprop_geterror());
	   printf( "T = %f, rho = %f, dktdT_rho = %f, dktdrho_dT = %f\n", T, rho, dktdT_rho, dktdT_rho);
        }
}

CFluidPropConductivity::~CFluidPropConductivity(void) { }


