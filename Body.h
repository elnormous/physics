//
//  Box.h
//  Bursch
//
//  Created by Elviss Strazdins on 12.06.2014.
//  Copyright (c) 2014 Bool Games. All rights reserved.
//

#pragma once

#include "Contanct.h"

namespace BearSlayer
{
    class CollisionHandler;
    class Body;
    class Physics;
    class Space;
    
    class Body: public cocos2d::Ref
	{
		friend Physics;
	public:
        enum class Shape
        {
            None = 0,
            Box = 1,
            Circle = 2
        };
        
        struct Def
        {
            bool dynamic = true;
            bool sensor = false;
            Shape shape = Shape::None;
            cocos2d::Vec2 position;
            cocos2d::Size size;
            float radius = 0.0f;
            void* userData = nullptr;
            uint32_t category = 0xFFFFFF;
            uint32_t mask = 0xFFFFFF;
        };
        
		virtual ~Body();
        
        bool isDynamic() const { return _dynamic; }
        bool isSensor() const { return _sensor; }
        void setSensor(bool sensor) { _sensor = sensor; }

        Shape getShape() const { return _shape; }
        void setPosition(const cocos2d::Vec2& position);
        const cocos2d::Vec2& getPosition() const { return _position; }
        const cocos2d::Size& getSize() const { return _size; }
        float getRadius() const { return _radius; }
        
        void setVelocity(const cocos2d::Vec2& velocity) { _velocity = velocity; }
        const cocos2d::Vec2& getVelocity() const { return _velocity; }
        
        bool getDebugCollided() const { return _debugCollided; }
        
        void setUserData(void* userData) { _userData = userData; }
        void* getUserData() const { return _userData; }
        
        void setCategory(uint32_t category) { _category = category; }
        uint32_t getCategory() const { return _category; }
        
        const cocos2d::AABB2& getAABB() const { return _aabb; }
        
        void addCollisionHandler(CollisionHandler* collisionHandler);
        void removeCollisionHandler(CollisionHandler* collisionHandler);
        
        const std::vector<Contact>& getContancts() const { return _contacts; }
        void clearContacts();
        void addContact(const Contact& contanct);
        
        void setEnabled(bool enabled) { _enabled = enabled; }
        bool getEnabled() const { return _enabled; }
        
        const std::set<const Space*>& getSpaces() const { return _spaces; }
        
	protected:
        Body(const Def& bodyDef, Physics* physics);
        
        void updateSpace();
        
        Physics* _physics;
        
        bool _dynamic;
        bool _sensor;
        
        Shape _shape;
        cocos2d::Vec2 _position;
        cocos2d::Size _size;
        float _radius;
        cocos2d::Vec2 _velocity;
        
        bool _debugCollided;
        
        void* _userData;
        
        uint32_t _category;
        uint32_t _mask;
        
        cocos2d::AABB2 _aabb;
        
        std::vector<CollisionHandler*> _collisionHandlers;
        std::vector<Contact> _contacts;
        
        int32_t _spaceX;
        int32_t _spaceY;
        int32_t _spaceId = -1;
        
        std::set<const Space*> _spaces;
        
        bool _enabled = true;
	};
    
    typedef cocos2d::Vector<Body*> Bodies;
}
