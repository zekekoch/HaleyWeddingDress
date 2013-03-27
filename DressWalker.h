//
//  DressWalker.h
//  
//
//  Created by Zeke Koch on 2/28/13.
//
//

#ifndef ____DressWalker__
#define ____DressWalker__

// top v - center 35, front left 50-70, front right 0-20
// bottom v - center 70, left 137-165, right 70-99
// top ring - front center 222, front left 199-222, front right 222-245
// middle ring - front center 307, front left 281-307, front right 307-331
// bottom ring - front center 396, front left 369-396, front right 396-421

class DressWalker
{
    struct Junction
    {
        int West;
        int East;
        int North;
        int South;
        int NorthEast;
        int NorthWest;
        int SouthEast;
        int SouthWest;
    };
    
    Junction juntions[4] =
    {
        {70,0,0,0,71,165,0,0},
        {70,0,0,0,0,0,0,0},
        {70,0,0,0,0,0,0,0},
        {70,0,0,0,0,0,0,0}
    };
    
    DressWalker()
    {
        
    }
    
    ~DressWalker()
    {
        
    }
    
    
};


#endif /* defined(____DressWalker__) */
