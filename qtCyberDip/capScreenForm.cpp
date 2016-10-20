#include "capScreenForm.h"

capScreenForm::capScreenForm(qtCyberDip* win, QWidget *parent)
	: QWidget(parent), shouldRun(false)
{
	ui = new Ui::capScreenForm;
	ui->setupUi(this);
#ifdef VIA_OPENCV
	resize(200, 95);
#endif
	mParentWindow = win;

}

capScreenForm::~capScreenForm()
{
	if (ui)
		delete ui;

	ui = nullptr;
}


void capScreenForm::closeEvent(QCloseEvent *evt)
{
#ifdef VIA_OPENCV
	mParentWindow->closeCV();
#endif
	shouldRun = false;
	QWidget::closeEvent(evt);
	mParentWindow->show();
}

void capScreenForm::capSetHWND(HWND wnd)
{
	hWnd = wnd;
	this->setWindowTitle("Capture 0x" + QString::number((uint)hWnd, 16));
}

void capScreenForm::capStart()
{
	shouldRun = true;
	while (true)
	{
	
		if (!isVisible() || !ui || !shouldRun){ qDebug() << QString::number((uint)hWnd, 16) + " is not visible. "; break; }

		::HDC hdc = ::GetWindowDC(hWnd);
		::LPRECT wRect = new ::RECT();
		if (!::GetWindowRect(hWnd, wRect)){ break; }
		qDebug() << "Windows Info:\n Left:" << wRect->left << " Right:" << wRect->right << " Top:" << wRect->top << " Bottom" << wRect->bottom;
		int width = wRect->right - wRect->left;
		int height = wRect->bottom - wRect->top;
		::HDC hdcDst = ::CreateCompatibleDC(hdc);
		::HBITMAP bmpDst= ::CreateCompatibleBitmap(hdc, width, height);
		::HGDIOBJ bmpHDst = ::SelectObject(hdcDst, bmpDst);
		bool isSame = true, isAlive = true;
		while (!(!isVisible() || !ui || !shouldRun) && isSame && isAlive)
		{
			isAlive = ::GetWindowRect(hWnd, wRect);
			int nW = wRect->right - wRect->left;
			int nH = wRect->bottom - wRect->top;
			isSame = (nW == width) && (nH == height);
		
			BitBlt(hdcDst, 0, 0, width, height, hdc, 0, 0, SRCCOPY);

			QImage img = qt_imageFromWinHBITMAP(hdcDst, bmpDst, width, height);
#ifndef VIA_OPENCV
			ui->capDisplay->setImage(img);
			
#endif
			qApp->processEvents();
			emit imgReady(img);
		}
		::DeleteDC(hdcDst);
		::ReleaseDC(hWnd, hdc);
		::DeleteObject(bmpDst);
		//����Ǵ��ڹر�/�����۵����µļǵ�ɾȥ�Ǹ�����
		if (!isAlive || wRect->right < wRect->left || wRect->top > wRect->bottom)
		{
			qDebug() << QString::number((uint)hWnd, 16) + " Disappeared.";
			shouldRun = false;
		}
		//��������ǳߴ粻ͬ���ҷ��Ϲ淶������
		else if (!isSame&&isAlive&&shouldRun)
		{
			continue;
		}
		break;//����ѭ��
	}
		close();
}