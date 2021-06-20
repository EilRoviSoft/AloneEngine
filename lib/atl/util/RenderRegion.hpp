#pragma once
////sf
//#include <SFML/Graphics/Drawable.hpp> //Drawable
//#include <SFML/Graphics/Texture.hpp> //Texture
//#include <SFML/Graphics/RenderTarget.hpp> //RenderTarget
//#include <SFML/Graphics/RenderStates.hpp> //RenderStates
//#include <SFML/Graphics/PrimitiveType.hpp> //PrimituveType
//#include <SFML/Graphics/Rect.hpp> //Rect
//#include <SFML/Graphics/Vertex.hpp> //Vertex
//#include <SFML/System/Vector2.hpp> //Vector2f
//
//namespace atl::util {
//	class RenderRegion : public sf::Drawable {
//	public:
//		RenderRegion() {}
//
//		void setTexture(const sf::Texture& texture) {
//			_texture = &texture;
//		}
//		void setRect(const sf::Rect <uint8_t>& rect) {
//			_rect = rect;
//		}
//
//	protected:
//		void draw(sf::RenderTarget& target, sf::RenderStates states) const {
//			if (_texture) {
//				states.texture = _texture;
//				target.draw(_vertices, 4, sf::TrianglesStrip, states);
//			}
//		}
//
//	private:
//		void _updateTextureCoords() {
//			auto left = _rect.left;
//			auto right = left + _rect.width;
//			auto top = _rect.top;
//			auto bottom = top + _rect.height;
//
//			_vertices[0].texCoords = sf::Vector2f(left, top);
//			_vertices[1].texCoords = sf::Vector2f(left, bottom);
//			_vertices[2].texCoords = sf::Vector2f(right, top);
//			_vertices[3].texCoords = sf::Vector2f(right, bottom);
//
//			_vertices[0].position = sf::Vector2f(0, 0);
//			_vertices[1].position = sf::Vector2f(0, _rect.height);
//			_vertices[2].position = sf::Vector2f(_rect.width, 0);
//			_vertices[3].position = sf::Vector2f(_rect.width, _rect.height);
//		}
//
//		const sf::Texture* _texture;
//		sf::Rect <uint8_t> _rect;
//		sf::Vertex _vertices[4];
//	};
//}