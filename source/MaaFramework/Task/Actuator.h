#pragma once

#include <string_view>
#include <stack>

#include <meojson/json.hpp>

#include "API/MaaTypes.h"
#include "Conf/Conf.h"
#include "Instance/InstanceInternalAPI.hpp"
#include "Recognizer.h"
#include "Resource/PipelineResMgr.h"
#include "Resource/PipelineTypes.h"


MAA_TASK_NS_BEGIN

class Actuator : public MaaInstanceSink
{
public:
    using TaskData = MAA_RES_NS::TaskData;

public:
    Actuator(InstanceInternalAPI* inst);

    bool run(const Recognizer::Result& rec_result, const TaskData& task_data);

public: // from MaaInstanceSink
    virtual void on_stop() override { need_exit_ = true; }

private:
    void click(const MAA_RES_NS::Action::ClickParam& param, const cv::Rect& cur_box);
    void swipe(const MAA_RES_NS::Action::SwipeParam& param, const cv::Rect& cur_box);
    void press_key(const MAA_RES_NS::Action::KeyParam& param);

    void start_app(const MAA_RES_NS::Action::AppParam& param);
    void stop_app(const MAA_RES_NS::Action::AppParam& param);
    void custom_action(const std::string& task_name, const MAA_RES_NS::Action::CustomParam& param,
                       const cv::Rect& cur_box, const json::value& cur_rec_detail);

    void wait_freezes(const MAA_RES_NS::WaitFreezesParam& param, const cv::Rect& cur_box);

    cv::Rect get_target_rect(const MAA_RES_NS::Action::Target target, const cv::Rect& cur_box);

private:
    MAA_CTRL_NS::ControllerMgr* controller() { return inst_ ? inst_->inter_controller() : nullptr; }
    InstanceStatus* status() { return inst_ ? inst_->inter_status() : nullptr; }
    bool need_exit() const { return need_exit_; }
    void sleep(unsigned ms) const;
    void sleep(std::chrono::milliseconds ms) const;

private:
    bool need_exit_ = false;
    InstanceInternalAPI* inst_ = nullptr;
};

MAA_TASK_NS_END
