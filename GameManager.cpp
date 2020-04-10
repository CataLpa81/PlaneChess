
#include"GameManager.h"



void GameManager::GameInputLogic(sf::Event event)
{
	switch (turn)
	{
	case GameManager::PLANE:
		planepool->Input(event,dice->Number);
		break;
	case GameManager::BRIGE_TODICE:
		if(dice->Number!=6)
		planepool->SwitchToNextTurn();
		if(planepool->currentpool->fine==true)
			planepool->SwitchToNextTurn();
		if (planepool->currentpool->fine == true)
			planepool->SwitchToNextTurn();
		if (planepool->currentpool->fine == true)
			planepool->SwitchToNextTurn();
		turn = DICE;
		break;
	case GameManager::BRIGE_TOPLANE:
		if (this->planepool->currentpool->JudgeAvailable(dice->Number))
			turn = PLANE;
		else
			turn = BRIGE_TODICE;
		break;
	case GameManager::DICE:
		dice->input(event);
		break;
	default:
		break;
	}

}

void GameManager::GameUpdateLogic()
{
	planepool->Update();
	//chessboard->Update();
}

void GameManager::GameRenderLogic()
{

	planepool->Render();
	dice->Rander();
}

void GameManager::onNotify(Entity* entity_,MVCEvent event)
{
	switch (event)
	{
	case DICETIME:
		turn = BRIGE_TODICE;
		break;
	case PLANETIME:
		turn = BRIGE_TOPLANE;

		break;
	default:
		break;
	}
}