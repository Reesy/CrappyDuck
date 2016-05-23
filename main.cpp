
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
#include <math.h>
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"


//game objects
sf::RenderWindow window(sf::VideoMode(430, 750), "Crappy Duck");


sf::Image icon;
// Load a sprite to display
sf::Texture texture;

//pipe textures
sf::Texture pipe_texture;
sf::Texture paused_icon;

sf::Sprite paused_sprite;
sf::Sprite sprite;
sf::Sprite pipe_sprite;
sf::Music music;


sf::Texture top_pipe;
sf::Texture bottom_pipe;

sf::Sprite top_pipe_sprite;
sf::Sprite bottom_pipe_sprite;

sf::Sprite numbers;

sf::RectangleShape birdBox(sf::Vector2f(55, 45));

sf::RectangleShape topPipeBox(sf::Vector2f(70, 400));

sf::RectangleShape bottomPipeBox(sf::Vector2f(70, 400));


sf::Font font;
sf::Text text("So beta, wow", font, 50);

sf::Texture birdTexture1;
sf::Sprite birdSprite;

sf::Texture birdTexture2;

sf::Texture birdTexture3;

sf::Texture One;
sf::Texture Two;
sf::Texture Three;
sf::Texture Four;
sf::Texture Five;
sf::Texture Six;
sf::Texture Seven;
sf::Texture Eight;
sf::Texture Nine;


sf::Event event;
std::vector<sf::Sprite> birdAnimation;
static void lerp(float currentPosition, float outputPosition, float deltaTime);

int gap = 140; //change this to increase difficulty by making gaps from each pillar wider
int pipe_gap; // This is the vertical gap between the pair of piped
int currentdistance;
int frameCounter;
int score;
float currentTimeSlice;
float accumulator;
float animateSpeed;
bool started;
bool countBlock;
bool paused;
bool endState;
bool flight; // this is true when the user has input a jump command for a specific unit of time.
bool flapping;
float timeOfClick;

static void collided(){
    
 
    if(birdBox.getGlobalBounds().intersects(topPipeBox.getGlobalBounds()) || birdBox.getGlobalBounds().intersects(bottomPipeBox.getGlobalBounds())){
        paused = true;
    }
}

static void update(float elapsed){
    float delta = elapsed * 60;
    int speed = 5;
    
    pipe_sprite.move((-speed * delta), 0);
    bottom_pipe_sprite.move((-speed * delta), 0);
    bottomPipeBox.move((-speed * delta), 0);
    topPipeBox.move((-speed * delta), 0);
    
    top_pipe_sprite.move((-speed * delta), 0);
    if(pipe_sprite.getPosition().x < -40){
        pipe_sprite.move(40, 0);
        
    }
  
    if(bottomPipeBox.getPosition().x < 110 && countBlock == false){
        score++;
        countBlock = true;
        std::cout << "The Score is: " << score << std::endl;
    }
 
    if(bottom_pipe_sprite.getPosition().x < -50){
        int random_dist = rand() % 2;
        if(random_dist == 0 & bottom_pipe_sprite.getPosition().y < gap){
            currentdistance += gap;
        }else{
            currentdistance -= gap;
        }
        top_pipe_sprite.move(500, 0);
        bottom_pipe_sprite.move(500, 0);
        bottomPipeBox.move(500, 0);
        topPipeBox.move(500, 0);
        
        bottom_pipe_sprite.setPosition(bottom_pipe_sprite.getPosition().x, currentdistance);
        bottomPipeBox.setPosition(bottomPipeBox.getPosition().x, currentdistance);
        top_pipe_sprite.setPosition(top_pipe_sprite.getPosition().x, (400 + gap)+ currentdistance);
        topPipeBox.setPosition(top_pipe_sprite.getPosition().x, (400 + gap)+ currentdistance);
        countBlock = false;
       
    }
    collided();
    //gravity
    
    if(flight){
        timeOfClick += delta;
        std::cout << timeOfClick << std::endl;
        if(timeOfClick > 15){
            flight = false;
        }
    }
    
    if(flight){
        birdSprite.move(0, -4);
        birdBox.move(0, -4);
    }else{
        birdSprite.move(0, 4);
        birdBox.move(0, 4);
    }
}


static void birdAnimate(float elapsedTime){
 //   birdSprite.setTexture(birdTexture1);
    accumulator += elapsedTime * animateSpeed;
  
    if(accumulator > 1 && accumulator < 2){
        birdSprite.setTexture(birdTexture1);
    }else if(accumulator > 2 && accumulator < 3){
        birdSprite.setTexture(birdTexture2);
    }else if(accumulator > 3 && accumulator < 4){
        birdSprite.setTexture(birdTexture3);
    }else if(accumulator > 4){
        birdSprite.setTexture(birdTexture2);
        accumulator = 0;
    }
}

static void render(){
    // Draw the sprite
    window.draw(sprite);
    
    window.draw(bottom_pipe_sprite);
    
    window.draw(top_pipe_sprite);
    
    window.draw(pipe_sprite);
    
    window.draw(birdBox);
   
    window.draw(birdSprite);
    
    window.draw(bottomPipeBox);
    
    window.draw(topPipeBox);
   
    if(paused == true){
        window.draw(paused_sprite);
    }
}
static void lerp(float currentPosition, float outputPosition, float deltaTime){
    
    
    std::cout << sin(deltaTime) << std::endl;
    
    
    
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
        timeOfClick = 0;
        flight = true;
    }
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K){
        paused = false;
    }
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left){
        birdSprite.setTexture(birdTexture1);
    }
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right){
        birdSprite.setTexture(birdTexture2);
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
    
    if (!bottom_pipe.loadFromFile(resourcePath() + "flappy.png", sf::IntRect(302, 0, 27, 135))) {
        return EXIT_FAILURE;
    }
    if (!top_pipe.loadFromFile(resourcePath() + "flappy.png", sf::IntRect(330, 0, 27, 135))) {
        return EXIT_FAILURE;
    }
    if (!paused_icon.loadFromFile(resourcePath() + "flappy.png", sf::IntRect(242, 197, 40, 13))){
        return EXIT_FAILURE;
        
    }
    
    if (!birdTexture1.loadFromFile(resourcePath() + "flappy.png", sf::IntRect(220, 120, 20, 20))){
        return EXIT_FAILURE;
        
    }
    if (!birdTexture2.loadFromFile(resourcePath() + "flappy.png", sf::IntRect(261, 86, 20, 20))){
        return EXIT_FAILURE;
        
    }
    if (!birdTexture3.loadFromFile(resourcePath() + "flappy.png", sf::IntRect(261, 60, 20, 20))){
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
    window.setFramerateLimit(60);
    sprite.setScale(3, 3);
    sprite.setTexture(texture);
    
    pipe_sprite.setScale(4, 3);
    pipe_sprite.setTexture(pipe_texture);
    paused_sprite.setTexture(paused_icon);
    paused_sprite.move(130, 200);
    paused_sprite.setScale(4,4);
    pipe_gap = 20;
    bottom_pipe_sprite.setTexture(bottom_pipe);
    bottom_pipe_sprite.setScale(3,3);
    bottomPipeBox.move(600, 0);
    
    bottom_pipe_sprite.move(600, 0);
    
    top_pipe_sprite.setTexture(top_pipe);
    top_pipe_sprite.setScale(3, 3);
    top_pipe_sprite.move(600, 400 + gap);
    topPipeBox.move(600, 400 + gap);
    
    birdSprite.setTexture(birdTexture1);
    birdSprite.setScale(4, 4);
    birdSprite.move(160, 240);
    
    birdBox.move(178,258);
    
    pipe_sprite.move(0, 600);
    music.play();
    currentdistance = 0;
    paused = false;
    started = true;
    endState = false;
    frameCounter = 0;
    
    animateSpeed = 5;
    timeOfClick = 0;
    flight = false;
    flapping = false;
    //birdAnimation.push_back(pipe_sprite);
}

int main(int, char const**)
{
    // Create the main window
    loadResources();
    init();
    
    sf::Clock clock;
    
    
    // Start the game loop
    while (window.isOpen())
    {
        
        sf::Time elapsed = clock.restart();
        
        while (window.pollEvent(event))
        {
            input();
        }
        
        // Clear screen
        window.clear();
    
        birdAnimate(elapsed.asSeconds());
        render();
        if(paused == false && started == true){
            update(elapsed.asSeconds());
        }
    
        window.display();
        
    }

    return EXIT_SUCCESS;
    
}



