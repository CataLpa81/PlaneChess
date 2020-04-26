
#include"GameManager.h"



void GameManager::GameInputLogic(sf::Event event)
{
	for (int i = 0;i < 3;i++)
	{
		switch (turn)
		{
		case GameManager::PLANE:
			planepool->Input(event, dice->Number);
			break;
		case GameManager::BRIGE_TODICE:
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
	

	btnB.Input(event);

}

void GameManager::GameUpdateLogic()
{
	int fineCount = 0;
	planepool->Update();
	//chessboard->Update();
	dice->Update();
}

void GameManager::GameRenderLogic()
{
	btnB.Render();
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



void GameManagerClient::GameInputLogic(sf::Event event)
{
	this->CR->Input(event);
	for (int i = 0;i < 3;i++)
	{
		switch (turn)
		{
		case GameManagerClient::PLANE:
			if (Player == planepool->TURN)
				planepool->currentpool->Input(event, dice->Number);
			break;
		case GameManagerClient::BRIGE_TODICE:
			if (dice->Number != 6)
				planepool->SwitchToNextTurn();
			if (planepool->currentpool->fine == true || planepool->currentpool->playerName == "null")
				planepool->SwitchToNextTurn();
			if (planepool->currentpool->fine == true || planepool->currentpool->playerName == "null")
				planepool->SwitchToNextTurn();
			if (planepool->currentpool->fine == true || planepool->currentpool->playerName == "null")
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
			break;
		default:
			break;
		}
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
	CR->Render();
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

GameManagerClient::GameManagerClient()
{
	
	CR = ChatRoom::Instance();
	dice = Dice_Client::instance();
	planepool = Plane_ClientPool::instance();

	CR->setPosition(700, 0);
}
