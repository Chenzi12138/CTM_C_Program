/*
 * ctm_base.h
 *
 *  Created on: August 29th, 2013
 *      Author: ZHOU, Huide
 */

#ifndef CTM_BASE_H_
#define CTM_BASE_H_
#include <vector>
using namespace std;

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

#define LANE_TYPE_NORMAL 0
#define LANE_TYPE_ENTRY 1
#define LANE_TYPE_EXIT 2

class CtmLane {
public:
	int type;
	double cap;
	double sat_rate;
	double in_rate;
	double out_ratio;
	int in_cell;
	int out_cell;
	int o_cell;
	int d_cell;
	int in_link;
	int out_link;
};

class CtmInnerCell {
public:
	double cap;
	double sat_rate;
	int index;
	CtmInnerCell() {
		cap = 0; sat_rate = 0; index = 0;
	}
	CtmInnerCell(double _cap,double _rate) {
		cap = _cap;
		sat_rate = _rate;
		index = 0;
	}
};

class CtmPhase {
public:
	int info[7];
	int head;
	int tail;
};

class CtmIntersection {
public:
	vector<CtmLane *> in_lanes;
	vector<CtmLane *> out_lanes;
	int num_cells;
	vector<CtmInnerCell *> inner_cells;
	vector<CtmPhase *> phases;
	int cur_phase;
	vector<int> in_cells;
	vector<int> out_cells;
	~CtmIntersection() {
		for (int i=0;i<(int)inner_cells.size();i++)
			delete inner_cells[i];
		inner_cells.clear();
		for (int i=0;i<(int)phases.size();i++)
			delete phases[i];
		phases.clear();
	}
};

#endif /* CTM_BASE_H_ */
