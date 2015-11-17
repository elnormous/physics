//
//  Space.h
//  BearSlayer
//
//  Created by Elviss Strazdins on 04/11/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "Body.h"

namespace BearSlayer
{
    class Space: public cocos2d::Ref
    {
    public:
        Space(int32_t spaceId);
        
        int32_t _spaceId;
        
        Bodies _bodies;
    };
    
    typedef cocos2d::Map<int32_t, Space*> Spaces;
}
