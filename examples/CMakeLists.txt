cmake_minimum_required(VERSION 3.10.2)
# This project is designed to be built outside the Insight source tree.
project( PhaseSymmetryImageFilter)

find_package(ITK REQUIRED
  COMPONENTS
    PhaseSymmetry
    ITKImageIO
    ITKTransformIO
  )
include(${ITK_USE_FILE})

find_package( SlicerExecutionModel REQUIRED )
include( ${SlicerExecutionModel_USE_FILE} )

SEMMacroBuildCLI(
  NAME PhaseSymmetryFilter
  TARGET_LIBRARIES ${ITK_LIBRARIES}
  )

add_executable( PhaseSymmetryImageFilter2D main2.cxx)
target_link_libraries( PhaseSymmetryImageFilter2D ${ITK_LIBRARIES} )

add_executable( PhaseSymmetryImageFilter3D main3.cxx)
target_link_libraries( PhaseSymmetryImageFilter3D ${ITK_LIBRARIES} )
