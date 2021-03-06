#ifndef _UEGUI_POIQUERYLISTHOOK_H
#define _UEGUI_POIQUERYLISTHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#include "uequery/uerecord.h"

#include "menubackgroundhook.h"

//#include "uilabel.h"
#include "uibutton.h"
//#include "uiradiobutton.h"
//#include "uicheckbutton.h"

namespace UeGui
{
  class UEGUI_CLASS CPoiQueryListHook : public CMenuBackgroundHook
  {
  public:
    enum PoiQueryListHookCtrlType
    {
      PoiQueryListHook_Begin = MenuBackgroundHook_End,
      PoiQueryListHook_DistSwitchBtn,
      PoiQueryListHook_DistSelectBtn,
      PoiQueryListHook_DistSelectBtnIcon,
      PoiQueryListHook_InformationBtn,
      PoiQueryListHook_RouteBtn,
      PoiQueryListHook_Bar,

      PoiQueryListHook_List1Btn,
      PoiQueryListHook_List1PoiNameBox,
      PoiQueryListHook_List1CursorBox,
      PoiQueryListHook_List1PoiDistBox,
      PoiQueryListHook_List1PoiTelBox,
      PoiQueryListHook_List1PoiFarBox,
      PoiQueryListHook_List1PoiCursorBox,

      PoiQueryListHook_List2Btn,
      PoiQueryListHook_List2PoiNameBox,
      PoiQueryListHook_List2CursorBox,
      PoiQueryListHook_List2PoiDistBox,
      PoiQueryListHook_List2PoiTelBox,
      PoiQueryListHook_List2PoiFarBox,
      PoiQueryListHook_List2PoiCursorBox,

      PoiQueryListHook_List3Btn,
      PoiQueryListHook_List3PoiNameBox,
      PoiQueryListHook_List3CursorBox,
      PoiQueryListHook_List3PoiDistBox,
      PoiQueryListHook_List3PoiTelBox,
      PoiQueryListHook_List3PoiFarBox,
      PoiQueryListHook_List3PoiCursorBox,

      PoiQueryListHook_List4Btn,
      PoiQueryListHook_List4PoiNameBox,
      PoiQueryListHook_List4CursorBox,
      PoiQueryListHook_List4PoiDistBox,
      PoiQueryListHook_List4PoiTelBox,
      PoiQueryListHook_List4PoiFarBox,
      PoiQueryListHook_List4PoiCursorBox,

      PoiQueryListHook_PageUpBtn,
      PoiQueryListHook_PageUpBtnIcon,
      PoiQueryListHook_PageDownBtn,
      PoiQueryListHook_PageDownBtnIcon,
      PoiQueryListHook_PageBack,
      PoiQueryListHook_CurPageInfo,
      PoiQueryListHook_AllPageInfo,
      PoiQueryListHook_PageInfoInterval,
      PoiQueryListHook_BtnIntervalLine1,
      PoiQueryListHook_BtnIntervalLine2,

      PoiQueryListHook_Cursor1,
      PoiQueryListHook_Cursor2,
      PoiQueryListHook_Cursor3,
      PoiQueryListHook_Cursor4,
      PoiQueryListHook_Cursor5,
      PoiQueryListHook_Cursor6,
      PoiQueryListHook_Cursor7,
      PoiQueryListHook_Cursor8,

      PoiQueryListHook_End
    };

    CPoiQueryListHook();

    virtual ~CPoiQueryListHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual void Load();

  protected:

    virtual void MakeNames();

    void MakeControls();

    void SearchForResult();

    void ResetResultList();

    void SetDirection(const SQLRecord &oneRecord, int index);

    void GetDistances();

  private:
    static void DistSwitchCallBack(void *pDoCallBackObj, const SQLRecord *pResult);

    void DoDistSwitchCallBack(const SQLRecord *pResult);

  private:
    CUiButton m_distSwitchBtn;
    CUiBitButton m_distSelectBtn;

    CUiButton m_poiBtn;
    CUiButton m_routeBtn;
    CUiBitButton m_infoBtn[4];
    CUiLabel m_poiLabel[4];
    CUiLabel m_addrLabel[4];
    CUiLabel m_farLabel[4];
    CUiLabel m_telLabel[4];
    CUiButton m_cursorIcon[4];

    CUiBitButton m_returnBtn;
    
    CUiBitButton m_pageUpBtn;
    CUiBitButton m_pageDownBtn;

    CUiLabel m_curPageInfo;
    CUiLabel m_totalPageInfo;

    CUeRecord m_records;

    PointList m_pointList;
  };
}
#endif
