#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <ctime>
#include <unistd.h>

const unsigned int SIZE = 50;
class ChessBoard
{
    std::vector<std::pair<size_t,size_t>> queens;
    sf::RenderWindow window;
    size_t n;
    sf::Image image;
    void addQueen(size_t c,size_t r);
    void removeQueen();
    bool isUnderAttack(size_t c,size_t r) const;
public:
    bool solve(size_t column);
    void draw();
    void setN(size_t n);
};

int main(int , char **)
{
    unsigned int n;
    ChessBoard chessBoard;
    std::cout << "Authors: Anubhab Mukherjee and Soham Kar.\n"
              << "This is an implementation of the classic N Queens problem\n"
              << "Enter n:\n";
    std::cin >> n;
    if(n<4)
    {
        std::cout << "Solutions exist from n=4 onwards.\nSetting n to 4." << std::endl;
        n = 4;
    }
    chessBoard.setN(n);
    chessBoard.solve(0);
}
void ChessBoard::setN(size_t N)
{
    this->n = N;
    window.create(sf::VideoMode(static_cast<uint>(n*SIZE),static_cast<uint>(n*SIZE)),"N Queens",sf::Style::Close);
    image.loadFromFile("./queen.png");
    window.setIcon(image.getSize().x,image.getSize().y,image.getPixelsPtr());

}
void ChessBoard::addQueen(size_t c, size_t r)
{
    queens.push_back(std::make_pair(c, r));
    draw();
}
void ChessBoard::removeQueen()
{
    queens.pop_back();
    draw();
}
bool ChessBoard::isUnderAttack(size_t c, size_t r) const
{
    bool flag = false;
    for(auto& [ic,ir] : queens)
    {
        if(ir == r)
            flag = true;
        if(ic == c)
            flag = true;
        if(ic - ir == c-r)
            flag = true;
        if(ir + ic == r+c)
            flag = true;
    }
    return flag;
}
bool ChessBoard::solve(size_t column)
{
    for(size_t i=0; i<n; i++)
    {
        if(!isUnderAttack(column,i))
        {
            addQueen(column,i);
            if(column+1 < n)
            {
                if(solve(column+1))
                {
                    if(column == 0)
                    {
                        sf::Event event;
                        std::cout << "Press \"SPACE\" to exit..." << std::endl;
                        while(window.isOpen())
                        {
                            if(window.pollEvent(event))
                            {
                                if(event.type == sf::Event::Closed)
                                    window.close();
                                else if(event.type == sf::Event::KeyReleased)
                                    window.close();
                            }
                        }
                    }
                    return true;
                }
                else
                {
                    removeQueen();
                    continue;
                }
            }

            else
                return true;
        }
    }
    return false;
}
void ChessBoard::draw()
{
    if(!window.isOpen())
        exit(0);
    size_t posCol=0,posRow=0;
    sf::Event event;
    sf::RectangleShape rectangle;
    sf::Texture texture;
    sf::Sprite sprite;
    rectangle.setSize(sf::Vector2f(SIZE,SIZE));
    window.setFramerateLimit(60u);
    if(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window.close();
        else if(event.type == sf::Event::KeyPressed)
            window.close();
    }

    window.clear(sf::Color::White);
    for(size_t i=0; i<n; i++)
    {
        for(size_t j=0; j<n; j++)
        {
            if((i+j)%2)
                rectangle.setFillColor(sf::Color(124, 9, 20, 255));
            else
                rectangle.setFillColor(sf::Color(246, 237, 195, 255));
            rectangle.setPosition(i*SIZE, j*SIZE);
            window.draw(rectangle);
        }
    }
    texture.loadFromFile("./queen.png");
    sprite.setTexture(texture);
    sprite.setScale(SIZE/50,SIZE/50);
    sprite.setColor(sf::Color(185, 123, 107 ,255));
    for(auto &[col,row]: queens)
    {
        posCol=col*SIZE;
        posRow=row*SIZE;
        sprite.setPosition(posCol,posRow);
        window.draw(sprite);
        window.display();
    }
    usleep(50000);
}
