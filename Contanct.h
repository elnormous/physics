//
//  Contanct.h
//  BearSlayer
//
//  Created by Elviss Strazdins on 11/04/15.
//
//

#pragma once

namespace BearSlayer
{
    class Body;

    struct Contact
    {
        Body* bodyA;
        Body* bodyB;
        
        cocos2d::Vec2 normal;
    };
}
