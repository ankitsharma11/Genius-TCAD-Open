// $Id: fe_type.h 2501 2007-11-20 02:33:29Z benkirk $

// The libMesh Finite Element Library.
// Copyright (C) 2002-2007  Benjamin S. Kirk, John W. Peterson
  
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
  
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
  
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



#ifndef __fe_type_h__
#define __fe_type_h__

// C++ includes

// Local includes
#include "auto_ptr.h"
#include "genius_common.h"
#include "enum_order.h"
#include "enum_fe_family.h"

// Forward declarations
class QBase;


/**
 * class FEType hides (possibly multiple) FEFamily and approximation
 * orders, thereby enabling specialized finite element families.
 */
class FEType
{
public:

  /**
   * Constructor.  Optionally takes the approximation \p Order
   * and the finite element family \p FEFamily
   */
  FEType(const Order    o = FIRST,
	 const FEFamily f = LAGRANGE) :
    order(o),
    family(f)
  {}


  //TODO:[BSK] Could these data types all be const?  
  // [RHS] Order can't in the case of p refinement!
  /**
   * The approximation order of the element.  
   */
  Order order;

  /**
   * The type of finite element.  Valid types are \p LAGRANGE,
   * \p HIERARCHIC, etc...
   */
  FEFamily family;

  /**
   * @tests equality
   */
  bool operator== (const FEType &f2) const
  { return (order == f2.order && family == f2.family); }

  /**
   * @an ordering to make FEType useful as a std::map key
   */
  bool operator< (const FEType &f2) const
  {
    if (order != f2.order)
      return (order < f2.order);
    if (family != f2.family)
      return (family < f2.family);
      
    return false;
  }

  /**
   * @returns the default quadrature order for this \p FEType.  The
   * default quadrature order is calculated assuming a polynomial of
   * degree \p order and is based on integrating the mass matrix for
   * such an element exactly.
   */
  Order default_quadrature_order () const;

  /**
   * @returns a quadrature rule of appropriate type and order for this \p
   * FEType.  The default quadrature rule is based on integrating the mass
   * matrix for such an element exactly.  Higher or lower degree rules can
   * be chosen by changing the extraorder parameter.
   */
  AutoPtr<QBase> default_quadrature_rule (const unsigned int dim,
					  const int extraorder=0) const;

  
private:  
  
};



//-------------------------------------------------------------------
// FEType inline methods
inline
Order FEType::default_quadrature_order () const
{
  return static_cast<Order>(2*static_cast<unsigned int>(order) + 1);
}


#endif // #ifndef __fe_type_h__




