#pragma once

#include <libcloudph++/common/units.hpp>
#include <libcloudph++/common/macros.hpp>
#include <libcloudph++/common/earth.hpp>
#include <libcloudph++/common/theta_std.hpp>

namespace libcloudphxx
{
  namespace common
  {
    namespace hydrostatic
    {
      using theta_std::p_1000;
      using moist_air::R; // TODO: czy na pewno potzebne?
      using moist_air::c_pd;
      using moist_air::R_d;
      using earth::g;

      // pressure profile derived by integrating the hydrostatic eq.
      // assuming constant theta, constant rv and R=R(rv)
      template <typename real_t>
      quantity<si::pressure,real_t> p(
	quantity<si::length, real_t> z,
	quantity<si::temperature,real_t> th_0,
	quantity<si::dimensionless, real_t> r_0,
	quantity<si::length, real_t> z_0,
	quantity<si::pressure, real_t> p_0
      ) {
	return p_1000<real_t>() * real_t(pow(
	  pow(p_0 / p_1000<real_t>(), R_d<real_t>()/c_pd<real_t>())
	  -
	  R_d<real_t>()/c_pd<real_t>() * g<real_t>() / th_0 / R<real_t>(r_0) * (z - z_0),
	  c_pd<real_t>() / R_d<real_t>()
	));
      }
    };
  };
};
