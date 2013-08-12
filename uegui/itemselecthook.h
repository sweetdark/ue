/*
* ͨ������ѡ��Ի���
*/
#ifndef _UEGUI_ITEMSELECTHOOK_H
#define _UEGUI_ITEMSELECTHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uibutton.h"

namespace UeGui
{
  typedef void (*ItemSelectEvent)(CAggHook* sender, short selectIndex);

  class UEGUI_CLASS CItemSelectHook : public CAggHook
  {
  public:
    enum ItemSelectHookCtrlType
    {
      ItemSelectHook_Begin = 0,
      ItemSelectHook_BackGround,
      ItemSelectHook_PopupListTop,
      ItemSelectHook_PopupListBottom,
      ItemSelectHook_Item1,
      ItemSelectHook_Item1_Icon,
      ItemSelectHook_Item2,
      ItemSelectHook_Item2_Icon,
      ItemSelectHook_Item3,
      ItemSelectHook_Item3_Icon,
      ItemSelectHook_Item4,
      ItemSelectHook_Item4_Icon,
      ItemSelectHook_Line1,
      ItemSelectHook_Line2,
      ItemSelectHook_Line3,
      ItemSelectHook_End
    };

    enum ItemType
    {
      ITEM1,
      ITEM2,
      ITEM3,
      ITEM4,
      ITEM_END
    };

    struct ItemInfo
    {
      char m_itemName[128]; //��Ŀ����
      bool m_enable;        //��Ŀ�Ƿ���Ч
      bool m_showIcon;      //�Ƿ���ʾѡ��ͼ��
    };
    typedef std::vector<ItemInfo> ItemInfoList;

    CItemSelectHook();

    virtual ~CItemSelectHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();

    /*
    * ����ѡ���¼�
    */
    void SetSelectEvent(CAggHook* senderHook, ItemSelectEvent selectEvent, const ItemInfoList& itemInfoList);
  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();
  private:
    /*
    * ��Ŀѡ��
    */
    void DoSelect(ItemType type);
    /*
    * �رմ���
    */
    void DoClose();
  private:
    CUiButton m_backGround;
    CUiButton m_item1;
    CUiButton m_item1_Icon;
    CUiButton m_item2;
    CUiButton m_item2_Icon;
    CUiButton m_item3;
    CUiButton m_item3_Icon;
    CUiButton m_item4;
    CUiButton m_item4_Icon;
  private:
    CAggHook* m_senderHook;
    ItemSelectEvent m_itemSelectEvent;
  };
}
#endif