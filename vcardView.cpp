// vcardView.cpp : implementation of the CVcardView class
//

#include "stdafx.h"
#include <string>
#include "vcard.h"
#include "vcardDoc.h"
#include "vcardView.h"
//using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVcardView

IMPLEMENT_DYNCREATE(CVcardView, CEditView)

BEGIN_MESSAGE_MAP(CVcardView, CEditView)
	//{{AFX_MSG_MAP(CVcardView)
	ON_COMMAND(ID_EXPORT_TXT, OnExportTxt)
	ON_COMMAND(ID_EXPORT_VCF, OnExportVcf)
	ON_COMMAND(ID_HELP_USE, OnHelpUse)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVcardView construction/destruction

CVcardView::CVcardView()
{
	// TODO: add construction code here

}

CVcardView::~CVcardView()
{
}

BOOL CVcardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CVcardView drawing

void CVcardView::OnDraw(CDC* pDC)
{
	CVcardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CVcardView printing

BOOL CVcardView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CVcardView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CVcardView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CVcardView diagnostics

#ifdef _DEBUG
void CVcardView::AssertValid() const
{
	CEditView::AssertValid();
}

void CVcardView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CVcardDoc* CVcardView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVcardDoc)));
	return (CVcardDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVcardView message handlers

void CVcardView::OnExportTxt() 
{
	// TODO: Add your command handler code here

    CVcardDoc* pDoc = GetDocument();  //获取文档对象指针,通过该指针来访问文档类的成员
	CString file_name = pDoc->file_path;  //获取文件名
	CStdioFile vcf_file;

	//以文本模式打开txt文件,默认是以二进制模式打开
	//以二进制打开读取时换行是0D 0A两个字符
	//此时程序中的换行和文本中比较会出现问题,程序中的是0A
	//设置读取模式只能是CFile的派生类(CStdioFile)使用
    //要不然设置成文本模式程序会崩溃
    if (vcf_file.Open(file_name, CStdioFile::modeRead|CStdioFile::typeText) == 0)  
 	{
 		AfxMessageBox("打开文件失败.");
		return;
 	}
     
	////////////////////////////vcf固定格式///////////////////////////////////
	const char* vcard_head = "BEGIN:VCARD\n";
    const char* vcard_end = "END:VCARD\n";
	
    const char* f_name_title = "FN;CHARSET=UTF-8;ENCODING=QUOTED-PRINTABLE:";
    const char*  mobile_number_title = "TEL;CELL:";
    const char*  home_number_title = "TEL;HOME:";
   //////////////////////////////////////////////////////////////////////////

    char name[512] = "";
    char mobile_number[64] = "";
    char home_number[64] = ""; // 可以存移动短号

	// 读取文件到内存
    size_t file_size = vcf_file.GetLength();  //获取文件大小
	char* inbuf = new char[file_size + 1];
	vcf_file.Read(inbuf, file_size);

    char* vcard_text = new char[8 * 1024];
    memset(vcard_text, 0, 8 * 1024);
    size_t offset = 0;
	
    const char* vps = inbuf;
    size_t count = file_size;
	// 判断是否是vcf文件,如果是则将记录写入vcard_text
    bool is_vcard = MemSearchVcard(vps, count, vcard_head, vcard_end,  vcard_text, &offset);
    if (!is_vcard)  //不是vcf文件
	{
		AfxMessageBox("文件格式错误,不是vcf格式");
		return;
	}
	
	CFileDialog vcard_dlg(FALSE, "txt", file_name);
	vcard_dlg.m_ofn.lpstrFilter = "txt files(*.txt)|*.txt||";
	vcard_dlg.m_ofn.lpstrTitle = "导出成txt文件";
	if (vcard_dlg.DoModal() == IDOK)
	{
		CFile txt_file;
		if (txt_file.Open(vcard_dlg.GetFileName(), CFile::modeWrite|CFile::modeCreate) == 0)
		{
			AfxMessageBox("转换失败");
			return;
		}
		CString title = "姓名\t移动电话\t家庭电话\n";
		txt_file.Write(title, title.GetLength());
        while (is_vcard)
		{
			const char* ps = vcard_text;
			const char* ps2 = vcard_text;
			size_t len = strlen(vcard_text);
			
			ps = MemoryFind(vcard_text, f_name_title, len);		
			if (ps != NULL)
			{
				// 搜索解码姓名
				ps2 = MemoryFind(ps, "\n", len - (ps - vcard_text));
				std::string str(ps + strlen(f_name_title), ps2);
				strcpy(name, str.c_str());
				QpDecode(name);
				UTF8ToGB(name, name, strlen(name));
				txt_file.Write(name, strlen(name));  //姓名写入文件
				txt_file.Write("\t", 1);
				
				// 获得电话号码
				ps = MemoryFind(vcard_text, mobile_number_title, len);
				if (ps != NULL)
				{
					ps2 = MemoryFind(ps, "\n", len - (ps - vcard_text));
					std::string str(ps + strlen(mobile_number_title), ps2);
					strcpy(mobile_number, str.c_str());
					txt_file.Write(mobile_number, strlen(mobile_number));
					txt_file.Write("\t", 1);
				}
				
				// 获得家庭电话
				ps = MemoryFind(vcard_text, home_number_title, len);
				if (ps != NULL)
				{
					ps2 = MemoryFind(ps, "\n", len - (ps - vcard_text));
					std::string str(ps + strlen(home_number_title), ps2);
					strcpy(home_number, str.c_str());
					txt_file.Write(home_number, strlen(home_number));
				}
				txt_file.Write("\n", 1);
			}
			
			// 移动到下一个 搜索区间
			count = file_size - offset;
			vps = inbuf + offset;
			is_vcard = MemSearchVcard(vps, count, vcard_head, vcard_end,  vcard_text, &offset);
		}
		
		// 释放内存和关闭文件
		delete[]  vcard_text;
		delete[]  inbuf;
        txt_file.Close();
		vcf_file.Close();
		AfxMessageBox("转换成功");
	}    
}

void CVcardView::UTF8ToGB(char *src, char *dst, int len)
{
    int ret = 0;
    WCHAR* strA;
	//获取接收待转换字符串需要的宽字符数
    int i = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
    if (i <= 0) {
        return;
    }
    strA = (WCHAR*)malloc(i * 2); //缓冲区大小
    MultiByteToWideChar(CP_UTF8, 0, src, -1, strA, i);  //UTF8转UNICODE
    i = WideCharToMultiByte(CP_ACP, 0, strA, -1, NULL, 0, NULL, NULL);  //获取转换所需字节数 
    if (len >= i) {
        ret = WideCharToMultiByte(CP_ACP, 0, strA, -1, dst, i, NULL, NULL);  //UNICODE转GBK(ANSI)
        dst[i] = 0;
    }
    if (ret <= 0) {
        free(strA);
        return;
    }
	
    free(strA);
}

void CVcardView::GBToUTF8(char *src, char *dst, int len)
{
    int ret = 0;
    WCHAR* strA;
    //获取接收待转换字符串需要的宽字符数
    int i = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0);
    if (i <= 0)
	{
        return;
    }
    strA = (WCHAR*)malloc(i * 2);  //缓冲区大小
    MultiByteToWideChar(CP_ACP, 0, src, -1, strA, i);  //GBK(ANSI)转UNICODE
    i = WideCharToMultiByte(CP_UTF8, 0, strA, -1, NULL, 0, NULL, NULL);  //获取转换所需字节数 
    if (len >= i)
	{
		memset(dst, 0, 512);
        ret = WideCharToMultiByte(CP_UTF8, 0, strA, -1, dst, i, NULL, NULL);  //UNICODE转UTF8
        dst[i] = 0;
    }
	
    if (ret <= 0)
	{
        free(strA);
        return;
    }
    free(strA);
}

void CVcardView::QpDecode(char *value)
{
	unsigned char* p = reinterpret_cast<unsigned char*>(value);
	unsigned char* q = p;
	while(*p)
	{
		// Look for q-p character
		switch(*p)
		{
		case '=':
			// Look for valid q-p encoded character
			if (p[1] && p[2])
			{
				unsigned char d1 = qp_fromhex[p[1]];
				unsigned char d2 = qp_fromhex[p[2]];
				
				if ((d1 != 0xFF) && (d2 != 0xFF))
				{
					*q++ = (d1 << 4) | d2;
					p += 3;
				}
				else
					*q++ = *p++;
			}
			else
				*q++ = *p++;
			break;
		default:
			*q++ = *p++;
			break;
		}
	}
	
	// Terminate
	*q = 0;
}

char* CVcardView::MemoryFind(const char *buf, const char *tofind, size_t len)
{
    size_t findlen = strlen(tofind);
    if (findlen > len)
	{
        return ((char*)NULL);
    }
    if (len < 1)
	{
        return ((char*)buf);
    }
	
    {
        const char* bufend = &buf[len - findlen + 1];  //循环次数d
        const char* c = buf;
        for (; c < bufend; c++)
		{
            if (*c == *tofind)  // first letter matches
			{
				if (!memcmp(c, tofind, findlen))  //内存比较,在buf中找到tofind,不比较换行字符
				{
                    return ((char*)c);
                } 
            }
        }
    }
	
    return ((char*)NULL);
}

bool CVcardView::MemSearchVcard(const char *vps, size_t count, 
								const char *flag_beg, const char *flag_end,
								char *vcard_text, size_t *offset)
{
    char* pch = NULL;
    char* pch2 = NULL;
    pch = MemoryFind(vps, flag_beg, count);  //VCARD开始标记
    if (pch == NULL)
	{
        //   printf("警告: 内存缓冲区找不到 flag_beg\n");
        return false;
    }
    if (pch != NULL) 
	{
        pch2 = MemoryFind(vps, flag_end, count);  //VCARD结束标记
        if (pch2 == NULL)
            return false;
		std::string str(pch, pch2 + strlen(flag_end));  //一个VCARD记录
        strcpy(vcard_text, str.c_str());
        *offset += pch2 - vps + strlen(flag_end); // 记录搜索结果的结尾偏移
    }

    return true;
}

void CVcardView::OnExportVcf() 
{
	// TODO: Add your command handler code here
	CVcardDoc* pDoc = GetDocument();  //获取文档对象指针,通过该指针来访问文档类的成员
	CString file_name = pDoc->file_path;  //获取文件名
	CStdioFile txt_file;
	
	
	//以文本模式打开txt文件,默认是以二进制模式打开
	//以二进制打开读取时换行是0D 0A两个字符
	//此时程序中的换行和文本中比较会出现问题,程序中的是0A
	//设置读取模式只能是CFile的派生类(CStdioFile)使用
    //要不然设置成文本模式程序会崩溃
    if (txt_file.Open(file_name, CStdioFile::modeRead|CStdioFile::typeText) == 0)  
	{
		AfxMessageBox("打开文件失败");
		return;
 	}
	////////////////////////////vcf文件固定格式//////////////////////////////
	const char* vcard_head = "BEGIN:VCARD\nVERSION:2.1\n";
    const char* vcard_end = "END:VCARD\n";
	
    const char* name_title = "N;CHARSET=UTF-8;ENCODING=QUOTED-PRINTABLE:;";
    const char* end_name = ";;;";
	
    const char* f_name_title = "FN;CHARSET=UTF-8;ENCODING=QUOTED-PRINTABLE:";
	
    const char*  mobile_number_title = "TEL;CELL:";
    const char*  home_number_title = "TEL;HOME:";
	//////////////////////////////////////////////////////////////////////////

	char name[512] = {"\0"};  //姓名
    char mobile_number[64] = {"\0"};  //移动电话
    char home_number[64] = {"\0"};  //可以存移动短号
	
    char* vcard_text =  new char[MAX_SIZE];  // 一个vcard文本
    char* line =  new char[MAX_SIZE];  //文本中一行
	memset(line, 0, MAX_SIZE);

	CFileDialog vcard_dlg(FALSE, "vcf", file_name);
	vcard_dlg.m_ofn.lpstrFilter = "vcf files(*.vcf)|*.vcf||";
	vcard_dlg.m_ofn.lpstrTitle = "导出成vcf文件";
	if (vcard_dlg.DoModal() == IDOK)
	{
		CFile vcf_file;
		if (vcf_file.Open(vcard_dlg.GetFileName(), CFile::modeWrite|CFile::modeCreate) == 0)
		{
			AfxMessageBox("转换失败");
			return;
		}
       	while (txt_file.ReadString(line, MAX_SIZE))  //读取文件每一行
		{
			if (strlen(line) < 10)  continue;
			if (!GetNameAndNumber(name, mobile_number, home_number, line))  continue;
			//把name转换成utf-8,然后使用=EE=FF=EE取16进制进行编码
			GBToUTF8(name, name, strlen(name) * 3 / 2 + 1);
			UTFToHex(name);
			// 组成 一个vcard文本
			sprintf(vcard_text, "%s%s%s%s\n%s%s\n%s%s\n%s%s\n%s", vcard_head,
				name_title, name, end_name,
				f_name_title, name,
				mobile_number_title, mobile_number,
				home_number_title, home_number,
				vcard_end);
			vcf_file.Write(vcard_text, strlen(vcard_text));  //转换后的记录写入文件
		}

		delete[] line;
		delete[] vcard_text;
        txt_file.Close();
		vcf_file.Close();
        AfxMessageBox("转换成功");
	}
}

bool CVcardView::GetNameAndNumber(char* name, char* mobile_number, char* home_number, char* line)
{
    char flag[] = "#;/"  ;  // 注释
    if ((line[0] == flag[0]) || (line[0] == flag[1]) || (line[0] == flag[2]))
        return false;
	
    // 清零
    name[0] = '\0' ;
    mobile_number[0] = '\0' ;
    home_number[0] = '\0' ;
	
    char* pch;
    char*   delimiters = ",;\t\n\"\'";
    pch = strtok(line, delimiters);
    if (pch != NULL) {
        sprintf(name, "%s", pch);
        pch = strtok(NULL, delimiters);
        if (pch != NULL) {
            sprintf(mobile_number, "%s", pch);
            pch = strtok(NULL, delimiters);
            if (pch != NULL)
                sprintf(home_number, "%s", pch);
        }
    }
	
    // 删除前后空格
    StrTrim(name);
    StrTrim(mobile_number);
    StrTrim(home_number);
	
    return true;
}

char* CVcardView::UTFToHex(char *cstr)
{
	unsigned char* pch = (unsigned char*)cstr;
    char byte_str[4] = {"\0"};
    char tmp[MAX_SIZE] = {"\0"};
	size_t len = strlen(cstr);
    for (size_t i = 0; i != len; i++)
	{
        sprintf(byte_str, "=%0.2X", *pch++);
        strcat(tmp, byte_str);
    }
	
    strcpy(cstr, tmp);
    return cstr;
}

char* CVcardView::StringReverse(char *string)
{
   if (string == NULL)  return NULL;
   char *left = string;
   char *right = string;
   char ch;
   while (*right++)   //循环介绍指向了字符串最后字符的后一个字符
	   ;
   right -= 2;  //指向字符串最后一个字符--非null结束字符
   while (left < right)
   {
	   ch = *left;  //临时交换变量
	   *left++ = *right;
	   *right-- = ch;
   }
   return string;
}

char* CVcardView::StrTrim(char *cs)
{
    char* ret = cs;
    char* pc = new char[strlen(cs) + 1];
	
    int pos = strspn(cs, "\t \n");      // 查找非空白处pos
    strcpy(pc, cs + pos);
    StringReverse(pc); // 反序字符串
    pos = strspn(pc, "\t \n");  // 原来后面的空白,就变成了前面的空白
    strcpy(cs, pc + pos);
    StringReverse(cs);  // 再反序,还原回来
	
    delete[] pc;
    return ret;
}

void CVcardView::OnHelpUse() 
{
	// TODO: Add your command handler code here
	ShellExecute(NULL, "open", "..\\帮助\\vcard工具使用说明.pdf", "", "", SW_SHOWNORMAL);
}
