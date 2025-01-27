#!/usr/bin/env python
# ==========================================================================
#
#   Copyright NumFOCUS
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          https://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
# ==========================================================================*/

import itk
import argparse
import numpy as np


def run(
    input_image_file,
    output_image_file,
    wavelengths=None,
    sigma=0.55,
    polarity=0,
    noise_threshold=10.0,
):
    input_image = itk.imread(input_image_file, itk.ctype("float"))
    boundary_condition = itk.PeriodicBoundaryCondition[type(input_image)]()
    padded = itk.fft_pad_image_filter(
        input_image, boundary_condition=boundary_condition
    )

    dimension = input_image.GetImageDimension()

    phase_symmetry_filter = itk.PhaseSymmetryImageFilter.New(padded)

    if wavelengths:
        scales = len(wavelengths) / dimension
        wavelength_matrix = itk.Array2D[itk.D](int(scales), dimension)
        np_array = np.array(wavelengths, dtype=np.float64)
        vnl_vector = itk.GetVnlVectorFromArray(np_array)
        wavelength_matrix.copy_in(vnl_vector.data_block())
        phase_symmetry_filter.SetWavelengths(wavelength_matrix)

    if dimension == 2:
        orientation_matrix = itk.Array2D[itk.D](2, dimension)
        np_array = np.array([1, 0, 0, 1], dtype=np.float64)
        vnl_vector = itk.GetVnlVectorFromArray(np_array)
        orientation_matrix.copy_in(vnl_vector.data_block())
        phase_symmetry_filter.SetOrientations(orientation_matrix)
    else:
        orientation_matrix = itk.Array2D[itk.D](3, dimension)
        np_array = np.array([1, 0, 0, 0, 1, 0, 0, 0, 1], dtype=np.float64)
        vnl_vector = itk.GetVnlVectorFromArray(np_array)
        orientation_matrix.copy_in(vnl_vector.data_block())
        phase_symmetry_filter.SetOrientations(orientation_matrix)

    phase_symmetry_filter.SetSigma(sigma)
    phase_symmetry_filter.SetPolarity(polarity)
    phase_symmetry_filter.SetNoiseThreshold(noise_threshold)

    phase_symmetry_filter.Initialize()

    output_image = phase_symmetry_filter.GetOutput()
    itk.imwrite(output_image, output_image_file, True)


def main():
    parser = argparse.ArgumentParser(
        description="Compute image phase symmetry.",
        epilog="Example invocation: phase-symmetry.py --wavelengths 10 10 10 20 20 20 30 30 30 --sigma 0.25 --polarity 1 --noise-threshold 10.0 -- /tmp/HeartUltrasound.mha /tmp/HeartUltrasoundPhaseSymmetry.mha",
    )

    parser.add_argument("input_image")
    parser.add_argument("output_image")
    parser.add_argument(
        "-w", "--wavelengths", dest="wavelengths", nargs="+", type=float
    )
    parser.add_argument("-s", "--sigma", dest="sigma", type=float, default=0.55)
    parser.add_argument(
        "-p", "--polarity", dest="polarity", type=int, choices=[-1, 0, 1], default=0
    )
    parser.add_argument(
        "-n", "--noise-threshold", dest="noise", type=float, default=10.0
    )
    args = parser.parse_args()

    run(
        args.input_image,
        args.output_image,
        args.wavelengths,
        args.sigma,
        args.polarity,
        args.noise,
    )


if __name__ == "__main__":
    main()
