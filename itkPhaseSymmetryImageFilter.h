/*=========================================================================

Phase congruency and feature type templated for an ndimensional image
See Peter Kovesi's site for details on the filter
=========================================================================*/
#ifndef __itkPhaseSymmetryImageFilter_h
#define __itkPhaseSymmetryImageFilter_h

#include "itkFFTShiftImageFilter.h"
#include "itkArray2D.h"
#include "itkImageToImageFilter.h"
#include "itkConceptChecking.h"
#include "itkMultiplyImageFilter.h"
#include "itkDivideImageFilter.h"
#include "itkAddImageFilter.h"
#include "itkSqrtImageFilter.h"
#include "itkSquareImageFilter.h"
#include "itkMaximumImageFilter.h"
#include "itkExpImageFilter.h"
#include "itkBoundedReciprocalImageFilter.h"
#include "itkAtan2ImageFilter.h"
#include "itkAcosImageFilter.h"
#include "itkLogGaborFreqImageSource.h"
#include "itkSteerableFilterFreqImageSource.h"
#include "itkButterworthFilterFreqImageSource.h"
#include "itkRealAndImaginaryToComplexImageFilter.h"
#include "itkMagnitudeAndPhaseToComplexImageFilter.h"
#include "itkImageAdaptor.h"
#include "itkVnlForwardFFTImageFilter.h"
#include "itkVnlInverseFFTImageFilter.h"
#include "itkFFTComplexToComplexImageFilter.h"
#include "itkComplexToRealImageFilter.h"
#include "itkComplexToPhaseImageFilter.h"
#include "itkComplexToImaginaryImageFilter.h"
#include "itkComplexToImaginaryImageFilter.h"
#include "itkComplexToModulusImageFilter.h"
#include "itkRealAndImaginaryToComplexImageFilter.h"
#include "itkShiftScaleImageFilter.h"
#include "itkAbsImageFilter.h"

#include <vector>
#include <complex>

namespace itk
{

template <class TInputImage, class TOutputImage>
class PhaseSymmetryImageFilter : public ImageToImageFilter<TInputImage,TOutputImage>
{
public:
  /** Standard class typedefs. */
  typedef PhaseSymmetryImageFilter                     Self;
  typedef ImageToImageFilter<TInputImage,TOutputImage> Superclass;
  typedef SmartPointer<Self>                           Pointer;
  typedef SmartPointer<const Self>                     ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(PhaseSymmetryImageFilter, ImageToImageFilter);

  itkStaticConstMacro(InputImageDimension, unsigned int, TInputImage::ImageDimension);
  itkStaticConstMacro(OutputImageDimension, unsigned int, TOutputImage::ImageDimension);

  /** Some convenient typedefs. */
  typedef TInputImage                            InputImageType;
  typedef typename    InputImageType::Pointer    InputImagePointer;
  typedef typename    InputImageType::RegionType InputImageRegionType;
  typedef typename    InputImageType::PixelType  InputImagePixelType;

  typedef TOutputImage                              OutputImageType;
  typedef typename     OutputImageType::Pointer     OutputImagePointer;
  typedef typename     OutputImageType::RegionType  OutputImageRegionType;
  typedef typename     OutputImageType::PixelType   OutputImagePixelType;

  typedef OutputImagePixelType                           ComplexPixelComponentType;
  typedef OutputImagePixelType                           ImagePixelType;
  typedef std::complex< ComplexPixelComponentType >      ComplexPixelType;

  typedef FixedArray< double, InputImageDimension >   ArrayType;
  typedef FixedArray< double, InputImageDimension-1 > DimMinusOneDoubleArrayType;
  typedef Array2D< double >                           MatrixType;

  typedef Image< ImagePixelType, InputImageDimension > FloatImageType;

  itkSetMacro(Wavelengths, MatrixType );
  itkSetMacro(Orientations, MatrixType );
  itkSetMacro(AngleBandwidth, double );
  itkSetMacro(Sigma,  double);
  itkSetMacro(T, double );
  itkSetMacro(Polarity, int );


  void Initialize();
  /** Input and output images must be the same dimension, or the output's
  dimension must be one less than that of the input. */
#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
  itkConceptMacro(ImageDimensionCheck,
    (Concept::SameDimension<InputImageDimension, OutputImageDimension>));
  /** End concept checking */
#endif


protected:
  PhaseSymmetryImageFilter();
  virtual ~PhaseSymmetryImageFilter() {};
  void PrintSelf(std::ostream& os, Indent indent) const;

  /** Apply changes to the output image information. */
  virtual void GenerateOutputInformation();

  /** Apply changes to the input image requested region. */
  virtual void GenerateInputRequestedRegion();

  void GenerateData(void);

  static const int   FFT_FORWARD = -1;
  static const int   FFT_BACKWARD = 1;

  typedef VnlForwardFFTImageFilter< InputImageType >         FFTFilterType;
  typedef typename FFTFilterType::OutputImageType            ComplexImageType;
  typedef FFTComplexToComplexImageFilter< ComplexImageType > IFFTFilterType;


  typedef std::vector< typename FloatImageType::Pointer > FloatImageStack;
  typedef std::vector< FloatImageStack >                  FloatImageBank;

  typedef MultiplyImageFilter< FloatImageType, FloatImageType >               MultiplyImageFilterType;
  typedef MultiplyImageFilter< ComplexImageType, ComplexImageType >           ComplexMultiplyImageFilterType;
  typedef DivideImageFilter< FloatImageType, FloatImageType, FloatImageType > DivideImageFilterType;
  typedef AddImageFilter< FloatImageType, FloatImageType >                    AddImageFilterType;
  typedef SqrtImageFilter< FloatImageType, FloatImageType >                   SqrtImageFilterType;
  typedef SquareImageFilter< FloatImageType, FloatImageType >                 SquareImageFilterType;
  typedef MaximumImageFilter< FloatImageType, FloatImageType >                MaxImageFilterType;
  typedef ExpImageFilter< FloatImageType, FloatImageType >                    ExpImageFilterType;
  typedef BoundedReciprocalImageFilter< FloatImageType, FloatImageType >      BoundedReciprocalImageFilterType;
  typedef Atan2ImageFilter< FloatImageType, FloatImageType, FloatImageType >  Atan2ImageFilterType;
  typedef AcosImageFilter< FloatImageType, FloatImageType >                   AcosImageFilterType;


  typedef LogGaborFreqImageSource< FloatImageType >          LogGaborFreqImageSourceType;
  typedef SteerableFilterFreqImageSource< FloatImageType >   SteerableFiltersFreqImageSourceType;
  typedef ButterworthFilterFreqImageSource< FloatImageType > ButterworthKernelFreqImageSourceType;

  typedef ShiftScaleImageFilter< FloatImageType, FloatImageType >                                                     ShiftScaleImageFilterType;
  typedef ComplexToRealImageFilter< ComplexImageType, FloatImageType >                                                ComplexToRealFilterType;
  typedef ComplexToImaginaryImageFilter< ComplexImageType, FloatImageType >                                           ComplexToImaginaryFilterType;
  typedef ComplexToModulusImageFilter< ComplexImageType, FloatImageType >                                             ComplexToModulusFilterType;
  typedef ComplexToPhaseImageFilter< ComplexImageType, FloatImageType >                                               ComplexToPhaseFilterType;
  typedef RealAndImaginaryToComplexImageFilter< ImagePixelType, ImagePixelType, ImagePixelType, InputImageDimension > RealAndImaginaryToComplexFilterType;
  typedef MagnitudeAndPhaseToComplexImageFilter< InputImageType, InputImageType, ComplexImageType >                   MagnitudeAndPhaseToComplexFilterType;
  typedef FFTShiftImageFilter< ComplexImageType, ComplexImageType >                                                   ComplexFFTShiftImageFilterType;
  typedef FFTShiftImageFilter< FloatImageType, FloatImageType >                                                       DoubleFFTShiftImageFilterType;
  typedef AbsImageFilter< FloatImageType, FloatImageType >                                                            AbsImageFilterType;

private:
  PhaseSymmetryImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  MatrixType m_Wavelengths;
  MatrixType m_Orientations;

  double m_AngleBandwidth;
  double m_Sigma;
  double m_T;
  int    m_Polarity;

  typename MultiplyImageFilterType::Pointer m_MultiplyImageFilter;
  typename DivideImageFilterType::Pointer   m_DivideImageFilter;
  typename AddImageFilterType::Pointer      m_AddImageFilter;
  typename AddImageFilterType::Pointer      m_AddImageFilter2;
  typename MaxImageFilterType::Pointer      m_MaxImageFilter;
  typename Atan2ImageFilterType::Pointer    m_AtanImageFilter;
  typename AcosImageFilterType::Pointer     m_AcosImageFilter;

  typename FFTFilterType::Pointer  m_FFTFilter;
  typename IFFTFilterType::Pointer m_IFFTFilter;

  typename ShiftScaleImageFilterType::Pointer            m_SSFilter;
  typename ShiftScaleImageFilterType::Pointer            m_NegateFilter;
  typename ShiftScaleImageFilterType::Pointer            m_NegateFilter2;
  typename ComplexToRealFilterType::Pointer              m_C2RFilter;
  typename ComplexToImaginaryFilterType::Pointer         m_C2IFilter;
  typename ComplexToModulusFilterType::Pointer           m_C2MFilter;
  typename ComplexToPhaseFilterType::Pointer             m_C2AFilter;
  typename AbsImageFilterType::Pointer                   m_AbsImageFilter;
  typename AbsImageFilterType::Pointer                   m_AbsImageFilter2;
  typename MagnitudeAndPhaseToComplexFilterType::Pointer m_MP2CFilter;

  typename FloatImageType::Pointer m_PhaseSymmetry;

  FloatImageBank m_FilterBank;
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkPhaseSymmetryImageFilter.txx"
#endif

#endif
