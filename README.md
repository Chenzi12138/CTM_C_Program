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

*cell* struct | description
:-------------|:----------------------------------------
type:int      | type of cell (normal;input;output)
rate:double   | saturated flow rate (veh/s)
cap:double    | capacity (veh)
length:double | current number of vehicles within (veh)
delay:double  | accumulated vehicle delay (veh*s)

*link* struct | description
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

