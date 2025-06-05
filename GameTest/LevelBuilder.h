#pragma once
#include <memory>
#include <glm.hpp>
#include "TileComponent.h"
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

// Coordinate system used for moving entities
//
//                               (0,0)
//                          (1,0)     (1,1)
//                     (2,0)     (2,1)     (2,2)
//                (3,0)     (3,1)     (3,2)     (3,3)
//           (4,0)     (4,1)     (4,2)     (4,3)     (4,4)
//      (5,0)     (5,1)     (5,2)     (5,3)     (5,4)     (5,5)
// (6,0)     (6,1)     (6,2)     (6,3)     (6,4)     (6,5)     (6,6)

namespace dae
{
	class Scene;
	class GameObject;
}

class LevelBuilder
{
public:
	static void LoadLevel1(dae::Scene& scene);

	static void LoadFromJson(dae::Scene& scene, const std::string& pathToJson);

	static std::shared_ptr<dae::GameObject> CreateTile(int id, const glm::vec2& pos);
	static const std::vector<std::vector<std::shared_ptr<dae::GameObject>>>& GetTileMap();
	static const std::vector<std::vector<std::shared_ptr<TileComponent>>>& GetTileComponentMap();

private:
	static std::vector<std::vector<std::shared_ptr<dae::GameObject>>> m_TilesByRow;
};
