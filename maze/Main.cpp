
# include <Siv3D.hpp>

#include <vector>

void Main()
{
	// 迷路の幅、高さ
	const int w = 41, h = 31;

	// 迷路 (true: 壁, false: 道)
	std::vector<std::vector<bool>> maze(w, std::vector<bool>(h, false));

	// 表示確認用にいくつか壁にする
	maze[0][0] = true;
	maze[w - 1][h - 1] = true;

	// 迷路の1マスを描画する大きさ
	const int cw = 15, ch = 15;

	// 壁と道の色
	const Color colWall = { 0, 0, 0 }, colFloor = { 192, 192, 192 };

	while (System::Update())
	{
		// 迷路を描画
		for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x) {
			Rect(x * cw, y * ch, cw, ch).draw(maze[x][y] ? colWall : colFloor);
		}
	}
}
