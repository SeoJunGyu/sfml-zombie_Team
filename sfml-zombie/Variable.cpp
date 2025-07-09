#include "stdafx.h"
#include "Variable.h"

bool Variable::isDrawHitBox = false;
int Variable::wave = 1;
int Variable::highScore = 300;
int Variable::score = 0;

bool Variable::fireRateBoost = false;
bool Variable::largerClipNextReload = false;
bool Variable::healthBoost = false;
bool Variable::fasterMovement = false;
bool Variable::betterHealthDrops = false;
bool Variable::betterAmmoDrops = false;

void Variable::ResetOptions()
{
	fireRateBoost = false;
	largerClipNextReload = false;
	healthBoost = false;
	fasterMovement = false;
	betterHealthDrops = false;
	betterAmmoDrops = false;
}
