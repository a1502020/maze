
# include <Siv3D.hpp>

#include <vector>

void Main()
{
	// 迷路の幅、高さ
	const int w = 41, h = 31;

	// 迷路 (true: 壁, false: 道)
	std::vector<std::vector<bool>> maze(w, std::vector<bool>(h, false));

	// ------------------------------
	// 棒倒し法で迷路を生成する
	// ------------------------------

	// 周囲を壁にする
	for (int x = 0; x < w; ++x) {
		maze[x][0] = true;
		maze[x][h - 1] = true;
	}
	for (int y = 0; y < h; ++y) {
		maze[0][y] = true;
		maze[w - 1][y] = true;
	}

	// 棒倒し
	for (int y = 2; y <= h - 3; y += 2) for (int x = 2; x <= w - 3; x += 2) {

		// 上下左右のうち、候補になるマスのリストを作る
		std::vector<Point> points;
		if (!maze[x + 1][y]) points.push_back({ x + 1, y });
		if (!maze[x - 1][y]) points.push_back({ x - 1, y });
		if (!maze[x][y + 1]) points.push_back({ x, y + 1 });
		if (y == 2) points.push_back({ x, y - 1 });

		// 候補から1つランダムに選ぶ
		Point p = points[Random(0, static_cast<int>(points.size() - 1))];

		// マス (x, y) と選んだマスを壁にする
		maze[x][y] = true;
		maze[p.x][p.y] = true;

	}

	// ------------------------------
	// 棒倒し法ここまで
	// ------------------------------

	// 迷路の1マスを描画する大きさ
	const int cw = 15, ch = 15;

	// 壁と道の色
	const Color colWall = { 0, 0, 0 }, colFloor = { 192, 192, 192 };

	// プレイヤーの位置
	Point me = { 1, 1 };

	// プレイヤーの色
	const Color colMe = { 255, 0, 0 };

	// プレイヤーの見た目の半径
	const int meRadius = std::min(cw, ch) / 2 - 1;

	// キー設定
	const auto keyR = Input::KeyRight | Input::KeyD;
	const auto keyU = Input::KeyUp | Input::KeyW;
	const auto keyL = Input::KeyLeft | Input::KeyA;
	const auto keyD = Input::KeyDown | Input::KeyS;

	while (System::Update())
	{
		// プレイヤーの操作
		if (keyR.clicked && !maze[me.x + 1][me.y]) ++me.x;
		if (keyU.clicked && !maze[me.x][me.y - 1]) --me.y;
		if (keyL.clicked && !maze[me.x - 1][me.y]) --me.x;
		if (keyD.clicked && !maze[me.x][me.y + 1]) ++me.y;

		// 迷路を描画
		for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x) {
			Rect(x * cw, y * ch, cw, ch).draw(maze[x][y] ? colWall : colFloor);
		}

		// プレイヤーを描画
		Circle({ me.x * cw + cw / 2, me.y * ch + ch / 2 }, meRadius).draw(colMe);
	}
}
