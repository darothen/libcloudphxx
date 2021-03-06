#pragma once 

namespace libcloudphxx
{
  namespace lgrngn
  {
    enum chem_species_t
    {
      SO2, H2O2, O3,    // both gas and aqueous + noneq (must be first as gas species vectors use only these!)
      HSO3, S_VI, SO3,  // only aqueous + noneq (must be after above and before the below to use odeint on a part of the vector only!)
      H, OH, HSO4, SO4, // only aqueous (not used in the odeint vector), the fact that H is first here is hardcoded near odeint calls!!!
      chem_gas_n = O3 + 1,
      chem_rhs_n = SO3 + 1,
      chem_aq_n  = SO4 + 1
    };
  };
};
