#include "LevelBuilder.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "TileComponent.h"
#include <fstream>



std::vector<std::vector<std::shared_ptr<dae::GameObject>>> LevelBuilder::m_TilesByRow{};

void LevelBuilder::LoadLevel1(dae::Scene& scene)
{
	constexpr int baseRow = 7;
	m_TilesByRow.resize(baseRow);

	constexpr float tileSize = 64.0f;
	constexpr float startX = 288.f;
	constexpr float startY = 64.f;

	int id = 0;
	for (int row = 0; row < baseRow; ++row)
	{
		for (int col = 0; col <= row; ++col)
		{
			glm::vec2 pos = {
				startX + (col - row / 2.0f) * tileSize,
				startY + row * tileSize * 0.75f
			};

			auto tile = CreateTile(id++, pos);
			auto tileComp = tile->GetComponent<TileComponent>();
			tileComp->SetGridPosition(row, col);

			m_TilesByRow[row].push_back(tile);

			// === DEBUG TEXT ===
			//auto [rowTest, colTest] = tileComp->GetGridPosition();
			//int testid = tileComp->GetID();
			//std::string coords = std::to_string(testid);
			//tile->AddComponent<dae::TextComponent>(*tile, coords, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));

			scene.Add(tile);
		}
	}
}
 
void LevelBuilder::LoadFromJson(dae::Scene& scene, const std::string& pathToJson)
{
	using json = nlohmann::json;

	std::filesystem::path path = pathToJson;
	std::cout << "[DEBUG] Attempting to load JSON from: " << std::filesystem::absolute(path) << '\n';


	std::ifstream file(pathToJson);
	if (!file.is_open())
		throw std::runtime_error("Failed to open level json: " + pathToJson);

	json data;
	file >> data;

	constexpr float tileSize = 64.0f;
	constexpr float startX = 288.f;
	constexpr float startY = 64.f;

	m_TilesByRow.clear();
	m_TilesByRow.resize(data["tileStates"].size());

	int id = 0;

	for (size_t row = 0; row < data["tileStates"].size(); ++row)
	{
		const auto& rowData = data["tileStates"][row];
		for (size_t col = 0; col < rowData.size(); ++col)
		{
			const auto& tileJson = rowData[col];

			glm::vec2 pos = {
				startX + (static_cast<float>(col) - static_cast<float>(row) / 2.0f) * tileSize,
				startY + static_cast<float>(row) * tileSize * 0.75f
			};

			auto tile = CreateTile(id++, pos);
			auto* tileComp = tile->GetComponent<TileComponent>();
			tileComp->SetGridPosition(static_cast<int>(row), static_cast<int>(col));

			if (tileJson.contains("start") && tileJson.contains("target"))
			{
				std::string intermediate = tileJson.contains("intermediate") ? tileJson["intermediate"].get<std::string>() : "";

				tileComp->SetColorStates(
					tileJson["start"].get<std::string>(),
					intermediate,
					tileJson["target"].get<std::string>()
				);
			}
			m_TilesByRow[row].push_back(tile);
			scene.Add(tile);
		}
	}
}

std::shared_ptr<dae::GameObject> LevelBuilder::CreateTile(int id, const glm::vec2& pos)
{
	//font is set for debugging (check debug text above)
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto tile = std::make_shared<dae::GameObject>();

	tile->AddComponent<dae::TextureComponent>(*tile, "testing/tile_default_test.png", 2.0f);
	tile->AddComponent<dae::TextComponent>(*tile, " ", font);

	auto* tileComp = tile->AddComponent<TileComponent>(*tile);
	tileComp->SetID(id);
	tileComp->SetState(TileState::Default);
	tileComp->SetTargetState(TileState::Target);

	tile->SetPosition(pos.x, pos.y);

	return tile;
}

const std::vector<std::vector<std::shared_ptr<dae::GameObject>>>& LevelBuilder::GetTileMap()
{
	return m_TilesByRow;
}
const std::vector<std::vector<std::shared_ptr<TileComponent>>>& LevelBuilder::GetTileComponentMap()
{
	static std::vector<std::vector<std::shared_ptr<TileComponent>>> tileComponentMap{};
	tileComponentMap.clear(); // bug fix of the row looping around

	for (const auto& row : m_TilesByRow)
	{
		std::vector<std::shared_ptr<TileComponent>> compRow;

		for (const auto& tileGO : row)
		{
			auto raw = tileGO->GetComponent<TileComponent>();

			if (raw)
			{
				auto shared = std::shared_ptr<TileComponent>(raw, [](TileComponent*) {});
				compRow.push_back(shared);
			}
		}
		tileComponentMap.push_back(std::move(compRow));
	}
	return tileComponentMap;
}
