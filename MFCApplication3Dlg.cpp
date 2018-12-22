
// MFCApplication3Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include "zp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//��ʾ����
    string buf;
	char haveView[256];
	int view=0;
	bool viewflag = false;
	string viewlist;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
   

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCApplication3Dlg �Ի���



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


// CMFCApplication3Dlg ��Ϣ�������

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication3Dlg::OnBnClickedButton1()
{
	extern CStringA strFilename;
	CString filter = _T("�����ļ�(*.*)|*.*||");
	CFileDialog fDlg(TRUE, _TEXT("txt"), NULL, NULL,filter,this);

	// ���� DoModal() �������򿪶Ի���  
	if (fDlg.DoModal() == IDOK)
	{
		// ���ñ༭��1������Ϊѡ���ļ���·��  
		// GetPathName() --> ����ѡ���ļ�������·��  
		SetDlgItemText(IDC_EDIT2, fDlg.GetPathName());
		CFile fFile(fDlg.GetPathName(), CFile::modeRead);

		// ��Ϊ��Windows�³��õ��ı��������ΪANSI  
		// ���������ڵ���ѡ���ʱ��ѡ����Unicode����  
		// ������Ҫʹ��CStringA���͵ı�����  

		strFilename = fDlg.GetFileName();
		CStringA strFile;
		// ��ȡ���ļ�����  
		// ��һ����������ȡ���ݵĻ�������  
		// �ڶ�����������ȡ���ݵĳ���  
		fFile.Read(strFile.GetBufferSetLength(fFile.GetLength()), fFile.GetLength());

		// �ر��ļ����  
		fFile.Close();

		// �ͷŻ�������  
		strFile.ReleaseBuffer();

		// �򻷾�ΪUnicdoe��ԭ��CStringA������ֱ����ʾ������ؼ���  
		// ����ʹ��CStringת��ΪUnicdoe�ַ�  
		SetDlgItemText(IDC_EDIT1, CString(strFile));
	}
	

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


int appendZero = 0; 
TreeNode * HuffmanRoot;

void CMFCApplication3Dlg::OnBnClickedButton3()
{
	if(strFilename == "0")
	{
		MessageBox(_T("û��ѡ���ļ���"));
		return;
	}
	FILE * fin = fopen(strFilename, "rb");
	int c;      //����c���ܶ���Ϊunsigned char �����������ѭ����Զ���������ˣ�ȡ����EOF(-1)  
	

	while ((c = fgetc(fin)) != EOF)
	{
		//putchar(c);  
		Ascii[c].alpha = c;
		Ascii[c].value++;
	}

	puts("");

	qsort(Ascii, sizeof(Ascii) / sizeof(Ascii[0]), sizeof(Ascii[0]), Comp);

	/*����Huffman��*/
	HuffmanRoot = CreateHuffmanTree(Ascii);//ok  

	/*�����ַ�-Huffman���,����浽charHuffmanTable[]*/
	preorder(HuffmanRoot);

	FILE * fout = fopen("huffman.bin", "wb");
	rewind(fin);    //�����ļ�ָ��  

	

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
		//����Huffman��������  
		fputc(decode(HuffmanRoot, buf), fout);
		//fputc(decode(HuffmanRoot, buf), fout);  
	}


	fclose(fin);
	fclose(fout);
	
	
	
	CString SMtr;
	SMtr = viewlist.c_str();




	MessageBox(_T("ѹ���ɹ�"));
	SetDlgItemText(IDC_EDIT5, SMtr);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication3Dlg::OnBnClickedButton2()
{


	MessageBox(_T("��ѹ�ɹ���"));
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication3Dlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication3Dlg::OnBnClickedButton4()
{

	CString filter = _T("�ı��ļ�(*.out)|*.out||�����ļ�(*.*)|*.*||");
	CFileDialog fDlg(TRUE, _TEXT("txt"), NULL, NULL, filter, this);

	// ���� DoModal() �������򿪶Ի���  
	if (fDlg.DoModal() == IDOK)
	{
		// ���ñ༭��1������Ϊѡ���ļ���·��  
		// GetPathName() --> ����ѡ���ļ�������·��  
		CFile fFile(fDlg.GetPathName(), CFile::modeRead);

		// ��Ϊ��Windows�³��õ��ı��������ΪANSI  
		// ���������ڵ���ѡ���ʱ��ѡ����Unicode����  
		// ������Ҫʹ��CStringA���͵ı�����  

		strFilename = fDlg.GetFileName();
		CStringA strFile;
		// ��ȡ���ļ�����  
		// ��һ����������ȡ���ݵĻ�������  
		// �ڶ�����������ȡ���ݵĳ���  
		fFile.Read(strFile.GetBufferSetLength(fFile.GetLength()), fFile.GetLength());

		// �ر��ļ����  
		fFile.Close();

		// �ͷŻ�������  
		strFile.ReleaseBuffer();

		// �򻷾�ΪUnicdoe��ԭ��CStringA������ֱ����ʾ������ؼ���  
		// ����ʹ��CStringת��ΪUnicdoe�ַ�  
		SetDlgItemText(IDC_EDIT4, CString(strFile));

	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CMFCApplication3Dlg::OnBnClickedButton5()
{
	CString filter = _T("�ı��ļ�(*.bin)|*.bin||�����ļ�(*.*)|*.*||");
	CFileDialog fDlg(TRUE, _TEXT("txt"), NULL, NULL, filter, this);

	// ���� DoModal() �������򿪶Ի���  
	if (fDlg.DoModal() == IDOK)
	{
		// ���ñ༭��1������Ϊѡ���ļ���·��  
		// GetPathName() --> ����ѡ���ļ�������·��  
		CFile fFile(fDlg.GetPathName(), CFile::modeRead);

		// ��Ϊ��Windows�³��õ��ı��������ΪANSI  
		// ���������ڵ���ѡ���ʱ��ѡ����Unicode����  
		// ������Ҫʹ��CStringA���͵ı�����  

		strFilename = fDlg.GetFileName();
		CStringA strFile;
		// ��ȡ���ļ�����  
		// ��һ����������ȡ���ݵĻ�������  
		// �ڶ�����������ȡ���ݵĳ���  
		fFile.Read(strFile.GetBufferSetLength(fFile.GetLength()), fFile.GetLength());

		// �ر��ļ����  
		fFile.Close();

		// �ͷŻ�������  
		strFile.ReleaseBuffer();

		// �򻷾�ΪUnicdoe��ԭ��CStringA������ֱ����ʾ������ؼ���  
		// ����ʹ��CStringת��ΪUnicdoe�ַ�  
		SetDlgItemText(IDC_EDIT3, CString(strFile));
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication3Dlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�


	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication3Dlg::OnEnChangeEdit6()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�


	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication3Dlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
