#pragma once

#include "TextureManager.h"
#include "utility.h"

class Animation
{
	protected:
		int refcount;
		bool Alive;
	public:
		virtual void Update(Uint32 TickDelta) = 0;
		virtual void Draw(Pos2D Position) = 0;
		void AddRef()
		{
			refcount++;
		}
		bool Release()
		{
			if(--refcount <= 0)
			{
				Destroy();
				return false;
			}
			return true;
		}

		bool isAlive()
		{
			return Alive;
		}
};