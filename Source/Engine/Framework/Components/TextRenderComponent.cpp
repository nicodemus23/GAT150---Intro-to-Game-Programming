#pragma once
#include "TextRenderComponent.h"
#include "Framework/Framework.h"
#include "Core/Json.h"
#include "Renderer/Renderer.h"

namespace kiko
{
	CLASS_DEFINITION(TextRenderComponent)

	TextRenderComponent::TextRenderComponent(const TextRenderComponent& other)
	{
		text = other.text;
		fontName = other.fontName;
		fontSize = other.fontSize;
	}
	bool TextRenderComponent::Initialize()
	{
		if (!fontName.empty()) m_text = std::make_unique<kiko::Text>(GET_RESOURCE(Font, fontName, fontSize));
		
		return true;
	}
	void TextRenderComponent::Update(float dt)
	{

	}
	void TextRenderComponent::Draw(Renderer& renderer)
	{
		// update the text if changed
		if (m_changed)
		{
			m_changed = false;
			// create text using text string and color
			m_text->Create(renderer, text, color);
		}
		// draw text
		m_text->Draw(renderer, m_owner->transform);

	}
	void TextRenderComponent::SetText(const std::string& string)
	{
		if (string != text)
		{
			text = string;
			m_changed = true;
		}
	}

	void TextRenderComponent::Read(const json_t& value)
	{
		READ_DATA(value, text);
		READ_DATA(value, fontName);
		READ_DATA(value, fontSize);
		READ_DATA(value, color);
	}		
}