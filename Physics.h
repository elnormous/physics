//
//  Physics.h
//  Bursch
//
//  Created by Elviss Strazdins on 20.06.2014.
//  Copyright (c) 2014 Bool Games. All rights reserved.
//

#pragma once

#include "Body.h"
#include "Space.h"
#include "CCAABB2.h"

const float SPACE_SIZE = 1;

namespace BearSlayer
{
	class Physics: public cocos2d::Ref
	{
        friend Body;
	public:
        Physics(const cocos2d::AABB2& worldSize = cocos2d::AABB2(cocos2d::Vec2(-500.0f, -500.0f), cocos2d::Vec2(500.0f, 500.0f)));
		virtual ~Physics();
		
		void update(float delta, uint32_t iterations);
		
		const Bodies& getBodies() const { return _bodies; }
		
        Body* createBody(const Body::Def& bodyDef);
		void removeBody(Body* body);
        
        Body* getClosestBody(const cocos2d::Vec2& position, uint32_t mask = 0) const;
        
        void reset();
        
        Space* getSpace(int32_t spaceId);
        
        bool checkCollision(Body* body1, Body* body2);
        
	private:
		DISALLOW_COPY_AND_ASSIGN(Physics);
        
        void separate(Body* body1, Body* body2, const cocos2d::Vec2& change);

		Bodies _bodies;
        cocos2d::AABB2 _worldSize;
        uint32_t _spacesX;
        uint32_t _spacesY;
        
        bool _locked = false;
        
        Spaces _spaces;
	};
}
