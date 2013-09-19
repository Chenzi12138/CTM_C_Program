# CTM_C_Program

Implementation of CTM by C++ Language

### lane-intersection structure

The previous version builds the model directly on the cell-link level, which makes it hard to scale.
To solve it, the new version will focus on the lane-intersection level.
During the operations on the lanes and the intersections, the related cells and links are automatically created or modified.

Another difference with the previous version is that the `access` field is transferred from `cell` to `link`,
so that the model can handle more complicated phases.

### lower-level

**Data Structure**

*cell*        |
:-------------|:----------------------------------------
type:int      | type of cell (normal;input;output)
rate:double   | saturated flow rate (veh/s)
cap:double    | capacity (veh)
length:double | current number of vehicles within (veh)
delay:double  | accumulated vehicle delay (veh*s)

*link*        |
:-------------|:------------------------------------
type:int      | type of link (direct;merge;diverge)
cells:int\[3] | indices of two or three cells
ratio:double  | merge or diverge ratio \[0,1]
access:bool   | availability of the link

data lists:

name           | description
:--------------|:----------------------------------
`list_cells`   | list of all cells
`list_links`   | list of all links
`list_pos_in`  | the possible inputs of all cells
`list_pos_out` | the possible outputs of all cells
`list_in`      | the real inputs of all cells
`list_out`     | the real outputs of all cells

**Simulation Procedure**

- Step 1: `list_cells --> list_pos_in, list_pos_out`

    calculate the possible inputs and outputs of all cells

- Step 2: `list_pos_in, list_pos_out, list_links --> list_in, list_out`

    calculate the real inputs and outputs of all cells

- Step 3: `list_cells, list_in, list_out --> list_cells`

    update the lengths and delays of all cells

### Data Model: Lane-Intersection

**Lane**

property         | description
:----------------|:----------------------------------------------------------
type:int         | type of lane (normal;entry;exit)
cap:double       | capacity (veh)
sat_rate:double  | saturated flow rate (veh/s)
in_rate:double   | input flow rate (veh/s)
out_ratio:double | the ratio of output vehicles due to all input ones \[0,1]
in_cell:int      | index of the input cell
out_cell:int     | index of the output cell
o_cell:int       | index of the origin normal cell
d_cell:int       | index of the destination normal cell
in_link:int      | index of the input link
out_link:int     | index of the output link

**Intersection**

property                 | description
:------------------------|:-----------------------------------------------
in_lanes:`list<Lane*>`   | list of input lanes
in_cells:`list<int>`     | list of indices of end cells of input lanes
out_lanes:`list<Lane*>`  | list of output lanes
out_cells:`list<int>`    | indices of begin cells of output lanes
num_cells:`int`          | number of inner cells
cells_info:`double[][2]` | the information of the inner cells (cap, rate)
cells:`list<int>`        | indices of the inner cells
phases:`list<Phase*>`    | the information of the phases
cur_phase:int            | index of the current phase

**Phase**

property            | description
:-------------------|:--------------------------
links_info:`int[7]` | information for the phase \[type,c1\_class,c1\_index,c2\_class,c2\_index,c3\_class,c3\_index]
links:`int[2]`      | indices of related links \[begin,end]

