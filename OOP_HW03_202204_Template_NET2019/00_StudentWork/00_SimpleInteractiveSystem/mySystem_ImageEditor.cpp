//
// Prof. Sai-Keung WONG
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/04/25
//
#include <iostream>
#include "mySystem_ImageEditor.h"

#define IMAGE_FILE_NAME "3d-flower-desktop.jpg"

#define IMAGE_MAX_HIERARCHY_DEPTH 8

IMAGE_SYSTEM::IMAGE_SYSTEM()
{
    m_ImageHierarchy = 0;
    m_Image = new ns_opengl::Image;
    m_Image->readFile(IMAGE_FILE_NAME);

    int wImage, hImage;
        m_Image->getInfo(wImage, hImage);

    int cur_depth = 0;
        int start_x = 0;
    int start_y = 0;

        int w = wImage;
        int h = hImage;
        float sx = 2; 
        float sy = 2;

        float radius = wImage/2.0*(sx+sy)*0.5;

    m_ImageHierarchy = new IMAGE_NODE(
        cur_depth, 
        start_x,
        start_y,
        w,
        h,
        sx,
        sy,
        radius
        ); 
    float r, g, b;
    computeAverageColor(start_x, start_y, w, h, r, g, b);

    m_ImageHierarchy->setColor(r,g,b);
    m_ImageHierarchy->computeDrawPosition(
        wImage, hImage
        );
    //
}

void IMAGE_SYSTEM::reset()
{
    flgReset(m_ImageHierarchy);
}

void IMAGE_SYSTEM::flgReset(IMAGE_NODE* node) {
    if (node->flg_explored == true) {
        node->flg_explored = false;
        for (int i = 0; i < 4; i++) {
            flgReset(node->children[i]);
        }
    }
    return;
}

void IMAGE_SYSTEM::handleKeyPressedEvent( unsigned char key )
{
    switch(key) {
    case ' ':
        break;
    case '.':
    case '<':
        break;
    case ',':
    case '>': 
        break;
    case 'r':
        reset();
        break;
    
    case 'k':
    case 'K':
        break;
    case 'l':
    case 'L':
        break;
    }
}

//
// Compute the node color.
// That is compute the average color of the block of the node
//
void IMAGE_SYSTEM::computeNodeColor(IMAGE_NODE *node)
{
    float nr = 0, ng = 0, nb = 0;
    computeAverageColor(node->start_x, node->start_y, node->w, node->h, nr, ng, nb);
    node->r = nr;
    node->g = ng;
    node->b = nb;
}

//
// Explore a node if it is not explored.
// Go down the children if the node is explored.
//
void IMAGE_SYSTEM::exploreImageNode(IMAGE_NODE *node, double x, double y)
{

    if (node->flg_explored) {
        // If the node has been explored, 
        // go to check its children
        for (int i = 0; i < 4; i++) {
            computeNodeColor(node->children[i]);
        }
    } else {
        // The node is not explored yet.
        // Now, explored it.
        // Do the following steps:
        // Can we explore it? If the dimension is less than 1x1, return.
        // If the dimension is at least 2x2
        //
        // Divide the image block into four children
        // Compute the draw positions of each child.
        //

        if (node->w/2 ==0 || node->h/2 == 0) return;
        float center_x = node->start_x + node->w / 2;
        float center_y = node->start_y + node->h / 2;
        int wImage, hImage;
        m_Image->getInfo(wImage, hImage);
        node->children[0] = new IMAGE_NODE(node->cur_depth,
            node->start_x + node->w / 2,
            node->start_y + node->h / 2,
            node->w / 2,
            node->h / 2,
            2,
            2,
            node->radius / 2);
        node->children[1] = new IMAGE_NODE(node->cur_depth,
            node->start_x,
            node->start_y + node->h / 2,
            node->w / 2,
            node->h / 2,
            2,
            2,
            node->radius / 2);
        node->children[2] = new IMAGE_NODE(node->cur_depth,
            node->start_x,
            node->start_y,
            node->w / 2,
            node->h / 2,
            2,
            2,
            node->radius / 2);
        node->children[3] = new IMAGE_NODE(node->cur_depth,
            node->start_x + node->w / 2,
            node->start_y,
            node->w / 2,
            node->h / 2,
            2,
            2,
            node->radius / 2);
        for (int i = 0; i < 4; i++) {
            node->children[i]->cur_depth = node->cur_depth + 1;
            node->children[i]->flg_explored = false;
            node->children[i]->computeDrawPosition(wImage, hImage);
            computeNodeColor(node->children[i]);

        }
        node->flg_explored = true;
    }
}

//
// call exploreImageNode(root, mouse_x, mouse_y)
//
void IMAGE_SYSTEM::handlePassiveMouseEvent( double x, double y )
{
    std::cout << "IMAGE_SYSTEM Mouse:" << x << "\t" << y << std::endl;
    findTouchedNode(x, y, m_ImageHierarchy);
}

void IMAGE_SYSTEM::findTouchedNode(double x, double y, IMAGE_NODE* current) {
    if (current->flg_explored == false && current->w >= 1) {//current->w >= 1
        double dx = x - current->draw_x;
        double dy = y - current->draw_y;
        double d2 = dx * dx + dy * dy;
        double r2 = current->radius * current->radius;
        if (d2 <= r2 && current != 0) {
            exploreImageNode(current, x, y);
        }
    }
    else if(current->flg_explored == true){//explored
        for (int i = 0; i < 4; i++) {
            findTouchedNode(x, y, current->children[i]);
        }
    }
}