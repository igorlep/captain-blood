#include "aiLevasserAllyKick.h"
#include "../../Brains/aiBrain.h"
#include "../../../character/components/CharacterPhysics.h"
#include "../../../character/components/CharacterLogic.h"


aiLevasserAllyKick::aiLevasserAllyKick(aiBrain* Brain) : aiThought (Brain)
{	
}

void aiLevasserAllyKick::Activate(Character* pChr, float fKickDistance)
{
	pTarget = pChr;
	fDistance = fKickDistance;
	fIdleTime = 0.0f;
	fTimeToNextAttack =  Rnd(0.7f)+0.5f;// + Rnd(2.0f);;

	bHasKick = false;

	bAllowRotate = false;

	aiThought::Activate();
}

bool aiLevasserAllyKick::Process (float fDeltaTime)
{	
	GetBrain()->OrinentToTarget();

	CharacterLogic::State st = GetBrain()->GetBody()->logic->GetState();	

	if (st == CharacterLogic::state_attack)
	{
		bHasKick = true;
	}


	if (st != CharacterLogic::state_attack && !bHasKick)
	{
		int k = (int)(Rnd(0.999f)*2);

		//k = 4;

		switch (k)
		{
			case 0:			
			{
				GetBrain()->GetBody()->animation->ActivateLink("Attack1");
				bAllowRotate = true;
			}
			break;
			case 1:			
			{
				GetBrain()->GetBody()->animation->ActivateLink("Attack2");
				bAllowRotate = true;
			}
			break;			
		}

		if (st == CharacterLogic::state_attack)
		{
			bHasKick = true;
		}
	}

	/*if (st != CharacterLogic::state_attack && fIdleTime > fTimeToNextAttack)
	{
		/*if ((vTrgtPos-vMyPos).GetLength() > fDistance)
		{
			return false;
		}*/

		/*if (Rnd(1)>0.5f) 
		{
			GetBrain()->GetBody()->logic->ActivateLink("Attack1");
		}		
		else
		{
			GetBrain()->GetBody()->logic->ActivateLink("Attack2");
		}

		fTimeToNextAttack = 0.5f + Rnd(2.0f);
		fIdleTime = 0.0f;

		return false;

	} else
	{
		if (st != CharacterLogic::state_attack) fIdleTime += fDeltaTime;
	}*/

	if (st != CharacterLogic::state_attack && bHasKick)
	{
		bAllowRotate = true;

		fIdleTime += fDeltaTime;

		if (fIdleTime > fTimeToNextAttack) return false;
	}

		

	return true;
}

void aiLevasserAllyKick::DebugDraw (const Vector& BodyPos, IRender* pRS)
{
	//pRS->Print(BodyPos + Vector (0.0f, 1.9f, 0.0f), 10000.0f, 0.0f, 0xFFFFFFFF, "wait");
}

void aiLevasserAllyKick::Stop ()
{
	bool bRes = GetBrain()->GetBody()->animation->ActivateLink("idle");
}

void aiLevasserAllyKick::Hit ()
{
	//Отвечать, если бьют...
	fTimeToNextAttack = 0.05f;
}