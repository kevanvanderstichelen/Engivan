#pragma once
#include <string>
#include "Scene.h"
#include <unordered_map>

class LevelLoader final
{
public:
	explicit LevelLoader(const std::string& pathMesh, const std::string& pathTexture);

	~LevelLoader() = default;
	LevelLoader(const LevelLoader& other) = delete;
	LevelLoader(LevelLoader&& other) noexcept = delete;
	LevelLoader& operator=(const LevelLoader& other) = delete;
	LevelLoader& operator=(LevelLoader&& other) noexcept = delete;

	void Load(dae::Scene* currentScene, const FPoint2& offset = FPoint2{ 0,0 });

	std::vector<FPoint2>& GetZenChansPositions() { return m_ZenChansPositions; }
	std::vector<FPoint2>& GetMatiasPositions() { return m_MaitasPositions; }

private:
	const std::string m_Path;
	const std::string m_PathTexture;
	std::vector<FPoint2> m_ZenChansPositions;
	std::vector<FPoint2> m_MaitasPositions;
	void CreateRectangle(const FPoint2& startPosition, std::unordered_map<unsigned int, bool>& checkedPixels, std::vector<FRect>& colliders);
	GLubyte* m_TexturePixels;
	FColor4 m_ColliderColor;
	FColor4 m_EmptySpaceColor;
	FColor4 m_MaitaColor;
	FColor4 m_ZenChanColor;
};

