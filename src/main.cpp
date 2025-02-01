#include <iostream>
#include <string>
#include <Eigen/Dense>
#include "ContinuousTransferFunction.h"
 
using Eigen::MatrixXd;

int main() {
    ContinuousTransferFunction tf{}

    std::cout << "------------------------------------" << std::endl;

    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << m << std::endl;

    std::cout << "Program finished." << std::endl;
}