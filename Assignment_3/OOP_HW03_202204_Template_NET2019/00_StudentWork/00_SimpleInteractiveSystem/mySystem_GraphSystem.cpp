//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
//********************************************
//
// Prof. Sai-Keung Wong
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/04/25
//
#include <iostream>
#include "mySystem_GraphSystem.h"
#include <time.h>
#include <limits>

using namespace std;

int Param::GRAPH_MAX_NUM_NODES = 10000;
int Param::GRAPH_MAX_NUM_EDGES = 10000;

GRAPH_SYSTEM::GRAPH_SYSTEM( )
{
    //cout << "Reset" << endl;
    reset();
    //cout << "Reset finish" << endl;
    mFlgAutoNodeDeletion = false;
    mNumPoints_DoubleCircles = 24;
    createDefaultGraph();
    //
    // Implement your own stuff
    //
}
void GRAPH_SYSTEM::initMemoryPool()
{
    mNodeArr_Pool = new GRAPH_NODE[Param::GRAPH_MAX_NUM_NODES];
    mEdgeArr_Pool = new GRAPH_EDGE[Param::GRAPH_MAX_NUM_EDGES];

    mCurNumOfActiveNodes = 0;
    mCurNumOfActiveEdges = 0;
    mActiveNodeArr = new int[Param::GRAPH_MAX_NUM_NODES];
    mActiveEdgeArr = new int[Param::GRAPH_MAX_NUM_EDGES];

    mFreeNodeArr = new int[Param::GRAPH_MAX_NUM_NODES];
    mFreeEdgeArr = new int[Param::GRAPH_MAX_NUM_EDGES];
    //
    for (int i = 0; i < Param::GRAPH_MAX_NUM_NODES; ++i) {
        mNodeArr_Pool[i].id = i; // assign a unique id
    }
    for (int i = 0; i < Param::GRAPH_MAX_NUM_EDGES; ++i) {
        mEdgeArr_Pool[i].id = i; // assign a unique id
    }
}

void GRAPH_SYSTEM::reset( )
{
    stopAutoNodeDeletion();
    //cout << "stoped" << endl;
    initMemoryPool();
    //cout << "inited" << endl;
    mPassiveSelectedNode = 0;
    mSelectedNode = 0;
    //
    // Implement your own stuff
    //
    mCurNumOfActiveNodes = 0;
    mCurNumOfActiveEdges = 0;

    mCurNumOfFreeNodes = Param::GRAPH_MAX_NUM_NODES;
    mCurNumOfFreeEdges = Param::GRAPH_MAX_NUM_EDGES;

    for (int i = 0; i < mCurNumOfFreeNodes; ++i) {
        mFreeNodeArr[i] = i; // index is not used
    }
    for (int i = 0; i < mCurNumOfFreeEdges; ++i) {
        mFreeEdgeArr[i] = i; // index is not used
    }

}

void GRAPH_SYSTEM::createDefaultGraph()
{
    reset();
    //
    // Implement your own stuff
    //
    int index1, index2, index3, indexe1, indexe2;
    index1 = addNode(0, 0, 0);
    index2 = addNode(3, 0, 0);
    index3 = addNode(0, 0, 3);
    indexe1 = addEdge(index1, index2);
    indexe2 = addEdge(index2, index3);
}

void GRAPH_SYSTEM::createRandomGraph_DoubleCircles(int n)
{
    reset( );
    srand(time(NULL));
    float dx = 5.0;
    float dz = 5.0;
    float r = 15; // radius
    float d = 10; // layer distance
    float offset_x = 15.;
    float offset_z = 15.;
    //
    // Implement your own stuff
    //
    float theta = 0;
    int temp;
    vector<int> index_temp;
    vector<vector<int>> index;
    //generate nodes
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < n; i++) {
            theta += 2 * 3.14159 / n;
            temp = addNode(r * cos(theta), 0, r * sin(theta));
            index_temp.push_back(temp);
        }
        index.push_back(index_temp);
        index_temp.clear();
        r += d;
    }
    //generate edges
    int circle_edge = n / 13 + 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int random = rand() % 2;
            if (random == 1 && (abs(i - j) <= circle_edge || ((n - j) <= (circle_edge - i) && abs(n-i-j) <= circle_edge) || (n - i <= (circle_edge - j) && abs(n - i - j) <= circle_edge))) {
                addEdge(index[0][i], index[1][j]);
            }
        }
    }
}

void GRAPH_SYSTEM::createNet_Circular( int n, int num_layers )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    float r = 5; // radius
    float d = 5; // layer distance 
    float offset_x = 15.;
    float offset_z = 15.;
    //
    // Implement your own stuff
    //
    vector<vector<int>> index;
    vector<int> index_temp;
    float theta;
    int temp;
    //generate nodes
    for (int i = 0; i <= num_layers; i++) {
        theta = 0;
        for (int j = 0; j < n; j++) {
            theta += 2 * 3.14159 / n;
            temp = addNode(r * cos(theta), 0, r * sin(theta));
            index_temp.push_back(temp);
        }
        index.push_back(index_temp);
        index_temp.clear();
        r += d;
    }
    //generate edge
    for (int i = 0; i < num_layers; i++) {
        for (int j = 0; j < n - 1; j++) {
            addEdge(index[i][j], index[i][j + 1]);//circular
        }
        addEdge(index[i][0], index[i][n - 1]);
    }
    for (int i = 0; i < num_layers; i++) {
        for (int j = 0; j < n; j++) {
            addEdge(index[i][j], index[i + 1][j]);//straight line
        }
    }
}
void GRAPH_SYSTEM::createNet_Square( int n, int num_layers )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    float r = 5; // radius
    float d = 5; // layer distance 
    float offset_x = 5.;
    float offset_z = 5.;
    //
    // Implement your own stuff
    //
    vector<vector<int>> index;
    vector<int> index_temp;
    int temp;
    int start_forbid = (num_layers - n) / 2;
    int end_forbid = start_forbid + n - 1;
    //generate nodes
    for (int i = 0; i < num_layers; i++) {
        for (int j = 0; j < num_layers; j++) {
            if (start_forbid <= i && i <= end_forbid && start_forbid <= j && j <= end_forbid) {
                index_temp.push_back(-1);
            }
            else {
                temp = addNode(dx * i, 0, dx * j);
                index_temp.push_back(temp);
            }
        }
        index.push_back(index_temp);
        index_temp.clear();
    }
    //generate edges
    for (int i = 0; i < num_layers; i++) {
        for (int j = 0; j < num_layers-1 ; j++) {
            if (index[i][j] != -1 && index[i][j + 1] != -1 )  {
                addEdge(index[i][j], index[i][j + 1]);//generate vertical
                //addEdge(index[i][j], index[i + 1][j]);
            }
        }
    }
    for (int i = 0; i < num_layers - 1; i++) {
        for (int j = 0; j < num_layers; j++) {
            if (index[i][j] != -1 && index[i + 1][j] != -1) {
                addEdge(index[i][j], index[i + 1][j]);//generate horizontal
            }
        }
    }
}

void GRAPH_SYSTEM::createNet_RadialCircular( int n ) {

    reset( );

    float offset_x = 15.0;
    float offset_z = 15.0;

    float r = 15; // radius
    //
    // Implement your own stuff
    //    
    float theta = 0;
    int temp;
    vector<int> index;
    int center_index = addNode(0, 0, 0);
    //generate nodes
    for (int i = 0; i < n; i++) {
        theta += 2 * 3.14159 / n;
        temp = addNode(r * cos(theta), 0, r * sin(theta));
        index.push_back(temp);
    }
    //generate edges
    for (int i = 0; i < n ; i++) {
        //addEdge(center_index, index[i]);
        addEdge(index[i], center_index);
    }
}

GRAPH_NODE* GRAPH_SYSTEM::getFreeNode() {
    if (mCurNumOfFreeNodes == 0) return 0;//no free node, return the nullptr.
    --mCurNumOfFreeNodes;
    int id = mFreeNodeArr[mCurNumOfFreeNodes];//take the last free node in the free node array, and take its id.
    GRAPH_NODE* n = &mNodeArr_Pool[id];//use the unique id to assign the node in the node pool array.
    mActiveNodeArr[mCurNumOfActiveNodes] = id;//use the unique id as the last element in the active node array.
    n->dynamicID = mCurNumOfActiveNodes;//index of the node
    ++mCurNumOfActiveNodes;
    return n;
}

// return node id
int GRAPH_SYSTEM::addNode( float x, float y, float z, float r)
{
    GRAPH_NODE* g;
    g = getFreeNode();
    if (g == 0) return -1; // invalid id.
    g->p = vector3(x, y, z);
    g->r = r;
    g->edgeID.clear();// 剛建好node 所以edge要clear
    return g->id;
}

GRAPH_EDGE* GRAPH_SYSTEM::getFreeEdge() {
    if (mCurNumOfFreeEdges == 0) return 0;
    --mCurNumOfFreeEdges;
    int id = mFreeEdgeArr[mCurNumOfFreeEdges];//get last edge's id.
    GRAPH_EDGE* e = &mEdgeArr_Pool[id];
    mActiveEdgeArr[mCurNumOfActiveEdges] = id;//put the id to the last edge.
    e->dynamicID = mCurNumOfActiveEdges;
    ++mCurNumOfActiveEdges;
    return e;
}

// return edge id
int GRAPH_SYSTEM::addEdge(int nodeID_0, int nodeID_1) {
    GRAPH_EDGE* e;
    e = getFreeEdge();
    if (e == 0) return -1; //cannot get free edge
    e->nodeID[0] = nodeID_0;//update the edge that connect to the two node.
    e->nodeID[1] = nodeID_1;
    mNodeArr_Pool[nodeID_0].edgeID.push_back(e->id);// update the node's edge.
    mNodeArr_Pool[nodeID_1].edgeID.push_back(e->id);
    return e->id;//return the edge's id.
}


void GRAPH_SYSTEM::askForInput( )
{
    //
    // Implement your own stuff
    // 
    cout << "GRAPH_SYSTEM" << endl;
    cout << "Key usage:" << endl;
    cout << "1: create a default graph" << endl;
    cout << "2: create a graph with 10x10 nodes. Connect the consecutive nodes horizontally" << endl;
    cout << "3: create a graph with 10x10 nodes. Connect the consecutive nodes vertically" << endl;
    cout << "4: create a graph with 10x10 nodes. Create 10 randomly generated edges" << endl;
    cout << "5: create a graph with 10x10 nodes. Create 10 randomly generated edges attached at a random node" << endl;
    cout << "Delete: delete a node and all the edges attached at it" << endl;
    cout << "Spacebar: unselect the selected node" << endl;
    cout << " " << endl;
    cout << "Use the mouse to select nodes and add edges" << endl;
    cout << "Click the left button to select/unselect or create an edge" << endl;
    cout << " " << endl;
    cout << "A selected node is highlighted as red." << endl;

}

GRAPH_NODE *GRAPH_SYSTEM::findNearestNode( double x, double z, double &cur_distance2 ) const
{
    GRAPH_NODE* n = 0, * temp = 0;
    cur_distance2 = DBL_MAX;
    vector3 p(x, 0, z);
    for (int i = 0; i < mCurNumOfActiveNodes; i++) {
        temp = &mNodeArr_Pool[mActiveNodeArr[i]];
        if (cur_distance2 > p.distance2(temp->p)) {
            cur_distance2 = p.distance2(temp->p);
            n = temp;
            //cout << "cur_distance2: " << cur_distance2 << endl;
        }
    }
    //cout << "nearest: " << n->p.x << ", " << n->p.z << endl;
    return n;
}

//
// compute mSelectedNode
//
void GRAPH_SYSTEM::clickAt(double x, double z)
{
    //
    // Implement your own stuff
    // 
    handlePassiveMouseEvent(x, z);
    if (mSelectedNode != mPassiveSelectedNode) {
        if (mSelectedNode != 0 && mPassiveSelectedNode != 0) {
            //check whether the edge has been connected.
            bool flg_sameEdge = false;
            for (int i = 0; i < mNodeArr_Pool[mSelectedNode->id].edgeID.size(); i++) {
                for (int j = 0; j < mNodeArr_Pool[mPassiveSelectedNode->id].edgeID.size(); j++) {
                    if (mNodeArr_Pool[mSelectedNode->id].edgeID[i] == mNodeArr_Pool[mPassiveSelectedNode->id].edgeID[j]) {
                        flg_sameEdge = true;
                    }
                }
            }

            if (flg_sameEdge == false) {
                addEdge(mSelectedNode->id, mPassiveSelectedNode->id);
                //cout << "not same edge!" << endl;
            }
            if (flg_sameEdge == true) {
                //cout << "same edge!" << endl;
            }
            mSelectedNode = 0;
        }
        else {
            mSelectedNode = mPassiveSelectedNode;
        }

    }
    else mSelectedNode = 0;
}

void GRAPH_SYSTEM::deleteEdge(int edgeID) {//may have bugs
    //step 0: Get the ID of the edge
    GRAPH_EDGE* e = &mEdgeArr_Pool[edgeID];

    //step 1: Assign the ID of the edge back to FE, and update FE.
    mFreeEdgeArr[mCurNumOfFreeEdges] = e->id;//put back the id of the edge that we want to delete.
    mCurNumOfFreeEdges++;

    //step 2: Get the dynamic ID of the edge we want to delete, delete it from AE, and update AE.
    mCurNumOfActiveEdges--; // update AE;
    mActiveEdgeArr[e->dynamicID] = mActiveEdgeArr[mCurNumOfActiveEdges];//Move the last edge to the position of the edge we want to delete.
    int id = mActiveEdgeArr[mCurNumOfActiveEdges];//mActiveEdgeArr[mCurNumOfActiveEdges] is the ID of the last edge.
    GRAPH_EDGE* update = &mEdgeArr_Pool[id];
    update->dynamicID = e->dynamicID;//update the last edge's dynamic id 

    //step 3: delete the edge IDs in the nodes connecting the edge.
    for (int i = 0; i < 2; i++) {
    GRAPH_NODE* node = &mNodeArr_Pool[e->nodeID[i]];
    vector<int>::iterator it = find(node->edgeID.begin(), node->edgeID.end(), e->id); //find the index of the edge we want to delete in the node.
    node->edgeID.erase(it);//delete the edge id.
    }
    
}

void GRAPH_SYSTEM::deleteNode( int nodeID ) {//may have bugs
    //
    // Implement your own stuff
    // 
    GRAPH_NODE* node = &mNodeArr_Pool[nodeID];

    // Assign the ID of the node back to FN, and update FN.
    mFreeNodeArr[mCurNumOfFreeNodes] = node->id;//put back the id of the edge that we want to delete.
    mCurNumOfFreeNodes++;

    // Get the dynamic ID of the node we want to delete, delete it from AN, and update AN.
    mCurNumOfActiveNodes--; // update AN;
    mActiveNodeArr[node->dynamicID] = mActiveNodeArr[mCurNumOfActiveNodes];//Move the last node to the position of the node we want to delete.
    int id = mActiveNodeArr[mCurNumOfActiveNodes];//mActiveNodeArr[mCurNumOfActiveNodes] is the ID of the last node.
    GRAPH_NODE* update = &mNodeArr_Pool[id];
    update->dynamicID = node->dynamicID;//update the last node's dynamic id 

    // Delete all the edges that connect to the node.
    while (node->edgeID.size()) {
        //cout << "Debug: Before deleting node->edgeID[0], node->edgeID[0] = " << node->edgeID[0] << endl;
        deleteEdge(node->edgeID[0]);
        //cout << "Debug: After deleting node->edgeID[0], node->edgeID[0] = " << node->edgeID[0] << endl;
    }

    // Reset the selected node and passive selected node.
    mSelectedNode = 0;
    mPassiveSelectedNode = 0;
}

void GRAPH_SYSTEM::deleteSelectedNode(  ) {
    //
    // Implement your own stuff
    // 
    if (isSelectedNode())
        deleteNode(mSelectedNode->id);
}

bool GRAPH_SYSTEM::isSelectedNode( ) const
{
    if (mSelectedNode != 0) return true;
    //
    // Implement your own stuff
    // 
    else return false;
}

void GRAPH_SYSTEM::getInfoOfSelectedPoint( double &r, vector3 &p ) const
{
    // r = mSelectedNode->r;
     //p = mSelectedNode->p;
    //
    // Implement your own stuff
    // 
     if (isSelectedNode()) {
         r = mSelectedNode->r;
         p = mSelectedNode->p;
     }
}



void GRAPH_SYSTEM::handleKeyPressedEvent( unsigned char key )
{
    
    switch( key ) {
    case 127: // delete
        mFlgAutoNodeDeletion = false;
        deleteSelectedNode( );
        break;
    case '1':
        mFlgAutoNodeDeletion = false;
        createDefaultGraph( );
        mSelectedNode = 0;
        break;
    case '2':
        mFlgAutoNodeDeletion = false;
        createNet_Circular(12, 3);
        mSelectedNode = 0;

        break;
    case '3':
        mFlgAutoNodeDeletion = false;
        createNet_Square(3, 11); // you can modify this
        mSelectedNode = 0;

        break;
    case '4':
        mFlgAutoNodeDeletion = false;
        createNet_RadialCircular(24);
        mSelectedNode = 0;

        break;
    case '5':
        mFlgAutoNodeDeletion = false;
        createRandomGraph_DoubleCircles(mNumPoints_DoubleCircles);
        mSelectedNode = 0;

        break;
    case '>':
        if (mNumPoints_DoubleCircles < 36) mNumPoints_DoubleCircles++;
        mFlgAutoNodeDeletion = false;
        createRandomGraph_DoubleCircles(mNumPoints_DoubleCircles);
        mSelectedNode = 0;
        break;

    case '<':
        if (mNumPoints_DoubleCircles > 3) mNumPoints_DoubleCircles--;
        mFlgAutoNodeDeletion = false;
        createRandomGraph_DoubleCircles(mNumPoints_DoubleCircles);
        mSelectedNode = 0;
        break;
    case ' ':
        mFlgAutoNodeDeletion = false;
        mSelectedNode = 0;
        break;
    case 'g':
        mFlgAutoNodeDeletion = !mFlgAutoNodeDeletion;
        break;
    }
}

void GRAPH_SYSTEM::handlePassiveMouseEvent( double x, double z )
{
    double cur_d2;
    GRAPH_NODE *n = findNearestNode( x, z, cur_d2 );
    if ( n == 0 ) return;
    if ( cur_d2 > n->r*n->r ) {
        mPassiveSelectedNode = 0;
        return;
    }
    mPassiveSelectedNode = n;
}

//
// get the number of nodes
//
int GRAPH_SYSTEM::getNumOfNodes( ) const
{
    //
    // Implement your own stuff
    // 
    return mCurNumOfActiveNodes;
}

void GRAPH_SYSTEM::getNodeInfo( int nodeIndex, double &r, vector3 &p ) const
{
    //
    // Implement your own stuff
    // 
    GRAPH_NODE* node = &mNodeArr_Pool[mActiveNodeArr[nodeIndex]];
    r = node->r;
    p = node->p;
}

//
// return the number of edges
//
int GRAPH_SYSTEM::getNumOfEdges( ) const
{
    //
    // Implement your own stuff
    // 
    return mCurNumOfActiveEdges;
}

//
// an edge should have two nodes: index 0 and index 1
// return the position of node with nodeIndex
//傳某個edge的node
//node index = 0傳這個edge的第一個node
//node index = 1傳這個edge的第二個node
//
vector3 GRAPH_SYSTEM::getNodePositionOfEdge( int edgeIndex, int nodeIndex ) const
{
    
    //
    // Implement your own stuff
    // 
    GRAPH_EDGE* edge = &mEdgeArr_Pool[mActiveEdgeArr[edgeIndex]];
    GRAPH_NODE* node = &mNodeArr_Pool[edge->nodeID[nodeIndex]];
    vector3 p = node->p;
    return p;
}

void GRAPH_SYSTEM::stopAutoNodeDeletion()
{
    mFlgAutoNodeDeletion = false;
}

//
// For every frame, update( ) function is called.
// 
//
void GRAPH_SYSTEM::update( )
{
    if (!mFlgAutoNodeDeletion) {
     
        return;
    }
    mSelectedNode = 0;
    mPassiveSelectedNode = 0;

    Sleep(250);
    //
    //
    // Implement your own stuff
    // 

}
