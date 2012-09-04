#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>

bool PixelPerfectTest(const sf::Sprite& Object1, const sf::Image& Image1, const sf::Sprite& Object2, const sf::Image& Image2, sf::Uint8 AlphaLimit) {
    sf::FloatRect Object1AABB = Object1.getGlobalBounds();
    sf::FloatRect Object2AABB = Object2.getGlobalBounds();
 
    sf::FloatRect Intersection;

    if (Object1AABB.intersects(Object2AABB, Intersection))
	{
        if (AlphaLimit == 0) return true;
 
        sf::FloatRect O1SubRect = Object1.getLocalBounds();
        sf::FloatRect O2SubRect = Object2.getLocalBounds();
 
        sf::Vector2f O1SubRectSize(O1SubRect.width, O1SubRect.height);
        sf::Vector2f O2SubRectSize(O2SubRect.width, O2SubRect.height);
 
        sf::Vector2f o1v;
        sf::Vector2f o2v;

        //Loop through our pixels
		for (int i = static_cast<int>(Intersection.left); i < static_cast<int>(Intersection.width + Intersection.left); i++) {
			for (int j = static_cast<int>(Intersection.top); j < static_cast<int>(Intersection.height + Intersection.top); j++) {

				o1v.x = static_cast<float>(i);
				o1v.y = static_cast<float>(j);

				o2v.x = static_cast<float>(i);
				o2v.y = static_cast<float>(j);

                o1v = Object1.getInverseTransform().transformPoint(o1v);
                o2v = Object2.getInverseTransform().transformPoint(o2v);
 
				//Hack to make sure pixels fall withint the Sprite's Image
                if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
                        o1v.x < O1SubRectSize.x && o1v.y < O1SubRectSize.y &&
                        o2v.x < O2SubRectSize.x && o2v.y < O2SubRectSize.y) {
 
					sf::Color c1 = Image1.getPixel(static_cast<unsigned int> (o1v.x), static_cast<unsigned int> (o1v.y));
					sf::Color c2 = Image2.getPixel(static_cast<unsigned int> (o2v.x), static_cast<unsigned int> (o2v.y));

                    //If both sprites have opaque pixels at the same point we've got a hit
                    if (c1.a > AlphaLimit && c2.a > AlphaLimit) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    return false;
}