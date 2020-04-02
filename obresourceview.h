/*===========================================================================
 *
 * File:	Obresourceview.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 5, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBRESOURCEVIEW_H
#define __OBRESOURCEVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obimagectrl.h"
  #include "bsafile/obresourcehandler.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Custom window messages */
  #define ID_OBRESOURCE_CHECKDROP (WM_APP + 901)
  #define ID_OBRESOURCE_DROP      (WM_APP + 902)

	/* Return values from notify messages */
  #define OBRESOURCE_DROPCHECK_OK	2345
  #define OBRESOURCE_DROPCHECK_ERROR	5432
  #define OBRESOURCE_DROPCHECK_NOCHANGE 2346

	/* Default main resource paths */
  #define OBRESOURCE_PATH_TEXTURES	"textures\\"
  #define OBRESOURCE_PATH_MESHES	"meshes\\"
  #define OBRESOURCE_PATH_SOUNDS	"sound\\"

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

  struct obrespreviewinfo_t {
	CObResourceInstance*	pInstance;
	CString			Filename;
	int64			Filesize;
	int64			StartOffset;
	bool			PlainFile;
  };

	/* Used to test drop targets */
  struct obresourcedropinfo_t {
   	NMHDR			Notify;
   	CObResourceFile*	pResourceFile;
	dword			ParentThread;
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObResourceView Definition
 *
 *=========================================================================*/
class CObResourceView : public CFormView {
  DECLARE_DYNCREATE(CObResourceView);

  /*---------- Begin Protected Class Members ------------------------------*/
protected:
  CObResourceHandler*	m_pResourceHandler;	/* References to resource objects */
  CObBsaFileArray*	m_pBsaFiles;

  CObResourceInstance*	m_pCurrentInstance;
  CImageList		m_ImageList;

  CObResourceFile*	m_pDragResource;
  CImageList*		m_pDragImage;
  bool			m_IsDragging;
  HCURSOR		m_hGoodDropCursor;
  HCURSOR		m_hBadDropCursor;
  bool			m_LastDropValid;
  CWnd*			m_pLastDropWnd;

  bool			m_EnablePreview;

  CBitmap		m_Bitmaps[10];


  /*---------- Begin Protected Class Methods ------------------------------*/
protected:

	/* Create from serialization only */
  CObResourceView();

	/* Update helpers */
  void      FillResourceTree   (void);
  void      FillResourceTree   (CObResourceFolder* pFolder, HTREEITEM hParent);
  HTREEITEM AddResourceTree    (CObResourceFile* pFile, HTREEITEM hParent);
  void      UpdateResourceTree (CObResourceFile* pFile, HTREEITEM hItem);

  void ClearDisplayedInstance  (void);
  void UpdateDisplayedInstance (void);

  void PreviewInstance (CObResourceInstance* pInstance);
  void PreviewImage    (CObResourceInstance* pInstance, obrespreviewinfo_t& PreviewInfo);
  void PreviewUnknown  (CObResourceInstance* pInstance, obrespreviewinfo_t& PreviewInfo);
  void PreviewText     (CObResourceInstance* pInstance, obrespreviewinfo_t& PreviewInfo);
  void ClearPreview    (void);

  void CleanupDrag    (void);
  int  SendDropNotify (CPoint Point, const int MessageID);


  /*---------- Begin Public Class Methods ---------------------------------*/
public:
	/* Destructor */
  virtual ~CObResourceView();

	/* Set class members */
  void SetEnablePreview   (const bool              Flag) { m_EnablePreview    = Flag; }
  void SetResourceHandler (CObResourceHandler* pHandler) { m_pResourceHandler = pHandler; }
  void SetBsaFileArray    (CObBsaFileArray*      pArray) { m_pBsaFiles        = pArray; }

	/* Find and select a particular resource */
  bool SelectResource (const char* pResource);


	/* Resource members */
  //{{AFX_DATA(CObResourceView)
  enum { IDD = IDD_RESOURCE_VIEW };
  CRichEditCtrl	m_PreviewText;
  CEdit		m_Filetime;
  CEdit		m_Filesize;
  CEdit		m_Filename;
  CStatic	m_HBar;
  CTreeCtrl	m_ResourceTree;
  CObImageCtrl  m_PreviewImage;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObResourceView)
public:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnInitialUpdate();
  //}}AFX_VIRTUAL

// Implementation
public:


#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif


	/* Generated message map functions */
protected:
  //{{AFX_MSG(CObResourceView)
  afx_msg void OnDblclkResourceTree(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnSelchangedResourceTree(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  afx_msg void OnBegindragResourceTree(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnCaptureChanged(CWnd *pWnd);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnHelp (void);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObResourceView Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obresourceview.H
 *=========================================================================*/
 
