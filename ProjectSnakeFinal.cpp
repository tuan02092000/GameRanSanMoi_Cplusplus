#include <iostream>
#include <string.h>
#include "Thuviencuatoi.h"
#include <list>
#include <iterator>
#define MAX 100
using namespace std;
int sl = 3;
class GameSnake{
	private:
		string name;
		int point;
		int speed;
	public:
		GameSnake(){};
		GameSnake(string name,int point,int speed){
			this->name = name;
			this->point = point;
			this->speed = speed;
		}
		~GameSnake(){};
		string getName(){
			return this->name;
		}
		void setName(string name){
			this->name = name;
		}
		int getPoint(){
			return this->point;
		}
		void setPoint(int point){
			this->point = point;
		}
		int getSpeed(){
			return this->speed;
		}
		void setSpeed(int speed){
			this->speed = speed;
		}
		//Nhap thong tin nguoi choi
		void Input(){
			SetColor(5);
			cin.ignore();
			gotoXY(40,9); cout<<"Nhap ten nguoi choi : "; getline(cin,name);
			gotoXY(40,10); cout<<"Nhap toc do choi (10 > 50 > 100 ...) : "; cin>>speed;
		}
		//Xuat thong tin nguoi choi
		void Output(){
			SetColor(5);
			gotoXY(50,5); cout<<"Nguoi choi : "<<name<<endl;
			gotoXY(50,6); cout<<"Diem : "<<point;
		}
		//In ra Top Diem
		void PrintTopPoint(int x,int y){
			gotoXY(x,y); cout<<name;
			gotoXY(x+20,y); cout<<point;
			gotoXY(x+40,y); cout<<speed;
		}
		void VeTuongTren(){
			int x = 10, y = 1;
			while(x <= 100){
				gotoXY(x,y);
				cout<<"*";
				x++;
				Sleep(5);
			}
		}
		void VeTuongDuoi(){
			int x = 100, y = 26;
			while (x >= 10){
				gotoXY(x, y);
				cout << "*";
				x--;
				Sleep(5);
			}
		}
		void VeTuongPhai(){
			int x = 100, y = 1;
			while (y <= 26){
				gotoXY(x, y);
				cout << "*";
				y++;
				Sleep(5);
			}
		}
		void VeTuongTrai(){
			int x = 10, y = 26;
			while (y >= 1){
				gotoXY(x, y);
				cout << "*";
				y--;
				Sleep(5);
			}
		}
		//Ve khung tro choi
		void VeTuong(){
			SetColor(1);
			VeTuongTren();
			VeTuongPhai();
			VeTuongDuoi();	
			VeTuongTrai();
			SetColor(7);
		}
		void KhoiTaoRan(int toaDoX[],int toaDoY[]){
			int x = 50 , y = 13;
			for(int i = 0 ; i < sl ; i++){
				toaDoX[i] = x;
				toaDoY[i] = y;
				x--;
			}
		}
		void VeRan(int toaDoX[],int toaDoY[]){
			for(int i = 0 ; i < sl ; i++){
				gotoXY(toaDoX[i], toaDoY[i]);
				ShowCur(0);
				if(i == 0){
					cout<<"0";
				}else{
					cout<<"o";
				}
			}
		}
		void XoaDuLieuCu(int toaDoX[],int toaDoY[]){
			for(int i = 0 ; i < sl ; i++){
				gotoXY(toaDoX[i],toaDoY[i]);
				cout<<" ";
			}
		}
		void Them(int a[],int x){
			for(int  i = sl ; i > 0 ; i--){
				a[i] = a[i - 1];
			}
			a[0] = x;
			sl++;
		}
		void Xoa(int a[],int vt){
			for(int  i = vt ; i < sl ; i++){
				a[i] = a[i + 1];
			}
			sl--;
		}
		void XyLyRan(int toaDoX[],int toaDoY[],int x,int y,int& xqua,int& yqua){
			Them(toaDoX,x);
			Them(toaDoY,y);
			if(CheckRanAnQua(xqua, yqua, toaDoX[0], toaDoY[0]) == false){
				Xoa(toaDoX,sl - 1);
				Xoa(toaDoY,sl - 1);
			}else{
				sl--;
				point += 5;
				TaoQua(xqua,yqua,toaDoX,toaDoY);
			}
			VeRan(toaDoX,toaDoY);
		}
		//Kiem tra ran cham tuong 
		bool CheckRanChamTuong(int x0,int y0){
			//Ran cham tuong tren
			if(y0 == 1 && (x0 >= 10 && x0 <= 100)){
				return true;
			}
			//Ran cham tuong duoi
			else if(y0 == 26 && (x0 >= 10 && x0 <= 100)){
				return true;
			}
			//Ran cham tuong phai
			else if(x0 == 100 && (y0 > 1 && y0 <= 26)){
				return true;
			}
			//Ran cham tuong trai
			else if(x0 == 10 && (y0 > 1 && y0 <= 26)){
				return true;
			}
			return false;
		}
		//Kiem tra ran cham duoi
		bool CheckRanChamDuoi(int toaDoX[], int toaDoY[]){
			for(int i = 1 ; i < sl ; i++){
				if((toaDoX[0] == toaDoX[i]) && toaDoY[0] == toaDoY[i]){
					return true;
				}
			}
			return false;
		}
		bool CheckRan(int toaDoX[],int toaDoY[]){
			bool check1 = CheckRanChamTuong(toaDoX[0],toaDoY[0]); // gameover = true;
			bool check2 = CheckRanChamDuoi(toaDoX,toaDoY); // gameover = true;
			bool check3 = (point == 500); // game win
			if(check1 || check2 || check3){
				return true; // gameover
			}
			return false;
		}
		//Tao qua tang diem
		void TaoQua(int &xqua,int &yqua,int toaDoX[],int toaDoY[]){
			do{
				//11 <= xqua <= 99
				xqua = rand() % (99 - 11 + 1) + 11;
				//2 <= yqua <= 25
				yqua = rand() % (25 - 2 + 1) + 2;	
			}while(CheckRanDeQua(xqua, yqua, toaDoX, toaDoY));
			int i = rand() % (15 - 1 + 1) + 1;
			SetColor(i);
			gotoXY(xqua,yqua);
			cout<<"o";
			SetColor(i);	
		}
		//Kiem tra ran de len qua
		bool CheckRanDeQua(int xqua,int yqua,int toaDoX[], int toaDoY[]){
			for (int i = 0; i < sl; i++){
				if ((xqua == toaDoX[i]) && (yqua == toaDoY[i])){
					return true;//ran de len qua
				}	
			}
			return false;
		}
		//Kiem tra ran an qua 
		bool CheckRanAnQua(int xqua,int yqua,int x0,int y0){
			if ((x0 == xqua) && (y0 == yqua)){
				return true;//ran an qua
			}
			return false;
		}
		//Vao choi
		void Start(list<GameSnake>& listPoint){
			system("cls");
			setPoint(0);
			bool gameOver = false;
			int toaDoX[MAX], toaDoY[MAX];
			VeTuong();
			KhoiTaoRan(toaDoX,toaDoY);
			VeRan(toaDoX,toaDoY);
			//=======Kiem tra va tao Qua======
			srand(time(NULL));
			int xqua = 0, yqua = 0;
			TaoQua(xqua, yqua, toaDoX, toaDoY);
			int x = 50, y = 13; // Vi tri ban dau cua Ran
			int check = 2;
			while(gameOver == false){
				XoaDuLieuCu(toaDoX,toaDoY);	
				//0: di xuong
				//1: di len
				//2: qua phai
				//3: qua trai	
			//======Dieu Khien======	
			if (_kbhit()){
				char kitu = _getch();
				if (kitu == -32)
				{
					kitu = _getch();
					if (kitu == 72 && check != 0)//di len
					{
						check = 1;
					}
					else if (kitu == 80 && check != 1)//di xuong
					{
						check = 0;
					}
					else if (kitu == 77 && check != 3)//di phai
					{
						check = 2;
					}
					else if (kitu == 75 && check != 2)//di trai
					{
						check = 3;
					}
				}
			}
			//======Thuc Hien Di Chuyen======
			if (check == 0){
				y++;//di xuong
			}else if (check == 1){
				y--;//di len
			}else if (check == 2){
				x++;//di qua phai
			}
			else if (check == 3){
				x--;//di qua trai	
			}	
			XyLyRan(toaDoX, toaDoY, x, y, xqua, yqua);
			//========== kiem tra =========
			gameOver = CheckRan(toaDoX,toaDoY);
			gotoXY(2,30); cout<<"Diem : "<<point;
			if(point < 100){
				gotoXY(2,31);
				cout<<"Level : 1";
			}else if(point < 250){
				gotoXY(2,31);
				cout<<"Level : 2";
				speed = speed - 10 ;
			}else if(point < 500){
				gotoXY(2,31);
				cout<<"Level : 3";
				speed = speed - 20;
			}
			Sleep(speed);
		}
		system("cls");
		ShowCur(0);
		if(point == 500){
			SetColor(12);
			gotoXY(45,3); Sleep(500); printf("%c%c%c",3,3,3);
			gotoXY(50,3); Sleep(500); printf("YOU WIN");
			gotoXY(59,3); Sleep(500); printf("%c%c%c",3,3,3);
			gotoXY(45,10); SetColor(7); cout<<"Press any key to continue . . .";
		}else{
			Sleep(300);
			gotoXY(50,3); SetColor(12); cout<<"GAME OVER";
			Sleep(300); Output();
			sl = 3;
			gotoXY(50,10); SetColor(7); cout<<"Press any key to continue . . .";
		}
		//them doi tuong snake vao listPoint
		GameSnake snake(name,point,speed);
		listPoint.push_back(snake);
		_getch();	
	}		
};
void Menu(){
	SetColor(9);
	gotoXY(40,10); Sleep(100); cout<<"1. Bat Dau";
	gotoXY(40,11); Sleep(100); cout<<"2. Huong Dan";
	gotoXY(40,12); Sleep(100); cout<<"3. Top Diem";
	gotoXY(40,13); Sleep(100); cout<<"0. Thoat";
	gotoXY(40,14); Sleep(100); cout<<"Lua chon cua ban : ";
}
void Intro(){
	system("cls");
	SetColor(9);
	gotoXY(50,3); SetColor(12); printf("GAME RAN SAN MOI");
	gotoXY(47,4); SetColor(12); printf("%c%c%c",3,3,3);gotoXY(66,4);printf("%c%c%c",3,3,3);
	Sleep(300);
	gotoXY(52,4); SetColor(11); printf("LOADING GAME");
	for(int i = 0 ; i <= 100 ; i += 10){ 
		gotoXY(52,5); SetColor(13); printf(".....%d%%.....",i);
		Sleep(50);
	}
	gotoXY(38,6); SetColor(14); printf("____________________________________________");
}
void HuongDan(){
	gotoXY(40,10); SetColor(10); cout << "LUAT CHOI :";
	gotoXY(40,11); Sleep (50); cout << "1. Dieu khien con ran bang cac phim Len/Xuong/Trai/Phai";
	gotoXY(40,12); Sleep (50); cout << "2. Muc dich de an cac qua, an duoc 1 qua con ran se dai them 1 dot";
	gotoXY(40,13); Sleep (50); cout << "3. Diem cua ban se duoc cong 5 neu an duoc qua";
	gotoXY(40,14); Sleep (50); cout << "4. Neu con ran cham tuong hoac cham than thi ban thua cuoc!";
	gotoXY(40,15); Sleep (50); cout << "5. Neu ban dat duoc 500 diem ban se chien thang!";
	gotoXY(40,16); Sleep (50); cout << "Cuoi cung! Chuc cac ban co giay phut thu gian thoai mai! Mai iu <3!!!\n";
	SetColor(7);
}
//Sap xep diem trong listPoint
bool Sort(GameSnake First,GameSnake Next){
	if (First.getPoint() > Next.getPoint()) 
		return true; 
	if (First.getPoint() < Next.getPoint()) 
		return false;
	return true;
}
void MoDau(GameSnake snake,list<GameSnake> &listPoint){
		system("cls");
		int luachon;	
		do{
			Intro();
			Menu();
			cin>>luachon;
			switch(luachon){
				case 1:{
					system("cls");
					Intro();
					snake.Input();
					snake.Start(listPoint);
					break;
				}
				case 2:{
					Intro();
					HuongDan();
					system("pause");
					break;
				}
				case 3:{
					system("cls");
					SetColor(12);
					gotoXY(50,4); SetColor(12); printf("%c%c%c",3,3,3);
					gotoXY(57,4); SetColor(11); printf("Top Point");
					gotoXY(70,4); SetColor(12); printf("%c%c%c",3,3,3);
					SetColor(13);
					gotoXY(40,7) ; cout<<"Name"; gotoXY(60,7); cout<<"Point"; gotoXY(80,7); cout<<"Speed";
					
					listPoint.sort(Sort);
					
					//Toa do in diem
					int x=40,y=8;
					
					list <GameSnake> :: iterator it; 
    				for(it = listPoint.begin(); it != listPoint.end(); ++it) {
    					Sleep(200);
    					(*it).PrintTopPoint(x,y);
    					y++;
					}
					cout<<endl<<endl;
					SetColor(7);
					system("pause");
					break;
				}
				case 0:{
					listPoint.clear();
					gotoXY(47,16); SetColor(12); printf("%c%c%c",3,3,3);
					gotoXY(52,16); SetColor(11); printf("GOODDD BYEEE");
					gotoXY(66,16); SetColor(12); printf("%c%c%c",3,3,3);
					break;
				}
				default:{
					SetColor(10); 
					gotoXY(40,15); Sleep(200); cout<<"Lua chon khong hop le !"<<endl;
					system("pause");
					break;
				}
			}
		}while(luachon != 0);
	}
int main(){
	GameSnake snake;
	list<GameSnake> listPoint;
	MoDau(snake,listPoint);
	return 0;
}









