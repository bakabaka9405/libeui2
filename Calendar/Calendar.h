#pragma once
#include<stdexcept>
#include<easyx.h>
#include<windows.h>
#include<time.h>
#include<stdio.h>
#include"Property.h"
class Calendar {
public:
	Calendar();
	void Update();
	void Draw(IMAGE* working_image = nullptr);
	void TurnToNow();
	void TurnToDate(int year, int month, int date);
	void ToNextDay();
	void ToNextMonth();
	void ToNextYear();
	Property<int, PropertyMode::ReadWrite>X, Y;
	Property<int, PropertyMode::ReadWrite>Size;
	Property<int, PropertyMode::ReadWrite>Year, Month, Date;
	Property<COLORREF, PropertyMode::ReadWrite>ThemeColor;
private:
	//�ж�ĳһ���Ƿ������꣬���yearΪ0���������Ĭ��Ϊ��������ʾ�����
	bool is_leap_year(int year = 0);

	//��������
	void calc();
private:
	int m_x, m_y;
	int m_size;
	int m_year, m_month, m_date;
	int m_first_day;			//����µĵ�һ�������ڼ�
	int m_ldlm;					//last day of last month
	int m_days;					//���µ�����
	COLORREF m_theme_color;
	static constexpr COLORREF m_gray_color = RGB(200, 200, 200);
public:
	class {
	public:
		int x, y, size;
		TCHAR ch;
		COLORREF theme_color;
		COLORREF final_color;
		void Init() {
			x = 1;
			y = 1;
			size = 29;
			ch = 0;
			theme_color = GREEN;
			final_color = RGB(133, 191, 79);
			m_current_color = theme_color;
			m_mouse_on = false;
			m_start = 0;
		}
		void Draw(IMAGE* working_image) {
			SetWorkingImage(working_image);
			setlinestyle(PS_NULL);
			setfillstyle(BS_SOLID);
			setfillcolor(m_current_color);
			fillrectangle(x, y, x + size, y + size);
			settextcolor(WHITE);
			drawtext(ch, new RECT{ x,y,x + size,y + size },
					 DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			SetWorkingImage();
		}
		void Update() {
			if (m_mouse_on) {
				int r = GetRValue(theme_color);
				int g = GetGValue(theme_color);
				int b = GetBValue(theme_color);
				int r1 = GetRValue(final_color);
				int g1 = GetGValue(final_color);
				int b1 = GetBValue(final_color);
				double t =
					double(clock() - m_start) * 3 / CLOCKS_PER_SEC;
				if (t > 1)t = 1;
				int r2 = r + int((r1 - r) * t);
				int g2 = g + int((g1 - g) * t);
				int b2 = b + int((b1 - b) * t);
				m_current_color = RGB(r2, g2, b2);
			}
			else if (m_current_color != theme_color) {
				int r = GetRValue(theme_color);
				int g = GetGValue(theme_color);
				int b = GetBValue(theme_color);
				int r1 = GetRValue(final_color);
				int g1 = GetGValue(final_color);
				int b1 = GetBValue(final_color);
				double t =
					double(clock() - m_start) * 3 / CLOCKS_PER_SEC;
				if (t > 1)t = 1;
				int r2 = r1 - int((r1 - r) * t);
				int g2 = g1 - int((g1 - g) * t);
				int b2 = b1 - int((b1 - b) * t);
				m_current_color = RGB(r2, g2, b2);
			}
		}
		void Mouse_On() {
			m_mouse_on = true;
			m_start = clock();
		}
		void Mouse_Leave() {
			m_mouse_on = false;
			m_start = clock();
		}
	private:
		COLORREF m_current_color;//��ǰ����ɫ
		bool m_mouse_on;//����Ƿ��°�ť
		clock_t m_start;//��갴�°�ť��ʱ��
	}m_bt_left, m_bt_right;
};