// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance) {
    m_dungeon = new Dungeon(goblinSmellDistance);
    m_player = m_dungeon->getPlayer();
}

Game::~Game() {
    delete m_player;
    delete m_dungeon;
}

void Game::play()
{
    cout << "Press q to exit game." << endl;
    m_dungeon->generate();
    m_dungeon->display();
    char c, pos;
    while ((c = getCharacter()) != 'q') {
        // If player is dead or picked up the golden idol, we will not accept any further operation, only 'q' to exit
        if (m_player->isDead() || m_player->pickedUpGoldenIdol()) {
            continue;
        }
        if (trueWithProbability(0.1)) {
            m_player->regainHitPoints();
        }
        if (m_player->getSleepTime() > 0) {
            m_player->setSleepTime(m_player->getSleepTime() - 1);
            if (c == 'c') {
                m_player->setMaxHitPoints(50);
                m_player->setHitPoints(50);
                m_player->setStrengthPoints(9);
            } else {
                m_dungeon->update();
                m_dungeon->display();
            }
            continue;
        }
        switch (c) {
            case ARROW_LEFT:
                m_dungeon->movePlayer(Actor::LEFT);
                break;
                
            case ARROW_RIGHT:
                m_dungeon->movePlayer(Actor::RIGHT);
                break;
                
            case ARROW_UP:
                m_dungeon->movePlayer(Actor::UP);
                break;
                
            case ARROW_DOWN:
                m_dungeon->movePlayer(Actor::DOWN);
                break;
                
                // pick up an object by stepping on it and typing g
            case 'g':
                // check if the player stays at '?' scroll or ')' weapon or '&' golden idol
                // pick up the object and put it in the inventory
                m_dungeon->pickUpIfThereIsItem();
                break;
                
                // Wield a weapon by typing w and then selecting a weapon from your inventory.
            case 'w': {
                // clear the window
                clearScreen();
                // open Inventory
                m_player->openInventory();
                pos = getCharacter();
                if (m_player->canGetItemByPos(pos)) {
                    // wield weapon
                    string result = m_player->wieldWeapon(pos);
                    m_dungeon->addMessage(result);
                }
                break;
            }
                
                // Read a scroll by typing r and then selecting a scroll from your inventory.
            case 'r': {
                // clear the window
                clearScreen();
                // open Inventory
                m_player->openInventory();
                pos = getCharacter();
                if (m_player->canGetItemByPos(pos)) {
                    // read scroll
                    string message = m_player->readScroll(pos);
                    if (!message.empty()) {
                        m_dungeon->addMessage(message);
                        if (message.find("teleportation") != string::npos) {
                            m_dungeon->teleportPlayer();
                        }
                    }
                }
                break;
            }
                
                // See an inventory of your items by typing i.
            case 'i': {
                // clear the window
                clearScreen();
                // open Inventory
                m_player->openInventory();
                // Accept any character to go back
                getCharacter();
                break;
            }
                
                // When standing on a stairway, descend deeper into the dungeon by typing >
            case '>':
                // check if the Player stands on the >
                // if '>' generate a new dundeon
                // increment level
                m_dungeon->goToNextLevelIfOnStair();
                continue;
                
                // cheat by typing c
            case 'c': {
                // cheat
                m_player->setMaxHitPoints(50);
                m_player->setHitPoints(50);
                m_player->setStrengthPoints(9);
                break;
            }
        }
        m_dungeon->update();
        m_dungeon->display();
    }
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
