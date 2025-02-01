#ifndef CONTINUOUSTRANSFERFUNCTION_H
#define CONTINUOUSTRANSFERFUNCTION_H

#include <string>
#include <Eigen/Dense>

using Eigen::VectorXd;

/**
 * This class holds the representation of a continuous transfer function of the form:
 * <pre>
 * G(s) = k * (b_0*s^m + b_1*s^{m-1} + ... + b_{m-1}*s + b_m)/(a_0*s^n + a_1*s^{n-1} + ... + a_{n-1}*s + a_n)
 * </pre>
 * where numerator[] = [b_0, b_1, ..., b_{m-1}, b_m] and denominator[] = [a_0, a_1, ..., a_{n-1}, a_n]. This class can
 * be passed into the TransferFunctionDiscretizer to create a discrete representation of that transfer function
 * in the FilteredVar class.
 * In addition, two ContinuousTransferFunctions can be cascaded together to produce a new transfer function of the form
 * <pre>
 *                            N1(s)      N2(s)        N3(s)
 * H3(s) = H1(s)*H2(s) = k1 * ----- k2 * ----- = k3 * -----
 *                            D1(s)      D2(s)        D3(s)
 * </pre>
 *
 * @author Connor Herron
 */
class ContinuousTransferFunction 
{
    public:
        ContinuousTransferFunction(std::string name, double k, VectorXd numerator, VectorXd denominator) : m_name(name), m_k(k), m_denominator(denominator), m_numerator(numerator);
        ContinuousTransferFunction(std::string name, ContinuousTransferFunction severalContinuousTransferFunctions[]);
        ~ContinuousTransferFunction(){};
        
        // Cascade two transfer functions
        ContinuousTransferFunction cascadeTwoTransferFunctions(ContinuousTransferFunction H1, ContinuousTransferFunction H2);

        // Get/setters
        void setName(std::string name) {
            m_name = name;
        }
        
        std::string getName() {
            return name;
        }

        void setNumerator(VectorXd numerator) {
            m_numerator = numerator;
        }

        VectorXd getNumerator() {
            return m_numerator;
        }

        void setDenominator(VectorXd denominator) {
            m_denominator = denominator;
        }

        VectorXd getDenominator() {
            return m_denominator;
        }

        void setGain(double k) {
            m_k = k;
        }

        double getGain() {
            return m_k;
        }
    private:
        std::string m_name;       // Transfer Function Name
        double m_k;               // DC Gain
        VectorXd m_numerator;     // Numerator Coefficients
        VectorXd m_denominator;   // Denominator Coefficients
        VectorXd cascadePolynomials(VectorXd poly1, VectorXd poly2);

}

#endif // CONTINUOUSTRANSFERFUNCTION_H