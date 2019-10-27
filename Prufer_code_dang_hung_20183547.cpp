#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int k;
int n;
int dem=0; // bien gioi han so lan in ra
struct PRC //PRufer Code
{
	int cha;
	int bac=0;
};
struct node
{
	vector<int> DK; // mot mang luu tru dinh ke
	int num=0; //so luong dinh ke cua dinh
};
void Enter(node Node[],int &n,PRC List[])//nhap du lieu
{
	int d,dk;
	cout<< "Nhap cac canh: ";
	for(int i=0;i<n;i++)
	{
		cout<< "\nCanh thu "<<i+1<<": ";
		cin>>d>>dk;
		Node[d].DK.push_back(dk);//them cac dinh ke
		Node[d].num++;//cho biet so luong dinh ke cua mot dinh de xet
		Node[dk].DK.push_back(d);
		Node[dk].num++;
		List[d].bac++;//tang bac cua dinh len 1 don vi
		List[dk].bac++;
	}
}
queue<int> myQueue; //thiet lap hang doi

bfs(int u,node Node[],PRC List[],int Free[]) //thuat toan tim kiem chieu rong de thiet lap dinh cha va con
{
	for(int i=0;i<Node[u].num;i++) //duyet tat ca cac dinh ke voi u. khi do u la dinh cha
	{
		if(Free[Node[u].DK.at(i)]==0) //Free de luu cac dinh tu do
			//vi du: nhap 0-2 thi dinh 0 co dinh ke la 2 va nguoc lai
			//khi do sau khi duyet cho 0 la dinh cha cua 2 thi danh dau Free (0)=1 de khi xet dinh 2 phan tu 0 se bi bo qua
		{
			myQueue.push(Node[u].DK.at(i)); //them tat ca cac dinh con vao hang doi
			List[Node[u].DK.at(i)].cha=u;//u la dinh cha cua tat ca dinh con vua xet
		}
	}
	Free[u]=1;//thiet lap dinh u la duoc duyet xong
	myQueue.pop();//xoa dinh u khoi hang doi va duyet dinh dau tien trong hang doi
	if(myQueue.empty()==0)
		bfs(myQueue.front(),Node,List,Free); //front : lay phan tu dau tien cua hang doi
}
test(int &m,PRC List[]) // test de in ra cac dinh co bac 1 nho nhat
{
	if(List[m].bac==1&&m!=0)
	{
		if(dem<n-1) //n-1 la phan tu 0 ta bo qua
		{
			cout<< List[m].cha<<"  ";
			dem++;
		}
		List[m].bac--; //giam bac dinh m
		List[List[m].cha].bac--; // giam bac dinh cha
		if(List[List[m].cha].bac==1&&List[m].cha<=k){
			test(List[m].cha,List);
		}//neu dinh cha co bac 1 thi xet xem da tung xet qua chua. Neu da xet qua tuc la khi xoa dinh con tao ra dinh cha la nho nhat
		//neu chua xet qua thi tuc la co the co dinh nho hon nen ta k xet dinh cha nua
	}
}
int main()
{
	cout<< "Nhap so canh: ";
	cin>>n;
	node Node[n+1];
	PRC List[n+1];
	int Free[n+1];
	for(int i=0;i<n+1;i++)
		Free[i]=0;
	myQueue.push(0);
	Enter(Node,n,List);
	bfs(0,Node,List,Free);
	List[0].cha=0;
	cout<< "\nPrufer codes: ";
	for(int i=1;i<n+1;i++)
		{
			k=i;
			test(i,List);
		}
    return 0;
}
