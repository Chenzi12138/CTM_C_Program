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
	double cap;
	double length;
	double delay;
}CtmCell;

#define LINK_TYPE_DIRECT 0
#define LINK_TYPE_MERGE 1
#define LINK_TYPE_DIVERGE 2

typedef struct ctm_link {
	int type;
	int cells[3];
	double ratio;
	bool access;
}CtmLink;

class CtmInfo {
public:
	bool is_valid;
	bool is_sim_on;
	double vf;
	double w_vf;
	double veh_len;
	double cell_cap;
};

#endif /* CTM_BASE_H_ */
