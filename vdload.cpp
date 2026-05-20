#include <opencv2/opencv.hpp>
#include <iostream>

// 外部（main.cpp）向けのプロトタイプ宣言（引数をint型に変更）
bool vdload_open(int camera_id = 0, double target_fps = 5.0, int target_width = 640);
bool vdload_next_frame(cv::Mat& frame);

// 内部状態を管理する変数（ここはそのまま）
static cv::VideoCapture g_cap;
static int g_width = 640;
static int g_height = 0;
static int g_skip_interval = 1;
static long g_frame_count = 0;

// 【変更】カメラを開く関数
bool vdload_open(int camera_id, double target_fps, int target_width) {
    if (!g_cap.open(camera_id))
    {
        std::cerr << "[Error] カメラが起動できません" << std::endl;
        return false;
    }

    // カメラの元のFPSを取得（一般的なWebカメラは30fpsなど）
    double orig_fps = g_cap.get(cv::CAP_PROP_FPS);
    if (orig_fps <= 0) orig_fps = 30.0; // カメラによってFPSが正常に取得できない場合の安全策

    // 間引き間隔の計算 (例: 30fps / 5fps = 6フレームに1回処理)
    g_skip_interval = static_cast<int>(orig_fps / target_fps);
    if (g_skip_interval < 1) g_skip_interval = 1;

    // カメラの初期解像度を取得してアスペクト比を計算
    int orig_w = static_cast<int>(g_cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int orig_h = static_cast<int>(g_cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    g_width = target_width;
    g_height = static_cast<int>(orig_h * (static_cast<double>(target_width) / orig_w));
    
    std::cout << "[VideoLoader] カメラ起動成功 (ID: " << camera_id << ")" << std::endl;
    return true;
}

// 次のフレームを取得する関数
bool vdload_next_frame(cv::Mat& frame) 
{
    cv::Mat raw;
    while (true)
    {
        if (!g_cap.read(raw)) return false; // カメラから映像が切れたら終了
        
        if (g_frame_count % g_skip_interval == 0)
        {
            cv::resize(raw, frame, cv::Size(g_width, g_height));
            g_frame_count++;
            return true;
        }
        g_frame_count++;
    }
}