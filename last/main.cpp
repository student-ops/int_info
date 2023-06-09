#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define N_LEARN 2000 // 学習の回数
#define N_I 36       // 入力層の数（バイアスも含む）
#define N_H 20       // 中間層の数（適当（バイアスも含む））
#define N_O 5        // 出力層の数（出力数３個）
#define ETA 0.2      // 学習時の重み修正定数（η）

double sigmoid(double x) // シグモイド関数
{
  double f;
  double gain = 1.0;
  f = 1.0 / (1.0 + exp(-gain * x));
  return f; /*戻す値が関数の値になる*/
}

// 入力、出力の教師データ
// 教師データ（txが入力、tyが出力）
// 文字（アルファベット）の認識
int tx[26][N_I] = {
    {0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1}, // A
    {1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1}, // B
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1}, // C
    {1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1}, // D
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1}, // E
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, // F
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1}, // G
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1}, // H
    {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1}, // I
    {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1}, // J
    {1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1}, // K
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1}, // L
    {1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1}, // M
    {1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1}, // N
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1}, // O
    {1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, // P
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1}, // Q
    {1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1}, // R
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1}, // S
    {1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1}, // T
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1}, // U
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1}, // V
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, // W
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1}, // X
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1}, // Y
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1}  // Z
};
int ty[26][N_O] = {
    {0, 0, 0, 0, 1}, // A
    {1, 0, 1, 0, 1}, // B
    {0, 0, 1, 0, 1}, // C
    {1, 0, 0, 1, 1}, // D
    {1, 1, 0, 1, 0}, // E
    {1, 1, 0, 0, 1}, // F
    {0, 0, 1, 1, 0}, // G
    {0, 1, 1, 1, 1}, // H
    {0, 0, 0, 1, 0}, // I
    {0, 0, 0, 1, 1}, // J
    {1, 0, 0, 0, 0}, // K
    {0, 1, 0, 0, 1}, // L
    {1, 0, 0, 1, 0}, // M
    {1, 0, 0, 0, 1}, // N
    {0, 0, 1, 1, 1}, // O
    {1, 0, 1, 0, 0}, // P
    {0, 1, 0, 0, 0}, // Q
    {1, 0, 1, 1, 0}, // R
    {0, 0, 1, 0, 0}, // S
    {1, 1, 0, 0, 0}, // T
    {0, 1, 1, 0, 1}, // U
    {0, 1, 1, 0, 0}, // V
    {0, 1, 1, 1, 0}, // W
    {0, 1, 0, 1, 1}, // X
    {0, 1, 0, 1, 0}, // Y
    {1, 0, 1, 1, 1}  // Z
};
// 入力、中間、出力層素子
double x[N_I], h[N_H], y[N_O];
// 入力ー中間、中間ー出力の重み
double w1[N_I][N_H], w2[N_H][N_O];
// 中間、出力の誤差逆伝播量
double h_back[N_H], y_back[N_O];

int main(void)
{

  int isample, i, j, k, lrn;
  double u, v, y_back_jk, eta;

  srand((unsigned)time(NULL));
  eta = (double)ETA;

  // 重みにランダムな初期値を与える
  for (i = 0; i < N_I; i++)
    for (j = 0; j < N_H - 1; j++)
      w1[i][j] = ((double)rand() / RAND_MAX) / 10;

  for (j = 0; j < N_H; j++)
    for (k = 0; k < N_O; k++)
      w2[j][k] = ((double)rand() / RAND_MAX) / 10;

  // 学習プロセス
  for (lrn = 0; lrn < N_LEARN; lrn++)
  {
    // eta = eta * 0.9;
    // 訓練データに関するループ
    for (isample = 0; isample < 26; isample++)
    {
      // 順方向の動作
      // 訓練データに従って、ネットワークへの入力設定
      for (i = 0; i < N_I; i++)
        x[i] = tx[isample][i];

      // 閾値設定x[N_I-1] = 1.0
      x[N_I - 1] = (double)1.0;
      // 隠れ素子の計算
      for (j = 0; j < N_H - 1; j++)
      {
        u = 0;
        for (i = 0; i < N_I; i++)
          u = u + w1[i][j] * x[i];
        // シグモイドの適用
        h[j] = sigmoid(u);
      }

      // 閾値設定h[N_H-1] = 1.0
      h[N_H - 1] = (double)1.0;
      // 出力素子の計算
      printf("学習回数：%6d 入力(%c)-->出力(", lrn, 'A' + isample);
      for (k = 0; k < N_O; k++)
      {
        v = 0;
        for (j = 0; j < N_H; j++)
          v = v + w2[j][k] * h[j];
        // シグモイドの適用
        y[k] = sigmoid(v);
        printf("(%lf)", y[k]);
      }
      printf(")\n");

      // 誤差の逆伝播
      // 出力層素子の逆伝播
      for (k = 0; k < N_O; k++)
        y_back[k] = (y[k] - ty[isample][k]) * ((double)1.0 - y[k]) * y[k];
      // 隠れ層-->出力層への重みの修正
      for (j = 0; j < N_H; j++)
        for (k = 0; k < N_O; k++)
          w2[j][k] = w2[j][k] - eta * h[j] * y_back[k];

      // 隠れ層素子の逆伝播
      for (j = 0; j < N_H - 1; j++)
      {
        y_back_jk = 0;
        for (k = 0; k < N_O; k++)
          y_back_jk = y_back_jk + w2[j][k] * y_back[k];
        h_back[j] = y_back_jk * ((double)1.0 - h[j]) * h[j];
      }
      // 入力層-->隠れ層への重みの修正
      for (i = 0; i < N_I; i++)
        for (j = 0; j < N_H - 1; j++)
          w1[i][j] = w1[i][j] - eta * x[i] * h_back[j];
    } // 訓練データのループ終わり
  }   // 学習のループ終わり

  // 判定プロセスの追加
  int txx[N_I] = {0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1}; // A

  // int txx[N_I] = {1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1};

  // 未学習の文字パターンの入力
  printf("入力文字はこれですね\n");
  for (i = 0; i < N_I - 1; i++)
  {
    x[i] = txx[i];
    if (x[i] == 0)
      printf("　");
    else
      printf("＊");
    if (i % 5 == 4)
      printf("\n");
  }

  // ここから判定プロセスのプログラムを追加して完成させよう！
  for (j = 0; j < N_H - 1; j++)
  {
    u = 0;
    for (i = 0; i < N_I; i++)
      u = u + w1[i][j] * x[i];
    // シグモイドの適用
    h[j] = sigmoid(u);
  }
  for (k = 0; k < N_O; k++)
  {
    v = 0;
    for (j = 0; j < N_H; j++)
      v = v + w2[j][k] * h[j];
    // シグモイドの適用
    y[k] = sigmoid(v);
    printf("(%lf)", y[k]);
  }
  // int tans = 0;
  // for (k = 0; k < 5; k++)
  // {
  //   if (y[k] > 0.5)
  //   {
  //     y[k] = 1;
  //     tans += 1 * pow(2, k);
  //   }
  //   else
  //     y[k] = 0;
  //   printf("%lf", y[k]);
  // }
  // printf("ANS:%d", tans);

  // printf("予想はこれです。\n");
  // for (i = 0; i < N_I - 1; i++)
  // {
  //   x[i] = tx[tans][i];
  //   if (x[i] == 0)
  //     printf("　");
  //   else
  //     printf("＊");
  //   if (i % 5 == 4)
  //     printf("\n");
  // }

  return 0;
}