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
    vector<CtmCell *> list_cells;
    vector<CtmLink *> list_links;
    vector<double> list_pos_in,list_pos_out,list_in,list_out;
    CtmInfo info;
    vector<CtmLane *> list_lanes;
    vector<CtmIntersection *> list_ints;
public:
    CellTransModel();
    virtual ~CellTransModel();
    bool sim(double dt, int steps=1);
    void resetSystem(double vf, double w, double veh_len, double pos_dt);
    int addLane(int type, double cap,
            double sat_rate, double in_rate, double out_ratio);
    int addIntersection(int n_in,int *in_lanes,
            int n_out,int *out_lanes,
            int n_inner,double **inner_cells);
    bool addPhase(int index,int n_links,double info[][8]);
    bool buildCTM();
    bool checkCells();
    bool checkPhases();
    bool startSim();
    bool setLaneQueue(int i,double x);
    bool setIntersectionPhase(int i,int p);
    bool startSim(const vector<double> &x,const vector<int> &p);
    bool stopSim();
    bool cleanAllCells();
    bool addInputs(const vector<double> &in);
    bool modifyLaneInRate(int i,double r);
    bool modifyLaneSatRate(int i,double r);
    bool modifyLaneOutRatio(int i,double r);
    bool switchIntersection(int i);
    bool readCells(vector<double> &tar);
    bool readLanes(vector<double> &tar);
    bool readPhases(vector<int> &tar);
    bool readLaneDelays(vector<double> &tar);
    double readTotalDelay();
    void resetDelay();
private:
    void calPosFlows(double dt);
    void calRealFlows();
    bool updateCells(double dt);
    double min(double d1, double d2);
    double mid(double d1, double d2, double d3);
    void modelingLane(CtmLane *l);
    void modelingIntersection(CtmIntersection *l);
};

#endif /* CELLTRANSMODEL_H_ */
