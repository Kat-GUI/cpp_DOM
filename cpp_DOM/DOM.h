#ifndef DOM_OBJ
#define DOM_OBJ
#include<initializer_list>
#include<memory>
#include<typeindex>
#include<vector>
namespace DOM
{

    template<typename T>
    class ItemBase
    {
    public:
        virtual void assign(T* object)=0;
    };

	template<typename T,typename M>
	class Item:public ItemBase<T>
	{
        M T::*ptr;
		M value;
	public:
        Item(M T::*ptr,M value):value(value),ptr(ptr){}
        void assign(T* object)override
        {
            (object->*ptr)=value;
        }
	};

	template<typename T>
	class MutiItem:public ItemBase<T>
	{
		std::vector<ItemBase<T>*> Itemlist;
	public:
		MutiItem(std::initializer_list<ItemBase<T>*> list):Itemlist(list)
		{
			Itemlist=list;
			int a=0;
			a++;
		}
		void assign(T* object)override
		{
			for (ItemBase<T>* item : Itemlist)
			{
				item->assign(object);
				delete item;
			}
		}
	};
	
	template<typename T,typename M>
	Item<T, M>* item(M T::*ptr,M value)
	{
		return new Item<T,M>(ptr,value);
	};

	template<typename T>
	using DOM_initializer = std::initializer_list<ItemBase<T>*>;

	template<typename T>
	void moveProperty(DOM_initializer<T> property,T* destination)
	{
		for (ItemBase<T>* iter : property)
		{
			iter->assign(destination);
			delete iter;
		}
	}

}
#endif