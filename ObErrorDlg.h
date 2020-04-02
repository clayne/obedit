/*===========================================================================
 *
 * File:	Oberrordlg.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	July 31, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBERRORDLG_H
#define __OBERRORDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Error dialog flags */
  #define OBERRDLG_SHOWALLERRORS	1
  #define OBERRDLG_SHOWUNTAGGEDERRORS	2

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/

     
/*===========================================================================
 *
 * Begin Class CObErrorDlg Definition
 *
 *=========================================================================*/
class CObErrorDlg : public CDialog {


  /*---------- Protected Class Members -------------------------------*/
protected:
  CString	m_Title;
  CString	m_Message;
  dword		m_Flags;
  dword		m_OutputCount;


  /*---------- Protected Class Members -------------------------------*/
protected:

	/* Add error information to the dialog */
  void AddLastError            (void);
  void AddAllErrors            (void);
  void AddAllUntaggedErrors    (void);
  void AddErrorInfo            (CObError* pError, const int ErrorIndex);


  /*---------- Public Class Methods ---------------------------------*/
public:

	/* Constructor */
  CObErrorDlg(CWnd* pParent = NULL);


	/* Set class members */
  void SetTitle   (const TCHAR* pString) { m_Title   = pString; }
  void SetMessage (const TCHAR* pString) { m_Message = pString; }
  void SetFlags   (const dword    Flags) { m_Flags   = Flags; }

	/* Dialog Data */
  //{{AFX_DATA(CObErrorDlg)
  enum { IDD = IDD_OBERROR_DLG };
  CEdit	m_ErrorDetails;
  CEdit	m_ErrorMessage;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObErrorDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CObErrorDlg)
  virtual BOOL OnInitDialog();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObErrorDlg Definition
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
 *		End of File Oberrordlg.H
 *=========================================================================*/
