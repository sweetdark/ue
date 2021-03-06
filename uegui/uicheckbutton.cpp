#include "uicheckbutton.h"

using namespace UeGui;

void CUiCheckButton::MouseDown()
{
  if (!IsVisible() || !IsEnable())
  {
    return;
  }
  CUiButton::MouseDown();
}

void CUiCheckButton::MouseUp()
{
  if (!IsVisible() || !IsEnable())
  {
    return;
  }
  CUiButton::MouseUp();

  if (m_checked)
  {
    DoCheck(false);
  }
  else
  {
    DoCheck(true);
  }
}

void CUiCheckButton::MouseMove()
{
  //暂时没有效果
  CUiButton::MouseMove();  
}

void CUiCheckButton::SetCheck( bool value )
{
  if (!IsVisible() || !IsEnable())
  {
    return;
  }
  DoCheck(value);
  if (m_atoRefresh)
  {
    RenderElements();
  }
}

void UeGui::CUiCheckButton::DoCheck( bool value )
{
  m_checked = value;
  if (m_iconElement)
  {
    if (m_checked)
    {      
      //m_iconElement->m_textStyle = m_iconElement->m_focusTextStyle;
      m_iconElement->m_backStyle = m_iconElement->m_bkFocus;
    }
    else
    {
      //m_iconElement->m_textStyle = m_iconElement->m_normalTextStylpe;
      m_iconElement->m_backStyle = m_iconElement->m_bkNormal;
    }
  }
}

bool CUiCheckButton::Checked()
{
  return m_checked;
}

void UeGui::CUiCheckButton::SetVisible( bool value )
{
  CUiBitButton::SetVisible(value);
}

void UeGui::CUiCheckButton::SetEnable( bool value )
{
  CUiBitButton::SetEnable(value);
  //由于调用完基类的SetEnable后，会将当前按钮选中和非选中状态的图片换成禁用状态图片，所以这里须重修处理
  if (m_iconElement)
  {
    if (m_checked)
    {
      m_iconElement->m_backStyle = m_iconElement->m_bkFocus;
    }
    else
    {
      if (m_iconElement->m_bkDisabled > 0)
      {
        m_iconElement->m_backStyle = m_iconElement->m_bkNormal;
      }      
    }
  }
}

void UeGui::CUiCheckButton::RenderElements()
{
  CUiBitButton::RenderElements();
}