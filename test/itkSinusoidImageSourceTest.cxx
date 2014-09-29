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

#include "itkFilterWatcher.h"
#include "itkSinusoidImageSource.h"
#include "itkTestingMacros.h"
#include "itkImageFileWriter.h"

int itkSinusoidImageSourceTest(int argc, char* argv[] )
{
  if( argc < 2 )
    {
    std::cerr << "Usage: " << argv[0] << " OutputImage [XFrequency] [YFrequency] [ZFrequency] [PhaseShift]" << std::endl;
    return EXIT_FAILURE;
    }
  const char * outputImageFileName = argv[1];
  double xFrequency = 0.02;
  if( argc > 2 )
    {
    xFrequency = atof( argv[2] );
    }
  double yFrequency = 0.1;
  if( argc > 3 )
    {
    yFrequency = atof( argv[3] );
    }
  double zFrequency = 0.2;
  if( argc > 4 )
    {
    zFrequency = atof( argv[4] );
    }
  double phaseShift = 0.2;
  if( argc > 5 )
    {
    phaseShift = atof( argv[5] );
    }

  // This can be changed!
  const unsigned int    Dimension = 3;
  typedef float          PixelType;

  // Image typedef
  typedef itk::Image< PixelType, Dimension > ImageType;

  // Create a gaussian image source
  typedef itk::SinusoidImageSource< ImageType > SinusoidSourceType;
  SinusoidSourceType::Pointer source = SinusoidSourceType::New();
  FilterWatcher watcher(source, "source");

  ImageType::SpacingValueType   spacing[] = { 1.2f, 1.3f, 1.4f };
  ImageType::PointValueType     origin[] = { 1.0f, 4.0f, 2.0f };
  ImageType::SizeValueType      size[] = {  30,  50,  20 };

  SinusoidSourceType::ArrayType frequency;
  frequency[0] = 0.01;
  frequency[1] = 0.2;
  frequency[2] = 0.4;

  source->SetSize( size );
  source->SetOrigin( origin );
  source->SetSpacing( spacing );
  source->SetFrequency( frequency );
  source->SetPhaseShift( 0.3 );

  // Test the get macros as well (booorrring...)
  source->GetSize();
  source->GetSpacing();
  source->GetOrigin();
  source->GetDirection();
  source->GetFrequency();
  source->GetPhaseShift();

  // Test the get/set parameters
  SinusoidSourceType::ParametersType params = source->GetParameters();
  if ( params.GetSize() != 4 )
    {
    std::cerr << "Incorrect number of parameters. Expected 4, got "
              << params.GetSize() << "." << std::endl;
    return EXIT_FAILURE;
    }

  if ( params[0] != frequency[0] || params[1] != frequency[1] || params[2] != frequency[2] )
    {
    std::cerr << "Parameters have incorrect frequency value." << std::endl;
    return EXIT_FAILURE;
    }

  if ( params[3] != 0.3 )
    {
    std::cerr << "Parameters have incorrect phase shift value." << std::endl;
    return EXIT_FAILURE;
    }

  params[0] = xFrequency;
  params[1] = yFrequency;
  params[2] = zFrequency;
  params[3] = phaseShift;
  source->SetParameters( params );

  if ( source->GetFrequency()[0] != params[0] ||
       source->GetFrequency()[1] != params[1] ||
       source->GetFrequency()[2] != params[2] )
    {
    std::cerr << "Frequency disagrees with parameters array." << std::endl;
    std::cerr << "Frequency: " << source->GetFrequency() << ", parameters: ["
              << params[0] << ", " << params[1] << ", " << params[2]
              << "]" << std::endl;
    return EXIT_FAILURE;
    }

  if ( source->GetPhaseShift() != params[3] )
    {
    std::cerr << "PhaseShift disagrees with parameters array." << std::endl;
    std::cerr << "PhaseShift: " << source->GetPhaseShift() << ", parameters: "
              << params[3] << std::endl;
    return EXIT_FAILURE;
    }

  // Get the output of the source
  ImageType::ConstPointer image = source->GetOutput();

  // Run the pipeline
  TRY_EXPECT_NO_EXCEPTION( source->Update() );

  // Exercise the print method
  std::cout << source << std::endl;
  std::cout << image << std::endl;

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputImageFileName );
  writer->SetInput( source->GetOutput() );
  TRY_EXPECT_NO_EXCEPTION( writer->Update() );

  // Instantiate 1D case.
  typedef itk::Image< PixelType, 1 >              Image1DType;
  typedef itk::SinusoidImageSource< Image1DType > SinusoidSource1DType;
  SinusoidSource1DType::Pointer source1D = SinusoidSource1DType::New();

  return EXIT_SUCCESS;
}
