#include "ContinuousTransferFunction.h"

ContinuousTransferFunction::ContinuousTransferFunction(std::string name, ContinuousTransferFunction severalContinuousTransferFunctions[], int size) : m_name(name) {
    // Set gain, numerator, and denominator equivalent to first entry.
    m_k             = severalContinuousTransferFunctions[0].getGain();
    m_numerator     = severalContinuousTransferFunctions[0].getNumerator();
    m_denominator   = severalContinuousTransferFunctions[0].getDenominator();

    // Cascade several transfer functions together.
    for (int i = 1; i < size; i++) {
        m_k *= severalContinuousTransferFunctions[i].getGain();
        m_numerator     = cascadePolynomials(m_numerator, severalContinuousTransferFunctions[i].getNumerator());
        m_denominator   = cascadePolynomials(m_denominator, severalContinuousTransferFunctions[i].getDenominator());
    }
}

VectorXd ContinuousTransferFunction::cascadePolynomials(VectorXd poly1, VectorXd poly2) {
    VectorXd polyOut{poly1.rows() + poly2.rows()-1};
    polyOut.setZero();

    // Loop through each polynomials and combine them into polyOut.
    for (int i = 0; i < poly1.rows(); i++) {
        for (int j = 0; j < poly2.rows(); j++) {
            polyOut(i + j) += poly1(i) * poly2(j);
        }
    }

    return polyOut;
}