#ifndef ESTIMATION_METHOD_TYPE_H_
#define ESTIMATION_METHOD_TYPE_H_
/**
 * \file estimationMethodType.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 */

/**
 * Helper namespace to hide EstimationMethodType enum from global context.
 */

namespace EstimationMethodType {

/** 
 * \brief Estimation Method Type 
 * Estimation Method Type 
 */
enum EstimationMethodType {
    /** 
     * \brief RANSAC 
     * RANSAC 
     */
    RANSAC = 0,
    /** 
     * \brief Iterative 
     * Iterative 
     */
    ITERATIVE = 1,
    /** 
     * \brief Manual 
     * Manual 
     */
    MANUAL = 2,
    /** 
     * \brief Last virtual option to run cycles to
     */
    ESTIMATION_METHOD_TYPE_LAST
};

} //namespace EstimationMethodType

#endif  //ESTIMATION_METHOD_TYPE_H_
