/*
 * CellTransModel.h
 *
 *  Created on: 26 mars 2013
 *      Author: Edward
 */

#ifndef CELLTRANSMODEL_H_
#define CELLTRANSMODEL_H_
#include <string>
#include <sstream>
#include "ctm_base.h"
using namespace std;

class CellTransModel {
private:
	CtmCell *list_cells;
	CtmLink *list_links;
	int n_cells,n_links;
	double *list_pos_in,*list_pos_out,*list_in,*list_out;
	CtmInfo info;
	vector<CtmLane *> list_lanes;
	vector<CtmIntersection *> list_ints;
public:
	CellTransModel();
	virtual ~CellTransModel();
	bool sim(double dt, int steps=1);
	void resetSystem(double vf, double w, double veh_len, double pos_dt);
	bool addLane(int type, double cap, double sat_rate, double in_rate, double out_ratio);
private:
	void calPosFlows(double dt);
	void calRealFlows();
	bool updateCells(double dt);
	double min(double d1, double d2);
	double mid(double d1, double d2, double d3);
};

#endif /* CELLTRANSMODEL_H_ */
