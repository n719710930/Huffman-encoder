
// MFCApplication3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include "zp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//显示编码
    string buf;
	char haveView[256];
	int view=0;
	bool viewflag = false;
	string viewlist;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
   

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 对话框



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication3Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication3Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication3Dlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCApplication3Dlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication3Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication3Dlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication3Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT6, &CMFCApplication3Dlg::OnEnChangeEdit6)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication3Dlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 消息处理程序

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication3Dlg::OnBnClickedButton1()
{
	extern CStringA strFilename;
	CString filter = _T("所有文件(*.*)|*.*||");
	CFileDialog fDlg(TRUE, _TEXT("txt"), NULL, NULL,filter,this);

	// 调用 DoModal() 方法来打开对话框  
	if (fDlg.DoModal() == IDOK)
	{
		// 设置编辑框1的内容为选择文件的路径  
		// GetPathName() --> 返回选定文件的完整路径  
		SetDlgItemText(IDC_EDIT2, fDlg.GetPathName());
		CFile fFile(fDlg.GetPathName(), CFile::modeRead);

		// 因为在Windows下常用的文本保存编码为ANSI  
		// 而本工程在当初选择的时候选择了Unicode环境  
		// 所以需要使用CStringA类型的变量。  

		strFilename = fDlg.GetFileName();
		CStringA strFile;
		// 读取打开文件内容  
		// 第一个参数：读取内容的缓冲区域  
		// 第二个参数：读取内容的长度  
		fFile.Read(strFile.GetBufferSetLength(fFile.GetLength()), fFile.GetLength());

		// 关闭文件句柄  
		fFile.Close();

		// 释放缓冲区域  
		strFile.ReleaseBuffer();

		// 因环境为Unicdoe的原因，CStringA不可以直接显示到界面控件上  
		// 所以使用CString转换为Unicdoe字符  
		SetDlgItemText(IDC_EDIT1, CString(strFile));
	}
	

	// TODO: 在此添加控件通知处理程序代码
}


int appendZero = 0; 
TreeNode * HuffmanRoot;

void CMFCApplication3Dlg::OnBnClickedButton3()
{
	if(strFilename == "0")
	{
		MessageBox(_T("没有选择文件！"));
		return;
	}
	FILE * fin = fopen(strFilename, "rb");
	int c;      //这里c不能定义为unsigned char 否则下面这个循环永远都结束不了，取不了EOF(-1)  
	

	while ((c = fgetc(fin)) != EOF)
	{
		//putchar(c);  
		Ascii[c].alpha = c;
		Ascii[c].value++;
	}

	puts("");

	qsort(Ascii, sizeof(Ascii) / sizeof(Ascii[0]), sizeof(Ascii[0]), Comp);

	/*构造Huffman树*/
	HuffmanRoot = CreateHuffmanTree(Ascii);//ok  

	/*建立字符-Huffman码表,结果存到charHuffmanTable[]*/
	preorder(HuffmanRoot);

	FILE * fout = fopen("huffman.bin", "wb");
	rewind(fin);    //重置文件指针  

	

	while ((c = fgetc(fin)) != EOF)
	{

		int x;
		viewflag = false;
		for(x= 0;x<view;x++){
			if(haveView[x]==c) viewflag = true;
		}

		if(viewflag!=true){
			
			haveView[view] = c;
			view++;
			if(c!=NULL&&c!='\n'&&c!='\r'&&c!='\r\n'){
			viewlist = viewlist+' '+(char)c+ ' '+ charHuffmanTable[c]+ "\r\n";
			}
			else viewlist = viewlist+' '+"\\n"+ ' '+ charHuffmanTable[c]+ "\r\n";
		}
		
		
		buf += charHuffmanTable[c];
		if (buf.length() >= 8)
		{
			fputc(StrToBin(buf.substr(0, 8)), fout);
			buf.erase(0, 8);
		}
	}

	   
	if (!buf.empty())
	{
		appendZero = 8 - buf.length();
		buf.append(appendZero, '0');
		fputc(StrToBin(buf.substr(0, 8)), fout);
		buf.erase(0, 8);
	}

	fclose(fin);
	fclose(fout);

	fin = fopen("huffman.bin", "rb");
	fout = fopen("huffman.out", "wb");

	int uc;

	while ((uc = fgetc(fin)) != EOF) 	{
		buf += BinToStr(uc);  
	}
	/*-----------Debug----------*/

	while (buf.length() - appendZero != 0 && !buf.empty())
	{
		//搜索Huffman树并译码  
		fputc(decode(HuffmanRoot, buf), fout);
		//fputc(decode(HuffmanRoot, buf), fout);  
	}


	fclose(fin);
	fclose(fout);
	
	
	
	CString SMtr;
	SMtr = viewlist.c_str();




	MessageBox(_T("压缩成功"));
	SetDlgItemText(IDC_EDIT5, SMtr);
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnBnClickedButton2()
{


	MessageBox(_T("解压成功！"));
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnBnClickedButton4()
{

	CString filter = _T("文本文件(*.out)|*.out||所有文件(*.*)|*.*||");
	CFileDialog fDlg(TRUE, _TEXT("txt"), NULL, NULL, filter, this);

	// 调用 DoModal() 方法来打开对话框  
	if (fDlg.DoModal() == IDOK)
	{
		// 设置编辑框1的内容为选择文件的路径  
		// GetPathName() --> 返回选定文件的完整路径  
		CFile fFile(fDlg.GetPathName(), CFile::modeRead);

		// 因为在Windows下常用的文本保存编码为ANSI  
		// 而本工程在当初选择的时候选择了Unicode环境  
		// 所以需要使用CStringA类型的变量。  

		strFilename = fDlg.GetFileName();
		CStringA strFile;
		// 读取打开文件内容  
		// 第一个参数：读取内容的缓冲区域  
		// 第二个参数：读取内容的长度  
		fFile.Read(strFile.GetBufferSetLength(fFile.GetLength()), fFile.GetLength());

		// 关闭文件句柄  
		fFile.Close();

		// 释放缓冲区域  
		strFile.ReleaseBuffer();

		// 因环境为Unicdoe的原因，CStringA不可以直接显示到界面控件上  
		// 所以使用CString转换为Unicdoe字符  
		SetDlgItemText(IDC_EDIT4, CString(strFile));

	}
	// TODO: 在此添加控件通知处理程序代码
}

void CMFCApplication3Dlg::OnBnClickedButton5()
{
	CString filter = _T("文本文件(*.bin)|*.bin||所有文件(*.*)|*.*||");
	CFileDialog fDlg(TRUE, _TEXT("txt"), NULL, NULL, filter, this);

	// 调用 DoModal() 方法来打开对话框  
	if (fDlg.DoModal() == IDOK)
	{
		// 设置编辑框1的内容为选择文件的路径  
		// GetPathName() --> 返回选定文件的完整路径  
		CFile fFile(fDlg.GetPathName(), CFile::modeRead);

		// 因为在Windows下常用的文本保存编码为ANSI  
		// 而本工程在当初选择的时候选择了Unicode环境  
		// 所以需要使用CStringA类型的变量。  

		strFilename = fDlg.GetFileName();
		CStringA strFile;
		// 读取打开文件内容  
		// 第一个参数：读取内容的缓冲区域  
		// 第二个参数：读取内容的长度  
		fFile.Read(strFile.GetBufferSetLength(fFile.GetLength()), fFile.GetLength());

		// 关闭文件句柄  
		fFile.Close();

		// 释放缓冲区域  
		strFile.ReleaseBuffer();

		// 因环境为Unicdoe的原因，CStringA不可以直接显示到界面控件上  
		// 所以使用CString转换为Unicdoe字符  
		SetDlgItemText(IDC_EDIT3, CString(strFile));
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。


	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。


	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
}
