#include "ContinuousTransferFunction.h"

ContinuousTransferFunction::ContinuousTransferFunction(std::string name, ContinuousTransferFunction severalContinuousTransferFunctions[], int size) : m_name(name) {
    // Set gain, numerator, and denominator equivalent to first entry.
    m_k             = severalContinuousTransferFunctions[0].getGain();
    m_numerator     = severalContinuousTransferFunctions[0].getNumerator();
    m_denominator   = severalContinuousTransferFunctions[0].getDenominator();

    std::cout << "ContinuousTransferFunction several functions together constructor called, size : " << size << std::endl;
    std::cout << name << " num : " << m_numerator << std::endl;
    std::cout << name << " den : " << m_denominator << std::endl;

    // Cascade several transfer functions together.
    for (int i = 1; i < size; i++) {
        std::cout << "Combining " << name << " and " << severalContinuousTransferFunctions[i].getName() << std::endl;
        std::cout << name << " gain : " << m_k << ", " << severalContinuousTransferFunctions[i].getGain() << std::endl;

        m_k *= severalContinuousTransferFunctions[i].getGain();
        m_numerator     = cascadePolynomials(m_numerator, severalContinuousTransferFunctions[i].getNumerator());
        m_denominator   = cascadePolynomials(m_denominator, severalContinuousTransferFunctions[i].getDenominator());
        std::cout << name << " gain : " << m_k << std::endl;
        std::cout << name << " num : " << m_numerator << std::endl;
        std::cout << name << " den : " << m_denominator << std::endl;
        std::cout << "------------------------------------" << std::endl;

    }
}

VectorXd ContinuousTransferFunction::cascadePolynomials(VectorXd poly1, VectorXd poly2) {
    VectorXd polyOut{poly1.rows() + poly2.rows()-1};
    polyOut.setZero();
    std::cout << "poly1 : " << poly1 << std::endl;
    std::cout << "poly2 : " << poly2 << std::endl;

    // Loop through each polynomials and combine them into polyOut.
    for (int i = 0; i < poly1.rows(); i++) {
        // std::cout << "i : " << i << std::endl;

        for (int j = 0; j < poly2.rows(); j++) {
            // std::cout << "j : " << j << std::endl;
            polyOut(i + j) += poly1(i) * poly2(j);
            // std::cout << "polyOut(i + j) : " << polyOut(i + j) << std::endl;

        }
    }

    std::cout << "polyOut : " << polyOut << std::endl;


    return polyOut;
}