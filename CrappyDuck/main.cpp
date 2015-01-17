
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <iostream>
#include <stdlib.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"


//game objects
sf::RenderWindow window(sf::VideoMode(430, 750), "Crappy Duck");


sf::Image icon;
// Load a sprite to display
sf::Texture texture;

//pipe textures
sf::Texture pipe_texture;
sf::Sprite sprite;
sf::Sprite pipe_sprite;
sf::Music music;


sf::Texture top_pipe;
sf::Texture bottom_pipe;

sf::Sprite top_pipe_sprite;
sf::Sprite bottom_pipe_sprite;


sf::Font font;
sf::Text text("So beta, wow", font, 50);

sf::Event event;

int gap = 100; //change this to increase difficulty by making gaps from each pillar wider
int currentdistance;



static void update(){
    pipe_sprite.move(-1, 0);
    bottom_pipe_sprite.move(-1, 0);
    if(pipe_sprite.getPosition().x < -40){
        pipe_sprite.move(40, 0);
      
    }
  
 
    if(bottom_pipe_sprite.getPosition().x < -50){
        int random_dist = rand() % 2;
        if(random_dist == 0 & bottom_pipe_sprite.getPosition().y < gap){
            currentdistance += gap;
        }else{
            currentdistance -= gap;
        }
        bottom_pipe_sprite.move(500, 0);
        bottom_pipe_sprite.setPosition(bottom_pipe_sprite.getPosition().x, currentdistance);
        std::cout << currentdistance << std::endl;
    }

}

static void render(){
    
    // Draw the sprite
    window.draw(sprite);
    
    // Draw the pipe sprite
    window.draw(pipe_sprite);
    
    window.draw(bottom_pipe_sprite);
    
    
    window.draw(text);
}

static void input(){
    
    // Close window: exit
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    
    // Escape pressed: exit
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        window.close();
    }
    
    // plays music
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
        
        sprite.move(0, 1);
        
    }
    
}

static void loadResources(){
    
    // Set the Icon
    
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
   
    if (!texture.loadFromFile(resourcePath() + "flappy2.png", sf::IntRect(0, 0, 145, 250))) {
        return EXIT_FAILURE;
    }
    
    if (!pipe_texture.loadFromFile(resourcePath() + "flappy2.png", sf::IntRect(150, 0, 150, 50))) {
        return EXIT_FAILURE;
    }
    
    if (!bottom_pipe.loadFromFile(resourcePath() + "flappy.png", sf::IntRect(300, 0, 30, 135))) {
        return EXIT_FAILURE;
    }
    if (!top_pipe.loadFromFile(resourcePath() + "flappy.png", sf::IntRect(300, 0, 30, 135))) {
        return EXIT_FAILURE;
    }
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }

    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }
    
}

static void init(){
    text.setColor(sf::Color::Black);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    sprite.setScale(3, 3);
    sprite.setTexture(texture);
    pipe_sprite.setScale(4, 3 );
    pipe_sprite.setTexture(pipe_texture);
    bottom_pipe_sprite.setTexture(bottom_pipe);
    bottom_pipe_sprite.setScale(3,3);
    bottom_pipe_sprite.move(600, 0);
    
    top_pipe_sprite.setTexture(top_pipe);
    top_pipe_sprite.setScale(3, 3);
    
    
    pipe_sprite.move(0, 600);
    music.play();
    currentdistance = 0;
}

int main(int, char const**)
{
    // Create the main window
    loadResources();
    init();

    // Start the game loop
    while (window.isOpen())
    {
        
        
        while (window.pollEvent(event))
        {
            input();
        }

        // Clear screen
        window.clear();
        
        render();
        update();
        
        window.display();
    }

    return EXIT_SUCCESS;
    

}


