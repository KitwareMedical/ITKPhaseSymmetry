/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef __itkButterworthFilterFreqImageSource_hxx
#define __itkButterworthFilterFreqImageSource_hxx

#include "itkButterworthFilterFreqImageSource.h"
#include "itkImageRegionIteratorWithIndex.h"


namespace itk
{

template <class TOutputImage>
ButterworthFilterFreqImageSource<TOutputImage>
::ButterworthFilterFreqImageSource():
  m_Cutoff( 0.4 ),
  m_Order( 4 )
{
  //Initial image is 64 wide in each direction.
  for (unsigned int i=0; i<TOutputImage::GetImageDimension(); i++)
  {
    m_Size[i] = 64;
    m_Spacing[i] = 1.0;
    m_Origin[i] = 0.0;
  }
  m_Direction.SetIdentity();
}


template <class TOutputImage>
ButterworthFilterFreqImageSource<TOutputImage>
::~ButterworthFilterFreqImageSource()
{
}


template <class TOutputImage>
void
ButterworthFilterFreqImageSource<TOutputImage>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os,indent);

  os << indent << "Cutoff: " << this->GetCutoff() << std::endl;
  os << indent << "Order:  " << this->GetOrder() << std::endl;
}


template <typename TOutputImage>
void
ButterworthFilterFreqImageSource<TOutputImage>
::GenerateOutputInformation()
{
  OutputImageType * output = this->GetOutput(0);

  typename TOutputImage::RegionType largestPossibleRegion;
  largestPossibleRegion.SetSize( m_Size );
  typename TOutputImage::IndexType index = {{0}};
  largestPossibleRegion.SetIndex( index );
  output->SetLargestPossibleRegion( largestPossibleRegion );

  output->SetSpacing(m_Spacing);
  output->SetOrigin(m_Origin);
  output->SetDirection(m_Direction);
}


template <typename TOutputImage>
void
ButterworthFilterFreqImageSource<TOutputImage>
::ThreadedGenerateData( const OutputImageRegionType& outputRegionForThread, ThreadIdType itkNotUsed(threadId) )
{
  OutputImageType * outputPtr = this->GetOutput();

  typename OutputImageType::PointType centerPoint;
  for( unsigned int ii = 0; ii < ImageDimension; ++ii )
    {
    centerPoint[ii] = double(m_Size[ii])/2.0;
    }

  typedef ImageRegionIteratorWithIndex<TOutputImage> OutputIterator;
  OutputIterator outIt = OutputIterator(outputPtr, outputRegionForThread);
  for( outIt.GoToBegin(); !outIt.IsAtEnd(); ++outIt )
    {
    const typename TOutputImage::IndexType index = outIt.GetIndex();
    //std::cout << "index: " << index << std::endl;

    double radius = 0.0;
    for( unsigned int ii = 0; ii < ImageDimension; ++ii )
      {
      const double dist = (centerPoint[ii] - double(index[ii])) / double(m_Size[ii]);
      // %todo: is this correct for odd numbers?
      //const SizeValueType halfLength = m_Size[ii] / 2;
      //const double dist = (index[ii] % halfLength) / double(halfLength);
      radius += dist * dist;
      }
    radius = std::sqrt(radius);
    //std::cout << "radius: " << radius << std::endl;

    double value = 0.0;
    value = radius / m_Cutoff;
    value = std::pow(value, 2 * m_Order);
    value = 1. / ( 1. + value );

    // Set the pixel value to the function value
    outIt.Set( static_cast< typename TOutputImage::PixelType >( value ));
    }
}


template<typename TOutputImage>
void
ButterworthFilterFreqImageSource<TOutputImage>
::SetSpacing( const SpacingType & spacing )
{
  if( m_Spacing != spacing )
    {
    this->m_Spacing = spacing;
    this->Modified();
    }
}


template<typename TOutputImage>
void
ButterworthFilterFreqImageSource<TOutputImage>
::SetOrigin( const PointType & origin )
{
  if( m_Origin != origin )
    {
    this->m_Origin = origin;
    this->Modified();
    }
}


template<typename TOutputImage>
void
ButterworthFilterFreqImageSource<TOutputImage>
::SetSize( const SizeType & size )
{
  if( m_Size != size )
    {
    this->m_Size = size;
    this->Modified();
    }
}


template<typename TOutputImage>
void
ButterworthFilterFreqImageSource<TOutputImage>
::SetDirection( const DirectionType & direction )
{
  if( m_Direction != direction )
    {
    this->m_Direction = direction;
    this->Modified();
    }
}

} // end namespace itk

#endif
