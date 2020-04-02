/*===========================================================================
 *
 * File:	MainFrm.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	Thursday, 27 July, 2006
 *
 * Defines the interface of the CMainFrame class.
 *
 *=========================================================================*/
#ifndef __MainFrm_H
#define __MainFrm_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "errorbar.h"
  #include "undobar.h"
  #include "obeditdoc.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Custom messages */
  #define OBE_MSG_UPDATEUNDO (WM_APP + 209)
  #define OBE_MSG_UNDOITEMS  (WM_APP + 210)
  #define OBE_MSG_LOCKUNDO   (WM_APP + 211)

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Definition
 *
 *=========================================================================*/
class CMainFrame : public CMDIFrameWnd {
  DECLARE_DYNAMIC(CMainFrame)
public:
  CMainFrame();

  /*---------- Begin Protected Class Members ----------------------*/
protected:
  CStatusBar		m_wndStatusBar;
  CToolBar		m_wndToolBar;
  CObErrorBar		m_wndErrorBar;
  CObUndoBar		m_wndUndoBar;


  /*---------- Begin Public Class Methods ------------------------*/
public:

	/* Destructor */
  virtual ~CMainFrame();

  CView*      GetActiveMainView  (void);
  CObEditDoc* GetActiveObEditDoc (void);


	/* Diagnostics */
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif


	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CMainFrame)
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  //}}AFX_VIRTUAL

	/* Generated message map functions */
protected:
  //{{AFX_MSG(CMainFrame)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnDestroy();
  afx_msg void OnViewErrorBar();
  afx_msg void OnUpdateViewErrorBar(CCmdUI* pCmdUI);
  afx_msg void OnViewUndobar();
  afx_msg void OnUpdateViewUndobar(CCmdUI* pCmdUI);
  afx_msg LRESULT OnUpdateUndo (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnUndoItems (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnUndoLock (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnMdiMaximize (WPARAM wParam, LPARAM lParam);
  afx_msg void OnHelp (void);
  afx_msg void OnViewResourceviewer();
  afx_msg void OnHelpUespwiki();
  afx_msg void OnHelpCswiki();
	afx_msg void OnViewResetlists();
	//}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CMainFrame Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File MainFrm.H
 *=========================================================================*/
