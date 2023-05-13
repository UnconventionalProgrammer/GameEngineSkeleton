//
// Created by Dan on 22/04/2023.
//

#ifndef GAMEENGINESKELETON_SRC_DRAWABLERECTANGLE_H_
#define GAMEENGINESKELETON_SRC_DRAWABLERECTANGLE_H_

#include <array>
#include <tuple>

#include "Drawable.h"

namespace rts
{
	class DrawableRectangle
	{
		static constexpr std::array<std::tuple<float, float>, 6> m_BoxCoords{std::make_tuple(1.0f, 0.0f), std::make_tuple(0.0f, 0.0f), std::make_tuple(1.0f, 1.0f),
																			 std::make_tuple(1.0f, 1.0f), std::make_tuple(0.0f, 0.0f), std::make_tuple(0.0f, 1.0f)};

		[[maybe_unused]] Drawable<DrawableRectangle> &m_Parent;

		std::tuple<float, float> m_Size{};
		std::tuple<float, float> m_Position{};

		std::tuple<uint8_t, uint8_t, uint8_t> m_ColourRGB;

	public:
		DrawableRectangle() = delete;
		explicit DrawableRectangle(Drawable<DrawableRectangle> &parent, const std::tuple<float, float> &size, const std::tuple<float, float> &position, const std::tuple<uint8_t, uint8_t, uint8_t> &colourRGB)
			: m_Parent(parent), m_Size(size), m_Position(position), m_ColourRGB(colourRGB) {}


		template <std::output_iterator<rts::Vertex> IteratorType>
		void draw(IteratorType outputBegin) const noexcept
		{
			const auto &[width, height] = m_Size;
			const auto &[posX, posY] = m_Position;

			for(auto &[boxX, boxY] : m_BoxCoords)
			{
				*(outputBegin++) = std::make_tuple(posX + (width * boxX), posY + (height * boxY), 0.0f, 0.0f, m_ColourRGB);
			}
		}

		void setPosition(const std::tuple<float, float> &newPosition) noexcept
		{
			m_Position = newPosition;
		}

		[[nodiscard]] const std::tuple<float, float> &getPosition() const
		{
			return m_Position;
		}
	};
} // rts

#endif //GAMEENGINESKELETON_SRC_DRAWABLERECTANGLE_H_
