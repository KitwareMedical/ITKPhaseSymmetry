itk_module_test()

set( PhaseSymmetryTests
  itkPhaseSymmetryImageFilterTest.cxx
  itkButterworthFilterFreqImageSourceTest.cxx
  itkLogGaborFreqImageSourceTest.cxx
  itkSteerableFilterFreqImageSourceTest.cxx
  )

CreateTestDriver( PhaseSymmetry "${PhaseSymmetry-Test_LIBRARIES}" "${PhaseSymmetryTests}" )

itk_add_test( NAME itkPhaseSymmetryImageFilterTest
  COMMAND PhaseSymmetryTestDriver itkPhaseSymmetryImageFilterTest )

itk_add_test( NAME itkButterworthFilterFreqImageSourceTest
  COMMAND PhaseSymmetryTestDriver itkButterworthFilterFreqImageSourceTest )

itk_add_test( NAME itkLogGaborFreqImageSourceTest
  COMMAND PhaseSymmetryTestDriver itkLogGaborFreqImageSourceTest )

itk_add_test( NAME itkSteerableFilterFreqImageSourceTest
  COMMAND PhaseSymmetryTestDriver itkSteerableFilterFreqImageSourceTest )