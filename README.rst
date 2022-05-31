ITKPhaseSymmetry
================

.. image:: https://github.com/KitwareMedical/ITKPhaseSymmetry/workflows/Build,%20test,%20package/badge.svg

.. image:: https://img.shields.io/pypi/v/itk-phasesymmetry.svg
    :target: https://pypi.python.org/pypi/itk-phasesymmetry
    :alt: PyPI

.. image:: https://img.shields.io/badge/License-Apache%202.0-blue.svg
    :target: https://github.com/KitwareMedical/ITKPhaseSymmetry/blob/master/LICENSE)
    :alt: License

Overview
--------

This is a module for the `Insight Toolkit (ITK) <https://itk.org>`_ that
provides multi-scale steerable filters for computing phase symmetry (PS).

Multi-scale steerable phase-symmetry filters are applied in the image Fourier
transform domain, and have been shown to be a useful pre-processing measure
for performing image registration and segmentation.

For more information, see the `Insight Journal article <https://hdl.handle.net/10380/3330>`_::

  Hatt C.
  Multi-scale Steerable Phase-Symmetry Filters for ITK
  The Insight Journal. July-December. 2011.
  https://hdl.handle.net/10380/3330
  https://www.insight-journal.org/browse/publication/846


Installation
------------

Install the binary Python package with::

  pip install itk-phasesymmetry

To build the C++ module, either enable the CMake option in ITK's
build configuration::

  Module_PhaseSymmetry:BOOL=ON

Or, build the module as a separate project against an ITK build tree::

  git clone https://github.com/KitwareMedical/ITKPhaseSymmetry
  mkdir ITKPhaseSymmetry-bulid
  cd ITKPhaseSymmetry-build
  cmake -DITK_DIR=/path/to/ITK-build ../ITKPhaseSymmetry
  cmake --build .


License
-------

This software is distributed under the Apache 2.0 license. Please see
the *LICENSE* file for details.
