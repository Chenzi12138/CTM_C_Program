/*
 * CellTransModel.h
 *
 *  Created on: 26 mars 2013
 *      Author: Edward
 */

#ifndef CELLTRANSMODEL_H_
#define CELLTRANSMODEL_H_
#include <string>
using namespace std;

#define CELL_TYPE_NORMAL 0
#define CELL_TYPE_INPUT 1
#define CELL_TYPE_OUTPUT 2
#define CELL_TYPE_SWITCH 1

typedef struct Cell {
	int type;
	double capacity;
	double length;
	double rate;
	int access;
}CELL;

#define LINK_TYPE_STRAIGHT 0
#define LINK_TYPE_MERGE 1
#define LINK_TYPE_DIVERGE 2

typedef struct Link {
	int type;
	int c1,c2,c3;
	double p;
}LINK;

class CellTransModel {
private:
	CELL *ListCell;
	LINK *ListLink;
	double *CellPosIn;
	double *CellPosOut;
	double *CellIn;
	double *CellOut;
	int n,m;
	string err;
public:
	CellTransModel();
	CellTransModel(int _n, int _m);
	virtual ~CellTransModel();
	string getErr() const {return err;}
	void cleanErr() {err="";}
	string getErrClean() {
		string t = err;
		err = "";
		return t;
	}
	void resetModel();
	bool initialModel(int _n, int _m, double _cap=10, double _s=0.5);
};

#endif /* CELLTRANSMODEL_H_ */
