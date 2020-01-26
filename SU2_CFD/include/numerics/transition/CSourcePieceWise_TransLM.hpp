﻿/*!
 * \file CSourcePieceWise_TransLM.hpp
 * \brief Delaration of numerics class CSourcePieceWise_TransLM, the
 *        implementation is in the CSourcePieceWise_TransLM.cpp file.
 * \author F. Palacios, T. Economon
 * \version 7.0.0 "Blackbird"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation
 * (http://su2foundation.org)
 *
 * Copyright 2012-2019, SU2 Contributors (cf. AUTHORS.md)
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

#pragma once

#include "../CNumerics.hpp"

/*!
 * \class CSourcePieceWise_TransLM
 * \brief Class for integrating the source terms of the Spalart-Allmaras turbulence model equation.
 * \ingroup SourceDiscr
 * \author A. Bueno.
 */
class CSourcePieceWise_TransLM : public CNumerics {
private:
  
  /*-- SA model constants --*/
  su2double cv1_3;
  su2double k2;
  su2double cb1;
  su2double cw2;
  su2double cw3_6;
  su2double sigma;
  su2double cb2;
  su2double cw1;
  
  /*-- gamma-theta model constants --*/
  su2double c_e1;
  su2double c_a1;
  su2double c_e2;
  su2double c_a2;
  su2double sigmaf;
  su2double s1;
  su2double c_theta;
  su2double sigmat;
  
  /*-- Correlation constants --*/
  su2double flen_global;
  su2double alpha_global;
  su2double Vorticity;

  bool implicit;
  
public:
  bool debugme; // For debugging only, remove this. -AA
  
  /*!
   * \brief Constructor of the class.
   * \param[in] val_nDim - Number of dimensions of the problem.
   * \param[in] val_nVar - Number of variables of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CSourcePieceWise_TransLM(unsigned short val_nDim, unsigned short val_nVar, CConfig *config);
  
  /*!
   * \brief Destructor of the class.
   */
  ~CSourcePieceWise_TransLM(void);
  
  /*!
   * \brief Residual for source term integration.
   * \param[out] val_residual - Pointer to the total residual.
   * \param[out] val_Jacobian_i - Jacobian of the numerical method at node i (implicit computation).
   * \param[out] val_Jacobian_j - Jacobian of the numerical method at node j (implicit computation).
   * \param[in] config - Definition of the particular problem.
   */
  void ComputeResidual_TransLM(su2double *val_residual, su2double **val_Jacobian_i, su2double **val_Jacobian_j, CConfig *config, su2double &gamma_sep);
  
  void CSourcePieceWise_TransLM__ComputeResidual_TransLM_d(su2double *TransVar_i, su2double *TransVar_id, su2double *val_residual, su2double *val_residuald, CConfig *config);
};