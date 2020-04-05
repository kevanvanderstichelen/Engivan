#pragma once
#include "Singleton.h"
#include "MainStructs.h"
struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture2D(const Texture2D* texture, const FRect& dest, const FRect& src);

		void SetClearColor(const FColor4& color) { m_ClearColor = color; }
		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

		void DrawPoint(const FPoint2& point, const float size, const FColor4& color = FColor4(1, 0, 1, 1));
		void DrawPoint(const float x, const float y, const float size, const FColor4& color = FColor4(1, 0, 1, 1));
		void DrawLine(const FPoint2& begin, const FPoint2& end, const float width = 1.f, const FColor4& color = FColor4(1, 0, 1, 1));
		void DrawLine(const float x1, const float y1, const float x2, const float y2, const float width = 1.f, const FColor4& color = FColor4(1, 0, 1, 1));
		void DrawRect(const float left, const float bottom, const float width, const float height, const float lineWidth, const FColor4& color = FColor4(1, 0, 1, 1));
		void DrawRect(const FRect& rectangle, const float lineWidth, const FColor4& color = FColor4(1, 0, 1, 1));
		void DrawCircle(const FPoint2& position, const float radius, const float lineWidth, const FColor4& color = FColor4(1, 0, 1, 1));
		void DrawCircle(const FCircle& circle, const float lineWidth, const FColor4& color = FColor4(1, 0, 1, 1));

	private:
		SDL_Window* m_pWindow{};
		SDL_Renderer* m_Renderer{};
		FColor4 m_ClearColor{0.f, 0.f, 0.f, 1.f};
	};
}

