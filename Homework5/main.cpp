#include <iostream>
#include <vector>
#include <memory>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class CustomRectangleShape : public sf::RectangleShape {
public:
    CustomRectangleShape(const sf::Vector2f &size, const sf::Vector2f &position) : sf::RectangleShape(size)
    {
        setPosition(position);
    }

    void setSpeed(const int& x_speed, const int& y_speed, const int & ro_speed) {
        x_speed_ = x_speed;
        y_speed_ = y_speed;
        ro_speed_ = ro_speed;
    }

    void animate(const sf::Time &elapsed){
        bouncce();
        float dt = elapsed.asSeconds();
        move(x_speed_*dt,y_speed_*dt);
        rotate(ro_speed_*dt);
    }

    void setBounds(const float& l_bound, const float& r_bound,const float& u_bound,const float& d_bound){
        l_bound_  = l_bound  ;
        r_bound_  = r_bound  ;
        u_bound_  = u_bound  ;
        d_bound_  = d_bound  ;
    }

private:
    int x_speed_ = 0 ;
    int y_speed_ = 0 ;
    int ro_speed_ = 0 ;
    float l_bound_ = 0;
    float r_bound_ = 0;
    float u_bound_ = 0;
    float d_bound_ = 0;


    void bouncce(){
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(rectangle_bounds.top <= u_bound_){
            y_speed_ = abs(y_speed_);
        }

        if(rectangle_bounds.top + rectangle_bounds.height >= d_bound_){
            y_speed_ = abs(y_speed_) * -1;
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds.left <= l_bound_ ){
           x_speed_ = abs(x_speed_);
           setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds.left + rectangle_bounds.width >= r_bound_){
            x_speed_ = abs(x_speed_) * -1;
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }
    }


};

void create_shapes(std::vector<std::unique_ptr<sf::Drawable>> &shapes_vec){

}




int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");


    std::vector<std::unique_ptr<sf::Drawable>> shapes;
    create_shapes(shapes);
    //--------
    sf::Vector2f size(120.0, 60.0);
    sf::Vector2f position(120.0, 60.0);
    CustomRectangleShape rectangle_inh(size, position);
    rectangle_inh.setFillColor(sf::Color(150, 100, 50));
    rectangle_inh.setSpeed(100, 150, 10);

    sf::Texture texture_bg;
    sf::Texture texture_guy;
    sf::Texture texture_wall;

    if(!texture_bg.loadFromFile("grass.png")) {std::cerr << "Could not load texture" << std::endl; }//return 0;
    if(!texture_guy.loadFromFile("guy.png")) {std::cerr << "Could not load texture" << std::endl; }//return 0;
    if(!texture_wall.loadFromFile("wall.png")) {std::cerr << "Could not load texture" << std::endl;}// return 0;

    sf::Sprite sprite_bg;

    texture_bg.setRepeated(true);

    sprite_bg.setTexture(texture_bg);
    sprite_bg.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));



    sf::Sprite guy;
    guy.setTexture(texture_guy);


    texture_wall.setRepeated(true);
    sf::Sprite wall;
    wall.setTexture(texture_wall);
    wall.setScale(0.3, 0.3);
    wall.setTextureRect(sf::IntRect(0, 0, 500, 500));

    //--------

//    shapes_vec.emplace_back(std::make_unique<CustomRectangleShape>(rectangle_inh));
//    shapes_vec.emplace_back(std::make_unique<sf::Sprite>(sprite_bg));
//    shapes_vec.emplace_back(std::make_unique<sf::Sprite>(guy));
//    shapes_vec.emplace_back(std::make_unique<sf::Sprite>(wall));


    sf::Clock clock;

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    //guy.animate(elapsed);
                    std::cout << "Space released" << std::endl;
                }
            }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
          //  rectangle_inh.animate(elapsed);
        }

        window.clear(sf::Color::Black);

        for(auto &s : shapes) {
            window.draw(*s);
        }


        window.draw(sprite_bg);
        window.draw(wall);
        window.draw(guy);
        window.display();
    }

    return 0;
}
