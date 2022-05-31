/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include "itkPhaseSymmetryImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkShiftScaleImageFilter.h"
#include "itkMultiplyImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImage.h"
#include "itkArray2D.h"
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <exception>

std::vector<std::string>
parse(std::string l, char delim)
{
  std::replace(l.begin(), l.end(), delim, ' ');
  std::istringstream       stm(l);
  std::vector<std::string> tokens;
  for (;;)
  {
    std::string word;
    if (!(stm >> word))
      break;
    tokens.push_back(word);
  }
  return tokens;
}

int
main(int argc, char * argv[])
{
  std::stringstream ss;
  std::string       infile;
  std::string       outfile;
  std::string       wavelengthsS;
  std::string       orientationsS;
  std::string       sigmaS;
  std::string       angular_bandwidthS;
  std::string       polarityS;
  std::string       ntS;

  double pi = 3.1416;

  if (argc < 3)
  {
    std::cerr << "Usage: PhaseSymmetryFilter3D.exe infile outfile wavelengths orientations sigma angular_bandwidth "
                 "polarity noise_threshhold"
              << std::endl;
    std::cerr
      << "Example: PhaseSymmetryFilter3D.exe i.mhd o.mhd 3,3,3,6,6,6,12,12,12 1,0,0,0,1,0,0,0,1 0.55 3.14 0 10.0"
      << std::endl;
    return EXIT_FAILURE;
  }
  else if (argc < 4)
  {
    ss << argv[1];
    infile = ss.str();
    ss.str("");
    ss << argv[2];
    outfile = ss.str();
    ss.str("");
    ss << "10,10,20,20,40,40";
    wavelengthsS = ss.str();
    ss.str("");
    ss << "1,0,0,1";
    orientationsS = ss.str();
    ss.str("");
    ss << "0.55";
    sigmaS = ss.str();
    ss.str("");
    ss << "3.1416";
    angular_bandwidthS = ss.str();
    ss.str("");
    ss << "1";
    polarityS = ss.str();
    ss.str("");
    ss << "10.0";
    ntS = ss.str();
    ss.str("");
  }
  else if (argc < 5)
  {
    ss << argv[1];
    infile = ss.str();
    ss.str("");
    ss << argv[2];
    outfile = ss.str();
    ss.str("");
    ss << argv[3];
    wavelengthsS = ss.str();
    ss.str("");
    ss << "1,0,0,1";
    orientationsS = ss.str();
    ss.str("");
    ss << "0.55";
    sigmaS = ss.str();
    ss.str("");
    ss << "3.1416";
    angular_bandwidthS = ss.str();
    ss.str("");
    ss << "1";
    polarityS = ss.str();
    ss.str("");
    ss << "10.0";
    ntS = ss.str();
    ss.str("");
  }
  else if (argc < 6)
  {
    ss << argv[1];
    infile = ss.str();
    ss.str("");
    ss << argv[2];
    outfile = ss.str();
    ss.str("");
    ss << argv[3];
    wavelengthsS = ss.str();
    ss.str("");
    ss << argv[4];
    orientationsS = ss.str();
    ss.str("");
    ss << "0.55";
    sigmaS = ss.str();
    ss.str("");
    ss << "3.1416";
    angular_bandwidthS = ss.str();
    ss.str("");
    ss << "1";
    polarityS = ss.str();
    ss.str("");
    ss << "10.0";
    ntS = ss.str();
    ss.str("");
  }
  else if (argc < 7)
  {
    ss << argv[1];
    infile = ss.str();
    ss.str("");
    ss << argv[2];
    outfile = ss.str();
    ss.str("");
    ss << argv[3];
    wavelengthsS = ss.str();
    ss.str("");
    ss << argv[4];
    orientationsS = ss.str();
    ss.str("");
    ss << argv[5];
    sigmaS = ss.str();
    ss.str("");
    ss << "3.1416";
    angular_bandwidthS = ss.str();
    ss.str("");
    ss << "1";
    polarityS = ss.str();
    ss.str("");
    ss << "10.0";
    ntS = ss.str();
    ss.str("");
  }
  else if (argc < 8)
  {
    ss << argv[1];
    infile = ss.str();
    ss.str("");
    ss << argv[2];
    outfile = ss.str();
    ss.str("");
    ss << argv[3];
    wavelengthsS = ss.str();
    ss.str("");
    ss << argv[4];
    orientationsS = ss.str();
    ss.str("");
    ss << argv[5];
    sigmaS = ss.str();
    ss.str("");
    ss << argv[6];
    angular_bandwidthS = ss.str();
    ss.str("");
    ss << "1";
    polarityS = ss.str();
    ss.str("");
    ss << "10.0";
    ntS = ss.str();
    ss.str("");
  }
  else if (argc < 9)
  {
    ss << argv[1];
    infile = ss.str();
    ss.str("");
    ss << argv[2];
    outfile = ss.str();
    ss.str("");
    ss << argv[3];
    wavelengthsS = ss.str();
    ss.str("");
    ss << argv[4];
    orientationsS = ss.str();
    ss.str("");
    ss << argv[5];
    sigmaS = ss.str();
    ss.str("");
    ss << argv[6];
    angular_bandwidthS = ss.str();
    ss.str("");
    ss << argv[7];
    polarityS = ss.str();
    ss.str("");
    ss << "10.0";
    ntS = ss.str();
    ss.str("");
  }
  else
  {
    ss << argv[1];
    infile = ss.str();
    ss.str("");
    ss << argv[2];
    outfile = ss.str();
    ss.str("");
    ss << argv[3];
    wavelengthsS = ss.str();
    ss.str("");
    ss << argv[4];
    orientationsS = ss.str();
    ss.str("");
    ss << argv[5];
    sigmaS = ss.str();
    ss.str("");
    ss << argv[6];
    angular_bandwidthS = ss.str();
    ss.str("");
    ss << argv[7];
    polarityS = ss.str();
    ss.str("");
    ss << argv[8];
    ntS = ss.str();
    ss.str("");
  }

  using ImagePixelType = float;
  int ndims = 2;
  using ImageType = itk::Image<ImagePixelType, 2>;
  using PSFilterType = itk::PhaseSymmetryImageFilter<ImageType, ImageType>;
  using ReaderType = itk::ImageFileReader<ImageType>;
  using WriterType = itk::ImageFileWriter<ImageType>;

  using DoubleMatrix = itk::Array2D<double>;

  ImageType::Pointer    inImg = ImageType::New();
  ReaderType::Pointer   reader = ReaderType::New();
  WriterType::Pointer   writer = WriterType::New();
  PSFilterType::Pointer psfilter = PSFilterType::New();


  // 3 wavelengths, 3 dimensions
  std::vector<std::string> wavelengthsVS = parse(wavelengthsS, ',');
  if (wavelengthsVS.size() % 2 != 0)
  {
    std::cerr << "wavelengths must be a comma seperated string of numbers with number of elements divisible by 3"
              << std::endl;
    return EXIT_FAILURE;
  }

  std::vector<std::string> orientationsVS = parse(orientationsS, ',');
  if (orientationsVS.size() % 2 != 0)
  {
    std::cerr << "orientations must be a comma seperated string of numbers with number of elements divisible by 3"
              << std::endl;
    return EXIT_FAILURE;
  }

  int          wvCount = int(double(wavelengthsVS.size()) / 2.0);
  DoubleMatrix wavelengths(wvCount, 2);
  int          orCount = int(double(orientationsVS.size()) / 2.0);
  DoubleMatrix orientations(orCount, 2);

  int idx = 0;
  for (int i = 0; i < wvCount; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      wavelengths(i, j) = std::stod(wavelengthsVS[idx].c_str());
      idx++;
    }
  }

  idx = 0;
  for (int i = 0; i < orCount; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      orientations(i, j) = std::stod(orientationsVS[idx].c_str());
      idx++;
    }
  }

  double sigma = 0;
  sigma = std::stod(sigmaS.c_str());

  double anglebandwidth = 0;
  anglebandwidth = std::stod(angular_bandwidthS.c_str());

  int polarity = 0;
  polarity = int(std::stod(polarityS.c_str()));

  double noiseT = 0;
  noiseT = std::stod(ntS.c_str());

  reader->SetFileName(infile.c_str());
  try
  {
    reader->Update();
    inImg = reader->GetOutput();
    inImg->DisconnectPipeline();
  }
  catch (itk::ExceptionObject & excp)
  {
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
  }

  psfilter->SetInput(inImg);
  psfilter->SetWavelengths(wavelengths);
  psfilter->SetOrientations(orientations);
  psfilter->SetSigma(sigma);
  psfilter->SetAngleBandwidth(anglebandwidth);
  psfilter->SetPolarity(polarity);
  psfilter->SetNoiseThreshold(noiseT);
  psfilter->Initialize();

  try
  {
    writer->SetFileName(outfile.c_str());
    writer->SetInput(psfilter->GetOutput());
    writer->Update();
  }
  catch (itk::ExceptionObject & excp)
  {
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
