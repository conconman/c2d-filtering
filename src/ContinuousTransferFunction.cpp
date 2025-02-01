#include "ContinuousTransferFunction.h"
#include <iostream>

ContinuousTransferFunction::ContinuousTransferFunction(std::string name, ContinuousTransferFunction severalContinuousTransferFunctions[]) : m_name(name) {
    std::cout << "ContinuousTransferFunction constructor called." << std::endl;
}