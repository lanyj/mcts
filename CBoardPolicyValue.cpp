#include "CBoardPolicyValue.h"

#define LOG_E log(2.71828)
#define EPISLION 1E-6

CBoardPolicyValue::CBoardPolicyValue() {}

CBoardPolicyValue::~CBoardPolicyValue() {}

void CBoardPolicyValue::step(CBoard* board, CNode* node, CList<double>* values, double* gate) {
	*gate = 1E8;

	for (int i = node->children->size() - 1; i >= 0; i--) {
		CNode* n = node->children->get(i);
		values->set(i, sqrt(2 * log(EPISLION + n->parent->visits) / LOG_E / (EPISLION + n->visits)));
	}
}