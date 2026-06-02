#include "snake.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <chrono>
using namespace ftxui;

int main()
{
    SnakeGame game;
    game.GameInit();
    auto screen = ScreenInteractive::FitComponent();

    Element GameView()
    {
        std::vector<Element> line;
        for (int y = 0; y < game.mapHeight; y++)
        {
            std::vector<Element> col;
            for (int x = 0; x < game.mapWidth; x++)
            {
                std::string str = " ";
                Color color = Color::Black;

                //绘制围墙
                if (x == 0 || x == game.mapWidth - 1 || y == 0 || y == game.mapHeight - 1)
                {
                    color = Color::Gray;
                }
                //蛇头
                if (game.snakeBody[0].first == x && game.snakeBody[0].second == y)
                {
                    str = "■";
                    color = Color::Green;
                }
                //蛇身体
                for (int i = 1; i < game.snakeBody.size(); i++)
                {
                    if (game.snakeBody[i].first == x && game.snakeBody[i].second == y)
                    {
                        str = "■";
                        color = Color::DarkGreen;
                    }
                }
                //食物
                if (game.food.first == x && game.food.second == y)
                {
                    str = "●";
                    color = Color::Red;
                }
                col.push_back(text(str) | bgcolor(color));
            }
            line.push_back(hbox(col));
        }

        return hbox(
            vbox(line) | border,
            vbox({
                text("贪吃蛇小游戏") | bold,
                text("得分：" + std::to_string(game.score)),
                separator(),
                text("↑ ↓ 控制上下"),
                text("← → 控制左右"),
                separator(),
                text("ESC 退出游戏") | dim
            }) | border
        );
    }

    auto render = Renderer(GameView);

    //键盘监听
    render |= CatchEvent([&](Event e)
    {
        if (e.is(Key::Escape))
            screen.ExitLoopClosure()();

        if (e.is(Key::Up) && game.dirY != 1)
        {
            game.dirX = 0; game.dirY = -1;
        }
        if (e.is(Key::Down) && game.dirY != -1)
        {
            game.dirX = 0; game.dirY = 1;
        }
        if (e.is(Key::Left) && game.dirX != 1)
        {
            game.dirX = -1; game.dirY = 0;
        }
        if (e.is(Key::Right) && game.dirX != -1)
        {
            game.dirX = 1; game.dirY = 0;
        }
        return true;
    });

    //自动移动计时器
    auto timeControl = Renderer(render, [&]()
    {
        static auto lastTime = std::chrono::steady_clock::now();
        auto nowTime = std::chrono::steady_clock::now();
        int gap = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - lastTime).count();

        if (gap >= 150)
        {
            lastTime = nowTime;
            game.SnakeMove();
            //游戏结束自动重置
            if(game.IsGameOver())
            {
                game.GameInit();
            }
        }
        return render.Render();
    });

    screen.Loop(timeControl);
    return 0;
}