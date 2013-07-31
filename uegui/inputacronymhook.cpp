#include "inputacronymhook.h"

#ifndef _UEGUI_QUERYWRAPPER_H
#include "querywrapper.h"
#endif

#ifndef _UEMAP_AGGCANVAS_H
#include "uemap\viewcanvas.h"
#endif

#include "inputswitchhook.h"

#include "districtselectionhook.h"

using namespace UeGui;

CInputAcronymHook::CInputAcronymHook()
{
  m_strTitle = "����";
  m_vecHookFile.push_back(_T("inputacronymhook.bin"));
}

CInputAcronymHook::~CInputAcronymHook()
{
  m_elements.clear();
  m_ctrlNames.clear();
  m_imageNames.clear();
}

void CInputAcronymHook::Init()
{
  CQueryWrapper::Get().SetQueryMode(UeQuery::IndexType::IT_PoiAcro);
  InitKeyBoard();
  m_iCurCursorIndex = 0;
  m_vecWordPosX.clear();
  m_vecWordPosX.push_back(m_keyWordBox.GetLabelElement()->m_startX-2);
}

void CInputAcronymHook::Load()
{
  CQueryWrapper::Get().SetDefaultQueryKind();
  SetQueryMode();
}

void CInputAcronymHook::MakeNames()
{
  CMenuBackgroundHook::MakeNames();
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_CharBack,	"CharBack"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode1,	"InputCode1"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode2,	"InputCode2"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode3,	"InputCode3"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode4,	"InputCode4"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode5,	"InputCode5"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode6,	"InputCode6"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode7,	"InputCode7"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode8,	"InputCode8"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode9,	"InputCode9"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode10,	"InputCode10"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode11,	"InputCode11"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode12,	"InputCode12"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode13,	"InputCode13"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode14,	"InputCode14"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode15,	"InputCode15"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode16,	"InputCode16"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode17,	"InputCode17"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode18,	"InputCode18"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode19,	"InputCode19"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode20,	"InputCode20"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode21,	"InputCode21"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode22,	"InputCode22"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode23,	"InputCode23"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode24,	"InputCode24"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode25,	"InputCode25"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputCode26,	"InputCode26"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputSwitchBtn,	"InputSwitchBtn"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_InputSwitchBtnIcon,	"InputSwitchBtnIcon"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_DistSwitchBtn,	"DistSwitchBtn"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_DistSelectBtn,	"DistSelectBtn"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_DistSelectBtnIcon,	"DistSelectBtnIcon"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_EditBox,	"EditBox"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_EditSelectBtn,	"EditSelectBtn"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_EditSelectBtnIcon,	"EditSelectBtnIcon"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_WordSeparation,	"WordSeparation"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_KeyWordBox,	"KeyWordBox"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_OtherSearchBtn,	"OtherSearchBtn"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_OtherSearchIcon,	"OtherSearchIcon"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_DeleteBtn,	"DeleteBtn"));
  m_ctrlNames.insert(GuiName::value_type(InputAcronymHook_SearchBtn,	"SearchBtn"));
}

void CInputAcronymHook::MakeControls()
{
  CMenuBackgroundHook::MakeControls();
  m_distSwitchBtn.SetCenterElement(GetGuiElement(InputAcronymHook_DistSwitchBtn));
  m_distSelectBtn.SetCenterElement(GetGuiElement(InputAcronymHook_DistSelectBtn));
  m_distSelectBtn.SetIconElement(GetGuiElement(InputAcronymHook_DistSelectBtnIcon));

  m_editSelectBtn.SetCenterElement(GetGuiElement(InputAcronymHook_EditSelectBtn));
  m_editSelectBtn.SetIconElement(GetGuiElement(InputAcronymHook_EditSelectBtnIcon));

  m_keyWordBox.SetLabelElement(GetGuiElement(InputAcronymHook_KeyWordBox));

  m_otherSearchBtn.SetCenterElement(GetGuiElement(InputAcronymHook_OtherSearchBtn));
  m_otherSearchBtn.SetIconElement(GetGuiElement(InputAcronymHook_OtherSearchIcon));

  m_searchBtn.SetCenterElement(GetGuiElement(InputAcronymHook_SearchBtn));
  m_searchBtn.SetEnable(false);
  m_deleteBtn.SetCenterElement(GetGuiElement(InputAcronymHook_DeleteBtn));
  m_deleteBtn.SetEnable(false);

  m_inputSwitchBtn.SetCenterElement(GetGuiElement(InputAcronymHook_InputSwitchBtn));
  m_inputSwitchBtn.SetIconElement(GetGuiElement(InputAcronymHook_InputSwitchBtnIcon));

  for(int i=0, j=InputAcronymHook_InputCode1; j<=InputAcronymHook_InputCode26; i++, j++)
    m_inputCode[i].SetCenterElement(GetGuiElement(j));

  m_pWordCursor = GetGuiElement(InputAcronymHook_WordSeparation);

  m_distSwitchBtn.SetCaption(CQueryWrapper::Get().GetQueryAdmName());
}

short CInputAcronymHook::MouseDown(CGeoPoint<short> &scrPoint)
{
  short ctrlType = CAggHook::MouseDown(scrPoint);
  switch(ctrlType)
  {
  case InputAcronymHook_DistSwitchBtn:
    {
      m_distSwitchBtn.MouseDown();
      AddRenderUiControls(&m_distSwitchBtn);
    }
    break;
  case InputAcronymHook_DistSelectBtn:
  case InputAcronymHook_DistSelectBtnIcon:
    {
      m_distSelectBtn.MouseDown();
      AddRenderUiControls(&m_distSelectBtn);
    }
    break;
  case InputAcronymHook_EditSelectBtn:
  case InputAcronymHook_EditSelectBtnIcon:
    {
      m_editSelectBtn.MouseDown();
      AddRenderUiControls(&m_editSelectBtn);
    }
    break;
  case InputAcronymHook_OtherSearchBtn:
  case InputAcronymHook_OtherSearchIcon:
    {
      m_otherSearchBtn.MouseDown();
      AddRenderUiControls(&m_otherSearchBtn);
    }
    break;
  case InputAcronymHook_SearchBtn:
    {
      m_searchBtn.MouseDown();
      AddRenderUiControls(&m_searchBtn);
    }
    break;
  case InputAcronymHook_DeleteBtn:
    {
      m_deleteBtn.MouseDown();
      AddRenderUiControls(&m_deleteBtn);
    }
    break;
  case InputAcronymHook_InputSwitchBtn:
  case InputAcronymHook_InputSwitchBtnIcon:
    {
      m_inputSwitchBtn.MouseDown();
      AddRenderUiControls(&m_inputSwitchBtn);
    }
    break;
  case InputAcronymHook_KeyWordBox:
  case InputAcronymHook_WordSeparation:
    {
      m_keyWordBox.MouseDown();
      AddRenderUiControls(&m_keyWordBox);
    }
    break;
  default:
    if (ctrlType>=InputAcronymHook_InputCode1 && ctrlType<=InputAcronymHook_InputCode26)
    {
      m_inputCode[ctrlType-InputAcronymHook_InputCode1].MouseDown();
      AddRenderUiControls(&m_inputCode[ctrlType-InputAcronymHook_InputCode1]);
      break;
    } 
    else
    {
      return CMenuBackgroundHook::MouseDown(scrPoint);
      break;
    }
  }

  if (m_isNeedRefesh)
  {
    Refresh();
  }
  m_isNeedRefesh = true;
  return ctrlType;
}

short CInputAcronymHook::MouseMove(CGeoPoint<short> &scrPoint)
{
  return -1;
}

short CInputAcronymHook::MouseUp(CGeoPoint<short> &scrPoint)
{
  short ctrlType = CAggHook::MouseUp(scrPoint);
  switch(m_downElementType)
  {
  case InputAcronymHook_DistSwitchBtn:
    {
      m_distSwitchBtn.MouseUp();
      CDistrictSelectionHook* hook = (CDistrictSelectionHook*)m_view->GetHook(DHT_DistrictSelectionHook);
      if (hook)
      {
        hook->SetCallBackFun(this, DistSwitchCallBack);
      }
      TurnTo(DHT_DistrictSelectionHook);
    }
    break;
  case InputAcronymHook_DistSelectBtn:
  case InputAcronymHook_DistSelectBtnIcon:
    {
      m_distSelectBtn.MouseUp();
    }
    break;
  case InputAcronymHook_EditSelectBtn:
  case InputAcronymHook_EditSelectBtnIcon:
    {
      m_editSelectBtn.MouseUp();
    }
    break;
  case InputAcronymHook_OtherSearchBtn:
  case InputAcronymHook_OtherSearchIcon:
    {
      m_otherSearchBtn.MouseUp();
      CAggHook::TurnTo(DHT_QueryMenuHook);
    }
    break;
  case InputAcronymHook_SearchBtn:
    {
      m_searchBtn.MouseUp();
      if (m_searchBtn.IsEnable())
      {
        if (CQueryWrapper::Get().GetSQLSentence().m_indexType == UeQuery::IT_PoiAcro)
        {
          CAggHook::TurnTo(DHT_PoiQueryListHook);
        }
        else
        {
          CAggHook::TurnTo(DHT_DistQueryListHook);
        }
      }
    }
    break;
  case InputAcronymHook_DeleteBtn:
    {
      m_deleteBtn.MouseUp();
      if(m_deleteBtn.IsEnable())
      {
        EraseOneKeyWord();
      }
    }
    break;
  case InputAcronymHook_InputSwitchBtn:
  case InputAcronymHook_InputSwitchBtnIcon:
    {
      m_inputSwitchBtn.MouseUp();
      if (m_inputSwitchBtn.IsEnable())
      {
        CAggHook::TurnTo(DHT_InputSwitchHook);
      }
    }
    break;
  case InputAcronymHook_KeyWordBox:
  case InputAcronymHook_WordSeparation:
    {
      m_keyWordBox.MouseUp();
      int curIndex = 0;
      for (; curIndex!=(m_vecWordPosX.size()-1); ++curIndex)
      {
        if (scrPoint.m_x<=(m_vecWordPosX[curIndex]+m_vecWordPosX[curIndex+1])/2)
        {
          break;
        }
      }
      if (curIndex!=m_iCurCursorIndex)
      {
        SetCursorPosX(curIndex);
      }
    }
    break;
  default:
    if (ctrlType>=InputAcronymHook_InputCode1 && ctrlType<=InputAcronymHook_InputCode26)
    {
      short tempcode = ctrlType-InputAcronymHook_InputCode1;
      m_inputCode[tempcode].MouseUp();
      if (m_inputCode[tempcode].IsEnable())
        AddOneKeyWord(m_inputCode[tempcode].GetCaption());
      break;
    }
    else
    {
      return CMenuBackgroundHook::MouseUp(scrPoint);
      break;
    }
  }

  if (m_isNeedRefesh)
  {
    Refresh();
  }
  m_isNeedRefesh = true;
  return ctrlType;
}

void CInputAcronymHook::InitKeyBoard()
{
  char cAcrKeyboard[][3] = {"A","B","C","D","E","F","G","H",
    "I","J","K","L","M","N","O","P","Q",
    "R","S","T","U","V","W","X","Y","Z"};

  m_vecWordsBuf.clear();
  unsigned uWordNum(sizeof(cAcrKeyboard)/3);
  for(int i=0, j=InputAcronymHook_InputCode1; j<=InputAcronymHook_InputCode26; i++, j++)
  {
    m_inputCode[i].SetCaption(cAcrKeyboard[i]);
  }

  //I U V ����������ʱ����
  m_inputCode[8].SetEnable(false);
  m_inputCode[20].SetEnable(false);
  m_inputCode[21].SetEnable(false);
}

bool CInputAcronymHook::EraseOneKeyWord(void)
{
  if (m_iCurCursorIndex)
  {
    -- m_iCurCursorIndex;
    m_vecWordPosX.clear();
    //
    m_tstrKeyWords.erase(m_iCurCursorIndex,1);
    //
    m_vecWordPosX.push_back(m_keyWordBox.GetLabelElement()->m_startX-2);
    //
    UeMap::CViewCanvas *aggCanvas(UeMap::CViewCanvas::GetCanvas(UeMap::CT_AGG));
    //
    for (short i(0),cursorPosX(m_keyWordBox.GetLabelElement()->m_startX); i!=m_tstrKeyWords.size(); ++i)
    {
      aggCanvas->GetCurCursorPos(m_keyWordBox.GetLabelElement()->m_textStyle,m_tstrKeyWords[i],
        cursorPosX);
      m_vecWordPosX.push_back(cursorPosX-2);
    }
    //
    SetCursorPosX(m_iCurCursorIndex);
    //
    TCHAR uniText[512];
    ::_tcscpy(uniText,m_tstrKeyWords.c_str());
    m_stringBasic.Chs2Ascii(uniText,m_keyWordBox.GetLabelElement()->m_label,MAXELEMENTNAME);
    //
    if (m_tstrKeyWords.size()<1)
    {
      m_searchBtn.SetEnable(false);
    }
  }
  return m_tstrKeyWords.size();
}

//����һ����
bool CInputAcronymHook::AddOneKeyWord(const char *pchLabelText)
{
  TCHAR uniChar[3] = {0, };
  m_stringBasic.Ascii2Chs(pchLabelText,uniChar,2);
  doAddOneKeyWord(uniChar[0]);
  return false;
}
bool CInputAcronymHook::doAddOneKeyWord(TCHAR oneWord)
{
  UeMap::CViewCanvas *aggCanvas(UeMap::CViewCanvas::GetCanvas(UeMap::CT_AGG));
  {
    short sCursorPosX(*(m_vecWordPosX.rbegin()));
    //
    aggCanvas->GetCurCursorPos(m_keyWordBox.GetLabelElement()->m_textStyle,oneWord,sCursorPosX);
    //
    if (sCursorPosX>(m_keyWordBox.GetLabelElement()->m_startX+m_keyWordBox.GetLabelElement()->m_width-5))
    {
      return false;
    }
  }
  m_tstrKeyWords.insert(m_iCurCursorIndex++,1,oneWord);
  //
  m_vecWordPosX.clear();
  m_vecWordPosX.push_back(m_keyWordBox.GetLabelElement()->m_startX-2);
  for (short i(0),cursorPosX(m_keyWordBox.GetLabelElement()->m_startX); i!=m_tstrKeyWords.size(); ++i)
  {
    aggCanvas->GetCurCursorPos(m_keyWordBox.GetLabelElement()->m_textStyle,m_tstrKeyWords[i],cursorPosX);
    m_vecWordPosX.push_back(cursorPosX-2);
  }
  m_searchBtn.SetEnable(m_tstrKeyWords.size()>0);
  //
  SetCursorPosX(m_iCurCursorIndex);
  //
  TCHAR uniText[512];
  ::_tcscpy(uniText,m_tstrKeyWords.c_str());
  m_stringBasic.Chs2Ascii(uniText,m_keyWordBox.GetLabelElement()->m_label,MAXELEMENTNAME);
  return true;
}

void CInputAcronymHook::ClearKeyWord(void)
{
  ::strcpy(m_keyWordBox.GetLabelElement()->m_label,"");
  //
  m_searchBtn.SetEnable(false);
  //
  m_vecWordPosX.clear();
  m_vecWordPosX.push_back(m_keyWordBox.GetLabelElement()->m_startX-2);
  //
  SetCursorPosX(0);
  m_tstrKeyWords.clear();
}

void CInputAcronymHook::ResetKeyWord(const char *pchKeyWord)
{
  if (pchKeyWord!=0)
  {
    ClearKeyWord();
    //
    TCHAR uniWords[512];
    unsigned uWordNum(m_stringBasic.Ascii2Chs(pchKeyWord,uniWords,512));
    //
    for (int i(0); i<uWordNum; ++i)
    {
      doAddOneKeyWord(uniWords[i]);
    }
  }
}

void CInputAcronymHook::SetCursorPosX(int curIndex)
{
  m_iCurCursorIndex = curIndex;
  m_deleteBtn.SetEnable(curIndex);
  m_pWordCursor->m_startX = m_vecWordPosX[curIndex];
}

char* CInputAcronymHook::GetKeyWord()
{
  return m_keyWordBox.GetCaption();
}

void CInputAcronymHook::DistSwitchCallBack(void *pDoCallBackObj,const SQLRecord *pResult)
{
  if (pDoCallBackObj)
  {
    ((CInputAcronymHook *)pDoCallBackObj)->DoDistSwitchCallBack(pResult);
  }
}

void CInputAcronymHook::DoDistSwitchCallBack(const SQLRecord *pResult)
{
  TCodeEntry codeEntry;
  codeEntry.m_uCode = pResult->m_addrCode;
  ::strcpy(codeEntry.m_chName, pResult->m_asciiName);
  CQueryWrapper::Get().SetQueryAdmInfo(codeEntry);
  m_distSwitchBtn.SetCaption(codeEntry.m_chName);
}

void CInputAcronymHook::SetQueryMode()
{
  //��������������ϴβ�һ������չؼ���
  int indexType = CQueryWrapper::Get().GetSQLSentence().m_indexType;
  //�ж��������͵��������ô����뷨�������һ������
  if (CAggHook::GetPrevHookType() == DHT_QueryMenuHook || CAggHook::GetPrevHookType() == DHT_DistrictSelectionHook)
  {
    if (indexType != UeQuery::IT_CityAcro && indexType != UeQuery::IT_CityName)
    {
      ResetKeyWord("");
    }
    CQueryWrapper::Get().SetQueryMode(UeQuery::IT_CityAcro);
    m_distSwitchBtn.SetCaption("ȫ��");
    m_distSwitchBtn.SetEnable(false);
    m_distSelectBtn.SetEnable(false);
    m_otherSearchBtn.SetVisible(false);
  }
  else
  {
    if (indexType == UeQuery::IT_CityAcro || indexType == UeQuery::IT_CityName)
    {
      ResetKeyWord("");
    }
    CQueryWrapper::Get().SetQueryMode(UeQuery::IT_PoiAcro);
    m_distSwitchBtn.SetCaption(CQueryWrapper::Get().GetQueryAdmName());
    m_distSwitchBtn.SetEnable(true);
    m_distSelectBtn.SetEnable(true);
    m_otherSearchBtn.SetVisible(true);
  }
}