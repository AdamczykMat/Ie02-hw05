#include <iostream>
#include <vector>
#include <memory>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class CustomSprite : public sf::Sprite {
public:
    CustomSprite(){}

    void setSpeed(const int& x_speed, const int& y_speed) {
        x_speed_ = x_speed;
        y_speed_ = y_speed;
    }

    void setBounds(const float& l_bound, const float& r_bound,const float& u_bound,const float& d_bound){
        l_bound_  = l_bound  ;
        r_bound_  = r_bound  ;
        u_bound_  = u_bound  ;
        d_bound_  = d_bound  ;
    }
    void setWallBounds(const float& l_bound, const float& r_bound,const float& u_bound,const float& d_bound){
        wall_l_bound_.emplace_back(l_bound);
        wall_r_bound_.emplace_back(r_bound);
        wall_u_bound_.emplace_back(u_bound);
        wall_d_bound_.emplace_back(d_bound);
    }

    void moveInDirection(const sf::Time &elapsed, const sf::Keyboard::Key &key)
    {
        float dt = elapsed.asSeconds();
        if(key == sf::Keyboard::Up)
        {
            y_speed_ = -1*abs(y_speed_);
            bouncce();

            sf::FloatRect rectangle_bounds = getGlobalBounds();
            for(int i =0;i<wall_d_bound_.size();i++)
            if((rectangle_bounds.top < wall_d_bound_[i] && rectangle_bounds.top > wall_u_bound_[i]) && (rectangle_bounds.left < wall_r_bound_[i] && rectangle_bounds.left + rectangle_bounds.width > wall_l_bound_[i]))
            {y_speed_ = abs(y_speed_);

            std::cout << "Colision up" << std::endl;}

            move(0,y_speed_*dt);
        }
        else if(key == sf::Keyboard::Down)
        {
            y_speed_ = abs(y_speed_);
            bouncce();

            sf::FloatRect rectangle_bounds = getGlobalBounds();
            for(int i =0;i<wall_d_bound_.size();i++)
            if((rectangle_bounds.top + rectangle_bounds.height > wall_u_bound_[i] && rectangle_bounds.top < wall_d_bound_[i])&&(rectangle_bounds.left < wall_r_bound_[i] && rectangle_bounds.left + rectangle_bounds.width  > wall_l_bound_[i]))
            {y_speed_ = abs(y_speed_) * -1;

            std::cout << "Colision down" << std::endl;}

            move(0,y_speed_*dt);
        }
        else if(key == sf::Keyboard::Left)
        {
            x_speed_ = -1*abs(x_speed_);
            bouncce();

            sf::FloatRect rectangle_bounds = getGlobalBounds();
            for(int i =0;i<wall_d_bound_.size();i++)
            if((rectangle_bounds.left < wall_r_bound_[i] && rectangle_bounds.left > wall_l_bound_[i]) && (rectangle_bounds.top + rectangle_bounds.height > wall_u_bound_[i] && rectangle_bounds.top < wall_d_bound_[i]))
                    {x_speed_ = abs(x_speed_);
                    std::cout << "Colision right" << std::endl;}

            move(x_speed_*dt,0);
        }
        else if(key == sf::Keyboard::Right)
        {
            x_speed_ = abs(x_speed_);
            bouncce();

            sf::FloatRect rectangle_bounds = getGlobalBounds();
            for(int i =0;i<wall_d_bound_.size();i++)
            if((rectangle_bounds.left < wall_r_bound_[i] && rectangle_bounds.left + rectangle_bounds.width > wall_l_bound_[i]) && (rectangle_bounds.top + rectangle_bounds.height > wall_u_bound_[i] && rectangle_bounds.top < wall_d_bound_[i]))
            {x_speed_ = abs(x_speed_) * -1;
            std::cout << "Colision left" << std::endl;}

            move(x_speed_*dt,0);
        }
    }


private:
    int x_speed_ = 0 ;
    int y_speed_ = 0 ;
    float l_bound_ = 0;
    float r_bound_ = 0;
    float u_bound_ = 0;
    float d_bound_ = 0;

    std::vector<float> wall_l_bound_;
    std::vector<float> wall_r_bound_;
    std::vector<float> wall_u_bound_;
    std::vector<float> wall_d_bound_;


    void bouncce(){
        sf::FloatRect rectangle_bounds = getGlobalBounds();
        std::cout << rectangle_bounds.top << " / " << rectangle_bounds.left << std::endl;

        if(rectangle_bounds.top <= u_bound_)
        {y_speed_ = abs(y_speed_);}

        if(rectangle_bounds.top + rectangle_bounds.height >= d_bound_)
        {y_speed_ = abs(y_speed_) * -1;}

        if(rectangle_bounds.left <= l_bound_ )
        {x_speed_ = abs(x_speed_);}

        if(rectangle_bounds.left + rectangle_bounds.width >= r_bound_)
        {x_speed_ = abs(x_speed_) * -1;}
    }

};


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::Texture texture_bg;
    sf::Texture texture_guy;
    sf::Texture texture_wall;

    if(!texture_bg.loadFromFile("grass.png")) {std::cerr << "Could not load texture" << std::endl; }//return 0;
    if(!texture_guy.loadFromFile("guy.png")) {std::cerr << "Could not load texture" << std::endl; }//return 0;
    if(!texture_wall.loadFromFile("wall.png")) {std::cerr << "Could not load texture" << std::endl;}// return 0;


    texture_bg.setRepeated(true);
    sf::Sprite sprite_bg;
    sprite_bg.setTexture(texture_bg);
    sprite_bg.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));


    CustomSprite guy;
    guy.setPosition(1.0,1.0);
    guy.setTexture(texture_guy);


    texture_wall.setRepeated(true);
    sf::Sprite wall;
    wall.setTexture(texture_wall);
    wall.setTextureRect(sf::IntRect(0, 0, 50, 250));
    wall.setPosition(25.0,100.0);

    sf::Sprite wall2;
    wall2.setTexture(texture_wall);
    wall2.setTextureRect(sf::IntRect(0, 0, 50, 300));
    wall2.setPosition(200.0,200.0);

    sf::Sprite wall3;
    wall3.setTexture(texture_wall);
    wall3.setTextureRect(sf::IntRect(0, 0, 150, 50));
    wall3.setPosition(350.0,75.0);

    sf::Sprite wall4;
    wall4.setTexture(texture_wall);
    wall4.setTextureRect(sf::IntRect(0, 0, 50, 350));
    wall4.setPosition(500.0,200.0);

    sf::Sprite wall5;
    wall5.setTexture(texture_wall);
    wall5.setTextureRect(sf::IntRect(0, 0, 200, 50));
    wall5.setPosition(550.0,400.0);


    //--------

//    shapes_vec.emplace_back(std::make_unique<CustomRectangleShape>(rectangle_inh));s
//    shapes_vec.emplace_back(std::make_unique<sf::Sprite>(sprite_bg));
//    shapes_vec.emplace_back(std::make_unique<sf::Sprite>(guy));
//    shapes_vec.emplace_back(std::make_unique<sf::Sprite>(wall));


    sf::Clock clock;


    guy.setBounds(0, window.getSize().x, 0, window.getSize().y);
    guy.setWallBounds(wall.getGlobalBounds().left , wall.getGlobalBounds().left + wall.getTextureRect().width ,wall.getGlobalBounds().top , wall.getGlobalBounds().top + wall.getTextureRect().height);
    guy.setWallBounds(wall2.getGlobalBounds().left , wall2.getGlobalBounds().left + wall2.getTextureRect().width ,wall2.getGlobalBounds().top , wall2.getGlobalBounds().top + wall2.getTextureRect().height);
    guy.setWallBounds(wall3.getGlobalBounds().left , wall3.getGlobalBounds().left + wall3.getTextureRect().width ,wall3.getGlobalBounds().top , wall3.getGlobalBounds().top + wall3.getTextureRect().height);
    guy.setWallBounds(wall4.getGlobalBounds().left , wall4.getGlobalBounds().left + wall4.getTextureRect().width ,wall4.getGlobalBounds().top , wall4.getGlobalBounds().top + wall4.getTextureRect().height);
    guy.setWallBounds(wall5.getGlobalBounds().left , wall5.getGlobalBounds().left + wall5.getTextureRect().width ,wall5.getGlobalBounds().top , wall2.getGlobalBounds().top + wall5.getTextureRect().height);

    std::cout << wall.getGlobalBounds().left <<"/"<< wall.getGlobalBounds().left + wall.getTextureRect().width <<"/"<<wall.getGlobalBounds().top <<"/"<< wall.getGlobalBounds().top + wall.getTextureRect().height;

    guy.setSpeed(100.0,100.0);
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ guy.moveInDirection(elapsed,sf::Keyboard::Right);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){ guy.moveInDirection(elapsed,sf::Keyboard::Left);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){ guy.moveInDirection(elapsed,sf::Keyboard::Up);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){ guy.moveInDirection(elapsed,sf::Keyboard::Down);}

        window.clear(sf::Color::Black);

        window.draw(sprite_bg);
        window.draw(wall);
        window.draw(wall2);
        window.draw(wall3);
        window.draw(wall4);
        window.draw(wall5);
        window.draw(guy);
        window.display();
    }

    return 0;
}
