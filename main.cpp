#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define N_LEARN 30000 //学習の回数
#define N_I 3 //入力層の数（論理回路の入力（バイアスも含む））
#define N_H 4 //中間層の数（適当（バイアスも含む））
#define N_O 1 //出力層の数（出力数１個）
#define ETA 0.001 //学習時の重み修正定数（η）

double sigmoid(double x)//シグモイド関数
{
double f;
double gain = 1.0;
f = 1.0 / (1.0 + exp(-gain * x));
return f;/*戻す値が関数の値になる*/

}

//入力、出力の教師データ（txが入力、tyが出力）
//XOR回路の例
int tx[4][N_I] = {
{ 1,1,1 },
{ 1,0,1 },
{ 0,1,1 },
{ 0,0,1 }
};
int ty[4][N_O] = {
{ 0 },
{ 1 },
{ 1 },
{ 0 }
};
//入力、中間、出力層素子
double x[N_I], h[N_H], y[N_O];
//入力ー中間、中間ー出力の重み
double w1[N_I][N_H], w2[N_H][N_O];
//中間、出力の誤差逆伝播量
double h_back[N_H], y_back[N_O];

int main(void) {

int isample, i, j, k, lrn;
double u, v, y_back_jk, eta;

srand((unsigned)time(NULL));
eta = (double)ETA;

//重みにランダムな初期値を与える
for (i = 0;i < N_I; i++)
for (j = 0;j < N_H-1; j++)
w1[i][j] = ((double)rand() / RAND_MAX) / 10;

for (j = 0;j < N_H; j++)
for (k = 0;k < N_O; k++)
w2[j][k] = ((double)rand() / RAND_MAX) / 10;

//学習のループ
for (lrn = 0; lrn < N_LEARN; lrn++){
//訓練データに関するループ
for (isample = 0; isample < 4; isample++){
//順方向の動作
//訓練データに従って、ネットワークへの入力設定
for (i = 0;i < N_I; i++)
x[i] = ; //???

//閾値設定x[N_I-1] = 1.0
x[N_I-1] = (double)1.0;
//隠れ素子の計算
for (j = 0; j < N_H-1;j++){
u = 0;
for (i = 0; i < N_I; i++)
u = u + ; //???
//シグモイドの適用
h[j] = sigmoid(u);
}

//閾値設定h[N_H-1] = 1.0
h[N_H-1] = (double)1.0;
//出力素子の計算
for (k = 0; k < N_O; k++){
v = 0;
for (j = 0;j < N_H; j++)
v = v + ; //???
//シグモイドの適用
y[k] = sigmoid(v);
printf("学習回数：%6d 入力(%d,%d)-->出力(%lf)\n", lrn, tx[isample][0], tx[isample][1], y[k]);
}

//誤差の逆伝播
//出力層素子の逆伝播
for (k = 0; k < N_O; k++)
y_back[k] = (y[k] - ty[isample][k])*((double)1.0 - y[k]) * y[k];
//隠れ層-->出力層への重みの修正
for (j = 0; j < N_H; j++)
for (k = 0; k < N_O; k++)
w2[j][k] = w2[j][k] - eta * h[j] * ; //???

//隠れ層素子の逆伝播
for (j = 0; j < N_H-1; j++){
y_back_jk = 0;
for (k = 0; k < N_O; k++)
y_back_jk = y_back_jk + w2[j][k] * ; //???
h_back[j] = y_back_jk * ((double)1.0 - h[j]) * h[j];
}
//入力層-->隠れ層への重みの修正
for (i = 0; i < N_I; i++)
for (j = 0; j < N_H-1; j++)
w1[i][j] = w1[i][j] - eta * x[i] * ; //???
}//訓練データのループ終わり
}//学習のループ終わり
}