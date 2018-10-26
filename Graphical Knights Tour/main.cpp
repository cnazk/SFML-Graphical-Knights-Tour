#include "Knight.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

bool musicPlaying = false;

RenderWindow * window;

Texture whiteTexture;
Texture blackTexture;

Texture knightTexture;

Font font;

Board *board;

int initialValues() {
    
    window = new RenderWindow(VideoMode(800, 800), "Knight's Tour", Style::Close);
    
    Image icon;
    if (!icon.loadFromFile("/Users/cnazaker/Projects/Xcode Projects/Graphical Knights Tour/Graphical Knights Tour/Board/ChessIcon.png")) {
        return EXIT_FAILURE;
    }
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    if (!whiteTexture.loadFromFile("/Users/cnazaker/Projects/Xcode Projects/Graphical Knights Tour/Graphical Knights Tour/Board/white.png")) {
        return EXIT_FAILURE;
    }
    whiteTexture.setSmooth(true);
    
    if (!blackTexture.loadFromFile("/Users/cnazaker/Projects/Xcode Projects/Graphical Knights Tour/Graphical Knights Tour/Board/gray.png")) {
        return EXIT_FAILURE;
    }
    blackTexture.setSmooth(true);
    
    if (!font.loadFromFile("/Users/cnazaker/Projects/Xcode Projects/Graphical Knights Tour/Graphical Knights Tour/sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    if (!knightTexture.loadFromFile("/Users/cnazaker/Projects/Xcode Projects/Graphical Knights Tour/Graphical Knights Tour/Board/ChessIcon.png")) {
        return EXIT_FAILURE;
    }
    knightTexture.setSmooth(true);
}

void drawWindow() {
    window->clear();
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Sprite s = (i + j) % 2 ? Sprite(blackTexture) : Sprite(whiteTexture);
            s.setPosition(i * (float)window->getSize().x / 8, j * (float)window->getSize().x / 8);
            s.setScale((float)window->getSize().x / 800, (float)window->getSize().x / 800);
            window->draw(s);
            
            if (board->HasGameStarted) {
                if (board->Get(i, j)->state == State::AlreadyIn) {
                    Sprite knightSprite(knightTexture);
                    knightSprite.setPosition(i * (float)window->getSize().x / 8, j * (float)window->getSize().x / 8);
                    knightSprite.setScale((float)window->getSize().x / 800, (float)window->getSize().x / 800);
                    cout<<knightSprite.getScale().x<<endl;
                    
                    window->draw(knightSprite);
                }
                
                else {
                    Text text(board->Get(i, j)->GetOrder(), font, 50);
                    text.setStyle(Text::Bold);
                    text.setPosition(i * (float)window->getSize().x / 8 + 20, j * (float)window->getSize().x / 8 + 20);
                    text.setFillColor(Color::Black);
                    window->draw(text);
                }
            }
        }
    }
}

int main(int argc, char const** argv)
{
    
    initialValues();
    
    board = new Board();

    while (window->isOpen())
    {
        Event event;
        while (window->pollEvent(event))
        {
            
            if (event.type == Event::Closed) {
                window->close();
            }
            
            if (event.type == Event::MouseButtonPressed && !board->HasGameStarted) {
                board = new Board(Term((int)(Mouse::getPosition(*window).x / ((float)window->getSize().x / 8)), (int)(Mouse::getPosition(*window).y / ((float)window->getSize().x / 8))));
            }
            
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
                board = new Board();
            }
            
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                if (!board->HasGameStarted || board->HasMetAllCells())
                    continue;
//                if(!board->HasMetAllCells())
                board->MoveToLeastOrder();
            }
            
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window->close();
            }
        }
        
        drawWindow();
        window->display();
    }

    return EXIT_SUCCESS;
}
