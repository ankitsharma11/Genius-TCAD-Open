// $Id: type_tensor.cc,v 1.2 2008/06/04 12:25:15 gdiso Exp $

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




// C++ includes
#include <iostream>
#include <iomanip> // for std::setw, std::setiosflags

// Local includes
#include "type_tensor.h"




// ------------------------------------------------------------
// TypeTensor<T> class member funcions


template <typename T>
void TypeTensor<T>::print(std::ostream& os) const
{
#if DIM == 1
  
  os << "x=" << (*this)(0) << std::endl;
  
#endif
#if DIM == 2
  
  os << "(xx,xy)=("
     << std::setw(8) << (*this)(0,0) << ", "
     << std::setw(8) << (*this)(0,1) << ")"
     << std::endl;
  os << "(yx,yy)=("
     << std::setw(8) << (*this)(1,0) << ", "
     << std::setw(8) << (*this)(1,1) << ")"
     << std::endl;

#endif
#if DIM == 3
  
  os <<  "(xx,xy,xz)=("
     << std::setw(8) << (*this)(0,0) << ", "
     << std::setw(8) << (*this)(0,1) << ", "
     << std::setw(8) << (*this)(0,2) << ")"
     << std::endl;
  os <<  "(yx,yy,yz)=("
     << std::setw(8) << (*this)(1,0) << ", "
     << std::setw(8) << (*this)(1,1) << ", "
     << std::setw(8) << (*this)(1,2) << ")"
     << std::endl;
  os <<  "(zx,zy,zz)=("
     << std::setw(8) << (*this)(2,0) << ", "
     << std::setw(8) << (*this)(2,1) << ", "
     << std::setw(8) << (*this)(2,2) << ")"
     << std::endl;
#endif
}





template <typename T>
void TypeTensor<T>::write_unformatted (std::ostream &out,
				       const bool newline) const
{
  assert (out);

  out << std::setiosflags(std::ios::showpoint)
      << (*this)(0,0) << " "
      << (*this)(0,1) << " "
      << (*this)(0,2) << " ";
  if (newline)
    out << '\n';      

  out << std::setiosflags(std::ios::showpoint)
      << (*this)(1,0) << " "
      << (*this)(1,1) << " "
      << (*this)(1,2) << " ";
  if (newline)
    out << '\n';      

  out << std::setiosflags(std::ios::showpoint)
      << (*this)(2,0) << " "
      << (*this)(2,1) << " "
      << (*this)(2,2) << " ";
  if (newline)
    out << '\n';      
}



template <typename T>
bool TypeTensor<T>::operator < (const TypeTensor<T>& rhs) const
{
  for (unsigned int i=0; i<DIM; i++)
    for (unsigned int j=0; j<DIM; j++)
      {
        if ((*this)(i,j) < rhs(i,j))
          return true;
        if ((*this)(i,j) > rhs(i,j))
          return false;
      }
  return false;
}





// ------------------------------------------------------------
// Explicit instantiations
template class TypeTensor<float>;
template class TypeTensor<double>;
template class TypeTensor<long double>;
template class TypeTensor<AutoDScalar>;


