/*
 * ctm_base.h
 *
 *  Created on: August 29th, 2013
 *      Author: ZHOU, Huide
 */

#ifndef CTM_BASE_H_
#define CTM_BASE_H_

#define CELL_TYPE_NORMAL 0
#define CELL_TYPE_INPUT 1
#define CELL_TYPE_OUTPUT 2

typedef struct ctm_cell {
	int type;
	double rate;
	int cap;
	double length;
	double pos_in, pos_out;
	double in, out;
}CtmCell;

#define LINK_TYPE_STRAIGHT 0
#define LINK_TYPE_MERGE 1
#define LINK_TYPE_DIVERGE 2

typedef struct ctm_link {
	int type;
	CtmCell * cells[3];
	double p;
	bool access;
}CtmLink;

class CtmInfo {
public:
	static double w_vf;
	static bool isSimOn;
};
double CtmInfo::w_vf = 1;
bool CtmInfo::isSimOn = false;

#endif /* CTM_BASE_H_ */
