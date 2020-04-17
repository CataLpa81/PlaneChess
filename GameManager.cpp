
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
	dice->Update();
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


void GameManagerServer::GameInputLogic(sf::Event event)
{
	switch (turn)
	{
	case GameManagerServer::PLANE:
		planepool->Input(event, dice->Number);
		break;
	case GameManagerServer::BRIGE_TODICE:
		if (dice->Number != 6)
			planepool->SwitchToNextTurn();
		if (planepool->currentpool->fine == true)
			planepool->SwitchToNextTurn();
		if (planepool->currentpool->fine == true)
			planepool->SwitchToNextTurn();
		if (planepool->currentpool->fine == true)
			planepool->SwitchToNextTurn();
		turn = DICE;
		break;
	case GameManagerServer::BRIGE_TOPLANE:
		if (this->planepool->currentpool->JudgeAvailable(dice->Number))
			turn = PLANE;
		else
			turn = BRIGE_TODICE;
		break;
	case GameManagerServer::DICE:
		dice->input(event);
		break;
	default:
		break;
	}

}

void GameManagerServer::GameUpdateLogic()
{
	planepool->Update();
	//chessboard->Update();
	dice->Update();
}

void GameManagerServer::GameRenderLogic()
{

	planepool->Render();
	dice->Rander();
}

void GameManagerServer::onNotify(Entity* entity_, MVCEvent event)
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





void GameManagerClient::GameInputLogic(sf::Event event)
{
	switch (turn)
	{
	case GameManagerClient::PLANE:
		if (Player == planepool->TURN)
			planepool->currentpool->Input(event,dice->Number);
		else
		{
			sf::Packet p;
			planepool->currentpool->Input(p, dice->Number);
		}

		break;
	case GameManagerClient::BRIGE_TODICE:
		if (dice->Number != 6)
			planepool->SwitchToNextTurn();
		if (planepool->currentpool->fine == true)
			planepool->SwitchToNextTurn();
		if (planepool->currentpool->fine == true)
			planepool->SwitchToNextTurn();
		if (planepool->currentpool->fine == true)
			planepool->SwitchToNextTurn();
		turn = DICE;
		break;
	case GameManagerClient::BRIGE_TOPLANE:
		if (this->planepool->currentpool->JudgeAvailable(dice->Number))
			turn = PLANE;
		else
			turn = BRIGE_TODICE;
		break;
	case GameManagerClient::DICE:
		if (Player == planepool->TURN)
			dice->input(event);
		else
		{
			sf::Packet p;
			dice->input(p);
		}
			

		break;
	default:
		break;
	}

}

void GameManagerClient::GameUpdateLogic()
{
	planepool->Update();
	//chessboard->Update();
	dice->Update();
}

void GameManagerClient::GameRenderLogic()
{

	planepool->Render();
	dice->Rander();
}

void GameManagerClient::onNotify(Entity* entity_, MVCEvent event)
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