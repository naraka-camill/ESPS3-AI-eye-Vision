#ifndef ESP32_CAMERA_H
#define ESP32_CAMERA_H

#include <esp_camera.h>
#include <esp_lcd_panel_ops.h>
#include <lvgl.h>
#include <thread>
#include <memory>
#include <atomic>

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#include "camera.h"

struct JpegChunk {
    uint8_t* data;
    size_t len;
};

class Esp32Camera : public Camera {
private:
    camera_fb_t* fb_ = nullptr;
    lv_img_dsc_t preview_image_;
    std::string explain_url_;
    std::string explain_token_;
    std::thread encoder_thread_;
    std::thread preview_thread_;
    std::atomic<bool> preview_running_{false};
    esp_lcd_panel_handle_t eye_panel1_ = nullptr;
    esp_lcd_panel_handle_t eye_panel2_ = nullptr;
    TaskHandle_t eye_task_handle_ = nullptr;

public:
    Esp32Camera(const camera_config_t& config);
    ~Esp32Camera();

    virtual void SetExplainUrl(const std::string& url, const std::string& token);
    virtual bool Capture();
    // 翻转控制函数
    virtual bool SetHMirror(bool enabled) override;
    virtual bool SetVFlip(bool enabled) override;
    virtual std::string Explain(const std::string& question);

    // 设置魔眼面板句柄，Capture() 时会自动将摄像头画面推送到这些面板
    void SetEyePanels(esp_lcd_panel_handle_t panel1, esp_lcd_panel_handle_t panel2, TaskHandle_t eye_task = nullptr) {
        eye_panel1_ = panel1;
        eye_panel2_ = panel2;
        eye_task_handle_ = eye_task;
    }
    camera_fb_t* GetFrameBuffer() const { return fb_; }

    // 实时预览控制
    void OnceCapPreview();
    void StartPreview();
    void StopPreview();

    // 等比缩放图像并推送到LCD面板
    // src: 源图像数据指针
    // src_w: 源图像宽度
    // src_h: 源图像高度
    // dst_panel1: 目标LCD面板1句柄
    // dst_panel2: 目标LCD面板2句柄
    // dst_w: 目标显示区域宽度
    // dst_h: 目标显示区域高度
    void ScaleAndDraw(const uint16_t* src, int src_w, int src_h,
                      esp_lcd_panel_handle_t dst_panel1, esp_lcd_panel_handle_t dst_panel2,
                      int dst_w = 240, int dst_h = 240);

    void ResumeEyeTask() {
        if (eye_task_handle_ != nullptr) {
            vTaskResume(eye_task_handle_);
        }
    }
};

#endif // ESP32_CAMERA_H