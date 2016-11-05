/*
 * PID.h
 *
 *  Created on: Sep 5, 2011
 *      Author: rbtying
 */

#ifndef PID_H_
#define PID_H_

struct PID_params {
	double set;
	double input;
	double output;
	double accumulated;
	double previous;
	double error;

	double proportional;
	double integral;
	double derivative;

	double accLimit;
};

typedef struct PID_params PID_params;

class PID {
public:
	PID(PID_params * p);
	void setInput(double in);
	
	void setSetPoint(double set);
	double getOutput();
	void clearPID();
	void process(double dt);


	void setProportional(double proportional);
	void setIntegral(double integral);
	void setDerivative(double derivative);
	void setAccLimit(double accLimit);

private:
	PID_params * m_param;
};

#endif /* PID_H_ */
