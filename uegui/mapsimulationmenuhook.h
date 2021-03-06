#ifndef _UEGUI_MAPSIMULATIONMENUHOOK_H
#define _UEGUI_MAPSIMULATIONMENUHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uibutton.h"
#include "routewrapper.h"
#include "viewwrapper.h"

namespace UeGui
{
  class UEGUI_CLASS CMapSimulationMenuHook : public CAggHook
  {
  public:
    enum MapSimulationMenuHookCtrlType
    {
      MapSimulationMenuHook_Begin = 0,
      MapSimulationMenuHook_ExpandBtn,
      MapSimulationMenuHook_CloseBtn,
      MapSimulationMenuHook_SlowlyDownBtn,
      MapSimulationMenuHook_SlowlyDownLabel,
      MapSimulationMenuHook_Delimiter1,
      MapSimulationMenuHook_SpeedLevelBtn,
      MapSimulationMenuHook_SpeedLevelLabel,
      MapSimulationMenuHook_Delimiter2,
      MapSimulationMenuHook_SpeedUpBtn,
      MapSimulationMenuHook_SpeedUpLabel,
      MapSimulationMenuHook_Delimiter3,
      MapSimulationMenuHook_PauseBtn,
      MapSimulationMenuHook_PauseLabel,
      MapSimulationMenuHook_PauseBtnR,
      MapSimulationMenuHook_StopSimulationBtn,
      MapSimulationMenuHook_StopSimulationLabel,
      MapSimulationMenuHook_End
    };

    //速度信息结构
    struct SpeedInfo
    {
      char m_speedText[10];
      short m_speed;
    };
    typedef std::vector<SpeedInfo> SpeedInfoList;

    CMapSimulationMenuHook();

    virtual ~CMapSimulationMenuHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();
    /**
    * \设置当前hook是否显示
    */
    virtual void Show( bool show = true );
    /**
    * \brief 更新Hook
    */
    virtual void Update(short type);
    /*
    * 设置父类hook
    */
    void SetParentHook(CAggHook* parentHook);
    /*
    * 展开和收缩菜单
    */
    void ExpandMenu(bool bExpand = true);

    /*
    * 初始化模拟导航信息
    */
    void ReseSimulation();
  protected:
    /**
    * \brief 返回皮肤配置文件名称
    */
    virtual tstring GetBinaryFileName();
    /**
    * \brief 生成控件名称
    */
    virtual void MakeNames();
    /**
    * \brief 生成控件
    */
    void MakeControls();
  private:
    /**
    * \brief 根据当前菜单展开状态、导航状态、屏幕状态等动态更新界面
    */
    void DynamicUpdate(bool bExpand, short planState, UeMap::ViewOpeMode viewMode);
    /**
    * \brief 显示和隐藏菜单栏
    * param bShow 显示还是隐藏
    * param bExpand 展开还是收缩
    */
    void ShowMenuBar(bool bShow, bool bExpand);
    /**
    * \brief 减速
    */
    void SlowlyDown();
    /**
    * \brief 加速
    */
    void SpeedUp();
    /**
    * \brief 设置按钮状态
    */
    void ResetSpeedBtnStatus();
    /**
    * \brief 设置按钮文字状态
    */
    void ResetSpeedBtnCaption();
    /**
    * \brief 刷新速度值
    */
    void RefreshSpeedLabel();
  private:
    CAggHook* m_parentHook;
    //展开菜单按钮
    CUiBitButton m_expandBtn;
    //关闭菜单按钮
    CUiBitButton m_closeBtn;
    //减速
    CUiBitButton m_slowlyDownBtn;
    //当前速度
    CUiBitButton m_speedLevelBtn;
    //加速
    CUiBitButton m_speedUpBtn;
    //暂停
    CUiBitButton m_pauseBtn;
    //停止导航
    CUiBitButton m_stopSimulation;
    //分割符
    CUiButton m_delimiter1;
    CUiButton m_delimiter2;
    CUiButton m_delimiter3;
  private:
    //地图访问接口
    CViewWrapper& m_viewWrapper;
    //路径规划访问接口
    CRouteWrapper& m_routeWrapper;
    //模拟导航状态:正在模式时为True,否则为False
    bool m_simulationStatus;
    //模拟导航速度索引值
    char m_speedIndex;
    SpeedInfoList m_speedList;
    //菜单状态
    bool m_expandStatus;
  };
}
#endif
