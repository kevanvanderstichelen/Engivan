#pragma once
#include <string>
#include "BaseComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
namespace dae
{
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(const std::string& text, Font* font);
		TextComponent(const std::string& text, Font* font, const SDL_Color& color);
		virtual ~TextComponent();
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		virtual void Initialize();
		virtual void Update(float elapsed);
		virtual void Render();
		virtual const std::string GetComponentName() const;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);
	private:
		static const std::string m_ComponentName;
		bool m_NeedsUpdate;
		std::string m_Text;
		Font* m_pFont;
		Texture2D* m_pTexture;
		SDL_Color m_Color;

	};


}
