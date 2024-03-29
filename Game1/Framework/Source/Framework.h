#pragma once

// This header includes all files inside the framework project.
// It is meant for use by game projects ONLY.
// As new files are created, include them here so the game has easy access to them.
// It should not be included by any files inside the framework project.

#include "CoreHeaders.h"

#include"../Libraries/imgui/imgui.h"

#include "Constants.h"
#include "FWCore.h"
#include "GameCore.h"
#include "Objects/GameObject.h"
#include "../../Game/source/GameObjects/Player.h"
#include "../../Game/source/GameObjects/Enemy.h"
#include "../../Game/source/GameObjects/Enemy2.h"
#include "../../Game/source/GameObjects/PickUp.h"
#include "../../Game/source/GameObjects/Bullet.h"
#include "Objects/PlayerController.h"
#include "Objects/CollisionController.h"
#include "Events/EventManager.h"
#include "Events/Event.h"


#include "Math/Vector.h"
#include "Objects/Mesh.h"


#include "Objects/ShaderProgram.h"

#include "UI/ImGuiManager.h"
#include "Utility/Utility.h"
