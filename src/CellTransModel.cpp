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
//    list_cells = NULL;
//    list_links = NULL;
//    list_pos_in = NULL;
//    list_pos_out = NULL;
//    list_in = NULL;
//    list_out = NULL;
//    n_cells = 0;
//    n_links = 0;
//    info.is_valid = false;
//    info.is_sim_on = false;
//    info.vf = 10;
//    info.w_vf = 1;
//    info.veh_len = 5;
//    info.cell_cap = 2
	resetSystem(10,10,5,1);
}

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

	for (int i=0;i<(int)list_lanes.size();i++)
		delete list_lanes[i];
	list_lanes.clear();

	for (int i=0;i<(int)list_ints.size();i++)
		delete list_ints[i];
	list_ints.clear();
}

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

void CellTransModel::resetSystem(double vf,
		double w,
		double veh_len,
		double pos_dt) {
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
	n_cells = 0;
	n_links = 0;

	info.is_valid = false;
	info.is_sim_on = false;
	info.vf = vf;
	info.w_vf = w/vf;
	info.veh_len = veh_len;
	info.cell_cap = vf*pos_dt/veh_len;

	for (int i=0;i<(int)list_lanes.size();i++)
		delete list_lanes[i];
	list_lanes.clear();

	for (int i=0;i<(int)list_ints.size();i++)
		delete list_ints[i];
	list_ints.clear();
}

int CellTransModel::addLane(int type,
		double cap,
		double sat_rate,
		double in_rate,
		double out_ratio) {
	if (info.is_sim_on) {
		return -1;
	}

	CtmLane * l = new CtmLane();
	l->type = type;
	bool isValid = false;
	switch (type) {
	case LANE_TYPE_NORMAL:
		if (cap<=0)
			break;
		else if (sat_rate <= 0)
			break;
		else if (in_rate < 0)
			break;
		else if (out_ratio<0 || out_ratio>1)
			break;
		isValid = true;
		l->cap = cap;
		l->sat_rate = sat_rate;
		l->in_rate = in_rate;
		l->out_ratio = out_ratio;
		break;
	case LANE_TYPE_ENTRY:
		if (cap<=0)
			break;
		else if (sat_rate <= 0)
			break;
		else if (in_rate < 0)
			break;
		isValid = true;
		l->cap = cap;
		l->sat_rate = sat_rate;
		l->in_rate = in_rate;
		l->out_ratio = 0;
		break;
	case LANE_TYPE_EXIT:
		isValid = true;
		l->cap = 0;
		l->sat_rate = std::numeric_limits<double>::max();
		l->in_rate = 0;
		l->out_ratio = 1;
		break;
	default:
		break;
	}

	if (isValid) {
		list_lanes.push_back(l);
		info.is_valid = false;
		return list_lanes.size()-1;
	}
	else {
		delete l;
		return -1;
	}
}

int CellTransModel::addIntersection(int n_in,int *in_lanes,
            int n_out,int *out_lanes,
            int n_inner,double **inner_cells) {
	if (info.is_sim_on) {
			return -1;
		}

	CtmIntersection * l = new CtmIntersection();
	for (int i=0;i<n_in;i++)
		l->in_lanes.push_back(list_lanes[in_lanes[i]]);
	for (int i=0;i<n_out;i++)
		l->out_lanes.push_back(list_lanes[out_lanes[i]]);
	for (int i=0;i<n_inner;i++) {
		CtmInnerCell * c = new CtmInnerCell(inner_cells[i][0],inner_cells[i][1]);
		l->inner_cells.push_back(c);
	}

	list_ints.push_back(l);
	info.is_valid = false;
	return list_ints.size()-1;
}
