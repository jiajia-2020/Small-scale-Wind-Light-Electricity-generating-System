#include "DIALOG.h"
#include "ButtonUse.h"
#include "led.h"
#include "beep.h"
#include "adc.h"
#include "includes.h"
#include "adc3.h"
#include "lsens.h"
#include "gizwits_protocol.h"
#include "gizwits_product.h"


#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_BUTTON_0 (GUI_ID_USER + 0x01)
#define ID_BUTTON_1 (GUI_ID_USER + 0x02)
#define ID_BUTTON_2 (GUI_ID_USER + 0x03)
#define ID_BUTTON_3 (GUI_ID_USER + 0x04)
#define ID_TEXT_0 (GUI_ID_USER + 0x05)
#define ID_GRAPH_0 (GUI_ID_USER + 0x06)
#define ID_TEXT_1 (GUI_ID_USER + 0x07)
#define ID_TEXT_2 (GUI_ID_USER + 0x08)
#define ID_PROGBAR_0  (GUI_ID_USER + 0x09)
#define ID_SLIDER_0   (GUI_ID_USER + 0x0A)
#define ID_TEXT_3 (GUI_ID_USER + 0x0B)
#define ID_TEXT_4 (GUI_ID_USER + 0x0C)
#define ID_TEXT_5 (GUI_ID_USER + 0x0D)
#define ID_CHECK_0 (GUI_ID_USER + 0x0E)
#define ID_LISTWHEEL_0 (GUI_ID_USER + 0x0F)
#define ID_LISTWHEEL_1 (GUI_ID_USER + 0x10)
#define ID_LISTWHEEL_2 (GUI_ID_USER + 0x11)
#define  ID_DROPDOWN_0 (GUI_ID_USER + 0x12)
#define  ID_DROPDOWN_1 (GUI_ID_USER + 0x13)
#define ID_RADIO_0 (GUI_ID_USER + 0x14)
#define ID_TEXT_6 (GUI_ID_USER + 0x15)
#define ID_TEXT_7 (GUI_ID_USER + 0x16)
#define ID_TEXT_8 (GUI_ID_USER + 0x17)
#define ID_TEXT_9 (GUI_ID_USER + 0x18)
#define  ID_DROPDOWN_2 (GUI_ID_USER + 0x19)
#define ID_RADIO_1 (GUI_ID_USER + 0x1A)

static GRAPH_SCALE_Handle hScaleV; //垂直刻度句柄
static GRAPH_SCALE_Handle _hScaleH; /* 水平刻度句柄 */
static GRAPH_DATA_Handle ahData;
static short temp; //
/*static const char* _apLabel[]={
	"WIFI Control allow",
	"3 States",
	"Box XL",
	"Box XXL"
};*/

static int Count = 0;
u8 adcx;
static u8 wifi_allow=0;
dataPoint_t currentDataPoint;

GUI_BITMAP buttonbmp_tab[2];


WM_HWIN CreateFramewin1(void); 
WM_HWIN CreateFramewin2(void);
WM_HWIN CreateFramewin3(void);
WM_HWIN CreateFramewin4(void);

	WM_HWIN hWin1;

/*
*********************************************************************************************************
*	函 数 名: _cbButton
*	功能说明: 按钮回调函数
*	形    参: pMsg  消息指针
*	返 回 值: 无
*********************************************************************************************************
*/
static void _cbButton1(WM_MESSAGE * pMsg) 
{
	WM_HWIN  hWin;

	hWin  = pMsg->hWin;
	switch (pMsg->MsgId) 
	{
		case WM_PAINT:
			if (BUTTON_IsPressed(hWin)) 
			{
				GUI_SetBkColor(GUI_WHITE);
				GUI_Clear();
				GUI_SetAlpha(0xb0);
			 	GUI_DrawBitmap(&bmpic1, 8, 8);
				GUI_SetAlpha(0);		
			} 
			else 
			{
				GUI_DrawBitmap(&bmpic1, 8, 8);		
			}
			break;
			
		default:
			BUTTON_Callback(pMsg);
	}
}

static void _cbButton2(WM_MESSAGE * pMsg) 
{
	WM_HWIN  hWin;

	hWin  = pMsg->hWin;
	switch (pMsg->MsgId) 
	{
		case WM_PAINT:
			if (BUTTON_IsPressed(hWin)) 
			{
				GUI_SetBkColor(GUI_WHITE);
				GUI_Clear();
				GUI_SetAlpha(0xb0);
			 	GUI_DrawBitmap(&bm2, 8, 8); 
				GUI_SetAlpha(0);		
			} 
			else 
			{
				GUI_DrawBitmap(&bm2, 8, 8);		
			}
			break;
			
		default:
			BUTTON_Callback(pMsg);
	}
}

static void _cbButton3(WM_MESSAGE * pMsg) 
{
	WM_HWIN  hWin;

	hWin  = pMsg->hWin;
	switch (pMsg->MsgId) 
	{
		case WM_PAINT:
			if (BUTTON_IsPressed(hWin)) 
			{
				GUI_SetBkColor(GUI_WHITE);
				GUI_Clear();
				GUI_SetAlpha(0xb0);
			 	GUI_DrawBitmap(&bm3, 8, 8); 
				GUI_SetAlpha(0);		
			} 
			else 
			{
				GUI_DrawBitmap(&bm3, 8, 8);		
			}
			break;
			
		default:
			BUTTON_Callback(pMsg);
	}
}


//对话框资源表
static const GUI_WIDGET_CREATE_INFO _aDialogCreate1[] = 
{
	{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x64, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 100, 150, 110, 80, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 325, 150, 110, 80, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 550, 150, 110, 80, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_0, 87, 240, 120, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_1, 312, 240, 120, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_2, 532, 240, 120, 20, 0, 0x64, 0 }
};

//对话框回调函数
static void _cbDialog1(WM_MESSAGE * pMsg) 
{
	WM_HWIN hItem;
	int     NCode;
	int     Id;
	
	switch (pMsg->MsgId) 
	{
			case WM_PAINT:
		 // GUI_DrawBitmap(&bm1,0,0);
				GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			
			break;
				
		case WM_INIT_DIALOG:
			//初始化对话框
			hItem = pMsg->hWin;
			FRAMEWIN_SetTitleHeight(hItem, 30);
		FRAMEWIN_SetText(hItem, "ShanDong University");
			FRAMEWIN_SetFont(hItem, GUI_FONT_24_ASCII);
			FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			FRAMEWIN_SetTextColor(hItem, 0x0000FFFF);
		
			//初始化BUTTON0
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			/*BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
			BUTTON_SetText(hItem, "Temperature");*/
				WM_SetHasTrans(hItem);
			WM_SetCallback(hItem, _cbButton1);
			
			//初始化BUTTON1
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
	/*	BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
			BUTTON_SetText(hItem, "Illumination");*/
			WM_SetHasTrans(hItem);
			WM_SetCallback(hItem, _cbButton3);
		
				//初始化BUTTON2
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
			/*BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
			BUTTON_SetText(hItem, "LED Control");*/
			WM_SetHasTrans(hItem);
			WM_SetCallback(hItem, _cbButton2);
			
								hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
			TEXT_SetText(hItem, "Temperature");
									hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
			TEXT_SetText(hItem, "illumination");
									hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
			TEXT_SetText(hItem, "LED Control");
				
			break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id) 
			{
				case ID_BUTTON_0: //BUTTON_0的通知代码，控制LED1
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED: //按钮被按下并释放
          GUI_EndDialog(pMsg->hWin, 0);
							CreateFramewin2();
							break;	
					}
					break;
				case ID_BUTTON_1: //BUTTON_1的通知代码，控制BEEP
							hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED:
								GUI_EndDialog(pMsg->hWin, 0);
							CreateFramewin4();
					
					
							break;
					}
					break;
					case ID_BUTTON_2: //BUTTON_0的通知代码，控制LED1
							hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED: //按钮被按下并释放
							GUI_EndDialog(pMsg->hWin, 0);
							CreateFramewin3();
							break;	
					}
					break;
			}
			break;
		default:
			WM_DefaultProc(pMsg);
			break;
	}
}

//创建一个对话框
WM_HWIN CreateFramewin1(void) 
{

		buttonbmp_tab[0]=bmBUTTONOFF;
	buttonbmp_tab[1]=bmBUTTONON;

	hWin1 = GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
	return hWin1;
}





static const GUI_WIDGET_CREATE_INFO _aDialogCreate2[] = 
{
	{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x64, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 195, 310, 110, 40, 0, 0x0, 0 },
	/*{ BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 580, 130, 177, 52, 0, 0x0, 0 },*/
	{ GRAPH_CreateIndirect, "Graph", ID_GRAPH_0, 377, 207, 400, 240, 0, 0x0, 0 },
	{ TEXT_CreateIndirect,      "Temperature:00",    ID_TEXT_0,    425,175,300,48, 0,0},
		/*{ TEXT_CreateIndirect, "Text", ID_TEXT_1, 30, 10, 180, 20, 0, 0x64, 0 },*/
		{ TEXT_CreateIndirect, "CPU:", ID_TEXT_2, 685, 3, 100, 20, 0, 0 },
		{ TEXT_CreateIndirect, "Water Level :", ID_TEXT_3, 450, 83, 300, 48, 0, 0x64, 0 },
			/*{ TEXT_CreateIndirect, "Text", ID_TEXT_4, 30, 230, 180, 20, 0, 0x64, 0 },
			{ TEXT_CreateIndirect, "Text", ID_TEXT_5, 30, 300, 180, 20, 0, 0x64, 0 }*/
		{ PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_0, 490, 130, 175, 35, 0, 0x0, 0 },
		{ CHECKBOX_CreateIndirect, "WIFI Control allow", ID_CHECK_0,610,  43, 150,20,0,0x0,0 },
	{ DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_0,160,30, 130,30,0,0x0,0 },
	{ TEXT_CreateIndirect,      "Start time:",    ID_TEXT_4,    30,30,120,30, 0,0},
	{ TEXT_CreateIndirect,      "Block using number:",    ID_TEXT_5,    30,70,220,30, 0,0},
	{ DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_1,260,72, 130,30,0,0x0,0 },
	{ RADIO_CreateIndirect, "Radio", ID_RADIO_0, 193, 125, 120, 75, 0, 0x1903, 0 },
	{ TEXT_CreateIndirect,      "Heating mode:",    ID_TEXT_6,  30,120,150,30, 0,0},
	{ TEXT_CreateIndirect,      "Target Temperature:80",    ID_TEXT_7,  30,215,250,30, 0,0},
	{ TEXT_CreateIndirect,      "Water Infusing:",    ID_TEXT_8,  30,260,180,30, 0,0},
	{ RADIO_CreateIndirect, "Radio", ID_RADIO_1, 45, 310, 120, 75, 0, 0x1903, 0 },
};



static void _UserDraw(WM_HWIN hWin, int Stage)
{
 /* 在绘制之后被调用 */
if (Stage == GRAPH_DRAW_LAST) {
 char acText[] = "Temperature";
 GUI_RECT Rect;
 GUI_RECT RectInvalid;
 int FontSizeY;
 /* 设置字体 */
 GUI_SetFont(&GUI_Font13_ASCII);
FontSizeY = GUI_GetFontSizeY();
/* 获得图形控件区域坐标 */
 WM_GetInsideRect(&Rect);
 WM_GetInvalidRect(hWin, &RectInvalid);
 Rect.x1 = Rect.x0 + FontSizeY;
GUI_SetColor(GUI_YELLOW);
/* 根据获取的图形控件坐标和字体的高度，将字母 Temperature 显示出来 */
 GUI_DispStringInRectEx(acText, &Rect, GUI_TA_HCENTER, strlen(acText), GUI_ROTATE_CCW);
 } }

 
 
 
static void _cbDialog2(WM_MESSAGE * pMsg) 
{
	WM_HWIN hItem;
	int     NCode;
	int     Id;
	 WM_HWIN hWin = pMsg->hWin;
char buf[10];
	char buf2[10];
	unsigned char waterlevel;
	static u8 waterflag=0;
		waterlevel=82;
	switch (pMsg->MsgId) 
	{
		
				case WM_PAINT:
		 // GUI_DrawBitmap(&bm1,0,0);
				GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			
			break;
				
				
		case WM_INIT_DIALOG:
			//
			// 初始化框架窗口
			//
			hItem = pMsg->hWin;
			FRAMEWIN_SetTitleHeight(hItem, 30);
			FRAMEWIN_SetText(hItem, "Electrical Heating Device");
			FRAMEWIN_SetFont(hItem, GUI_FONT_24_ASCII);
			FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			FRAMEWIN_SetTextColor(hItem, 0x0000FFFF);
		
			//
			// 初始按钮控件
			//
			/*hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetFont(hItem, GUI_FONT_20_1);
			BUTTON_SetText(hItem, "Back");
		
			//
			// 初始化按钮控件
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
			BUTTON_SetFont(hItem, GUI_FONT_20_1);
			BUTTON_SetText(hItem, "LED Control");*/
			
			
					hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
		ahData = GRAPH_DATA_YT_Create(GUI_GREEN, 400, 0, 0);
		GRAPH_AttachData(hItem, ahData);
		GRAPH_SetGridDistY(hItem, 40);
		GRAPH_SetGridDistX(hItem, 40);
		//GRAPH_SetGridFixedX(hItem, 1);
		GRAPH_SetGridVis(hItem, 1);
		GRAPH_SetUserDraw(hItem, _UserDraw);
		hScaleV = GRAPH_SCALE_Create( 20, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 40);
		GRAPH_SCALE_SetTextColor(hScaleV, GUI_YELLOW); /* 设置刻度标签的颜色 */
		
		_hScaleH = GRAPH_SCALE_Create(230, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 40);/* 创建水平刻度对象*/
		GRAPH_SCALE_SetTextColor(_hScaleH, GUI_DARKGREEN); /* 设置刻度标签的颜色 */
		GRAPH_AttachScale(hItem, _hScaleH); /* 将水平刻度对象添加到图形控件 */
		
		
		GRAPH_AttachScale(hItem, hScaleV);
		GRAPH_SCALE_SetFactor(hScaleV, 0.5);
		GRAPH_SCALE_SetTextColor(hScaleV, GUI_RED);
		GRAPH_SetBorder(hItem, 20, 10, 10, 10);
		
		/*			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
			TEXT_SetText(hItem, "Temperature:");*/
			
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
			
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24B_ASCII);
			
								hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24B_ASCII);

								hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24B_ASCII);
			
											hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24B_ASCII);
														hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24B_ASCII);
			
	/*		
						hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
			TEXT_SetText(hItem, "IOUT: 0.93 A");
			
						hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
			TEXT_SetText(hItem, "POUT: 205.16 W");*/
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
			PROGBAR_SetFont(hItem, GUI_FONT_16_ASCII);
		
					/* 设置最大值100，最小值0 */
			PROGBAR_SetMinMax(hItem, 0, 100); 
			PROGBAR_SetValue(hItem, waterlevel);
			
			hItem = WM_GetDialogItem(pMsg->hWin,ID_CHECK_0);
		//	CHECKBOX_SetState(hItem,2);
			CHECKBOX_SetFont(hItem,GUI_FONT_16B_ASCII);
			CHECKBOX_SetText(hItem, "WIFI Control allow");
		//	CHECKBOX_SetText(hItem,_apLabel[1]);
			
			
			TEXT_SetFont(WM_GetDialogItem(hWin,ID_TEXT_2), GUI_FONT_16_ASCII);
			TEXT_SetFont(WM_GetDialogItem(hWin,ID_TEXT_0), GUI_FONT_24_ASCII);//&GUI_FontD24x32
			
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0); 
 DROPDOWN_SetFont(hItem, GUI_FONT_24_ASCII); 
 DROPDOWN_AddString(hItem, "19:00:00"); 
 DROPDOWN_AddString(hItem, "19:30:00");
 DROPDOWN_AddString(hItem, "20:00:00");
 DROPDOWN_AddString(hItem, "20:30:00");
 DROPDOWN_AddString(hItem, "21:00:00");
 DROPDOWN_AddString(hItem, "21:30:00");
  DROPDOWN_AddString(hItem, "22:00:00");
	DROPDOWN_SetAutoScroll(hItem, 1); 
DROPDOWN_SetListHeight(hItem, 100); 
DROPDOWN_SetScrollbarWidth(hItem, 16); 

 			hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_1); 
 DROPDOWN_SetFont(hItem, GUI_FONT_24_ASCII);
 DROPDOWN_AddString(hItem, "1"); 
 DROPDOWN_AddString(hItem, "2");
 DROPDOWN_AddString(hItem, "3");
 DROPDOWN_AddString(hItem, "4");
 	DROPDOWN_SetAutoScroll(hItem, 1); 
DROPDOWN_SetListHeight(hItem, 100); 
DROPDOWN_SetScrollbarWidth(hItem, 16); 

hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_0); 
 RADIO_SetText(hItem, "High-power", 0); 
 RADIO_SetText(hItem, "Medium-power", 1);
 RADIO_SetText(hItem, "Low-power", 2);
 RADIO_SetFont(hItem, GUI_FONT_16B_ASCII); 
 
 hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_1); 
 RADIO_SetText(hItem, "Block A", 0); 
 RADIO_SetText(hItem, "Block B", 1);
 RADIO_SetText(hItem, "Block C", 2);
 RADIO_SetFont(hItem, GUI_FONT_16B_ASCII); 
 
 			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetBitmapEx(hItem,0,&buttonbmp_tab[0],0,0);
			BUTTON_SetText(hItem, "");
			
			break;
			
			
			case WM_TIMER:
      //      Count++;
			temp=Get_Temprate();	//得到温度值 
			temp=temp*2;//注意为了和刻度对齐！！！
			sprintf(buf, "Temperature:%02d ℃", temp/2);
			TEXT_SetText(WM_GetDialogItem(hWin,ID_TEXT_0), (const char *)buf);
		if(wifi_allow!=0)
		{
			currentDataPoint.valueWater_temperature = temp/2%100;
			gizwitsHandle((dataPoint_t *)&currentDataPoint);//循环处理机智云协议数据
		}
			
			
			
		GRAPH_DATA_YT_AddValue(ahData, temp%150);
			
			sprintf(buf2, "CPU: %02d%% ",OSStatTaskCPUUsage/100);
				TEXT_SetText(WM_GetDialogItem(hWin,ID_TEXT_2), (const char *)buf2);
			
			WM_RestartTimer(pMsg->Data.v, 100);
            break;
			
			
		
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id) 
			{
				case ID_CHECK_0: // Notifications sent by 'Checkbox'
switch(NCode) {
case WM_NOTIFICATION_CLICKED: //--------------（ 5）
wifi_allow=~wifi_allow;
break;
case WM_NOTIFICATION_RELEASED: //--------------（ 6）
// USER START (Optionally insert code for reacting on notification message)
// USER END
break;
case WM_NOTIFICATION_VALUE_CHANGED: //--------------（ 7）
// USER START (Optionally insert code for reacting on notification message)
// USER END
break;
// USER START (Optionally insert additional code for further notification handling)
// USER END
}
break;
	
				case ID_BUTTON_0: 
							hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED:

						waterflag=~waterflag;
							BUTTON_SetBitmapEx(hItem,0,waterflag?&buttonbmp_tab[1]:&buttonbmp_tab[0],0,0);	
							break;
					}
					break;
					
					
					
					
				
			}
			break;
			
		default:
			WM_DefaultProc(pMsg);
			break;
	}
}

WM_HWIN CreateFramewin2(void) 
{
	WM_HWIN hWin;
		WM_HTIMER hTimer;

	hWin = GUI_CreateDialogBox(_aDialogCreate2, GUI_COUNTOF(_aDialogCreate2), _cbDialog2, WM_HBKWIN, 0, 0);
  hTimer = WM_CreateTimer(WM_GetClientWindow(hWin), 0, 100, 0);
	return hWin;
}



static const GUI_WIDGET_CREATE_INFO _aDialogCreate3[] = 
{
	{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x64, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 650, 370, 110, 40, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 350, 120, 110, 40, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 350, 185, 110, 40, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_3, 350, 250, 110, 40, 0, 0x0, 0 },
		{ TEXT_CreateIndirect, "Text", ID_TEXT_0, 266, 130, 80, 20, 0, 0x64, 0 },
			{ TEXT_CreateIndirect, "Text", ID_TEXT_1, 266, 195, 80, 20, 0, 0x64, 0 },
				{ TEXT_CreateIndirect, "Text", ID_TEXT_2, 266, 260, 80, 20, 0, 0x64, 0 },
};

//对话框回调函数
static void _cbDialog3(WM_MESSAGE * pMsg) 
{
	WM_HWIN hItem;
	int     NCode;
	int     Id;
static u8 ledflag1=0,ledflag2=0,ledflag3=0;
	
	switch (pMsg->MsgId) 
	{
			case WM_PAINT:
				GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			
			break;
				
		case WM_INIT_DIALOG:
			//初始化对话框
			hItem = pMsg->hWin;
			FRAMEWIN_SetTitleHeight(hItem, 30);
			FRAMEWIN_SetText(hItem, "LED Control");
			FRAMEWIN_SetFont(hItem, GUI_FONT_24_ASCII);
			FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			FRAMEWIN_SetTextColor(hItem, 0x0000FFFF);
		
			//初始化BUTTON0
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
		   BUTTON_SetText(hItem, "Back");
			
			//初始化BUTTON1
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
			BUTTON_SetBitmapEx(hItem,0,&buttonbmp_tab[0],0,0);
			BUTTON_SetText(hItem, "");
			//BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
		
				//初始化BUTTON2
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
				BUTTON_SetBitmapEx(hItem,0,&buttonbmp_tab[0],0,0);
			//BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
			BUTTON_SetText(hItem, "");
				//初始化BUTTON3
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
				BUTTON_SetBitmapEx(hItem,0,&buttonbmp_tab[0],0,0);
			//BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
			BUTTON_SetText(hItem, "");   //之所以第一页图标不是透明 因为在case paint里没有GUI_SetBkColor(GUI_WHITE);GUI_Clear();
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32_ASCII);
			TEXT_SetText(hItem, "LED1:");
			
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32_ASCII);
			TEXT_SetText(hItem, "LED2:");
			
			
							hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32_ASCII);
			TEXT_SetText(hItem, "LED3:");
			
			
			
			
			break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id) 
			{
				case ID_BUTTON_0: //BUTTON_0的通知代码，控制LED1
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED: //按钮被按下并释放
          GUI_EndDialog(pMsg->hWin, 0);
							CreateFramewin1();
							break;	
					}
					break;
				case ID_BUTTON_1: //BUTTON_1的通知代码，控制BEEP
							hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED:
							LED1=~LED1;		//蜂鸣器反转
							//LED1=~LED1;
						ledflag1=~ledflag1;
							BUTTON_SetBitmapEx(hItem,0,ledflag1?&buttonbmp_tab[1]:&buttonbmp_tab[0],0,0);	
							break;
					}
					break;
					case ID_BUTTON_2: //BUTTON_0的通知代码，控制LED1
							hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED: //按钮被按下并释放
							LED2=~LED2;		//LED1反转
							//BEEP=~BEEP;
						ledflag2=~ledflag2;
							BUTTON_SetBitmapEx(hItem,0,ledflag2?&buttonbmp_tab[1]:&buttonbmp_tab[0],0,0);	
							break;	
					}
					break;
					case ID_BUTTON_3: //BUTTON_0的通知代码，控制LED1
							hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED: //按钮被按下并释放
							LED3=~LED3;		//LED1反转
							//BEEP=~BEEP;
						ledflag3=~ledflag3;
							BUTTON_SetBitmapEx(hItem,0,ledflag3?&buttonbmp_tab[1]:&buttonbmp_tab[0],0,0);	
							break;	
					}
					break;
			}
			break;
		default:
			WM_DefaultProc(pMsg);
			break;
	}
}

//创建一个对话框
WM_HWIN CreateFramewin3(void) 
{
	WM_HWIN hWin;
		buttonbmp_tab[0]=bmBUTTONOFF;
	buttonbmp_tab[1]=bmBUTTONON;

	hWin = GUI_CreateDialogBox(_aDialogCreate3, GUI_COUNTOF(_aDialogCreate3), _cbDialog3, WM_HBKWIN, 0, 0);
	return hWin;
}





static const GUI_WIDGET_CREATE_INFO _aDialogCreate4[] = 
{
	{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x64, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 640, 350, 110, 40, 0, 0x0, 0 },
	{ TEXT_CreateIndirect,      "Text",    ID_TEXT_0,    30,60,300,48, 0,0},
		{ TEXT_CreateIndirect, "Text", ID_TEXT_1, 30, 10, 180, 20, 0, 0x64, 0 },
		{ TEXT_CreateIndirect, "CPU:", ID_TEXT_2, 670, 10, 100, 20, 0, 0 },
		{ PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_0, 55, 180, 175, 35, 0, 0x0, 0 },
			{ TEXT_CreateIndirect, "Text", ID_TEXT_3, 360, 110, 220, 20, 0, 0 },
		{ SLIDER_CreateIndirect, "Slider", ID_SLIDER_0, 370, 150, 150, 50, 0, 0x0, 0 },
};


static void _cbDialog4(WM_MESSAGE * pMsg) 
{
	WM_HWIN hItem;
	int     NCode;
	int     Id;
	 WM_HWIN hWin = pMsg->hWin;
char buf[10];
	char buf2[10];
	char i;
	
	switch (pMsg->MsgId) 
	{
		case WM_INIT_DIALOG:
			//
			// 初始化框架窗口
			//
			hItem = pMsg->hWin;
			FRAMEWIN_SetTitleHeight(hItem, 30);
			FRAMEWIN_SetText(hItem, "Illumination");
			FRAMEWIN_SetFont(hItem, GUI_FONT_24_ASCII);
			FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			FRAMEWIN_SetTextColor(hItem, 0x0000FFFF);
		
		
		
					hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
			PROGBAR_SetFont(hItem, GUI_FONT_16_ASCII);
		
					/* 设置最大值100，最小值0 */
			PROGBAR_SetMinMax(hItem, 0, 100); 
		
			//
			// 初始按钮控件
			//
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetFont(hItem, GUI_FONT_20_1);
			BUTTON_SetText(hItem, "Back");
		

		
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
			TEXT_SetText(hItem, "Related Strength:");
			
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
			TEXT_SetText(hItem, "PWM Out (10%-100%):");
			
		
			TEXT_SetFont(WM_GetDialogItem(hWin,ID_TEXT_2), GUI_FONT_24_ASCII);	
			TEXT_SetFont(WM_GetDialogItem(hWin,ID_TEXT_0), GUI_FONT_32_ASCII);//&GUI_FontD24x32
			
						hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
			/* 设置滑块控件上面显示10个刻度标签 */
			SLIDER_SetNumTicks(hItem, 10);
			/* 设置滑块的范围，最小值0，最大值10 */
			SLIDER_SetRange(hItem, 0, 9);
			
			
			break;
			
			
			case WM_TIMER:
     adcx=Lsens_Get_Val();
			sprintf(buf, "%02d", adcx);
			TEXT_SetText(WM_GetDialogItem(hWin,ID_TEXT_0), (const char *)buf);
	 i++;
			if(i>=3){
			sprintf(buf2, "CPU: %02d%% ",OSStatTaskCPUUsage/100);
				TEXT_SetText(WM_GetDialogItem(hWin,ID_TEXT_2), (const char *)buf2);
				
				hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
					PROGBAR_SetValue(hItem, adcx);
				
				i=0;
			}
			WM_RestartTimer(pMsg->Data.v, 100);
            break;
			
			
		
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id) 
			{
				case ID_BUTTON_0: 
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						
						/* 关闭当前对话框， 创建对话框1 */
						case WM_NOTIFICATION_RELEASED:
							GUI_EndDialog(pMsg->hWin, 0);
							CreateFramewin1();
							break;
					}
					break;
					
			}
			break;
			
		default:
			WM_DefaultProc(pMsg);
			break;
	}
}

WM_HWIN CreateFramewin4(void) 
{
	WM_HWIN hWin;
		WM_HTIMER hTimer;

	hWin = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbDialog4, WM_HBKWIN, 0, 0);
  hTimer = WM_CreateTimer(WM_GetClientWindow(hWin), 0, 100, 0);
	return hWin;
}




//BUTTO演示函数
void ButtonUse_Demo(void)
{
	WM_HWIN hWin;

	
	WM_SetCreateFlags(WM_CF_MEMDEV);
	hWin=CreateFramewin1();

	while(1)
	{
		GUI_Delay(100);
	}
}

