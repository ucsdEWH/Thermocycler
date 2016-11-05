/*
 * PID.cpp
 *
 *  Created on: Sep 5, 2011
 *      Author: rbtying
 */

#include "PID.h"

PID::PID(PID_params * p) {
	m_param = p;
}

void PID::setInput(double in) {
	m_param->input = in;
}



void PID::setSetPoint(double set){
	
	m_param->set=set;

}
void PID::setProportional(double proportional){
	m_param->proportional = proportional;
}
void PID::setIntegral(double integral){
	m_param->integral = integral;
}
void PID::setDerivative(double derivative){
	m_param->derivative = derivative;
}
void PID::setAccLimit(double accLimit){
	m_param->accLimit = accLimit;
}
double PID::getOutput() {
	return m_param->output;
}

void PID::clearPID() {
	m_param->error = 0;
	m_param->previous = 0;
	m_param->accumulated = 0;
	m_param->input = 0;
	m_param->output = 0;
}

void PID::process(double dt) {
	// calculate the error
	m_param->error = m_param->set - m_param->input;

	// integrate the error using Riemann sum
	m_param->accumulated += m_param->error * dt;

	// limit the integrated error to +/- accLimit
	if (m_param->accumulated > m_param->accLimit) {
		m_param->accumulated = m_param->accLimit;
	} else if (m_param->accumulated < -m_param->accLimit) {
		m_param->accumulated = -m_param->accLimit;
	}

	// do the actual PID calculation
	m_param->output = m_param->proportional * m_param->error
			+ m_param->integral * m_param->accumulated + m_param->derivative
			* (m_param->error - m_param->previous) / dt;

	// save the current error for next time to caluclate derivative
	m_param->previous = m_param->error;
}
