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
	isSimOn = false;
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
	isSimOn = false;
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
	isSimOn = false;
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

bool CellTransModel::setCell(int i, int _type, double _cap, double _s) {
	if(n==0) {
		err = "No cell in the model yet!";
		return false;
	}
	if (i>=n || i<0) {
		err = "Wrong index of cell!";
		return false;
	}
	if (_s<=0) {
		err = "Negative maximal flow rate!";
		return false;
	}
	switch (_type) {
	case CELL_TYPE_INPUT:
		ListCell[i].type = _type;
		ListCell[i].rate = _s;
		break;
	case CELL_TYPE_OUTPUT:
		ListCell[i].type = _type;
		ListCell[i].rate = _s;
		break;
	case CELL_TYPE_SWITCH:
		if (_cap<=0) {
			err = "Negative capacity of cell!";
			return false;
		}
		ListCell[i].type = _type;
		ListCell[i].capacity = _cap;
		ListCell[i].rate = _s;
		break;
	case CELL_TYPE_NORMAL:
	default:
		if (_cap<=0) {
			err = "Negative capacity of cell!";
			return false;
		}
		ListCell[i].type = CELL_TYPE_NORMAL;
		ListCell[i].capacity = _cap;
		ListCell[i].rate = _s;
		break;
	}
	return true;
}

bool CellTransModel::setLinks(int const _type[],
                                  int const _cells[][],
                                  double const _p[]) {
	if (m==0) {
		err = "No link in the model yet!";
		return false;
	}
	for (int i=0;i<m;i++) {
		switch (_type[i]) {
		case LINK_TYPE_MERGE:
		case LINK_TYPE_DIVERGE:
			if (_cells[i][0]<0 || _cells[i][1]<0 || _cells[i][2]<0) {
				err = "Negative cell index in link "+i+"!";
				return false;
			}
			if (_cells[i][0]>=n || _cells[i][1]>=n || _cells[i][2]>=n) {
				err = "Too large cell index in link "+i+"!";
				return false;
			}
			if (_p[i]<=0 || _p[i]>1) {
				err = "Wrong proportion in link "+i+"!";
				return false;
			}
			ListLink[i].type = _type[i];
			ListLink[i].c1 = _cells[i][0];
			ListLink[i].c2 = _cells[i][1];
			ListLink[i].c3 = _cells[i][2];
			ListLink[i].p = _p[i];
			break;
		case LINK_TYPE_STRAIGHT:
		default:
			if (_cells[i][0]<0 || _cells[i][1]<0) {
				err = "Negative cell index in link "+i+"!";
				return false;
			}
			if (_cells[i][0]>=n || _cells[i][1]>=n) {
				err = "Too large cell index in link "+i+"!";
				return false;
			}
			ListLink[i].type = LINK_TYPE_STRAIGHT;
			ListLink[i].c1 = _cells[i][0];
			ListLink[i].c2 = _cells[i][1];
			break;
		}
	}
	return true;
}

bool CellTransModel::setLinkProportion(int i, double _p) {
	if (m==0) {
		err = "No link in the model yet!";
		return false;
	}
	if (i>=m || i<0) {
		err = "Wrong index of link!";
		return false;
	}
	if (_p<=0 || _p>1) {
		err = "Wrong proportion of link!";
		return false;
	}
	ListLink[i].p = _p[i];
	return true;
}

bool CellTransModel::startSim(double const _len[], int const _acc[]) {
	if (n==0 || m==0) {
		err = "No cell and/or link in the model yet!";
		return false;
	}
	if (isSimOn) {
		err = "The Simulation had been started!";
		return false;
	}
	for (int i=0;i<n;i++) {
		switch (ListCell[i].type) {
		case CELL_TYPE_INPUT:
		case CELL_TYPE_OUTPUT:
			ListCell[i].length = 0;
			break;
		case CELL_TYPE_SWITCH:
		case CELL_TYPE_NORMAL:
		default:
			if (_len[i]<0) {
				err = "Negative length of cell "+i+"!";
				return false;
			}
			else if (_len[i]>ListCell[i].capacity) {
				err = "Negative length of cell "+i+"!";
				return false;
			}
			ListCell[i].length = _len[i];
			break;
		}
		if (ListCell[i].type==CELL_TYPE_SWITCH) {
			if(_acc[i]!=0)
				ListCell[i].access = 1;
			else
				ListCell[i].access = 0;
		}
	}
	isSimOn = true;
	return true;
}

bool CellTransModel::changeAccess(int i, int _acc) {
	if (i>=n || i<0) {
		err = "Wrong index of cell!";
		return false;
	}
	else if (ListCell[i].type != CELL_TYPE_SWITCH) {
		err = "This cell is not controlled by signals!";
		return false;
	}
	if (_acc!=0)
		ListCell[i].access = 1;
	else
		ListCell[i].access = 0;
	return true;
}

bool CellTransModel::changeAccesses(int const _acc[]) {

}
