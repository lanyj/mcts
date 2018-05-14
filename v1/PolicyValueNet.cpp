#include "PolicyValueNet.h"


double* PolicyValueNet::softmax(double* x, int length) {
	double max = x[0];
	for (int i = 0; i < length; i++) {
		if (max < x[i]) {
			max = x[i];
		}
	}
	double *tmp = new double[length];
	for (int i = 0; i < length; i++) {
		tmp[i] = exp(x[i]);
	}
	return 0;
}

double* PolicyValueNet::relu(double* x, int length) {
	double max = x[0];
	for (int i = 0; i < length; i++) {
		if (max < x[i]) {
			max = x[i];
		}
	}
	double *tmp = new double[length];
	for (int i = 0; i < length; i++) {
		tmp[i] = exp(x[i]);
	}
	return 0;
}

PolicyValueNet::PolicyValueNet()
{
}


PolicyValueNet::~PolicyValueNet()
{
}
