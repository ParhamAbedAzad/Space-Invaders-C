#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <cstdlib>
#include <sstream>
#include <time.h>
int main(){
    bool beam = 0;
    int bc,point=0,combo=0;
    float v = 1.5;
    int i,j,t=4,k,T=0.5,mana = 0;
    srand(time(NULL));
    float Px0,Px1,Py0,Py1,Sx,Sy;
    using namespace sf;
    using namespace std;
    stringstream type;
    SoundBuffer beambuff;
    beambuff.loadFromFile("196914_3660887-lq.wav");
    Sound beamsound(beambuff);
    type << "X" << combo;
    Font font;
    font.loadFromFile("Infinite_Stroke.otf");
    Text text_p(type.str(),font);
    text_p.setCharacterSize(50);
    text_p.setColor(Color::Red);
    text_p.setPosition(1000,0);
    Text text_c(type.str(),font);
    text_c.setCharacterSize(50);
    text_c.setColor(Color::Red);
    text_c.setRotation(-30);
    text_c.setPosition(1000,200);
    Text text_m(type.str(),font);
    text_m.setCharacterSize(50);
    text_m.setColor(Color::Blue);
    Clock beamclock;
    Clock clock;
    Texture beamtex;
    beamtex.loadFromFile("LaserBeam.jpg");
    Sprite beamsprite(beamtex);
    Music music;
    music.openFromFile("Doom (PC)_ End Game (Sweet Little Dead Bunny) - Video Game Music.wav");
    music.play();
    SoundBuffer buffer;
    buffer.loadFromFile("151022_1838182-lq.wav");
    Sound sound;
    sound.setBuffer(buffer);
    RenderWindow window(VideoMode(1366, 768), "Space Invaders",Style::Fullscreen);
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);
    Texture bullettex;
    Texture invadertex;
    Texture spacetex;
    Texture spaceshiptex;
    Texture alienshottex;
    alienshottex.loadFromFile("alienshot.png");
    spacetex.loadFromFile("space.jpg");
    bullettex.loadFromFile("LaserBullet.png");
    invadertex.loadFromFile("alien.png");
    invadertex.setSmooth(true);
    spaceshiptex.loadFromFile("spaceship.png");
    spaceshiptex.setSmooth(true);
    bullettex.setSmooth(true);
    music.setLoop(true);
    Sprite invaders[1000];
    int ic[1000];
    int Sc[1000];
    for(k=0;k<1000;k++){
        i = rand()%10;
        j = rand()%400;
        j *= -1;
        ic[k]=1;
        Sc[k]=0;
        invaders[k].setTexture(invadertex);
        invaders[k].setPosition(i*128.f,j*128.f);
    }
    Sprite bullet[2];
    bullet[1].setTexture(bullettex);
    bullet[0].setTexture(bullettex);
    bullet[0].setPosition(10000,10000);
    bullet[1].setPosition(10000,10000);
    Sprite alienshot[1000];
    for(i=0;i<1000;i++){
        alienshot[i].setTexture(alienshottex);
        alienshot[i].setPosition(0,768);
    }
    Sprite spaceship(spaceshiptex);
    Sprite space(spacetex);
    space.setScale(1/1.4,1/1.4);
    bullet[0].setScale(0.5,0.5);
    bullet[1].setScale(0.5,0.5);
    while (window.isOpen()){
        window.clear();
        if(clock.getElapsedTime().asSeconds() > T){
            v += 0.0005;
            T += 0.2;
        }
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseMoved)
                spaceship.setPosition(event.mouseMove.x-spaceship.getLocalBounds().width/2,event.mouseMove.y-spaceship.getLocalBounds().height/2);
            if (event.type == Event::KeyPressed){
                 switch (event.key.code){
                case Keyboard::Escape:
                    window.close();
                    break;
                 }
            }
            if(event.mouseButton.button == Mouse::Right && beamclock.getElapsedTime().asSeconds() > 1.f && mana>200){
                 mana -= 200;
                 beamsound.play();
                 beamclock.restart();
                 beam = 1;
                 beamsprite.setPosition(spaceship.getPosition().x +54.5,spaceship.getPosition().y - 765);
                 for(i=0;i<1000;i++){
                    if(invaders[i].getPosition().x<beamsprite.getPosition().x+165 && invaders[i].getPosition().x>beamsprite.getPosition().x-128 && invaders[i].getPosition().y > 0) {
                        ic[i] = 0;
                        combo++;
                    }
                 }
            }
        }
        if((int)((clock.getElapsedTime()).asSeconds()*v*1.3) == t){
            t = 1;
            if(bc == 0)
                bc = 1;
            else
                bc = 0;
            bullet[bc].setPosition(event.mouseMove.x-3,event.mouseMove.y-spaceship.getLocalBounds().height/2 + 6);
            sound.play();
            clock.restart();
        }
        window.draw(space);
        bullet[0].move(0,-30.f);
        if(bullet[0].getPosition().y<0 && bullet[0].getPosition().y>-30)
            combo = 0;
        bullet[1].move(0,-30.f);
        if(bullet[1].getPosition().y<0 && bullet[1].getPosition().y>-30)
            combo = 0;
        Px0 = bullet[0].getPosition().x;
        Py0 = bullet[0].getPosition().y;
        Px1 = bullet[1].getPosition().x;
        Py1 = bullet[1].getPosition().y;
        Sx = spaceship.getPosition().x;
        Sy = spaceship.getPosition().y;
        for(i=0;i<1000;i++){
            if(invaders[i].getPosition().x-14<Px0&&invaders[i].getPosition().x+128>Px0&&invaders[i].getPosition().y<Py0&&invaders[i].getPosition().y+128>Py0&&ic[i] == 1 && invaders[i].getPosition().y+128>0){
                ic[i] = 0;
                point += (1000 + combo*100);
                mana += (combo + 5);                if(mana>1000)
                    mana = 1000;
                combo++;
                bullet[0].setPosition(10000,10000);
            }if(invaders[i].getPosition().x-14<Px1&&invaders[i].getPosition().x+128>Px1&&invaders[i].getPosition().y<Py1&&invaders[i].getPosition().y+128>Py1&&ic[i] == 1 && invaders[i].getPosition().y + 128>0){
                ic[i] = 0;
                point += (1000 + combo*100);
                mana += (combo + 5);
                if(mana>1000)
                    mana = 1000;
                combo++;
                bullet[1].setPosition(10000,10000);
            }
            if(invaders[i].getPosition().x-100<Sx&&invaders[i].getPosition().x+45>Sx&&invaders[i].getPosition().y-100<Sy&&invaders[i].getPosition().y+45>Sy&&ic[i] == 1){
                window.close();
            }
                if(ic[i] == 1){
                    window.draw(invaders[i]);
                    invaders[i].move(0,v);
                    if(invaders[i].getPosition().y > 768 && invaders[i].getPosition().y < 800)
                        window.close();
                }
            }
        i=rand()%200;
        Vector2f v1(64.f, 128.f);
        for(j=1;j<6;j++){
            i *= j;
            if(invaders[i].getPosition().y>0 && ic[i] == 1 && Sc[i] != 1){
                alienshot[i].setPosition(invaders[i].getPosition()+v1);
                Sc[i] = 1;
            }
            i /= j;
        }
        for(i=0;i<1000;i++){
        alienshot[i].move(0,10);;
        if(alienshot[i].getPosition().x<Sx+100&&alienshot[i].getPosition().x>Sx&&alienshot[i].getPosition().y<Sy+100&&alienshot[i].getPosition().y>Sy){
                window.close();
        }
        window.draw(alienshot[i]);
        }
        window.draw(spaceship);
        window.draw(bullet[0]);
        window.draw(bullet[1]);
        if(beam == 1){
            window.draw(beamsprite);
            if(beamclock.getElapsedTime().asSeconds() > 0.5)
                beam = 0;
        }
        type.str("");
        type << point;
        text_p.setString(type.str());
        window.draw(text_p);
        type.str("");
        type << "X" << combo;
        text_c.setString(type.str());
        window.draw(text_c);
        type.str("");
        type << mana << "/1000";
        text_m.setString(type.str());
        window.draw(text_m);
        window.display();

    }
/*	sf::RenderWindow window(sf::VideoMode(640, 480), "Building Games with SFML");
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(200, 100));
	rectangle.setFillColor(sf::Color::Green);
	sf::CircleShape circle;
	circle.setRadius(20);
	circle.setFillColor(sf::Color::Blue);
	circle.setOutlineThickness(4);
	circle.setOutlineColor(sf::Color::Yellow);

	sf::ConvexShape customShape;
	customShape.setPointCount(3);
	customShape.setPoint(0, sf::Vector2f(0,0));
	customShape.setPoint(1, sf::Vector2f(150,30));
	customShape.setPoint(2, sf::Vector2f(0,60));

	customShape.setFillColor(sf::Color::Magenta);

	sf::Image image;
	image.loadFromFile("assets/image.png");

	sf::Texture texture;
	texture.loadFromImage(image);

	sf::Sprite sprite(texture);
	sf::Font font;
	font.loadFromFile("font.ttf");


	sf::Text text;
	text.setFont(font);
	text.setString("ola SFML");
	text.setColor(sf::Color::Red);


	sf::Sprite sprite2(texture);
	sprite2.setPosition(300, 300);
	sprite2.setRotation(45);

	rectangle.setPosition(10, 10);
	circle.setPosition(400, 50);
	customShape.setPosition(250, 250);

	 while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();

                if (event.mouseButton.button == sf::Mouse::Left)
                std::cout << "Left Button";

                else if (event.mouseButton.button == sf::Mouse::Right)
                std::cout << "Right Button";
                std::cout << event.mouseButton.x << "&" << event.mouseButton.y << std::endl;

        }

        window.clear();

        window.draw(rectangle);
        window.draw(circle);
        window.draw(customShape);
        window.draw(sprite);
        window.draw(sprite2);
        window.draw(text);

        window.display();

        window.setFramerateLimit(60);
        sf::sleep(sf::seconds(1.f/60.f));
    }*/

	 return EXIT_SUCCESS;
}


