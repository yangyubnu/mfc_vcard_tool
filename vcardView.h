// vcardView.h : interface of the CVcardView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VCARDVIEW_H__6127D577_757A_42B9_97E9_13DEF84A82D2__INCLUDED_)
#define AFX_VCARDVIEW_H__6127D577_757A_42B9_97E9_13DEF84A82D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const size_t MAX_SIZE = 4 * 1024; 
// q-p tables
const unsigned char qp_fromhex[] =
{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// 0 - 15
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// 16 - 31
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// 32 - 47
0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// 48 - 63
0xFF, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// 64 - 79
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// 80 - 95
0xFF, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// 96 - 111
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// 112 - 127
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// 128 - 143
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// 144 - 159
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// 160 - 175
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// 176 - 191
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// 192 - 207
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// 208 - 223
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// 224 - 239
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

class CVcardView : public CEditView
{
protected: // create from serialization only
	CVcardView();
	DECLARE_DYNCREATE(CVcardView)

// Attributes
public:
	CVcardDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVcardView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	char* StrTrim(char* cs);  //去除字符串中前后空白
	char* StringReverse(char* string);  //反序字符串
	char* UTFToHex(char* cstr);  //UTF编码成HEX
	bool GetNameAndNumber(char* name, char* mobile_number,  //获取姓名和电话号码
		                 char* home_number, char* line); 
	bool MemSearchVcard(  // 内存搜索VCARD 提取标记之间字符，装载到 vcard_text[]
		                const char* vps,  //起始位置
		                size_t count,  //总长度
		                const char* flag_beg,  //vcard开始标记
						const char* flag_end,  //vcard结束标记
						char* vcard_text,  //内存缓冲
						size_t* offset  //偏移量
						);
	char* MemoryFind(const char* buf, const char* tofind, size_t len);  //内存匹配函数,在buf中找到tofind,返回匹配处指针
	void QpDecode(char* value);  //quoted-printable解码

    //////////////////////////////////////////////////////////////////////////
	///GBK(ANSI)转UTF8时,先将GBK转成UNICODE(宽字符),然后将UNICODE转换
	///成UTF8. 因为多字节和宽字节转换有系统提供的API.
	///   GBK-->UNICODE:MultiByteToWideChar(...);
	///   UNICODE-->UTF8:WideCharToMultiByte(...);  
	///   UTF8转GBK同GB转UTF8类似,都是借助宽字节处理函数...
	//////////////////////////////////////////////////////////////////////////
	void GBToUTF8(char* src, char* dst, int len);
	void UTF8ToGB(char* src, char* dst, int len);
	virtual ~CVcardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVcardView)
	afx_msg void OnExportTxt();
	afx_msg void OnExportVcf();
	afx_msg void OnHelpUse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in vcardView.cpp
inline CVcardDoc* CVcardView::GetDocument()
   { return (CVcardDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCARDVIEW_H__6127D577_757A_42B9_97E9_13DEF84A82D2__INCLUDED_)
