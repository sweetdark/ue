#include "inputhandhook.h"

#ifndef _UEGUI_QUERYWRAPPER_H
#include "querywrapper.h"
#endif

#ifndef _UEMAP_AGGCANVAS_H
#include "uemap\viewcanvas.h"
#endif

// The 3rd handwriting definition
#include "third\arm\hzrecog.h"

#include "districtselectionhook.h"

#include "inputswitchhook.h"

using namespace UeGui;

short CInputHandHook::m_writingNum(0);
short *CInputHandHook::m_writingPts(0);
short CInputHandHook::m_writingCursor(0);
unsigned char *CInputHandHook::m_hwAddress(0);

CInputHandHook::CInputHandHook():m_pWrittingArea(0),m_isNewChar(true),
m_writingTime(0),m_prevX(-1),m_prevY(-1),m_isWriting(false),
m_pen(0),m_oldPen(0),m_renderingDC(0)
{
  m_strTitle = "����";
  m_vecHookFile.push_back(_T("inputhandhook.bin"));
}

CInputHandHook::~CInputHandHook()
{
  m_elements.clear();
  m_ctrlNames.clear();
  m_imageNames.clear();
}

void CInputHandHook::Init()
{
  CQueryWrapper::Get().SetQueryMode(UeQuery::IndexType::IT_PoiName);
  m_iCurCursorIndex = 0;
  m_vecWordPosX.clear();
  m_vecWordPosX.push_back(m_keyWordBox.GetLabelElement()->m_startX-2);
}

void CInputHandHook::Load()
{
  CQueryWrapper::Get().SetDefaultQueryKind();
  SetQueryMode();
  GetAssociateThing();
}

void CInputHandHook::UnLoad()
{
  m_isNewChar = true;
  if (m_renderingDC!=0)
  {
    if (m_oldPen!=0)
    {
      ::DeleteObject(::SelectObject(m_renderingDC,m_oldPen));
      m_oldPen = 0;
    }
    ::ReleaseDC(reinterpret_cast<HWND>(m_view->GetWndHandle()),m_renderingDC);
    m_renderingDC = 0;
  }
  UninitHandWriting();
};

void CInputHandHook::MakeNames()
{
  CMenuBackgroundHook::MakeNames();
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_CharBack,	"CharBack"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_InputCode1,	"InputCode1"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_InputCode2,	"InputCode2"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_InputCode3,	"InputCode3"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_InputCode4,	"InputCode4"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_InputCode5,	"InputCode5"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_InputCode6,	"InputCode6"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_InputCode7,	"InputCode7"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_InputCode8,	"InputCode8"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_InputCode9,	"InputCode9"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_InputCode10,	"InputCode10"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_WrittingArea,	"WrittingArea"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_WriteBackShade,	"WriteBackShade"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_PageUpIcon,	"PageUpIcon"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_PageDownIcon,	"PageDownIcon"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_DistSwitchBtn,	"DistSwitchBtn"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_DistSelectBtn,	"DistSelectBtn"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_PageUpBtn,	"PageUpBtn"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_DistSelectBtnIcon,	"DistSelectBtnIcon"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_PageDownBtn,	"PageDownBtn"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_EditBox,	"EditBox"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_EditSelectBtn,	"EditSelectBtn"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_EditSelectBtnIcon,	"EditSelectBtnIcon"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_KeyWordBox,	"KeyWordBox"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_WordSeparation,	"WordSeparation"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_OtherSearchBtn,	"OtherSearchBtn"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_InputSwitchBtn,	"InputSwitchBtn"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_OtherSearchIcon,	"OtherSearchIcon"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_InputSwitchBtnIcon,	"InputSwitchBtnIcon"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_DeleteBtn,	"DeleteBtn"));
  m_ctrlNames.insert(GuiName::value_type(InputHandHook_SearchBtn,	"SearchBtn"));
}

void CInputHandHook::MakeControls()
{
  CMenuBackgroundHook::MakeControls();
  m_distSwitchBtn.SetCenterElement(GetGuiElement(InputHandHook_DistSwitchBtn));
  m_distSelectBtn.SetCenterElement(GetGuiElement(InputHandHook_DistSelectBtn));
  m_distSelectBtn.SetIconElement(GetGuiElement(InputHandHook_DistSelectBtnIcon));

  m_editSelectBtn.SetCenterElement(GetGuiElement(InputHandHook_EditSelectBtn));
  m_editSelectBtn.SetIconElement(GetGuiElement(InputHandHook_EditSelectBtnIcon));

  m_keyWordBox.SetLabelElement(GetGuiElement(InputHandHook_KeyWordBox));

  m_otherSearchBtn.SetCenterElement(GetGuiElement(InputHandHook_OtherSearchBtn));
  m_otherSearchBtn.SetIconElement(GetGuiElement(InputHandHook_OtherSearchIcon));

  m_searchBtn.SetCenterElement(GetGuiElement(InputHandHook_SearchBtn));
  m_searchBtn.SetEnable(false);
  m_deleteBtn.SetCenterElement(GetGuiElement(InputHandHook_DeleteBtn));
  m_deleteBtn.SetEnable(false);

  m_inputSwitchBtn.SetCenterElement(GetGuiElement(InputHandHook_InputSwitchBtn));
  m_inputSwitchBtn.SetIconElement(GetGuiElement(InputHandHook_InputSwitchBtnIcon));

  m_pageUpBtn.SetCenterElement(GetGuiElement(InputHandHook_PageUpBtn));
  m_pageUpBtn.SetIconElement(GetGuiElement(InputHandHook_PageUpIcon));
  m_pageUpBtn.SetEnable(false);

  m_pageDownBtn.SetCenterElement(GetGuiElement(InputHandHook_PageDownBtn));
  m_pageDownBtn.SetIconElement(GetGuiElement(InputHandHook_PageDownIcon));
  m_pageDownBtn.SetEnable(false);

  for(int i=0, j=InputHandHook_InputCode1; j<=InputHandHook_InputCode10; i++, j++)
    m_inputCode[i].SetCenterElement(GetGuiElement(j));

  m_pWordCursor = GetGuiElement(InputHandHook_WordSeparation);
  m_pWrittingArea = GetGuiElement(InputHandHook_WrittingArea);
}

short CInputHandHook::MouseDown(CGeoPoint<short> &scrPoint)
{
  short ctrlType = CAggHook::MouseDown(scrPoint);
  switch(ctrlType)
  {
  case InputHandHook_DistSwitchBtn:
    {
      m_distSwitchBtn.MouseDown();
      AddRenderUiControls(&m_distSwitchBtn);
    }
    break;
  case InputHandHook_DistSelectBtn:
  case InputHandHook_DistSelectBtnIcon:
    {
      m_distSelectBtn.MouseDown();
      AddRenderUiControls(&m_distSelectBtn);
    }
    break;
  case InputHandHook_EditSelectBtn:
  case InputHandHook_EditSelectBtnIcon:
    {
      m_editSelectBtn.MouseDown();
      AddRenderUiControls(&m_editSelectBtn);
    }
    break;
  case InputHandHook_OtherSearchBtn:
  case InputHandHook_OtherSearchIcon:
    {
      m_otherSearchBtn.MouseDown();
      AddRenderUiControls(&m_otherSearchBtn);
    }
    break;
  case InputHandHook_SearchBtn:
    {
      m_searchBtn.MouseDown();
      AddRenderUiControls(&m_searchBtn);
    }
    break;
  case InputHandHook_DeleteBtn:
    {
      m_deleteBtn.MouseDown();
      AddRenderUiControls(&m_deleteBtn);
    }
    break;
  case InputHandHook_InputSwitchBtn:
  case InputHandHook_InputSwitchBtnIcon:
    {
      m_inputSwitchBtn.MouseDown();
      AddRenderUiControls(&m_inputSwitchBtn);
    }
    break;
  case InputHandHook_PageUpBtn:
  case InputHandHook_PageUpIcon:
    {
      m_pageUpBtn.MouseDown();
      AddRenderUiControls(&m_pageUpBtn);
    }
    break;
  case InputHandHook_PageDownBtn:
  case InputHandHook_PageDownIcon:
    {
      m_pageDownBtn.MouseDown();
      AddRenderUiControls(&m_pageDownBtn);
    }
    break;
  case InputHandHook_KeyWordBox:
  case InputHandHook_WordSeparation:
    {
      m_keyWordBox.MouseDown();
      AddRenderUiControls(&m_keyWordBox);
    }
    break;
  default:
    if (ctrlType>=InputHandHook_InputCode1 && ctrlType<=InputHandHook_InputCode10)
    {
      m_inputCode[ctrlType-InputHandHook_InputCode1].MouseDown();
      AddRenderUiControls(&m_inputCode[ctrlType-InputHandHook_InputCode1]);
      break;
    } 
    else if (m_pWrittingArea->m_extent.IsContain(scrPoint))
    {
      //֮ǰû��д����
      if(m_isNewChar)
      {
        InitHandWriting();
        //
        m_isNewChar = false;
        // New start position
        if(!m_renderingDC)
        {
          m_renderingDC = ::GetDC(reinterpret_cast<HWND>(m_view->GetWndHandle()));
          m_pen = ::CreatePen(PS_SOLID, 4, RGB(255,255,255));
          m_oldPen = reinterpret_cast<HPEN>(::SelectObject(m_renderingDC, m_pen));
        }
      }
      if (m_writingPts)
      {
        m_isWriting = true;
        if(m_writingCursor<(m_writingNum-2))
        {
          m_writingPts[m_writingCursor++] = scrPoint.m_x-m_pWrittingArea->m_startX;
          m_writingPts[m_writingCursor++] = scrPoint.m_y-m_pWrittingArea->m_startY;
          //
          m_prevX = scrPoint.m_x;
          m_prevY = scrPoint.m_y;
        }
      }
      return InputHandHook_WrittingArea;
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

short CInputHandHook::MouseMove(CGeoPoint<short> &scrPoint)
{
  if (m_isWriting && m_writingCursor<(m_writingNum-2))
  {
    if (m_pWrittingArea->m_extent.IsContain(scrPoint))
    {
      m_writingPts[m_writingCursor++] = scrPoint.m_x-m_pWrittingArea->m_startX;
      m_writingPts[m_writingCursor++] = scrPoint.m_y-m_pWrittingArea->m_startY;

      if(::abs(m_prevX-scrPoint.m_x)>1 || ::abs(m_prevY-scrPoint.m_y)>1)
      {
        ::MoveToEx(m_renderingDC, m_prevX, m_prevY, NULL);
        ::LineTo(m_renderingDC, scrPoint.m_x, scrPoint.m_y);

        m_prevX = scrPoint.m_x;
        m_prevY = scrPoint.m_y;

        //����ˢ�£�����ʲô��û����
        //Refresh();
      }
      return InputHandHook_WrittingArea;
    }
  }
  return 0;
}

short CInputHandHook::MouseUp(CGeoPoint<short> &scrPoint)
{
  short ctrlType = CAggHook::MouseUp(scrPoint);
  switch(m_downElementType)
  {
  case InputHandHook_DistSwitchBtn:
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
  case InputHandHook_DistSelectBtn:
  case InputHandHook_DistSelectBtnIcon:
    {
      m_distSelectBtn.MouseUp();
    }
    break;
  case InputHandHook_EditSelectBtn:
  case InputHandHook_EditSelectBtnIcon:
    {
      m_editSelectBtn.MouseUp();
    }
    break;
  case InputHandHook_OtherSearchBtn:
  case InputHandHook_OtherSearchIcon:
    {
      m_otherSearchBtn.MouseUp();
      CAggHook::TurnTo(DHT_QueryMenuHook);
    }
    break;
  case InputHandHook_SearchBtn:
    {
      m_searchBtn.MouseUp();
      if (m_searchBtn.IsEnable())
      {
        if (CQueryWrapper::Get().GetSQLSentence().m_indexType == UeQuery::IT_PoiName)
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
  case InputHandHook_DeleteBtn:
    {
      m_deleteBtn.MouseUp();
      if(m_deleteBtn.IsEnable())
      {
        EraseOneKeyWord();
        GetAssociateThing();
      }
    }
    break;
  case InputHandHook_InputSwitchBtn:
  case InputHandHook_InputSwitchBtnIcon:
    {
      m_inputSwitchBtn.MouseUp();
      if (m_inputSwitchBtn.IsEnable())
      {
        CAggHook::TurnTo(DHT_InputSwitchHook);
      }
    }
    break;
  case InputHandHook_PageUpBtn:
  case InputHandHook_PageUpIcon:
    {
      m_pageUpBtn.MouseUp();
      if (m_pageUpBtn.IsEnable())
      {
        m_iCurWordIndex -= INPUTCODENUM;
        SetAssociateBtnLabels();
      }
    }
    break;
  case InputHandHook_PageDownBtn:
  case InputHandHook_PageDownIcon:
    {
      m_pageDownBtn.MouseUp();
      if (m_pageDownBtn.IsEnable())
      {
        m_iCurWordIndex += INPUTCODENUM;
        SetAssociateBtnLabels();
      }
    }
    break;
  case InputHandHook_KeyWordBox:
  case InputHandHook_WordSeparation:
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
    if (ctrlType>=InputHandHook_InputCode1 && ctrlType<=InputHandHook_InputCode10)
    {
      short tempcode = ctrlType-InputHandHook_InputCode1;
      m_inputCode[tempcode].MouseUp();
      AddOneKeyWord(m_inputCode[tempcode].GetCaption());
      GetAssociateThing();
      break;
    }
    else if (m_isWriting && m_pWrittingArea->m_extent.IsContain(scrPoint))
    {
      m_writingTime = ::GetTickCount();
      //
      if (m_writingCursor<(m_writingNum-2))
      {
        m_writingPts[m_writingCursor++] = scrPoint.m_x-m_pWrittingArea->m_startX;
        m_writingPts[m_writingCursor++] = scrPoint.m_y-m_pWrittingArea->m_startY;
        //
        m_writingPts[m_writingCursor++] = -1;
        m_writingPts[m_writingCursor++] = 0;
      }
      m_isWriting = false;
      return InputHandHook_WrittingArea;
    }
    else
    {
      m_isWriting = false;
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

bool CInputHandHook::EraseOneKeyWord(void)
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
bool CInputHandHook::AddOneKeyWord(const char *pchLabelText)
{
  TCHAR uniChar[3] = {0, };
  m_stringBasic.Ascii2Chs(pchLabelText,uniChar,2);
  doAddOneKeyWord(uniChar[0]);
  return false;
}
bool CInputHandHook::doAddOneKeyWord(TCHAR oneWord)
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

void CInputHandHook::ClearKeyWord(void)
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

void CInputHandHook::ResetKeyWord(const char *pchKeyWord)
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

void CInputHandHook::SetCursorPosX(int curIndex)
{
  m_iCurCursorIndex = curIndex;
  m_deleteBtn.SetEnable(curIndex);
  m_pWordCursor->m_startX = m_vecWordPosX[curIndex];
}

bool CInputHandHook::GetAssociateThing()
{
  //
  m_iCurWordIndex = 0;
  m_vecWordsBuf.clear();
  //
  CQueryWrapper &queryWrapper(CQueryWrapper::Get());
  queryWrapper.SetAssociateNextWord(&m_vecWordsBuf);
  queryWrapper.SetQueryKeyword(m_keyWordBox.GetCaption());

  //
  CUeRecord *pRecordVec(0);
  queryWrapper.SetMaxQueryRecordNum(20);
  pRecordVec = queryWrapper.DoQueryGetRecord();

  if ((pRecordVec==0 || pRecordVec->GetCount())
    && m_vecWordsBuf.size()==0)
  {
    for (int i=0; i<INPUTCODENUM; ++i)
    {
      m_inputCode[i].SetEnable(false);
      m_inputCode[i].SetCaption("");
    }
  }
  else
  {
    SetAssociateBtnLabels();
  }

  return true;
}

void CInputHandHook::SetAssociateBtnLabels()
{
  int i(0),j(m_iCurWordIndex);
  for (; j<m_vecWordsBuf.size() && i<INPUTCODENUM; ++i,++j)
  {
    m_inputCode[i].SetEnable(true);
    m_inputCode[i].SetCaption(m_vecWordsBuf[j].c_str());
  }
  m_pageUpBtn.SetEnable(m_iCurWordIndex!=0);
  //
  m_pageDownBtn.SetEnable(j<m_vecWordsBuf.size());
  //
  for (; i<INPUTCODENUM; ++i)
  {
    m_inputCode[i].SetEnable(false);
    m_inputCode[i].SetCaption("");
  }
}

char* CInputHandHook::GetKeyWord()
{
  return m_keyWordBox.GetCaption();
}

void CInputHandHook::DoHandWriting(int curTime)
{
  if (!m_isNewChar && !m_isWriting)
  {
    if ((curTime-m_writingTime)>1000)
    {
      m_writingTime = 0;
      m_isNewChar = true;
      m_writingPts[m_writingCursor++] = -1;
      m_writingPts[m_writingCursor++] = -1;

      m_iCurWordIndex = 0;
      m_vecWordsBuf.clear();
#ifdef _WIN32_WCE
      //��ȡ20�����ܵ�����
      unsigned uMaxNum(20);
      unsigned short *pusWordBuf(new unsigned short[uMaxNum]);
      if (pusWordBuf!=0)
      {
        //int iWordNum(HZCharacterRecognize(m_writingPts,pusWordBuf,
        //	uMaxNum,RECOG_RANGE_GB |RECOG_RANGE_ADAPTATION));
        int iWordNum(HZCharacterRecognize(m_writingPts,pusWordBuf,
          uMaxNum,RECOG_RANGE_ALL));
        //
        char cWord[3] = {};
        for (int i(0); i<(iWordNum*2); i+=2)
        {
          cWord[0] = *((char *)pusWordBuf+i);
          cWord[1] = *((char *)pusWordBuf+i+1);
          //
          m_vecWordsBuf.push_back(cWord);
        }
        //�����ֶ��Ų����İ�ť��
        SetAssociateBtnLabels();
        if (iWordNum!=0)
        {
          AddOneKeyWord(m_inputCode[0].GetCaption());
        }
        delete[] pusWordBuf;
      }
#else
      m_vecWordsBuf.push_back("��");
      m_vecWordsBuf.push_back("��");
      m_vecWordsBuf.push_back("��");
      m_vecWordsBuf.push_back("��");
      m_vecWordsBuf.push_back("��");
      m_vecWordsBuf.push_back("ʹ");
      m_vecWordsBuf.push_back("��");
      m_vecWordsBuf.push_back("��");
      m_vecWordsBuf.push_back("��");
      m_vecWordsBuf.push_back("��");
      SetAssociateBtnLabels();
		  m_keyWordBox.SetCaption("���������ʹ�ô˹���");
#endif
      //
      m_writingCursor = 0;
      ::memset(m_writingPts,0x00,sizeof(short)*m_writingNum);
      return Refresh();
    }
  }
}

void CInputHandHook::InitHandWriting()
{
  if (m_hwAddress!=0)
    return;
  // Given writing points
  m_writingNum = 1024 * 1;
  m_writingPts = (short *)::malloc(sizeof(short) * m_writingNum);
  ::memset(m_writingPts, 0x00, sizeof(short) * m_writingNum);
  m_writingCursor = 0;

  // Load HW dictionary
  const CPathBasic &pathBasic(CPathBasic::Get());
  TCHAR path[CPathBasic::MAXPATHLENGTH] = {0, };
  pathBasic.GetModulePath(path, CPathBasic::MAXPATHLENGTH);
  tstring hwFile = path;
  pathBasic.GetPathSeperator(hwFile);
  hwFile += _T("jHWRDic.dat");

  const CFileBasic &fileBasic = CFileBasic::Get();
  void *hwHandle = fileBasic.OpenFile(hwFile, CFileBasic::UE_FILE_READ);
  assert(fileBasic.IsValidHandle(hwHandle));
  fileBasic.SeekFile(hwHandle, 0, CFileBasic::UE_SEEK_END);
  long size = fileBasic.TellFilePos(hwHandle);
  m_hwAddress = (unsigned char *)(::malloc(size));
  assert(m_hwAddress);

  fileBasic.SeekFile(hwHandle, 0, CFileBasic::UE_SEEK_BEGIN);
  void *ptr = (void *)m_hwAddress;
  int count = 1;
  fileBasic.ReadFile(hwHandle, &ptr, size, count);
  fileBasic.CloseFile(hwHandle);
#ifdef _WIN32_WCE
  HZInitCharacterRecognition(m_hwAddress);
#endif
}

void CInputHandHook::UninitHandWriting()
{
  if (m_hwAddress==0)
    return;
  //
#ifdef _WIN32_WCE
  HZExitCharacterRecognition();
#endif
  if(m_hwAddress!=NULL)
  {
    ::free(m_hwAddress);
    m_hwAddress = 0;
  }
  if(m_writingPts)
  {
    ::free(m_writingPts);
    m_writingPts = 0;
  }
  m_writingNum = 0;
}

void CInputHandHook::DistSwitchCallBack(void *pDoCallBackObj,const SQLRecord *pResult)
{
  if (pDoCallBackObj)
  {
    ((CInputHandHook *)pDoCallBackObj)->DoDistSwitchCallBack(pResult);
  }
}

void CInputHandHook::DoDistSwitchCallBack(const SQLRecord *pResult)
{
  TCodeEntry codeEntry;
  codeEntry.m_uCode = pResult->m_addrCode;
  ::strcpy(codeEntry.m_chName, pResult->m_asciiName);
  CQueryWrapper::Get().SetQueryAdmInfo(codeEntry);
  m_distSwitchBtn.SetCaption(codeEntry.m_chName);
  GetAssociateThing();
}

void CInputHandHook::SetQueryMode()
{
  //��������������ϴβ�һ������չؼ���
  int indexType = CQueryWrapper::Get().GetSQLSentence().m_indexType;
  //�ж��������͵��������ô����뷨�������һ������
  if (CAggHook::GetPrevHookType() == DHT_QueryMenuHook || CAggHook::GetPrevHookType() == DHT_DistrictSelectionHook)
  {
    if (indexType != UeQuery::IT_CityName && indexType != UeQuery::IT_CityAcro)
    {
      ResetKeyWord("");
    }
    CQueryWrapper::Get().SetQueryMode(UeQuery::IT_CityName);
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
    CQueryWrapper::Get().SetQueryMode(UeQuery::IT_PoiName);
    m_distSwitchBtn.SetCaption(CQueryWrapper::Get().GetQueryAdmName());
    m_distSwitchBtn.SetEnable(true);
    m_distSelectBtn.SetEnable(true);
    m_otherSearchBtn.SetVisible(true);
  }
}