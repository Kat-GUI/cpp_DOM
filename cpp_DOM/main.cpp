#include<iostream>
#include"DOM.h"
#include<string>
using namespace DOM;
using namespace std;
class Layout
{
public:
	string id;
	int left = 0;
	int top = 0;
	int right=0;
	int bottom=0;
	int height = 0, width = 0;
	Layout* child;
	Layout()=default;
	Layout(DOM_initializer list)
	{
		moveProperty(list, this);
	}
	void show() 
	{

	}
};
class Widget
{
public:
	Widget(DOM_initializer list)
	{
		moveProperty(list,this);
	}
};
inline auto left(int px) { return item(&Layout::left, px); }
inline auto top(int px) { return item(&Layout::top, px); }
inline auto width(int px) { return item(&Layout::width, px); }
inline auto height(int px) { return item(&Layout::height, px); }
inline auto child(Layout* layout) { return item(&Layout::child, layout); }
inline auto id(string name){return item(&Layout::id,name); }
inline auto margin(int left,int top,int right,int bottom){
	return new MutiItem<Layout>{item(&Layout::left,left),item(&Layout::top,top),item(&Layout::right,right),item(&Layout::bottom,bottom)};
}
inline auto margin(int px){return margin(px,px,px,px);}
#define Position(int )

int main()
{
	//<Layout id="MyWindow",left=10,top=10,width=500,height=300>
	//		<Layout id="child1",width=200,height=200>
	//				<Layout id="child2"/>
	//		<Layout/>
	//<Layout/>

	Widget window = {
		id("MyWindow"),margin(10)
	};
	/*window.show();*/

}