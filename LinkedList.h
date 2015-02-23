/* 
 * File:   LinkedList.h
 * Author: zschafft
 *
 * Created on February 20, 2015, 9:19 PM
 */

#ifndef LINKEDLIST_H
#define	LINKEDLIST_H

#ifdef	__cplusplus
extern "C" {
#endif


    struct node
    {
    int coordinate; //GPS Coordinate
    struct node *next;
    };

    typedef struct node waypoint;
    
#ifdef	__cplusplus
}
#endif

#endif	/* LINKEDLIST_H */

