#include "TransferFunctionDiscretizer.h"
#include <iostream>

TransferFunctionDiscretizer::TransferFunctionDiscretizer(std::string name, ContinuousTransferFunction tf, int sampleFrequency) : m_name(name), m_sampleFrequency(sampleFrequency) {
    std::cout << "TransferFunctionDiscretizer Constructor called." << std::endl;
} 

