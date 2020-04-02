/*===========================================================================
 *
 * File:	MainFrm.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	Wednesday, July 03, 2002
 *
 * Implementation of the CMainFrame class.
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "MainFrm.h"
#include "modfile/obundoitem.h"
#include "obeditdoc.h"
#include "obeditview.h"


/*===========================================================================
 *
 * Local Definitions
 *
 *=========================================================================*/

	/* Debug defines */
//#ifdef _DEBUG
//  #define new DEBUG_NEW
//  #undef THIS_FILE
//  static char THIS_FILE[] = __FILE__;
//#endif

	/* Status bar setup */
  static UINT indicators[] = {
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
   };

  IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void l_ErrorBarLogCallback (pString, Args, UserData);
 *
 *=========================================================================*/
void l_ErrorBarLogCallback (const SSCHAR* pString, va_list Args, const dword UserData) {
  CObErrorBar* pErrorBar = (CObErrorBar *) UserData;
  CString Buffer;

  Buffer.FormatV(pString, Args);
  if (pErrorBar) pErrorBar->AddText(Buffer);
}
/*===========================================================================
 *		End of Function l_ErrorBarLogCallback()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void l_ErrorBarErrorCallback (pError, UserData);
 *
 *=========================================================================*/
void l_ErrorBarErrorCallback (CObError* pError, const dword UserData) {
  CObErrorBar* pErrorBar = (CObErrorBar *) UserData;
  CString Buffer;

  Buffer.Format("ERROR: %s", pError->GetErrorMessage());
  if (pErrorBar) pErrorBar->AddBoldText(Buffer);
}
/*===========================================================================
 *		End of Function l_ErrorBarErrorCallback()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_VIEW_ERROR_BAR, OnViewErrorBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ERROR_BAR, OnUpdateViewErrorBar)
	ON_COMMAND(ID_VIEW_UNDOBAR, OnViewUndobar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_UNDOBAR, OnUpdateViewUndobar)
	ON_MESSAGE(OBE_MSG_UPDATEUNDO, OnUpdateUndo)
	ON_MESSAGE(OBE_MSG_UNDOITEMS, OnUndoItems)
	ON_MESSAGE(OBE_MSG_LOCKUNDO, OnUndoLock)
	ON_MESSAGE(WM_MDIMAXIMIZE, OnMdiMaximize)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_COMMAND(ID_VIEW_RESOURCEVIEWER, OnViewResourceviewer)
	ON_COMMAND(ID_HELP_UESPWIKI, OnHelpUespwiki)
	ON_COMMAND(ID_HELP_CSWIKI, OnHelpCswiki)
	ON_COMMAND(ID_VIEW_RESETLISTS, OnViewResetlists)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Class CMainFrame Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Constructor
 *
 *=========================================================================*/
CMainFrame::CMainFrame() {
 }
/*===========================================================================
 *		End of Class CMainFrame Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Destructor
 *
 *=========================================================================*/
CMainFrame::~CMainFrame() {
 }
/*===========================================================================
 *		End of Class CMainFrame Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Event - int OnCreate (lpCreateStruct);
 *
 *=========================================================================*/
int CMainFrame::OnCreate (LPCREATESTRUCT lpCreateStruct) {

	/* Call the base class create method first */
  if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1) return (-1);

  if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
    TRACE0("Failed to create toolbar\n");
    return (-1);
  }

  if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT))) {
    TRACE0("Failed to create status bar\n");
    return (-1);
  }

  if (!m_wndErrorBar.Create(_T("System Log"), this, 123)) {
    TRACE0("Failed to create error bar\n");
    return (-1);
  }

  if (!m_wndUndoBar.Create(_T("Undo Items"), this, CSize(150,300), true, 124)) {
    TRACE0("Failed to create undo bar\n");
    return (-1);
  }

  m_wndErrorBar.SetBarStyle(CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_ALIGN_BOTTOM );
  m_wndUndoBar.SetBarStyle(CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_ALIGN_RIGHT );

  m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
  m_wndErrorBar.EnableDocking(CBRS_ALIGN_ANY);
  m_wndUndoBar.EnableDocking(CBRS_ALIGN_ANY);
  EnableDocking(CBRS_ALIGN_ANY);
  DockControlBar(&m_wndToolBar);
  DockControlBar(&m_wndErrorBar);
  DockControlBar(&m_wndUndoBar);

  SystemLog.SetCallback(l_ErrorBarLogCallback, (dword) &m_wndErrorBar);
  ObErrorHandler->AddCallback(l_ErrorBarErrorCallback, (dword) &m_wndErrorBar);

  return (0);
} 
/*===========================================================================
 *		End of Class Event CMainFrame::OnCreate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Method - BOOL PreCreateWindow (cs);
 *
 *=========================================================================*/
BOOL CMainFrame::PreCreateWindow (CREATESTRUCT& cs) {
  if( !CMDIFrameWnd::PreCreateWindow(cs) ) return FALSE;

  return TRUE;
 }
/*===========================================================================
 *		End of Class Method CMainFrame::PreCreateWindow()
 *=========================================================================*/


#ifdef _DEBUG
/*===========================================================================
 *
 * Class CMainFrame Diagnostics
 *
 *=========================================================================*/
void CMainFrame::AssertValid() const {
  CMDIFrameWnd::AssertValid();
 }

void CMainFrame::Dump(CDumpContext& dc) const {
  CMDIFrameWnd::Dump(dc);
 }
/*===========================================================================
 *		End of Class CMainFrame Diagnostics
 *=========================================================================*/
#endif


/*===========================================================================
 *
 * Class CMainFrame Event - void OnDestroy ();
 *
 *=========================================================================*/
void CMainFrame::OnDestroy() {
  SystemLog.SetCallback(NULL, 0);
  ObErrorHandler->RemoveCallback(l_ErrorBarErrorCallback);
  CMDIFrameWnd::OnDestroy();
}
/*===========================================================================
 *		End of Class Event CMainFrame::OnDestroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Event - void OnViewErrorBar ();
 *
 *=========================================================================*/
void CMainFrame::OnViewErrorBar() {
  OnBarCheck(123);
}
/*===========================================================================
 *		End of Class Event CMainFrame::OnViewErrorBar()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Event - void OnUpdateViewErrorBar (pCmdUI);
 *
 *=========================================================================*/
void CMainFrame::OnUpdateViewErrorBar(CCmdUI* pCmdUI) {
  pCmdUI->SetCheck((m_wndErrorBar.GetStyle() & WS_VISIBLE) != 0);
}
/*===========================================================================
 *		End of Class Event CMainFrame::OnUpdateViewErrorBar()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Event - void OnViewUndobar ();
 *
 *=========================================================================*/
void CMainFrame::OnViewUndobar() {
  OnBarCheck(124);
}
/*===========================================================================
 *		End of Class Event CMainFrame::OnViewUndobar()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Event - void OnUpdateViewUndobar (pCmdUI);
 *
 *=========================================================================*/
void CMainFrame::OnUpdateViewUndobar(CCmdUI* pCmdUI) {
  pCmdUI->SetCheck((m_wndUndoBar.GetStyle() & WS_VISIBLE) != 0);
}
/*===========================================================================
 *		End of Class Event CMainFrame::OnUpdateViewUndobar()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Event - LRESULT OnUpdateUndo (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CMainFrame::OnUpdateUndo (WPARAM wParam, LPARAM lParam) {
  CObUndoItemArray* pUndoItems = (CObUndoItemArray *) wParam;

  m_wndUndoBar.UpdateList(pUndoItems);
  return (0);
}
/*===========================================================================
 *		End of Class Event CMainFrame::OnUpdateUndo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Event - LRESULT OnUndoItems (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CMainFrame::OnUndoItems (WPARAM wParam, LPARAM lParam) {
  CObUndoItem* pItem;
  CObEditDoc*  pDoc;

  pItem = m_wndUndoBar.GetCurrentUndoItem();
  if (pItem == NULL) return (0); 

  pDoc = GetActiveObEditDoc();
  if (pDoc == NULL) return (0);

  pDoc->GetRecordHandler().PerformUndoTo(pItem);
  
  pDoc->UpdateAllViews(NULL, OBEDIT_DOC_HINT_UPDATEALL, NULL);
  //m_wndUndoBar.UpdateList(&pDoc->GetRecordHandler().GetUndoItems());
  return (0);
} 
/*===========================================================================
 *		End of Class Event CMainFrame::OnUndoItems()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Method - CDocument* GetActiveObEditDoc (void);
 *
 *=========================================================================*/
CObEditDoc* CMainFrame::GetActiveObEditDoc (void) {
  CView*     pView = GetActiveMainView();
  CDocument* pDoc;

  if (pView == NULL) return (NULL);

  pDoc = pView->GetDocument();
  if (pDoc == NULL) return (NULL);

  if (pDoc->IsKindOf(RUNTIME_CLASS(CObEditDoc))) return (CObEditDoc *) (pDoc);
  return (NULL);
}
/*===========================================================================
 *		End of Class Method CMainFrame::GetActiveObEditDoc()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Method - CView* GetActiveMainView (void);
 *
 * Attempt to find the current CMWEditView object which is returned.
 * NULL is returned if it is not found.
 *
 *=========================================================================*/
CView* CMainFrame::GetActiveMainView (void) {
  CMDIChildWnd* pActiveWnd = MDIGetActive();
  CView*	pView;
  POSITION	ViewPos;
  CDocument*	pDoc;  
  
	/* Ensure there is an active child window, view, and document */
  if (pActiveWnd == NULL) return (NULL);
  CView* pActiveView = pActiveWnd->GetActiveView();
  if (pActiveView == NULL) return (NULL);
  pDoc = pActiveView->GetDocument();
  if (pDoc == NULL) return (NULL);

	/* Find the 'main' view in the list of current document views */
  ViewPos = pDoc->GetFirstViewPosition();

  while (ViewPos != NULL) {
    pView = pDoc->GetNextView(ViewPos);
    if (pView->IsKindOf(RUNTIME_CLASS(CObEditView))) return (pView);
   }

	/* No matching view found */
  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CMainFrame::GetActiveMainView()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Event - LRESULT OnMdiMaximize (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CMainFrame::OnMdiMaximize (WPARAM wParam, LPARAM lParam) {
  int i = 0;

  return (0);
} 
/*===========================================================================
 *		End of Class Event CMainFrame::OnMdiMaximize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Event - void OnHelp (void);
 *
 *=========================================================================*/
void CMainFrame::OnHelp (void) {
  CObEditView* pView = (CObEditView *) GetActiveMainView();

  if (pView == NULL) {
    GetObEditApp().OpenWebHelp(NULL);
  }
  else {
    pView->GetDlgHandler().OnHelp(NULL, NULL);
  }

}
/*===========================================================================
 *		End of Class Event CMainFrame::OnHelp()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Event - void OnViewResourceviewer ();
 *
 *=========================================================================*/
void CMainFrame::OnViewResourceviewer() {
  GetObEditApp().OpenResourceView();
}
/*===========================================================================
 *		End of Class Event CMainFrame::OnViewResourceviewer()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Event - void OnHelpUespwiki ();
 *
 *=========================================================================*/
void CMainFrame::OnHelpUespwiki() {
  OpenWebPage(CObEditDlgHandler::GetOptions().UESPWikiPrefix + CObEditDlgHandler::GetOptions().DefaultUESPPage);
}
/*===========================================================================
 *		End of Class Event CMainFrame::OnHelpUespwiki()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Event - void OnHelpCswiki ();
 *
 *=========================================================================*/
void CMainFrame::OnHelpCswiki() {
  OpenWebPage(CObEditDlgHandler::GetOptions().CSWikiPrefix + CObEditDlgHandler::GetOptions().DefaultCSPage);
}
/*===========================================================================
 *		End of Class Event CMainFrame::OnHelpCswiki()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Event - LRESULT OnUndoLock (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CMainFrame::OnUndoLock (WPARAM wParam, LPARAM lParam) {
  m_wndUndoBar.LockUpdates(wParam != 0);
  return (0);
} 
/*===========================================================================
 *		End of Class Event CMainFrame::OnUndoLock()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Event - void OnViewResetlists (void);
 *
 *=========================================================================*/
void CMainFrame::OnViewResetlists() {

  GetObEditApp().ResetListState();
}
/*===========================================================================
 *		End of Class Event CMainFrame::OnViewResetlists()
 *=========================================================================*/
