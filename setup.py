# -*- coding: utf-8 -*-
from __future__ import print_function
from os import sys

try:
    from skbuild import setup
except ImportError:
    print('scikit-build is required to build from source.', file=sys.stderr)
    print('Please run:', file=sys.stderr)
    print('', file=sys.stderr)
    print('  python -m pip install scikit-build')
    sys.exit(1)

setup(
    name='itk-phasesymmetry',
    version='1.0.5',
    author='Charles Hatt',
    author_email='hatt@wisc.edu',
    packages=['itk'],
    package_dir={'itk': 'itk'},
    download_url=r'https://github.com/KitwareMedical/ITKPhaseSymmetry',
    description=r'ITK classes for computing phase symmetry using multi-scale steerable filters ',
    long_description='itk-phasesymmetry provides multi-scale steerable filters '
                     'for computing phase symmetry (PS) in the image Fourier '
                     'transform domain.\n'
                     'Please refer to:\n'
                     'C. Hatt, "Multi-scale Steerable Phase-Symmetry Filters for ITK.", '
                     'Insight Journal, July-December 2011, http://hdl.handle.net/10380/3330.',
    classifiers=[
        "License :: OSI Approved :: Apache Software License",
        "Programming Language :: Python",
        "Programming Language :: C++",
        "Development Status :: 4 - Beta",
        "Intended Audience :: Developers",
        "Intended Audience :: Education",
        "Intended Audience :: Healthcare Industry",
        "Intended Audience :: Science/Research",
        "Topic :: Scientific/Engineering",
        "Topic :: Scientific/Engineering :: Medical Science Apps.",
        "Topic :: Scientific/Engineering :: Information Analysis",
        "Topic :: Software Development :: Libraries",
        "Operating System :: Android",
        "Operating System :: Microsoft :: Windows",
        "Operating System :: POSIX",
        "Operating System :: Unix",
        "Operating System :: MacOS"
        ],
    license='Apache',
    keywords='ITK InsightToolkit Phase-symmetry Multi-scale Fourier-domain',
    url=r'https://github.com/KitwareMedical/ITKPhaseSymmetry',
    install_requires=[
        r'itk>=5.3rc3'
    ]
    )
