//
//  Box.cpp
//  Bursch
//
//  Created by Elviss Strazdins on 12.06.2014.
//  Copyright (c) 2014 Bool Games. All rights reserved.
//
#include "Body.h"
#include "Physics.h"
#include "Space.h"

namespace BearSlayer
{
    Body::Body(const Body::Def& bodyDef, Physics* physics):
		_shape(bodyDef.shape), _dynamic(bodyDef.dynamic), _sensor(bodyDef.sensor),
        _position(bodyDef.position), _size(bodyDef.size), _radius(bodyDef.radius),
        _debugCollided(false), _userData(bodyDef.userData), _category(bodyDef.category),
        _mask(bodyDef.mask)
	{
        _physics = physics;
        
        switch (_shape)
        {
            case Shape::Box:
                _aabb.set(cocos2d::Vec2(-_size.width / 2.0f, -_size.height / 2.0f),
                          cocos2d::Vec2(_size.width / 2.0f, _size.height / 2.0f));
                break;
            case Shape::Circle:
                _aabb.set(cocos2d::Vec2(-_radius, -_radius),
                          cocos2d::Vec2(_radius, _radius));
                break;
            default:
                break;
        }
        
        updateSpace();
	}

	Body::~Body()
	{
	}
    
    void Body::setPosition(const cocos2d::Vec2& position)
    {
        _position = position;
        updateSpace();
    }
    
    void Body::addCollisionHandler(CollisionHandler* collisionHandler)
    {
        _collisionHandlers.push_back(collisionHandler);
    }
    
    void Body::removeCollisionHandler(CollisionHandler* collisionHandler)
    {
        std::vector<CollisionHandler*>::iterator i = std::find(_collisionHandlers.begin(), _collisionHandlers.end(), collisionHandler);
        
        if (i != _collisionHandlers.end())
        {
            _collisionHandlers.erase(i);
        }
    }
    
    void Body::clearContacts()
    {
        _contacts.clear();
    }
    
    void Body::addContact(const Contact& contanct)
    {
        for (const Contact& existingContact : _contacts)
        {
            // if contact already exists, do nothing
            if (existingContact.bodyB == contanct.bodyB)
            {
                return;
            }
        }
        
        _contacts.push_back(contanct);
    }
    
    void Body::updateSpace()
    {
        cocos2d::Vec2 offset = _position - _physics->_worldSize._min;
        
        _spaceX = ceilf(offset.x / SPACE_SIZE);
        _spaceY = ceilf(offset.y / SPACE_SIZE);
        
        int32_t oldSpace = _spaceId;
        
        _spaceId = _spaceY * _physics->_spacesX + _spaceX;
        
        if (oldSpace != _spaceId || oldSpace == -1)
        {
            _physics->getSpace(oldSpace)->_bodies.eraseObject(this);
            _physics->getSpace(_spaceId)->_bodies.pushBack(this);
            
            _spaces.clear();
            
            for (int32_t spaceY = std::max(0, _spaceY - 1); spaceY <= _spaceY + 1; ++spaceY)
            {
                for (int32_t spaceX = std::max(0, _spaceX - 1); spaceX <= _spaceX + 1; ++spaceX)
                {
                    Space* space = _physics->getSpace(spaceY * _physics->_spacesX + spaceX);
                    
                    _spaces.insert(space);
                }
            }
        }
    }
}
