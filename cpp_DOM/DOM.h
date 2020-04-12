#ifndef DOM_OBJ
#define DOM_OBJ
#include<initializer_list>
#include<memory>
#include<typeindex>
#include<vector>
#include<string>
#include<iostream>
#include<exception>
namespace DOM
{
    class ItemBase
    {
    public:
        virtual void assign(void* object, std::string type)=0;
    };

	template<typename T,typename M>
	class Item:public ItemBase
	{
        M T::*ptr;
		M value;
	public:
        Item(M T::*ptr,M value):value(value),ptr(ptr){}
        void assign(void* object,std::string type)override
        {
			((T*)object->*ptr)=value;
				//std::cerr<<"无效的初始化: "<<type<<"不存在目标成员。该属性只能初始化"<<typeid(T).name()<<"及其派生类"<<std::endl;
        }
	};

	template<typename T>
	class MutiItem:public ItemBase
	{
		std::vector<ItemBase*> Itemlist;
	public:
		MutiItem(std::initializer_list<ItemBase*> list):Itemlist(list){}
		void assign(void* object, std::string type)override
		{
			for (ItemBase* item : Itemlist)
			{
				item->assign(object,type);
				delete item;
			}
		}
	};
	
	template<typename T,typename M>
	Item<T, M>* item(M T::*ptr,M value)
	{
		return new Item<T,M>(ptr,value);
	};

	using DOM_initializer = std::initializer_list<ItemBase*>;

	template<typename T>
	void moveProperty(DOM_initializer property,T* destination)
	{
		for (ItemBase* iter : property)
		{
			iter->assign(destination,typeid(destination).name());
			delete iter;
		}
	}

}
#endif