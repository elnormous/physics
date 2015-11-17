//
//  CollisionHandler.h
//  BearSlayer
//
//  Created by Elviss Strazdins on 25/03/15.
//  Copyright (c) 2015 Bool Games. All rights reserved.
//

#pragma once

#include "Contanct.h"

namespace BearSlayer
{
    class CollisionHandler
    {
        virtual void handleTouchEnter(const Contact& contact);
        virtual void handleTouchExit(const Contact& contact);
        
        virtual void handleCollisionEnter(const Contact& contact);
        virtual void handleCollisionExit(const Contact& contact);
    };
}
