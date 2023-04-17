#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N_I 3		//入力層のユニット数（バイアス項があるもの）
//出力層のユニット数は1なので定義せず
#define N_LEARN 60000	//学習回数

int main() {

	int i, j, k, lrn;
	//入力データと出力データ
	double input[N_I], o;
	//入力層-->出力層への重み
	double w_io[N_I];
	//入力データと重みの荷重和
	double u;

	//ここを書き換えてOR回路やXOR回路の学習も試してみよう
	//教師データ（AND回路）
	//入力（1,1）-->出力（1）
	//入力（1,0）-->出力（0）
	//入力（0,1）-->出力（0）
	//入力（0,0）-->出力（0）
	double t[4][3] = {
		{ 1, 1, 1 },
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 0 }
	};
	//学習率
	double eta = 0.95;
	//シグモイド関数の係数
	double gain = 1.0;

	//疑似乱数の発生系列を変更
	srand((unsigned)time(NULL));
	//疑似乱数をもとに入力層-->出力層への重みを初期化
	for (i = 0; i < N_I; i++)
		w_io[i] = ((double)rand() / RAND_MAX) / 10;

	for (lrn = 1; lrn < N_LEARN; lrn++) {
		for (j = 0; j < 4; j++) {
			//入力層のセット
			input[0] = t[j][0];	//a
			input[1] = t[j][1];	//b
			//バイアス項（1.0）のセット
			input[N_I - 1] = 1.0;
			//入力データと重みの荷重和の初期化
			u = 0.0;
			for (k = 0; k < N_I; k++)
				//入力データと重みの荷重和の計算
				u = u + input[k] * w_io[k];	//c, d
			//活性化関数による出力
			//シグモイド関数の場合
			o = 1.0 / (1.0 + exp(-gain * u));
			//ステップ関数の場合
			//if (u <= 0)
			//	o = 0;
			//else
			//	o = 1;
			printf("学習回数：%6d 入力(%lf,%lf)-->出力(%lf)\n", lrn, input[0], input[1], o);
			//勾配降下法による重みの更新
			for (k = 0; k < N_I; k++)
				w_io[k] = w_io[k] + eta * (t[j][2] - o)*input[k];	//e
		}
	}
}
