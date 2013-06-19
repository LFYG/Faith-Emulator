/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "world.h"

/* static */
World* World::sInstance = nullptr;

/* static */
World&
World :: getInstance()
{
    // TODO? Thread-safe
    if (sInstance == nullptr)
    {
        sInstance = new World();
    }
    return *sInstance;
}

World :: World()
{

}

World :: ~World()
{

}
