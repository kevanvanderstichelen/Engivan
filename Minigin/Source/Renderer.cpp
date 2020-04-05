#pragma once
#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"

void dae::Renderer::Init(SDL_Window * window)
{
	m_pWindow = window;
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void dae::Renderer::Render() const
{
	glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);

	SceneManager::GetInstance().Render();
	
	SDL_GL_SwapWindow(m_pWindow);
}

void dae::Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture2D(const Texture2D* texture, const FRect& dest, const FRect& src)
{
	//SOURCE: http://web.archive.org/web/20131228023100/http://content.gpwiki.org/SDL:Tutorials:Using_SDL_with_OpenGL

	//Using which texture
	glBindTexture(GL_TEXTURE_2D, texture->GetID());
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	//Draw actual texture
	glEnable(GL_TEXTURE_2D);
	{
		glBegin(GL_QUADS);
		{
			glTexCoord2f(src.left, src.bottom);
			glVertex2f(dest.left, dest.bottom);

			glTexCoord2f(src.left, src.bottom + src.height);
			glVertex2f(dest.left, dest.bottom + dest.height);

			glTexCoord2f(src.left + src.width, src.bottom + src.height);
			glVertex2f(dest.left + dest.width, dest.bottom + dest.height);

			glTexCoord2f(src.left + src.width, src.bottom);
			glVertex2f(dest.left + dest.width, dest.bottom);
		}
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

}

void dae::Renderer::DrawPoint(const FPoint2& point, const float size, const FColor4& color)
{
	DrawPoint(point.x, point.y, size, color);
}

void dae::Renderer::DrawPoint(const float x, const float y, const float size, const FColor4& color)
{
	glColor4f(color.r, color.g, color.b, color.a);
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void dae::Renderer::DrawRect(const float left, const float bottom, const float width, const float height, const float lineWidth, const FColor4& color)
{
	glColor4f(color.r, color.g, color.b, color.a);
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	glVertex2f(left, bottom);
	glVertex2f(left + width, bottom);
	glVertex2f(left + width, bottom + height);
	glVertex2f(left, bottom + height);
	glEnd();
}

void dae::Renderer::DrawLine(const FPoint2& begin, const FPoint2& end, const float width, const FColor4& color)
{
	DrawLine(begin.x, begin.y, end.x, end.y, width, color);
}

void dae::Renderer::DrawLine(const float x1, const float y1, const float x2, const float y2, const float width, const FColor4& color)
{
	glColor4f(color.r, color.g, color.b, color.a);
	glLineWidth(width);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void dae::Renderer::DrawRect(const FRect& rectangle, const float lineWidth, const FColor4& color)
{
	DrawRect(rectangle.left, rectangle.bottom, rectangle.width, rectangle.height, lineWidth, color);
}

void dae::Renderer::DrawCircle(const FPoint2& position, const float radius, const float lineWidth, const FColor4& color)
{
	glColor4f(color.r, color.g, color.b, color.a);
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	for (float angle = 0.0; angle < float(2 * PI); angle += (PI / radius))
	{
		glVertex2f(position.x + radius * float(cos(angle)), position.y + radius * float(sin(angle)));
	}
	glEnd();
}

void dae::Renderer::DrawCircle(const FCircle& circle, const float lineWidth, const FColor4& color)
{
	glColor4f(color.r, color.g, color.b, color.a);
	float dAngle{ circle.radiusX > circle.radiusY ? float(PI / circle.radiusX) : float(PI / circle.radiusY) };
	
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	{
		for (float angle = 0.0; angle < float(2 * PI); angle += dAngle)
		{
			glVertex2f(circle.center.x + circle.radiusX * float(cos(angle)), circle.center.y + circle.radiusY * float(sin(angle)));
		}
	}
	glEnd();
}
