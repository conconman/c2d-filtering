#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "ContinuousTransferFunction.h"
 
using Eigen::MatrixXd;
using Eigen::VectorXd;


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
  ASSERT_TRUE(1.0 == 1.0);
}

/*
  This is the most basic use-case of combining filters through cascading. This test doesn't do anything 
  different than the previous test, but it combines two TFs for filters we might actually want to combine.
  This test cascades a 2nd order Butterworth and Notch TFs.
*/
TEST(ContinuousTransferFunctionTest, CascadeButterworthAndNotchFilterTest) {
  ASSERT_TRUE(1.0 == 1.0);
}

/*
  This tests to make sure that the order with which you cascade your TFs doesn't matter and results in the
  same TF.
*/
TEST(ContinuousTransferFunctionTest, CascadeOrderShouldntMatterTest) {
  ASSERT_TRUE(1.0 == 1.0);
}