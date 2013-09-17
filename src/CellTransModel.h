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

//#define CELL_TYPE_NORMAL 0
//#define CELL_TYPE_INPUT 1
//#define CELL_TYPE_OUTPUT 2
//#define CELL_TYPE_SWITCH 3

//typedef struct Cell {
//	int type;
//	double capacity;
//	double length;
//	double rate;
//	int access;
//}CELL;

//#define LINK_TYPE_STRAIGHT 0
//#define LINK_TYPE_MERGE 1
//#define LINK_TYPE_DIVERGE 2

//typedef struct Link {
//	double p;
//	int c1;
//	double p1;
//	int c2;
//	double p2;
//}LINK;

class CellTransModel {
private:
	CtmCell *list_cells;
	CtmLink *list_links;
	int n_cells,n_links;
	double *list_pos_in,*list_pos_out,*list_in,*list_out;
	CtmInfo info;
public:
	CellTransModel();
	virtual ~CellTransModel();
//	void resetModel();
//	bool initialModel(int _n, double _cap=10, double _s=0.5);
//	bool setCell(int i, int _type, double _cap, double _s);
//	bool setLink(int i, double _p, int _c1, double _p1=1, int _c2=0, double _p2=0);
//	bool startSim(double const _len[], int const _acc[]);
	bool sim(double dt, int steps=1);
//	bool changeAccess(int i, int _acc);
//	bool changeAccesses(int const _acc[]);
//	bool getCurrentLengths(double _len[]);
//	void stopSim();
//	bool resumeSim();
//	void print();
private:
	void calPosFlows(double dt);
	void calRealFlows();
	bool updateCells(double dt);
	double min(double d1, double d2);
	double mid(double d1, double d2, double d3);
};

#endif /* CELLTRANSMODEL_H_ */
