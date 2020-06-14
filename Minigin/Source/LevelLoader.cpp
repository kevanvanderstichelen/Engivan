#include "MiniginPCH.h"
#include "LevelLoader.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Devlog.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

LevelLoader::LevelLoader(const std::string& pathMesh, const std::string& pathTexture)
	: m_Path(pathMesh), m_PathTexture(pathTexture)
	, m_ColliderColor(0,0,0,255), m_EmptySpaceColor(255,255,255,255)
	, m_ZenChanColor(255,0,0,255), m_MaitaColor(0,0, 255 , 255)
{
}

void LevelLoader::Load(dae::Scene* currentScene, const FPoint2& offset)
{
	const auto& tex = dae::ResourceManager::GetInstance().LoadImageTexture(m_Path);

	const auto& wWidth = ENGINE.GetWindowWidth();
	const auto& wHeight = ENGINE.GetWindowHeight();

	if ((int)tex->GetWidth() != wWidth || (int)tex->GetHeight() != wHeight)
	{
		DEBUGLOG.PrintWarning("LevelLoader::LevelLoader(), Texture is not the same size as the window!");
		DEBUGLOG.PrintWarning("Path = " + m_Path);
		DEBUGLOG.PrintWarning("LevelLoader cancelled.");
		return;
	}


	m_TexturePixels = new GLubyte[wWidth * wHeight * 4]; // 4 = amount of color channels

	glBindTexture(GL_TEXTURE_2D, tex->GetID());
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_TexturePixels);


	GLuint r, g, b, a; // or GLubyte r, g, b, a;

	size_t x, y;
	x = 0;
	y = 0;

	size_t elmes_per_line = wWidth * 4; // elements per line = 256 * "RGBA"

	std::unordered_map<unsigned int, bool> checkedPixels;
	checkedPixels.reserve(size_t(wWidth * wHeight));

	std::vector<FRect> colliders;

	for (size_t i = 0; i < size_t(wWidth * wHeight); i++)
	{
		checkedPixels[int(i)] = false;
	}

	for (int i = 0; i < wHeight; i++)
	{
		for (int j = 0; j < wWidth; j++)
		{
			if (checkedPixels[(i * wWidth) + j] == true)
			{
				x++;
				continue;
			}

			size_t row = y * elmes_per_line;
			size_t col = x * 4;

			r = m_TexturePixels[row + col];
			g = m_TexturePixels[row + col + 1];
			b = m_TexturePixels[row + col + 2];
			a = m_TexturePixels[row + col + 3];




			if (r == m_ZenChanColor.r && g == m_ZenChanColor.g
				&& b == m_ZenChanColor.b && m_ZenChanColor.a == a)
			{
				m_ZenChansPositions.push_back(FPoint2(float(x), float(y)));
			}

			if (r == m_MaitaColor.r && g == m_MaitaColor.g
				&& b == m_MaitaColor.b && m_MaitaColor.a == a)
			{
				m_MaitasPositions.push_back(FPoint2(float(x), float(y)));
			}

			if (r == m_ColliderColor.r && g == m_ColliderColor.g
				&& b == m_ColliderColor.b && m_ColliderColor.a == a)
			{
				//checkedPixels[i * j] = true;

				const FPoint2 startPos{ float(x), float(y) };
				CreateRectangle(startPos, checkedPixels, colliders);
			}
			x++;

		}
		x = 0;
		y++;
	}
	using namespace dae;

	auto levelTexture = new GameObject();
	levelTexture->GetTransform()->Translate(offset.x, offset.y);
	levelTexture->AddComponent(new SpriteComponent(m_PathTexture));

	currentScene->Add(levelTexture);


	for (const FRect& rect : colliders)
	{
		auto box = new GameObject();
		box->AddComponent(new BoxColliderComponent(true));
		box->GetTransform()->SetPosition(rect.left + offset.x, rect.bottom + offset.y);
		box->GetComponent<BoxColliderComponent>()->SetWidth(rect.width);
		box->GetComponent<BoxColliderComponent>()->SetHeight(rect.height);

		currentScene->Add(box);
	}


	//Cleanup
	delete[] m_TexturePixels;
	delete tex;
}

void LevelLoader::CreateRectangle(const FPoint2& startPosition, std::unordered_map<unsigned int, bool>& checkedPixels, std::vector<FRect>& colliders)
{
	const auto& wWidth = (size_t)ENGINE.GetWindowWidth();
	const auto& wHeight = (size_t)ENGINE.GetWindowHeight();

	//find furthest right side
	size_t leftIndex{ size_t(startPosition.x) };
	size_t topIndex{ size_t(startPosition.y) };
	size_t rightIndex{ leftIndex };
	size_t bottomIndex{ topIndex };

	size_t elmes_per_line = wWidth * 4; // elements per line = 256 * "RGBA"

	size_t x, y;
	x = size_t(startPosition.x);
	y = size_t(startPosition.y);

	GLuint r, g, b, a;
	for (size_t i = leftIndex; i < wWidth; i++)
	{
		if (checkedPixels[int((y * wWidth) + x)] == true)
		{
			break;
		}
		size_t row = y * elmes_per_line;
		size_t col = x * 4;

		r = m_TexturePixels[row + col];
		g = m_TexturePixels[row + col + 1];
		b = m_TexturePixels[row + col + 2];
		a = m_TexturePixels[row + col + 3];

		if (r == m_EmptySpaceColor.r && g == m_EmptySpaceColor.g 
			&& b == m_EmptySpaceColor.b && a == m_EmptySpaceColor.a)
		{
			break;
		}

		x++;
	}
	rightIndex = x;
	x = size_t(startPosition.x);

	//find furthest bottom corner
	for (size_t i = topIndex; i < wHeight; i++)
	{
		if (checkedPixels[int((y * wWidth) + x)] == true)
		{
			break;
		}
		size_t row = y * elmes_per_line;
		size_t col = x * 4;

		r = m_TexturePixels[row + col];
		g = m_TexturePixels[row + col + 1];
		b = m_TexturePixels[row + col + 2];
		a = m_TexturePixels[row + col + 3];

		if (r == m_EmptySpaceColor.r && g == m_EmptySpaceColor.g
			&& b == m_EmptySpaceColor.b && a == m_EmptySpaceColor.a)
		{
			break;
		}

		y++;
	}
	bottomIndex = y;

	//Mark checked pixels (so you don't check it again)
	for (size_t i = topIndex; i < bottomIndex; i++)
	{
		for (size_t j = leftIndex; j < rightIndex; j++)
		{
			size_t row = i * wWidth;
			size_t col = j;

			checkedPixels[int(row + col)] = true;


		}
	}

	//Make colliders
	colliders.push_back(FRect(float(leftIndex), float(topIndex), float(rightIndex - leftIndex), float(bottomIndex - topIndex)));
}
