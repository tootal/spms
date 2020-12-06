// C++ 简易学生成绩管理系统
// 面向对象思路设计, 单文件

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

const string info[] = {"学号", "姓名", "性别", "分科"};
const string subj[] = {"中文", "数学", "英语"};
const string art[] = {"政治", "历史", "地理"};
const string sci[] = {"物理", "化学", "生物"};

template <typename T>
class student{
public:
	student *next, *pre;
	int id;
	// 获取学生信息(0-学号、1-姓名、2-性别)
	student(){
		next = pre = nullptr;
	}
	virtual string getInfo(int x){
		switch(x){
			case 0: return sid;
			case 1: return name;
			case 2: return gender;
			default: return "";
		}
	}
	// 获取学生成绩(0-中文、1-数学、2-英语)
	virtual T getScore(int x){
		if(x >= 0 && x < 3)	return scores[x];
		else return -1;
	}
	virtual bool setInfo(int x, string s){
		switch(x){
			case 0:{ sid = s; return true; }
			case 1:{ name = s; return true; }
			case 2:{ gender = s; return true; }
			default: return false;
		}
	}
	virtual bool setScore(int x, T s){
		if(x >= 0 && x < 3){ scores[x] = s; return true; }
		else return false;
	}

protected:
	string sid,name,gender;
	T scores[3];
};

template <typename T>
class artStu:public student<T>{
public:
	string getInfo(int x){
		if(x == 3) return branch;
		else return student<T>::getInfo(x);
	}
	T getScore(int x){
		if(x >= 3 && x < 6) return scores[x - 3];
		else return student<T>::getScore(x);
	}
	bool setInfo(int x, string s){
		if(x == 3) { branch = s; return true; }
		else return student<T>::setInfo(x, s);
	}
	bool setScore(int x, T s){
		if(x >= 3 && x < 6) { scores[x - 3] = s; return true; }
		else return student<T>::setScore(x, s);
	}
	
	template <typename Ty>
	friend istream& operator>>(istream &in, artStu<Ty> &x);
	template <typename Ty>
	friend ostream& operator<<(ostream &out, artStu<Ty> &x);
private:
	string branch;
	T scores[3];
};

template <typename T>
istream& operator>>(istream &in, artStu<T> &x){
	for(int i = 0;i < 6;i ++){
		T s;
		cout << "(" ;
		if(i < 3) cout << subj[i];
		else cout << art[i - 3];
		cout << "成绩?) ";
		in >> s;
		x.setScore(i, s);
	}
	getchar();
	return in;
}

template <typename T>
ostream& operator<<(ostream &out,artStu<T> &x){
	for(int j = 0;j < 4;j ++)
		out << info[j] << ": " << x.getInfo(j) << "\n";		
	for(int j = 0;j < 6;j ++){
		if(j < 3) out << subj[j];
		else out << art[j - 3];
		out << "成绩: " << x.getScore(j) << "\n";
	}
	return out;
}

template <typename T>
class sciStu:public student<T>{
public:
	string getInfo(int x){
		if(x == 3) return branch;
		else return student<T>::getInfo(x);
	}
	T getScore(int x){
		if(x >= 3 && x < 6) return scores[x - 3];
		else return student<T>::getScore(x);
	}
	bool setInfo(int x, string s){
		if(x == 3) { branch = s; return true; }
		else return student<T>::setInfo(x, s);
	}
	bool setScore(int x, T s){
		if(x >= 3 && x < 6) { scores[x - 3] = s; return true; }
		else return student<T>::setScore(x, s);
	}
	
	template <typename Ty>
	friend istream& operator>>(istream &in, sciStu<Ty> &x);
	template <typename Ty>
	friend ostream& operator<<(ostream &out, sciStu<Ty> &x);
private:
	string branch;
	T scores[3];
};

template <typename T>
istream& operator>>(istream &in, sciStu<T> &x){
	for(int i = 0;i < 6;i ++){
		T s;
		cout << "(" ;
		if(i < 3) cout << subj[i];
		else cout << sci[i - 3];
		cout << "成绩?) ";
		in >> s;
		x.setScore(i, s);
	}
	getchar();
	return in;
}

template <typename T>
ostream& operator<<(ostream &out,sciStu<T> &x){
	for(int j = 0;j < 4;j ++)
		out << info[j] << ": " << x.getInfo(j) << "\n";		
	for(int j = 0;j < 6;j ++){
		if(j < 3) out << subj[j];
		else out << sci[j - 3];
		out << "成绩: " << x.getScore(j) << "\n";
	}
	return out;
}
// 比较大小
template <typename T>
bool cmp(student<T> *x, student<T> *y){
	T xs[5] = {0}, ys[5] = {0};
	for(int i = 0;i < 3;i ++){
		xs[i + 1] = x -> getScore(i);
		ys[i + 1] = y -> getScore(i);
		xs[0] += xs[i + 1];
		ys[0] += ys[i + 1];
	}
	for(int i = 3;i < 6;i ++){
		xs[0] += x -> getScore(i);
		ys[0] += y -> getScore(i);
	}
	xs[4] = - (x -> id);
	ys[4] = - (y -> id);
	for(int i = 0;i < 5;i ++){
		if(xs[i] != ys[i]) return xs[i] > ys[i];
		// cout << xs[i] << " " << ys[i] << "\n";
	}
	return true;
}
// 交换链表节点(头尾节点不参与交换)
template <typename T>
void swapside(student<T> *&x){
	student<T> *y = x -> next;
	x -> pre -> next = y;
	y -> next -> pre = x;
	x -> next = y -> next;
	y -> pre = x -> pre;
	x -> pre = y;
	y -> next = x;
	x = y;
}
template <typename T>
void swap(student<T> *&x, student<T> *&y){
	if(x == y)return ;
	if(x -> next == y)
		swapside(x);
	else if(y -> next == x)
		swapside(y);
	else{
		x -> pre -> next = y;
		x -> next -> pre = y;
		y -> pre -> next = x;
		y -> next -> pre = x;
		student<T> *temp = x -> pre; x -> pre = y -> pre; y -> pre = temp;
		temp = x -> next; x -> next = y -> next; y -> next = temp;
		temp = x; x = y; y = temp;
	}
} 
// 选择排序
template <typename T>
void sort(student<T> *first, student<T> *last, bool (*func)(student<T>*, student<T>*)){
	for(student<T> *p = first;p -> next != last;p = p -> next){
		student<T> *temp = p;
		for(student<T> *q = p -> next;q != last;q = q -> next)
			if(func(q, temp)) temp = q;
		swap(p, temp);
	}
}

template <typename T>
class app{
public:
	app(){
		size = 0;
		artSz = 0;
		head = new student<T>;
		tail = new student<T>;
		head -> next = tail;
		tail -> pre = head;
	}
	void show(){
		cout << "C++ 学生成绩管理系统\n";
		cout << "1.录入\n";
		cout << "2.查看\n";
		cout << "3.统计\n";
		cout << "4.排名\n";
		cout << "5.导入\n";
		cout << "6.导出\n";
		cout << "h.菜单\n";
		cout << "0.退出\n\n";
	}
	int exec(){
		string in;
		while(true){
			cout << ">>> ";
			getline(cin, in);
			if(in[0] == ':'){ system(string(in.begin()+1,in.end()).c_str()); continue; }
			if(in == "") continue;
			if(in == "0") return 0;
			if(in == "1") add();
			else if(in == "2") query();
			else if(in == "3") stat();
			else if(in == "4") rank();
			else if(in == "5") impt();
			else if(in == "6") expt();
			else if(in == "h") show();
			else cout << "输入错误, 请重新输入.\n";
			
		}
		return 0;
	}
	void insert(student<T> *x){
		x -> next = tail;
		x -> pre = tail -> pre;
		tail -> pre -> next = x;
		tail -> pre = x;
	}
	void add(){
		cout << "请输入学生信息, 分科请输入 文科/理科.\n";
		cout << "输入 # 取消录入.\n";
		string readit[4];
		for(int i = 0;i < 4;i ++){
			cout << "(" << info[i] << "?) ";
			getline(cin, readit[i]);
			if(readit[i][0]=='#')return;
		}
		student<T> *x;
		if(readit[3] == "文科"){
			artSz ++;
			x = new artStu<T>;
			cin >> (artStu<T>&)*x;
		}else if(readit[3] == "理科"){
			x = new sciStu<T>;
			cin >> (sciStu<T>&)*x;
		}else{
			cout << "分科信息输入错误.\n";
			return ;
		}
		x -> id = size + 1;
		for(int i = 0;i < 4;i ++)
			x -> setInfo(i,readit[i]);
		insert(x);
		cout << "添加学生信息成功.\n";
		size ++;
	}
	void query(){
		if(size == 0){
			cout << "没有学生信息.\n";
			return;
		}
		cout << "请输入学号: ";
		string s;
		getline(cin, s);
		int cnt = 0;
		for(student<T> *p = head -> next;p != tail;p = p -> next){
			if(p -> getInfo(0) == s){
				cnt ++;
				double sum = 0;
				for(int j = 0;j < 6;j ++)
					sum += p -> getScore(j);
				if(p -> getInfo(3) == "文科")
					cout << (artStu<T>&)*p;
				else cout << (sciStu<T>&)*p;
				cout << "总分: " << sum << "\n";
				cout << "平均分: " << sum / 6 << "\n";
			}
		}
		if(cnt == 0) cout << "未找到学号为 \"" << s << "\" 的学生.\n"; 
	}
	void stat(){
		if(size == 0) cout << "没有学生信息.\n";
		else{
			T sum[9] = {0}, artSum = 0, sciSum = 0, all = 0;
			for(student<T> *p = head -> next;p != tail;p = p -> next){
				for(int j = 0;j < 6;j ++){
					if(p -> getInfo(3) == "文科" || j < 3)
						sum[j] += p -> getScore(j);
					else
						sum[j + 3] += p -> getScore(j);
					all += p -> getScore(j);
				}
			}
			cout << "学生成绩统计: \n共有学生 "<<size<<" 人,其中文科生 "<<artSz<<" 人,理科生 "<<size-artSz<<" 人.\n";
			for(int i = 0;i < 3; i ++)
				cout << subj[i] << "平均分: " << sum[i] / size << "\n";
			if(artSz != 0)
				for(int i = 0;i < 3;i ++)
					cout << art[i] << "平均分: " << sum[i + 3] / artSz << "\n";
			if(artSz != size)
				for(int i = 0;i < 3;i ++)
					cout << sci[i] << "平均分: " << sum[i + 6] / (size - artSz) << "\n";
			cout << "总成绩平均分: " << all / size << "\n";
		}
	}
	void rank(){
		if(size == 0){
			cout << "没有学生信息.\n";
			return;
		}
		cout << "成绩排名:\n";
		sort(head -> next, tail, cmp);
		int rk = 0;
		for(student<T> *p = head -> next;p != tail;p = p -> next){
			cout << "第" << ++rk << "名:\n";
			T sum = 0;
			for(int i = 0;i < 6;i ++)
				sum += p -> getScore(i);
			if(p -> getInfo(3) == "文科")
				cout << (artStu<T>&)*p;
			else
				cout << (sciStu<T>&)*p;
			cout << "总分: " << sum << "\n\n";
		}
	}
	void impt(){
		cout<<"1.文本文件\n";
		cout<<"2.二进制文件\n";
		cout<<"请输入导入文件模式: ";
		string in;
		getline(cin,in);
		while(true){
			if(in=="1"){
				impt1();
				break;
			}else if(in=="2"){
				impt2();
				break;
			}else
				cout<<"输入错误,请重新输入: ";
		}
	}
	void expt(){
		if(size == 0){
			cout << "没有学生信息.\n";
			return;
		}
		cout<<"1.文本文件\n";
		cout<<"2.二进制文件\n";
		cout<<"请输入导出文件模式: ";
		string in;
		getline(cin,in);
		while(true){
			if(in=="1"){
				expt1();
				break;
			}else if(in=="2"){
				expt2();
				break;
			}else
				cout<<"输入错误,请重新输入: ";
		}

	}
	void impt1(){
		cout << "请输入导入文件名: ";
		string path;
		getline(cin, path);
		ifstream in(path.c_str());
		if(in.is_open()){
			char ch;
			string you;
			getline(in, you);
			int cnt = 0,artCnt=0;
			while(getline(in, you)){
				string readi[4];
				T reads[7];
				istringstream line(you);
				for(int i = 0;i < 4;i ++)
					getline(line, readi[i], ',');
				for(int i = 0;i < 7;i ++)
					line >> reads[i] >> ch;
				student<T> *fresh;
				if(readi[3] == "文科"){
					fresh = new artStu<T>;
					artCnt++;
				}
				else 
					fresh = new sciStu<T>;
				for(int i = 0;i < 4;i ++)
					fresh -> setInfo(i, readi[i]);
				for(int i = 0;i < 6;i ++)
					fresh -> setScore(i, reads[i]);
				fresh -> id = size + 1;
				insert(fresh);
				cnt ++;
			}
			if(cnt == 0)
				cout << "无数据.\n";
			else{
				cout << "从 "<<path<<" 导入学生信息成功.\n";
				cout << "共导入 "<<cnt<<" 位学生,其中文科生 "<<artCnt<<" 人,理科生 "<<cnt-artCnt<<" 位.\n";
			}
			size+=cnt;
			artSz+=artCnt;
		}else
			cout << "导入失败.\n";
	}
	void expt1(){
		cout << "请输入导出文件名: ";
		string path;
		getline(cin, path);
		ofstream out(path.c_str());
		if(out.is_open()){
			for(int i = 0;i < 4;i ++)
				out << info[i] << ",";
			for(int i = 0;i < 3;i ++)
				out << subj[i] << ",";
			for(int i = 0;i < 3;i ++)
				out << art[i] << "/" << sci[i] << ",";
			out << "总分\n";
			for(student<T> *p = head -> next;p != tail;p = p -> next){
				for(int i = 0;i < 4;i ++)
					out << p -> getInfo(i) << ",";
				T sum = 0;
				for(int i = 0;i < 6;i ++){
					out << p -> getScore(i) << ",";
					sum += p -> getScore(i);
				}
				out << sum << "\n";
			}
			cout << "导出到文件 "<<path<<" 成功.\n";
			cout << "共导出 "<<size<<" 人,其中文科生 "<<artSz<<" 人,理科生 "<<size-artSz<<" 人.\n";
		}else
			cout << "导出失败.\n";
	}
	//导入二进制数据文件
	void impt2(){
		cout << "请输入导入文件名: ";
		string path;
		getline(cin, path);
		ifstream in(path.c_str(),ios::binary);
		int cnt=0,artCnt=0;
		if(in.is_open()){
			in.read((char*)&cnt,sizeof(int));
			for(int i=0;i<cnt;i++){
				student<T> *fresh;
				string readi[4];
				T reads[6];
				for(int j=0;j<4;j++){
					int len;
					in.read((char*)&len,sizeof(int));
					char *temp=new char[len];
					in.read((char*)temp,len*sizeof(char));
					readi[j]=temp;
				}
				for(int j=0;j<6;j++)
					in.read((char*)(reads+j),sizeof(T));
				if(readi[3]=="文科"){
					fresh=new artStu<T>;
					artCnt++;
				}else
					fresh=new sciStu<T>;
				for(int j=0;j<4;j++)
					fresh->setInfo(j,readi[j]);
				for(int j=0;j<6;j++)
					fresh->setScore(j,reads[j]);
				insert(fresh);
			}
			if(cnt==0){
				cout << "无数据.\n";
				return ;
			}else{
				cout << "从 "<<path<<" 导入学生信息成功.\n";
				cout << "共导入 "<<cnt<<" 位学生,其中文科生 "<<artCnt<<" 人,理科生 "<<cnt-artCnt<<" 人.\n";
			}
			size+=cnt;
			artSz+=artCnt;
		}else
			cout << "导入失败.\n";
	}
	//导出二进制数据文件
	//数据文件开头一个整型变量表示数据数量
	void expt2(){
		cout << "请输入导出文件名: ";
		string path;
		getline(cin, path);
		ofstream out(path.c_str(),ios::binary);
		if(out.is_open()){
			out.write((char*)&size,sizeof(int));
			for(student<T> *p = head -> next;p != tail;p = p -> next){
				for(int i=0;i<4;i++){
					string temp=p->getInfo(i);
					int len=temp.length();
					out.write((char*)&len,sizeof(int));
					out.write((char*)temp.c_str(),len*sizeof(char));
				}
				for(int i=0;i<6;i++){
					T temp=p->getScore(i);
					out.write((char*)&temp,sizeof(T));
				}
			}
			cout << "导出到文件 "<<path<<" 成功.\n";
			cout << "共导出 "<<size<<" 人,其中文科生 "<<artSz<<" 人,理科生 "<<size-artSz<<" 人.\n";
		}else
			cout << "导出失败.\n";
	}
private:
	student<T> *head, *tail;
	int size;
	int artSz;
};

int main(){
	app<double> spms;
	spms.show();
	return spms.exec();
}


