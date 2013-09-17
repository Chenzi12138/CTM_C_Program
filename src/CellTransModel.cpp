/*
 * CellTransModel.cpp
 *
 *  Created on: 26 mars 2013
 *      Author: Edward
 */

#include "CellTransModel.h"
#include <iostream>
#include <limits>
using namespace std;

CellTransModel::CellTransModel() {
    // initialize the parameters
    list_cells = NULL;
    list_links = NULL;
    list_pos_in = NULL;
    list_pos_out = NULL;
    list_in = NULL;
    list_out = NULL;
    n_cells = 0;
    n_links = 0;
    info.is_valid = false;
    info.is_sim_on = false;
    info.vf = 10;
    info.w_vf = 1;
    info.veh_len = 5;
    info.cell_cap = 2;
}
//
//CellTransModel::CellTransModel(int _n) {
//    // initialize the parameters
//    ListCell = NULL;
//    ListLink = NULL;
//    CellPosIn = NULL;
//    CellPosOut = NULL;
//    CellIn = NULL;
//    CellOut = NULL;
//    err = "";
//    n = 0;
//    isSimOn = false;
//    // initialize model with n cells and m links
//    initialModel(_n);
//}
//
CellTransModel::~CellTransModel() {
    if(list_cells!=NULL)
        delete list_cells;
    if(list_links!=NULL)
        delete list_links;
    if(list_pos_in!=NULL)
        delete list_pos_in;
    if(list_pos_out!=NULL)
        delete list_pos_out;
    if(list_in!=NULL)
        delete list_in;
    if(list_out!=NULL)
        delete list_out;
}
//
//void CellTransModel::resetModel() {
//    if(ListCell!=NULL) {
//        delete ListCell;
//        ListCell = NULL;
//    }
//    if(ListLink!=NULL) {
//        delete ListLink;
//        ListLink = NULL;
//    }
//    if(CellPosIn!=NULL) {
//        delete CellPosIn;
//        CellPosIn = NULL;
//    }
//    if(CellPosOut!=NULL) {
//        delete CellPosOut;
//        CellPosOut = NULL;
//    }
//    if(CellIn!=NULL) {
//        delete CellIn;
//        CellIn = NULL;
//    }
//    if(CellOut!=NULL) {
//        delete CellOut;
//        CellOut = NULL;
//    }
//    err = "";
//    n = 0;
//    isSimOn = false;
//}
//
//bool CellTransModel::initialModel(int _n, double _cap, double _s) {
//    if (_n<=0) {
//        err = "Non-positive number of cells!";
//        return false;
//    }
//    resetModel();
//    n = _n;
//    ListCell = new CELL[n];
//    ListLink = new LINK[n];
//    CellPosIn = new double[n];
//    CellPosOut = new double[n];
//    CellIn = new double[n];
//    CellOut = new double[n];
//    for (int i=0;i<n;i++) {
//        ListCell[i].type = CELL_TYPE_NORMAL;
//        ListCell[i].capacity = _cap;
//        ListCell[i].length = 0;
//        ListCell[i].rate = _s;
//        ListCell[i].access = 1;
//        CellPosIn[i] = 0;
//        CellPosOut[i] = 0;
//        CellIn[i] = 0;
//        CellOut[i] = 0;
//        ListLink[i].p = 1;
//        ListLink[i].c1 = (i-1)>=0?(i-1):0;
//        ListLink[i].c2 = 0;
//        ListLink[i].p1 = 1;
//        ListLink[i].p2 = 0;
//    }
//    return true;
//}
//
//bool CellTransModel::setCell(int i, int _type, double _cap, double _s) {
//    if(n==0) {
//        err = "No cell in the model yet!";
//        return false;
//    }
//    if (i>=n || i<0) {
//        err = "Wrong index of cell!";
//        return false;
//    }
//    if (_s<=0) {
//        err = "Negative maximal flow rate!";
//        return false;
//    }
//    switch (_type) {
//    case CELL_TYPE_INPUT:
//        ListCell[i].type = _type;
//        ListCell[i].rate = _s;
//        break;
//    case CELL_TYPE_OUTPUT:
//        ListCell[i].type = _type;
//        ListCell[i].rate = _s;
//        break;
//    case CELL_TYPE_SWITCH:
//        if (_cap<=0) {
//            err = "Negative capacity of cell!";
//            return false;
//        }
//        ListCell[i].type = _type;
//        ListCell[i].capacity = _cap;
//        ListCell[i].rate = _s;
//        break;
//    case CELL_TYPE_NORMAL:
//    default:
//        if (_cap<=0) {
//            err = "Negative capacity of cell!";
//            return false;
//        }
//        ListCell[i].type = CELL_TYPE_NORMAL;
//        ListCell[i].capacity = _cap;
//        ListCell[i].rate = _s;
//        break;
//    }
//    return true;
//}
//
//bool CellTransModel::setLink(int i, double _p, int _c1, double _p1, int _c2, double _p2) {
//    if(n==0) {
//        err = "No link in the model yet!";
//        return false;
//    }
//    if (i>=n || i<0) {
//        err = "Wrong index of link!";
//        return false;
//    }
//    if (_p<=0 || _p>1 || _p1<=0 || _p1>1 || _p2<0 || _p2>1) {
//        err = "Wrong proportion!";
//        return false;
//    }
//    if (_c1<0 || _c1>=n || _c2<0 || _c2>=n) {
//        err = "Wrong index of input cell(s)!";
//        return false;
//    }
//    ListLink[i].p = _p;
//    ListLink[i].c1 = _c1;
//    ListLink[i].p1 = _p1;
//    ListLink[i].c2 = _c2;
//    ListLink[i].p2 = _p2;
//    return true;
//}
//
//bool CellTransModel::startSim(double const _len[], int const _acc[]) {
//    if (n==0) {
//        err = "No cell and/or link in the model yet!";
//        return false;
//    }
//    if (isSimOn) {
//        err = "The Simulation was started!";
//        return false;
//    }
//    for (int i=0;i<n;i++) {
//        switch (ListCell[i].type) {
//        case CELL_TYPE_INPUT:
//        case CELL_TYPE_OUTPUT:
//            ListCell[i].length = 0;
//            break;
//        case CELL_TYPE_SWITCH:
//        case CELL_TYPE_NORMAL:
//        default:
//            if (_len[i]<0) {
//                ostringstream oss;
//                oss << "Negative length of Cell " << i << "!";
//                err = oss.str();
//                return false;
//            }
//            else if (_len[i]>ListCell[i].capacity) {
//                ostringstream oss;
//                oss << "Over the capacity of Cell " << i << "!";
//                err = oss.str();
//                return false;
//            }
//            ListCell[i].length = _len[i];
//            break;
//        }
//        if (ListCell[i].type==CELL_TYPE_SWITCH) {
//            if(_acc[i]!=0)
//                ListCell[i].access = 1;
//            else
//                ListCell[i].access = 0;
//        }
//    }
//    isSimOn = true;
//    return true;
//}
//
//bool CellTransModel::changeAccess(int i, int _acc) {
//    if (i>=n || i<0) {
//        err = "Wrong index of cell!";
//        return false;
//    }
//    else if (ListCell[i].type != CELL_TYPE_SWITCH) {
//        err = "This cell is not controlled by signals!";
//        return false;
//    }
//    if (_acc!=0)
//        ListCell[i].access = 1;
//    else
//        ListCell[i].access = 0;
//    return true;
//}
//
//bool CellTransModel::changeAccesses(int const _acc[]) {
//    if(n==0) {
//        err = "No cell in the model yet!";
//        return false;
//    }
//    for (int i=0;i<n;i++) {
//        if (ListCell[i].type == CELL_TYPE_SWITCH) {
//            if (_acc[i]!=0)
//                ListCell[i].access = 1;
//            else
//                ListCell[i].access = 0;
//        }
//    }
//    return true;
//}
//
//bool CellTransModel::getCurrentLengths(double _len[]) {
//    if(n==0) {
//        err = "No cell in the model yet!";
//        return false;
//    }
//    for (int i=0;i<n;i++) {
//        _len[i] = ListCell[i].length;
//    }
//    return true;
//}
//
bool CellTransModel::sim(double dt, int steps) {
    if (!info.is_sim_on) {
//        err = "The Simulation has not been started!";
        return false;
    }
    if (dt<=0) {
//        err = "Non-positive interval!";
        return false;
    }
    if (steps<=0) {
//        err = "Non-positive steps!";
        return false;
    }
    for (int i=0;i<steps;i++) {
        calPosFlows(dt);
        calRealFlows();
        if(!updateCells(dt))
            return false;
    }
    return true;
}
//
//void CellTransModel::stopSim() {
//    isSimOn = false;
//}
//
//bool CellTransModel::resumeSim() {
//    if (n==0) {
//        err = "No cell and/or link in the model yet!";
//        return false;
//    }
//    if (isSimOn) {
//        err = "The Simulation was started!";
//        return false;
//    }
//    isSimOn = true;
//    return true;
//}
//
void CellTransModel::calPosFlows(double dt) {
    for (int i=0;i<n_cells;i++) {
        list_in[i] = 0;
        list_out[i] = 0;
        switch (list_cells[i].type) {
        case CELL_TYPE_INPUT:
            list_pos_in[i] = 0;
            list_cells[i].length += list_cells[i].rate*dt;
            list_pos_out[i] = list_cells[i].length;
            break;
        case CELL_TYPE_OUTPUT:
            list_pos_in[i] = std::numeric_limits<double>::max();
            list_pos_out[i] = 0;
            break;
        case CELL_TYPE_NORMAL:
        default:
            double maxFlow = list_cells[i].rate*dt;
            list_pos_in[i] = min(maxFlow,info.w_vf*(list_cells[i].cap-list_cells[i].length));
            list_pos_out[i] = min(maxFlow,list_cells[i].length);
            break;
        }
    }
}

double CellTransModel::min(double d1, double d2) {
    if (d1<d2)
        return d1;
    else
        return d2;
}

void CellTransModel::calRealFlows() {
    for (int i=0;i<n_links;i++) {
        if(list_links[i].access) {
        	int c1 = list_links[i].cells[0], c2 = list_links[i].cells[1], c3 = list_links[i].cells[2];
        	double b1 = list_links[i].ratio; double b2 = 1-b1;
            double f1,f2;
            switch (list_links[i].type) {
            case LINK_TYPE_MERGE:
                if (list_pos_in[c3]>=list_pos_out[c1]+list_pos_out[c2]) {
                    f1 = list_pos_out[c1];
                    f2 = list_pos_out[c2];
                }
                else {
                    f1 = mid(list_pos_out[c1],list_pos_in[c3]-list_pos_out[c2],b1*list_pos_in[c3]);
                    f2 = mid(list_pos_out[c2],list_pos_in[c3]-list_pos_out[c1],b2*list_pos_in[c3]);
                }
				list_out[c1] = f1;
				list_out[c2] = f2;
				list_in[c3] = f1+f2;
                break;
            case LINK_TYPE_DIVERGE:
            	f1 = min(list_pos_out[c1],min(list_pos_in[c2]/b1,list_pos_in[c3]/b2));
            	list_out[c1] = f1;
            	list_in[c2] = f1*b1;
            	list_in[c3] = f1*b2;
                break;
            case LINK_TYPE_DIRECT:
            default:
            	f1 = min(list_pos_out[c1],list_pos_in[c2]);
            	list_out[c1] = f1;
            	list_in[c2] = f1;
                break;
            }
        }
    }
}

double CellTransModel::mid(double d1, double d2, double d3) {
    if (d1<=d2) {
        if (d2<=d3)
            return d2;
        else {
            if (d1<=d3)
                return d3;
            else
                return d1;
        }
    }
    else {
        if (d1<=d3)
            return d1;
        else {
            if (d2<=d3)
                return d3;
            else
                return d2;
        }
    }
}

bool CellTransModel::updateCells(double dt) {
    for (int i=0;i<n_cells;i++) {
        if (list_in[i]>list_pos_in[i]+1e-6 || list_out[i]>list_pos_out[i]+1e-6) {
//            ostringstream oss;
//            oss << "Simulation failed with unknown reason in Cell " << i << "!";
//            err = oss.str();
            return false;
        }
        list_cells[i].length += list_in[i]-list_out[i];
        list_cells[i].delay += dt*(list_cells[i].length-list_out[i]*list_cells[i].cap*info.veh_len/info.vf);
    }
    return true;
}
//
//void CellTransModel::print() {
//    for (int i=0;i<n;i++) {
//        cout << "Cell " << i+1 << ": ";
//        cout << "cap " << ListCell[i].capacity << "\t";
//        cout << "length " << ListCell[i].length << "\t";
//        cout << "last in " << CellIn[i] << "\t";
//        cout << "last out " << CellOut[i] << endl;
//    }
//}
