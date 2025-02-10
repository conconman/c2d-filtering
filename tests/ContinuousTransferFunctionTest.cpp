#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "ContinuousTransferFunction.h"
#include <memory>
#include <math.h>
 
using Eigen::MatrixXd;
using Eigen::VectorXd;

// Set tolerance on Matlab
double tolerance = 0.00000000001;

/*
  Check that the numerator and denominator are get/set correctly.
*/
TEST(ContinuousTransferFunctionTest, NumeratorAndDenominatorSetCorrectlyTest) {
  
  // Set parameters.
  std::string name = "tf";
  double k = 1.0;             // Gain
  VectorXd numerator{5};      // TF Numerator polynomial.
  VectorXd denominator{5};    // TF Denominator polynomial.
  numerator << 1.0, 2.0, 3.0, 4.0, 5.0;
  denominator << 5.0, 4.0, 3.0, 2.0, 1.0;

  // Build a ContinuousTransferFunction object.
  ContinuousTransferFunction tf{name, k, numerator, denominator};

  // Return name, gain, numerator, and denominator and check that they are correct.
  std::string r_name      = tf.getName();
  double r_k              = tf.getGain();
  VectorXd r_numerator(5);
  VectorXd r_denominator(5);
  r_numerator << tf.getNumerator();
  r_denominator << tf.getDenominator();

  std::cout << "Check that we construct the objects correctly." << std::endl;
  ASSERT_TRUE(name == r_name);
  ASSERT_TRUE(k == r_k);
  ASSERT_TRUE(numerator.isApprox(r_numerator));
  ASSERT_TRUE(denominator.isApprox(r_denominator));  

  // Set the numerator and denominator to something new and check that they are correct.
  name = "new_name";
  k = 10.0;
  numerator.resize(3);
  denominator.resize(3);
  numerator << 9.0, 10.0, 1.0;
  denominator << 1.0, 10.0, 3.0;

  tf.setName(name);
  tf.setGain(k);
  tf.setNumerator(numerator);
  tf.setDenominator(denominator);

  r_name          = tf.getName();
  r_k             = tf.getGain();
  r_numerator.resize(3);
  r_denominator.resize(3);
  r_numerator << tf.getNumerator();
  r_denominator << tf.getDenominator();

  std::cout << "Check that we can correctly adjust member variables." << std::endl;
  ASSERT_TRUE(name == r_name);
  ASSERT_TRUE(k == r_k);
  ASSERT_TRUE(numerator.isApprox(r_numerator));
  ASSERT_TRUE(denominator.isApprox(r_denominator));  

}
/*
  Test to see if cascaded TFs result in the correct TF when combined.
*/
TEST(ContinuousTransferFunctionTest, CascadingTFsTest) {
  
  //Construct several transfer functions and combine them into a large one.
  std::string name1 = "tf1";
  double k1 = 5;
  VectorXd numerator1{4};
  VectorXd denominator1{5};
  numerator1.setZero();
  denominator1.setZero();
  numerator1 << 1.0, 2.0, 3.0, 5.0;
  denominator1 << 5.0, 4.0, 3.0, 2.0, 1.0;
  ContinuousTransferFunction tf1{name1, k1, numerator1, denominator1};
  std::cout << "Transfer function " << name1 << " constructed." << std::endl;

  std::string name2 = "tf2";
  double k2 = 9;
  VectorXd numerator2{3};
  VectorXd denominator2{5};
  numerator2.setZero();
  denominator2.setZero();
  numerator2 << 10.0, 5.0, 5.0;
  denominator2 << 18.0, 0.1, 1.8, 49.0, 0.0;
  ContinuousTransferFunction tf2{name2, k2, numerator2, denominator2};
  std::cout << "Transfer function " << name2 << " constructed." << std::endl;

  std::string name3 = "tf3";
  double k3 = 1;
  VectorXd numerator3{5};
  VectorXd denominator3{9};
  numerator3.setZero();
  denominator3.setZero();
  numerator3 << 9.0, 0.0, 0.0, 45.0, 1.9;
  denominator3 << 5.0, 4.0, 3.0, 6.0, 10.0, 1.8, 17.0, 9.0, 4.0;
  ContinuousTransferFunction tf3{name3, k3, numerator3, denominator3};
  std::cout << "Transfer function " << name3 << " constructed." << std::endl;


  // Combine Transfer Functions.
  std::string name4 = "combinedTF";
  ContinuousTransferFunction severalContinuousTransferFunctions[3] = {tf1, tf2, tf3};
  ContinuousTransferFunction combinedTF{name4, severalContinuousTransferFunctions, 3};
  std::cout << "Transfer function " << name4 << " constructed." << std::endl;

  // Set expected values for Combined Transfer Function calculated via MATLAB.
  double k_expected = k1*k2*k3;
  VectorXd numerator_expected{10};
  VectorXd denominator_expected{17}; 
  numerator_expected.setZero();
  denominator_expected.setZero();
  numerator_expected <<   90,
                          225,
                          405,
                          1125,
                          1504,
                          2.297500000000000e+03,
                          3.460500000000000e+03,
                          1.942500000000000e+03,
                          1201,
                          47.500000000000000;
  denominator_expected << 450,
                          7.225000000000000e+02,
                          877,
                          2.453600000000000e+03,
                          3.777200000000000e+03,
                          3.764800000000000e+03,
                          5.786100000000000e+03,
                          7.455520000000000e+03,
                          6.205200000000000e+03,
                          8.413180000000000e+03,
                          8.146559999999999e+03,
                          6.361940000000000e+03,
                          4.019500000000000e+03,
                          2334,
                          8.402000000000000e+02,
                          196,
                          0;

  // Set assertions so that the expected values from MATLAB are what we get in return.
  EXPECT_NEAR(k_expected, combinedTF.getGain(), tolerance);
  EXPECT_TRUE(numerator_expected.isApprox(combinedTF.getNumerator(), tolerance));
  EXPECT_TRUE(denominator_expected.isApprox(combinedTF.getDenominator(), tolerance));
}

/*
  This is the most basic use-case of combining filters through cascading. This test doesn't do anything 
  different than the previous test, but it combines two TFs for filters we might actually want to combine.
  This test cascades a 2nd order Butterworth and Notch TFs.
*/
TEST(ContinuousTransferFunctionTest, CascadeButterworthAndNotchFilterTest) {
  
  //Build Butterworth and Notch filters.
  std::string name_butter = "Second Order Low-pass Butterworth Filter";
  double k_butter = 1.0;          // DC Gain
  double wc = 2*M_PI*10.0;        // Cut-off Frequency
  VectorXd numerator_butter{1};
  VectorXd denominator_butter{3};
  numerator_butter.setZero();
  denominator_butter.setZero();
  numerator_butter << wc * wc;
  denominator_butter << 1.0, sqrt(2) * wc, wc * wc;
  ContinuousTransferFunction tf_butter{name_butter, k_butter, numerator_butter, denominator_butter};
  std::cout << "Transfer function " << name_butter << " constructed." << std::endl;

  std::string name_notch = "Second Order Notch Filter";
  double k_notch = 1.0;         // DC Gain
  double wn = 60 * 2 * M_PI;    // Attenuate Frequency
  double Q = 5.0;               // Filter Quality
  VectorXd numerator_notch{3};
  VectorXd denominator_notch{3};
  numerator_notch.setZero();
  denominator_notch.setZero();
  numerator_notch << 1.0, 0.0, wn * wn;
  denominator_notch << 1.0, wn / Q, wn * wn;
  ContinuousTransferFunction tf_notch{name_notch, k_notch, numerator_notch, denominator_notch};
  std::cout << "Transfer function " << name_notch << " constructed." << std::endl;

  // Create Combined Tranfer Function.
  std::string name_combined = "combinedTF";
  ContinuousTransferFunction severalContinuousTransferFunctions[2] = {tf_butter, tf_notch};
  ContinuousTransferFunction combinedTF{name_combined, severalContinuousTransferFunctions, 2};
  std::cout << "Transfer function " << name_combined << " constructed." << std::endl;

  // Create expected output and compare gain, numerator, and denominator of Combined TF to expected output.
  double k_expected = k_butter * k_notch;
  VectorXd numerator_expected{3};
  VectorXd denominator_expected{5}; 
  numerator_expected.setZero();
  denominator_expected.setZero();
  numerator_expected << 3.947841760435743e+03, 0, 5.610763643558538e+08;
  denominator_expected << 1, 1.642558824493224e+02, 1.527698547677758e+05, 1.292631539212299e+07, 5.610763643558538e+08;

  // Set assertions so that the expected values from MATLAB are what we get in return.
  EXPECT_NEAR(k_expected, combinedTF.getGain(), tolerance);
  EXPECT_TRUE(numerator_expected.isApprox(combinedTF.getNumerator(), tolerance));
  EXPECT_TRUE(denominator_expected.isApprox(combinedTF.getDenominator(), tolerance));
}

/*
  This tests to make sure that the order with which you cascade your TFs doesn't matter and results in the
  same TF.
*/
TEST(ContinuousTransferFunctionTest, CascadeOrderShouldntMatterTest) {
    //Build Butterworth and Notch filters.
    std::string name_butter = "Second Order Low-pass Butterworth Filter";
    double k_butter = 1.0;          // DC Gain
    double wc = 2*M_PI*10.0;        // Cut-off Frequency
    VectorXd numerator_butter{1};
    VectorXd denominator_butter{3};
    numerator_butter.setZero();
    denominator_butter.setZero();
    numerator_butter << wc * wc;
    denominator_butter << 1.0, sqrt(2) * wc, wc * wc;
    ContinuousTransferFunction tf_butter{name_butter, k_butter, numerator_butter, denominator_butter};
    std::cout << "Transfer function " << name_butter << " constructed." << std::endl;
  
    std::string name_notch = "Second Order Notch Filter";
    double k_notch = 1.0;         // DC Gain
    double wn = 60 * 2 * M_PI;    // Attenuate Frequency
    double Q = 5.0;               // Filter Quality
    VectorXd numerator_notch{3};
    VectorXd denominator_notch{3};
    numerator_notch.setZero();
    denominator_notch.setZero();
    numerator_notch << 1.0, 0.0, wn * wn;
    denominator_notch << 1.0, wn / Q, wn * wn;
    ContinuousTransferFunction tf_notch{name_notch, k_notch, numerator_notch, denominator_notch};
    std::cout << "Transfer function " << name_notch << " constructed." << std::endl;
  
    // Create Combined Tranfer Functions.
    std::string name_combined_butter_notch = "Combined TF Butterworth and Notch";
    ContinuousTransferFunction severalContinuousTransferFunctions_butter_notch[2] = {tf_butter, tf_notch};
    ContinuousTransferFunction combinedTF_butter_notch{name_combined_butter_notch, severalContinuousTransferFunctions_butter_notch, 2};
    std::cout << "Transfer function " << name_combined_butter_notch << " constructed." << std::endl;

    std::string name_combined_notch_butter = "Combined TF Notch and Butter";
    ContinuousTransferFunction severalContinuousTransferFunctions_notch_butter[2] = {tf_notch, tf_butter};
    ContinuousTransferFunction combinedTF_notch_butter{name_combined_notch_butter, severalContinuousTransferFunctions_notch_butter, 2};
    std::cout << "Transfer function " << name_combined_notch_butter << " constructed." << std::endl;

  
    // Set assertions so that the expected values from MATLAB are what we get in return.
    EXPECT_NEAR(combinedTF_butter_notch.getGain(), combinedTF_notch_butter.getGain(), tolerance);
    EXPECT_TRUE(combinedTF_butter_notch.getNumerator().isApprox(combinedTF_notch_butter.getNumerator(), tolerance));
    EXPECT_TRUE(combinedTF_butter_notch.getDenominator().isApprox(combinedTF_notch_butter.getDenominator(), tolerance));
}