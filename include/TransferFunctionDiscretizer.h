#ifndef TRANSFERFUNCTIONDISCRETIZER_H
#define TRANSFERFUNCTIONDISCRETIZER_H

#include "ContinuousTransferFunction.h"
#include <Eigen/Dense>

using Eigen::VectorXd;

/**
 * This class is intended to be used with the FilteredVar to filter a signal with a desired causal transfer function.
 * The TransferFunctionDiscretizer creates a discrete filter from a continuous transfer function representation:
 * <pre>
 * G(s) = k * (b_0*s^m + b_1*s^{m-1} + ... + b_{m-1}*s + b_m)/(a_0*s^n + a_1*s^{n-1} + ... + a_{n-1}*s + a_n)
 * </pre>
 * Where n >= m for the transfer function to be causal. This class does not check whether your desired transfer function is stable.
 * More details can be found in the docs.
 *
 * @author Connor Herron
 */
class TransferFunctionDiscretizer 
{
    public:
        // Constructors.
        TransferFunctionDiscretizer(ContinuousTransferFunction tf, int sampleFrequency) : TransferFunctionDiscretizer(tf.getName(), tf, sampleFrequency) {};
        TransferFunctionDiscretizer(std::string name, ContinuousTransferFunction tf, int sampleFrequency);
        
        // Destructor.
        ~TransferFunctionDiscretizer(){};

        // Getters.
        VectorXd getInputCoefficients() {
            return m_inputCoefficients;
        }
        VectorXd getOutputCoefficients() {
            return m_outputCoefficients;
        }
        VectorXd getName() {
            return m_name;
        }

    private:
        std::string m_name;
        VectorXd m_inputCoefficients{};
        VectorXd m_outputCoefficients{};
        int m_sampleFrequency;
        void buildFilter();

}

#endif // TRANSFERFUNCTIONDISCRETIZER_H