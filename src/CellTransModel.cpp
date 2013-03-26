/*
 * CellTransModel.cpp
 *
 *  Created on: 26 mars 2013
 *      Author: Edward
 */

#include "CellTransModel.h"

CellTransModel::CellTransModel() {
	// initialize the parameters
	ListCell = NULL;
	ListLink = NULL;
	CellPosIn = NULL;
	CellPosOut = NULL;
	CellIn = NULL;
	CellOut = NULL;
	err = "";
	n = 0; m = 0;
}

CellTransModel::CellTransModel(int _n, int _m) {
	// initialize the parameters
	ListCell = NULL;
	ListLink = NULL;
	CellPosIn = NULL;
	CellPosOut = NULL;
	CellIn = NULL;
	CellOut = NULL;
	err = "";
	n = 0; m = 0;
	// initialize model with n cells and m links
	initialModel(_n,_m);
}

CellTransModel::~CellTransModel() {
	if(ListCell!=NULL)
		delete ListCell;
	if(ListLink!=NULL)
		delete ListLink;
	if(CellPosIn!=NULL)
		delete CellPosIn;
	if(CellPosOut!=NULL)
		delete CellPosOut;
	if(CellIn!=NULL)
		delete CellIn;
	if(CellOut!=NULL)
		delete CellOut;
}

void CellTransModel::resetModel() {
	if(ListCell!=NULL) {
		delete ListCell;
		ListCell = NULL;
	}
	if(ListLink!=NULL) {
		delete ListLink;
		ListLink = NULL;
	}
	if(CellPosIn!=NULL) {
		delete CellPosIn;
		CellPosIn = NULL;
	}
	if(CellPosOut!=NULL) {
		delete CellPosOut;
		CellPosOut = NULL;
	}
	if(CellIn!=NULL) {
		delete CellIn;
		CellIn = NULL;
	}
	if(CellOut!=NULL) {
		delete CellOut;
		CellOut = NULL;
	}
	err = "";
	n = 0; m = 0;
}

bool CellTransModel::initialModel(int _n, int _m, double _cap, double _s) {
	if (_n<=0 || _m<=0)
		return false;
	resetModel();
	n = _n; _m = m;
	ListCell = new CELL[n];
	ListLink = new LINK[m];
	CellPosIn = new double[n];
	CellPosOut = new double[n];
	CellIn = new double[n];
	CellOut = new double[n];
	for (int i=0;i<n;i++) {
		ListCell[i].type = CELL_TYPE_NORMAL;
		ListCell[i].capacity = _cap;
		ListCell[i].length = 0;
		ListCell[i].rate = _s;
		ListCell[i].access = 1;
		CellPosIn[i] = 0;
		CellPosOut[i] = 0;
		CellIn[i] = 0;
		CellOut[i] = 0;
	}
	for (int i=0;i<m;i++) {
		ListLink[i].type = LINK_TYPE_STRAIGHT;
		ListLink[i].c1 = 0;
		ListLink[i].c2 = 0;
		ListLink[i].c3 = 0;
		ListLink[i].p = 0.5;
	}
	return true;
}
