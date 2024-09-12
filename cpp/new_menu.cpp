#include <iostream>
#include <string>
#include <vector>
//! 多态：父类指针指向子类对象
// 基类尽量少 多在子类中实现 函数不要有太多的功能
class ChangeFunc{
public:
    virtual void show();
    virtual void back();
};

class ChangeGoodMenu : public ChangeFunc{

};

class ChangePersonMenu : public ChangeFunc{

};

class MenuBase{
public:
    std::string title; 
    std::vector<MenuBase*> sub_menu;
    MenuBase(const std::string& t) : title(t) {}
    void add_sub_menu(MenuBase* menu){ sub_menu.push_back(menu); }
    virtual void back(); 
    virtual void change_info();
};

class ChangableMenu : public MenuBase{
public:
    ChangableMenu(const std::string& t) : MenuBase(t) {}
    ChangeFunc* change_func;
};


class PersonMenu : public ChangableMenu{
public:
    PersonMenu(const std::string& t) : ChangableMenu(t) {
        change_func = new ChangePersonMenu();
    }
    void my_info();
    void recharge();
    void change_info() override
    {

    }
    void back() override
    {

    }

};

class SellerMenu : public ChangableMenu{
public:
    SellerMenu(const std::string& t) : ChangableMenu(t) {
        change_func = new ChangeGoodMenu();
    }
    void sell();
    void my_good();
    void delete_good();
    void query_ticket();

    void change_info() override{

    }
    void back() override{

    }

};

class BuyerMenu : public MenuBase{
public:
    void back() override{
        
    }
};

class ManagerMenu : public MenuBase{
public:
    void get_all_good();
    void search_good();
    void query_good();
    void get_all_user();
    void delete_user();
    void delete_good();
    void back() override
    {
        
    }
};

class MenuFactory{
public:
    MenuBase* get_menu(){

    }
};

int main()
{
    
}