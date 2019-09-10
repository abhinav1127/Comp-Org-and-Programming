/**
* @file graphics.c
* @author Abhinav Tirath
* @date 10-29-2018
* @brief A graphics library for drawing geometry, for Homework 9 of Georgia Tech
*        CS 2110, Fall 2018.
*/

// Please take a look at the header file below to understand what's required for
// each of the functions.
#include "graphics.h"
#include <stdio.h>

// Don't touch this. It's used for sorting for the drawFilledPolygon function.
int int_cmp(const void *a, const void *b)
{
    const int *ia = (const int *)a;
    const int *ib = (const int *)b;
    return *ia  - *ib;
}

Pixel noFilter(Pixel c) {
    // Don't touch this.
    return c;
}

// TODO: Complete according to the prototype in graphics.h
Pixel greyscaleFilter(Pixel c) {
    

    
    uint16_t r = c & 31;
    r *= 77;
    
    uint16_t g = (c & 992) >> 5;
    g *= 151;
    
    uint16_t b = (c & 31744) >> 10;
    b *= 28;
    
    uint16_t channel = (r + b + g) >> 8;
    
    c = (channel << 10) + (channel << 5) + (channel);

    return c;
}

// TODO: Complete according to the prototype in graphics.h
Pixel redOnlyFilter(Pixel c) {
    
    c = c & 31;

    return c;
}

// TODO: Complete according to the prototype in graphics.h
Pixel brighterFilter(Pixel c) {

    
    uint16_t r = c & 31;
    uint16_t g = (c & 992) >> 5;
    uint16_t b = (c & 31744) >> 10;
    
    uint16_t max = 31;
    
    uint16_t diffr = max - r;
    uint16_t diffg = max - g;
    uint16_t diffb = max - b;
    
    r = r + (diffr >> 1);
    g = g + (diffg >> 1);
    b = b + (diffb >> 1);

    c = (b << 10) + (g << 5) + (r);
    
    return c;
}


// TODO: Complete according to the prototype in graphics.h
void drawPixel(Screen *screen, Vector coordinates, Pixel pixel) {
    
    if (coordinates.x < 0 || coordinates.x >= screen -> size.x || coordinates.y < 0 || coordinates.y >= screen -> size.y) {
        return;
    }
    
    int index = ((screen -> size.x) * coordinates.y) + coordinates.x;
    screen -> buffer[index] = pixel;
}

// TODO: Complete according to the prototype in graphics.h
void drawFilledRectangle(Screen *screen, Rectangle *rectangle) {
    
    for (int i = 0; i < rectangle -> size.y; i++) {
        for (int j = 0; j < rectangle -> size.x; j++) {
            Vector v;
            v.x = rectangle -> top_left.x + j;
            v.y = rectangle -> top_left.y + i;
            drawPixel(screen, v, rectangle -> color);
        }
    }
}

// TODO: Complete according to the prototype in graphics.h
void drawLine(Screen *screen, Line *line) {
    
    int changed = 0;
    int x = line -> start.x;
    int y = line -> start.y;
    int dx = ((line -> end.x) - x);
    int dy = ((line -> end.y) - y);
    int signx = 1;
    int signy = 1;
    
    if (dx < 0) {
        dx *= -1;
        signx = -1;
    } else if (dx == 0) {
        signx = 0;
    }
    
    if (dy < 0) {
        dy *= -1;
        signy = -1;
    } else if (dy == 0) {
        signy = 0;
    }
    
    if (dy > dx) {
        int holder = dx;
        dx = dy;
        dy = holder;
        changed = 1;
    }
    
    int e = (2 * dy) - dx;
    
    for (int i = 1; i <= dx; i++) {
        Vector v;
        v.x = x;
        v.y = y;
        drawPixel(screen, v, line -> color);
        
        while (e >= 0) {
            if (changed) {
                x += signx;
            } else {
                y += signy;
            }
            e = e - 2 * dx;
        }
        
        if (changed) {
            y += signy;
        }
        else {
            x += signx;
        }
        e = e + 2 * dy;
    }
    
    Vector v;
    v.x = (line -> end.x);
    v.y = (line -> end.y);
    drawPixel(screen, v, line -> color);
    
}

// TODO: Complete according to the prototype in graphics.h
void drawPolygon(Screen *screen, Polygon *polygon) {
    
    for (int i = 0; i < polygon -> num_vertices; i++) {
        
        Line l;
        l.color = polygon -> color;
        l.start = polygon -> vertices[i];
        
        if (i == polygon -> num_vertices - 1) {
            l.end = polygon -> vertices[0];
        } else {
            l.end = polygon -> vertices[i + 1];
        }
        
        drawLine(screen, &l);
        
    }
    
}

// TODO: Complete according to the prototype in graphics.h
void drawFilledPolygon(Screen *screen, Polygon *polygon) {
    UNUSED(screen);
	int min_y = INT_MAX;
    int max_y = INT_MIN;

    // -------------------------------------------------------------------------
    // TODO: Here, write some code that will find the minimum and maximum
    // Y values that belong to vertices of the polygon, and store them as
    // min_y and max_y.
    // -------------------------------------------------------------------------
    
    for (int i = 0; i < polygon -> num_vertices; i++) {
        if (polygon -> vertices[i].y < min_y) {
            min_y = polygon -> vertices[i].y;
        }
        if (polygon -> vertices[i].y > max_y) {
            max_y = polygon -> vertices[i].y;
        }
    }

    // -------------------------------------------------------------------------
    // END OF TODO
    // -------------------------------------------------------------------------

    // Now we iterate through the rows of our polygon
	for (int row = min_y; row <= max_y; row++) {
        // This variable contains the number of nodes found. We start with 0.
		int nNodes = 0;

        // This array will contain the X coords of the nodes we find.
        // Note that there are at most num_vertices of those. We allocate
        // that much room, but at any time only the first nNodes ints will
        // be our actual data.
        int nodeX[polygon->num_vertices];

        // This loop finds the nodes on this row. It intersects the line
        // segments between consecutive pairs of vertices with the horizontal
        // line corresponding to the row we're on. Don't worry about the
        // details, it just works.
		int j = polygon->num_vertices - 1;
		for (int i = 0; i < polygon->num_vertices; i++) {
			if ((polygon->vertices[i].y < row && polygon->vertices[j].y >= row) ||
				(polygon->vertices[j].y < row && polygon->vertices[i].y >= row)) {
				nodeX[nNodes++] = (polygon->vertices[i].x +
                    (row - polygon->vertices[i].y) *
                    (polygon->vertices[j].x - polygon->vertices[i].x) /
                    (polygon->vertices[j].y - polygon->vertices[i].y));
			}
			j = i;
		}

        // ---------------------------------------------------------------------
        // TODO: Make a call to qsort here to sort the nodeX array we made,
        // from small to large x coordinate. Note that there are nNodes elements
        // that we want to sort, and each is an integer. We give you int_cmp
        // at the top of the file to use as the comparator for the qsort call,
        // so you can just pass it to qsort and not need to write your own
        // comparator.
        // ---------------------------------------------------------------------

        qsort(nodeX, nNodes, sizeof(nodeX[0]), int_cmp);

        // ---------------------------------------------------------------------
        // END OF TODO
        // ---------------------------------------------------------------------



        // ---------------------------------------------------------------------
        // TODO: Now we fill the x coordinates corresponding to the interior of
        // the polygon. Note that after every node we switch sides on the
        // polygon, that is, if we are on the outside, when we pass a node we
        // end up on the inside, and if are inside, we end up on the outside.
        // As a result, all you need to do is start at the 0th node, iterate
        // through all of the even-indexed nodes, and fill until the next node.
        // For example, you need to fill between nodes 0-1, between nodes 2-3,
        // nodes 4-5 etc. but not between nodes 1-2, or nodes 3-4.
        // ---------------------------------------------------------------------
        UNUSED(nodeX);
        
        for (int i = 0; i < nNodes; i++) {
            if (i % 2 == 0) {
                if (i != nNodes - 1) {
                    
                    for (int j = nodeX[i]; j < nodeX[i + 1]; j++) {
                        Vector v;
                        v.x = j;
                        v.y = row;
                        drawPixel(screen, v, polygon -> color);
                    }
                }
            }
        }

        // ---------------------------------------------------------------------
        // END OF TODO
        // ---------------------------------------------------------------------
	}
}

// TODO: Complete according to the prototype in graphics.h
void drawRectangle(Screen *screen, Rectangle *rectangle) {
    
    /**
     * @brief Draw the rectangle provided, onto the screen provided.
     * @param screen The Screen to draw onto.
     * @param rectangle The Rectangle to draw.
     * @details We will interpret this (unfilled) rectangle as a Polygon with 4
     *          vertices. As a result, your implementation should use the Rectangle
     *          provided to create a Polygon struct and then draw this Polygon using
     *          the drawPolygon function. No actual drawing should be done in this
     *          function.
     */
    
    Polygon polygon;
    polygon.num_vertices = 4;
    polygon.color = rectangle -> color;
    
    Vector nodes[4];
    
    nodes[0] = rectangle -> top_left;
    
    Vector node1;
    node1.x = rectangle -> top_left.x;
    node1.y = rectangle -> top_left.y + rectangle -> size.y - 1;
    nodes[1] = node1;
    
    Vector node2;
    node2.x = rectangle -> top_left.x + rectangle -> size.x - 1;
    node2.y = rectangle -> top_left.y + rectangle -> size.y - 1;
    nodes[2] = node2;
    
    Vector node3;
    node3.x = rectangle -> top_left.x + rectangle -> size.x - 1;
    node3.y = rectangle -> top_left.y;
    nodes[3] = node3;
    
    polygon.vertices = nodes;
    
    drawPolygon(screen, &polygon);

    
}

// TODO: Complete according to the prototype in graphics.h
void drawCircle(Screen *screen, Circle *circle) {

    
    //    typedef struct {
//        Vector center; // coordinates (width, height) of the center of the circle
//        int radius; // radius of the circle
//        Pixel color; // the color of the circle
//    } Circle;
    
    //void drawPixel(Screen *screen, Vector coordinates, Pixel pixel) {
    
    int x = 0;
    int y = circle -> radius;
    int d = 1 - circle -> radius;
    
    while (x <= y) {
        Vector vector;
        
        vector.x = circle -> center.x + x;
        vector.y = circle -> center.y + y;
        drawPixel(screen, vector, circle -> color);
        vector.y = circle -> center.y - y;
        drawPixel(screen, vector, circle -> color);

        vector.x = circle -> center.x - x;
        vector.y = circle -> center.y + y;
        drawPixel(screen, vector, circle -> color);
        vector.y = circle -> center.y - y;
        drawPixel(screen, vector, circle -> color);
        
        vector.x = circle -> center.x + y;
        vector.y = circle -> center.y + x;
        drawPixel(screen, vector, circle -> color);
        vector.y = circle -> center.y - x;
        drawPixel(screen, vector, circle -> color);

        vector.x = circle -> center.x - y;
        vector.y = circle -> center.y + x;
        drawPixel(screen, vector, circle -> color);
        vector.y = circle -> center.y - x;
        drawPixel(screen, vector, circle -> color);
        
        if (d < 0) {
            d = d + 2 * x + 3;
            x += 1;
        } else {
            d = d + 2 * (x-y) + 5;
            x += 1;
            y -= 1;
        }

    }
}

// TODO: Complete according to the prototype in graphics.h
void drawFilledCircle(Screen *screen, Circle *circle) {
    
    int x = 0;
    int y = circle -> radius;
    int d = 1 - circle -> radius;
    int mx = circle -> center.x;
    int my = circle -> center.y;
    
    while (x <= y) {
        Vector vector1;
        vector1.x = mx + x;
        vector1.y = my + y;
        
        Vector vector2;
        vector2.x = mx + x;
        vector2.y = (my > y) ? (my - y) : 0;
        
        Line l;
        l.start = vector1;
        l.end = vector2;
        l.color = circle -> color;
        drawLine(screen, &l);
        
        if (mx >= x) {
            vector1.x = mx - x;
            vector1.y = my + y;
            
            vector2.x = mx - x;
            vector2.y =  (my > y) ? my - y : 0;
            
            l.start = vector1;
            l.end = vector2;
            l.color = circle -> color;
            drawLine(screen, &l);
        }
        
        vector1.x = mx + y;
        vector1.y = my + x;
        
        vector2.x = mx + y;
        vector2.y = (my > x) ? (my - x) : 0;
        
        l.start = vector1;
        l.end = vector2;
        l.color = circle -> color;
        drawLine(screen, &l);
        
        if (mx >= y) {
            vector1.x = mx - y;
            vector1.y = my + x;
            
            vector2.x = mx - y;
            vector2.y = (my > x) ? (my - x) : 0;
            
            l.start = vector1;
            l.end = vector2;
            l.color = circle -> color;
            drawLine(screen, &l);
        }
        
        if (d < 0) {
            d = d + 2 * x + 3;
            x += 1;
        } else {
            d = d + 2 * (x-y) + 5;
            x += 1;
            y -= 1;
        }
    }
}

// TODO: Complete according to the prototype in graphics.h
void drawImage(Screen *screen, Image *image, Pixel (*colorFilter)(Pixel)) {
    
    int numPixels = image -> size.x * image -> size.y;
    Vector v;
    
    for (int i = 0; i < numPixels; i++) {
        Pixel p = image -> buffer[i];
        p = colorFilter(p);
        
        v.x = image -> top_left.x + (i % image -> size.x);
        v.y = image -> top_left.y + (i / image -> size.x);
        
        drawPixel(screen, v, p);
        
    }
    
}

// TODO: Complete according to the prototype in graphics.
Image rotateImage(Image *image, int degrees) {
    
    
    /**
     * @brief Make a rotated copy of a given image.
     * @param image The Image to rotate
     * @param degrees An integer which will be a multiple of 90 (e.g. 90, -270, 1350,
     *                etc.) corresponding to the angle you're rotating the image by,
     *                COUNTERCLOCKWISE.
     * @return A copy of the image, rotated around the top-left corner, by the given
     *         angle.
     * @details Before rotating the image, you need to create room for a copy of the
     *          image. You should NOT use malloc for the image struct (since you
     *          return the struct and NOT a pointer, you can have it on the stack),
     *          however, you will need to malloc the new pixel buffer. Remember that
     *          the rotated pixel buffer has the same size as the original buffer as
     *          the pixel buffers are 1d arrays.
     *
     *          Then, to rotate the image, first calculate the new size of the image
     *          and place it in the 'size' member of the struct. Once that's ready,
     *          iterate over each row,col pair of coordinates in the new image
     *          and place the pixel at that address to the correct location in the
     *          rotated image.
     *
     *          You do NOT need to check for malloc errors. Assume malloc returns a
     *          valid pointer.
     *
     */
    
    
    Image rotated;
    rotated.buffer = malloc(sizeof(Pixel) * image -> size.x * image -> size.y);
    rotated.top_left = image -> top_left;
    
    if (degrees % 180 == 0) {
        rotated.size = image -> size;
    } else {
        rotated.size.x = image -> size.y;
        rotated.size.y = image -> size.x;
    }
    
    if (degrees > 360 || degrees < 0) {
        if (degrees > 360) {
            while (degrees > 360) {
                degrees -= 360;
            }
        } else {
            while (degrees < 0) {
                degrees += 360;
            }
        }
    }
    
    //after this point, all degrees are 0, 90, 180, or 270
    if (degrees == 360) {
        degrees = 0;
    }
    
    //    typedef struct {
    //        Vector top_left; // the coordinates of the top left vertex of the rectangle
    //        Vector size; // the size of the original image (width, height)
    //        Pixel* buffer; // the pixel array to read the image pixels from
    //    } Image;
    if (degrees == 0) {
        int numOfPixels = rotated.size.x * rotated.size.y;
        for (int i = 0; i < numOfPixels; i++) {
            rotated.buffer[i] = image -> buffer[i];
        }
    } else if (degrees == 180) {
        int numOfPixels = rotated.size.x * rotated.size.y;
        for (int i = 0; i < numOfPixels; i++) {
            rotated.buffer[i] = image -> buffer[numOfPixels - 1 - i];
        }
    } else if (degrees == 90) {
        for (int i = 0; i < image -> size.y; i++) {
            for (int j = 0; j < image -> size.x; j++) {
                int newRow = image -> size.x - 1 - j;
                int newCol = i;
                rotated.buffer[(newRow * rotated.size.x) + newCol] = image -> buffer[(i * image -> size.x) + j];
            }
        }
    } else {
        for (int i = 0; i < image -> size.y; i++) {
            for (int j = 0; j < image -> size.x; j++) {
                int newRow = j;
                int newCol = image -> size.y - 1 - i;
                rotated.buffer[(newRow * rotated.size.x) + newCol] = image -> buffer[(i * image -> size.x) + j];
            }
        }
    }
    
    
    return rotated;
    
}










